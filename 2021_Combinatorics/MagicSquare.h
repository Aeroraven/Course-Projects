#pragma once

class MagicSquare;
class MagicSquareAssistant;

//MagicSquare Class: Construct and output the magic square
class MagicSquare {
private:
	int rank = -1; //Rank of the square
	int** square = nullptr; //Matrix of the square
	MagicSquareAssistant* bind_assistant = nullptr;

public:
	void initialize(int arg_rank);
	void deallocate();
	void fill_by_loubere_algo();
	void fill_by_yanghui_algo();
	void fill_by_loubere_algo_detail();
	void fill_by_yanghui_algo_detail();
	void fill_by_yanghui_manual_algo_detail();

	void print_square(int border_only);
	void print_square_yanghui(int border_only);
	void set_assistant(MagicSquareAssistant* x) { bind_assistant = x; }
	int get_rank();

	void reset();
	~MagicSquare();
};


//MagicSquareAssistant Class: Tackle input and output operations
class MagicSquareAssistant {
private:
	MagicSquare magic_square;
public:
	int problem_input();
	void problem_output();
	void problem_output_loubere();
	void problem_output_yanghui();
	void problem_output_yanghui_manual();

	static void interface_gotoxy(int row, int col);
	static void interface_sleep(int ms);
	static void interface_cls();
	static int interface_getch();
	static int interface_getch_ex();
	static bool interface_kbhit();
	
	MagicSquareAssistant() { magic_square.set_assistant(this); }
};
