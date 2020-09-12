#include "Game_Common.h"
void Game_Common::base_Randomize(int randSeed) {
	srand(randSeed);
}
int Game_Common::base_RandInt(int randLBound, int randUbound) {
	return randLBound + rand() % (randUbound - randLBound + 1);
}
