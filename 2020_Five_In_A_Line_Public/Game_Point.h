#pragma once
#include "Game_Interface.h"
#include "Game_Algorithm.h"
#include "Game_Common.h"
class Game_Point:public Game_Common{
private:
	int posX, posY,lastPrintLen;
	bool altered;
	base_ColorID pxColorFore,pxColorBack;
	string pxContent;
	int pxEncoding;
public:
	Game_Point(int x, int y, string newInfo = "", base_ColorID newFColor = base_ColorID_White, base_ColorID newBColor = base_ColorID_Default, int newEncoding = base_Encoding_GBK);
	void point_SetPos(int x, int y);
	void point_SetForeColor(base_ColorID newColor);
	void point_SetBackColor(base_ColorID newColor);
	void point_SetContent(string content);
	void point_Print(bool forceRedraw=false);
	void point_Clear();
	base_Pair point_GetPos();
	string point_GetContent();
};

