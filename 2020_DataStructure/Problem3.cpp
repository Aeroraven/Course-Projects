#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <string>
#include <climits> 
#include <stdexcept> 

//************************************
// 全名:  isDigitStr
// 功能: 判断一个字符串是否是数字字符串
// 权限:    public 
// 返回:   bool
// 参数: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}

struct Pair { //点对
	int x, y;//坐标信息
	bool operator ==(const Pair& p) { //判断两点是否相同
		return(x == p.x&&y == p.y);
	}
};
template<class Type>class LinkedListNode { //链表结点
public:
	Type data; //数据域
	LinkedListNode<Type> *successor = nullptr, *predecessor = nullptr;//指针域
};
template<class Type> class Stack { //链式栈
public:
	LinkedListNode<Type> *head = nullptr;//链表头节点
	LinkedListNode<Type> *tail = nullptr; //链表尾部结点
	int stackSize = 0;//栈大小

	Stack(); //构造函数
	~Stack();//析构函数
	void GetTop(Type& result); //若栈非空，获得栈顶元素
	void Push(const Type& data); //将元素入栈
	void Pop(); //若栈非空，删除栈顶元素
};
class Maze {//迷宫游戏求解部分
public:
	typedef Stack<Pair> LinkedList ;

	bool** map; //存储迷宫地图
	bool** sel; //保存DFS过程中的访问状态
	int rows = 0, cols = 0; //迷宫的行和列
	LinkedList route;//迷宫答案路径
	bool complete = false; //完成状态

	void dfs(Pair entrance, Pair exit);//求解迷宫路径
	void printMap(); //输出答案地图和答案路径
	void generateMap();//随机生成地图
	void presetMap();//加载预置地图1
	void presetMap2();//加载预置地图2
	void presetMap3();//加载预置地图3
	void presetMap4();//加载预置地图4
	void customizeMap();//自定义地图
	void selectMap();//显示地图选择页面，用户选择指定地图
};
template<class Type> Stack<Type>::Stack() {
	head = new LinkedListNode<Type>;
	tail = head;
}
template<class Type> Stack<Type>::~Stack() {
	LinkedListNode<Type> *tmp = head, *tmpNext = head->successor;
	while (1) {
		tmpNext = tmp->successor;
		delete tmp;
		if (tmpNext == nullptr) break;
		tmp = tmpNext;
	}
}
//************************************
// 全名:  Stack::GetTop
// 功能: 若栈非空，返回栈顶元素
// 权限:    public 
// 返回:   void
// 参数: Type & result 栈顶元素返回值
//************************************
template<class Type> void Stack<Type>::GetTop(Type& result) {
	if (stackSize) {
		result = tail->data;
	}
}
//************************************
// 全名:  Stack::Push
// 功能: 将指定元素入栈
// 权限:    public 
// 返回:   void
// 参数: const Type & data 要入栈的元素
//************************************
template<class Type> void Stack<Type>::Push(const Type& data) {
	LinkedListNode<Type> *newElement = new LinkedListNode<Type>;
	if (newElement) {
		newElement->data = data;
		newElement->successor = nullptr;
		newElement->predecessor = tail;
		tail->successor = newElement;
		tail = newElement;
		stackSize++;
	}
}
//************************************
// 全名:  Stack::Pop
// 功能: 若栈非空，则删除栈顶元素
// 权限:    public 
// 返回:   void
//************************************
template<class Type> void Stack<Type>::Pop() {
	if (stackSize) {
		LinkedListNode<Type> *pred = tail->predecessor;
		delete tail;
		tail = pred;
		pred->successor = nullptr;
		stackSize--;
	}
}
//************************************
// 全名:  Maze::selectMap
// 功能: 选择地图界面
// 权限:    public 
// 返回:   void
//************************************
void Maze::selectMap() {
	std::cout << std::endl;
	std::cout << "**                 勇闯迷宫游戏                        **" << std::endl;
	std::cout << "=========================================================" << std::endl;
	std::cout << "**                 0 --- 自定义地图                    **" << std::endl;
	std::cout << "**                 1 --- 随机地图(不保证有解)          **" << std::endl;
	std::cout << "**                 2 --- 样例地图 #1                   **" << std::endl;
	std::cout << "**                 3 --- 样例地图 #2                   **" << std::endl;
	std::cout << "**                 4 --- 样例地图 #3 (长宽不同)        **" << std::endl;
	std::cout << "**                 5 --- 样例地图 #4 (迷宫无解)        **" << std::endl;
	std::cout << "=========================================================" << std::endl << std::endl;
	std::cout << "请选择迷宫地图样式：";
	std::string readIn;
	while (1) {
		std::cin >> readIn;
		if (readIn == "0") {
			customizeMap();
		}
		else if (readIn == "1") {
			generateMap();
		}
		else if (readIn == "2") {
			presetMap();
		}
		else if (readIn == "3") {
			presetMap2();
		}
		else if (readIn == "4") {
			presetMap3();
		}
		else if (readIn == "5") {
			presetMap4();
		}
		else {
			std::cout << "输入的序号无效，请选择迷宫地图样式:";
			continue;
		}
		std::cout << std::endl;
		break;
	}
}
//************************************
// 全名:  Maze::customizeMap
// 功能: 自定义地图功能
// 权限:    public 
// 返回:   void
//************************************
void Maze::customizeMap() {
	std::string readIn;
	while (1) {
		std::cout << "请输入迷宫行数（输入大于2的数字）:";
		std::cin >> readIn;
		if (isDigitStr(readIn) && readIn != "0"&&readIn!="1"&&readIn!="2") {
			try {
				rows = std::stoi(readIn);
				if (rows > 50) {
					std::cout << "数字太大，请重新输入" << std::endl;
					continue;
				}
			}
			catch (std::out_of_range) {
				std::cout << "数字太大，请重新输入" << std::endl;
				continue;
			}
			break;
		}
		else {
			std::cout << "输入数字无效，请重新输入" << std::endl;
		}
	}

	while (1) {
		std::cout << "请输入迷宫列数（输入大于2的数字）:";
		std::cin >> readIn;
		if (isDigitStr(readIn) && readIn != "0"&&readIn != "1"&&readIn != "2") {
			try {
				cols = std::stoi(readIn);
				if (rows > 50) {
					std::cout << "数字太大，请重新输入" << std::endl;
					continue;
				}
			}
			catch (std::out_of_range) {
				std::cout << "数字太大，请重新输入" << std::endl;
				continue;
			}
			break;
		}
		else {
			std::cout << "输入数字无效，请重新输入" << std::endl;
		}
	}
	map = new bool*[rows];
	sel = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new bool[cols];
		sel[i] = new bool[cols];
	}
	std::cout << "请输入每行的迷宫样式：#表示该处为墙，0表示该处无障碍 (不为#的字符将视为该处无障碍）。" << std::endl;
	for (int i = 0; i < rows; i++) {
		while (1) {
			std::cout << "输入第" << i << "行的迷宫样式：";
			std::cin >> readIn;
			if (readIn.size() != cols) {
				std::cout << "输入格式无效，请重新输入" << std::endl;
				continue;
			}
			for (int j = 0; j < cols; j++) {
				if (readIn[j] == '#') {
					map[i][j] = 0;
				}
				else if (readIn[j] == '0') {
					map[i][j] = 1;
				}
				else {
					map[i][j] = 1;
				}
				sel[i][j] = 0;
			}
			break;
		}
	}
}
//************************************
// 全名:  Maze::generateMap
// 功能: 加载随机地图
// 权限:    public 
// 返回:   void
//************************************
void Maze::generateMap() {
	srand(time(NULL));
	rows = 10;
	cols = 10;
	map = new bool*[rows];
	sel = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new bool[cols];
		sel[i] = new bool[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int k = rand() % 100;
			map[i][j] = k < 80;
			sel[i][j] = false;
		}
	}

	for (int i = 0; i < rows; i++) {
		map[i][0] = 0;
		map[i][cols - 1] = 0;
	}
	for (int i = 0; i < cols; i++) {
		map[cols - 1][i] = 0;
		map[0][i] = 0;
	}
	map[rows - 2][cols - 2] = 1;
}
//************************************
// 全名:  Maze::presetMap2
// 功能: 使用2号预置地图
// 权限:    public 
// 返回:   void
//************************************
void Maze::presetMap2() {
	rows = 7;
	cols = 7;
	map = new bool*[rows];
	sel = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new bool[cols];
		sel[i] = new bool[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sel[i][j] = false;
			map[i][j] = false;
		}
	}
	map[1][1] = true;
	map[2][1] = true;
	map[3][1] = true;
	map[4][1] = true;
	map[5][1] = true;
	map[3][2] = true;
	map[3][3] = true;
	map[4][3] = true;
	map[5][3] = true;
	map[4][5] = true;
	map[5][5] = true;
	map[1][3] = true;
	map[1][4] = true;
	map[1][5] = true;
	map[2][3] = true;
	map[3][5] = true;
	map[2][5] = true;
}
//************************************
// 全名:  Maze::presetMap3
// 功能: 使用3号预置地图
// 权限:    public 
// 返回:   void
//************************************
void Maze::presetMap3() {
	rows = 11;
	cols = 9;
	map = new bool*[rows];
	sel = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new bool[cols];
		sel[i] = new bool[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sel[i][j] = false;
			map[i][j] = false;
		}
	}
	std::string readIn[11] = {
		"#########",
		"#0#00000#",
		"#0#0#0#0#",
		"#000#0#0#",
		"#0#0#0#0#",
		"#0#0#0#0#",
		"#0#00#00#",
		"#0##0#0##",
		"#0000#0##",
		"####0#00#",
		"#########"
	};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (readIn[i][j] == '#') {
				map[i][j] = 0;
			}
			else if (readIn[i][j] == '0') {
				map[i][j] = 1;
			}
			else {
				map[i][j] = 1;
			}
			sel[i][j] = 0;
		
		}
	}
}
//************************************
// 全名:  Maze::presetMap4
// 功能: 使用4号预置地图
// 权限:    public 
// 返回:   void
//************************************
void Maze::presetMap4() {
	rows = 11;
	cols = 9;
	map = new bool*[rows];
	sel = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new bool[cols];
		sel[i] = new bool[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sel[i][j] = false;
			map[i][j] = false;
		}
	}
	std::string readIn[11] = {
		"#########",
		"#0#00000#",
		"#0000000#",
		"#000#0#0#",
		"#0#0#0#0#",
		"#0#0#0###",
		"#0#00#00#",
		"#0##0####",
		"#0000#0##",
		"##0#0#00#",
		"#########"
	};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (readIn[i][j] == '#') {
				map[i][j] = 0;
			}
			else if (readIn[i][j] == '0') {
				map[i][j] = 1;
			}
			else {
				map[i][j] = 1;
			}
			sel[i][j] = 0;

		}
	}
}
//************************************
// 全名:  Maze::presetMap
// 功能: 使用1号预置地图
// 权限:    public 
// 返回:   void
//************************************
void Maze::presetMap() {
	rows = 7;
	cols = 7;
	map = new bool*[rows];
	sel = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new bool[cols];
		sel[i] = new bool[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sel[i][j] = false;
			map[i][j] = false;
		}
	}
	map[1][1] = true;
	map[2][1] = true;
	map[3][1] = true;
	map[4][1] = true;
	map[5][1] = true;
	map[3][2] = true;
	map[3][3] = true;
	map[4][3] = true;
	map[5][3] = true;
	map[4][4] = true;
	map[4][5] = true;
	map[5][5] = true;

	map[1][3] = true;
	map[1][4] = true;
	map[1][5] = true;
	map[2][3] = true;
	map[3][5] = true;
}
//************************************
// 全名:  Maze::dfs
// 功能: 使用DFS求解迷宫路径
// 权限:    public 
// 返回:   void
// 参数: Pair entrance 迷宫起点
// 参数: Pair exit 迷宫终点
//************************************
void Maze::dfs(Pair entrance, Pair exit) {
	//表示visit的数组sel已经预先清零

	Stack<Pair> st; //储存DFS路径上的结点
	Stack<int> directionSt; //储存DFS路径时的结点的下一探查方向（0-下/1-右/2-左/3-上/4-所有方向均已经探查）
	Pair cur; //表示当前DFS的结点
	int curDirection; //表示当前DFS结点的下一探查方向信息
	st.Push(entrance);//将起点作为第一个访问的结点
	directionSt.Push(0);
	route.Push(entrance);
	while (st.stackSize) { //栈中还有结点，即DFS未结束
		st.GetTop(cur);
		directionSt.GetTop(curDirection); 
		sel[cur.x][cur.y] = true;//访问当前结点
		if (cur == exit) { //当前结点为出口表示DFS到达终点，退出
			break;
		}
		st.Pop();
		directionSt.Pop();
		if (curDirection <= 3) {
			st.Push(cur);
			directionSt.Push(curDirection + 1); //探查该点的下一方向
		}
		else { //该点所有方向已经完成探查
			sel[cur.x][cur.y] = false;
			route.Pop();
		}

		if (curDirection == 0) {
			if (cur.x < rows - 1) { //访问下方结点
				if (map[cur.x + 1][cur.y] && !sel[cur.x + 1][cur.y]) { //判断该点是否可访问（即是否未被访问且该点是否可行）
					st.Push({ cur.x + 1,cur.y });
					directionSt.Push(0);
					route.Push({ cur.x + 1,cur.y });
					continue;
				}
			}
		}
		if (curDirection == 3) { //访问上方结点
			if (cur.x > 0) {
				if (map[cur.x - 1][cur.y] && !sel[cur.x - 1][cur.y]) {
					st.Push({ cur.x - 1,cur.y });
					directionSt.Push(0);
					route.Push({ cur.x - 1,cur.y });
					continue;
				}
			}
		}
		if (curDirection == 2) {//访问左侧结点
			if (cur.y > 0) {
				if (map[cur.x][cur.y - 1] && !sel[cur.x][cur.y - 1]) {
					st.Push({ cur.x,cur.y - 1 });
					directionSt.Push(0);
					route.Push({ cur.x,cur.y - 1 });
					continue;
				}
			}
		}
		if (curDirection == 1) {//访问右侧结点
			if (cur.y < cols - 1) {
				if (map[cur.x][cur.y + 1] && !sel[cur.x][cur.y + 1]) {
					st.Push({ cur.x,cur.y + 1 });
					directionSt.Push(0);
					route.Push({ cur.x,cur.y + 1 });
					continue;
				}
			}
		}
		
	}
}
//************************************
// 全名:  Maze::printMap
// 功能: 输出迷宫地图
// 权限:    public 
// 返回:   void
//************************************
void Maze::printMap() {
	//输出地图
	std::cout << "迷宫地图:" << std::endl << std::endl << "   \t";

	for (int i = 0; i < cols; i++) {
		std::cout << i << "列\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {
		std::cout << i << "行\t";
		for (int j = 0; j < cols; j++) {
			if (!map[i][j]) {
				std::cout << "#\t";
			}
			else if (sel[i][j]) {
				std::cout << "x\t";
			}
			else {
				std::cout << "0\t";
			}
		}
		std::cout << std::endl << std::endl;
	}
	//输出路径
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "迷宫路径:" << std::endl << std::endl;
	if (route.head->successor == nullptr) { //路径为空
		std::cout << "(起点到终点不存在连通路径)" << std::endl;
	}
	else {
		for (LinkedListNode<Pair> *i = route.head->successor; i != nullptr; i = i->successor) {
			std::cout << "(" << i->data.x << "," << i->data.y << ")";
			if (i->successor != nullptr) {
				std::cout << " ---> ";
			}
		}
	}
	std::cout << std::endl;
}

int main() {
	Maze problem;
	problem.selectMap(); //选择地图（输入）
	Pair start = { 1,1 }, end = { problem.rows-2,problem.cols-2 }; //设定终点和起点
	problem.dfs(start, end); //开始求解
	problem.printMap(); //输出答案
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
