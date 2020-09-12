#include "Game_Player.h"
Game_Player::Game_Player(int initScores, string initPlayerName, bool initIntelligence) {
	player_Scores = initScores;
	player_cheatRecorded = false;
	player_SetName(initPlayerName);
	player_SetOrder(-1);
	player_SetIntelligence(initIntelligence);
	player_hshc.hash_SetSeed(base_RandInt(1, 32700));
	player_ScoreMap = player_hshc.hash_GetCode(player_Scores);
}
int Game_Player::player_GetScores() { return player_Scores; }
string Game_Player::player_GetName() { return player_Name; }
bool Game_Player::player_IsIntelligence() { return player_Intelligence; }
int Game_Player::player_GetOrder() { return player_Order; }

void Game_Player::player_SetScore(int setValue) {
	if (player_ValidateCheat()) {
		player_cheatRecorded = true;
	}
	player_Scores = setValue;
	player_ScoreMap = player_hshc.hash_GetCode(player_Scores);
}
void Game_Player::player_AddScore(int deltaValue) {
	player_Scores += deltaValue;
	player_ScoreMap = player_hshc.hash_GetCode(player_Scores);
}
void Game_Player::player_SetName(string setValue) {
	player_Name = setValue;
}
void Game_Player::player_SetIntelligence(bool setValue) {
	player_Intelligence = setValue;
}
void Game_Player::player_SetOrder(int setValue) {
	player_Order = setValue;
}
void Game_Player::player_SetSeed(int setValue) {
	player_hshc.hash_SetSeed(setValue);
	player_ScoreMap = player_hshc.hash_GetCode(player_Scores);
}
bool Game_Player::player_ValidateCheat() {
	if (player_cheatRecorded) {
		return true;
	}
	if (player_ScoreMap ==  player_hshc.hash_GetCode(player_Scores)) {
		return false;
	}
	return true;
}

string Game_Player::player_getAddr() {
	stringstream oss;
	oss << (&player_Scores);
	return oss.str();
}

int Game_Player::player_GetScoreMap() {
	return player_ScoreMap;
}
int Game_Player::player_GetSeed() {
	return player_hshc.hash_GetSeed();
}