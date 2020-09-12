#include "Game_Board.h"
//int Game_Board::notDeallocatedCounter = 0;
Game_Board::Game_Board(const Game_Board& cpSource) {
	board_Height = cpSource.board_Height;
	board_Width = cpSource.board_Width;
	board_BeadTypes = cpSource.board_BeadTypes;
	board_BeadDisplayMap = cpSource.board_BeadDisplayMap;
	board_BeadColorMap = cpSource.board_BeadColorMap;
	board_EmptyTiles = cpSource.board_EmptyTiles;
	board_IsInitialized = cpSource.board_IsInitialized;
	board_Occupied = cpSource.board_Occupied;
	board_Construct();
	for (int i = 0; i < board_Height; i++) {
		for (int j = 0; j < board_Width; j++) {
			board_Table[i][j] = cpSource.board_Table[i][j];
			board_TableAvailable[i][j] = cpSource.board_TableAvailable[i][j];
		}
	}
}
void Game_Board::board_Construct() {
	board_Table = new int*[board_Height];
	board_TableAvailable = new bool*[board_Height];
	for (int i = 0; i < board_Height; i++) {
		board_Table[i] = new int[board_Width];
		board_TableAvailable[i] = new bool[board_Width];
		for (int j = 0; j < board_Width; j++) {
			board_Table[i][j] = -1;
			board_TableAvailable[i][j] = false;
			board_EmptyTiles.push_back({ i,j });
		}
	}
	board_Occupied = 0;
	board_IsInitialized = true;
}
void Game_Board::board_SetHeight(int heightValue) {
	if (!board_IsInitialized) board_Height = heightValue;
}
void Game_Board::board_SetWidth(int widthValue) {
	if (!board_IsInitialized) board_Width = widthValue;
}
void Game_Board::board_Demolish() {
	if (!board_IsInitialized)return;
	for (int i = 0; i < board_Height; i++) {
		delete[] board_Table[i];
		delete[] board_TableAvailable[i];
		//notDeallocatedCounter -= 2;
	}
	delete[] board_Table;
	delete[] board_TableAvailable;
	//notDeallocatedCounter -= 2;
	board_IsInitialized = false;
}
void Game_Board::board_SetBeadMapping(string* mappingChars, base_ColorID* mappingColors, int typeCounts) {
	for (int i = 0; i < typeCounts; i++) {
		board_BeadDisplayMap[i] = mappingChars[i];
		board_BeadColorMap[i] = mappingColors[i];
	}
	board_BeadTypes = typeCounts;
}
void Game_Board::board_SetElement(int x, int y, int beadTypeId) {
	if (!board_TableAvailable[x][y]) {
		base_VectorRemoveByVal(board_EmptyTiles, { x,y });
		board_Occupied++;
	}
	board_Table[x][y] = beadTypeId;
	board_TableAvailable[x][y] = true;
}
void Game_Board::board_RemoveElement(int x, int y) {
	if (board_TableAvailable[x][y]) {
		board_Occupied--;
		board_EmptyTiles.push_back({ x,y });
	}
	board_Table[x][y] = -1;
	board_TableAvailable[x][y] = false;
}
string Game_Board::board_GetBeadMappingChars(int beadTypeId) {
	return board_BeadDisplayMap[beadTypeId];
}
Game_BaseDefinition::base_ColorID Game_Board::board_GetBeadMappingColors(int beadTypeId) {
	return board_BeadColorMap[beadTypeId];
}
int Game_Board::board_GetHeight() {
	return board_Height;
}
int Game_Board::board_GetWidth() {
	return board_Width;
}
int Game_Board::board_GetElement(int x, int y) {
	return board_Table[x][y];
}
int Game_Board::board_GetOccupied() {
	return board_Occupied;
}
int Game_Board::board_GetEmpty() {
	return board_EmptyTiles.size();
}
int Game_Board::board_GetTypes() {
	return board_BeadTypes;
}
bool Game_Board::board_GetEmptyStat(int x, int y) {
	return !board_TableAvailable[x][y];
}
int Game_Board::board_GetVID(int x, int y) {
	return x * board_Width + y;
}
int Game_Board::board_GetSize() {
	return board_Height * board_Width;
}
Game_BaseDefinition::base_Pair Game_Board::board_GetPID(int vid) {
	int y = vid % board_Width;
	int x = vid / board_Width;
	return { x,y };
}
Game_BaseDefinition::base_Pair Game_Board::board_GetEmptyByIterator(int lb) {
	return board_EmptyTiles[lb];
}
void Game_Board::board_Init(int heightValue, int widthValue, string* mappingChars, base_ColorID* mappingColors, int typeCounts) {
	board_SetHeight(heightValue);
	board_SetWidth(widthValue);
	board_SetBeadMapping(mappingChars, mappingColors, typeCounts);
	board_Construct();
}
void Game_Board::board_Unload() {
	board_Demolish();
}
Game_Board::Game_Board(int heightValue, int widthValue, string* mappingChars, base_ColorID* mappingColors, int typeCounts) {
	board_Init(heightValue, widthValue, mappingChars, mappingColors, typeCounts);
}
Game_Board::~Game_Board() {
	board_Unload();
}

void Game_Board::board_Reset() {
	board_Demolish();
	vector<base_Pair>().swap(board_EmptyTiles);
	board_Construct();
}