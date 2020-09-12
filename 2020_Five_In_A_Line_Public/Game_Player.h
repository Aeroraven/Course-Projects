#pragma once
#include "Game_Common.h"
#include "Game_Algorithm.h"
class Game_Player :public Game_Common{
	int player_Scores,player_ScoreMap;
	string player_Name;
	bool player_Intelligence;
	bool player_cheatRecorded;
	int player_Order;
	string player_getAddr(); //PRIVATE 
	Game_Algorithm::HashCode player_hshc;
public:
	Game_Player(int initScores = 0, string initPlayerName = "", bool initIntelligence = false);

	int player_GetScores();
	string player_GetName();
	bool player_IsIntelligence();
	int player_GetOrder();
	int player_GetScoreMap();
	int player_GetSeed();

	void player_SetScore(int setValue);
	void player_AddScore(int deltaValue);
	void player_SetName(string setValue);
	void player_SetIntelligence(bool setValue);
	void player_SetOrder(int setValue);
	void player_SetSeed(int setValue);

	

	bool player_ValidateCheat();
};

