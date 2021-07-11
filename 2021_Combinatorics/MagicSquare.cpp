#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termio.h>
#include <fcntl.h>
#endif
#include "MagicSquare.h"
using namespace std;
int MagicSquareAssistant:: interface_getch_ex() {
	while (interface_kbhit()) interface_getch();
	return  interface_getch();
}
bool MagicSquareAssistant::interface_kbhit() {
#ifdef _WIN32
	return _kbhit();
#else
	struct termios oldt, newt;
	int ch;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
#endif
}

//Show the detail procedure of La Loubere's algorithm 
void MagicSquare::fill_by_loubere_algo_detail() {
	if (bind_assistant == nullptr) {
		cout << "The function cannot be executed now" << endl;
		return;
	}
	else {
		bind_assistant->interface_cls();
	}
	this->print_square(1);
	if (rank == -1) {
		cout << "Not initialized" << endl;
		return;
	}
	int r = 0;
	int c = rank >> 1;
	int n = rank * rank;
	for (int i = 0; i < n; i++) {
		if (square[r][c]) {
			//If the next cell is occupied, go downward
			r = (r + 2 + rank) % rank;
			c = (c - 1 + rank) % rank;
		}
		//Fill the cell and then go on
		bind_assistant->interface_gotoxy(r * 2 + 1, c * 4+1);
		cout << setw(3) << i + 1 << flush;
		bind_assistant->interface_sleep(200);
		square[r--][c++] = i + 1;
		r += rank;
		r %= rank;
		c %= rank;
	}
	bind_assistant->interface_gotoxy(rank * 2 + 3, 0);
	cout << "构造完成，按任意键继续...";
	bind_assistant-> interface_getch_ex();
}

//Show the detail procedure of Yanghui's algorithm (in optimized method)
void MagicSquare::fill_by_yanghui_algo_detail() {
	if (bind_assistant == nullptr) {
		cout << "The function cannot be executed now" << endl;
		return;
	}
	else {
		bind_assistant->interface_cls();
	}
	this->print_square(1);
	if (rank == -1) {
		cout << "Not initialized" << endl;
		return;
	}
	for (int i = 0; i < rank; i++) {
		for (int j = 0; j < rank; j++) {
			int bound = (rank - 1) / 2;
			//Positioning numbers in the extended grid chart
			int dy = -(bound * 2 - j - i);
			int dx = -i + j;
			//If the cell exceeds the limit of the original chart
			//Then move it inside correspondingly
			if (dy > bound) dy -= rank;
			if (dy < -bound)dy += rank;
			if (dx > bound) dx -= rank;
			if (dx < -bound)dx += rank;
			//Fill in the cell
			bind_assistant->interface_gotoxy((dy + bound) * 2 + 1, (dx + bound) * 4 + 1);
			cout << setw(3) << i * rank + j + 1 << flush;
			bind_assistant->interface_sleep(400);
			square[dy + bound][dx + bound] = i * rank + j + 1;
		}
	}
	bind_assistant->interface_gotoxy(rank * 2 + 3, 0);
	cout << "构造完成，按任意键继续...";
	bind_assistant-> interface_getch_ex();
}

//Show the detail procedure of Yanghui's algorithm (in original manual method)
void MagicSquare::fill_by_yanghui_manual_algo_detail() {
	if (bind_assistant == nullptr) {
		cout << "The function cannot be executed now" << endl;
		return;
	}
	else {
		bind_assistant->interface_cls();
	}
	this->print_square_yanghui(1);
	if (rank == -1) {
		cout << "Not initialized" << endl;
		return;
	}
	for (int i = 0; i < rank; i++) {
		for (int j = 0; j < rank; j++) {
			int bound = (rank - 1) / 2;
			//Positioning numbers in the extended grid chart
			int dy = -(bound * 2 - j - i);
			int dx = -i + j;
			//Fill in the cell
			bind_assistant->interface_gotoxy((dy + 2*bound) * 2 + 1, (dx + 2*bound) * 4 + 1);
			cout << setw(3) << i * rank + j + 1 << flush;
			bind_assistant->interface_sleep(200);
			//square[dy + bound][dx + bound] = i * rank + j + 1;
		}
	}
	bind_assistant->interface_gotoxy(rank * 4 + 3, 0);
	cout << "步骤1-斜排过程完成，按任意键进行第2步...";
	bind_assistant-> interface_getch_ex();

	bool moves = false;
	for (int i = 0; i < rank; i++) {
		for (int j = 0; j < rank; j++) {
			moves = false;
			int bound = (rank - 1) / 2;
			//Positioning numbers in the extended grid chart
			int dy = -(bound * 2 - j - i);
			int dx = -i + j;
			int ody = dy, odx = dx;
			//Fill in the cell
			if (dy > bound) dy -= rank, moves = true;
			if (dy < -bound)dy += rank, moves = true;
			if (dx > bound) dx -= rank, moves = true;
			if (dx < -bound)dx += rank, moves = true;
			if (!moves)continue;
			bind_assistant->interface_gotoxy((ody + 2 * bound) * 2 + 1, (odx + 2 * bound) * 4 + 1);
			cout << setw(3) << " ";
			bind_assistant->interface_gotoxy((dy + 2 * bound) * 2 + 1, (dx + 2 * bound) * 4 + 1);
			cout << setw(3) << i * rank + j + 1 << flush;
			bind_assistant->interface_sleep(200);
			//square[dy + bound][dx + bound] = i * rank + j + 1;
		}
	}
	bind_assistant->interface_gotoxy(rank * 4 + 3, 0);
	cout << "步骤2结束                                 " << endl;
	cout << "人工构造过程模拟结束，按任意键继续...";
	bind_assistant-> interface_getch_ex();

}

void MagicSquareAssistant::problem_output_loubere() {
	magic_square.reset();
	magic_square.fill_by_loubere_algo_detail();
}

void MagicSquareAssistant::problem_output_yanghui() {
	magic_square.reset();
	magic_square.fill_by_yanghui_algo_detail();
}

void MagicSquareAssistant::problem_output_yanghui_manual() {
	magic_square.reset();
	magic_square.fill_by_yanghui_manual_algo_detail();
}

int MagicSquareAssistant:: interface_getch() {
#ifdef _WIN32
	int ch;
	ch = _getch();
	return ch;
#else
	struct termios tm, tm_old;
	int fd = 0, ch;
	if (tcgetattr(fd, &tm) < 0) {
		return -1;
	}
	tm_old = tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd, TCSANOW, &tm) < 0) {
		return -1;
	}
	ch = getchar();
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
		return -1;
	}
	return ch;
#endif // _WIN32

	
}

void MagicSquareAssistant::interface_cls(){
#ifdef _WIN32
	system("cls");
#else
	cout << "\033c";
#endif
}

void MagicSquareAssistant::interface_sleep(int ms) {
	chrono::milliseconds x(ms);
	this_thread::sleep_for(x);
}

void MagicSquareAssistant::interface_gotoxy(int row, int col) {
#ifdef _WIN32
	COORD coord;
	coord.X = col;
	coord.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
	printf("%c[%d;%df", 0x1b, row+1, col+1);
#endif
}

//Reset the magic square matrix with zero
void MagicSquare::reset() {
	for (int i = 0; i < rank; i++) {
		for (int j = 0; j < rank; j++) {
			square[i][j] = 0;
		}
	}
}
//Get the rank of the magic square matrix
int MagicSquare::get_rank() {
	return rank;
}

//Initialize the magic square class
//Argument: int arg_rank - rank of the magic square
void MagicSquare::initialize(int arg_rank) {
	if (square != nullptr)
		deallocate();
	if (!(arg_rank & 1)) {
		cout << "Invalid input" << endl;
		return;
	}
	rank = arg_rank;
	square = new int* [rank];
	for (int i = 0; i < rank; i++) {
		square[i] = new int[rank];
		for (int j = 0; j < rank; j++) {
			square[i][j] = 0;
		}
	}
}

//Deallocate the arrays allocated in the magic square class
void MagicSquare::deallocate() {
	for (int i = 0; i < rank; i++) {
		delete[] square[i];
	}
	delete[] square;
}

MagicSquare::~MagicSquare() {
	deallocate();
}

//Solve the problem via La Loubere Algorithm
void MagicSquare::fill_by_loubere_algo() {
	if (rank == -1) {
		cout << "Not initialized" << endl;
		return;
	}
	int r = 0;
	int c = rank >> 1;
	int n = rank * rank;
	for (int i = 0; i < n; i++) {
		if (square[r][c]) {
			//If the next cell is occupied, go downward
			r = (r + 2 + rank) % rank;
			c = (c - 1 + rank) % rank;
		}
		//Continue to the next cell
		square[r--][c++] = i + 1;
		r += rank;
		r %= rank;
		c %= rank;
	}
}
//Solve the problem via Yanghui Algorithm
void MagicSquare::fill_by_yanghui_algo() {
	if (rank == -1) {
		cout << "Not initialized" << endl;
		return;
	}
	for (int i = 0; i < rank; i++) {
		for (int j = 0; j < rank; j++) {
			int bound = (rank - 1) / 2;
			//Positioning numbers in the extended grid chart
			int dy = -(bound * 2 - j - i);
			int dx = -i + j;
			//If the cell exceeds the limit of the original chart
			//Then move it inside correspondingly
			if (dy > bound) dy -= rank;
			if (dy < -bound)dy += rank;
			if (dx > bound) dx -= rank;
			if (dx < -bound)dx += rank;
			//Fill in the cell
			square[dy + bound][dx + bound] = i * rank + j + 1;
		}
	}
}
//Output the matrix
void MagicSquare::print_square(int border_only) {
	cout << "-";
	for (int j = 0; j < rank; j++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < rank; i++) {
		cout << "|";
		for (int j = 0; j < rank; j++) {
			if (border_only)cout << setw(3) << " " << "|";
			else cout << setw(3) << square[i][j] << "|";
		}
		cout << endl;
		cout << "-";
		for (int j = 0; j < rank; j++) {
			cout << "----";
		}
		cout << endl;
	}
	cout << endl;
}
//Print the matrix used in original Yanghui's algorithm
void MagicSquare::print_square_yanghui(int border_only) {
	int rank2 = rank + (rank - 1);
	cout << "-";
	for (int j = 0; j < rank2; j++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < rank2; i++) {
		cout << "|";
		for (int j = 0; j < rank2; j++) {
			if (border_only)cout << setw(3) << " " << "|";
			else cout << setw(3) << square[i][j] << "|";
		}
		cout << endl;
		cout << "-";
		for (int j = 0; j < rank2; j++) {
			cout << "----";
		}
		cout << endl;
	}
	cout << endl;
}
//Tackle the input (including invalid inputs)
int MagicSquareAssistant::problem_input() {
	interface_cls();
	int r;
	int mode = 0;
	cout << "===================================================" << endl;
	cout << "                 奇数幻方生成器" << endl;
	cout << "===================================================" << endl;
	cout << "1 - 仅输出幻方的构造结果" << endl;
	cout << "2 - 输出LeLoubere幻方的构造过程" << endl;
	cout << "3 - 输出杨辉法幻方的构造过程 (算法填充过程)" << endl;
	cout << "4 - 输出杨辉法幻方的构造过程 (人工填充过程)" << endl;
	cout << "0 - 退出" << endl;
	cout << "===================================================" << endl;
	cout << "选项3将斜排过程与最终填充过程进行整合，\n如想看原始的杨辉算法过程，请选择选项4" << endl;
	cout << "选择选项2~4时，需要保证控制台大小足够大，否则无法正常显示" << endl;
	cout << "===================================================" << endl;

	cout << "请输入选项：";
	while (1) {
		cin >> mode;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(0x7fffffff, '\n');
			cout << "输入无效，请重新输入。请保证输入的数值为整数。" << endl;
			continue;
		}
		else if (mode != 1 && mode != 2 && mode!=3 && mode!=4 && mode!=0) {
			cout << "输入无效，请重新输入。请保证输入的数值为0~4." << endl;
			continue;
		}
		break;
	}
	if (mode == 0) {
		return 0;
	}

	if (mode == 4) {
		cout << "受限于控制台宽度，在幻方阶数过大时，视觉效果可能不佳" << endl;
	}
	cout << "请输入X值，计算2X+1阶幻方,(X为1~9):";
	while (1) {
		cin >> r;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(0x7fffffff, '\n');
			cout << "输入无效，请重新输入。请保证输入的数值为整数。" << endl;
			continue;
		}
		else if (r < 1 || r>9) {
			cout << "输入无效，请重新输入。请保证输入的数值在1~9范围内。" << endl;
			continue;
		}
		break;
	}
	magic_square.initialize(r * 2 + 1);
	cout << endl;
	return mode;
}

//Output the result of two algorithm
void MagicSquareAssistant::problem_output() {
	interface_cls();

	magic_square.reset();
	magic_square.fill_by_yanghui_algo();
	cout << "[杨辉构造法的结果]" << endl;
	cout << magic_square.get_rank() << "阶幻方的一个结果是:" << endl;
	magic_square.print_square(0);

	magic_square.reset();
	magic_square.fill_by_loubere_algo();
	cout << "[La Loubere的结果]" << endl;
	cout << magic_square.get_rank() << "阶幻方的一个结果是:" << endl;
	magic_square.print_square(0);

	cout << "构造完成，按任意键继续...";
	interface_getch_ex();
}

//Main function
int main() {
	MagicSquareAssistant x;
	while (1) {
		int opt = x.problem_input();
		if (opt == 1) {
			x.problem_output();
		}
		else if (opt == 2) {
			x.problem_output_loubere();
		}
		else if (opt == 3) {
			x.problem_output_yanghui();
		}
		else if (opt == 4) {
			x.problem_output_yanghui_manual();
		}
		else if (opt == 0) {
			return 0;
		}
	}
	
	
	return 0;
}
