#pragma once
#include "Game_Common.h"
//**********************************
//	Game_Board
//	������Ϣ�洢 & ���̻�������
//**********************************
class Game_Board :public Game_Common{
private:
	unordered_map<int, string> board_BeadDisplayMap;	//����ID������ͼ�ε�ӳ��
	unordered_map<int, base_ColorID> board_BeadColorMap;	//����ID��������ɫ��ӳ��
	vector<base_Pair> board_EmptyTiles;	//�������̸�����
	int board_Width, board_Height;	//���̱߳�
	int board_BeadTypes;	//����֧�ֵ�����������
	int** board_Table;	//��������
	bool** board_TableAvailable;	//��������ÿ��״̬
	bool board_IsInitialized;	//���̶����ʼ��״̬
	int board_Occupied;	//����ȫ��״̬
public:
	
	~Game_Board(); //��������
	Game_Board(int heightValue = base_DefaultBoardHeight, int widthValue = base_DefaultBoardWidth, string* mappingChars = nullptr, base_ColorID* mappingColors = (base_ColorID*)base_DefaultBeadColors, int typeCounts = base_DefaultBeadTypes);
	Game_Board(const Game_Board& cpSource);
	void board_Init(int heightValue = base_DefaultBoardHeight, int widthValue = base_DefaultBoardWidth, string* mappingChars = nullptr , base_ColorID* mappingColors = (base_ColorID*)base_DefaultBeadColors, int typeCounts = base_DefaultBeadTypes);
	void board_Unload();

	void board_Construct();	//��������
	void board_SetHeight(int heightValue = base_DefaultBoardHeight); //�趨�߶�
	void board_SetWidth(int widthValue = base_DefaultBoardWidth); //�趨���
	void board_Demolish(); //�ݻ�����
	void board_SetBeadMapping(string* mappingChars , base_ColorID* mappingColors = (base_ColorID*)base_DefaultBeadColors, int typeCounts = base_DefaultBeadTypes); //�趨ͼ����ʽ
	void board_SetElement(int x, int y, int beadTypeId); //��������
	void board_RemoveElement(int x, int y); //�Ƴ�����

	string board_GetBeadMappingChars(int beadTypeId); //��ȡID��Ӧ�������ַ�
	base_ColorID board_GetBeadMappingColors(int beadTypeId); //��ȡID��Ӧ��������ɫ
	int board_GetHeight(); //������̸߶�
	int board_GetWidth(); //������̿��
	int board_GetElement(int x, int y); //��ö�Ӧ����ϵ�����
	int board_GetOccupied(); //�������ռ��״̬
	int board_GetEmpty(); //������̿���״̬
	int board_GetTypes(); //�������֧�ֵ�����������
	bool board_GetEmptyStat(int x, int y); //���һ�����ӵĿ���״̬
	int board_GetSize(); //������̹��
	base_Pair board_GetEmptyByIterator(int lb); //�����±��ÿ��������ڵĸ��
	int board_GetVID(int x, int y); //������ת��Ϊһά���
	base_Pair board_GetPID(int vid); //��һά���ת��Ϊ����
	void board_Reset(); //������ӷ�����Ϣ�����¼�������
};

