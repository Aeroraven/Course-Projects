#include <iostream>
#include<string>
#include <climits>
#include <stdexcept>
//************************************
// 全名:  isDigitStr
// 功能: 判断一个字符串是不是数字字符串
// 权限:    public 
// 返回:   bool
// 参数: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}
class MinimumHeap { //最小堆
private:
	int *heapArray = nullptr, heapSize = 0, heapCapacity = 0; //Size为当前大小，Capacity为最大容量
	void swap(int& x, int &y); //元素交换
	void siftUp(int node); //最小堆：节点向上更新
	void siftDown(int node); //最小堆：向下更新
public:
	enum MinimunHeapException {
		MinHeapExcept_SUCCESS, //操作成功
		MinHeapExcept_ALLOCATE_FAILURE, //动态分配空间失败
		MinHeapExcept_EXCEED_CAPACITY, //插入节点超出最大容量
		MinHeapExcept_EMPTY_HEAP //空堆无法对堆顶元素进行操作
	};
	void build(int *data, int size, int maxSize, int& errorId); //初始化并建立最小堆
	void insert(int data, int& errorId); //将一个新的节点插入最小堆中
	void top(int& result, int& errorId); //获取最小堆堆顶的元素
	void pop(int& errorId); //弹出最小堆堆顶的元素
	int getSize(int& errorId); //获取最小堆的当前大小
	~MinimumHeap(); //析构函数
};

class WoodSplitting { //修理牧场
public:
	MinimumHeap Heap; //建立最小堆
	int *data; //读入的数据
	int length; //读入数据的总大小
	int answer; //最优解的值

	bool readData(); //读取数据
	void solution(); //求解和返回
};

//最小堆：成员函数

//************************************
// 全名:  MinimumHeap::swap
// 功能: 交换元素
// 权限:    private 
// 返回:   void
// 参数: int & x
// 参数: int & y
//************************************
void MinimumHeap::swap(int& x, int &y) {
	int t = x;
	x = y;
	y = t;
}
//************************************
// 全名:  MinimumHeap::siftUp
// 功能: 堆向上调整
// 权限:    private 
// 返回:   void
// 参数: int node
//************************************
void MinimumHeap::siftUp(int node) {
	int cur = node, curParent = ((node + 1) >> 1) - 1;
	int temp = heapArray[cur];
	while (curParent>=0) {
		if (temp < heapArray[curParent]) { //若当前节点的值小于其父节点，则交换
			heapArray[cur] = heapArray[curParent];
			cur = curParent;
			curParent = ((curParent + 1) >> 1) - 1;
		}
		else {
			break;
		}
	}
	heapArray[cur] = temp;
}
//************************************
// 全名:  MinimumHeap::siftDown
// 功能: 堆向下调整
// 权限:    private 
// 返回:   void
// 参数: int node
//************************************
void MinimumHeap::siftDown(int node) {
	int cur = node, curChild = (node << 1)+1;
	int temp = heapArray[node];
	while (curChild < heapSize) {
		if (curChild < heapSize-1) {
			if (heapArray[curChild + 1] < heapArray[curChild])curChild++; //若另一个兄弟节点值更小，则切换到另一个节点
		}
		if (temp <= heapArray[curChild]) { //如果父节点的值小于子节点的最小值，则堆已成立，退出
			break;
		}
		else { //否则交换，对子节点的堆继续维护
			heapArray[cur] = heapArray[curChild];
			cur = curChild;
			curChild =(curChild<<1)+1;
		}
	}
	heapArray[cur] = temp;
}
//************************************
// 全名:  MinimumHeap::build
// 功能: 建立堆
// 权限:    public 
// 返回:   void
// 参数: int * data 初始内容
// 参数: int size 初始大小
// 参数: int maxSize 堆的最大容量
// 参数: int & errorId 状态码
//************************************
void MinimumHeap::build(int *data, int size, int maxSize, int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (size > maxSize) { //若插入数据的大小大于最大容量，则返回失败
		errorId = MinHeapExcept_EXCEED_CAPACITY;
		return;
	}
	heapArray = new int[maxSize + 1];
	if (heapArray == nullptr) { //若数组无法建立，则返回失败信息
		errorId = MinHeapExcept_ALLOCATE_FAILURE;
		return;
	}
	heapCapacity = maxSize;
	heapSize = size;
	for (int i = 0; i < size; i++) {
		heapArray[i] = data[i];
	}
	int cur = heapSize / 2 - 1;
	while (cur>=0) {
		siftDown(cur);
		cur--;
	}
}
//************************************
// 全名:  MinimumHeap::insert
// 功能: 向堆中放入数据
// 权限:    public 
// 返回:   void
// 参数: int data
// 参数: int & errorId
//************************************
void MinimumHeap::insert(int data, int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (heapSize == heapCapacity) { //若插入后大于最大容量，则返回失败信息
		errorId = MinHeapExcept_EXCEED_CAPACITY;
		return;
	}
	heapArray[heapSize] = data;
	siftUp(heapSize);
	heapSize++;
}
//************************************
// 全名:  MinimumHeap::top
// 功能: 获得堆顶
// 权限:    public 
// 返回:   void
// 参数: int & result
// 参数: int & errorId
//************************************
void MinimumHeap::top(int& result, int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (!heapSize) { //若为空堆，返回错误信息
		errorId = MinHeapExcept_EMPTY_HEAP;
		return;
	}
	result = heapArray[0];
	return;
}
//************************************
// 全名:  MinimumHeap::pop
// 功能: 删除堆顶
// 权限:    public 
// 返回:   void
// 参数: int & errorId
//************************************
void MinimumHeap::pop(int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (!heapSize) { //若为空堆，返回错误信息
		errorId = MinHeapExcept_EMPTY_HEAP;
		return;
	}
	swap(heapArray[0], heapArray[heapSize-1]);
	heapSize--;
	siftDown(0);
}
//************************************
// 全名:  MinimumHeap::getSize
// 功能: 获得堆的大小
// 权限:    public 
// 返回:   int
// 参数: int & errorId
//************************************
int MinimumHeap::getSize(int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	return heapSize;
}
MinimumHeap::~MinimumHeap() {
	if (heapArray != nullptr) {
		delete[] heapArray;
	}
}

//修理牧场：成员函数

//************************************
// 全名:  WoodSplitting::readData
// 功能: 读取数据
// 权限:    public 
// 返回:   bool
//************************************
bool WoodSplitting::readData() {
	std::string readIn;
	while (1) {
		std::cin >> readIn;
		if (isDigitStr(readIn)&&readIn!="0") {
			try {
				length = std::stoi(readIn);
			}
			catch (std::out_of_range) {
				std::cout << "输入的数字过大，请重新输入" << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				continue;
			}
			break;
		}
		std::cout << "输入的不是有效的正整数，请重新输入" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	try{
		data = new int[length];
	}
	catch (std::bad_array_new_length) {
		std::cout << "内存不足，请保证内存充足后再运行此程序" << std::endl;
		return false;
	}
	catch (std::bad_alloc) {
		std::cout << "内存不足，请保证内存充足后再运行此程序" << std::endl;
		return false;
	}
	
	
	while (1) {
		bool validFlag = true;
		for (int i = 0; i < length; i++) {
			std::cin >> readIn;
			if (isDigitStr(readIn)) {
				try {
					data[i] = std::stoi(readIn);
				}
				catch (std::out_of_range) {
					std::cout << "输入的数字过大。请重新输入所有木头长度数值。" << std::endl;
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					validFlag = false;
				}
				
			}
			else {
				std::cout << "输入的内容不是正整数。请重新输入所有木头长度数值。" << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				validFlag = false;
			}
			if (!validFlag)break;
		}
		if (validFlag)break;
	}
	return true;
}

//************************************
// 全名:  WoodSplitting::solution
// 功能: 求解问题
// 权限:    public 
// 返回:   void
//************************************
void WoodSplitting::solution() {
	int stat;
	int smallestFirst, smallestSecond;
	answer = 0;
	try {
		Heap.build(data, length, length, stat);
	}
	catch(std::bad_alloc){
		std::cout << "内存不足，请保证内存充足后再运行此程序" << std::endl;
		return ;
	}
	catch (std::bad_array_new_length) {
		std::cout << "内存不足，请保证内存充足后再运行此程序" << std::endl;
		return;
	}
	
	while (Heap.getSize(stat) > 1) { //每次从堆中取两个最小元素合并后，丢入堆中，直至堆中仅剩一个元素
		Heap.top(smallestFirst, stat);
		Heap.pop(stat);
		Heap.top(smallestSecond, stat);
		Heap.pop(stat);
		answer += smallestFirst + smallestSecond;  //合并木头长度的代价
		Heap.insert(smallestFirst + smallestSecond, stat); //将合并后的长度插入堆中
	}
	std::cout << answer;
}

int main()
{
	WoodSplitting sol;
	if (sol.readData()) {
		sol.solution();
	}
	std::cout << std::endl;
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
