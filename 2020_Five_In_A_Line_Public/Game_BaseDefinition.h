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
#include <windows.h> //��Windows��
#include <conio.h>
#else
#include <unistd.h> //��Linux��
#include <termio.h>
#include <fcntl.h>
#endif

//�ڴ�й©���
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
//�ڴ�й©������
using namespace std;

//**********************************
//	Game_BaseDefinition
//	��Ϸ��������ģ��
//**********************************
class Game_BaseDefinition {
public:
	struct Game_Base_Author {
		string authorName;
		string authorStudentIdentity;
	};
public:
	//����
	struct base_Pair {
		int x, y;
		bool operator == (const struct base_Pair& a) {return (x == a.x&&y == a.y);}
		//С�����أ�������STL����
		bool operator <(const struct base_Pair& a) const {return (x < a.x&&y < a.y);} 
	};
	//�豸������Ϣ
	struct base_InputInfo {
		int deviceType;			//�����豸���ͣ����Ϊ1������Ϊ2������Ϊ3
		base_Pair mouseInfo;	//�����������
		int mouseExtInfo;		//��������¼�����
		int mouseExtInfo2;		//��갴������
		int keyInfo;			//���̰��������ֵ
		bool keyDown;			//���̰���״̬
	};
	//�������ϵͳ
#ifdef _WIN32
	const static int base_CompileOS = 1;	//Windows����ϵͳ
#else
	const static int base_CompileOS = 2;	//��Windows����ϵͳ
#endif


	//�Զ�����ɫ����
	enum base_ColorID {
		base_ColorID_Default = 0,	//��ɫĬ��ֵ
		base_ColorID_Black = 1,		//��ɫ
		base_ColorID_Red = 2,		//��ɫ
		base_ColorID_Green = 3,		//��ɫ
		base_ColorID_Yellow = 4,	//��ɫ
		base_ColorID_Blue = 5,		//��ɫ
		base_ColorID_Magenta = 6,	//��ɫ/���
		base_ColorID_Cyan = 7,		//��ɫ
		base_ColorID_White = 8,		//��ɫ
		base_ColorID_Gray=9			//��ɫ��Windows����̨������
	};

	//�Զ�����뷽ʽ
	enum base_Encoding {
		base_Encoding_UTF8=1,	//UTF8���뷽ʽ
		base_Encoding_GBK=2,	//GBK��GB18030���뷽ʽ
	};

	const static string base_GameName;	//��Ϸ���Ƴ���
	const static Game_Base_Author base_GameAuthor; //��Ϸ����1950641

	//Ĭ����Ϸ������������Ĭ��ֵ��
	const static base_ColorID base_DefaultBeadColors[13]; //����Ĭ����ɫ
	const static int base_DefaultBoardWidth = 9; //����Ĭ�Ͽ�ȣ�Ĭ��Ϊ9
	const static int base_DefaultBoardHeight = 9; //����Ĭ�ϸ߶ȣ�Ĭ��Ϊ9
	const static int base_DefaultBoardMarginLeft = 60; //������߾�
	const static int base_DefaultBoardMarginTop = 5; //�����ϱ߾�

	const static int base_DefaultBeadTypes = 7; //Ĭ��������������Ĭ��Ϊ7
	const static int base_DefaultStartBeads = 7; //Ĭ�Ͽ�����������Ĭ��Ϊ7
	const static int base_DefaultBeadsRegen = 3; //Ĭ��������������Ĭ��Ϊ3
	const static int base_DefaultBeadChain = 5; //Ĭ������������Ҫͬ�����������Ĭ��Ϊ5
	const static int base_DefaultBasicScore = 10; //Ĭ��������õķ���������Ĭ��Ϊ10
	const static int base_DefaultAddedScore = 2; //Ĭ��������õĶ������������Ĭ��Ϊ2
	const static int base_DefaultAreaId = 2; //Ĭ�������������ã���ֹ��������Ϊ1-2

	//����(��Чȫ�ǿո�)
	const static string base_WCharSpace;

	//�������ֵ����ϵͳ��getch����
#ifdef _WIN32
	const static int base_GetchVal_Left = 299;	//�Զ���Getch���ص��������ֵ
	const static int base_GetchVal_Up = 296;	//�Զ���Getch���ص��Ϸ������ֵ
	const static int base_GetchVal_Down = 304;	 //�Զ���Getch���ص��·������ֵ
	const static int base_GetchVal_Right = 301;	 //�Զ���Getch���ص��ҷ������ֵ
#else
	const static int base_GetchVal_Left = 1068;
	const static int base_GetchVal_Up = 1065;
	const static int base_GetchVal_Down = 1066;
	const static int base_GetchVal_Right = 1067;
#endif


};


