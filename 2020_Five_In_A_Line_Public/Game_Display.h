#pragma once
#include "Game_Common.h"
#include "Game_Interface.h"

class Game_Display :public Game_Common{
private:
	Game_Interface sysInf;
public:
	void display_sleep(int microseconds);
	void display_cls();
	void display_hideCursor();
	void display_WinOSInit();
	void display_LinuxInit();
	void display_WinChcp_GBK();
	void display_WinChcp_UTF8();
};

