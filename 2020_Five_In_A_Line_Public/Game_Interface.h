#pragma once
#include "Game_Common.h"
#ifndef _WIN32

#endif

class Game_Interface :public Game_Common{
private:
#ifdef _WIN32
	//Windows 前景色常量
	enum interfaceWin_WinForeColor {
		interfaceWin_WinForeColor_Default = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
		interfaceWin_WinForeColor_Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		//interfaceWin_WinForeColor_Blue =  FOREGROUND_RED,
		interfaceWin_WinForeColor_Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_Magenta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		interfaceWin_WinForeColor_Cyan = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_White = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_Gray = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_DarkRed = FOREGROUND_RED,
		interfaceWin_WinForeColor_DarkGreen = FOREGROUND_GREEN,
		interfaceWin_WinForeColor_DarkBlue = FOREGROUND_BLUE,
		interfaceWin_WinForeColor_DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
		interfaceWin_WinForeColor_DarkCyan = FOREGROUND_BLUE | FOREGROUND_GREEN,
		interfaceWin_WinForeColor_Black = 0,
		interfaceWin_WinForeColor_Intensity = FOREGROUND_INTENSITY
	};

	//Windows 背景色常量
	enum interfaceWin_WinBackColor {
		interfaceWin_WinBackColor_Default = 0,
		interfaceWin_WinBackColor_Red = BACKGROUND_INTENSITY | BACKGROUND_RED,
		interfaceWin_WinBackColor_Green = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		interfaceWin_WinBackColor_Blue = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		interfaceWin_WinBackColor_Yellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		interfaceWin_WinBackColor_Magenta = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		interfaceWin_WinBackColor_Cyan = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN,
		interfaceWin_WinBackColor_White = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		interfaceWin_WinBackColor_Gray = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		interfaceWin_WinBackColor_DarkRed = BACKGROUND_RED,
		interfaceWin_WinBackColor_DarkGreen = BACKGROUND_GREEN,
		interfaceWin_WinBackColor_DarkBlue = BACKGROUND_BLUE,
		interfaceWin_WinBackColor_DarkYellow = BACKGROUND_RED | BACKGROUND_GREEN,
		interfaceWin_WinBackColor_DarkMagenta = BACKGROUND_RED | BACKGROUND_BLUE,
		interfaceWin_WinBackColor_DarkCyan = BACKGROUND_BLUE | BACKGROUND_GREEN,
		interfaceWin_WinBackColor_Black = 0,
		interfaceWin_WinBackColor_Intensity = BACKGROUND_INTENSITY
	};
	const static interfaceWin_WinForeColor interfaceWin_WinForeColorMapping[10];
	const static interfaceWin_WinBackColor interfaceWin_WinBackColorMapping[10];
#endif
public:
	string interface_asciiControl(int controlPrefix, string controlSuffix = "m");
	template<typename Any>string interface_colorOutputStr(Any outputString, base_ColorID outputForeColor = base_ColorID_Default, base_ColorID outputBackColor = base_ColorID_Default);
	template<typename Any>void interface_colorOutput(Any outputString, base_ColorID outputForeColor = base_ColorID_Default, base_ColorID outputBackColor = base_ColorID_Default);
	void interface_clearScreen();
	void interface_setPos(int x, int y);
	bool interface_kbhit();
	void interface_sleep(int microSecond);
	void interface_toggleCursorDisplay(bool showCursor = true);
	int interface_getch();
	int interface_getEnterKeyVal();
	int interface_getOS();
	base_InputInfo interface_getInput();
	base_InputInfo interface_getActivatedInput(bool allowMouse=true, bool allowKeyboard=true);

	void interface_disableScale();
	void interface_disableConsoleEdit();
	void interface_enableMouseInput();
	void interface_disableMouseInput();
	void interface_changeCodePage(base_Encoding codeType);
	int interface_GetCodepage();

private:
#ifdef _WIN32
	void interfaceWin_setPos(int x, int y);
	void interfaceWin_clearScreen();
	void interfaceWin_disableScale();
	void interfaceWin_disableConsoleEdit();
	void interfaceWin_enableMouseInput();
	void interfaceWin_disableMouseInput();
	base_InputInfo interfaceWin_getConsoleInput();
	void interfaceWin_chcp(base_Encoding codeType);
	int interfaceWin_getConsoleCodepage();
#else
    int interfaceLinux_getch();
	int interfaceLinux_kbhit();
#endif

};

template<typename Any> string Game_Interface::interface_colorOutputStr(Any outputString, base_ColorID outputForeColor, base_ColorID outputBackColor) {
	ostringstream strConv;
	string ret;
	strConv << outputString;
	string foreColorAscStr = outputForeColor ? interface_asciiControl(29 + outputForeColor) : "";
	string backColorAscStr = outputBackColor ? interface_asciiControl(39 + outputBackColor) : "";
	ret = foreColorAscStr + backColorAscStr + strConv.str() + interface_asciiControl(0);
	return ret;
}

template<typename Any>void Game_Interface::interface_colorOutput(Any outputString, base_ColorID outputForeColor, base_ColorID outputBackColor) {
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(unsigned short)((unsigned short)interfaceWin_WinForeColorMapping[(int)outputForeColor] | (unsigned short)interfaceWin_WinBackColorMapping[(int)outputBackColor]));
	cout << outputString;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (unsigned short)((unsigned short)interfaceWin_WinForeColor_White | (unsigned short)interfaceWin_WinBackColor_Black));
#else
    cout << interface_colorOutputStr(outputString, outputForeColor, outputBackColor)<<flush;

#endif
}
