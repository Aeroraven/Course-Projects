#pragma once
#include "Game_Common.h"
#include "Game_Scene.h"
#include "Game_Display.h"
#include "Game_Input.h"
class Game_Layout_MainTitle :public Game_Common{
private:
	Game_Scene* sceneObj;
	Game_Localization* langObj;
	Game_Input inputInf;
	Game_Display displayEffect;
public:
	void layout_LangBind(const Game_Localization* sourcePtr);
	void layout_SceneBind(const Game_Scene* sourcePtr);
	void layout_SceneInit();
	void layout_Show(int& retVal);
	void layout_Author();
};

class Game_Layout_LanguagePreselect :public Game_Common {
private:
	Game_Scene* sceneObj;
	Game_Localization* langObj;
	Game_Input inputInf;
	Game_Display displayEffect;
public:
	void layout_LangBind(const Game_Localization* sourcePtr);
	void layout_SceneBind(const Game_Scene* sourcePtr);
	void layout_SceneInit();
	void layout_Show(int& retVal);
};

