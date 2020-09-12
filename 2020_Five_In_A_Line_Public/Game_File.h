#pragma once
#include "Game_Common.h"
#include "Game_Interface.h"
#include "Game_Localization.h"
#include "Game_Board.h"
#include "Game_Exception.h"
#include "Game_Player.h"
#include "Game_Algorithm.h"
#define GAMESAVE_DEFAULT_MAXSPACE 1000
#define GAMESAVE_INTERFERE_SIZE 700
//´æµµÄÚÈÝ
class Game_SaveCompatible {
public:
	int save_RandomFactors[GAMESAVE_INTERFERE_SIZE];
	int save_GameArgv1;
	int save_GameArgv2;
	int save_GameArgv3;
	bool save_GameArgv_MoveLimit;
	bool save_GameArgv_Foresee;

	char save_BoardData[GAMESAVE_DEFAULT_MAXSPACE];
	int save_BoardData_Len;
	char save_BoardData_Validator[GAMESAVE_DEFAULT_MAXSPACE];
	int save_BoardData_Validator_Len;

	int save_PlayerScore;
	char save_PlayerScore_Validator[GAMESAVE_DEFAULT_MAXSPACE];
	int save_PlayerScore_Validator_Len;

	int save_PlayerScoreMap;
	char save_PlayerScoreMap_Validator[GAMESAVE_DEFAULT_MAXSPACE];
	int save_PlayerScoreMap_Validator_Len;

	int save_PlayerScoreSeed;
	char save_PlayerScoreSeed_Validator[GAMESAVE_DEFAULT_MAXSPACE];
	int save_PlayerScoreSeed_Validator_Len;

	int save_RandomKey;

	int save_VitalGameArgv_Height;
	int save_VitalGameArgv_Width;
	int save_VitalGameArgv_TypeCount;

};
class Game_Save:public Game_Common {
private:
	Game_Localization* saveLang;
public:
	string save_BoardData;
	string save_BoardData_Validator;
	int save_PlayerScore;
	string save_PlayerScore_Validator;
	int save_PlayerScoreMap;
	string save_PlayerScoreMap_Validator;
	int save_PlayerScoreSeed;
	string save_PlayerScoreSeed_Validator;
	
	int save_GameArgv1;
	int save_GameArgv2;
	int save_GameArgv3;
	bool save_GameArgv_MoveLimit;
	bool save_GameArgv_Foresee;

	int save_VitalGameArgv_Height;
	int save_VitalGameArgv_Width;
	int save_VitalGameArgv_TypeCount;

	Game_Save(int areaId);
	~Game_Save();
	void save_ConvertToSave(Game_Player* playerObj,Game_Board* boardObj);
	void save_ConvertToCompat(Game_SaveCompatible& p);
	void save_RandomFill(char* dest, int size);
	void save_StrEncrypt(char* dest, int size, int key);
	string save_GetCompatDigest(Game_SaveCompatible& p);
	void save_CompatDecrypt(Game_SaveCompatible& p);
	string save_GetValidator(string source);
};

//ÎÄ¼þ¶ÁÐ´
class Game_File :public Game_Common {
private:
	Game_Localization* langObj;
public:
	Game_File(int areaId);
	~Game_File();
	void gamefile_Save(Game_Save& svdata);
	int gamefile_LoadCompat(Game_SaveCompatible& svcompData);
	int gamefile_Load(Game_Save& svdata);
};

