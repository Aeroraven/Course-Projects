#include "Game_Exception.h"
//异常处理 - 文件读入
Game_Exception::GameException_FileInput::GameException_FileInput(int AreaId) {
	x = new Game_Localization(AreaId);
}
Game_Exception::GameException_FileInput::~GameException_FileInput() {
	delete x;
}
string Game_Exception::GameException_FileInput::what() {
	return x->lang_GetString(x->TEXT_EXCEPTION_FILEIO_INPUT_FAILED);
}


// 异常处理 - 文件输出
Game_Exception::GameException_FileOutput::GameException_FileOutput(int AreaId) {
	x = new Game_Localization(AreaId);
}
Game_Exception::GameException_FileOutput::~GameException_FileOutput() {
	delete x;
}
string Game_Exception::GameException_FileOutput::what() {
	return (x->lang_GetString(x->TEXT_EXCEPTION_FILEIO_OUTPUT_FAILED));
}

// 异常处理 - 文件损坏
Game_Exception::GameException_FileBroken::GameException_FileBroken(int AreaId) {
	x = new Game_Localization(AreaId);
}
Game_Exception::GameException_FileBroken::~GameException_FileBroken() {
	delete x;
}
string Game_Exception::GameException_FileBroken::what()  {
	return (x->lang_GetString(x->TEXT_EXCEPTION_FILEIO_FILE_BROKEN));
}

// 异常处理 - 文件损坏2
Game_Exception::GameException_FileSignatureBroken::GameException_FileSignatureBroken(int AreaId) {
	x = new Game_Localization(AreaId);
}
Game_Exception::GameException_FileSignatureBroken::~GameException_FileSignatureBroken() {
	delete x;
}
string Game_Exception::GameException_FileSignatureBroken::what() {
	return (x->lang_GetString(x->TEXT_EXCEPTION_FILEIO_SIGNATURE_CONFLICT));
}

// 异常处理 - 游戏存档不兼容
Game_Exception::GameException_FileSettingsIncompatible::GameException_FileSettingsIncompatible(int AreaId) {
	x = new Game_Localization(AreaId);
}
Game_Exception::GameException_FileSettingsIncompatible::~GameException_FileSettingsIncompatible() {
	delete x;
}
string Game_Exception::GameException_FileSettingsIncompatible::what() {
	return (x->lang_GetString(x->TEXT_EXCEPTION_FILEIO_GAMESETTINGS_CONFLICT));
}

//异常处理
Game_ExceptionHandle::Game_ExceptionHandle(int AreaId) {
	x = new Game_Localization(AreaId);
}
Game_ExceptionHandle::~Game_ExceptionHandle() {
	delete x;
}
int Game_ExceptionHandle::except_UserChoice(Game_ExceptionBase& exceptSource) {
	Game_Interface sysInf;
	Game_Input sysInp;
	int offset = 23;
	sysInf.interface_clearScreen();
	sysInf.interface_setPos(offset, 10);
	cout << x->lang_GetString(x->TEXT_EXCEPTHANDLE_HEADER);
	sysInf.interface_setPos(offset+5, 12);
	cout << exceptSource.what() << endl;
	sysInf.interface_setPos(offset+5, 14);
	cout << x->lang_GetString(x->TEXT_INFO_PRESS_ANY_KEY_TO_CONTINUE);
	sysInf.interface_setPos(offset, 16);
	cout << "----------------------------------------------------------------------------" << endl;
	sysInp.input_pressKeyToContinue();
	sysInf.interface_clearScreen();
	return 1;
}