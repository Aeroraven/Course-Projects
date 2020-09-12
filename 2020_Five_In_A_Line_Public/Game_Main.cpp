#include "Game_Main.h"

void Game_Main::main_SingleGameTest(int& retVal, int areaId, bool usingSave, Game_Save& saveData) {
	
	Game_Display displayMain;
	Game_Localization langMain(areaId);
	Game_Player singlePlayer(0, "Player", false);
	Game_Scene sceneMain;
	Game_Operation sysOp;
#ifdef _WIN32
	string preSetPattern[13] = {
		langMain.lang_GetString(langMain.SYMBOL_PRESET_RECT),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_TRIANGLE),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_CIRCLE),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_DIAMOND),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_FILLED_STAR),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_HOLLOW_STAR),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_CROSS_WITH_DOT),

		langMain.lang_GetString(langMain.SYMBOL_PRESET_TRIANGLE),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_CIRCLE),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_DIAMOND),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_FILLED_STAR),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_HOLLOW_STAR),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_RECT),
	};
#else
	string preSetPattern[7] = {
		langMain.lang_GetString(langMain.SYMBOL_PRESET_SHARP),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_ZERO),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_AT),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_ADD),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_CROSS),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_PERCENT),
		langMain.lang_GetString(langMain.SYMBOL_PRESET_DOLLAR)
	};
#endif
	Game_Board boardMain(base_DefaultBoardHeight, base_DefaultBoardWidth, preSetPattern, (base_ColorID*)base_DefaultBeadColors, base_DefaultBeadTypes);
	sysOp.opBoard_Bind(&boardMain);
	sysOp.opScene_Bind(&sceneMain);
	sysOp.opLang_Bind(&langMain);
	sysOp.opScene_Init();
	sysOp.opDisplay_Bind(&displayMain);
	sysOp.opPlayer_AddPlayer(&singlePlayer);
	if (usingSave == false) {
		sysOp.opBoard_StartUp();
	}
	else {
		sysOp.opFunc_GameLoad(saveData);
	}
	sysOp.opScene_UpdateBoardPixels();
	sysOp.opScene_UpdateForeseeResult();
	sysOp.opScene_UpdateScoresDefault();

	sysOp.opDisplay_Print();
	if (usingSave == false) {
		sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_GAME_STARTED));
	}
	else {
		sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_GAME_LOADED));
	}
	sysOp.opDisplay_Sleep(1300);
	sysOp.opPlayerAct_CheckClear(&singlePlayer, true);
	int a, b, c, d, extCmd, moveRet, emptySkipFlag;
	bool removeStat;
	while (1) {
		removeStat = 0;
		while (1) {
			if (sysOp.opFunc_CheckGotoMainTitleStat()) {
				retVal = 1;
				return;
			}
			if (sysOp.opFunc_CheckLangChange()) {
				int lc = sysOp.opFunc_CheckLangChange();
				retVal = 1000 + lc;
				return;
			}
			if (sysOp.opFunc_GetExitRequest()) {
				retVal = 3;
				return;
			}
			sysOp.opDisplay_Print();
			emptySkipFlag = 0;
			if (sysOp.opBoard_AllEmpty() == true) {
				emptySkipFlag = 1;
				break;
			}
			sysOp.opInput_ReadMovementCoord2(a, b, c, d, extCmd);
			if (extCmd != 0) { //按下了非数字按键
				if (extCmd == 1) { //游戏重启
					sysOp.opSubScene_Restart();
					continue;
				}
				else if (extCmd == 2) { //游戏帮助
					sysOp.opSubScene_Help();
					continue;
				}
				else if (extCmd == 3) { //游戏退出
					sysOp.opSubScene_Exit();
					continue;
				}
				else if (extCmd == 4) { //游戏设置
					sysOp.opSubScene_SettingMain();
					continue;
				}
				else if (extCmd == 5) { //作者信息
					sysOp.opSubScene_Author();
					continue;
				}
				else if (extCmd == 6) { //输入重置
					sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_INPUT_RESET));
					sysOp.opDisplay_Sleep(1000);
					continue;
				}
				else if (extCmd == 7) {
					sysOp.opFunc_Save();
					sysOp.opDisplay_Sleep(1000);
					continue;
				}
				else { //按键非法
					sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_INVALID_INPUT));
					sysOp.opDisplay_Sleep(1000);
					continue;
				}
			}
			moveRet = sysOp.opBoard_Move({ a,b }, { c,d });
			if (moveRet == 0) {
				break;
			}
			else {
				string invalidInfo = langMain.lang_GetString(langMain.TEXT_INFO_INVALID_MOVE_HEADER);
				if ((moveRet >> 0) & 1) { //unconnected
					invalidInfo += " ";
					invalidInfo += langMain.lang_GetString(langMain.TEXT_INFO_INVALID_MOVE_UNCONNECTED);
				}
				if ((moveRet >> 1) & 1) { //source empty
					invalidInfo += " ";
					invalidInfo += langMain.lang_GetString(langMain.TEXT_INFO_INVALID_MOVE_EMPTY);
				}
				if ((moveRet >> 2) & 1) { //destination occupied
					invalidInfo += " ";
					invalidInfo += langMain.lang_GetString(langMain.TEXT_INFO_INVALID_MOVE_OCCUPIED);
				}
				if ((moveRet >> 3) & 1) { //invalid coordinate
					invalidInfo += " ";
					invalidInfo += langMain.lang_GetString(langMain.TEXT_INFO_INVALID_COORD);
				}
				sysOp.opScene_SetTipInfo(invalidInfo);
				sysOp.opDisplay_Sleep(1000);
			}
		}
		sysOp.opScene_UpdateBoardPixels();
		if (emptySkipFlag == 0) {
			sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_MOVE_SUCCESS));
		}
		else {
			sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_NO_AVAILABLE_MOVES));
		}
		
		sysOp.opDisplay_Print();
		sysOp.opDisplay_Sleep(1000);

		if (sysOp.opPlayerAct_CheckClear(&singlePlayer) == false) {
			sysOp.opBoard_RandomPlaces();
			sysOp.opScene_UpdateBoardPixels();
			sysOp.opScene_UpdateForeseeResult();
			sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_NEWBEADS_PLACED));
			sysOp.opDisplay_Print();
			sysOp.opDisplay_Sleep(1000);
			sysOp.opPlayerAct_CheckClear(&singlePlayer,true); //系统移除第二个参数为true
		}
		if (sysOp.opBoard_AllOccupied()) {
			while (sysOp.opBoard_AllOccupied()) {
				sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_COMPLETE_OCCPUIED));
				sysOp.opInput_ReadFunc(extCmd);
				if (extCmd != 0) { //按下了非数字按键
					if (extCmd == 1) { //游戏重启
						sysOp.opSubScene_Restart();
					}
					else if (extCmd == 2) { //游戏帮助
						sysOp.opSubScene_Help();
					}
					else if (extCmd == 3) { //游戏退出
						sysOp.opSubScene_Exit();
					}
					else if (extCmd == 4) { //游戏设置
						sysOp.opSubScene_SettingMain();
					}
					else if (extCmd == 5) { //作者信息
						sysOp.opSubScene_Author();
					}
					if (sysOp.opFunc_CheckGotoMainTitleStat()) {
						retVal = 1;
						return;
					}
					if (sysOp.opFunc_CheckLangChange()) {
						int lc = sysOp.opFunc_CheckLangChange();
						retVal = 1000 + lc;
						return;
					}
				}
			}
		}
		sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_PRESS_ANY_KEY_TO_CONTINUE));
		//sysOp.opInput_Waiting();
	}
	while (1) {
		sysOp.opScene_SetTipInfo(langMain.lang_GetString(langMain.TEXT_INFO_COMPLETE_OCCPUIED));
		sysOp.opDisplay_Sleep(5000);
	}
}

void Game_Main::main_Init() {
	Game_Display displayAssistant;
	displayAssistant.display_hideCursor();

#ifdef _WIN32
	system("mode con cols=120 lines=40");
	system("title Five or More [By Huang Zhiwen] ");
	displayAssistant.display_WinOSInit();
#else
	cout << "\033]0;Five or More [By Huang Zhiwen]\007" << flush;
	displayAssistant.display_LinuxInit();
	system("resize -s 40 120");
	displayAssistant.display_cls();
#endif
	int g = 0, s = vck.length();
	for (int i = 0; i < s; i++) {
		g += vck[i] ^ vck[s - 1 - i];
	}
	seriesID = g << 1;
}
void Game_Main::main_LanguagePreselection() {
	int t = base_CompileOS;
	if (t == 2) {
		Game_Layout_LanguagePreselect layoutMain;
		Game_Localization* langMain = new Game_Localization(2);
		Game_Scene* sceneMain = new Game_Scene;
		layoutMain.layout_LangBind(langMain);
		layoutMain.layout_SceneBind(sceneMain);
		layoutMain.layout_SceneInit();
		int s;
		layoutMain.layout_Show(s);
		langPresel = s - 1000;
		delete langMain;
		delete sceneMain;
	}
	else {
		Game_Display displayEffect;
		Game_Interface cpInf;
		if (cpInf.interface_GetCodepage() == 936) { //936!
			displayEffect.display_WinChcp_GBK();
			langPresel = 3;
		}
		else if(cpInf.interface_GetCodepage()==65001){
			displayEffect.display_WinChcp_UTF8();
			langPresel = 4;
		}
		else {
			Game_PointCollection cpNotSupported;
			Game_Localization* langMain = new Game_Localization(2);
			Game_Scene* sceneMain = new Game_Scene;
			Game_Input cpnsInput;
			sceneMain->scene_Exception_CodePageUnsupported(*langMain, cpNotSupported);
			cpNotSupported.pointset_Print(true);
			cpnsInput.input_pressKeyToContinue();
			displayEffect.display_WinChcp_UTF8();
			langPresel = 4;
		}
		displayEffect.display_cls();
	}
}

void Game_Main::main_MainTitle() {
	int ls, gs, tl = 0;
	int curLangId = langPresel;
	Game_Layout_MainTitle mainTitle;
	Game_Display displayEffects;
	Game_Localization* langMain = new Game_Localization(langPresel);
	Game_Scene* sceneMain = new Game_Scene;
	while (1) {
		gs = 0, ls = 0;
		if (tl == 0) {
			mainTitle.layout_LangBind(langMain);
			mainTitle.layout_SceneBind(sceneMain);
			mainTitle.layout_SceneInit();
			tl = 1;
		}
		mainTitle.layout_Show(ls);

		if (ls == 1||ls==2) {
			//预载存档
			Game_File saveLoader(curLangId);
			Game_Save saveContent(curLangId);
			if (ls == 2) {
				int status = saveLoader.gamefile_Load(saveContent);
				if (status == 2)continue;
			}
			//预载存档结束
			displayEffects.display_cls();

			delete sceneMain;
			delete langMain;
			if (ls == 1) {
				main_SingleGameTest(gs, curLangId, false, saveContent);
			}
			else {
				main_SingleGameTest(gs, curLangId, true, saveContent);
			}

			langMain = new Game_Localization(curLangId);
			sceneMain = new Game_Scene;
			mainTitle.layout_LangBind(langMain);
			mainTitle.layout_SceneBind(sceneMain);
			mainTitle.layout_SceneInit();

			if (gs == 1) {
				continue;
			}
			else if (gs >= 1001 && gs<=1004) {
				delete langMain;
				delete sceneMain;
				langMain = new Game_Localization(gs-1000);
				sceneMain = new Game_Scene;
				mainTitle.layout_LangBind(langMain);
				mainTitle.layout_SceneBind(sceneMain);
				mainTitle.layout_SceneInit();
				curLangId = gs - 1000;
				if (curLangId == 1 || curLangId == 3) {
					displayEffects.display_WinChcp_GBK();
				}
				else {
					displayEffects.display_WinChcp_UTF8();
				}

				continue;
			}
			if (gs == 3) {
				displayEffects.display_cls();
				break;
			}
			
		}
		if (ls == 10) {
			displayEffects.display_cls();
			break;
		}
		
		break;
	}
	delete langMain;
	delete sceneMain;
}
