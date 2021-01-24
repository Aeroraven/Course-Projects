#include <iostream>
#include <string>
#include <climits> 
template<class Type> class LinkedListNode; //链表结点
template<class Type> class LinkedListIterator; //链表迭代器(游标)
template<class Type> class LinkedList; //链表对象

template<class Type> class LinkedListIterator {//链表迭代器
	friend class LinkedListNode<Type>;
	friend class LinkedList<Type>;
private:
	LinkedListNode<Type>* currentPosition; //游标当前指向的结点
	const LinkedList<Type>* boundLinkedList; //游标归属的链表
public:
	LinkedListIterator(const LinkedList<Type>* host) { //构造函数
		boundLinkedList = host;
		currentPosition = host->head->successor;
	}
	void goNext(int pos) { //游标向尾部移动一定数量的位置（pos:后移的结点数量）
		for (int i = 0; i < pos; i++) {
			if (currentPosition == nullptr)break;
			currentPosition = currentPosition->successor;
		}
	}
	Type getData()const { //返回当前游标指向的节点数据
		return currentPosition->data;
	}
	void reset() { //将游标重置回头部
		currentPosition = boundLinkedList->head->successor;
	}
	bool isNullptr()const { //判断游标当前指向位置是否为空指针
		return currentPosition == nullptr; 
	}
};

template<class Type> class LinkedListNode { //链表节点
public:
	Type data; //存储结点数据（数据域）
	LinkedListNode<Type> *successor = nullptr; //存储结点后继（指针域）
	LinkedListNode() :successor(nullptr) {}
	LinkedListNode(Type nData, LinkedListNode<Type> *next) :data(nData), successor(next) {}
};

template<class Type> class LinkedList {
	friend class LinkedListIterator<Type>;
private:
	LinkedListNode<Type>* head = nullptr; //头指针
	LinkedListNode<Type>* tail = nullptr; //尾指针（用于向尾部插入）
	int listSize = 0; //链表中的结点数量
public:
	LinkedList<Type>() { //构造空链表
		head = new LinkedListNode<Type>;
		tail = head;
	}
	~LinkedList<Type>() {//析构空链表
		clear(false);
	}
	//************************************
	// 全名:  LinkedList<Type>::clear
	// 功能: 清除所有结点（包括头节点）并置空
	// 权限:    public 
	// 返回:   void
	// 参数: bool redo 为true时重新初始化为空链表
	//************************************
	void clear(bool redo) { 
		LinkedListNode<Type> *cur = head, *curSucc;
		while (1) {
			curSucc = cur->successor;
			delete cur;
			if (curSucc == nullptr) break;//已经到链表尾端，结束delete
			cur = curSucc;
		}
		if (redo) { //重新初始化为空链表
			head = new LinkedListNode<Type>;
			tail = head;
		}
	}
	//************************************
	// 全名:  LinkedList<Type>::pushTail
	// 功能: //在链表尾部插入数据
	// 权限:    public 
	// 返回:   bool
	// 参数: Type data 要插入的数据
	//************************************
	bool pushTail(Type data) { 
		LinkedListNode<Type> *newEl = new LinkedListNode<Type>;
		if (newEl == nullptr)return false; //无法动态新建结点时，返回false
		newEl->data = data;
		newEl->successor = nullptr;
		tail->successor = newEl;
		tail = newEl;
		listSize++;
		return true;
	}
	//************************************
	// 全名:  LinkedList<Type>::getSize
	// 功能: 获取链表的大小
	// 权限:    public 
	// 返回:   int
	//************************************
	int getSize() {return listSize;} //获取链表大小
};

template<class Type> class LinkedListIntersection { //链表求交集
public:
	//************************************
	// 全名:  LinkedListIntersection<Type>::getLinkedListIntersection
	// 功能: 链表求交
	// 权限:    public 
	// 返回:   void
	// 参数: const LinkedList<Type> & sourceFirst 参与运算的链表
	// 参数: const LinkedList<Type> & sourceSecond 参与运算的链表
	// 参数: LinkedList<Type> & result 返回结果的链表
	//************************************
	void getLinkedListIntersection(const LinkedList<Type>& sourceFirst, const LinkedList<Type>& sourceSecond, LinkedList<Type>& result) {
		LinkedListIterator<Type> firstIter(&sourceFirst), secondIter(&sourceSecond);
		bool isFirstElement = true;
		Type last;
		//在两个游标指向均不为空的时候，继续运算
		while (!firstIter.isNullptr()&&!secondIter.isNullptr()) {
			//若第一个游标指向结点的值大于第二个，第二个游标节点指向当前结点后继
			if (firstIter.getData() > secondIter.getData()) secondIter.goNext(1);
			//若第2个游标指向结点的值大于第1个，第1个游标节点指向当前结点后继; 
			else if (secondIter.getData() > firstIter.getData())firstIter.goNext(1); 
			//二者相等时，将当前游标指向结点的值插入结果链表尾部，并且将两个游标同时后移
			else { 
				if (isFirstElement) {
					isFirstElement = false;
					last = firstIter.getData();
				}
				else {
					if (firstIter.getData() == last) { //当前元素与上一加入交集的元素重复，放弃操作
						firstIter.goNext(1);
						secondIter.goNext(1);
						continue;
					}
					else {
						last = firstIter.getData(); //若元素不重复，将当前元素作为“上一元素”的标识
					}
				}
				result.pushTail(firstIter.getData()); //将元素加入交集
				firstIter.goNext(1);
				secondIter.goNext(1);
			}
		}
	}
};

class Solution { 
public:
	LinkedList<long long> inputFirst,inputSecond,result;
	//************************************
	// 全名:  Solution::readNum
	// 功能: 读取数字，处理非预期的输入情况
	// 权限:    public 
	// 返回:   long long 读取的数字
	// 参数: int & stat 状态码
	//************************************
	long long readNum(int& stat) { 
		stat = 0;
		std::string inputInfo;
		std::cin >> inputInfo;
		int sz = inputInfo.size();
		for (int i = 0; i < sz; i++) {
			if ((inputInfo[i]<'0' || inputInfo[i]>'9')) { //判断是否为数字
				if ((i != 0 && inputInfo[i] == '-') || (inputInfo[i] != '-')) { //判断是否为首端的负号
					stat = 1;//标记非法
				}
			}
		}
		if (stat == 1)return 0;
		else if (std::stoll(inputInfo) <= -2) {
			stat = 1;
			return 0;
		}
		return std::stoll(inputInfo); //将合法的数字字符串转为longlong整数
	}
	//************************************
	// 全名:  Solution::readIn
	// 功能: 处理输入
	// 权限:    public 
	// 返回:   void
	//************************************
	void readIn() {
		long long readCh,last=-2; //接受输入的整数 
		int stat;//接受输入合法性的标识
		std::cin.sync_with_stdio(false);
		while (1) {
			readCh = readNum(stat);
			if (stat == 1) { //输入非预期的字符时
				std::cin.ignore(INT_MAX, '\n'); //忽略cin缓冲区数据，达到重新输入效果
				std::cout << "输入有误，请重新输入第一行" << std::endl;
				inputFirst.clear(true); //置空链表
				last = -2;
				continue;
			}
			if (readCh != -1) {
				if (inputFirst.pushTail(readCh) == false) { //无法新建结点时
					std::cout << "无法新建链表节点，请确保内存充足后，重新输入第一行。" << std::endl;
					std::cin.ignore(INT_MAX, '\n');
					inputFirst.clear(true);  //置空链表
					last = -2;
					continue;
				}
				if (readCh < last) {
					std::cout << "输入序列不单调，请重新输入第一行。" << std::endl;
					std::cin.ignore(INT_MAX, '\n');
					inputFirst.clear(true);  //置空链表
					last = -2;
					continue;
				}
				last = readCh;
				continue;
			}
			break;
		}
		last = -2;
		while (1) {
			readCh = readNum(stat);
			if (stat == 1) {//输入非预期的字符时
				std::cin.ignore(INT_MAX, '\n');//忽略cin缓冲区数据，达到重新输入效果
				std::cout << "输入有误，请重新输入第二行" << std::endl;
				inputSecond.clear(true); //置空链表
				last = -2;
				continue;
			}
			if (readCh != -1) {
				if (inputSecond.pushTail(readCh) == false) {//无法新建结点时
					std::cout << "无法新建链表节点，请确保内存充足后，重新输入第二行。" << std::endl;

					inputSecond.clear(true);//置空链表
					last = -2;
					continue;
				}
				if (readCh < last) {
					std::cout << "输入序列不单调，请重新输入第二行。" << std::endl;
					std::cin.ignore(INT_MAX, '\n');
					inputFirst.clear(true);  //置空链表
					last = -2;
					continue;
				}
				last = readCh;
				continue;
			}
			break;
		}
	}
	void solveIntersection() { //求交运算
		LinkedListIntersection<long long> insSol;
		insSol.getLinkedListIntersection(inputFirst, inputSecond, result);
		return;
	}
	//************************************
	// 全名:  Solution::outputResult
	// 功能: 输出求交运算的结果
	// 权限:    public 
	// 返回:   void
	//************************************
	void outputResult() { //
		if (result.getSize()) { //判断答案链表是否为空
			bool isFirst = true; //用于标识是否为第一个输出
			LinkedListIterator<long long> curIter(&result);
			while (!curIter.isNullptr()) {
				if (isFirst) isFirst = false; //为第一个数据时，不输出空格，将标识取false
				else std::cout << " "; //不是第一个输入的数字时，输出空格
				std::cout << curIter.getData(); //输出当前游标指向的数据
				curIter.goNext(1);//游标指向下一个位置
			}
		}
		else std::cout << "NULL"; //链表为空时，输出NULL
	}
};
int main() {
	Solution sol;
	sol.readIn(); //读取数据
	sol.solveIntersection(); //进行交集运算
	sol.outputResult(); //输出结果
	std::cout << std::endl;
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}

