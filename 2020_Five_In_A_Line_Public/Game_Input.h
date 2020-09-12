#pragma once
#include "Game_Common.h"
#include "Game_Interface.h"
#include "Game_Algorithm.h"
class Game_Input :public Game_Common{
	Game_Interface sysInf;
public:
	void input_readInputCoord(int& acceptant,string prInf="",int encodingType=base_Encoding_GBK );
	void input_pressKeyToContinue();
	void input_pressEnterToContinue();
	int input_readCh();
	int input_enterKeyVal();
	base_InputInfo input_MouseInput();
	base_InputInfo input_CompInput();

	void inputDebug_inputTest();
};

