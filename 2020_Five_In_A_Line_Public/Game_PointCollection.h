#pragma once
#include "Game_Common.h"
#include "Game_Point.h"
class Game_PointCollection :public Game_Common{
private:
	bool autoDestroy;
	vector<Game_Point*> pxList;
	unordered_map<int, int> pxAliasMapping;
	
public:
	~Game_PointCollection();
	Game_PointCollection();
	void pointset_Add(Game_Point* pxPtr, int alias = 0);
	void pointset_Print(bool forceRedraw=false);
	void pointset_Destroy();
	Game_Point* pointset_GetByAlias(int alias);
	void pointset_SetAutoDestroy(bool opt = true);
};

//请勿对PixelCollections进行复制！否则将导致原有对象的Game_Point*被delete!