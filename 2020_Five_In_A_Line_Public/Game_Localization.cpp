#include "Game_Localization.h"
//地区设置
string Game_Localization::lang_GetString(lang_ExprIndex stringIdx, bool useSetArea, int langArea) {
	int areaSetting = useSetArea ? defaultArea : langArea;
	return dictionary[areaSetting][stringIdx];
}
void Game_Localization::lang_Init(int areaId) {
	defaultArea = areaId;
	switch (areaId) {
	case 1:
		defaultCode = ENCODING_GBK;
		langPre_SetEnglish_b64_gbk();
		break;
	case 2:
		defaultCode = ENCODING_UTF8;
		langPre_SetEnglish_b64_utf8();
		break;
	case 3:
		defaultCode = ENCODING_GBK;
		langPre_SetChineseS_b64_gbk();
		break;
	case 4:
		defaultCode = ENCODING_UTF8;
		langPre_SetChineseS_b64_utf8();
		break;
	default:
		break;
	}
}
int Game_Localization::lang_GetDefaultArea() {
	return defaultArea;
}
int Game_Localization::lang_GetDefaultCode() {
	return defaultCode;
}
Game_Localization::Game_Localization(int areaId) { lang_Init(areaId); }

//赋值重载
Game_Localization Game_Localization::operator=(const Game_Localization& x) {
	Game_Localization ret;
	ret.lang_Init(((Game_Localization)x).lang_GetDefaultArea());
	return ret;
}

//字符串常量设置
void Game_Localization::langPre_SetSymbol_b64_gbk(int x) {
	dictionary[x][SYMBOL_PRESET_SHARP] = "#";
	dictionary[x][SYMBOL_PRESET_ZERO] = "O";
	dictionary[x][SYMBOL_PRESET_AT] = "@";
	dictionary[x][SYMBOL_PRESET_ADD] = "+";
	dictionary[x][SYMBOL_PRESET_CROSS] = "X";
	dictionary[x][SYMBOL_PRESET_PERCENT] = "%";
	dictionary[x][SYMBOL_PRESET_DOLLAR] = "$";

	dictionary[x][SYMBOL_PRESET_RECT] = b64.base64_Decode("ofY=");
	dictionary[x][SYMBOL_PRESET_TRIANGLE] = b64.base64_Decode("ofg=");
	dictionary[x][SYMBOL_PRESET_CIRCLE] = b64.base64_Decode("qZY=");
	dictionary[x][SYMBOL_PRESET_DIAMOND] = b64.base64_Decode("ofQ=");
	dictionary[x][SYMBOL_PRESET_FILLED_STAR] = b64.base64_Decode("oe8=");
	dictionary[x][SYMBOL_PRESET_HOLLOW_STAR] = b64.base64_Decode("oe4=");
	dictionary[x][SYMBOL_PRESET_CROSS_WITH_DOT] = b64.base64_Decode("ofk=");

	dictionary[x][SYMBOL_TABLE_LTCORNER] = b64.base64_Decode("qbAg");
	dictionary[x][SYMBOL_TABLE_RTCORNER] = b64.base64_Decode("qbQg");
	dictionary[x][SYMBOL_TABLE_LBCORNER] = b64.base64_Decode("qbgg");
	dictionary[x][SYMBOL_TABLE_RBCORNER] = b64.base64_Decode("qbwg");
	dictionary[x][SYMBOL_TABLE_CROSS] = b64.base64_Decode("qeAg");
	dictionary[x][SYMBOL_TABLE_LBRANCH] = b64.base64_Decode("qcAg");
	dictionary[x][SYMBOL_TABLE_RBRANCH] = b64.base64_Decode("qcgg");
	dictionary[x][SYMBOL_TABLE_TBRANCH] = b64.base64_Decode("qdAg");
	dictionary[x][SYMBOL_TABLE_BBRANCH] = b64.base64_Decode("qdgg");
	dictionary[x][SYMBOL_TABLE_HORZLINE] = b64.base64_Decode("qaQg");
	dictionary[x][SYMBOL_TABLE_VERTLINE] = b64.base64_Decode("qaYg");

	dictionary[x][SYMBOL_FWNUMBER_0] = b64.base64_Decode("o7A=");
	dictionary[x][SYMBOL_FWNUMBER_1] = b64.base64_Decode("o7E=");
	dictionary[x][SYMBOL_FWNUMBER_2] = b64.base64_Decode("o7I=");
	dictionary[x][SYMBOL_FWNUMBER_3] = b64.base64_Decode("o7M=");
	dictionary[x][SYMBOL_FWNUMBER_4] = b64.base64_Decode("o7Q=");
	dictionary[x][SYMBOL_FWNUMBER_5] = b64.base64_Decode("o7U=");
	dictionary[x][SYMBOL_FWNUMBER_6] = b64.base64_Decode("o7Y=");
	dictionary[x][SYMBOL_FWNUMBER_7] = b64.base64_Decode("o7c=");
	dictionary[x][SYMBOL_FWNUMBER_8] = b64.base64_Decode("o7g=");
	dictionary[x][SYMBOL_FWNUMBER_9] = b64.base64_Decode("o7k=");

	dictionary[x][SYMBOL_SQUARE_1] = b64.base64_Decode("qIE=");
	dictionary[x][SYMBOL_SQUARE_2] = b64.base64_Decode("qH4=");
	dictionary[x][SYMBOL_FWEXT_QUESTIONMARK] = b64.base64_Decode("o78=");
}


void Game_Localization::langPre_SetSymbol_b64_utf8(int x) {
	dictionary[x][SYMBOL_PRESET_SHARP] = "#";
	dictionary[x][SYMBOL_PRESET_ZERO] = "O";
	dictionary[x][SYMBOL_PRESET_AT] = "@";
	dictionary[x][SYMBOL_PRESET_ADD] = "+";
	dictionary[x][SYMBOL_PRESET_CROSS] = "X";
	dictionary[x][SYMBOL_PRESET_PERCENT] = "%";
	dictionary[x][SYMBOL_PRESET_DOLLAR] = "$";

	dictionary[x][SYMBOL_PRESET_RECT] = b64.base64_Decode("4pag");
	dictionary[x][SYMBOL_PRESET_TRIANGLE] = b64.base64_Decode("4pay");
	dictionary[x][SYMBOL_PRESET_CIRCLE] = b64.base64_Decode("44CH");
	dictionary[x][SYMBOL_PRESET_DIAMOND] = b64.base64_Decode("4peG");
	dictionary[x][SYMBOL_PRESET_FILLED_STAR] = b64.base64_Decode("4piF");
	dictionary[x][SYMBOL_PRESET_HOLLOW_STAR] = b64.base64_Decode("4piG");
	dictionary[x][SYMBOL_PRESET_CROSS_WITH_DOT] = b64.base64_Decode("4oC7");

	dictionary[x][SYMBOL_TABLE_LTCORNER] = b64.base64_Decode("4pSMIA==");
	dictionary[x][SYMBOL_TABLE_RTCORNER] = b64.base64_Decode("4pSQIA==");
	dictionary[x][SYMBOL_TABLE_LBCORNER] = b64.base64_Decode("4pSUIA==");
	dictionary[x][SYMBOL_TABLE_RBCORNER] = b64.base64_Decode("4pSYIA==");
	dictionary[x][SYMBOL_TABLE_CROSS] = b64.base64_Decode("4pS8IA==");
	dictionary[x][SYMBOL_TABLE_LBRANCH] = b64.base64_Decode("4pScIA==");
	dictionary[x][SYMBOL_TABLE_RBRANCH] = b64.base64_Decode("4pSkIA==");
	dictionary[x][SYMBOL_TABLE_TBRANCH] = b64.base64_Decode("4pSsIA==");
	dictionary[x][SYMBOL_TABLE_BBRANCH] = b64.base64_Decode("4pS0IA==");
	dictionary[x][SYMBOL_TABLE_HORZLINE] = b64.base64_Decode("4pSAIA==");
	dictionary[x][SYMBOL_TABLE_VERTLINE] = b64.base64_Decode("4pSCIA==");

	dictionary[x][SYMBOL_FWNUMBER_0] = b64.base64_Decode("77yQ");
	dictionary[x][SYMBOL_FWNUMBER_1] = b64.base64_Decode("77yR");
	dictionary[x][SYMBOL_FWNUMBER_2] = b64.base64_Decode("77yS");
	dictionary[x][SYMBOL_FWNUMBER_3] = b64.base64_Decode("77yT");
	dictionary[x][SYMBOL_FWNUMBER_4] = b64.base64_Decode("77yU");
	dictionary[x][SYMBOL_FWNUMBER_5] = b64.base64_Decode("77yV");
	dictionary[x][SYMBOL_FWNUMBER_6] = b64.base64_Decode("77yW");
	dictionary[x][SYMBOL_FWNUMBER_7] = b64.base64_Decode("77yX");
	dictionary[x][SYMBOL_FWNUMBER_8] = b64.base64_Decode("77yY");
	dictionary[x][SYMBOL_FWNUMBER_9] = b64.base64_Decode("77yZ");

	dictionary[x][SYMBOL_SQUARE_1] = b64.base64_Decode("4paJ");
	dictionary[x][SYMBOL_SQUARE_2] = b64.base64_Decode("4paH");
	dictionary[x][SYMBOL_FWEXT_QUESTIONMARK] = b64.base64_Decode("77yf");
}
void Game_Localization::langPre_SetEnglish_b64_gbk() {
	langPre_SetEnglish_common(1);
	langPre_SetSymbol_b64_gbk(1);
}
void Game_Localization::langPre_SetEnglish_b64_utf8() {
	langPre_SetEnglish_common(2);
	langPre_SetSymbol_b64_utf8(2);
}


void Game_Localization::langPre_SetEnglish_common(int x) {
	dictionary[x][TEXT_GUIDE_INPUT_PLACECOORD] = "Enter the coordinate of the bead awaiting move";
	dictionary[x][TEXT_GUIDE_INPUT_MOVECOORD] = "Enter the coordinate that you want to place the bead:";
	dictionary[x][TEXT_GUIDE_INPUT_PLAYERNAME] = "Input player's name ：";
	dictionary[x][TEXT_GUIDE_INPUT_PLAYERORDER] = "Input player's order ：";
	dictionary[x][TEXT_GUIDE_INPUT_SOURCECOORD_X] = "<Key>Enter the row coordinate of the bead awaiting move";
	dictionary[x][TEXT_GUIDE_INPUT_SOURCECOORD_Y] = "<Key>Enter the column coordinates of the bead awaiting move";
	dictionary[x][TEXT_GUIDE_INPUT_DESTCOORD_X] = "<Key>Enter the destination's row coordinate ";
	dictionary[x][TEXT_GUIDE_INPUT_DESTCOORD_Y] = "<Key>Enter the destination's column coordinate";
	dictionary[x][TEXT_GUIDE_INPUT_CLICK_SOURCECOORD] = "<Mouse>Click the bead you want to move";
	dictionary[x][TEXT_GUIDE_INPUT_CLICK_DESTCOORD] = "<Mouse>Click the place you want to place the bead";
	dictionary[x][TEXT_GUIDE_INPUT_COORD] = "Input [Press Enter to submit]:";

	dictionary[x][TEXT_LABEL_SCORES] = "< Scores Gained >";
	dictionary[x][TEXT_LABEL_REMOVE_CNT] = "Counts of removed beads:";
	dictionary[x][TEXT_LABEL_REMOVE_SCORE] = "Scores gained:";
	dictionary[x][TEXT_LABEL_CURRENT_PLAYER] = "< Current Player >";
	dictionary[x][TEXT_LABEL_CURRENT_PLAYER_PLACEHOLDER] = "          ";
	dictionary[x][TEXT_LABEL_FINAL_SCORE] = "Final Score:";
	dictionary[x][TEXT_LABEL_REMOVE_TOTALSCORE] = "After the move, you gained scores:";
	dictionary[x][TEXT_LABEL_TOTALMOVES] = "< Total Moves >";
	dictionary[x][TEXT_LABEL_FORESEE] = "< Coming-soon Beads >";
	dictionary[x][TEXT_LABEL_AUTHOR_NAME] = "Author's Name:";
	dictionary[x][TEXT_LABEL_AUTHOR_STUID] = "Author's Student Identity:";
	dictionary[x][TEXT_LABEL_RESET_INPUT] = "Press [P] to reset the inputted info.";
	dictionary[x][TEXT_LABEL_SOURCE_CELL] = "[Source Cell]";
	dictionary[x][TEXT_LABEL_SYSTEM_REMOVAL] = " Automatic removal, you gain no scores.";


	dictionary[x][TEXT_INFO_INVALID_MOVE_UNCONNECTED] = "[Route Blocked]";
	dictionary[x][TEXT_INFO_INVALID_MOVE_OCCUPIED] = "[Destination Blocked]";
	dictionary[x][TEXT_INFO_INVALID_MOVE_EMPTY] = "[Empty Starting Cell]";
	dictionary[x][TEXT_INFO_INVALID_MOVE_HEADER] = "Invalid Move ";

	dictionary[x][TEXT_INFO_COMPLETE_OCCPUIED] = "Game over! All cells are occupied";
	dictionary[x][TEXT_INFO_NEWBEADS_PLACED] = "New beads have already been placed";
	dictionary[x][TEXT_INFO_MOVE_SUCCESS] = "The bead have already been successfully moved!";
	dictionary[x][TEXT_INFO_PRESS_ANY_KEY_TO_CONTINUE] = "Press Any Key To Continue......";
	dictionary[x][TEXT_INFO_PRESS_ENTER_TO_CONTINUE] = "Press Enter To Continue......";
	dictionary[x][TEXT_INFO_INVALID_COORD] = "The coordinate inputted is invalid.";
	dictionary[x][TEXT_INFO_MOVE_WITHOUT_REMOVAL] = "No beads are removed!";
	dictionary[x][TEXT_INFO_GAIN_ANOTHER_CHANCE] = "You have an extra move.";
	dictionary[x][TEXT_INFO_GAME_RESTARTED] = "Game has already been restarted!";
	dictionary[x][TEXT_INFO_INVALID_INPUT] = "Please enter proper keys or click within proper area.";
	dictionary[x][TEXT_INFO_RESTARTING_CONFIRM] = "Do you want to restart the game?";
	dictionary[x][TEXT_INFO_CHEAT_DETECTED] = "We detected cheat operations. Please close the application!";
	dictionary[x][TEXT_INFO_EXIT_CONFIRM] = "Do you want to quit the game?";
	dictionary[x][TEXT_INFO_MOUSE_UNSUPPORTED] = "Mouse input is unsupported on this OS";
	dictionary[x][TEXT_INFO_KEYBOARD_UNSUPPORTED] = "Keyboard input is unsupported on this OS";
	dictionary[x][TEXT_INFO_MOVELIMIT_CONFIRM] = "Enable the rule that the starting cell and ";
	dictionary[x][TEXT_INFO_MOVELIMIT_CONFIRM_2] = "the destination cell should be connected by empty cells?";
	dictionary[x][TEXT_INFO_MOVELIMIT_DISABLED] = "The move limit has been removed";
	dictionary[x][TEXT_INFO_MOVELIMIT_ENABLED] = "The move limit has been placed.";
	dictionary[x][TEXT_INFO_INPUTDEVICE_SWITCH_CONFIRM] = "Switch the input method used to move beads";
	dictionary[x][TEXT_INFO_COMING_SOON] = "This function is currently unavailable";
	dictionary[x][TEXT_INFO_FORESEE_CONFIRM] = "Do you want to prefigure beads that will be generated next round?";
	dictionary[x][TEXT_INFO_GAME_STARTED] = "Game start!";

	dictionary[x][TEXT_INFO_LANG_SWITCH_A] = "Do you want to change the language or the encoding method?";
	dictionary[x][TEXT_INFO_LANG_SWITCH_B] = "After the change, your game will be reinitialized and restarted.";

	dictionary[x][TEXT_INFO_MAINTITLE_OPTION_SWITCH] = "Use [Arrow Keys+Enter] or [E/L/S Keys] to switch options";
	dictionary[x][TEXT_INFO_DO_NOT_DISTRIBUTE] = "by Hzw. A project for lesson 'Principles of Programming Languages'.";
	dictionary[x][TEXT_INFO_OS_NOT_SUPPORTED] = "This function is currently unavailable on your operating system.";
	dictionary[x][TEXT_INFO_SHOWROUTE_CONFIRM] = "Do you want to display the route animation of any move?";
	dictionary[x][TEXT_INFO_NOT_INPUTTED] = "Not Inputted";
	dictionary[x][TEXT_INFO_INPUT_RESET] = "Inputted information has been reset!";
	dictionary[x][TEXT_INFO_GAME_SAVED] = "Your progress has already been saved!";
	dictionary[x][TEXT_INFO_GAME_LOADED] = "Your progress has already been loaded!";
	dictionary[x][TEXT_INFO_NO_AVAILABLE_MOVES] = "No Available Moves! The turn ends.";

	dictionary[x][TEXT_LABEL_ALERTTITLE_COMMON] = "Information";
	dictionary[x][TEXT_LABEL_ALERTTITLE_RESTART] = "Restart";
	dictionary[x][TEXT_LABEL_ALERTTITLE_HELP] = "How to play?";
	dictionary[x][TEXT_LABEL_ALERTTITLE_EXIT] = "Exit";
	dictionary[x][TEXT_LABEL_ALERTTITLE_ANTICHEAT] = "Cheat Detection";
	dictionary[x][TEXT_LABEL_ALERTTITLE_SETTINGS] = "Game Settings";
	dictionary[x][TEXT_LABEL_ALERTTITLE_SETTINGS_INPUTDEVICE] = "Game Settings / Input Device";
	dictionary[x][TEXT_LABEL_ALERTTITLE_SETTINGS_LANG] = "Game Settings / Language";
	dictionary[x][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_FORESEE] = "Game Settings / Game Rule - Foreknowledge";
	dictionary[x][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_MOVELIMIT] = "Game Settings / Game Rule - Move Restriction";
	dictionary[x][TEXT_LABEL_ALERTTITLE_CREDIT] = "Author's Information";
	dictionary[x][TEXT_LABEL_ALERTTITLE_LANGUAGE] = "Language Settings";
	dictionary[x][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_SHOWROUTE] = "Game Settings / Game Rule - Route Animation";


	dictionary[x][TEXT_OPTION_RESTART] = "< Restart  > (Key R)";
	dictionary[x][TEXT_OPTION_EXIT] = "< Exit     > (Key E)";
	dictionary[x][TEXT_OPTION_WITHDRAW] = "< Retrace > (Key B)";
	dictionary[x][TEXT_OPTION_SETTING] = "< Settings > (Key C)";
	dictionary[x][TEXT_OPTION_ABORT] = "< Abandon > (Key Q)";
	dictionary[x][TEXT_OPTION_CREDIT] = "< Author   > (Key A)";
	dictionary[x][TEXT_OPTION_HELP] = "< Help     > (Key H)";
	dictionary[x][TEXT_OPTION_YES] = "< Yes > (Y)";
	dictionary[x][TEXT_OPTION_NO] = "< No > (N)";
	dictionary[x][TEXT_OPTION_CLOSE] = "< Close > (C)";
	dictionary[x][TEXT_OPTION_TITLESCENE] = "< Main Title > (T)";
	dictionary[x][TEXT_OPTION_EXIT2] = "< Exit > (E)";
	dictionary[x][TEXT_OPTION_CANCEL] = "< Cancel > (C)";
	dictionary[x][TEXT_OPTION_ON] = "< Enable > (S)";
	dictionary[x][TEXT_OPTION_OFF] = "< Disable > (T)";
	dictionary[x][TEXT_OPTION_KNOWN] = "< I Know > (Y)";
	dictionary[x][TEXT_OPTION_SAVE] = "< Save     > (Key S)";

	dictionary[x][TEXT_OPTION_MAINTITLE_STARTGAME] = "[ GAME START ](S)";
	dictionary[x][TEXT_OPTION_MAINTITLE_AUTHOR] = "[ AUTHOR ](A)";
	dictionary[x][TEXT_OPTION_MAINTITLE_EXIT] = "[ EXIT ](E)";
	dictionary[x][TEXT_OPTION_MAINTITLE_LOAD] = "[ LOAD ](L)";

	dictionary[x][TEXT_OPTION_OPERATION_DEVICE] = "< Switch Input Method > (D)";
	dictionary[x][TEXT_OPTION_OPERATION_DEVICE_KEYBOARD] = "< Keyboard Only > (K)";
	dictionary[x][TEXT_OPTION_OPERATION_DEVICE_MOUSE] = "< Allow Mouse > (M)";
	dictionary[x][TEXT_OPTION_LANGUAGE] = "< Language > (L)";
	dictionary[x][TEXT_OPTION_LANGUAGE_ZHCN] = "< Chinese >";
	dictionary[x][TEXT_OPTION_LANGUAGE_ENUS] = "< English >";
	dictionary[x][TEXT_OPTION_LANGUAGE_ENUS_GBK] = "< English (GBK) >";
	dictionary[x][TEXT_OPTION_LANGUAGE_ENUS_UTF8] = "< English (UTF8) >";
	dictionary[x][TEXT_OPTION_LANGUAGE_ZHCN_GBK] = "< Simplified Chinese (GBK) >";
	dictionary[x][TEXT_OPTION_LANGUAGE_ZHCN_UTF8] = "< Simplified Chinese (UTF8) >";

	dictionary[x][TEXT_OPTION_GAMERULE_FORESEE] = "< Prefigure Beads > (F)";
	dictionary[x][TEXT_OPTION_GAMERULE_MOVE_LIMIT] = "< Move Restriction > (M)";
	dictionary[x][TEXT_OPTION_GAMERULE_SHOWROUTE] = "< Route Animation > (S)";


	dictionary[x][TEXT_HELP_1] = "1.Use keyboard or mouse to move beads";
	dictionary[x][TEXT_HELP_2] = "2.We'll remove beads if there are 5 same beads in row/col/diagonal";
	dictionary[x][TEXT_HELP_3] = "3.Every time you remove a bead, you can gain 2pts";
	dictionary[x][TEXT_HELP_4] = "4.Normally, 3 beads will be placed after a move without removals.";
	dictionary[x][TEXT_HELP_5] = "5.But no beads will be placed after a removal.";
	dictionary[x][TEXT_HELP_6] = "6.Starting cell and destination should be connected";
	dictionary[x][TEXT_HELP_7] = "7.Press R to restart, C for settings, H for help, A for author info.";
	dictionary[x][TEXT_HELP_8] = "8.When all cells are occupied, the game is over. ";
	dictionary[x][TEXT_HELP_9] = "9.Seven beads will be placed every time game starts.";
	dictionary[x][TEXT_HELP_10] = "10.Beads might automatically removed after placement.";
	dictionary[x][TEXT_HELP_11] = "11.You won't get scores under the situation mentioned in Rule #10.";

	dictionary[x][TEXT_BORDERLINE_1] = "-----------------";
	dictionary[x][TEXT_BORDERLINE_2] = "---------------------";
	dictionary[x][TEXT_BORDERLINE_3] = "---------------";

	dictionary[x][TEXT_EXCEPTHANDLE_HEADER] = "----------------------------Exception Detected------------------------------";
	dictionary[x][TEXT_EXCEPTHANDLE_SELECT_EXIT_AND_IGNORE] = "Ignore the exception or terminate the process? (Y-Exit/N-Ignore):";
	dictionary[x][TEXT_EXCEPTHANDLE_SELECT_EXIT_ONLY] = "Application will exit. Press any key to continue:";
	
	dictionary[x][TEXT_EXCEPTION_FILEIO_INPUT_DENIED] = "Permission Denied (File Read)";
	dictionary[x][TEXT_EXCEPTION_FILEIO_OUTPUT_DENIED] = "Permission Denied (File Write)";
	dictionary[x][TEXT_EXCEPTION_FILEIO_INPUT_INVALID] = "File cannot be correctly explained by built-in functions.";
	dictionary[x][TEXT_EXCEPTION_FILEIO_INPUT_HASH_CONFLICT] = "File cannot be correctly validated.";
	dictionary[x][TEXT_EXCEPTION_FILEIO_INPUT_FAILED] = "File cannot be read. Be sure that the file exists and can be edited.";
	dictionary[x][TEXT_EXCEPTION_FILEIO_OUTPUT_FAILED] = "File cannot be written.  Be sure that the file exists and can be edited.";
	dictionary[x][TEXT_EXCEPTION_FILEIO_FILE_BROKEN] = "File to be loaded is broken. Data cannot be correctly loaded.";
	dictionary[x][TEXT_EXCEPTION_FILEIO_SIGNATURE_CONFLICT] = "File cannot be loaded for the signature saved is wrong.";
	dictionary[x][TEXT_EXCEPTION_FILEIO_VALIDATOR_CONFLICT] = "File cannot be loaded for validation is not successful.";

	dictionary[x][TEXT_EXCEPTION_CODEPAGE_NOT_SUPPORTED] = "Your code page setting is unsupported. We'll use an alternative setting.";
	dictionary[x][TEXT_EXCEPTION_CODEPAGE_NOT_SUPPORTED_2] = "If you continue running the application, you might meet garbled characters.";
	dictionary[x][TEXT_EXCEPTION_FILEIO_GAMESETTINGS_CONFLICT] = "File cannot be loaded for the content is incompatible with current settings.";

}

//Chinese
void Game_Localization::langPre_SetChineseS_b64_utf8() {
	langPre_SetSymbol_b64_utf8(4);
	dictionary[4][TEXT_GUIDE_INPUT_PLACECOORD] = b64.base64_Decode("6K+36L6T5YWl6ZyA6KaB5pS+572u5qOL5a2Q55qE5Z2Q5qCH77ya");
	dictionary[4][TEXT_GUIDE_INPUT_MOVECOORD] = b64.base64_Decode("6K+36L6T5YWl6ZyA6KaB56e75Yqo5qOL5a2Q55qE5Z2Q5qCH77ya");
	dictionary[4][TEXT_GUIDE_INPUT_PLAYERNAME] = b64.base64_Decode("6L6T5YWl546p5a625aeT5ZCN77ya");
	dictionary[4][TEXT_GUIDE_INPUT_PLAYERORDER] = b64.base64_Decode("6L6T5YWl546p5a625qyh5bqP77ya");
	dictionary[4][TEXT_GUIDE_INPUT_SOURCECOORD_X] = b64.base64_Decode("44CQ6ZSu55uY44CR6L6T5YWl6KaB56e75Yqo5qOL5a2Q55qE6KGM5Z2Q5qCH77yI5Y+v5oyJ5LiL54m55a6a5a2X5q+N6YCJ5oup5bem5L6n6YCJ6aG577yJ77ya");
	dictionary[4][TEXT_GUIDE_INPUT_SOURCECOORD_Y] = b64.base64_Decode("44CQ6ZSu55uY44CR6L6T5YWl6KaB56e75Yqo5qOL5a2Q55qE5YiX5Z2Q5qCH77yI5Y+v5oyJ5LiL54m55a6a5a2X5q+N6YCJ5oup5bem5L6n6YCJ6aG577yJ77ya");
	dictionary[4][TEXT_GUIDE_INPUT_DESTCOORD_X] = b64.base64_Decode("44CQ6ZSu55uY44CR6L6T5YWl6KaB5pS+572u5qOL5a2Q55qE6KGM5Z2Q5qCH77yI5Y+v5oyJ5LiL54m55a6a5a2X5q+N6YCJ5oup5bem5L6n6YCJ6aG577yJ77ya");
	dictionary[4][TEXT_GUIDE_INPUT_DESTCOORD_Y] = b64.base64_Decode("44CQ6ZSu55uY44CR6L6T5YWl6KaB5pS+572u5qOL5a2Q55qE5YiX5Z2Q5qCH77yI5Y+v5oyJ5LiL54m55a6a5a2X5q+N6YCJ5oup5bem5L6n6YCJ6aG577yJ77ya");
	dictionary[4][TEXT_GUIDE_INPUT_CLICK_SOURCECOORD] = b64.base64_Decode("44CQ6byg5qCH44CR6K+354K55Ye76KaB56e75Yqo55qE5qOL5a2Q77ya");
	dictionary[4][TEXT_GUIDE_INPUT_CLICK_DESTCOORD] = b64.base64_Decode("44CQ6byg5qCH44CR6K+354K55Ye76KaB5pS+572u5qOL5a2Q55qE5L2N572u77ya");
	dictionary[4][TEXT_GUIDE_INPUT_COORD] = b64.base64_Decode("6ZSu55uY6L6T5YWl44CQ5oyJ5LiL5Zue6L2m5o+Q5Lqk44CROg==");

	dictionary[4][TEXT_LABEL_SCORES] = b64.base64_Decode("44CQ5b6XIOWIhuOAkQ==");
	dictionary[4][TEXT_LABEL_REMOVE_CNT] = b64.base64_Decode("5oiQ5Yqf5raI6Zmk55qE5qOL5a2Q5Liq5pWw5Li6Og==");
	dictionary[4][TEXT_LABEL_REMOVE_SCORE] = b64.base64_Decode("6I635b6X55qE5YiG5pWw5Li6Og==");
	dictionary[4][TEXT_LABEL_CURRENT_PLAYER] = b64.base64_Decode("44CQ5b2T5YmN546p5a6244CR");
	dictionary[4][TEXT_LABEL_CURRENT_PLAYER_PLACEHOLDER] = b64.base64_Decode("ICAgICAgICAgIA==");
	dictionary[4][TEXT_LABEL_FINAL_SCORE] = b64.base64_Decode("5pyA57uI5b6X5YiGOg==");
	dictionary[4][TEXT_LABEL_REMOVE_TOTALSCORE] = b64.base64_Decode("5q2k5qyh5pON5L2c77yM5raI6Zmk6I635b6X5oC75YiGOg==");
	dictionary[4][TEXT_LABEL_TOTALMOVES] = b64.base64_Decode("44CQ56e75Yqo5oC75pWw44CR");
	dictionary[4][TEXT_LABEL_FORESEE] = b64.base64_Decode("44CQ5Y2z5bCG55Sf5oiQ44CR");
	dictionary[4][TEXT_LABEL_AUTHOR_NAME] = b64.base64_Decode("5L2c6ICF5aeT5ZCN77ya");
	dictionary[4][TEXT_LABEL_AUTHOR_STUID] = b64.base64_Decode("5a2m5Y+377ya");
	dictionary[4][TEXT_LABEL_RESET_INPUT] = b64.base64_Decode("5oyJ5LiL6ZSu55uYUOmUrumHjee9rui+k+WFpQ==");
	dictionary[4][TEXT_LABEL_SOURCE_CELL] = b64.base64_Decode("W+i1t+eCueWdkOagh10=");
	dictionary[4][TEXT_LABEL_SYSTEM_REMOVAL] = b64.base64_Decode("IOezu+e7n+enu+mZpO+8jOS4jeiuoeWIhg==");


	dictionary[4][TEXT_INFO_INVALID_MOVE_UNCONNECTED] = b64.base64_Decode("55uu5qCH5LiO5p2l5rqQ5qC85a2Q6ZyA6IGU6YCa");
	dictionary[4][TEXT_INFO_INVALID_MOVE_OCCUPIED] = b64.base64_Decode("55uu5qCH5qC85a2Q5bey6KKr5Y2g55So");
	dictionary[4][TEXT_INFO_INVALID_MOVE_EMPTY] = b64.base64_Decode("5p2l5rqQ5qC85a2Q5Li656m6");
	dictionary[4][TEXT_INFO_INVALID_MOVE_HEADER] = b64.base64_Decode("56e75Yqo5peg5pWI");

	dictionary[4][TEXT_INFO_COMPLETE_OCCPUIED] = b64.base64_Decode("5ri45oiP57uT5p2f77yM5omA5pyJ5qC85a2Q5bey57uP6KKr5Y2g55So");
	dictionary[4][TEXT_INFO_NEWBEADS_PLACED] = b64.base64_Decode("5bey57uP5pS+572u5LqG5paw55qE5qOL5a2Q");
	dictionary[4][TEXT_INFO_MOVE_SUCCESS] = b64.base64_Decode("56e75Yqo5oiQ5Yqf");
	dictionary[4][TEXT_INFO_PRESS_ANY_KEY_TO_CONTINUE] = b64.base64_Decode("5oyJ5LiL5Lu75oSP6ZSu5Lul57un57utLi4uLi4u");
	dictionary[4][TEXT_INFO_PRESS_ENTER_TO_CONTINUE] = b64.base64_Decode("5oyJ5LiLRW50ZXLku6Xnu6fnu60uLi4uLi4=");
	dictionary[4][TEXT_INFO_INVALID_COORD] = b64.base64_Decode("6L6T5YWl55qE5Z2Q5qCH5peg5pWI77yB");
	dictionary[4][TEXT_INFO_MOVE_WITHOUT_REMOVAL] = b64.base64_Decode("5q2k5qyh6L6T5YWl5pyq5raI6Zmk5Lu75L2V5qOL5a2Q");
	dictionary[4][TEXT_INFO_GAIN_ANOTHER_CHANCE] = b64.base64_Decode("5oKo6I635b6X5LqG6aKd5aSW55qE56e75Yqo5py65Lya77yB");
	dictionary[4][TEXT_INFO_GAME_RESTARTED] = b64.base64_Decode("5ri45oiP5bey57uP6YeN5paw5byA5aeL77yB");
	dictionary[4][TEXT_INFO_INVALID_INPUT] = b64.base64_Decode("6L6T5YWl6Z2e5rOV77yM6K+35oyJ5pWw5a2X6ZSu44CB54m55a6a5a2X5q+N5oyJ6ZSu5oiW5Y+M5Ye75q2j56Gu5Yy65Z+f77yB");
	dictionary[4][TEXT_INFO_RESTARTING_CONFIRM] = b64.base64_Decode("5oKo5piv5ZCm5bCG6YeN5paw5byA5aeL5LiA5bGA5paw55qE5ri45oiP77yf77yI5L2/55SoWS9O5oyJ6ZSu5oiW5pa55ZCR6ZSuK0VudGVy56Gu5a6aKQ==");
	dictionary[4][TEXT_INFO_CHEAT_DETECTED] = b64.base64_Decode("5L6m5rWL5Yiw5L2c5byK77yB6K+35oKo5YWz6Zet5ri45oiP5ZCO6YeN5ZCv77yB");
	dictionary[4][TEXT_INFO_EXIT_CONFIRM] = b64.base64_Decode("5oKo5piv5ZCm5bCG6YCA5Ye65pys5bGA5ri45oiP77yf77yI5L2/55SoQy9UL0XmjInplK7miJbmlrnlkJHplK4rRW50ZXLnoa7lrpop");
	dictionary[4][TEXT_INFO_MOUSE_UNSUPPORTED] = b64.base64_Decode("5b2T5YmN5pON5L2c57O757uf55qE54mI5pys5pqC5LiN5pSv5oyB6byg5qCH5pON5L2c");
	dictionary[4][TEXT_INFO_KEYBOARD_UNSUPPORTED] = b64.base64_Decode("5b2T5YmN5pON5L2c57O757uf55qE54mI5pys5pqC5LiN5pSv5oyB6ZSu55uY5pON5L2c");
	dictionary[4][TEXT_INFO_MOVELIMIT_CONFIRM] = b64.base64_Decode("5piv5ZCm6LCD5pW056e75Yqo55qE6LW354K55ZKM57uI54K56ZyA6KaB6IGU6YCa55qE6ZmQ5Yi277yf77yI6buY6K6k5byA5ZCv77yJ");
	dictionary[4][TEXT_INFO_MOVELIMIT_CONFIRM_2] = b64.base64_Decode("IA==");
	dictionary[4][TEXT_INFO_MOVELIMIT_DISABLED] = b64.base64_Decode("56e75Yqo6ZmQ5Yi25bey57uP6KKr5YWz6Zet");
	dictionary[4][TEXT_INFO_MOVELIMIT_ENABLED] = b64.base64_Decode("56e75Yqo6ZmQ5Yi25bey57uP6KKr5ZCv55So");
	dictionary[4][TEXT_INFO_INPUTDEVICE_SWITCH_CONFIRM] = b64.base64_Decode("5YiH5o2i5ri45oiP55qE6L6T5YWl5pa55byP77yfKOm7mOiupOmUruebmO+8jOiuvue9ruS7heWvueaji+WtkOenu+WKqOaTjeS9nOacieaViCk=");
	dictionary[4][TEXT_INFO_COMING_SOON] = b64.base64_Decode("5q2k6aG55Yqf6IO95pqC5pe25LiN5pSv5oyB44CC77yI5oyJ5LiLRW50ZXLmiJZZ5YWz6Zet5q2k5L+h5oGv77yJ");
	dictionary[4][TEXT_INFO_FORESEE_CONFIRM] = b64.base64_Decode("6LCD5pW06aKE6KeB5Yqf6IO977yf5byA5ZCv5ZCO5bCG5o+Q56S65LiL5LiA6L2u55Sf5oiQ55qE5qOL5a2Q44CC77yI6buY6K6k5YWz6Zet77yJ");
	dictionary[4][TEXT_INFO_GAME_STARTED] = b64.base64_Decode("5ri45oiP546w5Zyo5byA5aeL77yB");
	dictionary[4][TEXT_INFO_LANG_SWITCH_A] = b64.base64_Decode("5piv5ZCm5YiH5o2i6K+t6KiA44CC6LCD5pW05ZCO5ri45oiP5bCG6YeN5paw5Yid5aeL5YyW77yM5q2k5bGA5ri45oiP5by65Yi257uT5p2f44CC");
	dictionary[4][TEXT_INFO_LANG_SWITCH_B] = b64.base64_Decode("QWZ0ZXIgdGhlIGNoYW5nZSwgeW91ciBnYW1lIHdpbGwgYmUgcmVzdGFydGVkIGFuZCByZWluaXRpYWxpemVkLg==");
	dictionary[4][TEXT_INFO_MAINTITLE_OPTION_SWITCH] = b64.base64_Decode("5L2/55So44CQ5pa55ZCR6ZSu5ZKMRW50ZXLjgJEg5oiWIOOAkEUvTC9T6ZSu44CR6YCJ5oup6YCJ6aG5");
	dictionary[4][TEXT_INFO_DO_NOT_DISTRIBUTE] = "";
	dictionary[4][TEXT_INFO_OS_NOT_SUPPORTED] = b64.base64_Decode("5q2k5Yqf6IO955uu5YmN5Zyo5oKo55qE5pON5L2c57O757uf5LiK5LiN5Y+v55So44CC");
	dictionary[4][TEXT_INFO_SHOWROUTE_CONFIRM] = b64.base64_Decode("5oKo6ZyA6KaB5bGV56S6L+i3s+i/h+enu+WKqOaji+WtkOeahOi3r+W+hOi/h+eoi+WKqOeUu+WQl++8nw==");
	dictionary[4][TEXT_INFO_NOT_INPUTTED] = b64.base64_Decode("5pyq6L6T5YWl");
	dictionary[4][TEXT_INFO_INPUT_RESET] = b64.base64_Decode("6L6T5YWl5bey57uP6YeN572u77yM6K+36YeN5paw6L6T5YWl");
	dictionary[4][TEXT_INFO_GAME_SAVED] = b64.base64_Decode("5oKo55qE5ri45oiP6L+b5bqm5bey57uP6KKr5L+d5a2Y77yB");
	dictionary[4][TEXT_INFO_NO_AVAILABLE_MOVES] = b64.base64_Decode("5rKh5pyJ5Y+v55So55qE56e75Yqo77yM5q2k6L2u57uT5p2f44CC");

	dictionary[4][TEXT_LABEL_ALERTTITLE_COMMON] = b64.base64_Decode("5L+h5oGv");
	dictionary[4][TEXT_LABEL_ALERTTITLE_RESTART] = b64.base64_Decode("6YeN5paw5byA5aeL");
	dictionary[4][TEXT_LABEL_ALERTTITLE_HELP] = b64.base64_Decode("546p5rOV5biu5Yqp");
	dictionary[4][TEXT_LABEL_ALERTTITLE_EXIT] = b64.base64_Decode("6YCA5Ye65pys5bGA5ri45oiP");
	dictionary[4][TEXT_LABEL_ALERTTITLE_ANTICHEAT] = b64.base64_Decode("5L2c5byK5L6m5rWL");
	dictionary[4][TEXT_LABEL_ALERTTITLE_SETTINGS] = b64.base64_Decode("5ri45oiP6K6+572u");
	dictionary[4][TEXT_LABEL_ALERTTITLE_SETTINGS_INPUTDEVICE] = b64.base64_Decode("5ri45oiP6K6+572uIC8g6L6T5YWl6K6+5aSH6K6+5a6a");
	dictionary[4][TEXT_LABEL_ALERTTITLE_SETTINGS_LANG] = b64.base64_Decode("5ri45oiP6K6+572uIC8g6K+t6KiA6K6+572u");
	dictionary[4][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_FORESEE] = b64.base64_Decode("5ri45oiP6K6+572uIC8g5ri45oiP6KeE5YiZIC0g5o+Q56S65LiL6L2u5qOL5a2Q");
	dictionary[4][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_MOVELIMIT] = b64.base64_Decode("5ri45oiP6K6+572uIC8g5ri45oiP6KeE5YiZIC0g6K6+5a6a56e75Yqo6ZmQ5Yi2");
	dictionary[4][TEXT_LABEL_ALERTTITLE_CREDIT] = b64.base64_Decode("5L2c6ICF5L+h5oGv");
	dictionary[4][TEXT_LABEL_ALERTTITLE_LANGUAGE] = b64.base64_Decode("6K+t6KiA6K6+572uIExhbmd1YWdlIFNldHRpbmdz");
	dictionary[4][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_SHOWROUTE] = b64.base64_Decode("5ri45oiP6K6+572uIC8g5ri45oiP6KeE5YiZIC0g5bGV56S656e75Yqo6Lev5b6E");

	dictionary[4][TEXT_OPTION_RESTART] = b64.base64_Decode("44COIOmHjeaWsOW8gOWniyDjgI/vvIjplK7nm5hS77yJ");
	dictionary[4][TEXT_OPTION_EXIT] = b64.base64_Decode("44COIOmAgOWHuua4uOaIjyDjgI/vvIjplK7nm5hF77yJ");
	dictionary[4][TEXT_OPTION_WITHDRAW] = b64.base64_Decode("44COIOWbniAgICDpgIAg44CP77yI6ZSu55uYQu+8iQ==");
	dictionary[4][TEXT_OPTION_SETTING] = b64.base64_Decode("44COIOiuviAgICDnva4g44CP77yI6ZSu55uYQ++8iQ==");
	dictionary[4][TEXT_OPTION_ABORT] = b64.base64_Decode("44COIOaUviAgICDlvIMg44CP77yI6ZSu55uYUe+8iQ==");
	dictionary[4][TEXT_OPTION_CREDIT] = b64.base64_Decode("44COIOS9nOiAheS/oeaBryDjgI/vvIjplK7nm5hB77yJ");
	dictionary[4][TEXT_OPTION_HELP] = b64.base64_Decode("44COIOeOqeazleW4ruWKqSDjgI/vvIjplK7nm5hI77yJ");
	dictionary[4][TEXT_OPTION_YES] = b64.base64_Decode("44COIOaYryDjgI/vvIhZ77yJ");
	dictionary[4][TEXT_OPTION_NO] = b64.base64_Decode("44COIOWQpiDjgI/vvIhO77yJ");
	dictionary[4][TEXT_OPTION_CLOSE] = b64.base64_Decode("44COIOWFsyDpl60g44CP77yIQ++8iQ==");
	dictionary[4][TEXT_OPTION_TITLESCENE] = b64.base64_Decode("44COIOWbnuWIsOS4u+agh+mimCDjgI/vvIhU77yJ");
	dictionary[4][TEXT_OPTION_EXIT2] = b64.base64_Decode("44COIOWFs+mXrea4uOaIjyDjgI/vvIhF77yJ");
	dictionary[4][TEXT_OPTION_CANCEL] = b64.base64_Decode("44COIOWPliDmtogg44CP77yIQ++8iQ==");
	dictionary[4][TEXT_OPTION_ON] = b64.base64_Decode("44COIOW8gCDlkK8g44CP77yIU++8iQ==");
	dictionary[4][TEXT_OPTION_OFF] = b64.base64_Decode("44COIOWFsyDpl60g44CP77yIVO+8iQ==");
	dictionary[4][TEXT_OPTION_KNOWN] = b64.base64_Decode("44COIOS6hiDop6Mg44CP77yIWe+8iQ==");
	dictionary[4][TEXT_OPTION_SAVE] = b64.base64_Decode("44COIOS/neWtmOa4uOaIjyDjgI/vvIjplK7nm5hT77yJ");

	dictionary[4][TEXT_OPTION_MAINTITLE_STARTGAME] = b64.base64_Decode("44CQIOW8gCDlp4sg5ri4IOaIjyDjgJEoUyk=");
	dictionary[4][TEXT_OPTION_MAINTITLE_AUTHOR] = b64.base64_Decode("44CQIOS9nCDogIUg5L+hIOaBryDjgJEoQSk=");
	dictionary[4][TEXT_OPTION_MAINTITLE_EXIT] = b64.base64_Decode("44CQIOmAgCDlh7og5ri4IOaIjyDjgJEoRSk=");
	dictionary[4][TEXT_OPTION_MAINTITLE_LOAD] = b64.base64_Decode("44CQIOWKoCDovb0g5ri4IOaIjyDjgJEoTEwp=");

	dictionary[4][TEXT_OPTION_OPERATION_DEVICE] = b64.base64_Decode("44COIOiuvue9rui+k+WFpeaWueW8jyDjgI/vvIhE77yJ");
	dictionary[4][TEXT_OPTION_OPERATION_DEVICE_KEYBOARD] = b64.base64_Decode("44COIOS7hemUruebmOi+k+WFpSDjgI/vvIhL77yJ");
	dictionary[4][TEXT_OPTION_OPERATION_DEVICE_MOUSE] = b64.base64_Decode("44COIOWFgeiuuOm8oOagh+i+k+WFpSDjgI/vvIhN77yJ");
	dictionary[4][TEXT_OPTION_LANGUAGE] = b64.base64_Decode("44COIOivreiogExhbmd1YWdlIOOAj++8iEzvvIk=");
	dictionary[4][TEXT_OPTION_LANGUAGE_ZHCN] = b64.base64_Decode("44COIOeugOS9k+S4reaWhyDjgI8=");
	dictionary[4][TEXT_OPTION_LANGUAGE_ENUS] = b64.base64_Decode("44COIEVuZ2xpc2gg44CP");
	dictionary[4][TEXT_OPTION_LANGUAGE_ENUS_GBK] = b64.base64_Decode("44COIEVuZ2xpc2ggKEdCSykg44CP");
	dictionary[4][TEXT_OPTION_LANGUAGE_ENUS_UTF8] = b64.base64_Decode("44COIEVuZ2xpc2ggKFVURjgpIOOAjw==");
	dictionary[4][TEXT_OPTION_LANGUAGE_ZHCN_GBK] = b64.base64_Decode("44COIOeugOS9k+S4reaWhyBHQksg44CP");
	dictionary[4][TEXT_OPTION_LANGUAGE_ZHCN_UTF8] = b64.base64_Decode("44COIOeugOS9k+S4reaWhyBVVEY4IOOAjw==");

	dictionary[4][TEXT_OPTION_GAMERULE_FORESEE] = b64.base64_Decode("44COIOaPkOekuuS4i+i9ruaji+WtkCDjgI/vvIhG77yJ");
	dictionary[4][TEXT_OPTION_GAMERULE_MOVE_LIMIT] = b64.base64_Decode("44COIOenu+WKqOmZkOWItuiuvuWumiDjgI/vvIhN77yJ");
	dictionary[4][TEXT_OPTION_GAMERULE_SHOWROUTE] = b64.base64_Decode("44COIOiuvuWumuenu+WKqOWKqOeUuyDjgI/vvIhT77yJ");


	dictionary[4][TEXT_HELP_1] = b64.base64_Decode("MS7kvb/nlKjplK7nm5jovpPlhaXlnZDmoIcv5oiW6byg5qCH54K55Ye777yM56e75Yqo5qOL5a2Q");
	dictionary[4][TEXT_HELP_2] = b64.base64_Decode("Mi7lvZPlkIzoibLmo4vlrZDmqKrlkJEv56uW5ZCRL+aWnOWQkei2hei/hzXkuKrlkI7vvIzlsIbkvJrmtojpmaQ=");
	dictionary[4][TEXT_HELP_3] = b64.base64_Decode("My7mr4/mtojpmaTkuIDkuKrmo4vlrZDvvIzorqEy5YiG");
	dictionary[4][TEXT_HELP_4] = b64.base64_Decode("NC7lpoLmnpzkuIDmrKHmnKrmtojpmaTku7vkvZXnmoTmo4vlrZDvvIzns7vnu5/pmo/mnLrmlL4z5Liq5qOL5a2Q");
	dictionary[4][TEXT_HELP_5] = b64.base64_Decode("NS7lpoLmnpzkuIDmrKHnp7vliqjmtojpmaTkuobmo4vlrZDvvIzpop3lpJbojrflvpfmnLrkvJo=");
	dictionary[4][TEXT_HELP_6] = b64.base64_Decode("Ni7np7vliqjnmoTotbfngrnlkoznu4jngrnlv4XpobvogZTpgJrvvIjml6Dlhbbku5bmo4vlrZDlkozmo4vnm5jovrnnlYzpmLvmjKHvvIk=");
	dictionary[4][TEXT_HELP_7] = b64.base64_Decode("Ny7mjInkuItS6ZSu5Y+v6YeN5paw5byA5aeL77yMQ+mUruiwg+WHuuiuvue9ru+8jEXplK7pgIDlh7rmuLjmiI/vvIxI6ZSu5p+l55yL5biu5Yqp");
	dictionary[4][TEXT_HELP_8] = b64.base64_Decode("OC7lvZPmo4vnm5jlhajmu6HvvIzkuJTml6Dlj6/mtojpmaTnmoTmo4vlrZDml7bvvIzmuLjmiI/nu5PmnZ8=");
	dictionary[4][TEXT_HELP_9] = b64.base64_Decode("OS7mr4/lsYDmuLjmiI/lvIDlp4vvvIzns7vnu5/lsIbpmo/mnLrmlL7nva435Liq5qOL5a2Q");
	dictionary[4][TEXT_HELP_10] = b64.base64_Decode("MTAu5q+P5qyh5pS+572u5ZCO57O757uf5Lya6Ieq5Yqo56e76Zmk56ym5ZCI5p2h5Lu255qE5qOL5a2Q");
	dictionary[4][TEXT_HELP_11] = b64.base64_Decode("MTEu5aaC5p6c5qOL5a2Q6KKr6Ieq5Yqo56e76Zmk77yM5YiZ5LiN6K6h5YiG");
	dictionary[4][TEXT_BORDERLINE_1] = "------------------------";
	dictionary[4][TEXT_BORDERLINE_2] = "------------------------";
	dictionary[4][TEXT_BORDERLINE_3] = "------------------------";

	dictionary[4][TEXT_EXCEPTHANDLE_HEADER] = b64.base64_Decode("LS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLei/kOihjOWHuueOsOW8guW4uC0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0=");
	dictionary[4][TEXT_EXCEPTHANDLE_SELECT_EXIT_AND_IGNORE] = b64.base64_Decode("6YCJ5oup6YCA5Ye656iL5bqP6L+Y5piv5b+955Wl5q2k5o+Q56S677yM57un57ut6L+Q6KGM56iL5bqP6YOo5YiG5Yqf6IO95Y+v6IO95Y+X6ZmQ77yIWS3pgIDlh7ovbi3lv73nlaXvvInvvJo=");
	dictionary[4][TEXT_EXCEPTHANDLE_SELECT_EXIT_ONLY] = b64.base64_Decode("56iL5bqP5bCG57uT5p2f44CC5oyJ5LiL5Lu75oSP6ZSu5p2l6YCA5Ye644CC");

	dictionary[4][TEXT_EXCEPTION_FILEIO_INPUT_DENIED] = "Permission Denied (File Read)";
	dictionary[4][TEXT_EXCEPTION_FILEIO_OUTPUT_DENIED] = "Permission Denied (File Write)";
	dictionary[4][TEXT_EXCEPTION_FILEIO_INPUT_INVALID] = "File cannot be correctly explained by built-in functions.";
	dictionary[4][TEXT_EXCEPTION_FILEIO_INPUT_HASH_CONFLICT] = "File cannot be correctly validated.";
	dictionary[4][TEXT_EXCEPTION_FILEIO_INPUT_FAILED] = b64.base64_Decode("6K+75Y+W5paH5Lu25aSx6LSl77yM5paH5Lu25LiN5a2Y5Zyo5oiW5peg5rOV5omT5byA44CC");
	dictionary[4][TEXT_EXCEPTION_FILEIO_OUTPUT_FAILED] = b64.base64_Decode("5YaZ5YWl5paH5Lu25aSx6LSl77yM5paH5Lu25peg5rOV5omT5byA44CC");
	dictionary[4][TEXT_EXCEPTION_FILEIO_FILE_BROKEN] = b64.base64_Decode("5paH5Lu25bey57uP5o2f5Z2P5oiW5qC85byP5LiN5YW85a655b2T5YmN54mI5pys44CC");

	dictionary[4][TEXT_EXCEPTION_FILEIO_SIGNATURE_CONFLICT] = b64.base64_Decode("5paH5Lu25pGY6KaB5L+h5oGv6ZSZ6K+v77yM5oiR5Lus5peg5rOV6aqM6K+B5Yqg6L295L+h5oGv55qE5q2j56Gu5oCn77yM5Yqg6L295bCG57uI5q2i44CC");
	dictionary[4][TEXT_EXCEPTION_FILEIO_VALIDATOR_CONFLICT] = b64.base64_Decode("5paH5Lu25YaF6YOo6aqM6K+B5L+h5oGv5Yay56qB77yM5oiR5Lus5peg5rOV6aqM6K+B5paH5Lu25pyJ5pWI5oCn77yM5Yqg6L295bCG57uI5q2i44CC");
	dictionary[4][TEXT_EXCEPTION_FILEIO_GAMESETTINGS_CONFLICT] = b64.base64_Decode("5paH5Lu25YaF5a655LiO5b2T5YmN54mI5pys6K6+572u5LiN5YW85a6577yM5paH5Lu25peg5rOV5Yqg6L2944CC");

	dictionary[4][TEXT_INFO_GAME_LOADED] = b64.base64_Decode("5bey57uP5oiQ5Yqf5Yqg6L295oKo55qE5ri45oiP6L+b5bqm77yB");

}

void Game_Localization::langPre_SetChineseS_b64_gbk() {
	langPre_SetSymbol_b64_gbk(3);
	dictionary[3][TEXT_GUIDE_INPUT_PLACECOORD] = b64.base64_Decode("x+vK5Mjr0OjSqrfF1sPG5dfTtcTX+LHqo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_MOVECOORD] = b64.base64_Decode("x+vK5Mjr0OjSqtLGtq/G5dfTtcTX+LHqo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_PLAYERNAME] = b64.base64_Decode("yuTI683mvNLQ1cP7o7o=");
	dictionary[3][TEXT_GUIDE_INPUT_PLAYERORDER] = b64.base64_Decode("yuTI683mvNK0ztDyo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_SOURCECOORD_X] = b64.base64_Decode("ob68/MXMob/K5Mjr0qrSxravxuXX07XE0NDX+LHqo6i/ybC0z8LM2Lao19bEuNGh1PHX87Lg0aHP7qOpo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_SOURCECOORD_Y] = b64.base64_Decode("ob68/MXMob/K5Mjr0qrSxravxuXX07XEwdDX+LHqo6i/ybC0z8LM2Lao19bEuNGh1PHX87Lg0aHP7qOpo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_DESTCOORD_X] = b64.base64_Decode("ob68/MXMob/K5Mjr0qq3xdbDxuXX07XE0NDX+LHqo6i/ybC0z8LM2Lao19bEuNGh1PHX87Lg0aHP7qOpo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_DESTCOORD_Y] = b64.base64_Decode("ob68/MXMob/K5Mjr0qq3xdbDxuXX07XEwdDX+LHqo6i/ybC0z8LM2Lao19bEuNGh1PHX87Lg0aHP7qOpo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_CLICK_SOURCECOORD] = b64.base64_Decode("ob7K87Hqob/H67Xju/fSqtLGtq+1xMbl19Ojug==");
	dictionary[3][TEXT_GUIDE_INPUT_CLICK_DESTCOORD] = b64.base64_Decode("ob7K87Hqob/H67Xju/fSqrfF1sPG5dfTtcTOu9bDo7o=");
	dictionary[3][TEXT_GUIDE_INPUT_COORD] = b64.base64_Decode("vPzFzMrkyOuhvrC0z8K72LO1zOG9u6G/Og==");

	dictionary[3][TEXT_LABEL_SCORES] = b64.base64_Decode("ob61wyC31qG/");
	dictionary[3][TEXT_LABEL_REMOVE_CNT] = b64.base64_Decode("s8m5ps/7s/21xMbl19O49sr9zqo6");
	dictionary[3][TEXT_LABEL_REMOVE_SCORE] = b64.base64_Decode("u/G1w7XEt9bK/c6qOg==");
	dictionary[3][TEXT_LABEL_CURRENT_PLAYER] = b64.base64_Decode("ob61scewzea80qG/");
	dictionary[3][TEXT_LABEL_CURRENT_PLAYER_PLACEHOLDER] = b64.base64_Decode("ICAgICAgICAgIA==");
	dictionary[3][TEXT_LABEL_FINAL_SCORE] = b64.base64_Decode("1+7W1bXDt9Y6");
	dictionary[3][TEXT_LABEL_REMOVE_TOTALSCORE] = b64.base64_Decode("tMu0zrLZ1/ejrM/7s/278bXD19y31jo=");
	dictionary[3][TEXT_LABEL_TOTALMOVES] = b64.base64_Decode("ob7Sxrav19zK/aG/");
	dictionary[3][TEXT_LABEL_FORESEE] = b64.base64_Decode("ob68tL2ryfqzyaG/");
	dictionary[3][TEXT_LABEL_AUTHOR_NAME] = b64.base64_Decode("1/fV39DVw/ujug==");
	dictionary[3][TEXT_LABEL_AUTHOR_STUID] = b64.base64_Decode("0ae6xaO6");
	dictionary[3][TEXT_LABEL_RESET_INPUT] = b64.base64_Decode("sLTPwrz8xcxQvPzW2NbDyuTI6w==");
	dictionary[3][TEXT_LABEL_SOURCE_CELL] = b64.base64_Decode("W8bwtePX+LHqXQ==");
	dictionary[3][TEXT_LABEL_SYSTEM_REMOVAL] = b64.base64_Decode("IM+1zbPSxrP9o6yyu7zGt9Y=");


	dictionary[3][TEXT_INFO_INVALID_MOVE_UNCONNECTED] = b64.base64_Decode("xL+x6tPrwLTUtLjx19PQ6MGqzag=");
	dictionary[3][TEXT_INFO_INVALID_MOVE_OCCUPIED] = b64.base64_Decode("xL+x6rjx19PS0bG71bzTww==");
	dictionary[3][TEXT_INFO_INVALID_MOVE_EMPTY] = b64.base64_Decode("wLTUtLjx19POqr/V");
	dictionary[3][TEXT_INFO_INVALID_MOVE_HEADER] = b64.base64_Decode("0sa2r87e0Kcg");

	dictionary[3][TEXT_INFO_COMPLETE_OCCPUIED] = b64.base64_Decode("087Pt73hyvijrMv509C48dfT0tG+rbG71bzTww==");
	dictionary[3][TEXT_INFO_NEWBEADS_PLACED] = b64.base64_Decode("0tG+rbfF1sPBy9DCtcTG5dfT");
	dictionary[3][TEXT_INFO_MOVE_SUCCESS] = b64.base64_Decode("0sa2r7PJuaY=");
	dictionary[3][TEXT_INFO_PRESS_ANY_KEY_TO_CONTINUE] = b64.base64_Decode("sLTPwsjO0uK8/NLUvMzQ+C4uLi4uLg==");
	dictionary[3][TEXT_INFO_PRESS_ENTER_TO_CONTINUE] = b64.base64_Decode("sLTPwkVudGVy0tS8zND4Li4uLi4u");
	dictionary[3][TEXT_INFO_INVALID_COORD] = b64.base64_Decode("yuTI67XE1/ix6s7e0KejoQ==");
	dictionary[3][TEXT_INFO_MOVE_WITHOUT_REMOVAL] = b64.base64_Decode("tMu0zsrkyOvOtM/7s/3IzrrOxuXX0w==");
	dictionary[3][TEXT_INFO_GAIN_ANOTHER_CHANCE] = b64.base64_Decode("xPq78bXDwcu27s3itcTSxravu/q74aOh");
	dictionary[3][TEXT_INFO_GAME_RESTARTED] = b64.base64_Decode("087Pt9LRvq3W2NDCv6rKvKOh");
	dictionary[3][TEXT_INFO_INVALID_INPUT] = b64.base64_Decode("yuTI67fHt6ijrMfrsLTK/dfWvPyhoszYtqjX1sS4sLS8/Lvyy6u799X9yLfH+NPyo6E=");
	dictionary[3][TEXT_INFO_RESTARTING_CONFIRM] = b64.base64_Decode("xPrKx7fxvavW2NDCv6rKvNK7vtbQwrXE087Pt6O/o6jKudPDWS9OsLS8/Lvyt73P8rz8K0VudGVyyLe2qCk=");
	dictionary[3][TEXT_INFO_CHEAT_DETECTED] = b64.base64_Decode("1eyy4rW91/ex16Ohx+vE+rnYsdXTzs+3uvPW2Mb0o6E=");
	dictionary[3][TEXT_INFO_EXIT_CONFIRM] = b64.base64_Decode("xPrKx7fxvavNy7P2sb6+1tPOz7ejv6OoyrnTw0MvVC9FsLS8/Lvyt73P8rz8K0VudGVyyLe2qCk=");
	dictionary[3][TEXT_INFO_MOUSE_UNSUPPORTED] = b64.base64_Decode("tbHHsLLZ1/fPtc2ztcSw5rG+1N2yu9ans9bK87HqstnX9w==");
	dictionary[3][TEXT_INFO_KEYBOARD_UNSUPPORTED] = b64.base64_Decode("tbHHsLLZ1/fPtc2ztcSw5rG+1N2yu9ans9a8/MXMstnX9w==");
	dictionary[3][TEXT_INFO_MOVELIMIT_CONFIRM] = b64.base64_Decode("yse38bX31fvSxravtcTG8LXjus3W1bXj0OjSqsGqzai1xM/e1sajv6OoxKzIz7+qxvSjqQ==");
	dictionary[3][TEXT_INFO_MOVELIMIT_CONFIRM_2] = b64.base64_Decode("IA==");
	dictionary[3][TEXT_INFO_MOVELIMIT_DISABLED] = b64.base64_Decode("0sa2r8/e1sbS0b6tsbu52LHV");
	dictionary[3][TEXT_INFO_MOVELIMIT_ENABLED] = b64.base64_Decode("0sa2r8/e1sbS0b6tsbvG9NPD");
	dictionary[3][TEXT_INFO_INPUTDEVICE_SWITCH_CONFIRM] = b64.base64_Decode("x9C7u9POz7e1xMrkyOu3vcq9o78oxKzIz7z8xcyjrMno1sO99rbUxuXX09LGtq+y2df309DQpyk=");
	dictionary[3][TEXT_INFO_COMING_SOON] = b64.base64_Decode("tMvP7rmmxNzU3cqxsrvWp7PWoaOjqLC0z8JFbnRlcrvyWbnYsdW0y9DFz6KjqQ==");
	dictionary[3][TEXT_INFO_FORESEE_CONFIRM] = b64.base64_Decode("tffV+9SkvPu5psTco7+/qsb0uvO9q8zhyr7PwtK7wtbJ+rPJtcTG5dfToaOjqMSsyM+52LHVo6k=");
	dictionary[3][TEXT_INFO_GAME_STARTED] = b64.base64_Decode("087Pt8/W1Nq/qsq8o6E=");
	dictionary[3][TEXT_INFO_LANG_SWITCH_A] = b64.base64_Decode("yse38cfQu7vT79HUoaO199X7uvPTzs+3vavW2NDCs/XKvLuvo6y0y77W087Pt8e/1sa94cr4oaM=");
	dictionary[3][TEXT_INFO_LANG_SWITCH_B] = b64.base64_Decode("QWZ0ZXIgdGhlIGNoYW5nZSwgeW91ciBnYW1lIHdpbGwgYmUgcmVzdGFydGVkIGFuZCByZWluaXRpYWxpemVkLg==");
	dictionary[3][TEXT_INFO_MAINTITLE_OPTION_SWITCH] = b64.base64_Decode("yrnTw6G+t73P8rz8us1FbnRlcqG/ILvyIKG+RS9ML1O8/KG/0aHU8dGhz+4=");
	
	dictionary[3][TEXT_INFO_DO_NOT_DISTRIBUTE] = "";
	dictionary[3][TEXT_INFO_OS_NOT_SUPPORTED] = b64.base64_Decode("tMu5psTcxL/HsNTaxPq1xLLZ1/fPtc2zyc+yu7/J08Ohow==");
	dictionary[3][TEXT_INFO_SHOWROUTE_CONFIRM] = b64.base64_Decode("xPrQ6NKq1bnKvi/M+Ln90sa2r8bl19O1xMK3vra5/bPMtq+7rcLwo78=");
	dictionary[3][TEXT_INFO_NOT_INPUTTED] = b64.base64_Decode("zrTK5Mjr");
	dictionary[3][TEXT_INFO_INPUT_RESET] = b64.base64_Decode("yuTI69LRvq3W2NbDo6zH69bY0MLK5Mjr");

	dictionary[3][TEXT_INFO_GAME_SAVED] = b64.base64_Decode("xPq1xNPOz7e9+LbI0tG+rbG7saO05qOh");
	dictionary[3][TEXT_INFO_NO_AVAILABLE_MOVES] = b64.base64_Decode("w7vT0L/J08O1xNLGtq+jrLTLwta94cr4oaM=");

	dictionary[3][TEXT_LABEL_ALERTTITLE_COMMON] = b64.base64_Decode("0MXPog==");
	dictionary[3][TEXT_LABEL_ALERTTITLE_RESTART] = b64.base64_Decode("1tjQwr+qyrw=");
	dictionary[3][TEXT_LABEL_ALERTTITLE_HELP] = b64.base64_Decode("zea3qLDv1vo=");
	dictionary[3][TEXT_LABEL_ALERTTITLE_EXIT] = b64.base64_Decode("zcuz9rG+vtbTzs+3");
	dictionary[3][TEXT_LABEL_ALERTTITLE_ANTICHEAT] = b64.base64_Decode("1/ex19XssuI=");
	dictionary[3][TEXT_LABEL_ALERTTITLE_SETTINGS] = b64.base64_Decode("087Pt8no1sM=");
	dictionary[3][TEXT_LABEL_ALERTTITLE_SETTINGS_INPUTDEVICE] = b64.base64_Decode("087Pt8no1sMgLyDK5MjryeixuMnotqg=");
	dictionary[3][TEXT_LABEL_ALERTTITLE_SETTINGS_LANG] = b64.base64_Decode("087Pt8no1sMgLyDT79HUyejWww==");
	dictionary[3][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_FORESEE] = b64.base64_Decode("087Pt8no1sMgLyDTzs+3uebU8iAtIMzhyr7PwsLWxuXX0w==");
	dictionary[3][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_MOVELIMIT] = b64.base64_Decode("087Pt8no1sMgLyDTzs+3uebU8iAtIMnotqjSxravz97Wxg==");
	dictionary[3][TEXT_LABEL_ALERTTITLE_CREDIT] = b64.base64_Decode("1/fV39DFz6I=");
	dictionary[3][TEXT_LABEL_ALERTTITLE_LANGUAGE] = b64.base64_Decode("0+/R1Mno1sMgTGFuZ3VhZ2UgU2V0dGluZ3M=");
	dictionary[3][TEXT_LABEL_ALERTTITLE_SETTINGS_GAMERULE_SHOWROUTE] = b64.base64_Decode("087Pt8no1sMgLyDTzs+3uebU8iAtINW5yr7Sxravwre+tg==");

	dictionary[3][TEXT_OPTION_RESTART] = b64.base64_Decode("obog1tjQwr+qyrwgobujqLz8xcxSo6k=");
	dictionary[3][TEXT_OPTION_EXIT] = b64.base64_Decode("obogzcuz9tPOz7cgobujqLz8xcxFo6k=");
	dictionary[3][TEXT_OPTION_WITHDRAW] = b64.base64_Decode("obogu9ggICAgzcsgobujqLz8xcxCo6k=");
	dictionary[3][TEXT_OPTION_SETTING] = b64.base64_Decode("obogyeggICAg1sMgobujqLz8xcxDo6k=");
	dictionary[3][TEXT_OPTION_ABORT] = b64.base64_Decode("obogt8UgICAgxvogobujqLz8xcxRo6k=");
	dictionary[3][TEXT_OPTION_CREDIT] = b64.base64_Decode("obog1/fV39DFz6IgobujqLz8xcxBo6k=");
	dictionary[3][TEXT_OPTION_HELP] = b64.base64_Decode("obogzea3qLDv1vogobujqLz8xcxIo6k=");
	dictionary[3][TEXT_OPTION_YES] = b64.base64_Decode("obogyscgobujqFmjqQ==");
	dictionary[3][TEXT_OPTION_NO] = b64.base64_Decode("obogt/EgobujqE6jqQ==");
	dictionary[3][TEXT_OPTION_CLOSE] = b64.base64_Decode("obogudggsdUgobujqEOjqQ==");
	dictionary[3][TEXT_OPTION_TITLESCENE] = b64.base64_Decode("obogu9i1vdb3serM4iChu6OoVKOp");
	dictionary[3][TEXT_OPTION_EXIT2] = b64.base64_Decode("obogudix1dPOz7cgobujqEWjqQ==");
	dictionary[3][TEXT_OPTION_CANCEL] = b64.base64_Decode("obogyKEgz/sgobujqEOjqQ==");
	dictionary[3][TEXT_OPTION_ON] = b64.base64_Decode("obogv6ogxvQgobujqFOjqQ==");
	dictionary[3][TEXT_OPTION_OFF] = b64.base64_Decode("obogudggsdUgobujqFSjqQ==");
	dictionary[3][TEXT_OPTION_KNOWN] = b64.base64_Decode("obogwcsgveIgobujqFmjqQ==");

	dictionary[3][TEXT_OPTION_MAINTITLE_STARTGAME] = b64.base64_Decode("ob4gv6ogyrwg084gz7cgob8oUyk=");
	dictionary[3][TEXT_OPTION_MAINTITLE_AUTHOR] = b64.base64_Decode("ob4g1/cg1d8g0MUgz6Igob8oQSk=");
	dictionary[3][TEXT_OPTION_MAINTITLE_EXIT] = b64.base64_Decode("ob4gzcsgs/Yg084gz7cgob8oRSk=");
	dictionary[3][TEXT_OPTION_MAINTITLE_LOAD] = b64.base64_Decode("ob4gvNMg1Ngg084gz7cgob8oTCk=");

	dictionary[3][TEXT_OPTION_OPERATION_DEVICE] = b64.base64_Decode("obogyejWw8rkyOu3vcq9IKG7o6hEo6k=");
	dictionary[3][TEXT_OPTION_OPERATION_DEVICE_KEYBOARD] = b64.base64_Decode("obogvfa8/MXMyuTI6yChu6OoS6Op");
	dictionary[3][TEXT_OPTION_OPERATION_DEVICE_MOUSE] = b64.base64_Decode("obog1MrQ7crzserK5MjrIKG7o6hNo6k=");
	dictionary[3][TEXT_OPTION_LANGUAGE] = b64.base64_Decode("obog0+/R1Exhbmd1YWdlIKG7o6hMo6k=");
	dictionary[3][TEXT_OPTION_LANGUAGE_ZHCN] = b64.base64_Decode("obogvPLM5dbQzsQgobs=");
	dictionary[3][TEXT_OPTION_LANGUAGE_ENUS_GBK] = b64.base64_Decode("obogRW5nbGlzaCAoR0JLKSChuw==");
	dictionary[3][TEXT_OPTION_LANGUAGE_ENUS_UTF8] = b64.base64_Decode("obogRW5nbGlzaCAoVVRGOCkgobs=");
	dictionary[3][TEXT_OPTION_LANGUAGE_ZHCN_GBK] = b64.base64_Decode("obogvPLM5dbQzsQgR0JLIKG7");
	dictionary[3][TEXT_OPTION_LANGUAGE_ZHCN_UTF8] = b64.base64_Decode("obogvPLM5dbQzsQgVVRGOCChuw==");
	dictionary[3][TEXT_OPTION_SAVE] = b64.base64_Decode("obogsaO05tPOz7cgobujqLz8xcxTo6k=");


	dictionary[3][TEXT_OPTION_GAMERULE_FORESEE] = b64.base64_Decode("obogzOHKvs/CwtbG5dfTIKG7o6hGo6k=");
	dictionary[3][TEXT_OPTION_GAMERULE_MOVE_LIMIT] = b64.base64_Decode("obog0sa2r8/e1sbJ6LaoIKG7o6hNo6k=");
	dictionary[3][TEXT_OPTION_GAMERULE_SHOWROUTE] = b64.base64_Decode("obogyei2qNLGtq+2r7utIKG7o6hTo6k=");


	dictionary[3][TEXT_HELP_1] = b64.base64_Decode("MS7KudPDvPzFzMrkyOvX+LHqL7vyyvOx6rXju/ejrNLGtq/G5dfT");
	dictionary[3][TEXT_HELP_2] = b64.base64_Decode("Mi61sc2syavG5dfTuuHP8i/K+s/yL9Cxz/KzrLn9Nbj2uvOjrL2ru+HP+7P9");
	dictionary[3][TEXT_HELP_3] = b64.base64_Decode("My7Dv8/7s/3Su7j2xuXX06OsvMYyt9Y=");
	dictionary[3][TEXT_HELP_4] = b64.base64_Decode("NC7I57n70ru0zs60z/uz/cjOus61xMbl19OjrM+1zbPL5rv6t8UzuPbG5dfT");
	dictionary[3][TEXT_HELP_5] = b64.base64_Decode("NS7I57n70ru0ztLGtq/P+7P9wcvG5dfTo6y27s3iu/G1w7v6u+E=");
	dictionary[3][TEXT_HELP_6] = b64.base64_Decode("Ni7SxravtcTG8LXjus3W1bXjsdjQ68GqzaijqM7exuTL+8bl19O6zcblxcyx373n1+i1sqOp");
	dictionary[3][TEXT_HELP_7] = b64.base64_Decode("Ny6wtM/CUrz8v8nW2NDCv6rKvKOsQ7z8tfez9sno1sOjrEW8/M3Ls/bTzs+3o6xIvPyy6b+0sO/W+g==");
	dictionary[3][TEXT_HELP_8] = b64.base64_Decode("OC61scblxczIq8L6o6zH0s7ev8nP+7P9tcTG5dfTyrGjrNPOz7e94cr4");
	dictionary[3][TEXT_HELP_9] = b64.base64_Decode("OS7Dv77W087Pt7+qyryjrM+1zbO9q8vmu/q3xdbDN7j2xuXX0w==");
	dictionary[3][TEXT_HELP_10] = b64.base64_Decode("MTAuw7+0zrfF1sO688+1zbO74dfUtq/SxrP9t/u6z8z1vP61xMbl19M=");
	dictionary[3][TEXT_HELP_11] = b64.base64_Decode("MTEuyOe5+8bl19Oxu9fUtq/SxrP9o6zU8rK7vMa31g==");

	dictionary[3][TEXT_BORDERLINE_1] = "------------------------";
	dictionary[3][TEXT_BORDERLINE_2] = "------------------------";
	dictionary[3][TEXT_BORDERLINE_3] = "------------------------";

	dictionary[3][TEXT_EXCEPTHANDLE_HEADER] = b64.base64_Decode("LS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLdTL0NCz9s/W0uyzoy0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLS0=");
	dictionary[3][TEXT_EXCEPTHANDLE_SELECT_EXIT_AND_IGNORE] = b64.base64_Decode("0aHU8c3Ls/azzNDyu7nKx7r2wtS0y8zhyr6jrLzM0PjUy9DQs8zQ8rK/t9a5psTcv8nE3Mrcz96jqFktzcuz9i9uLbr2wtSjqaO6");
	dictionary[3][TEXT_EXCEPTHANDLE_SELECT_EXIT_ONLY] = b64.base64_Decode("s8zQ8r2rveHK+KGjsLTPwsjO0uK8/MC0zcuz9qGj");

	dictionary[3][TEXT_EXCEPTION_FILEIO_INPUT_DENIED] = "Permission Denied (File Read)";
	dictionary[3][TEXT_EXCEPTION_FILEIO_OUTPUT_DENIED] = "Permission Denied (File Write)";
	dictionary[3][TEXT_EXCEPTION_FILEIO_INPUT_INVALID] = "File cannot be correctly explained by built-in functions.";
	dictionary[3][TEXT_EXCEPTION_FILEIO_INPUT_HASH_CONFLICT] = "File cannot be correctly validated.";
	dictionary[3][TEXT_EXCEPTION_FILEIO_INPUT_FAILED] = b64.base64_Decode("tsHIoc7EvP7Kp7Dco6zOxLz+sru05tTau/LO3reotPK/qqGj");
	dictionary[3][TEXT_EXCEPTION_FILEIO_OUTPUT_FAILED] = b64.base64_Decode("0LTI687EvP7Kp7Dco6zOxLz+zt63qLTyv6qhow==");
	dictionary[3][TEXT_EXCEPTION_FILEIO_FILE_BROKEN] = b64.base64_Decode("zsS8/tLRvq3L8Lu1u/K48cq9sru85sjdtbHHsLDmsb6how==");

	dictionary[3][TEXT_EXCEPTION_FILEIO_SIGNATURE_CONFLICT] = b64.base64_Decode("zsS8/tWq0qrQxc+itO3O86OsztLDx87et6jR6dakvNPU2NDFz6K1xNX9yLfQ1KOsvNPU2L2r1tXWuaGj");
	dictionary[3][TEXT_EXCEPTION_FILEIO_VALIDATOR_CONFLICT] = b64.base64_Decode("zsS8/sTasr/R6dak0MXPorPlzbujrM7Sw8fO3reo0enWpM7EvP7T0NCn0NSjrLzT1Ni9q9bV1rmhow==");
	dictionary[3][TEXT_EXCEPTION_FILEIO_GAMESETTINGS_CONFLICT] = b64.base64_Decode("zsS8/sTayN3T67Wxx7Cw5rG+yejWw7K7vObI3aOszsS8/s7et6i809TYoaM=");

	
	dictionary[3][TEXT_INFO_GAME_LOADED] = b64.base64_Decode("0tG+rbPJuaa809TYxPq1xNPOz7e9+LbIo6E=");

}


string Game_LocalizationGadget::FwNumConversion::Num2Fw(int x,int minDigit, Game_Localization* encodeSetting) {
	stringstream oss;
	string source, ret = "";
	string chTable[10] = {
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_0),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_1),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_2),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_3),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_4),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_5),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_6),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_7),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_8),
		encodeSetting->lang_GetString(encodeSetting->SYMBOL_FWNUMBER_9)
	};
	int sz;
	oss << x;
	source = oss.str();
	sz = source.length();
	if (sz < minDigit) {
		for (int i = 0; i < minDigit - sz; i++) {
			ret += chTable[0];
		}
	}
	for (int i = 0; i < sz; i++) {
		ret += chTable[source.data()[i] - '0'];
	}
	return ret;
}