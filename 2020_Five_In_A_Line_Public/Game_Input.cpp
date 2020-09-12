#include "Game_Input.h"
void Game_Input::input_readInputCoord(int& acceptant, string prInf, int encodingType ) {
	int tmp,slen=0,prlen;
	Game_Algorithm::STLExtensions stlex;
	stringstream oss;
	string accStr, placeholder, pr= prInf;
	sysInf.interface_setPos(50, 37);
	cout << pr;
	acceptant = 0;
	if (encodingType == base_Encoding_GBK) {
		prlen = pr.length();
	}
	else {
		prlen = stlex.stlex_Strlen(pr, 1, 2, base_Encoding_UTF8);
	}
	while (1) {
		tmp = sysInf.interface_getch();
		if (tmp >= '0'&&tmp <= '9') {
			slen++;
			acceptant = acceptant * 10 + (int)(tmp - '0');
			sysInf.interface_colorOutput(char(tmp), base_ColorID_Green);
		}
		else {
			if (tmp == 8 || tmp==127) { //退格
				if (slen > 0) {
					slen--;
					acceptant /= 10;
					sysInf.interface_setPos(50 + slen + prlen, 37);
					sysInf.interface_colorOutput(" ", base_ColorID_Black);
					sysInf.interface_setPos(50 + slen + prlen, 37);
				}
			}
			else if (tmp == sysInf.interface_getEnterKeyVal()) {
				break;
			}
			else {
				acceptant = (int)(tmp - '0');
				break;
			}
		}
	}
	sysInf.interface_setPos(50, 37);
	
	for (int i = 0; i < slen+prlen; i++) {
		placeholder += " ";
	}
	cout << placeholder;
}
void Game_Input::input_pressKeyToContinue() {
	sysInf.interface_setPos(50, 37);
	sysInf.interface_getch();
}
void Game_Input::input_pressEnterToContinue() {
	sysInf.interface_setPos(50, 37);
	string s;
	getline(cin, s);
}
int Game_Input::input_readCh() {
	int s = sysInf.interface_getch();
	return s;
}
int Game_Input::input_enterKeyVal() {
	return sysInf.interface_getEnterKeyVal();
}
Game_Input::base_InputInfo Game_Input::input_MouseInput() {
	return sysInf.interface_getActivatedInput(true, false);
}
Game_Input::base_InputInfo Game_Input::input_CompInput() {
	return sysInf.interface_getActivatedInput(true, true);
}


//DEBUG
void Game_Input::inputDebug_inputTest() {
	while (1) {
		cout << " 我是一个粉刷匠，粉刷本领强！" << endl << endl;

		base_InputInfo inputInf = sysInf.interface_getActivatedInput(true,false);
		cout << "设备种类:" << inputInf.deviceType << endl;
		cout << "鼠标x坐标:" << inputInf.mouseInfo.x << endl;
		cout << "鼠标y坐标:" << inputInf.mouseInfo.y << endl;
		cout << "鼠标状态:" << inputInf.mouseExtInfo << endl;
		cout << "键盘按下:" << inputInf.keyDown << endl;
		cout << "键盘按键:" << inputInf.keyInfo << endl;
		sysInf.interface_sleep(300);
		sysInf.interface_clearScreen();
	}
}

