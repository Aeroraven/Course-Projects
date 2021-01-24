#include <iostream>
#include <string>
#include <climits> 
#include <stdexcept> 
//************************************
// 全名:  isDigitStr
// 功能: 判断一个字符串是否只包含数字
// 权限:    public 
// 返回:   bool
// 参数: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}
class LinkedListNode { //链表节点
public:
	int data = -1;
	LinkedListNode *successor = nullptr, *predecessor = nullptr; //后继和前驱
};
class LinkedList { //链表
private:
	LinkedListNode *head = nullptr; //头指针
	LinkedListNode *tail = nullptr; //尾指针
	int listSize = 0;

public:
	enum LinkedListException {
		LLExcept_SUCCESS, //成功
		LLExcept_ALLOCATE_FAILURE, //新建节点失败
		LLExcept_EMPTY_LINKEDLIST, //空链表
		LLExcept_INIT_FAILURE, //初始化失败
		LLExcept_INVALID_ARUGMENT //无效参数
	};
	LinkedList();
	~LinkedList();
	void InsertTail(int data, int& errId);
	void RemoveFront(int& errId);
	void Find(int pos, int& result, int& errId);
	void FindReversed(int revPos, int& result, int& errId);
	int Size();

};
class Queue { //队列
private:
	LinkedList List;
public:
	enum QueueException {
		QExcept_SUCCESS, //成功
		QExcept_LINKEDLIST_EXCEPTION, //链表发生错误
		QExcept_EMPTY_QUEUE, //空队列
	};
	void GetFront(int& result, int& errId); 
	void Pop(int& errId);
	void Push(int data, int& errId);
	bool Empty();
};

class BankService_Solution { //银行业务题目
public:
	void Solve();
};

LinkedList::LinkedList() {
	head = new LinkedListNode;
	tail = head;
}
LinkedList::~LinkedList() {
	LinkedListNode *cur = head, *curSucc;
	while (1) {
		curSucc = cur->successor;
		delete cur;
		if (curSucc == nullptr) break;
		cur = curSucc;
	}
}
//************************************
// 全名:  LinkedList::InsertTail
// 功能: 向链表尾部插入元素
// 权限:    public 
// 返回:   void
// 参数: int data 要插入的数据
// 参数: int & errId 状态
//************************************
void LinkedList::InsertTail(int data, int& errId) {
	errId = LLExcept_SUCCESS;
	if (tail == nullptr) {
		errId = LLExcept_INIT_FAILURE;
		return;
	}
	LinkedListNode *newEl = new LinkedListNode;
	if (newEl == nullptr) {
		errId = LLExcept_ALLOCATE_FAILURE;
		return;
	}
	newEl->data = data;
	newEl->predecessor = tail;
	tail->successor = newEl;
	tail = newEl;
	listSize++;
}
//************************************
// 全名:  LinkedList::RemoveFront
// 功能: 删除链表头部的元素
// 权限:    public 
// 返回:   void
// 参数: int & errId 状态码
//************************************
void LinkedList::RemoveFront(int& errId) {
	errId = LLExcept_SUCCESS;
	if (head == nullptr) {
		errId = LLExcept_INIT_FAILURE;
		return;
	}
	if (listSize == 0) {
		errId = LLExcept_EMPTY_LINKEDLIST;
		return;
	}
	else if (listSize == 1) {
		delete head->successor;
		head->successor = nullptr;
		tail = head;
		listSize--;
	}
	else {
		head->successor = head->successor->successor;
		delete head->successor->predecessor;
		head->successor->predecessor = head;
		listSize--;
	}
}
//************************************
// 全名:  LinkedList::Find
// 功能: 查找链表指定位置的元素
// 权限:    public 
// 返回:   void
// 参数: int pos 位置
// 参数: int & result 返回的结果
// 参数: int & errId 状态
//************************************
void LinkedList::Find(int pos, int& result, int& errId) {
	errId = LLExcept_SUCCESS;
	if (pos < 0 || pos >= listSize) {
		errId = LLExcept_INVALID_ARUGMENT;
		return;
	}
	int curPos = 0;
	LinkedListNode* cur = head->successor;
	while (cur != nullptr) {
		if (curPos == pos) {
			result = cur->data;
			return;
		}
		curPos++;
		cur = cur->successor;
	}
}
//************************************
// 全名:  LinkedList::FindReversed
// 功能: 从尾部查找链表指定位置的元素
// 权限:    public 
// 返回:   void
// 参数: int revPos 位置
// 参数: int & result 返回的结果
// 参数: int & errId 状态
//************************************
void LinkedList::FindReversed(int revPos, int& result, int& errId) {
	errId = LLExcept_SUCCESS;
	if (revPos < 0 || revPos >= listSize) {
		errId = LLExcept_INVALID_ARUGMENT;
		return;
	}
	int curPos = 0;
	LinkedListNode* cur = tail->predecessor;
	while (cur != head) {
		if (curPos == revPos) {
			result = cur->data;
			return;
		}
		curPos++;
		cur = cur->predecessor;
	}
}
int LinkedList::Size() {
	return listSize;
}


//************************************
// 全名:  Queue::GetFront
// 功能: 获得队首元素
// 权限:    public 
// 返回:   void
// 参数: int & result 返回值
// 参数: int & errId 状态码
//************************************
void Queue::GetFront(int& result, int& errId) {
	int status;
	if (List.Size()) {
		errId = QExcept_SUCCESS;
		List.Find(0, result, status);
		if (status != LinkedList::LLExcept_SUCCESS) {
			errId = QExcept_LINKEDLIST_EXCEPTION;
			return;
		}
	}
	else {
		errId = QExcept_EMPTY_QUEUE;
		return;
	}
}


//************************************
// 全名:  Queue::Pop
// 功能: 出队列（DeQue)
// 权限:    public 
// 返回:   void
// 参数: int & errId
//************************************
void Queue::Pop(int& errId) {
	int status;
	if (List.Size()) {
		errId = QExcept_SUCCESS;
		List.RemoveFront(status);
		if (status != LinkedList::LLExcept_SUCCESS) {
			errId = QExcept_LINKEDLIST_EXCEPTION;
			return;
		}
	}
	else {
		errId = QExcept_EMPTY_QUEUE;
	}
}

//************************************
// 全名:  Queue::Push
// 功能: 入队列（EnQue)
// 权限:    public 
// 返回:   void
// 参数: int data
// 参数: int & errId
//************************************
void Queue::Push(int data, int& errId) {
	int status;
	errId = QExcept_SUCCESS;
	List.InsertTail(data, status);
	if (status != LinkedList::LLExcept_SUCCESS) {
		errId = QExcept_LINKEDLIST_EXCEPTION;
		return;
	}
}
//************************************
// 全名:  Queue::Empty
// 功能: 判断队列是否为空
// 权限:    public 
// 返回:   bool
//************************************
bool Queue::Empty() {
	return (List.Size() == 0);
}

//************************************
// 全名:  BankService_Solution::Solve
// 功能: 银行业务问题求解
// 权限:    public 
// 返回:   void
//************************************
void BankService_Solution::Solve() {

	Queue First, Second;
	std::string readIn;
	int n, *data, status;
	//输入N值
	while (1) {
		bool temp = true;
		std::cin >> readIn;
		if (isDigitStr(readIn) && readIn != "0") {
			try {
				n = std::stoi(readIn);
			}
			catch (std::out_of_range) {
				std::cout << "错误，数字太大，请重新输入" << std::endl;
				temp = false;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				continue;
			}
			break;
		}
		std::cout << "错误，输入的数字不是正整数！请重新输入" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	n = std::stoi(readIn);

	//输入顾客编号
	data = new int[n];
	if (data==nullptr) {
		std::cout << "错误，内存不足！" << std::endl;
		return;
	}
	bool validFlag = true;
	while (1) {
		validFlag = true;
		for (int i = 0; i < n; i++) {
			std::cin >> readIn;
			if (!isDigitStr(readIn)) {
				std::cout << "错误，输入的不是数字。请重新输入所有顾客编号" << std::endl;
				validFlag = false;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				break;
			}
			data[i] = std::stoi(readIn);
		}
		if (validFlag)break;
	}
	//入队列
	for (int i = 0; i < n; i++) {
		if (data[i] & 1) {
			First.Push(data[i], status);
		}
		else {
			Second.Push(data[i], status);
		}
		if (status != 0) {
			std::cout << "错误，内存不足，队列操作无法进行！" << std::endl;
			return;
		}
	}
	int tempFirst, tempSecond;
	//如果两个队列AB都非空，先从A中弹出1个元素，若A非空，再弹出一个元素，同时从B中弹出一个元素
	while (!First.Empty() && !Second.Empty()) { 
		First.GetFront(tempFirst, status); First.Pop(status);
		std::cout << tempFirst << " ";
		if (!First.Empty()) {
			First.GetFront(tempFirst, status); First.Pop(status);
			std::cout << tempFirst << " ";
		}
		Second.GetFront(tempSecond, status); Second.Pop(status);
		std::cout << tempSecond << " ";
	}
	//若A非空，则按顺序将A中元素输出
	while (!First.Empty()) {
		First.GetFront(tempFirst, status); First.Pop(status);
		std::cout << tempFirst << " ";

	}
	//若B非空，则按顺序将B中元素输出
	while (!Second.Empty()) {
		Second.GetFront(tempSecond, status); Second.Pop(status);
		std::cout << tempSecond << " ";
	}
	delete[] data;
}

int main() {
	BankService_Solution sol;
	sol.Solve();
	std::cout << std::endl;
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
