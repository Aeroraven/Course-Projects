#pragma once
#include "Game_Common.h"
#include "Game_PointCollection.h"
#include "Game_Board.h"
#include "Game_Localization.h"
#include "Game_Algorithm.h"
class Game_Scene :public Game_Common{
public:
	//游戏主场景
	Game_PointCollection scene_MainTitle; //主界面
	Game_PointCollection scene_Board; //棋盘的Pixel集合
	Game_PointCollection scene_LeftBar; //左栏的Pixel集合
	Game_PointCollection scene_BottomBar; //下栏的Pixel集合

	//辅助场景
	Game_PointCollection scene_ComingSoonBox;
	Game_PointCollection scene_OSNotSupported; //功能未在当前操作系统实现的确认框
	Game_PointCollection scene_RestartConfirm; //重新开始确认框
	Game_PointCollection scene_ExitConfirm; //退出确认框
	Game_PointCollection scene_HelpBox; //帮助
	Game_PointCollection scene_SettingBox; //设置
	Game_PointCollection scene_SettingBox_MoveLimit; //设置移动设置
	Game_PointCollection scene_SettingBox_Lang; //设置语言
	Game_PointCollection scene_SettingBox_Foresee; //设置预见
	Game_PointCollection scene_SettingBox_MoveAnimation; //设置移动动画
	Game_PointCollection scene_SettingBox_InputDevice; //设置输入设备
	Game_PointCollection scene_Author; //作者信息


public:
	void scene_ConstructBoardPixels(const Game_Localization& langObj,const Game_Board& boardObject, Game_PointCollection& pxList, int marginLeft, int marginTop);
	void scene_ConstructLeftBarPixels(const Game_Localization& langObj,Game_PointCollection& pxList);
	void scene_ConstructBottomBarPixels(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructRestartConfirm(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructExitConfirm(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructHelpBox(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructCreditBox(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructSettingBox(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructSettingBox_MoveLimit(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructSettingBox_Lang(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructSettingBox_Foresee(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructSettingBox_InputDevice(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_ConstructSettingBox_MoveAnimation(const Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_Construct_TipUniversal(const Game_Localization& langObj, Game_PointCollection& pxList, string strShow);
	void scene_ConstructMainTitle(const Game_Localization& langObj, Game_PointCollection& pxList);


	void scene_SyncBoardPixels(const Game_Board& boardObject, Game_PointCollection& pxList,vector<base_Pair> bgHighlightList = vector<base_Pair>());
	void scene_SyncForeseeResult(const Game_Localization& langObj,const Game_Board& boardObject,const vector<int>& foreseeResult, Game_PointCollection& pxList);
	void scene_SyncScores(int score,Game_Localization& langObj, Game_PointCollection& pxList);
	void scene_SyncSourceCoord(int x, int y, Game_PointCollection& pxList, string emptyInfo = "");
	void scene_SyncSourcePattern(base_ColorID sourceColor,string sourcePattern, Game_PointCollection& pxList);
	void scene_SyncTipInfo(string tpInfo, Game_PointCollection& pxList, bool forceUpdate = false);

	void scene_ExitConfirm_SetHighlight(int x, Game_PointCollection& pxList);
	void scene_SettingBox_SetHighlight(int x, Game_PointCollection& pxList);
	void scene_LangConfirm_SetHighlight(int x, Game_PointCollection& pxList);
	void scene_YesNoBox_SetHighlight(int x, Game_PointCollection& pxList);
	void scene_MainTitle_SetHighlight(int x, Game_PointCollection& pxList);



	void scene_Exception_CodePageUnsupported(const Game_Localization& langObj, Game_PointCollection& pxList);
};

//！新建的Pixel对象不需要手动delete，其会在其所属集合析构时被delete
