#pragma once
#include "Game_Common.h"
#include "Game_Display.h"
#include "Game_Board.h"
#include "Game_Operation.h"
#include "Game_Layout.h"
#include "Game_File.h"
class Game_Main :public Game_Common{
private:
	int langPresel,seriesID;
	string vck = base_GameAuthor.authorName;
public:
	void main_Init();
	void main_SingleGameTest(int& retVal, int areaId,bool usingSave,Game_Save& saveData);
	void main_MainTitle();
	void main_LanguagePreselection();
};

