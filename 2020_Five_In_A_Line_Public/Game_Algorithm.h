#pragma once
#include "Game_Common.h"
//**********************************
//	Game_Algorithm
//	�����㷨�Ͳ�����������ʵ��
//**********************************
class Game_Algorithm
{
public:
	//**********************************
	//	Game_Algorithm::Base64
	//	����Base64����
	//**********************************
	class Base64 { 
	public:
		string base64_Encode(string source); 
		string base64_Decode(string source);
	};

	//**********************************
	//	Game_Algorithm::Binary
	//	�������������
	//**********************************
	class Binary {
	public:
		int bin_NumberOfOne(int x);
	};

	//**********************************
	//	Game_Algorithm::HashAlgorithms
	//	�������е�hash�㷨
	//**********************************
	class HashAlgorithms {
	public:
		unsigned int hash_crc32(string source);
	};

	//**********************************
	//	Game_Algorithm::STLExtensions
	//	ʵ�ֶ���Ķ�STL�Ĳ���
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
	//	Hash �루������Ϸ���ɣ�
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

