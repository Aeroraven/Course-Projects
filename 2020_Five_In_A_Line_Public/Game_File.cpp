#include "Game_File.h"

Game_File::Game_File(int areaId) {
	langObj = new Game_Localization(areaId);
}
Game_File::~Game_File() {
	delete langObj;
}
void Game_File::gamefile_Save(Game_Save& svdata) {
	ofstream saveFile;
	ofstream saveFileSig;
	string exts;
	string digest;
	Game_ExceptionHandle fileExcept(langObj->lang_GetDefaultArea());
	Game_SaveCompatible saveBin;
	try {
		saveFile.open("GameSave.dat",ios::out|ios::binary);
		saveFileSig.open("GameSaveSignature.dat");
		if (saveFile.fail()) {
			throw Game_Exception::GameException_FileOutput(langObj->lang_GetDefaultArea());
		}
		if (saveFileSig.fail()) {
			throw Game_Exception::GameException_FileOutput(langObj->lang_GetDefaultArea());
		}
		svdata.save_ConvertToCompat(saveBin);
		saveFile.write((char*)&saveBin, sizeof(saveBin));
		digest = svdata.save_GetCompatDigest(saveBin);
		
		saveFileSig << digest;
		saveFile.close();
		saveFileSig.close();
	}
	catch (Game_ExceptionBase& except) {
		fileExcept.except_UserChoice(except);
	}
}
int Game_File::gamefile_LoadCompat(Game_SaveCompatible& svcompData) {
	ifstream saveFile;
	ifstream saveFileSig;
	string digest;
	string digestSaved;
	Game_ExceptionHandle fileExcept(langObj->lang_GetDefaultArea());
	Game_Save saveMain(langObj->lang_GetDefaultArea());
	try {
		saveFile.open("GameSave.dat", ios::in | ios::binary);
		saveFileSig.open("GameSaveSignature.dat");
		if (saveFile.fail()) {
			throw Game_Exception::GameException_FileInput(langObj->lang_GetDefaultArea());
		}
		if (saveFileSig.fail()) {
			throw Game_Exception::GameException_FileInput(langObj->lang_GetDefaultArea());
		}
		saveFile.read((char*)&svcompData, sizeof(svcompData));
		digest = saveMain.save_GetCompatDigest(svcompData);
		saveFileSig >> digestSaved;
		if (digestSaved != digest) {
			saveFile.close();
			saveFileSig.close();
			throw Game_Exception::GameException_FileSignatureBroken(langObj->lang_GetDefaultArea());
		}
		if (svcompData.save_VitalGameArgv_Height != base_DefaultBoardHeight ||
			svcompData.save_VitalGameArgv_TypeCount != base_DefaultBeadTypes ||
			svcompData.save_VitalGameArgv_Width != base_DefaultBoardWidth) {
			saveFile.close();
			saveFileSig.close();
			throw Game_Exception::GameException_FileSettingsIncompatible(langObj->lang_GetDefaultArea());
		}

		saveMain.save_CompatDecrypt(svcompData);


		saveFile.close();
		saveFileSig.close();
		
		return 1;
	}
	catch (Game_ExceptionBase& except) {
		fileExcept.except_UserChoice(except);
		return 2;
	}
}
int Game_File::gamefile_Load(Game_Save& svdata) {
	Game_SaveCompatible svcmpData;
	Game_Algorithm::Base64 b64;
	int loadStatus = gamefile_LoadCompat(svcmpData);
	if (loadStatus == 2) return 2;
	svdata.save_BoardData = b64.base64_Decode(svcmpData.save_BoardData);
	svdata.save_BoardData_Validator = svcmpData.save_BoardData_Validator;
	svdata.save_PlayerScore = svcmpData.save_PlayerScore;
	svdata.save_PlayerScoreMap = svcmpData.save_PlayerScoreMap;
	svdata.save_PlayerScoreSeed = svcmpData.save_PlayerScoreSeed;
	svdata.save_PlayerScoreMap_Validator = svcmpData.save_PlayerScoreMap_Validator;
	svdata.save_PlayerScore_Validator = svcmpData.save_PlayerScore_Validator;
	svdata.save_PlayerScoreSeed_Validator = svcmpData.save_PlayerScoreSeed_Validator;
	svdata.save_GameArgv1 = svcmpData.save_GameArgv1;
	svdata.save_GameArgv2 = svcmpData.save_GameArgv2;
	svdata.save_GameArgv3 = svcmpData.save_GameArgv3;
	svdata.save_GameArgv_Foresee = svcmpData.save_GameArgv_Foresee;
	svdata.save_GameArgv_MoveLimit = svcmpData.save_GameArgv_MoveLimit;
	svdata.save_VitalGameArgv_Height = svcmpData.save_VitalGameArgv_Height;
	svdata.save_VitalGameArgv_Width = svcmpData.save_VitalGameArgv_Width;
	svdata.save_VitalGameArgv_TypeCount = svcmpData.save_VitalGameArgv_TypeCount;
	return 1;
}
Game_Save::Game_Save(int areaId) {
	saveLang = new Game_Localization(areaId);
}
Game_Save::~Game_Save(){
	delete saveLang;
}
void Game_Save::save_RandomFill(char* dest, int size) {
	for (int i = 0; i < size; i++) {
		dest[i] = (char)base_RandInt(-127, 127);
		if (dest[i] == (char)0)dest[i] = (char)1;
	}
}
void Game_Save::save_StrEncrypt(char* dest, int size,int key) {
	Game_Algorithm::HashCode hashcode;
	hashcode.hash_SetSeed(key);
	char sc;
	if (size > GAMESAVE_DEFAULT_MAXSPACE) throw Game_Exception::GameException_FileBroken(saveLang->lang_GetDefaultArea());
	for (int i = 0; i < size; i++) {
		sc = (char)hashcode.hash_GetRangedCode(i, -90, 90);
		if (sc == 0)sc = 1;
		dest[i] = (char)((char)dest[i] ^ (char)sc);
	}
}

void Game_Save::save_CompatDecrypt(Game_SaveCompatible& p) {
	int key = p.save_RandomKey;
	
	save_StrEncrypt(p.save_BoardData,p.save_BoardData_Len,key);
	save_StrEncrypt(p.save_BoardData_Validator,p.save_BoardData_Validator_Len,  key);
	save_StrEncrypt(p.save_PlayerScore_Validator,p.save_PlayerScore_Validator_Len, key);
	save_StrEncrypt(p.save_PlayerScoreMap_Validator,p.save_PlayerScoreMap_Validator_Len, key);
	save_StrEncrypt(p.save_PlayerScoreSeed_Validator,p.save_PlayerScoreSeed_Validator_Len, key);
}

string Game_Save::save_GetCompatDigest(Game_SaveCompatible &p) {
	Game_Algorithm::Base64 b64;
	Game_Algorithm::HashAlgorithms hashValidate;
	Game_Algorithm::HashCode hsc;
	string digest,tp2;
	unsigned int crc = hashValidate.hash_crc32(b64.base64_Encode(string((char*)&p)));
	int g = (int)(crc >> 1U);
	int tp;
	hsc.hash_SetSeed(g);
	digest = base_Any2String(crc);
	digest += b64.base64_Encode(base_Any2String(hashValidate.hash_crc32(base_Any2String(p.save_RandomKey))));
	reverse(digest.begin(), digest.end());
	digest = b64.base64_Encode(digest);
	tp = digest.length();
	tp2 = base_Any2String(hsc.hash_GetCode(tp));
	reverse(tp2.begin(), tp2.end());
	tp2 = b64.base64_Encode(tp2);
	digest = tp2 + digest;
	digest = b64.base64_Encode(digest);
	
	return digest;
}

void Game_Save::save_ConvertToSave(Game_Player* playerObj, Game_Board* boardObj) {
	base_Pair p;
	Game_Algorithm::Base64 b64;
	Game_Algorithm::HashAlgorithms hashValidate;
	save_PlayerScore = playerObj->player_GetScores();
	save_PlayerScoreMap = playerObj->player_GetScoreMap();
	save_PlayerScoreSeed = playerObj->player_GetSeed();

	for (int i = 0; i < boardObj->board_GetSize(); i++) {
		p = boardObj->board_GetPID(i);
		save_BoardData += base_Any2String(boardObj->board_GetElement(p.x, p.y));
		save_BoardData += ",";
	}
	save_BoardData = b64.base64_Encode(save_BoardData);
	save_BoardData_Validator = b64.base64_Encode(base_Any2String(hashValidate.hash_crc32(b64.base64_Encode(save_BoardData))));
	save_PlayerScore_Validator = b64.base64_Encode(base_Any2String(hashValidate.hash_crc32(base_Any2String(save_PlayerScore))));
	save_PlayerScoreMap_Validator = b64.base64_Encode(base_Any2String(hashValidate.hash_crc32(base_Any2String(save_PlayerScoreMap))));
	save_PlayerScoreSeed_Validator = b64.base64_Encode(base_Any2String(hashValidate.hash_crc32(base_Any2String(save_PlayerScoreSeed))));

}
void Game_Save::save_ConvertToCompat(Game_SaveCompatible& p) {
	base_Randomize();
	base_RandInt(1, 127);
	p.save_RandomKey = base_RandInt(1, 32760);
	for (int i = 0; i < GAMESAVE_INTERFERE_SIZE; i++) {
		p.save_RandomFactors[i] = base_RandInt(1, 32760);
	}
	char ap;
	save_RandomFill(p.save_BoardData, sizeof(p.save_BoardData) / sizeof(ap));
	save_RandomFill(p.save_BoardData_Validator,  sizeof(p.save_BoardData_Validator) / sizeof(ap));
	save_RandomFill(p.save_PlayerScore_Validator,  sizeof(p.save_PlayerScore_Validator) / sizeof(ap));
	save_RandomFill(p.save_PlayerScoreMap_Validator,  sizeof(p.save_PlayerScoreMap_Validator) / sizeof(ap));
	save_RandomFill(p.save_PlayerScoreSeed_Validator,  sizeof(p.save_PlayerScoreSeed_Validator) / sizeof(ap));

	this->save_BoardData.copy(p.save_BoardData, this->save_BoardData.length(), 0);
	*(p.save_BoardData + this->save_BoardData.length()) = '\0';
	save_StrEncrypt(p.save_BoardData, this->save_BoardData.length(), p.save_RandomKey);

	this->save_BoardData_Validator.copy(p.save_BoardData_Validator, this->save_BoardData_Validator.length(), 0);
	*(p.save_BoardData_Validator + this->save_BoardData_Validator.length()) = '\0';
	save_StrEncrypt(p.save_BoardData_Validator, this->save_BoardData_Validator.length(), p.save_RandomKey);

	p.save_PlayerScore = this->save_PlayerScore;
	this->save_PlayerScore_Validator.copy(p.save_PlayerScore_Validator, this->save_PlayerScore_Validator.length(), 0);
	*(p.save_PlayerScore_Validator + this->save_PlayerScore_Validator.length()) = '\0';
	save_StrEncrypt(p.save_PlayerScore_Validator, this->save_PlayerScore_Validator.length(), p.save_RandomKey);

	p.save_PlayerScoreMap = this->save_PlayerScoreMap;
	this->save_PlayerScoreMap_Validator.copy(p.save_PlayerScoreMap_Validator, this->save_PlayerScoreMap_Validator.length(), 0);
	*(p.save_PlayerScoreMap_Validator + this->save_PlayerScoreMap_Validator.length()) = '\0';
	save_StrEncrypt(p.save_PlayerScoreMap_Validator, this->save_PlayerScoreMap_Validator.length(), p.save_RandomKey);

	p.save_PlayerScoreSeed = this->save_PlayerScoreSeed;
	this->save_PlayerScoreSeed_Validator.copy(p.save_PlayerScoreSeed_Validator, this->save_PlayerScoreSeed_Validator.length(), 0);
	*(p.save_PlayerScoreSeed_Validator + this->save_PlayerScoreSeed_Validator.length()) = '\0';
	save_StrEncrypt(p.save_PlayerScoreSeed_Validator, this->save_PlayerScoreSeed_Validator.length(), p.save_RandomKey);

	p.save_BoardData_Len = this->save_BoardData.length();
	p.save_BoardData_Validator_Len = this->save_BoardData_Validator.length();
	p.save_PlayerScoreMap_Validator_Len = this->save_PlayerScoreMap_Validator.length();
	p.save_PlayerScoreSeed_Validator_Len = this->save_PlayerScoreSeed_Validator.length();
	p.save_PlayerScore_Validator_Len = this->save_PlayerScore_Validator.length();

	p.save_GameArgv1 = this->save_GameArgv1;
	p.save_GameArgv2 = this->save_GameArgv2;
	p.save_GameArgv3 = this->save_GameArgv3;
	p.save_GameArgv_MoveLimit = this->save_GameArgv_MoveLimit;
	p.save_GameArgv_Foresee = this->save_GameArgv_Foresee;
	p.save_VitalGameArgv_Height = this->save_VitalGameArgv_Height;
	p.save_VitalGameArgv_TypeCount = this->save_VitalGameArgv_TypeCount;
	p.save_VitalGameArgv_Width = this->save_VitalGameArgv_Width;
}