#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>
#include <sstream>
#include <regex>
#include <map>
#include <unordered_map>
#include <ctime>
#include <vector>
#include <stack>
#include <exception>
#include <fstream>
#include <queue>
#ifdef _WIN32
#include <windows.h> //在Windows下
#include <conio.h>
#else
#include <unistd.h> //在Linux下
#include <termio.h>
#include <fcntl.h>
#endif

//内存泄漏检测
#ifdef _WIN32
#ifdef _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define _CHECK_MEMORY_LEAKS() _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)|_CRTDBG_LEAK_CHECK_DF);
#else
#define _CHECK_MEMORY_LEAKS() ;
#endif
#else
#define _CHECK_MEMORY_LEAKS() ;
#endif
//内存泄漏检测结束
using namespace std;

//**********************************
//	Game_BaseDefinition
//	游戏基础定义模块
//**********************************
class Game_BaseDefinition {
public:
	struct Game_Base_Author {
		string authorName;
		string authorStudentIdentity;
	};
public:
	//数对
	struct base_Pair {
		int x, y;
		bool operator == (const struct base_Pair& a) {return (x == a.x&&y == a.y);}
		//小于重载，仅用于STL容器
		bool operator <(const struct base_Pair& a) const {return (x < a.x&&y < a.y);} 
	};
	//设备输入信息
	struct base_InputInfo {
		int deviceType;			//输入设备类型：鼠标为1，键盘为2，其他为3
		base_Pair mouseInfo;	//鼠标输入坐标
		int mouseExtInfo;		//鼠标输入事件类型
		int mouseExtInfo2;		//鼠标按键类型
		int keyInfo;			//键盘按键虚拟键值
		bool keyDown;			//键盘按下状态
	};
	//编译操作系统
#ifdef _WIN32
	const static int base_CompileOS = 1;	//Windows操作系统
#else
	const static int base_CompileOS = 2;	//非Windows操作系统
#endif


	//自定义颜色常量
	enum base_ColorID {
		base_ColorID_Default = 0,	//颜色默认值
		base_ColorID_Black = 1,		//黑色
		base_ColorID_Red = 2,		//红色
		base_ColorID_Green = 3,		//绿色
		base_ColorID_Yellow = 4,	//黄色
		base_ColorID_Blue = 5,		//蓝色
		base_ColorID_Magenta = 6,	//紫色/洋红
		base_ColorID_Cyan = 7,		//青色
		base_ColorID_White = 8,		//白色
		base_ColorID_Gray=9			//灰色（Windows控制台高亮）
	};

	//自定义编码方式
	enum base_Encoding {
		base_Encoding_UTF8=1,	//UTF8编码方式
		base_Encoding_GBK=2,	//GBK或GB18030编码方式
	};

	const static string base_GameName;	//游戏名称常量
	const static Game_Base_Author base_GameAuthor; //游戏作者1950641

	//默认游戏规则常量（仅作默认值）
	const static base_ColorID base_DefaultBeadColors[13]; //棋子默认颜色
	const static int base_DefaultBoardWidth = 9; //棋盘默认宽度，默认为9
	const static int base_DefaultBoardHeight = 9; //棋盘默认高度，默认为9
	const static int base_DefaultBoardMarginLeft = 60; //棋盘左边距
	const static int base_DefaultBoardMarginTop = 5; //棋盘上边距

	const static int base_DefaultBeadTypes = 7; //默认棋子种类数，默认为7
	const static int base_DefaultStartBeads = 7; //默认开局棋子数，默认为7
	const static int base_DefaultBeadsRegen = 3; //默认新增棋子数，默认为3
	const static int base_DefaultBeadChain = 5; //默认消除最少需要同向的棋子数，默认为5
	const static int base_DefaultBasicScore = 10; //默认消除获得的分数基数，默认为10
	const static int base_DefaultAddedScore = 2; //默认消除获得的额外分数增长，默认为2
	const static int base_DefaultAreaId = 2; //默认语言区域设置，防止乱码设置为1-2

	//填充符(等效全角空格)
	const static string base_WCharSpace;

	//方向键键值（非系统的getch！）
#ifdef _WIN32
	const static int base_GetchVal_Left = 299;	//自定义Getch返回的左方向键键值
	const static int base_GetchVal_Up = 296;	//自定义Getch返回的上方向键键值
	const static int base_GetchVal_Down = 304;	 //自定义Getch返回的下方向键键值
	const static int base_GetchVal_Right = 301;	 //自定义Getch返回的右方向键键值
#else
	const static int base_GetchVal_Left = 1068;
	const static int base_GetchVal_Up = 1065;
	const static int base_GetchVal_Down = 1066;
	const static int base_GetchVal_Right = 1067;
#endif


};


