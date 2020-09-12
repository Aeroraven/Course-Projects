#include "Game_Main.h"
void Game_Call() {
	Game_Main five_in_a_line;
	five_in_a_line.main_Init();
	five_in_a_line.main_LanguagePreselection();
	five_in_a_line.main_MainTitle();
}
int main() {
	_CHECK_MEMORY_LEAKS();
	Game_Call();
	return 0;
}