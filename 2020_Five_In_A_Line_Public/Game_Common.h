#pragma once
#include "Game_BaseDefinition.h"
//**********************************
//	Game_Common
//	共用功能
//**********************************
class Game_Common :public Game_BaseDefinition {
public:
	int base_RandInt(int randLBound, int randUBound); //随机数
	void base_Randomize(int randSeed = (unsigned)time(NULL)); //随机种子随机化
	template<typename Var>void base_VectorShuffle(vector<Var>& destVector); //打乱向量容器
	template<typename Var>Var base_VectorRandPop(vector<Var>& destVector); //随机弹出向量容器内的元素
	template<typename Var>void base_VectorRemoveByVal(vector<Var>& destVector, Var val); //按值删除向量容器内的元素
	template<typename Any>string base_Any2String(Any convSource); //将任意可接受类型转为STLString
};

//模板函数定义

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