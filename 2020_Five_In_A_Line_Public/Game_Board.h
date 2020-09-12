#pragma once
#include "Game_Common.h"
//**********************************
//	Game_Board
//	棋盘信息存储 & 棋盘基础功能
//**********************************
class Game_Board :public Game_Common{
private:
	unordered_map<int, string> board_BeadDisplayMap;	//储存ID到棋子图形的映射
	unordered_map<int, base_ColorID> board_BeadColorMap;	//储存ID到棋子颜色的映射
	vector<base_Pair> board_EmptyTiles;	//空置棋盘格向量
	int board_Width, board_Height;	//棋盘边长
	int board_BeadTypes;	//棋盘支持的棋子种类数
	int** board_Table;	//棋盘主体
	bool** board_TableAvailable;	//储存棋盘每格状态
	bool board_IsInitialized;	//棋盘对象初始化状态
	int board_Occupied;	//棋盘全满状态
public:
	
	~Game_Board(); //析构函数
	Game_Board(int heightValue = base_DefaultBoardHeight, int widthValue = base_DefaultBoardWidth, string* mappingChars = nullptr, base_ColorID* mappingColors = (base_ColorID*)base_DefaultBeadColors, int typeCounts = base_DefaultBeadTypes);
	Game_Board(const Game_Board& cpSource);
	void board_Init(int heightValue = base_DefaultBoardHeight, int widthValue = base_DefaultBoardWidth, string* mappingChars = nullptr , base_ColorID* mappingColors = (base_ColorID*)base_DefaultBeadColors, int typeCounts = base_DefaultBeadTypes);
	void board_Unload();

	void board_Construct();	//建构棋盘
	void board_SetHeight(int heightValue = base_DefaultBoardHeight); //设定高度
	void board_SetWidth(int widthValue = base_DefaultBoardWidth); //设定宽度
	void board_Demolish(); //摧毁棋盘
	void board_SetBeadMapping(string* mappingChars , base_ColorID* mappingColors = (base_ColorID*)base_DefaultBeadColors, int typeCounts = base_DefaultBeadTypes); //设定图案样式
	void board_SetElement(int x, int y, int beadTypeId); //放置棋子
	void board_RemoveElement(int x, int y); //移除棋子

	string board_GetBeadMappingChars(int beadTypeId); //获取ID对应的棋子字符
	base_ColorID board_GetBeadMappingColors(int beadTypeId); //获取ID对应的棋子颜色
	int board_GetHeight(); //获得棋盘高度
	int board_GetWidth(); //获得棋盘宽度
	int board_GetElement(int x, int y); //获得对应格点上的棋子
	int board_GetOccupied(); //获得棋盘占用状态
	int board_GetEmpty(); //获得棋盘空置状态
	int board_GetTypes(); //获得棋盘支持的棋子种类数
	bool board_GetEmptyStat(int x, int y); //获得一个格子的空置状态
	int board_GetSize(); //获得棋盘规格
	base_Pair board_GetEmptyByIterator(int lb); //根据下标获得空置向量内的格点
	int board_GetVID(int x, int y); //将坐标转换为一维编号
	base_Pair board_GetPID(int vid); //将一维编号转换为坐标
	void board_Reset(); //清空棋子放置信息，重新加载棋盘
};

