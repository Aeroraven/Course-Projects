#pragma once
#include "Game_BaseDefinition.h"
//**********************************
//	Game_Common
//	���ù���
//**********************************
class Game_Common :public Game_BaseDefinition {
public:
	int base_RandInt(int randLBound, int randUBound); //�����
	void base_Randomize(int randSeed = (unsigned)time(NULL)); //������������
	template<typename Var>void base_VectorShuffle(vector<Var>& destVector); //������������
	template<typename Var>Var base_VectorRandPop(vector<Var>& destVector); //����������������ڵ�Ԫ��
	template<typename Var>void base_VectorRemoveByVal(vector<Var>& destVector, Var val); //��ֵɾ�����������ڵ�Ԫ��
	template<typename Any>string base_Any2String(Any convSource); //������ɽ�������תΪSTLString
};

//ģ�庯������

template<typename Var>void Game_Common::base_VectorShuffle(vector<Var>& destVector) {
	random_shuffle(destVector.begin(), destVector.end());
}
template<typename Var>Var Game_Common::base_VectorRandPop(vector<Var>& destVector) {
	int cur = base_RandInt(0, destVector.size() - 1);
	Var ret = destVector[cur];
	destVector.erase(destVector.begin() + cur);
	return ret;
}
template<typename Var>void Game_Common::base_VectorRemoveByVal(vector<Var>& destVector, Var val) {
	destVector.erase(remove(destVector.begin(), destVector.end(), val), destVector.end());
}
template<typename Any>string Game_Common::base_Any2String(Any convSource) {
	ostringstream oss;
	oss << convSource;
	return oss.str();
}