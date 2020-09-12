#include "Game_Operation.h"
//构造函数
Game_Operation::Game_Operation(const Game_Board* bindBoardObj, const Game_Display* bindDisplayObj, int leastChainBeads, int basicScore, int addedScore) {
	opBoard_Bind((Game_Board*)bindBoardObj);
	opDisplay_Bind((Game_Display*)bindDisplayObj);
	opRule_SetAddedScore(addedScore);
	opRule_SetLeastChainBeads(leastChainBeads);
	opRule_SetBasicScore(basicScore);
	counter_round = 0;
	counter_curPlayer = -1;
	base_Randomize();
	opRule_SetMoveLimit(true);
	opRule_SetForesee(false);
	opInput_SetDevice(2);
	int hashSeed = base_RandInt(0, 32767);
	randomGenerator.hash_SetSeed(hashSeed);
	counter_randomCnt1 = base_RandInt(0, 32767);
	counter_randomCnt2 = base_RandInt(0, 32767);
	argv_gotoMainTitle = 0;
	argv_langChanged = 0;
	rule_MoveAnimation = true;
	argv_ExitStat = 0;
}

//处理棋盘
void Game_Operation::opBoard_Bind(const Game_Board* boardPtr) {
	boardObject = (Game_Board*)boardPtr;
}
void Game_Operation::opBoard_RandomPlaces(int requestTiles) {
	int emptyCnt = boardObject->board_GetEmpty();
	int opCnt = (emptyCnt > requestTiles) ? requestTiles : emptyCnt;
	int t, sr;
	int sv = boardObject->board_GetTypes(), svt;
	base_Pair dest;
	for (int i = 0; i < opCnt; i++) {
		t = boardObject->board_GetEmpty();
		//svt = base_RandInt(0, sv - 1);
		//sr = base_RandInt(0, t - 1);
		svt = randomGenerator.hash_GetRangedCode(++counter_randomCnt1, 0, sv - 1);
		sr = randomGenerator.hash_GetRangedCode(++counter_randomCnt2, 0, t - 1);
		dest = boardObject->board_GetEmptyByIterator(sr);
		boardObject->board_SetElement(dest.x, dest.y, svt);
	}
}
void Game_Operation::opBoard_StartUp(int occupiedTiles) {
	opBoard_RandomPlaces(occupiedTiles);
}

int Game_Operation::opBoard_CheckMark(int& extraChance,int playerRemoval) {
	string opLog;
	vector<int>* adjGraph; //储存图
	adjGraph = new vector<int>[boardObject->board_GetSize()];
	bool* remStat; //储存销毁状态
	int* remDirection; //储存销毁方向
	remStat = new bool[boardObject->board_GetSize()];
	remDirection = new int[boardObject->board_GetSize()];
	for (int i = 0; i < boardObject->board_GetSize(); i++) remStat[i] = false, remDirection[i] = 0;
	stringstream oss;
	//建立图和标记销毁状态
	int curVid, forVid; //结点在图中的ID
	int chainCnt;
	for (int i = 0; i < boardObject->board_GetHeight(); i++) {
		for (int j = 0; j < boardObject->board_GetWidth(); j++) {
			if (boardObject->board_GetEmptyStat(i, j))continue;
			curVid = boardObject->board_GetVID(i, j);
			//右侧横向检测
			chainCnt = 0;
			for (int k = j; k < boardObject->board_GetWidth(); k++) {
				if (boardObject->board_GetElement(i, k) == boardObject->board_GetElement(i, j)) {
					chainCnt++;
				}
				else {
					break;
				}
			}
			if (chainCnt >= rule_MinChainBeads) {
				for (int k = j; k < j + chainCnt; k++) {
					forVid = boardObject->board_GetVID(i, k);
					remStat[forVid] = 1;
					remDirection[forVid] |= 1;
					if (k == j)continue;
					adjGraph[curVid].push_back(forVid);
					adjGraph[forVid].push_back(curVid);
				}
			}
			//下册纵向检测
			chainCnt = 0;
			for (int k = i; k < boardObject->board_GetHeight(); k++) {
				if (boardObject->board_GetElement(k, j) == boardObject->board_GetElement(i, j)) {
					chainCnt++;
				}
				else {
					break;
				}
			}
			if (chainCnt >= rule_MinChainBeads) {
				for (int k = i; k < i + chainCnt; k++) {
					forVid = boardObject->board_GetVID(k, j);
					remStat[forVid] = 1;
					remDirection[forVid] |= 2;
					if (i == k)continue;
					adjGraph[curVid].push_back(forVid);
					adjGraph[forVid].push_back(curVid);
				}
			}
			//右下斜向检测
			chainCnt = 0;
			for (int k = i, l = j; k < boardObject->board_GetHeight() && l < boardObject->board_GetWidth(); k++, l++) {
				if (boardObject->board_GetElement(k, l) == boardObject->board_GetElement(i, j)) {
					chainCnt++;
				}
				else {
					break;
				}
			}
			if (chainCnt >= rule_MinChainBeads) {
				for (int k = 0; k < chainCnt; k++) {
					forVid = boardObject->board_GetVID(i + k, j + k);
					remStat[forVid] = 1;
					remDirection[forVid] |= 4;
					if (k == 0)continue;
					adjGraph[curVid].push_back(forVid);
					adjGraph[forVid].push_back(curVid);
				}
			}
			//左下斜向检测
			chainCnt = 0;
			for (int k = i, l = j; k <boardObject->board_GetHeight() && l >=0; k++, l--) {
				if (boardObject->board_GetElement(k, l) == boardObject->board_GetElement(i, j)) {
					chainCnt++;
				}
				else {
					break;
				}
			}
			if (chainCnt >= rule_MinChainBeads) {
				for (int k = 0; k < chainCnt; k++) {
					forVid = boardObject->board_GetVID(i + k, j - k);
					remStat[forVid] = 1;
					remDirection[forVid] |= 8;
					if (k == 0)continue;
					adjGraph[curVid].push_back(forVid);
					adjGraph[forVid].push_back(curVid);
				}
			}
		}
	}
	//消除图的标记连通块
	queue<int> pendingList;
	string shwInf;
	Game_Algorithm::Binary bw;
	int clearCnt = 0;
	int scoreCnt = 0;
	int extChanceFlag = 0;
	int p, vecSz;
	base_Pair pPair;
	for (int i = 0; i < boardObject->board_GetHeight(); i++) {
		for (int j = 0; j < boardObject->board_GetWidth(); j++) {
			clearCnt = 0;
			curVid = boardObject->board_GetVID(i, j);
			if (!remStat[curVid] || boardObject->board_GetEmptyStat(i, j))continue;
			pendingList.push(curVid);
			while (!pendingList.empty()) { //队列空时，消除完毕
				p = pendingList.front();
				pendingList.pop();
				pPair = boardObject->board_GetPID(p);
				if (boardObject->board_GetEmptyStat(pPair.x, pPair.y))continue; //已经被消除的则跳过
				if (bw.bin_NumberOfOne(remDirection[curVid]) > 1) {
					extChanceFlag = 1;
				}
				boardObject->board_RemoveElement(pPair.x, pPair.y);
				opScene_UpdateBoardPixels();
				opDisplay_Print();
				opDisplay_Sleep(150);
				clearCnt++;
				vecSz = adjGraph[p].size();
				for (int k = 0; k < vecSz; k++) {
					pendingList.push(adjGraph[p][k]);
				}
			}
			if (playerRemoval) {
				scoreCnt += (rule_BasicScores + (clearCnt - rule_MinChainBeads)*rule_AddedScores);
				shwInf = langObject->lang_GetString(langObject->TEXT_LABEL_REMOVE_CNT);
				shwInf += base_Any2String(clearCnt);
				shwInf += " ";
				shwInf += langObject->lang_GetString(langObject->TEXT_LABEL_REMOVE_SCORE);
				shwInf += base_Any2String((clearCnt - rule_MinChainBeads)*rule_AddedScores + rule_BasicScores);
			}
			else {
				scoreCnt += 0;
				shwInf = langObject->lang_GetString(langObject->TEXT_LABEL_REMOVE_CNT);
				shwInf += base_Any2String(clearCnt);
				shwInf += " ";
				shwInf += langObject->lang_GetString(langObject->TEXT_LABEL_SYSTEM_REMOVAL);
			}
			
			//消除成功信息

			opScene_SetTipInfo(shwInf);
			opDisplay_Print();
			opDisplay_Sleep(1500);
		}
	}
	if (playerRemoval) {
		if (scoreCnt > 0) {
			shwInf = langObject->lang_GetString(langObject->TEXT_LABEL_REMOVE_TOTALSCORE);
			shwInf += base_Any2String(scoreCnt);
			shwInf += " ";
			shwInf += langObject->lang_GetString(langObject->TEXT_INFO_GAIN_ANOTHER_CHANCE);
			extraChance = 1;
		}
		else {
			shwInf = langObject->lang_GetString(langObject->TEXT_INFO_MOVE_WITHOUT_REMOVAL);
		}
		opScene_SetTipInfo(shwInf);
		opDisplay_Sleep(1000 + (scoreCnt > 0) * 1300);
	}
	
	delete[] adjGraph; //delete 动态新建的Vector
	delete[] remStat;
	delete[]remDirection;
	return scoreCnt;
}
//有效可达路径
bool Game_Operation::opBoard_AvailableMove(const base_Pair& source, const base_Pair& destination, vector<int>& routeList) {
	if (rule_MoveLimit == false) { //移动限制被关闭时
		routeList.push_back(boardObject->board_GetVID(destination.x, destination.y));
		routeList.push_back(boardObject->board_GetVID(source.x, source.y));
		return true;
	}
	vector<int>* adjGraph;//建立图
	queue<int> pendingList;
	int* dist; //最短路径长
	int* pred; //更新最短路径的来源
	bool* vis;
	int sourceVID = boardObject->board_GetVID(source.x, source.y), forVID, destVID = boardObject->board_GetVID(destination.x, destination.y);
	int p;
	base_Pair pPair;

	adjGraph = new vector<int>[boardObject->board_GetSize()];
	dist = new int[boardObject->board_GetSize()];
	pred = new int[boardObject->board_GetSize()];
	vis = new bool[boardObject->board_GetSize()];
	for (int i = 0; i < boardObject->board_GetSize(); i++) dist[i] = 9999,pred[i]=-1, vis[i] = false;
	dist[sourceVID] = 0;
	pred[sourceVID] = -2;
	pendingList.push(sourceVID);

	//更新可达状态
	while (!pendingList.empty()) {
		p = pendingList.front();
		pendingList.pop();
		vis[p] = true;
		pPair = boardObject->board_GetPID(p);
		//结点上侧
		if (pPair.x - 1 >= 0) {
			if (boardObject->board_GetEmptyStat(pPair.x - 1, pPair.y)) {
				forVID = boardObject->board_GetVID(pPair.x - 1, pPair.y);
				if (dist[p] + 1 < dist[forVID]) {
					dist[forVID] = dist[p] + 1;
					pred[forVID] = p;
					pendingList.push(forVID);
				}
			}
		}
		//结点下侧
		if (pPair.x + 1 < boardObject->board_GetHeight()) {
			if (boardObject->board_GetEmptyStat(pPair.x + 1, pPair.y)) {
				forVID = boardObject->board_GetVID(pPair.x + 1, pPair.y);
				if (dist[p] + 1 < dist[forVID]) {
					dist[forVID] = dist[p] + 1;
					pred[forVID] = p;
					pendingList.push(forVID);
				}
			}
		}
		//结点左侧
		if (pPair.y - 1 >= 0) {
			if (boardObject->board_GetEmptyStat(pPair.x, pPair.y - 1)) {
				forVID = boardObject->board_GetVID(pPair.x, pPair.y - 1);
				if (dist[p] + 1 < dist[forVID]) {
					pendingList.push(forVID);
					dist[forVID] = dist[p] + 1;
					pred[forVID] = p;
				}
			}
		}
		//结点右侧
		if (pPair.y + 1 < boardObject->board_GetWidth()) {
			if (boardObject->board_GetEmptyStat(pPair.x, pPair.y + 1)) {
				forVID = boardObject->board_GetVID(pPair.x, pPair.y + 1);
				if (dist[p] + 1 < dist[forVID]) {
					pendingList.push(forVID);
					dist[forVID] = dist[p] + 1;
					pred[forVID] = p;
				}
			}
		}
	}
	//更新最短路径的vector
	if (dist[destVID] != 9999) {
		int cur = destVID;
		routeList.push_back(cur);
		while (1) {
			cur = pred[cur];
			if (cur >= 0) {
				routeList.push_back(cur);
			}
			else if (cur == -2) {
				break;
			}
			else {
				
			}
		}
	}
	bool retValue = (dist[destVID] != 9999);
	delete[] adjGraph;
	delete[] pred;
	delete[] vis;
	delete[] dist;
	return retValue;
}
int Game_Operation::opBoard_Move(const base_Pair& source, const base_Pair& destination) {
	vector<int> routeRecord;
	if (source.x<0 || source.x>boardObject->board_GetHeight()) {
		return 8;
	}
	if (source.y<0 || source.y>boardObject->board_GetWidth()) {
		return 8;
	}
	bool validMove = opBoard_AvailableMove(source, destination, routeRecord);
	bool nonEmpty = !boardObject->board_GetEmptyStat(source.x, source.y);
	bool nonBlocked = boardObject->board_GetEmptyStat(destination.x, destination.y);
	if (validMove&&nonEmpty&&nonBlocked) {
		int sourceType = boardObject->board_GetElement(source.x, source.y);
		if (rule_MoveAnimation == false) {
			boardObject->board_RemoveElement(source.x, source.y);
			boardObject->board_SetElement(destination.x, destination.y, sourceType);
		}
		else {
			int vecSz = routeRecord.size();
			base_Pair cur, prev;
			for (int i = vecSz - 1; i >= 1; i--) {
				cur = boardObject->board_GetPID(routeRecord[i - 1]);
				prev = boardObject->board_GetPID(routeRecord[i]);
				boardObject->board_RemoveElement(prev.x, prev.y);
				boardObject->board_SetElement(cur.x, cur.y, sourceType);
				opScene_UpdateBoardPixels();
				opDisplay_Print();
				opDisplay_Sleep(75);
			}
		}
		return 0;
	}
	else {
		int retVal=0;
		if (validMove==false) retVal |= 1;
		if (nonEmpty == false) retVal |= 2;
		if (nonBlocked == false) retVal |= 4;
		return retVal;
	}
}
bool Game_Operation::opBoard_AllOccupied() {
	if (boardObject->board_GetEmpty() == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Game_Operation::opBoard_AllEmpty() {
	if (boardObject->board_GetEmpty() == boardObject->board_GetSize()) {
		return true;
	}
	else {
		return false;
	}
}
void Game_Operation::opBoard_GetForeseeResult(vector<int>& resultAcceptor) {
	int b = boardObject->board_GetTypes();
	int t = 3;
	for (int i = 1; i <= t; i++) {
		if (rule_EnableForesee) {
			resultAcceptor.push_back(randomGenerator.hash_GetRangedCode(counter_randomCnt1 + i, 0, b - 1));
		}
		else {
			resultAcceptor.push_back(-1);
		}

	}
}
//处理场景
void Game_Operation::opScene_Bind(const Game_Scene* scenePtr) {
	sceneObject = (Game_Scene*)scenePtr;
}
void Game_Operation::opScene_Init() {
	//主场景建构

	argv_boardMarginLeft = base_DefaultBoardMarginLeft;
	argv_boardMarginTop = base_DefaultBoardMarginTop;
	sceneObject->scene_ConstructBoardPixels(*langObject,*boardObject, sceneObject->scene_Board, argv_boardMarginLeft, argv_boardMarginTop);
	
	sceneObject->scene_ConstructLeftBarPixels(*langObject,sceneObject->scene_LeftBar);
	sceneObject->scene_ConstructBottomBarPixels(*langObject,sceneObject->scene_BottomBar);

	//辅助场景建构
	sceneObject->scene_ConstructRestartConfirm(*langObject, sceneObject->scene_RestartConfirm);
	sceneObject->scene_ConstructExitConfirm(*langObject, sceneObject->scene_ExitConfirm);
	sceneObject->scene_ConstructHelpBox(*langObject, sceneObject->scene_HelpBox);
	sceneObject->scene_ConstructCreditBox(*langObject, sceneObject->scene_Author);
	sceneObject->scene_ConstructSettingBox(*langObject, sceneObject->scene_SettingBox);
	sceneObject->scene_ConstructSettingBox_MoveLimit(*langObject, sceneObject->scene_SettingBox_MoveLimit);
	sceneObject->scene_ConstructSettingBox_Lang(*langObject, sceneObject->scene_SettingBox_Lang);
	sceneObject->scene_ConstructSettingBox_Foresee(*langObject, sceneObject->scene_SettingBox_Foresee);
	sceneObject->scene_ConstructSettingBox_InputDevice(*langObject, sceneObject->scene_SettingBox_InputDevice);
	sceneObject->scene_Construct_TipUniversal(*langObject, sceneObject->scene_ComingSoonBox, langObject->lang_GetString(langObject->TEXT_INFO_COMING_SOON));
	sceneObject->scene_Construct_TipUniversal(*langObject,sceneObject->scene_OSNotSupported,langObject->lang_GetString(langObject->TEXT_INFO_OS_NOT_SUPPORTED));
	sceneObject->scene_ConstructSettingBox_MoveAnimation(*langObject, sceneObject->scene_SettingBox_MoveAnimation);
}
void Game_Operation::opScene_UpdateBoardPixels(vector<base_Pair> highlightList) {
	sceneObject->scene_SyncBoardPixels(*boardObject, sceneObject->scene_Board, highlightList);
}
void Game_Operation::opScene_SetTipInfo(string tipStr) {
	sceneObject->scene_SyncTipInfo(tipStr, sceneObject->scene_BottomBar, true);
}
void Game_Operation::opScene_UpdateForeseeResult() {
	vector<int> resPlace;
	opBoard_GetForeseeResult(resPlace);
	sceneObject->scene_SyncForeseeResult(*langObject,*boardObject,resPlace,sceneObject->scene_LeftBar);
}
void Game_Operation::opScene_UpdateSourceCell(int x, int y) { //1为下界
	if (x != 0 || y != 0) {
		sceneObject->scene_SyncSourceCoord(x, y, sceneObject->scene_BottomBar, langObject->lang_GetString(langObject->TEXT_INFO_NOT_INPUTTED));
		if (boardObject->board_GetEmptyStat(x-1, y-1) != true) {
			sceneObject->scene_SyncSourcePattern(boardObject->board_GetBeadMappingColors(boardObject->board_GetElement(x-1, y-1)), boardObject->board_GetBeadMappingChars(boardObject->board_GetElement(x-1, y-1)), sceneObject->scene_BottomBar);
		}
		else {
			sceneObject->scene_SyncSourcePattern(base_ColorID_White, "?", sceneObject->scene_BottomBar);
		}
	}
	else {
		sceneObject->scene_SyncSourceCoord(0, 0, sceneObject->scene_BottomBar, langObject->lang_GetString(langObject->TEXT_INFO_NOT_INPUTTED));
		sceneObject->scene_SyncSourcePattern(base_ColorID_White, "X", sceneObject->scene_BottomBar);

	}
	sceneObject->scene_BottomBar.pointset_Print(true);
}
void Game_Operation::opScene_UpdateScores(Game_Player* playerObj) {
	sceneObject->scene_SyncScores(playerObj->player_GetScores(), *langObject, sceneObject->scene_LeftBar);
}
void Game_Operation::opScene_UpdateScoresDefault() {
	opScene_UpdateScores(playerObjectList[0]);
}

//处理语言
void Game_Operation::opLang_Bind(const Game_Localization* langPtr) {
	langObject = (Game_Localization*)langPtr;
}


//处理显示
void Game_Operation::opDisplay_Bind(const Game_Display* displayPtr) { displayObject = (Game_Display*)displayPtr; }
void Game_Operation::opDisplay_Sleep(int delayms) { displayObject->display_sleep(delayms); }
void Game_Operation::opDisplay_Print(bool forceRedraw) {
	sceneObject->scene_Board.pointset_Print(forceRedraw);
	sceneObject->scene_LeftBar.pointset_Print(forceRedraw);
	sceneObject->scene_BottomBar.pointset_Print(forceRedraw);
}


//处理输入
void Game_Operation::opInput_ReadMovementCoord(int &a, int &b, int &c, int &d,int &extFlag) {
	opScene_UpdateSourceCell(0, 0);
	opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_SOURCECOORD_X));
	inputInf.input_readInputCoord(a, langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_COORD),langObject->lang_GetDefaultCode());
	if (opInput_ReadMovementCoordExt(a, extFlag) != 0) return;
	opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_SOURCECOORD_Y));
	inputInf.input_readInputCoord(b, langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_COORD), langObject->lang_GetDefaultCode());
	if (opInput_ReadMovementCoordExt(b, extFlag) != 0) return;
	opScene_UpdateSourceCell(a, b);
	opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_DESTCOORD_X));
	inputInf.input_readInputCoord(c, langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_COORD), langObject->lang_GetDefaultCode());
	if (opInput_ReadMovementCoordExt(c, extFlag) != 0) {
		opScene_UpdateSourceCell(0, 0);
		return;
	}
	opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_DESTCOORD_Y));
	inputInf.input_readInputCoord(d, langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_COORD), langObject->lang_GetDefaultCode());
	if (opInput_ReadMovementCoordExt(d, extFlag) != 0) {
		opScene_UpdateSourceCell(0, 0);
		return;
	}
	a--, b--, c--, d--;
}
void Game_Operation::opInput_ReadMovementCoord2(int &a, int &b, int &c, int &d, int &extFlag) {
	if (input_InputDevice == 1) {
		opScene_UpdateSourceCell(0, 0);
		opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_CLICK_SOURCECOORD));
		while (1) {
			opInput_MouseInput(a, b, extFlag);
			if (extFlag != -1) {
				if (boardObject->board_GetEmptyStat(a, b) == false) {
					break;
				}
			}
		}
		
		if (extFlag == 0) {
			while (1) {
				opScene_UpdateSourceCell(a + 1, b + 1);
				opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_GUIDE_INPUT_CLICK_DESTCOORD));
				while (1) {
					opInput_MouseInput(c, d, extFlag);
					if (extFlag != -1)break;
				}
				if (extFlag == 0) {
					if (boardObject->board_GetEmptyStat(c, d) == false) {
						a = c;
						b = d;
					}
					else {
						break;
					}
				}
				else if (extFlag != 0) {
					opScene_UpdateSourceCell(0, 0);
					break;
				}
			}
		}
		opScene_UpdateSourceCell(0, 0);
	}
	else {
		opInput_ReadMovementCoord(a, b, c, d, extFlag);
	}
}
void Game_Operation::opInput_ReadFunc(int& extFlag) {
	int s;
	while (1) {
		s = inputInf.input_readCh()-'0';
		opInput_ReadMovementCoordExt(s, extFlag);
		if (extFlag != 6 || extFlag != 0 || extFlag!=-1)return;
	}
}
int Game_Operation::opInput_ReadMovementCoordExt(int& val, int& extFlag) {
	if (val + '0' == 'r' || val + '0' == 'R') {
		extFlag = 1;
	}
	else if (val + '0' == 'h' || val + '0' == 'H') {
		extFlag = 2;
	}
	else if (val + '0' == 'e' || val + '0' == 'E') {
		extFlag = 3;
	}
	else if (val + '0' == 'c' || val + '0' == 'C') {
		extFlag = 4;
	}
	else if (val + '0' == 'a' || val + '0' == 'A') {
		extFlag = 5;
	}
	else if (val + '0' == 'p' || val + '0' == 'P') {
		extFlag = 6;
	}
	else if (val + '0' == 's' || val + '0' == 'S') {
		extFlag = 7;
	}
	else if (val > 0 && val < 10) {
		extFlag = 0;
	}
	else {
		extFlag = -1;
	}
	return extFlag;
}
void Game_Operation::opInput_Waiting() {
	inputInf.input_pressKeyToContinue();
}
Game_Operation::base_Pair Game_Operation::opInput_MousePosConversion(int mouseX, int mouseY) {
	int convX, convY;
	convX = (mouseX - argv_boardMarginLeft) / 4;
	convY = (mouseY - argv_boardMarginTop) / 2;
	if ((mouseX - argv_boardMarginLeft) % 4 == 0) {
		convX--;
	}
	if ((mouseY - argv_boardMarginTop) % 2 == 0) {
		convX = 0;
		convY = 0;
	}
	base_Pair ret = { convX,convY };
	return ret;
}
void Game_Operation::opInput_MouseInput(int &a,int &b,int &extFlag) {
	base_InputInfo readInfo;
	base_Pair convPos;
	while (1) {
		//readInfo = inputInf.input_CompInput();
		readInfo = opInput_MouseInput2();
		if (readInfo.deviceType == 1) {
			convPos = opInput_MousePosConversion(readInfo.mouseInfo.x, readInfo.mouseInfo.y);
			b = convPos.x - 1;
			a = convPos.y - 1;
			if (b >= 0 && b < boardObject->board_GetWidth() && a >= 0 && a < boardObject->board_GetHeight()) {
				extFlag = 0;
			}
			else {
				extFlag = -1;
			}

			return;
		}
		else if(readInfo.deviceType==2) {
			if (readInfo.keyInfo == 0x52) {
				extFlag = 1;
				return;
			}
			else if (readInfo.keyInfo == 0x48) {
				extFlag = 2;
				return;
			}
			else if (readInfo.keyInfo == 0x45) {
				extFlag = 3;
				return;
			}
			else if (readInfo.keyInfo == 0x43) {
				extFlag = 4;
				return;
			}
			else if (readInfo.keyInfo == 0x41) {
				extFlag = 5;
				return;
			}
			else if (readInfo.keyInfo == 0x50) {
				extFlag = 6;
				return;
			}
			else if (readInfo.keyInfo == 0x53) {
				extFlag = 7;
				return;
			}
		}

	}
}
void Game_Operation::opInput_SetDevice(int deviceId) {
	input_InputDevice = deviceId;
}
Game_Operation::base_InputInfo Game_Operation::opInput_MouseInput2() {
	if (base_CompileOS == 1) {
		base_InputInfo ret;
		Game_Interface sysInf;
		int highlightFlag = 0;
		while (1) {
			sysInf.interface_enableMouseInput();
			ret = sysInf.interface_getInput();
			sysInf.interface_disableMouseInput();
			if (ret.deviceType == 1) {
				if (ret.mouseExtInfo2 == 1) {
					return ret;
				}
				else {
					base_Pair mcoord = opInput_MousePosConversion(ret.mouseInfo.x, ret.mouseInfo.y);
					if (mcoord.x > 0 && mcoord.x <= boardObject->board_GetHeight()&&
						mcoord.y>0&&mcoord.y<=boardObject->board_GetWidth()) {
						vector<base_Pair> mouseOverCellVec;
						base_Pair bkp = { mcoord.y - 1,mcoord.x - 1 };
						mouseOverCellVec.push_back(bkp);
						opScene_UpdateBoardPixels(mouseOverCellVec);
						opDisplay_Print();
						highlightFlag = 1;
					}
					else {
						if (highlightFlag == 1) {
							highlightFlag = 0;
							opScene_UpdateBoardPixels();
							opDisplay_Print();
						}
					}
				}
			}
			else if (ret.deviceType == 2) {
				if (ret.keyDown == true) {
					return ret;
				}
			}
		}
		return ret;
	}
}

//游戏规则
void Game_Operation::opRule_SetLeastChainBeads(int leastValue) { rule_MinChainBeads = leastValue; }
void Game_Operation::opRule_SetAddedScore(int setValue) { rule_AddedScores = setValue; }
void Game_Operation::opRule_SetBasicScore(int setValue) { rule_BasicScores = setValue; }
void Game_Operation::opRule_SetMoveLimit(bool setValue) { rule_MoveLimit = setValue; }
void Game_Operation::opRule_SetMoveAnimation(bool setValue) { rule_MoveAnimation = setValue; }
void Game_Operation::opRule_SetForesee(bool setValue) { rule_EnableForesee = setValue; }
//游戏功能
void Game_Operation::opFunc_Restart() {
	boardObject->board_Reset(); //棋盘重置
	for (int i = 0; i < (int)playerObjectList.size(); i++) {
		playerObjectList[i]->player_SetScore(0); //分数重置
	}
	counter_randomCnt1 = base_RandInt(0, 32767);
	counter_randomCnt2 = base_RandInt(0, 32767);
	opBoard_StartUp();
	opScene_UpdateBoardPixels();
	opScene_UpdateForeseeResult();
	if (playerObjectList.size() == 1) {
		sceneObject->scene_SyncScores(playerObjectList[0]->player_GetScores(),*langObject, sceneObject->scene_LeftBar);
	}

	displayObject->display_cls();
	opDisplay_Print(true);
	opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_INFO_GAME_RESTARTED));
	opDisplay_Sleep(1000);
}
void Game_Operation::opFunc_AntiCheat(Game_Player* playerObj) {
	int keyP;
	if(playerObj->player_ValidateCheat()){
		while (1) {
			opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_INFO_CHEAT_DETECTED));
			keyP = inputInf.input_readCh();
		}
	}
}
void Game_Operation::opFunc_Exit() {
	displayObject->display_cls();
	argv_ExitStat = 1;
}
void Game_Operation::opFunc_GotoMainTitle() {
	argv_gotoMainTitle = 1;
}
void Game_Operation::opFunc_AfterLangChange(int newLangID) {
	argv_langChanged = newLangID;
}
bool Game_Operation::opFunc_CheckGotoMainTitleStat() {
	return argv_gotoMainTitle;
}
int Game_Operation::opFunc_CheckLangChange() {
	return argv_langChanged;
}
void Game_Operation::opFunc_Save() {
	Game_File v(langObject->lang_GetDefaultArea());
	Game_Save saveData(langObject->lang_GetDefaultArea());
	saveData.save_ConvertToSave(playerObjectList[0], boardObject);
	saveData.save_GameArgv1 = randomGenerator.hash_GetSeed();
	saveData.save_GameArgv2 = counter_randomCnt1;
	saveData.save_GameArgv3 = counter_randomCnt2;
	saveData.save_GameArgv_Foresee = rule_EnableForesee;
	saveData.save_GameArgv_MoveLimit = rule_MoveLimit;

	saveData.save_VitalGameArgv_Height = base_DefaultBoardHeight;
	saveData.save_VitalGameArgv_Width = base_DefaultBoardWidth;
	saveData.save_VitalGameArgv_TypeCount = base_DefaultBeadTypes;

	v.gamefile_Save(saveData);
	opDisplay_Print(true);
	opScene_SetTipInfo(langObject->lang_GetString(langObject->TEXT_INFO_GAME_SAVED));
	displayObject->display_sleep(1000);
}
void Game_Operation::opFunc_GameLoad(Game_Save& svData) {
	Game_Algorithm::STLExtensions stringSeparator;
	//载入棋盘
	vector<string> stringPlace;
	base_Pair coordPair;
	int stringConv;
	int vecsz;
	stringSeparator.stlex_StringSplit(svData.save_BoardData, ",", stringPlace);
	vecsz = stringPlace.size();
	for (int i = 0; i < vecsz; i++) {
		stringConv = (stoi(stringPlace[i]));
		if (stringConv == -1)continue;
		coordPair = boardObject->board_GetPID(i);
		boardObject->board_SetElement(coordPair.x, coordPair.y, stringConv);
	}
	//载入玩家
	playerObjectList[0]->player_SetSeed(svData.save_PlayerScoreSeed);
	playerObjectList[0]->player_SetScore(svData.save_PlayerScore);
	//载入游戏设置
	randomGenerator.hash_SetSeed(svData.save_GameArgv1);
	counter_randomCnt1 = svData.save_GameArgv2;
	counter_randomCnt2 = svData.save_GameArgv3;
	opRule_SetForesee(svData.save_GameArgv_Foresee);
	opRule_SetMoveLimit(svData.save_GameArgv_MoveLimit);

}
bool Game_Operation::opFunc_GetExitRequest() {
	return argv_ExitStat;
}
//玩家处理
void Game_Operation::opPlayer_AddPlayer(Game_Player* playerObj) { playerObjectList.push_back(playerObj); }
bool Game_Operation::opPlayerAct_CheckClear(Game_Player* playerObj, bool sysOp) {
	int scores, extChance=0;
	if (!sysOp) {
		scores = opBoard_CheckMark(extChance,1);
	}
	else {
		scores = opBoard_CheckMark(extChance,0);
	}
	opFunc_AntiCheat(playerObj);
	playerObj->player_AddScore(scores);
	opFunc_AntiCheat(playerObj);
	sceneObject->scene_SyncScores(playerObj->player_GetScores(),*langObject, sceneObject->scene_LeftBar);
	return extChance;
}


//辅助场景处理
void Game_Operation::opSubScene_Restart() {
	int selOpt = 0,keyP;
	displayObject->display_cls();
	sceneObject->scene_YesNoBox_SetHighlight(0, sceneObject->scene_RestartConfirm);
	sceneObject->scene_RestartConfirm.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Left || keyP == base_GetchVal_Right) {
			selOpt = 1 - selOpt;
			sceneObject->scene_YesNoBox_SetHighlight(selOpt, sceneObject->scene_RestartConfirm);
			sceneObject->scene_RestartConfirm.pointset_Print();
		}
		if (keyP == inputInf.input_enterKeyVal()) {
			if (selOpt == 0) {
				opFunc_Restart();
				return;
			}
			else {
				displayObject->display_cls();
				opDisplay_Print(true);
				return;
			}
		}
		if (keyP == 'Y' || keyP == 'y') {
			opFunc_Restart();
			return;
		}
		if (keyP == 'N' || keyP == 'n') {
			displayObject->display_cls();
			opDisplay_Print(true);
			return;
		}
	}
}
void Game_Operation::opSubScene_Help() {
	int keyP;
	displayObject->display_cls();
	sceneObject->scene_HelpBox.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == inputInf.input_enterKeyVal() || keyP == 'C' || keyP == 'c') {
			displayObject->display_cls();
			opDisplay_Print(true);
			return;
		}
	}
}

void Game_Operation::opSubScene_Author() {
	int keyP;
	displayObject->display_cls();
	sceneObject->scene_Author.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == inputInf.input_enterKeyVal() || keyP == 'C' || keyP == 'c') {
			displayObject->display_cls();
			opDisplay_Print(true);
			return;
		}
	}
}
void Game_Operation::opSubScene_Exit() {
	int keyP,selOpt=0;
	displayObject->display_cls();
	sceneObject->scene_ExitConfirm_SetHighlight(0, sceneObject->scene_ExitConfirm);
	sceneObject->scene_ExitConfirm.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Left) {
			selOpt--;
			if (selOpt < 0)selOpt += 3;
			sceneObject->scene_ExitConfirm_SetHighlight(selOpt, sceneObject->scene_ExitConfirm);
			sceneObject->scene_ExitConfirm.pointset_Print();
		}
		if (keyP == base_GetchVal_Right) {
			selOpt++;
			if (selOpt >=3)selOpt -= 3;
			sceneObject->scene_ExitConfirm_SetHighlight(selOpt, sceneObject->scene_ExitConfirm);
			sceneObject->scene_ExitConfirm.pointset_Print();
		}
		if (keyP == 'C' || keyP == 'c' || (selOpt == 2 && keyP == inputInf.input_enterKeyVal())) { //取消退出
			displayObject->display_cls();
			opDisplay_Print(true);
			return;
		}
		if (keyP == 'E' || keyP == 'e' || (selOpt == 1 && keyP == inputInf.input_enterKeyVal())) { //直接退出
			opFunc_Exit();
			return;
		}
		if (keyP == 'T' || keyP == 't' || (selOpt == 0 && keyP == inputInf.input_enterKeyVal())) { //直接退出
			displayObject->display_cls();
			opFunc_GotoMainTitle();
			return;
		}
	}
}

void Game_Operation::opSubScene_SettingMain() {
	int keyP, selOpt = 0, childOpen = false;
	displayObject->display_cls();
	sceneObject->scene_SettingBox_SetHighlight(0, sceneObject->scene_SettingBox);
	sceneObject->scene_SettingBox.pointset_Print(true);
	while (1) {
		if (childOpen) {
			displayObject->display_cls();
			sceneObject->scene_SettingBox_SetHighlight(selOpt, sceneObject->scene_SettingBox);
			sceneObject->scene_SettingBox.pointset_Print(true);
			childOpen = false;
		}
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Up) {
			selOpt--; if (selOpt < 0)selOpt += 6;
			sceneObject->scene_SettingBox_SetHighlight(selOpt, sceneObject->scene_SettingBox);
			sceneObject->scene_SettingBox.pointset_Print();
		}
		if (keyP == base_GetchVal_Down) {
			selOpt++; if (selOpt >= 6)selOpt -= 6;
			sceneObject->scene_SettingBox_SetHighlight(selOpt, sceneObject->scene_SettingBox);
			sceneObject->scene_SettingBox.pointset_Print();
		}
		if (keyP == 'C' || keyP == 'c' || (selOpt == 5 && keyP == inputInf.input_enterKeyVal())) { //取消退出
			displayObject->display_cls();
			opDisplay_Print(true);
			return;
		}
		if (keyP == 'S' || keyP == 's' || (selOpt == 4 && keyP == inputInf.input_enterKeyVal())) { //取消退出
			childOpen = true;
			displayObject->display_cls();
			opSubScene_Setting_MoveAnimation();
		}
		if (keyP == 'M' || keyP == 'm' || (selOpt == 3 && keyP == inputInf.input_enterKeyVal())) { //取消退出
			childOpen = true;
			displayObject->display_cls();
			opSubScene_Setting_MoveLimit();
		}
		if (keyP == 'D' || keyP == 'd' || (selOpt == 0 && keyP == inputInf.input_enterKeyVal())) { //取消退出
			childOpen = true;
			displayObject->display_cls();
			bool flg = ((base_CompileOS) == 1);
			if(flg){
                opSubScene_Setting_InputDevice();
			}else{
                opSubScene_InfoWindow(&(sceneObject->scene_OSNotSupported));
			}

		}
		if (keyP == 'L' || keyP == 'l' || (selOpt == 1 && keyP == inputInf.input_enterKeyVal())) { //取消退出
			childOpen = true;
			displayObject->display_cls();
			opSubScene_Setting_Lang();
			displayObject->display_cls();
			if (opFunc_CheckLangChange() != 0) {
				return;
			}
			
		}
		if (keyP == 'F' || keyP == 'f' || (selOpt == 2 && keyP == inputInf.input_enterKeyVal())) { //取消退出
			childOpen = true;
			displayObject->display_cls();
			opSubScene_Setting_Foresee();
		}
	}
}
void Game_Operation::opSubScene_Setting_MoveLimit() {
	int keyP, selOpt = 0;
	displayObject->display_cls();
	sceneObject->scene_YesNoBox_SetHighlight(0, sceneObject->scene_SettingBox_MoveLimit);
	sceneObject->scene_SettingBox_MoveLimit.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Left || keyP == base_GetchVal_Right) {
			selOpt = 1 - selOpt;
			sceneObject->scene_YesNoBox_SetHighlight(selOpt, sceneObject->scene_SettingBox_MoveLimit);
			sceneObject->scene_SettingBox_MoveLimit.pointset_Print();
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 1) || keyP == 't' || keyP == 'T') {
			opRule_SetMoveLimit(false);
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 0) || keyP == 's' || keyP == 'S') {
			opRule_SetMoveLimit(true);
			displayObject->display_cls();
			return;
		}
	}
}
void Game_Operation::opSubScene_Setting_MoveAnimation() {
	int keyP, selOpt = 0;
	displayObject->display_cls();
	sceneObject->scene_YesNoBox_SetHighlight(0, sceneObject->scene_SettingBox_MoveAnimation);
	sceneObject->scene_SettingBox_MoveAnimation.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Left || keyP == base_GetchVal_Right) {
			selOpt = 1 - selOpt;
			sceneObject->scene_YesNoBox_SetHighlight(selOpt, sceneObject->scene_SettingBox_MoveAnimation);
			sceneObject->scene_SettingBox_MoveAnimation.pointset_Print();
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 1) || keyP == 'n' || keyP == 'N') {
			opRule_SetMoveAnimation(false);
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 0) || keyP == 'y' || keyP == 'Y') {
			opRule_SetMoveAnimation(true);
			displayObject->display_cls();
			return;
		}
	}
}
void Game_Operation::opSubScene_Setting_Foresee() {
	int keyP, selOpt = 0;
	displayObject->display_cls();
	sceneObject->scene_YesNoBox_SetHighlight(0, sceneObject->scene_SettingBox_Foresee);
	sceneObject->scene_SettingBox_Foresee.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Left || keyP == base_GetchVal_Right) {
			selOpt = 1 - selOpt;
			sceneObject->scene_YesNoBox_SetHighlight(selOpt, sceneObject->scene_SettingBox_Foresee);
			sceneObject->scene_SettingBox_Foresee.pointset_Print();
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 1) || keyP == 't' || keyP == 'T') {
			opRule_SetForesee(false);
			opScene_UpdateForeseeResult();
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 0) || keyP == 's' || keyP == 'S') {
			opRule_SetForesee(true);
			opScene_UpdateForeseeResult();
			displayObject->display_cls();
			return;
		}
	}
}

void Game_Operation::opSubScene_Setting_Lang() {
	int keyP, selOpt = 1;
	displayObject->display_cls();
	sceneObject->scene_LangConfirm_SetHighlight(selOpt, sceneObject->scene_SettingBox_Lang);
	sceneObject->scene_SettingBox_Lang.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Up || keyP == base_GetchVal_Down) {
			if (keyP == base_GetchVal_Up)selOpt--;
			if (keyP == base_GetchVal_Down)selOpt++;
			if (selOpt <= 0) selOpt += 5;
			if (selOpt > 5) selOpt -= 5;
			sceneObject->scene_LangConfirm_SetHighlight(selOpt, sceneObject->scene_SettingBox_Lang);
			sceneObject->scene_SettingBox_Lang.pointset_Print();
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 4) ) {
			opFunc_AfterLangChange(4);
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 3)) {

			opFunc_AfterLangChange(3);
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 2) ) {
			opFunc_AfterLangChange(2);
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 1)) {
			opFunc_AfterLangChange(1);
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 5)|| keyP=='c'||keyP=='C') {
			displayObject->display_cls();
			return;
		}
	}
}

void Game_Operation::opSubScene_Setting_InputDevice() {
	int keyP, selOpt = 0;
	displayObject->display_cls();
	sceneObject->scene_YesNoBox_SetHighlight(0, sceneObject->scene_SettingBox_InputDevice);
	sceneObject->scene_SettingBox_InputDevice.pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if (keyP == base_GetchVal_Left || keyP == base_GetchVal_Right) {
			selOpt = 1 - selOpt;
			sceneObject->scene_YesNoBox_SetHighlight(selOpt, sceneObject->scene_SettingBox_InputDevice);
			sceneObject->scene_SettingBox_InputDevice.pointset_Print();
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 0) || keyP == 'k' || keyP == 'K') {
			opInput_SetDevice(2);
			displayObject->display_cls();
			return;
		}
		if ((keyP == inputInf.input_enterKeyVal() && selOpt == 1) || keyP == 'm' || keyP == 'M') {
			opInput_SetDevice(1);
			displayObject->display_cls();
			return;
		}
	}
}

void Game_Operation::opSubScene_InfoWindow(Game_PointCollection* callDest) {
	int keyP;
	displayObject->display_cls();
	callDest->pointset_Print(true);
	while (1) {
		keyP = inputInf.input_readCh();
		if ((keyP == inputInf.input_enterKeyVal()) || keyP == 'y' || keyP == 'Y') {
			displayObject->display_cls();
			return;
		}
	}
}


//测试功能
void Game_Operation::opDebug_BoardPlace(int x, int y, int Type) {
	boardObject->board_SetElement(x, y, Type);
	//displayObject->display_PrintBoard(*boardObject, true);
}

void Game_Operation::opDebug_SceneCall(Game_PointCollection* pxList) {
	pxList->pointset_Print();
}

string Game_Operation::opDebug_GetBoardElement(int x, int y) {
	stringstream oss;
	oss << boardObject->board_GetElement(x, y);
	return oss.str();
}

