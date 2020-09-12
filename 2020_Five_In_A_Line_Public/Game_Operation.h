#pragma once
#include "Game_Common.h"
#include "Game_Display.h"
#include "Game_Board.h"
#include "Game_Player.h"
#include "Game_Scene.h"
#include "Game_Input.h"
#include "Game_File.h"
#include "Game_Algorithm.h"
class Game_Operation :public Game_Common{
private:
	Game_Algorithm::HashCode randomGenerator; //随机数生成器
	Game_Board* boardObject; //棋盘对象
	Game_Display* displayObject; //显示效果对象
	Game_Scene* sceneObject; //PixelsCollections 集合
	Game_Localization* langObject; //语言对象
	vector<Game_Player*> playerObjectList; //玩家对象
	Game_Input inputInf; //输入对象

	int rule_MinChainBeads;
	int rule_BasicScores;
	int rule_AddedScores;
	bool rule_MoveLimit;
	int rule_EnableForesee;
	int input_InputDevice;
	bool rule_MoveAnimation;
	int counter_round;
	int counter_curPlayer;
	int counter_randomCnt1;
	int counter_randomCnt2;

	int argv_boardMarginLeft;
	int argv_boardMarginTop;
	int argv_gotoMainTitle;
	int argv_langChanged;
	int argv_ExitStat;
public:
	//构造函数
	Game_Operation(
		const Game_Board* bindBoardObj = nullptr,
		const Game_Display* bindDisplayObj = nullptr,
		int leastChainBeads = base_DefaultBeadChain,
		int basicScore = base_DefaultBasicScore,
		int addedScore = base_DefaultAddedScore
	);

	//游戏规则
	void opRule_SetLeastChainBeads(int leastValue = base_DefaultBeadChain); //设置最少消除需求
	void opRule_SetBasicScore(int setValue = base_DefaultBasicScore);  //设置基础分数
	void opRule_SetAddedScore(int setValue = base_DefaultAddedScore); //设置加分
	void opRule_SetMoveLimit(bool setValue = true); //设置移动限制
	void opRule_SetMoveAnimation(bool setValue = true); //设置移动动画
	void opRule_SetForesee(bool setValue = false); //允许预见
	
	//游戏功能
	void opFunc_Restart();
	void opFunc_Exit();
	void opFunc_GotoMainTitle();
	bool opFunc_CheckGotoMainTitleStat();
	void opFunc_AfterLangChange(int newLangID);
	int opFunc_CheckLangChange();
	void opFunc_AntiCheat(Game_Player* playerObj);
	void opFunc_Save();
	void opFunc_GameLoad(Game_Save& svData);
	bool opFunc_GetExitRequest();

	//基于游戏规则的棋盘处理
	void opBoard_Bind(const Game_Board* boardPtr); //设置棋盘对象
	void opBoard_StartUp(int occupiedTiles = base_DefaultStartBeads); //起步放置
	void opBoard_RandomPlaces(int requestTiles = base_DefaultBeadsRegen); //随机放置
	int opBoard_CheckMark(int& extraChance,int playerRemoval=1); //清除标记
	bool opBoard_AvailableMove(const base_Pair& source, const base_Pair& destination, vector<int>& routeList); //检测移动是否有路径到达
	int opBoard_Move(const base_Pair& source, const base_Pair& destination); //执行移动
	bool opBoard_AllOccupied();
	bool opBoard_AllEmpty();
	void opBoard_GetForeseeResult(vector<int>& resultAcceptor);
	
	//场景处理
	void opScene_Bind(const Game_Scene* scenePtr); //设置场景对象
	void opScene_Init();
	void opScene_UpdateBoardPixels(vector<base_Pair> highlightList=vector<base_Pair>());
	void opScene_UpdateForeseeResult();
	void opScene_UpdateScores(Game_Player* playerObj);
	void opScene_UpdateScoresDefault();
	void opScene_UpdateSourceCell(int x,int y);
	void opScene_SetTipInfo(string tipStr);

	//语言处理
	void  opLang_Bind(const Game_Localization* langPtr);

	//显示处理
	void opDisplay_Bind(const Game_Display* displayPtr); //设置显示处理对象
	void opDisplay_Sleep(int delayms);
	void opDisplay_Print(bool forceRedraw = false);
	
	
	//输入处理
	void opInput_ReadMovementCoord(int &a,int &b,int &c,int &d,int& extFlag);
	int opInput_ReadMovementCoordExt(int& val,int& extFlag);
	void opInput_ReadMovementCoord2(int &a, int &b, int &c, int &d, int& extFlag);
	void opInput_Waiting();
	base_Pair opInput_MousePosConversion(int mouseX, int mouseY);
	void opInput_MouseInput(int &a,int &b,int &extFlag);
	void opInput_SetDevice(int deviceId = 2);
	void opInput_ReadFunc(int& extFlag);
	base_InputInfo opInput_MouseInput2();

	//玩家处理
	void opPlayer_AddPlayer(Game_Player* playerObj);
	bool opPlayerAct_CheckClear(Game_Player* playerObj,bool sysOp=false);

	//辅助场景处理
	void opSubScene_Restart();
	void opSubScene_Help();
	void opSubScene_Author();
	void opSubScene_Exit();
	void opSubScene_SettingMain();
	void opSubScene_Setting_MoveLimit();
	void opSubScene_Setting_InputDevice();
	void opSubScene_Setting_Foresee();
	void opSubScene_Setting_Lang();
	void opSubScene_Setting_MoveAnimation();
	void opSubScene_InfoWindow(Game_PointCollection* callDest);

	//Debug
	void opDebug_BoardPlace(int x, int y, int Type);
	void opDebug_SceneCall(Game_PointCollection* pxList);
	string opDebug_GetBoardElement(int x, int y);

};

