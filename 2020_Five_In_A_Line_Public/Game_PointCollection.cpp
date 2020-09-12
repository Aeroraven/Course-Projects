#include "Game_PointCollection.h"
void Game_PointCollection::pointset_Add(Game_Point* pxPtr, int alias /* = 0 */) {
	int tid = pxList.size();
	pxList.push_back(pxPtr);
	pxAliasMapping[alias] = tid;
}
void Game_PointCollection::pointset_Print(bool forceRedraw) {
	//OutputDebugStringA("¡¾DIRECT CALL¡¿\n");
	int vecSz = pxList.size();
	for (int i = 0; i < vecSz; i++) {
		pxList[i]->point_Print(forceRedraw);
	}
	//OutputDebugStringA("¡¾DIRECT CALL END¡¿\n");
}
void Game_PointCollection::pointset_Destroy() {
	int vecSz = pxList.size();
	for (int i = 0; i < vecSz; i++) {
		delete pxList[i];
	}
	for (int i = 0; i < vecSz; i++) {
		pxList.pop_back();
	}
}
Game_Point* Game_PointCollection::pointset_GetByAlias(int alias) {
	return pxList[pxAliasMapping[alias]];
}
void Game_PointCollection::pointset_SetAutoDestroy(bool opt /* = true */) {
	autoDestroy = opt;
}
Game_PointCollection::Game_PointCollection() {
	autoDestroy = 1;
}
Game_PointCollection::~Game_PointCollection() {
	if (autoDestroy) {
		pointset_Destroy();
	}
}