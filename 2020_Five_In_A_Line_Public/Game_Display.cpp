#include "Game_Display.h"

void Game_Display::display_sleep(int microseconds) {
	sysInf.interface_sleep(microseconds);
}
void Game_Display::display_cls() {
	sysInf.interface_clearScreen();
}
//void Game_Display::display_adjustCurPos() {
//	sysInf.interface_setPos(0, 40);
//}
void Game_Display::display_hideCursor() {
	sysInf.interface_toggleCursorDisplay(false);
}
void Game_Display::display_WinOSInit() {
#ifdef _WIN32
	sysInf.interface_disableScale();
	sysInf.interface_disableConsoleEdit();
	sysInf.interface_enableMouseInput();
#endif
}
void Game_Display::display_LinuxInit(){
#ifndef _WIN32

#endif // _WIN32
}
void Game_Display::display_WinChcp_GBK() {
	sysInf.interface_changeCodePage(base_Encoding_GBK);
}
void Game_Display::display_WinChcp_UTF8() {
	sysInf.interface_changeCodePage(base_Encoding_UTF8);
}