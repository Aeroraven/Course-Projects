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
// ȫ��:  isDigitStr
// ����: �ж�һ���ַ����Ƿ��������ַ���
// Ȩ��:    public 
// ����:   bool
// ����: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}

struct Pair { //���
	int x, y;//������Ϣ
	bool operator ==(const Pair& p) { //�ж������Ƿ���ͬ
		return(x == p.x&&y == p.y);
	}
};
template<class Type>class LinkedListNode { //������
public:
	Type data; //������
	LinkedListNode<Type> *successor = nullptr, *predecessor = nullptr;//ָ����
};
template<class Type> class Stack { //��ʽջ
public:
	LinkedListNode<Type> *head = nullptr;//����ͷ�ڵ�
	LinkedListNode<Type> *tail = nullptr; //����β�����
	int stackSize = 0;//ջ��С

	Stack(); //���캯��
	~Stack();//��������
	void GetTop(Type& result); //��ջ�ǿգ����ջ��Ԫ��
	void Push(const Type& data); //��Ԫ����ջ
	void Pop(); //��ջ�ǿգ�ɾ��ջ��Ԫ��
};
class Maze {//�Թ���Ϸ��ⲿ��
public:
	typedef Stack<Pair> LinkedList ;

	bool** map; //�洢�Թ���ͼ
	bool** sel; //����DFS�����еķ���״̬
	int rows = 0, cols = 0; //�Թ����к���
	LinkedList route;//�Թ���·��
	bool complete = false; //���״̬

	void dfs(Pair entrance, Pair exit);//����Թ�·��
	void printMap(); //����𰸵�ͼ�ʹ�·��
	void generateMap();//������ɵ�ͼ
	void presetMap();//����Ԥ�õ�ͼ1
	void presetMap2();//����Ԥ�õ�ͼ2
	void presetMap3();//����Ԥ�õ�ͼ3
	void presetMap4();//����Ԥ�õ�ͼ4
	void customizeMap();//�Զ����ͼ
	void selectMap();//��ʾ��ͼѡ��ҳ�棬�û�ѡ��ָ����ͼ
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
// ȫ��:  Stack::GetTop
// ����: ��ջ�ǿգ�����ջ��Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: Type & result ջ��Ԫ�ط���ֵ
//************************************
template<class Type> void Stack<Type>::GetTop(Type& result) {
	if (stackSize) {
		result = tail->data;
	}
}
//************************************
// ȫ��:  Stack::Push
// ����: ��ָ��Ԫ����ջ
// Ȩ��:    public 
// ����:   void
// ����: const Type & data Ҫ��ջ��Ԫ��
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
// ȫ��:  Stack::Pop
// ����: ��ջ�ǿգ���ɾ��ջ��Ԫ��
// Ȩ��:    public 
// ����:   void
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
// ȫ��:  Maze::selectMap
// ����: ѡ���ͼ����
// Ȩ��:    public 
// ����:   void
//************************************
void Maze::selectMap() {
	std::cout << std::endl;
	std::cout << "**                 �´��Թ���Ϸ                        **" << std::endl;
	std::cout << "=========================================================" << std::endl;
	std::cout << "**                 0 --- �Զ����ͼ                    **" << std::endl;
	std::cout << "**                 1 --- �����ͼ(����֤�н�)          **" << std::endl;
	std::cout << "**                 2 --- ������ͼ #1                   **" << std::endl;
	std::cout << "**                 3 --- ������ͼ #2                   **" << std::endl;
	std::cout << "**                 4 --- ������ͼ #3 (����ͬ)        **" << std::endl;
	std::cout << "**                 5 --- ������ͼ #4 (�Թ��޽�)        **" << std::endl;
	std::cout << "=========================================================" << std::endl << std::endl;
	std::cout << "��ѡ���Թ���ͼ��ʽ��";
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
			std::cout << "����������Ч����ѡ���Թ���ͼ��ʽ:";
			continue;
		}
		std::cout << std::endl;
		break;
	}
}
//************************************
// ȫ��:  Maze::customizeMap
// ����: �Զ����ͼ����
// Ȩ��:    public 
// ����:   void
//************************************
void Maze::customizeMap() {
	std::string readIn;
	while (1) {
		std::cout << "�������Թ��������������2�����֣�:";
		std::cin >> readIn;
		if (isDigitStr(readIn) && readIn != "0"&&readIn!="1"&&readIn!="2") {
			try {
				rows = std::stoi(readIn);
				if (rows > 50) {
					std::cout << "����̫������������" << std::endl;
					continue;
				}
			}
			catch (std::out_of_range) {
				std::cout << "����̫������������" << std::endl;
				continue;
			}
			break;
		}
		else {
			std::cout << "����������Ч������������" << std::endl;
		}
	}

	while (1) {
		std::cout << "�������Թ��������������2�����֣�:";
		std::cin >> readIn;
		if (isDigitStr(readIn) && readIn != "0"&&readIn != "1"&&readIn != "2") {
			try {
				cols = std::stoi(readIn);
				if (rows > 50) {
					std::cout << "����̫������������" << std::endl;
					continue;
				}
			}
			catch (std::out_of_range) {
				std::cout << "����̫������������" << std::endl;
				continue;
			}
			break;
		}
		else {
			std::cout << "����������Ч������������" << std::endl;
		}
	}
	map = new bool*[rows];
	sel = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		map[i] = new bool[cols];
		sel[i] = new bool[cols];
	}
	std::cout << "������ÿ�е��Թ���ʽ��#��ʾ�ô�Ϊǽ��0��ʾ�ô����ϰ� (��Ϊ#���ַ�����Ϊ�ô����ϰ�����" << std::endl;
	for (int i = 0; i < rows; i++) {
		while (1) {
			std::cout << "�����" << i << "�е��Թ���ʽ��";
			std::cin >> readIn;
			if (readIn.size() != cols) {
				std::cout << "�����ʽ��Ч������������" << std::endl;
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
// ȫ��:  Maze::generateMap
// ����: ���������ͼ
// Ȩ��:    public 
// ����:   void
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
// ȫ��:  Maze::presetMap2
// ����: ʹ��2��Ԥ�õ�ͼ
// Ȩ��:    public 
// ����:   void
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
// ȫ��:  Maze::presetMap3
// ����: ʹ��3��Ԥ�õ�ͼ
// Ȩ��:    public 
// ����:   void
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
// ȫ��:  Maze::presetMap4
// ����: ʹ��4��Ԥ�õ�ͼ
// Ȩ��:    public 
// ����:   void
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
// ȫ��:  Maze::presetMap
// ����: ʹ��1��Ԥ�õ�ͼ
// Ȩ��:    public 
// ����:   void
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
// ȫ��:  Maze::dfs
// ����: ʹ��DFS����Թ�·��
// Ȩ��:    public 
// ����:   void
// ����: Pair entrance �Թ����
// ����: Pair exit �Թ��յ�
//************************************
void Maze::dfs(Pair entrance, Pair exit) {
	//��ʾvisit������sel�Ѿ�Ԥ������

	Stack<Pair> st; //����DFS·���ϵĽ��
	Stack<int> directionSt; //����DFS·��ʱ�Ľ�����һ̽�鷽��0-��/1-��/2-��/3-��/4-���з�����Ѿ�̽�飩
	Pair cur; //��ʾ��ǰDFS�Ľ��
	int curDirection; //��ʾ��ǰDFS������һ̽�鷽����Ϣ
	st.Push(entrance);//�������Ϊ��һ�����ʵĽ��
	directionSt.Push(0);
	route.Push(entrance);
	while (st.stackSize) { //ջ�л��н�㣬��DFSδ����
		st.GetTop(cur);
		directionSt.GetTop(curDirection); 
		sel[cur.x][cur.y] = true;//���ʵ�ǰ���
		if (cur == exit) { //��ǰ���Ϊ���ڱ�ʾDFS�����յ㣬�˳�
			break;
		}
		st.Pop();
		directionSt.Pop();
		if (curDirection <= 3) {
			st.Push(cur);
			directionSt.Push(curDirection + 1); //̽��õ����һ����
		}
		else { //�õ����з����Ѿ����̽��
			sel[cur.x][cur.y] = false;
			route.Pop();
		}

		if (curDirection == 0) {
			if (cur.x < rows - 1) { //�����·����
				if (map[cur.x + 1][cur.y] && !sel[cur.x + 1][cur.y]) { //�жϸõ��Ƿ�ɷ��ʣ����Ƿ�δ�������Ҹõ��Ƿ���У�
					st.Push({ cur.x + 1,cur.y });
					directionSt.Push(0);
					route.Push({ cur.x + 1,cur.y });
					continue;
				}
			}
		}
		if (curDirection == 3) { //�����Ϸ����
			if (cur.x > 0) {
				if (map[cur.x - 1][cur.y] && !sel[cur.x - 1][cur.y]) {
					st.Push({ cur.x - 1,cur.y });
					directionSt.Push(0);
					route.Push({ cur.x - 1,cur.y });
					continue;
				}
			}
		}
		if (curDirection == 2) {//���������
			if (cur.y > 0) {
				if (map[cur.x][cur.y - 1] && !sel[cur.x][cur.y - 1]) {
					st.Push({ cur.x,cur.y - 1 });
					directionSt.Push(0);
					route.Push({ cur.x,cur.y - 1 });
					continue;
				}
			}
		}
		if (curDirection == 1) {//�����Ҳ���
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
// ȫ��:  Maze::printMap
// ����: ����Թ���ͼ
// Ȩ��:    public 
// ����:   void
//************************************
void Maze::printMap() {
	//�����ͼ
	std::cout << "�Թ���ͼ:" << std::endl << std::endl << "   \t";

	for (int i = 0; i < cols; i++) {
		std::cout << i << "��\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {
		std::cout << i << "��\t";
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
	//���·��
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "�Թ�·��:" << std::endl << std::endl;
	if (route.head->successor == nullptr) { //·��Ϊ��
		std::cout << "(��㵽�յ㲻������ͨ·��)" << std::endl;
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
	problem.selectMap(); //ѡ���ͼ�����룩
	Pair start = { 1,1 }, end = { problem.rows-2,problem.cols-2 }; //�趨�յ�����
	problem.dfs(start, end); //��ʼ���
	problem.printMap(); //�����
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
