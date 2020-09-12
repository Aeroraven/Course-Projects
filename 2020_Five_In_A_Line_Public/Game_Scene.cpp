#include "Game_Scene.h"
void Game_Scene::scene_ConstructBoardPixels(const Game_Localization& langObj,const Game_Board& boardObject, Game_PointCollection& pxList, int marginLeft, int marginTop) {
	Game_Point* pxPtr;
	Game_Board boardDup = boardObject;
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	string pxStr;
	//int cL = 0, cR = 0;
	int tWidth = boardDup.board_GetWidth() + 1;
	int tHeight = boardDup.board_GetHeight() + 1;
	//构建总体边框
	for (int i = 0; i < tHeight; i++) {
		for (int j = 0; j < tWidth; j++) {
			if (i == 0 && j == 0) {//格子位于左上角
				pxPtr = new Game_Point(marginLeft + 0, marginTop + 0, langDup.lang_GetString(langDup.SYMBOL_TABLE_LTCORNER), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + 2, marginTop + 0, langDup.lang_GetString(langDup.SYMBOL_TABLE_HORZLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + 0, marginTop + 1, langDup.lang_GetString(langDup.SYMBOL_TABLE_VERTLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
			}
			else if (i == 0) { //格子位于最上层
				pxPtr = new Game_Point(marginLeft + j * 4, marginTop + 0, langDup.lang_GetString(langDup.SYMBOL_TABLE_TBRANCH), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + j * 4 + 2, marginTop + 0, langDup.lang_GetString(langDup.SYMBOL_TABLE_HORZLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + j * 4, marginTop + 1, langDup.lang_GetString(langDup.SYMBOL_TABLE_VERTLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
			}
			else if (j == 0) { //格子位于最左层
				pxPtr = new Game_Point(marginLeft + j * 4, marginTop + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_LBRANCH), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + j * 4 + 2, marginTop + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_HORZLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + j * 4, marginTop + 1 + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_VERTLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
			}
			else { //其他格子
				pxPtr = new Game_Point(marginLeft + j * 4, marginTop + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_CROSS), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + j * 4 + 2, marginTop + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_HORZLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
				pxPtr = new Game_Point(marginLeft + j * 4, marginTop + 1 + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_VERTLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
				pxList.pointset_Add(pxPtr);
			}
		}
		if (i == 0) {//第一行末尾
			pxPtr = new Game_Point(marginLeft + tWidth * 4, marginTop + 0, langDup.lang_GetString(langDup.SYMBOL_TABLE_RTCORNER), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
			pxPtr = new Game_Point(marginLeft + tWidth * 4, marginTop + 1, langDup.lang_GetString(langDup.SYMBOL_TABLE_VERTLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
		}
		else {//其他行末尾
			pxPtr = new Game_Point(marginLeft + tWidth * 4, marginTop + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_RBRANCH), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
			pxPtr = new Game_Point(marginLeft + tWidth * 4, marginTop + 1 + i * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_VERTLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
		}
	}
	for (int i = 0; i < tWidth; i++) { //底侧边框
		if (i == 0) {
			pxPtr = new Game_Point(marginLeft + i * 4, marginTop + tHeight * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_LBCORNER), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
			pxPtr = new Game_Point(marginLeft + i * 4 + 2, marginTop + tHeight * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_HORZLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
		}
		else {
			pxPtr = new Game_Point(marginLeft + i * 4, marginTop + tHeight * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_BBRANCH), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
			pxPtr = new Game_Point(marginLeft + i * 4 + 2, marginTop + tHeight * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_HORZLINE), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr);
		}
	}
	pxPtr = new Game_Point(marginLeft + tWidth * 4, marginTop + tHeight * 2, langDup.lang_GetString(langDup.SYMBOL_TABLE_RBCORNER), base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
	pxList.pointset_Add(pxPtr);

	Game_LocalizationGadget::FwNumConversion fwConv;

	//坐标轴构建(horizontal)
	string coordVal;
	for (int i = 1; i < tWidth; i++) {
		if (i <= 9)coordVal = fwConv.Num2Fw(i,1,&langDup);
		else coordVal = base_Any2String(i);
		pxPtr = new Game_Point(marginLeft + i * 4 + 2, marginTop + 1, coordVal, base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
		pxList.pointset_Add(pxPtr, -1000 - i);
	}

	//坐标轴构建(vertical)
	for (int i = 1; i < tHeight; i++) {
		if (i <= 9)coordVal = coordVal = fwConv.Num2Fw(i, 1, &langDup);
		else coordVal = base_Any2String(i);
		pxPtr = new Game_Point(marginLeft + 2, marginTop + 1 + 2 * i, coordVal, base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
		pxList.pointset_Add(pxPtr, -2000 - i);
	}

	//棋盘空格对象构建
	for (int i = 0; i < tHeight - 1; i++) {
		for (int j = 0; j < tWidth - 1; j++) {
			pxPtr = new Game_Point(marginLeft + 6 + j * 4, marginTop + 3 + i * 2, "",  base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
			pxList.pointset_Add(pxPtr, boardDup.board_GetVID(i, j));
		}
	}
}

void Game_Scene::scene_SyncBoardPixels(const Game_Board& boardObject, Game_PointCollection& pxList, vector<base_Pair> bgHighlightList) {
	Game_Board boardDup = boardObject;
	Game_Point* pxPtr;
	base_Pair bp;
	base_ColorID ptFore,ptBack;
	string ptSymbol;
	int pxCnt = boardDup.board_GetWidth()*boardDup.board_GetHeight() - 1;
	for (int i = 0; i <= pxCnt; i++) {
		bp = boardDup.board_GetPID(i);
		pxPtr = pxList.pointset_GetByAlias(i);
		if (boardDup.board_GetEmptyStat(bp.x, bp.y)) {
			ptSymbol = "  ";
			ptFore = base_ColorID_Default;
			ptBack = base_ColorID_Default;
		}
		else {
			ptSymbol = boardDup.board_GetBeadMappingChars(boardDup.board_GetElement(bp.x, bp.y));
			ptFore = boardDup.board_GetBeadMappingColors(boardDup.board_GetElement(bp.x, bp.y));
			ptBack = base_ColorID_Default;
		}
		pxPtr->point_SetForeColor(ptFore);
		pxPtr->point_SetContent(ptSymbol);
		pxPtr->point_SetBackColor(ptBack);
	}
	int vecsz = bgHighlightList.size();
	for (int i = 0; i < vecsz; i++) {
		bp = bgHighlightList[i];
		pxPtr = pxList.pointset_GetByAlias(boardDup.board_GetVID(bp.x,bp.y));
		ptBack = base_ColorID_Gray;
		pxPtr->point_SetBackColor(ptBack);
	}
}

void Game_Scene::scene_ConstructLeftBarPixels(const Game_Localization& langObj,Game_PointCollection& pxList) {
	//绘制左栏右侧边框
	Game_Point* pxPtr;
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_LocalizationGadget::FwNumConversion fwConv;
	Game_Algorithm::STLExtensions strlength;
	string tmp;
	for (int i = 0; i < 40; i++) {
		pxPtr = new Game_Point(40, i, langDup.lang_GetString(langDup.SYMBOL_SQUARE_1));
		pxList.pointset_Add(pxPtr);
	}
	//绘制得分label
	tmp = langDup.lang_GetString(langDup.TEXT_LABEL_SCORES);
	pxPtr = new Game_Point(20 - strlength.stlex_Strlen(tmp, 1,2, langDup.lang_GetDefaultCode()) / 2, 13,tmp, base_ColorID_Yellow);
	pxList.pointset_Add(pxPtr);
	tmp = fwConv.Num2Fw(0, 8, &langDup);
	pxPtr = new Game_Point(12, 15, tmp);
	pxList.pointset_Add(pxPtr,1);

	//绘制移动预见label
	tmp = langDup.lang_GetString(langDup.TEXT_LABEL_FORESEE);
	pxPtr = new Game_Point(20 - strlength.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode()) / 2, 19, tmp,base_ColorID_Yellow);
	pxList.pointset_Add(pxPtr);
	for (int i = 0; i < 3; i++) {
		tmp = langDup.lang_GetString(langDup.SYMBOL_FWEXT_QUESTIONMARK);
		pxPtr = new Game_Point(13 + i * 6, 21, tmp);
		pxList.pointset_Add(pxPtr, 1000+i);
	}


	//绘制选项label
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_RESTART);
	pxPtr = new Game_Point(8, 27, tmp,base_ColorID_Red);
	pxList.pointset_Add(pxPtr,3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_EXIT);
	pxPtr = new Game_Point(8, 29, tmp,base_ColorID_Yellow);
	pxList.pointset_Add(pxPtr,4);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_SETTING);
	pxPtr = new Game_Point(8, 31, tmp, base_ColorID_Red);
	pxList.pointset_Add(pxPtr,5);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_CREDIT);
	pxPtr = new Game_Point(8, 33, tmp, base_ColorID_Yellow);
	pxList.pointset_Add(pxPtr, 5);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_HELP);
	pxPtr = new Game_Point(8, 35, tmp, base_ColorID_Red);
	pxList.pointset_Add(pxPtr, 5);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_SAVE);
	pxPtr = new Game_Point(8, 37, tmp, base_ColorID_Yellow);
	pxList.pointset_Add(pxPtr, 6);

	//绘制分栏
	for (int i = 0; i < 40; i++) {
		pxPtr = new Game_Point(i, 11, "-");
		pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(i, 17, "-");
		pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(i, 23, "-");
		pxList.pointset_Add(pxPtr);
	}

	//绘制Logo
	int soffset = 9,toffset=3;
	string firstRow[4]={
        "  ___ _            ___      ",
        " | __(_)_ _____   / _ \\ _ _ ",
        " | _|| \\ V / -_) | (_) | \'_|",
        " |_| |_|\\_/\\___|  \\___/|_|  "
	};
	string SecondRow[4]={
        "  __  __             ",
        " |  \\/  |___ _ _ ___ ",
        " | |\\/| / _ \\ \'_/ -_)",
        " |_|  |_\\___/_| \\___|"
	};
	for(int i=0;i<4;i++){
        pxPtr = new Game_Point(1 + toffset, 2+i, firstRow[i], base_ColorID_Blue);pxList.pointset_Add(pxPtr);
	}
	for(int i=0;i<4;i++){
        pxPtr = new Game_Point(1 + soffset, 6+i, SecondRow[i], base_ColorID_Red);pxList.pointset_Add(pxPtr);
	}
}

void Game_Scene::scene_SyncScores(int score,  Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Point* pxPtr;
	Game_LocalizationGadget::FwNumConversion fwConv;
	string updStr;
	pxPtr = pxList.pointset_GetByAlias(1);
	updStr = fwConv.Num2Fw(score, 8,&langObj);
	pxPtr->point_SetContent(updStr);
}

void Game_Scene::scene_SyncSourceCoord(int x,int y, Game_PointCollection& pxList,string emptyInfo) {
	Game_Point* pxPtr;
	ostringstream oss;
	if (x == 0 || y == 0) {
		oss << emptyInfo;
	}
	else {
		oss << "(" << x << "," << y << ")";
	}
	pxPtr = pxList.pointset_GetByAlias(2003);
	pxPtr->point_SetContent(oss.str());
}
void Game_Scene::scene_SyncSourcePattern(base_ColorID sourceColor, string sourcePattern, Game_PointCollection& pxList){
	Game_Point* pxPtr;
	ostringstream oss;
	pxPtr = pxList.pointset_GetByAlias(2004);
	pxPtr->point_SetContent(sourcePattern);
	pxPtr->point_SetForeColor(sourceColor);
}
void Game_Scene::scene_ConstructBottomBarPixels(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	//绘制横条
	Game_Point* pxPtr;
	for (int i = 0; i < 39; i++) {
#ifdef _WIN32
		pxPtr = new Game_Point(42 + i * 2, 30, langDup.lang_GetString(langDup.SYMBOL_SQUARE_2));
#else
		pxPtr = new Game_Point(42 + i * 2, 30, "--");
#endif
		pxList.pointset_Add(pxPtr);
	}

	//绘制提示文字区域
	pxPtr = new Game_Point(48, 35, "Hello World!!!");
	pxList.pointset_Add(pxPtr,2000);

	pxPtr = new Game_Point(48, 33, langDup.lang_GetString(langDup.TEXT_LABEL_RESET_INPUT),base_ColorID_Yellow);
	pxList.pointset_Add(pxPtr, 2001);

	pxPtr = new Game_Point(90, 33, langDup.lang_GetString(langDup.TEXT_LABEL_SOURCE_CELL), base_ColorID_Magenta);
	pxList.pointset_Add(pxPtr, 2002);

	pxPtr = new Game_Point(105, 33, "(-,-)", base_ColorID_Magenta);
	pxList.pointset_Add(pxPtr, 2003);

	pxPtr = new Game_Point(103, 33, "?", base_ColorID_White, base_ColorID_Default, langDup.lang_GetDefaultCode());
	pxList.pointset_Add(pxPtr, 2004);
}

void Game_Scene::scene_SyncTipInfo(string tpInfo,Game_PointCollection& pxList, bool forceUpdate) {
	Game_Point* pxPtr;
	pxPtr = pxList.pointset_GetByAlias(2000);
	pxPtr->point_SetContent(tpInfo);
	if (forceUpdate)pxList.pointset_Print();
}

void Game_Scene::scene_ConstructRestartConfirm(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_RESTART), tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;
	//绘制顶栏
	pxPtr = new Game_Point(20, 13, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 13, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(26 + tmpSize, 13, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 22, tmp); pxList.pointset_Add(pxPtr);

	//绘制侧栏
	for (int i = 14; i < 22; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp= langDup.lang_GetString(langDup.TEXT_INFO_RESTARTING_CONFIRM);
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr,2);
	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_YES);
	pxPtr = new Game_Point(45, 19, tmp, base_ColorID_Black,base_ColorID_White);
	pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_NO);
	pxPtr = new Game_Point(65, 19, tmp);
	pxList.pointset_Add(pxPtr, 4);
}

void Game_Scene::scene_YesNoBox_SetHighlight(int x, Game_PointCollection& pxList) {
	Game_Point* pxPtrY;
	Game_Point* pxPtrN;
	pxPtrY = pxList.pointset_GetByAlias(3);
	pxPtrN = pxList.pointset_GetByAlias(4);
	if (x == 0) {
		pxPtrY->point_SetForeColor(base_ColorID_Black);
		pxPtrY->point_SetBackColor(base_ColorID_White);
		pxPtrN->point_SetForeColor(base_ColorID_White);
		pxPtrN->point_SetBackColor(base_ColorID_Default);
	}
	else {
		pxPtrN->point_SetForeColor(base_ColorID_Black);
		pxPtrN->point_SetBackColor(base_ColorID_White);
		pxPtrY->point_SetForeColor(base_ColorID_White);
		pxPtrY->point_SetBackColor(base_ColorID_Default);
	}
}

void Game_Scene::scene_ConstructHelpBox(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_HELP);
	//绘制背景v2
	string tmp2;
	tmp2 = "";
	

	pxPtr = new Game_Point(20, 9, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 9, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = tmpSize + 26; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(25 + tmpSize +1, 9, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 26, tmp); pxList.pointset_Add(pxPtr);

	//绘制侧栏
	for (int i = 10; i < 26; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_1);
	pxPtr = new Game_Point(30, 12, tmp); pxList.pointset_Add(pxPtr, 1);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_2);
	pxPtr = new Game_Point(30, 13, tmp); pxList.pointset_Add(pxPtr, 2);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_3);
	pxPtr = new Game_Point(30, 14, tmp); pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_4);
	pxPtr = new Game_Point(30, 15, tmp); pxList.pointset_Add(pxPtr, 4);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_5);
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr, 5);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_6);
	pxPtr = new Game_Point(30, 17, tmp); pxList.pointset_Add(pxPtr, 6);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_7);
	pxPtr = new Game_Point(30, 18, tmp); pxList.pointset_Add(pxPtr, 7);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_8);
	pxPtr = new Game_Point(30, 19, tmp); pxList.pointset_Add(pxPtr, 8);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_9);
	pxPtr = new Game_Point(30, 20, tmp); pxList.pointset_Add(pxPtr, 8);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_10);
	pxPtr = new Game_Point(30, 21, tmp); pxList.pointset_Add(pxPtr, 8);
	tmp = langDup.lang_GetString(langDup.TEXT_HELP_11);
	pxPtr = new Game_Point(30, 22, tmp); pxList.pointset_Add(pxPtr, 8);

	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_CLOSE);
	pxPtr = new Game_Point(50, 24, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 100);
}
void Game_Scene::scene_ConstructCreditBox(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_CREDIT);
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;
	pxPtr = new Game_Point(20, 9, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 9, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());

	for (int i = 25 + tmpSize + 1; i < 100; i++) {
		pxPtr = new Game_Point(i, 9, "="); pxList.pointset_Add(pxPtr);
	}
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 26, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 10; i < 26; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	tmp = langDup.lang_GetString(langDup.TEXT_LABEL_AUTHOR_NAME) + base_GameAuthor.authorName;
	pxPtr = new Game_Point(30, 15, tmp); pxList.pointset_Add(pxPtr, 1);
	tmp = langDup.lang_GetString(langDup.TEXT_LABEL_AUTHOR_STUID) + base_GameAuthor.authorStudentIdentity;
	pxPtr = new Game_Point(30, 18, tmp); pxList.pointset_Add(pxPtr, 2);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_CLOSE);
	pxPtr = new Game_Point(50, 24, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 100);
}


void Game_Scene::scene_ConstructExitConfirm(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_EXIT),tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;

	//绘制顶栏
	pxPtr = new Game_Point(20, 13, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 13, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(26 + tmpSize, 13, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 22, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 14; i < 22; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_EXIT_CONFIRM);
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr, 2);

	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_TITLESCENE);
	pxPtr = new Game_Point(30, 19, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_EXIT2);
	pxPtr = new Game_Point(54, 19, tmp);
	pxList.pointset_Add(pxPtr, 4);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_CANCEL);
	pxPtr = new Game_Point(75, 19, tmp);
	pxList.pointset_Add(pxPtr, 5);
}

void Game_Scene::scene_ExitConfirm_SetHighlight(int x, Game_PointCollection& pxList) {
	Game_Point* pxPtrT;
	Game_Point* pxPtrE;
	Game_Point* pxPtrC;
	pxPtrT = pxList.pointset_GetByAlias(3);
	pxPtrE = pxList.pointset_GetByAlias(4);
	pxPtrC = pxList.pointset_GetByAlias(5);
	if (x == 0) {
		pxPtrT->point_SetForeColor(base_ColorID_Black);
		pxPtrT->point_SetBackColor(base_ColorID_White);
		pxPtrE->point_SetForeColor(base_ColorID_White);
		pxPtrE->point_SetBackColor(base_ColorID_Default);
		pxPtrC->point_SetForeColor(base_ColorID_White);
		pxPtrC->point_SetBackColor(base_ColorID_Default);
	}
	else if(x == 1) {
		pxPtrE->point_SetForeColor(base_ColorID_Black);
		pxPtrE->point_SetBackColor(base_ColorID_White);
		pxPtrT->point_SetForeColor(base_ColorID_White);
		pxPtrT->point_SetBackColor(base_ColorID_Default);
		pxPtrC->point_SetForeColor(base_ColorID_White);
		pxPtrC->point_SetBackColor(base_ColorID_Default);
	}
	else if (x == 2) {
		pxPtrC->point_SetForeColor(base_ColorID_Black);
		pxPtrC->point_SetBackColor(base_ColorID_White);
		pxPtrT->point_SetForeColor(base_ColorID_White);
		pxPtrT->point_SetBackColor(base_ColorID_Default);
		pxPtrE->point_SetForeColor(base_ColorID_White);
		pxPtrE->point_SetBackColor(base_ColorID_Default);
	}
}



void Game_Scene::scene_ConstructSettingBox(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_SETTINGS),tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;

	pxPtr = new Game_Point(20, 9, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 9, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(26 + tmpSize, 9, tmp2); pxList.pointset_Add(pxPtr);

	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 26, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 10; i < 26; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_OPERATION_DEVICE);
	pxPtr = new Game_Point(48, 12, tmp); pxList.pointset_Add(pxPtr, 0);

	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_LANGUAGE);
	pxPtr = new Game_Point(48, 14, tmp); pxList.pointset_Add(pxPtr, 1);

	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_GAMERULE_FORESEE);
	pxPtr = new Game_Point(48, 16, tmp); pxList.pointset_Add(pxPtr, 2);

	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_GAMERULE_MOVE_LIMIT);
	pxPtr = new Game_Point(48, 18, tmp); pxList.pointset_Add(pxPtr, 3);

	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_GAMERULE_SHOWROUTE);
	pxPtr = new Game_Point(48, 20, tmp); pxList.pointset_Add(pxPtr, 4);

	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_CLOSE);
	pxPtr = new Game_Point(48, 24, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 5);
}

void Game_Scene::scene_SettingBox_SetHighlight(int x, Game_PointCollection& pxList) {
	Game_Point* pxPtr[6];
	for (int i = 0; i < 6; i++) {
		pxPtr[i] = pxList.pointset_GetByAlias(i);
	}
	for (int i= 0; i < 6; i++) {
		if (i == x) {
			pxPtr[i]->point_SetForeColor(base_ColorID_Black);
			pxPtr[i]->point_SetBackColor(base_ColorID_White);
		}
		else {
			pxPtr[i]->point_SetBackColor(base_ColorID_Default);
			pxPtr[i]->point_SetForeColor(base_ColorID_White);
		}
	}
}

void Game_Scene::scene_LangConfirm_SetHighlight(int x, Game_PointCollection& pxList) {
	Game_Point* pxPtr[6];
	for (int i = 1; i <= 5; i++) {
		pxPtr[i] = pxList.pointset_GetByAlias(i);
	}
	for (int i = 1; i <=5; i++) {
		if (i == x) {
			pxPtr[i]->point_SetForeColor(base_ColorID_Black);
			pxPtr[i]->point_SetBackColor(base_ColorID_White);
		}
		else {
			pxPtr[i]->point_SetBackColor(base_ColorID_Default);
			pxPtr[i]->point_SetForeColor(base_ColorID_White);
		}
	}
}


void Game_Scene::scene_ConstructSettingBox_MoveLimit(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_MOVELIMIT);
	string tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;

	//绘制顶栏
	pxPtr = new Game_Point(20, 13, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 13, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(26 + tmpSize, 13, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 22, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 14; i < 22; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_MOVELIMIT_CONFIRM);
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr, 2);
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_MOVELIMIT_CONFIRM_2);
	pxPtr = new Game_Point(30, 17, tmp); pxList.pointset_Add(pxPtr, 2);
	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_ON);
	pxPtr = new Game_Point(45, 19, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_OFF);
	pxPtr = new Game_Point(65, 19, tmp);
	pxList.pointset_Add(pxPtr, 4);
}

void Game_Scene::scene_ConstructSettingBox_Foresee(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_FORESEE);
	string tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;

	//绘制顶栏
	pxPtr = new Game_Point(20, 13, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 13, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(26 + tmpSize, 13, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 22, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 14; i < 22; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_FORESEE_CONFIRM);
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr, 2);
	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_ON);
	pxPtr = new Game_Point(45, 19, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_OFF);
	pxPtr = new Game_Point(65, 19, tmp);
	pxList.pointset_Add(pxPtr, 4);
}



void Game_Scene::scene_ConstructSettingBox_InputDevice(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_SETTINGS_INPUTDEVICE);
	string tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;

	//绘制顶栏
	pxPtr = new Game_Point(20, 13, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 13, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(26 + tmpSize, 13, tmp2); pxList.pointset_Add(pxPtr);

	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) {
		tmp += "=";
	}
	pxPtr = new Game_Point(20, 22, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 14; i < 22; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_INPUTDEVICE_SWITCH_CONFIRM);
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr, 2);
	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_OPERATION_DEVICE_KEYBOARD);
	pxPtr = new Game_Point(35, 19, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_OPERATION_DEVICE_MOUSE);
	pxPtr = new Game_Point(65, 19, tmp);
	pxList.pointset_Add(pxPtr, 4);
}

void Game_Scene::scene_ConstructSettingBox_MoveAnimation(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_SHOWROUTE);
	string tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;

	//绘制顶栏
	pxPtr = new Game_Point(20, 13, "==== "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 13, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());
	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(26 + tmpSize, 13, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 22, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 14; i < 22; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_SHOWROUTE_CONFIRM);
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr, 2);
	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_YES);
	pxPtr = new Game_Point(35, 19, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_NO);
	pxPtr = new Game_Point(65, 19, tmp);
	pxList.pointset_Add(pxPtr, 4);
}

void Game_Scene::scene_ConstructSettingBox_Lang(const Game_Localization& langObj, Game_PointCollection& pxList) {
	//OutputDebugStringA("【CONSTRUCT CALL】\n");
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_SETTINGS_LANG);
	string tmp2;
	Game_Algorithm::STLExtensions stlex;
	int tmpSize;

	//绘制顶栏
	pxPtr = new Game_Point(20, 9, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(21, 9, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(22, 9, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(23, 9, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(24, 9, " "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 9, tmp); pxList.pointset_Add(pxPtr, 1000); //绘制标题
	tmp2 = "";
	tmpSize = stlex.stlex_Strlen(tmp, 1, 2, langDup.lang_GetDefaultCode());

	for (int i = 25 + tmpSize + 1; i < 100; i++) tmp2 += "=";

	pxPtr = new Game_Point(26 + tmpSize, 9, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) tmp += "=";
	pxPtr = new Game_Point(20, 28, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 10; i < 28; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_LANG_SWITCH_A);
	pxPtr = new Game_Point(30, 12, tmp); pxList.pointset_Add(pxPtr, 2000);
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_LANG_SWITCH_B);
	pxPtr = new Game_Point(30, 13, tmp); pxList.pointset_Add(pxPtr, 2001);
	tmp = "";
	pxPtr = new Game_Point(30, 14, tmp); pxList.pointset_Add(pxPtr, 2003);
	tmp = "";
	pxPtr = new Game_Point(30, 15, tmp); pxList.pointset_Add(pxPtr, 2004);
	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_LANGUAGE_ENUS_GBK);
	pxPtr = new Game_Point(45, 17, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 1);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_LANGUAGE_ENUS_UTF8);
	pxPtr = new Game_Point(45, 19, tmp);
	pxList.pointset_Add(pxPtr, 2);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_LANGUAGE_ZHCN_GBK);
	pxPtr = new Game_Point(45, 21, tmp);
	pxList.pointset_Add(pxPtr, 3);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_LANGUAGE_ZHCN_UTF8);
	pxPtr = new Game_Point(45, 23, tmp);
	pxList.pointset_Add(pxPtr, 4);
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_CANCEL);
	pxPtr = new Game_Point(45, 25, tmp);
	pxList.pointset_Add(pxPtr, 5);
}



void Game_Scene::scene_Construct_TipUniversal(const Game_Localization& langObj, Game_PointCollection& pxList,string strShow) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	string tmp = langDup.lang_GetString(langDup.TEXT_LABEL_ALERTTITLE_COMMON);
	string tmp2;
	

	//绘制顶栏
	pxPtr = new Game_Point(20, 13, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(21, 13, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(22, 13, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(23, 13, "="); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(24, 13, " "); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(25, 13, tmp); pxList.pointset_Add(pxPtr, 1); //绘制标题
	tmp2 = "";
	for (int i = 25 + tmp.size() + 1; i < 100; i++) tmp2 += "=";
	pxPtr = new Game_Point(25 + tmp.size(), 13, tmp2); pxList.pointset_Add(pxPtr);
	//绘制底栏v2
	tmp = "";
	for (int i = 20; i < 100; i++) {
		tmp += "=";
	}
	pxPtr = new Game_Point(20, 22, tmp); pxList.pointset_Add(pxPtr);
	//绘制侧栏
	for (int i = 14; i < 22; i++) {
		pxPtr = new Game_Point(20, i, "||"); pxList.pointset_Add(pxPtr);
		pxPtr = new Game_Point(98, i, "||"); pxList.pointset_Add(pxPtr);
	}
	//绘制中部内容
	tmp = strShow;
	pxPtr = new Game_Point(30, 16, tmp); pxList.pointset_Add(pxPtr, 2);
	//绘制选项
	tmp = langDup.lang_GetString(langDup.TEXT_OPTION_YES);
	pxPtr = new Game_Point(50, 19, tmp, base_ColorID_Black, base_ColorID_White);
	pxList.pointset_Add(pxPtr, 3);
}
void Game_Scene::scene_SyncForeseeResult(const Game_Localization& langObj,const Game_Board& boardObject, const vector<int>& foreseeResult, Game_PointCollection& pxList) {
	Game_Point* pxPtr;
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	vector<int> resDup = foreseeResult;
	Game_Board boardDup = boardObject;
	int vecSz = resDup.size();
	int i = 0;
	for (i = 0; i < vecSz; i++) {
		pxPtr = pxList.pointset_GetByAlias(1000 + i);
		if (resDup[i] != -1) {
			pxPtr->point_SetContent(boardDup.board_GetBeadMappingChars(resDup[i]));
			pxPtr->point_SetForeColor(boardDup.board_GetBeadMappingColors(resDup[i]));
		}
		else {
			pxPtr->point_SetContent(langDup.lang_GetString(langDup.SYMBOL_FWEXT_QUESTIONMARK));
			pxPtr->point_SetForeColor(base_ColorID_White);
		}
	}
	if (i < 7) {
		for (; i < 3; i++) {
			pxPtr = pxList.pointset_GetByAlias(1000 + i);
			pxPtr->point_SetContent("-");
			pxPtr->point_SetForeColor(base_ColorID_White);
		}
	}
}

void Game_Scene::scene_ConstructMainTitle(const Game_Localization& langObj, Game_PointCollection& pxList){
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Algorithm::STLExtensions stlex;
    string cnCharImg[10] = {
		"  # # # # # # # # # #       # # # # # # # #         # #     # #           # # # # # #   #       ",
		"          #                           # #           # # # # # # # # #         #   # # # # # # # ",
		"        # #                       # # #               #   # # #               #   # #   #       ",
		"    # # # # # # # #               # # #           # # # # # # # # # #         #   # # # # # # # ",
		"        # #     # #       # # # # # # # # # # #       #       #           # # # # #   # # #     ",
		"        # #       #                   #               # # # # # # # # #       #       # # #     ",
		"        #         #                   # #             #       #               #     # # # # #   ",
		"        #         #                   # #           # # #     #               # # # #   # # # # ",
		"  # # # # # # # # # # #       # # # # #           # # # # # # # # # #     # # # # #     #   # # ",
		"                                                  # #                                   #       ",
	};
	string enCharImg[5] = {
		" _____ _              ___         __  __                ",
		"|  ___(_)_   _____   / _ \\ _ __  |  \\/  | ___  _ __ ___ ",
		"| |_  | \\ \\ / / _ \\ | | | | \'__| | |\\/| |/ _ \\| \'__/ _ \\",
		"|  _| | |\\ V /  __/ | |_| | |    | |  | | (_) | | |  __/",
		"|_|   |_| \\_/ \\___|  \\___/|_|    |_|  |_|\\___/|_|  \\___|"
	};
	Game_Point* pxPtr;
	//字符画绘制
	for (int i = 0; i < 10; i++) {
		pxPtr = new Game_Point(10, i + 5, cnCharImg[i],base_ColorID_Red);
		pxList.pointset_Add(pxPtr);
	}
	for (int i = 0; i < 5; i++) {
		pxPtr = new Game_Point(30, i + 16, enCharImg[i],base_ColorID_Yellow);
		pxList.pointset_Add(pxPtr);
	}

	//菜单绘制
	string tmp,tmp2;
	tmp = " | ";
	tmp += langDup.lang_GetString(langDup.TEXT_OPTION_MAINTITLE_EXIT);
	tmp += " | ";
	pxPtr = new Game_Point(10, 30, tmp, base_ColorID_White);pxList.pointset_Add(pxPtr,1);
	tmp2 = " ";
	tmp2 += langDup.lang_GetString(langDup.TEXT_BORDERLINE_1);
	tmp2 += " ";
	pxPtr = new Game_Point(10, 29, tmp2, base_ColorID_White);pxList.pointset_Add(pxPtr,2);
	pxPtr = new Game_Point(10, 31, tmp2, base_ColorID_White); pxList.pointset_Add(pxPtr,3);

	tmp = " | ";
	tmp += langDup.lang_GetString(langDup.TEXT_OPTION_MAINTITLE_STARTGAME);
	tmp += " | ";
	pxPtr = new Game_Point(48, 30, tmp, base_ColorID_White);pxList.pointset_Add(pxPtr,4);
	tmp2 = " ";
	tmp2 += langDup.lang_GetString(langDup.TEXT_BORDERLINE_2);
	tmp2 += " ";
	pxPtr = new Game_Point(48, 29, tmp2, base_ColorID_White); pxList.pointset_Add(pxPtr,5);
	pxPtr = new Game_Point(48, 31, tmp2, base_ColorID_White); pxList.pointset_Add(pxPtr,6);


	tmp = " | ";
	tmp += langDup.lang_GetString(langDup.TEXT_OPTION_MAINTITLE_LOAD);
	tmp += " | ";
	pxPtr = new Game_Point(86, 30, tmp, base_ColorID_White);pxList.pointset_Add(pxPtr,7);
	tmp2 = " ";
	tmp2 += langDup.lang_GetString(langDup.TEXT_BORDERLINE_3);
	tmp2 += " ";
	pxPtr = new Game_Point(86, 29, tmp2, base_ColorID_White); pxList.pointset_Add(pxPtr,8);
	pxPtr = new Game_Point(86, 31, tmp2, base_ColorID_White); pxList.pointset_Add(pxPtr,9);

	tmp = langDup.lang_GetString(langDup.TEXT_INFO_MAINTITLE_OPTION_SWITCH);
	pxPtr = new Game_Point(60-stlex.stlex_Strlen(tmp,1,2,langDup.lang_GetDefaultCode())/2, 34, tmp, base_ColorID_Yellow); pxList.pointset_Add(pxPtr, 20);
	tmp = langDup.lang_GetString(langDup.TEXT_INFO_DO_NOT_DISTRIBUTE);
	pxPtr = new Game_Point(1, 38, tmp, base_ColorID_Green); pxList.pointset_Add(pxPtr, 20);
}
void Game_Scene::scene_MainTitle_SetHighlight(int x, Game_PointCollection& pxList) {
	Game_Point *pxPtr[9];
	for (int i = 1; i <= 9; i++) {
		pxPtr[i - 1] = pxList.pointset_GetByAlias(i);
	}
	for (int i = 0; i < 9; i++) {
		pxPtr[i]->point_SetForeColor(base_ColorID_White);
		pxPtr[i]->point_SetBackColor(base_ColorID_Default);
	}
	pxPtr[x * 3]->point_SetForeColor(base_ColorID_Yellow);
	pxPtr[x * 3]->point_SetBackColor(base_ColorID_Red);
	pxPtr[x * 3 +1]->point_SetForeColor(base_ColorID_Yellow);
	pxPtr[x * 3 +1]->point_SetBackColor(base_ColorID_Red);
	pxPtr[x * 3 +2]->point_SetForeColor(base_ColorID_Yellow);
	pxPtr[x * 3 +2]->point_SetBackColor(base_ColorID_Red);
}


void Game_Scene::scene_Exception_CodePageUnsupported(const Game_Localization& langObj, Game_PointCollection& pxList) {
	Game_Localization langDup(((Game_Localization)langObj).lang_GetDefaultArea());
	Game_Point* pxPtr;
	pxPtr = new Game_Point(23, 10, langDup.lang_GetString(langDup.TEXT_EXCEPTHANDLE_HEADER)); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(23 + 5, 12, langDup.lang_GetString(langDup.TEXT_EXCEPTION_CODEPAGE_NOT_SUPPORTED)); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(23 + 5, 13, langDup.lang_GetString(langDup.TEXT_EXCEPTION_CODEPAGE_NOT_SUPPORTED_2)); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(23 + 5, 15, langDup.lang_GetString(langDup.TEXT_INFO_PRESS_ANY_KEY_TO_CONTINUE)); pxList.pointset_Add(pxPtr);
	pxPtr = new Game_Point(23, 17, "----------------------------------------------------------------------------"); pxList.pointset_Add(pxPtr);
}
