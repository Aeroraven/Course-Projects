#include "Game_Layout.h"
void Game_Layout_MainTitle::layout_LangBind(const Game_Localization* sourcePtr) {
	langObj = (Game_Localization*)sourcePtr;
}
void Game_Layout_MainTitle::layout_SceneBind(const Game_Scene* sourcePtr) {
	sceneObj = (Game_Scene*)sourcePtr;
}
void Game_Layout_MainTitle::layout_SceneInit() {
	sceneObj->scene_ConstructMainTitle(*langObj, sceneObj->scene_MainTitle);
	sceneObj->scene_ConstructHelpBox(*langObj, sceneObj->scene_HelpBox);
	sceneObj->scene_ConstructCreditBox(*langObj, sceneObj->scene_Author);
}
void Game_Layout_MainTitle::layout_Show(int& retVal) {
	int keyP, selOpt = 1;
	sceneObj->scene_MainTitle_SetHighlight(selOpt, sceneObj->scene_MainTitle);
	sceneObj->scene_MainTitle.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Left) {
			selOpt--; if (selOpt < 0)selOpt += 3;
			sceneObj->scene_MainTitle_SetHighlight(selOpt, sceneObj->scene_MainTitle);
			sceneObj->scene_MainTitle.pointset_Print();
		}
		if (keyP == base_GetchVal_Right) {
			selOpt++; if (selOpt >= 3)selOpt -= 3;
			sceneObj->scene_MainTitle_SetHighlight(selOpt, sceneObj->scene_MainTitle);
			sceneObj->scene_MainTitle.pointset_Print();
		}
		if (keyP == 'S' || keyP == 's' || (keyP==inputInf.input_enterKeyVal() && selOpt==1)) {
			retVal = 1;
			return;
		}
		if (keyP == 'L' || keyP == 'l' || (keyP == inputInf.input_enterKeyVal() && selOpt == 2)) {
			retVal = 2;
			return;
		}
		if (keyP == 'E' || keyP == 'e' || (keyP == inputInf.input_enterKeyVal() && selOpt == 0)) {
			retVal = 10;
			return;
		}
	}
}
void Game_Layout_MainTitle::layout_Author() {
	displayEffect.display_cls();
	int keyP;
	sceneObj->scene_Author.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == 'C' || keyP == 'c' || keyP == inputInf.input_enterKeyVal()) {
			displayEffect.display_cls();
			return;
		}
	}
}


void Game_Layout_LanguagePreselect::layout_LangBind(const Game_Localization* sourcePtr) {
	langObj = (Game_Localization*)sourcePtr;
}
void Game_Layout_LanguagePreselect::layout_SceneBind(const Game_Scene* sourcePtr) {
	sceneObj = (Game_Scene*)sourcePtr;
}
void Game_Layout_LanguagePreselect::layout_SceneInit() {
	sceneObj->scene_ConstructSettingBox_Lang(*langObj, sceneObj->scene_SettingBox_Lang);
}
void Game_Layout_LanguagePreselect::layout_Show(int& retVal) {
	//sceneObj->scene_ConstructSettingBox_Lang(*langObj, sceneObj->scene_SettingBox_Lang);
	sceneObj->scene_SettingBox_Lang.pointset_GetByAlias(2000)->point_SetContent("Choose your default language preference:");
	sceneObj->scene_SettingBox_Lang.pointset_GetByAlias(2001)->point_SetContent("Choose the encoding method via checking your terminal settings.");
	sceneObj->scene_SettingBox_Lang.pointset_GetByAlias(2003)->point_SetContent("");
	sceneObj->scene_SettingBox_Lang.pointset_GetByAlias(2004)->point_SetContent("Use [Arrow Keys] + [Enter] to choose options.");
	sceneObj->scene_SettingBox_Lang.pointset_GetByAlias(2004)->point_SetForeColor(base_ColorID_Red);
	sceneObj->scene_SettingBox_Lang.pointset_GetByAlias(2003)->point_SetForeColor(base_ColorID_Green);
	sceneObj->scene_SettingBox_Lang.pointset_GetByAlias(5)->point_SetContent("");
	int keyP, selOpt = 3;
	displayEffect.display_cls();
	sceneObj->scene_LangConfirm_SetHighlight(selOpt, sceneObj->scene_SettingBox_Lang);
	sceneObj->scene_SettingBox_Lang.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Up || keyP == base_GetchVal_Down) {
			if (keyP == base_GetchVal_Up)selOpt--;
			if (keyP == base_GetchVal_Down)selOpt++;
			if (selOpt <= 0) selOpt += 4;
			if (selOpt > 4) selOpt -= 4;
			sceneObj->scene_LangConfirm_SetHighlight(selOpt, sceneObj->scene_SettingBox_Lang);
			sceneObj->scene_SettingBox_Lang.pointset_Print();
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 4)) {
			retVal = 1004;
			displayEffect.display_WinChcp_UTF8();
			displayEffect.display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 3)) {

			retVal = 1003;
			displayEffect.display_WinChcp_GBK();
			displayEffect.display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 2)) {
			retVal = 1002;
			displayEffect.display_WinChcp_UTF8();
			displayEffect.display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 1)) {
			retVal = 1001;
			displayEffect.display_WinChcp_GBK();
			displayEffect.display_cls();
			return;
		}
	}
}
