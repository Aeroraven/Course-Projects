#pragma once
#include "Game_Common.h"
#include "Game_PointCollection.h"
#include "Game_Board.h"
#include "Game_Localization.h"
#include "Game_Algorithm.h"
class Game_Scene :public Game_Common{
public:
	//��Ϸ������
	Game_PointCollection scene_MainTitle; //������
	Game_PointCollection scene_Board; //���̵�Pixel����
	Game_PointCollection scene_LeftBar; //������Pixel����
	Game_PointCollection scene_BottomBar; //������Pixel����

	//��������
	Game_PointCollection scene_ComingSoonBox;
	Game_PointCollection scene_OSNotSupported; //����δ�ڵ�ǰ����ϵͳʵ�ֵ�ȷ�Ͽ�
	Game_PointCollection scene_RestartConfirm; //���¿�ʼȷ�Ͽ�
	Game_PointCollection scene_ExitConfirm; //�˳�ȷ�Ͽ�
	Game_PointCollection scene_HelpBox; //����
	Game_PointCollection scene_SettingBox; //����
	Game_PointCollection scene_SettingBox_MoveLimit; //�����ƶ�����
	Game_PointCollection scene_SettingBox_Lang; //��������
	Game_PointCollection scene_SettingBox_Foresee; //����Ԥ��
	Game_PointCollection scene_SettingBox_MoveAnimation; //�����ƶ�����
	Game_PointCollection scene_SettingBox_InputDevice; //���������豸
	Game_PointCollection scene_Author; //������Ϣ


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

//���½���Pixel������Ҫ�ֶ�delete���������������������ʱ��delete
