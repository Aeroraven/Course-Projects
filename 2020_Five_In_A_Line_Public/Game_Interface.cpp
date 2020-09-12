#include "Game_Interface.h"
#ifdef _WIN32
const Game_Interface::interfaceWin_WinForeColor Game_Interface::interfaceWin_WinForeColorMapping[10] = {
	interfaceWin_WinForeColor_Default,
	interfaceWin_WinForeColor_Black,
	interfaceWin_WinForeColor_Red,
	interfaceWin_WinForeColor_Green,
	interfaceWin_WinForeColor_Yellow,
	interfaceWin_WinForeColor_Blue,
	interfaceWin_WinForeColor_Magenta,
	interfaceWin_WinForeColor_Cyan,
	interfaceWin_WinForeColor_White,
	interfaceWin_WinForeColor_Intensity,

};
const Game_Interface::interfaceWin_WinBackColor Game_Interface::interfaceWin_WinBackColorMapping[10] = {
	interfaceWin_WinBackColor_Default,
	interfaceWin_WinBackColor_Black,
	interfaceWin_WinBackColor_Red,
	interfaceWin_WinBackColor_Green,
	interfaceWin_WinBackColor_Yellow,
	interfaceWin_WinBackColor_Blue,
	interfaceWin_WinBackColor_Magenta,
	interfaceWin_WinBackColor_Cyan,
	interfaceWin_WinBackColor_White,
	interfaceWin_WinBackColor_Intensity
};
#endif
string Game_Interface::interface_asciiControl(int controlPrefix, string controlSuffix) {
	ostringstream strConv;
	string ret;
	ret.append("\033[");
	strConv << controlPrefix; ret.append(strConv.str()); strConv.str("");
	strConv << controlSuffix; ret.append(strConv.str()); strConv.str("");
	return ret;
}


void Game_Interface::interface_clearScreen() {
#ifdef _WIN32
	interfaceWin_clearScreen();
#else
	cout << "\033c";
#endif
}

void Game_Interface::interface_sleep(int microSecond) {
#ifdef _WIN32
	Sleep(microSecond);
#else
	usleep(microSecond*1000);
#endif
	fflush(stdin);
	while (interface_kbhit())interface_getch();
}

bool Game_Interface::interface_kbhit() {
#ifdef _WIN32
	return (bool)_kbhit();
#else
	return (bool)interfaceLinux_kbhit();
#endif
}

int Game_Interface::interface_getOS(){
#ifdef _WIN32
    return 1;
#else
    return 2;
#endif // _WIN32
}

void Game_Interface::interface_toggleCursorDisplay(bool showCursor) {
#ifdef _WIN32
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO stdCursorInfo;
	GetConsoleCursorInfo(stdHandle, &stdCursorInfo);
	stdCursorInfo.bVisible = showCursor;
	SetConsoleCursorInfo(stdHandle, &stdCursorInfo);
#else
	if (showCursor) {
		cout << "\033[?25h";
	}
	else {
		cout << "\033[?25l";
	}
#endif
}

int Game_Interface::interface_getch() {
#ifdef _WIN32
	//fflush(stdin);
	int s = _getch();
	if (s == 224) s = _getch()+224;
	return s;
#else
    int s=interfaceLinux_getch();
    if(s==27) s=interfaceLinux_getch();
    if(s==91) s=interfaceLinux_getch()+1000;
    return s;
#endif
}
int Game_Interface::interface_getEnterKeyVal() {
#ifdef _WIN32
	return 13;
#else
	return 13;
#endif
}

void Game_Interface::interface_setPos(int x, int y) {
#ifdef _WIN32
	interfaceWin_setPos(x, y);
#else
	printf("%c[%d;%df",0x1b,y,x);
    cout<<"\033[?25l";
#endif
}

void Game_Interface::interface_disableScale() {
#ifdef _WIN32
	interfaceWin_disableScale();
#else
	
#endif
}

void Game_Interface::interface_disableConsoleEdit() {
#ifdef _WIN32
	interfaceWin_disableConsoleEdit();
#else
	
#endif
}

Game_Interface::base_InputInfo Game_Interface::interface_getInput() {
#ifdef _WIN32
	return interfaceWin_getConsoleInput();
#else

#endif
}

Game_Interface::base_InputInfo Game_Interface::interface_getActivatedInput(bool allowMouse, bool allowKeyboard) {
#ifdef _WIN32
	base_InputInfo ret;
	while (1) {
		if (allowMouse) {
			interface_enableMouseInput();
		}
		ret = interface_getInput();
		interface_disableMouseInput();
		if (ret.deviceType == 1 && allowMouse) {
			if (ret.mouseExtInfo2 == 1 ) {
				return ret;
			}
		}
		else if (ret.deviceType == 2 && allowKeyboard) {
			if (ret.keyDown == true) {
				return ret;
			}
		}
	}
	return ret;
#else
	
#endif
}
void Game_Interface::interface_enableMouseInput() {
#ifdef _WIN32
	interfaceWin_enableMouseInput();
#else
	
#endif
}
void Game_Interface::interface_disableMouseInput() {
#ifdef _WIN32
	interfaceWin_disableMouseInput();
#endif
}
void Game_Interface::interface_changeCodePage(base_Encoding codeType) {
#ifdef _WIN32
	interfaceWin_chcp(codeType);
#endif
}

int Game_Interface::interface_GetCodepage() {
#ifdef _WIN32
	return interfaceWin_getConsoleCodepage();
#endif
	return -1;
}

#ifdef _WIN32
void Game_Interface::interfaceWin_setPos(int x, int y) {
	COORD cursorPos = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}
void Game_Interface::interfaceWin_clearScreen() {
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	COORD cursorPos;
	SMALL_RECT sRect;
	CHAR_INFO charFill;
	if (!GetConsoleScreenBufferInfo(stdHandle, &bufferInfo)) return;
	sRect.Left = 0, sRect.Top = 0;
	sRect.Right = bufferInfo.dwSize.X, sRect.Bottom = bufferInfo.dwSize.Y;
	cursorPos.X = 0;
	cursorPos.Y = -bufferInfo.dwSize.Y;
	charFill.Char.UnicodeChar = L' ';
	charFill.Attributes = bufferInfo.wAttributes;
	ScrollConsoleScreenBufferW(stdHandle, &sRect, NULL, cursorPos, &charFill);
	cursorPos.Y = 0;
	SetConsoleCursorPosition(stdHandle, cursorPos);
}
void Game_Interface::interfaceWin_disableScale() {
	SetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE, GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE)& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
}
void Game_Interface::interfaceWin_disableConsoleEdit() {
	HANDLE stdHandle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(stdHandle, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(stdHandle, mode);
}
void Game_Interface::interfaceWin_disableMouseInput() {
	HANDLE stdHandle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(stdHandle, &mode);
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(stdHandle, mode);
}
Game_Interface::base_InputInfo Game_Interface::interfaceWin_getConsoleInput() {
	HANDLE hstdIn, hstdOut;
	INPUT_RECORD inputRecord;
	DWORD res;
	hstdIn = GetStdHandle(STD_INPUT_HANDLE);
	hstdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ReadConsoleInput(hstdIn, &inputRecord, 1, &res);
	if (inputRecord.EventType == MOUSE_EVENT) { //鼠标事件
		COORD mPos;
		base_InputInfo mouseRet;
		mouseRet.deviceType = 1;
		mPos = inputRecord.Event.MouseEvent.dwMousePosition;
		mouseRet.mouseInfo.x = mPos.X;
		mouseRet.mouseInfo.y = mPos.Y;
		mouseRet.mouseExtInfo = (int)inputRecord.Event.MouseEvent.dwEventFlags;
		mouseRet.mouseExtInfo2 = (int)inputRecord.Event.MouseEvent.dwButtonState;
		return mouseRet;
	}
	else if(inputRecord.EventType==KEY_EVENT) { //键盘事件
		base_InputInfo keyboardRet;
		keyboardRet.deviceType = 2;
		keyboardRet.keyInfo = (int)inputRecord.Event.KeyEvent.wVirtualKeyCode;
		keyboardRet.keyDown = inputRecord.Event.KeyEvent.bKeyDown;
		return keyboardRet;
	}
	else { //其他事件
		base_InputInfo emptyRet;
		emptyRet.deviceType = 3;
		return emptyRet;
	}
}
void Game_Interface::interfaceWin_enableMouseInput() {
	HANDLE stdHandle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(stdHandle, &mode);
	mode = mode | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(stdHandle, mode);
}
void Game_Interface::interfaceWin_chcp(base_Encoding codeType) {
	switch (codeType){
	case base_Encoding_GBK:
		system("chcp 936");
		break;
	case base_Encoding_UTF8:
		system("chcp 65001");
		break;
	default:
		break;
	}
	interface_clearScreen();
}
int Game_Interface::interfaceWin_getConsoleCodepage() {
	return GetConsoleCP();
}

#endif

#ifndef _WIN32
int Game_Interface::interfaceLinux_getch(){
    struct termios tm, tm_old;
    int fd = 0, ch;
    if (tcgetattr(fd, &tm) < 0) {
      return -1;
    }
    tm_old = tm;
    cfmakeraw(&tm);
    if (tcsetattr(fd, TCSANOW, &tm) < 0) {
      return -1;
    }
    ch = getchar();
    if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
      return -1;
    }
    return ch;
}
int Game_Interface::interfaceLinux_kbhit() {
	struct termios oldt, newt;
	int ch;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}
#endif
