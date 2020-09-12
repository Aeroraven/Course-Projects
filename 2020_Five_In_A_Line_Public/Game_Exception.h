#pragma once
#include "Game_BaseDefinition.h"
#include "Game_Localization.h"
#include "Game_Interface.h"
#include "Game_Input.h"
#include <exception>
#include <iostream>
using namespace std;
class Game_ExceptionBase {
public:
	virtual string what() = 0;
};

class Game_Exception{
public:
	class GameException_FileInput:public Game_ExceptionBase {
	private:
		Game_Localization* x;
	public:
		GameException_FileInput(int AreaId);
		~GameException_FileInput();
		string what();
	};

	class GameException_FileOutput :public Game_ExceptionBase {
	private:
		Game_Localization* x;
	public:
		GameException_FileOutput(int AreaId);
		~GameException_FileOutput();
		string what();
	};

	class GameException_FileBroken :public Game_ExceptionBase {
	private:
		Game_Localization* x;
	public:
		GameException_FileBroken(int AreaId);
		~GameException_FileBroken();
		string what();
	};
	class GameException_FileSignatureBroken :public Game_ExceptionBase {
	private:
		Game_Localization* x;
	public:
		GameException_FileSignatureBroken(int AreaId);
		~GameException_FileSignatureBroken();
		string what();
	};
	class GameException_FileSettingsIncompatible :public Game_ExceptionBase {
	private:
		Game_Localization* x;
	public:
		GameException_FileSettingsIncompatible(int AreaId);
		~GameException_FileSettingsIncompatible();
		string what();
	};
};

class Game_ExceptionHandle {
private:
	Game_Localization* x;
public:
	Game_ExceptionHandle(int AreaId);
	~Game_ExceptionHandle();
	int except_UserChoice(Game_ExceptionBase& exceptSource);
};
