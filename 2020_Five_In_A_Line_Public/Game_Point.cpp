#include "Game_Point.h"
Game_Point::Game_Point(int x, int y, string newInfo /* = "" */, base_ColorID newFColor /* = base_ColorID_Black */, base_ColorID newBColor/* = base_ColorID_White */, int newEncoding) {
	posX = x;
	posY = y;
	pxContent = newInfo;
	pxColorFore = newFColor;
	pxColorBack = newBColor;
	pxEncoding = newEncoding;
	lastPrintLen = 0;
	altered = true;
}
void Game_Point::point_SetPos(int x, int y) {
	posX = x;
	posY = y;
	altered = true;
}
void Game_Point::point_SetForeColor(base_ColorID newColor) {
	pxColorFore = newColor;
	altered = true;
}
void Game_Point::point_SetBackColor(base_ColorID newColor) {
	pxColorBack = newColor;
	altered = true;
}
void Game_Point::point_SetContent(string content) {
	pxContent = content;
	altered = true;
}
void Game_Point::point_Print(bool forceRedraw) {
	if (altered == false&&forceRedraw==false)return;
	Game_Interface sysInf;
	Game_Algorithm::STLExtensions stlex;
	int curLen;
	if (pxEncoding == base_Encoding_UTF8) {
		curLen = stlex.stlex_Strlen(pxContent, 1, 2, base_Encoding_UTF8);
	}
	else {
		curLen = pxContent.length();
	}
	
	sysInf.interface_setPos(posX, posY);
	string spaceholder = "";
	if (lastPrintLen > curLen) {
		for (int i = 0; i < lastPrintLen - curLen; i++) {
			spaceholder += " ";
		}
	}
	sysInf.interface_colorOutput(pxContent, pxColorFore, pxColorBack);
	sysInf.interface_colorOutput(spaceholder, pxColorFore, pxColorBack);
	lastPrintLen = curLen;
	altered = false;
}
void Game_Point::point_Clear() {
	Game_Interface sysInf;
	sysInf.interface_setPos(posX, posY);
	string spaceholder = "";
	for (int i = 0; i < lastPrintLen; i++) {
		spaceholder += " ";
	}
	cout << " ";
	lastPrintLen = 0;
	altered = true;
}
Game_Point::base_Pair Game_Point::point_GetPos() {
	return { posX,posY };
}
string Game_Point::point_GetContent() {
	return pxContent;
}
