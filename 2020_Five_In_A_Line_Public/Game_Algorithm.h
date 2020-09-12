#pragma once
#include "Game_Common.h"
//**********************************
//	Game_Algorithm
//	其它算法和部分其他功能实现
//**********************************
class Game_Algorithm
{
public:
	//**********************************
	//	Game_Algorithm::Base64
	//	处理Base64编码
	//**********************************
	class Base64 { 
	public:
		string base64_Encode(string source); 
		string base64_Decode(string source);
	};

	//**********************************
	//	Game_Algorithm::Binary
	//	处理二进制运算
	//**********************************
	class Binary {
	public:
		int bin_NumberOfOne(int x);
	};

	//**********************************
	//	Game_Algorithm::HashAlgorithms
	//	处理已有的hash算法
	//**********************************
	class HashAlgorithms {
	public:
		unsigned int hash_crc32(string source);
	};

	//**********************************
	//	Game_Algorithm::STLExtensions
	//	实现额外的对STL的操作
	//**********************************
	class STLExtensions {
	public:
		const static int STLEX_STRLEN_UTF8 = 1;
		const static int STLEX_STRLEN_GBK = 2;
		void stlex_StringSplit(string source, string delimiter, vector<string>& place);
		int stlex_Strlen(string source,int asciiWeight=1, int nonAsciiWeight = 1, int encoding = 1);
	};

	//**********************************
	//	Game_Algorithm::HashCode
	//	Hash 码（用于游戏生成）
	//**********************************
	class HashCode {
		int seed;
		int mod1 = 1000000007;
	public:
		void hash_SetSeed(int val);
		int hash_GetSeed();
		int hash_GetCode(int x);
		int hash_GetRangedCode(int x, int lb, int ub);
	};
};

