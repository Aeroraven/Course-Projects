#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include <string>
#include <climits>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
//************************************
// 全名:  isDigitStr
// 功能: 判断一个字符串是否为数字字符串
// 权限:    public
// 返回:   bool
// 参数: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}

template<class T>class LinkedListNode { //链表结点
public:
	LinkedListNode* succ = nullptr; //链表指针域
	T data; //链表数据域
};
template<class T>class Queue { //链式队列
private:
	LinkedListNode<T>* head = nullptr, *tail = nullptr; //链式队列头指针和尾指针
	int size = 0; //队列元素大小
public:
	Queue() { head = new LinkedListNode<T>; tail = head; } //构造函数
	void Push(const T& data); //入队列操作EnQue
	void Pop(); //出队列操作DeQue
	void Front(T& data); //获得队首元素
	bool Empty() { return !size; } //队列判空
};
template<class T>class MaxHeap { //最大堆
private:
public:
	int swapCount = 0; //交换次数
	T* arr=nullptr;
	int size = 0; //堆的大小
	~MaxHeap(); //析构函数
	void SiftDown(int x); //堆自上向下调整
	void Build(T* data, int len); //堆的建立
	void Pop(); //删除堆顶
	void Top(T& data); //获得堆顶元素
};

class SortAlgorithm {
private:
	template<class T>void ShellInsertSort(T* data, int begin, int interval, int len); //希尔排序的插入排序部分
	template<class T>void MergeSort(T* data, int l, int r, T* aux); //归并排序
	template<class T>void QuickSort(T* data, int l, int r); //快速排序
	template<class T>void QsortSwap(T& a, T& b); //元素交换
	template<class T>void QuickSortPartition(T* data, int l, int r, int& lv, int& rv); //快速排序的划分过程

	unsigned int rand_stat = 15; //随机数初值
public:
	int* arr = nullptr; //用于存放待排序数组
	int* arr_backup = nullptr; //用于备份待排序数组
	int size = 0; //数组大小
	unsigned long long swapCounter = 0; //交换次数
	unsigned long long compareCounter = 0; //比较次数
	int Random();//!!!!!
	void RandomFill(int x); //随机填充arr数组
	void RandomRecover() { for (int i = 0; i < size; i++)arr[i] = arr_backup[i]; } //将arr数组恢复到未排序的状态
	void Randomize() { rand_stat = time(NULL); } //随机化随机种子
	template<class T>void BubbleSort(T* data, int len); //冒泡排序
	template<class T>void SelectSort(T* data, int len); //直接选择排序
	template<class T>void InsertSort(T* data, int len); //直接插入排序
	template<class T>void ShellSort(T* data, int len); //希尔排序
	template<class T>void QuickSort(T* data, int len); //快速排序
	template<class T>void HeapSort(T* data, int len);  //堆排序
	template<class T>void MergeSort(T* data, int len); //归并排序
	template<class T>void RadixSort(T* data, int len); //基数LSD排序

	void PrintGuidance(); //打印提示界面
	void GetTime(int& ms); //获得当前系统时间
};

//************************************
// 全名:  Queue::Push
// 功能: 入队列操作EnQue
// 权限:    public
// 返回:   void
// 参数: const T & data
//************************************
template<class T>void Queue<T>::Push(const T& data) {
	LinkedListNode<T> *newEl = new LinkedListNode<T>;
	newEl->succ = nullptr;
	newEl->data = data;
	tail->succ = newEl;
	tail = newEl;
	size++;
}
//************************************
// 全名:  Queue::Pop
// 功能: 出队列操作DeQue
// 权限:    public
// 返回:   void
//************************************
template<class T>void Queue<T>::Pop() {
	if (!size)return;
	LinkedListNode<T>* temp = head->succ;
	head->succ = temp->succ;
	if (temp == tail)tail = head;
	size--;
	delete temp;
}
//************************************
// 全名:  Queue::Front
// 功能: 获得队首元素
// 权限:    public
// 返回:   void
// 参数: T & data 返回值
//************************************
template<class T>void Queue<T>::Front(T& data) {
	if (!size)return;
	data = head->succ->data;
}
template<class T> MaxHeap<T>::~MaxHeap() {
	//if (arr)delete[]arr;
	return;
}
//************************************
// 全名:  MaxHeap<T>::SifatDown
// 功能: 堆的向下调整
// 权限:    public
// 返回:   void
// 参数: int x 向下调整的起始结点
//************************************
template<class T>void MaxHeap<T>::SiftDown(int x) {
	int child = (x << 1) + 1;
	T temp = arr[x];
	while (child < size) {
		if (child + 1 < size) {
			if (arr[child] < arr[child + 1])child++;
		}
		if (temp < arr[child]) {
			arr[x] = arr[child];
			swapCount++;
			x = child;
			child = (child << 1) + 1;
		}
		else {
			break;
		}
	}
	arr[x] = temp;
}
//************************************
// 全名:  MaxHeap::Pop
// 功能: 删除堆顶元素
// 权限:    public
// 返回:   void
//************************************
template<class T>void MaxHeap<T>::Pop() {
	if (!size)return;
	int temp = arr[size - 1];
	arr[size - 1] = arr[0];
	swapCount++;
	arr[0] = temp; size--;
	SiftDown(0);
}
//************************************
// 全名:  MaxHeap::Top
// 功能: 获得堆顶元素
// 权限:    public
// 返回:   void
// 参数: T & data 返回值
//************************************
template<class T>void MaxHeap<T>::Top(T &data) {
	data = arr[0];
}
//************************************
// 全名:  MaxHeap::Build
// 功能: 建立堆
// 权限:    public
// 返回:   void
// 参数: T * data 初始元素
// 参数: int len 元素个数
//************************************
template<class T>void MaxHeap<T>::Build(T* data, int len) {
	arr = data;
	if (!arr)return;
	size = len;
	for (int i = (len / 2) - 1; i >= 0; i--)SiftDown(i);
}
//************************************
// 全名:  SortAlgorithm::Random
// 功能: 生成随机数
// 权限:    public
// 返回:   int
//************************************
int SortAlgorithm::Random() {
	unsigned int x = rand_stat;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	rand_stat = x;
	x >>= 1;
	return (int)x;
}
//************************************
// 全名:  SortAlgorithm::RandomFill
// 功能: 随机填充arr数组
// 权限:    public
// 返回:   void
// 参数: int x 随机生成数字的个数
//************************************
void SortAlgorithm::RandomFill(int x) {
	if (!arr_backup)delete[]arr_backup;
	if (!arr)delete[]arr;
	arr = new int[x];
	arr_backup = new int[x];
	if (!arr || !arr_backup) {
		size = 0;
		return;
	}
	for (int i = 0; i < x; i++) {
		arr[i] = Random();
		arr_backup[i] = arr[i];
	}
	size = x;
}
//************************************
// 全名:  SortAlgorithm::GetTime
// 功能: 获得当前系统时间，按照毫秒计算
// 权限:    public
// 返回:   void
// 参数: int & ms 返回值，当前的毫秒时间
//************************************
void SortAlgorithm::GetTime(int& ms) {
#ifdef WIN32
	ms = GetTickCount();
	return;
#else
	struct timeval t1;
	gettimeofday(&t1, NULL);
	ms = t1.tv_usec / 1000 + t1.tv_sec * 1000;
#endif
}
//************************************
// 全名:  SortAlgorithm::BubbleSort
// 功能: 冒泡排序
// 权限:    public
// 返回:   void
// 参数: T * data 待排序序列
// 参数: int len 序列长度
//************************************
template<class T>void SortAlgorithm::BubbleSort(T*data, int len) {
	T tmp;
	bool exchange = false;
	for (int i = 0; i < len - 1; i++) {
		exchange = false;
		for (int j = 0; j < len - i - 1; j++) {
			if (data[j] > data[j + 1]) {
				tmp = data[j + 1];
				data[j + 1] = data[j];
				data[j] = tmp;
				swapCounter++;
				exchange = true;
			}
		}
		if (exchange == false)break;
	}
}
//************************************
// 全名:  SortAlgorithm::SelectSort
// 功能: 直接选择排序
// 权限:    public
// 返回:   void
// 参数: T * data 待排序序列
// 参数: int len 序列长度
//************************************
template<class T>void SortAlgorithm::SelectSort(T*data, int len) {
	for (int i = 0; i < len; i++) {
		int pos = i;
		for (int j = i + 1; j < len; j++) {
			if (data[j] < data[pos]) {
				pos = j;
			}
		}
		if (i == pos)continue;
		T tmp;
		tmp = data[pos];
		data[pos] = data[i];
		data[i] = tmp;
		swapCounter++;
	}
}
//************************************
// 全名:  SortAlgorithm::InsertSort
// 功能: 直接插入排序
// 权限:    public
// 返回:   void
// 参数: T * data 待排序序列
// 参数: int len 序列长度
//************************************
template<class T>void SortAlgorithm::InsertSort(T*data, int len) {
	for (int i = 1; i < len; i++) {
		if (data[i] > data[i - 1])continue;
		T tmp = data[i];
		int pos = i - 1;
		while (pos >= 0) {
			if (tmp < data[pos]) {
				data[pos + 1] = data[pos];
				swapCounter++;
				pos--;
			}
			else {
				break;
			}
		}
		data[pos + 1] = tmp;
		swapCounter++;
	}
}
//************************************
// 全名:  SortAlgorithm::ShellInsertSort
// 功能: 希尔排序插入排序部分
// 权限:    private
// 返回:   void
// 参数: T * data 要排序的序列 （原序列）
// 参数: int begin 正在进行排序的子序列第一个元素在原序列中的下标
// 参数: int interval 子序列元素间在原序列中下标的最小间隔
// 参数: int len 原序列长度
//************************************
template<class T>void SortAlgorithm::ShellInsertSort(T* data, int begin, int interval, int len) {
	for (int i = begin + interval; i < len; i += interval) {
		if (data[i] > data[i - interval])continue;
		T tmp = data[i];
		int pos = i - interval;
		while (pos >= 0) {
			if (tmp < data[pos]) {
				data[pos + interval] = data[pos];
				swapCounter++;
				pos -= interval;
			}
			else break;
		}
		data[pos + interval] = tmp;
	}
}
//************************************
// 全名:  SortAlgorithm::QsortSwap
// 功能: 交换元素
// 权限:    private
// 返回:   void
// 参数: T & a
// 参数: T & b
//************************************
template<class T> void SortAlgorithm::QsortSwap(T& a, T& b) {
	T tmp = b;
	b = a;
	a = tmp;
	swapCounter++;
}
//************************************
// 全名:  SortAlgorithm::ShellSort
// 功能: 希尔排序
// 权限:    public
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int len 序列长度
//************************************
template<class T>void SortAlgorithm::ShellSort(T*data, int len) {
	for (int i = len / 2; i > 0; i /= 2) {
		for (int j = 0; j < i; j++) {
			ShellInsertSort(data, j, i, len);
		}
	}
}
//************************************
// 全名:  SortAlgorithm::QuickSortPartition
// 功能: 三路快排划分
// 权限:    private
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int l 正在排序区间左端点
// 参数: int r 正在排序区间右端点
// 参数: int & lv 划分结束后小于pivot数字所在区间[l,low]的右端点
// 参数: int & rv 划分结束后大于pivot数字所在区间[high,r]的左端点
//************************************
template<class T>void SortAlgorithm::QuickSortPartition(T* data, int l, int r, int& lv, int& rv) {
	int low = l - 1, high = r + 1, cur = l;
	T pivot = data[l];
	while (cur < high) {
		if (data[cur] < pivot) QsortSwap(data[cur++], data[++low]);
		else if (data[cur] > pivot) QsortSwap(data[cur], data[--high]);
		else cur++;
	}
	lv = low;
	rv = high;
}
//************************************
// 全名:  SortAlgorithm::QuickSort
// 功能: 快速排序
// 权限:    public
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int l 排序区间左端点
// 参数: int r 排序区间右端点
//************************************
template<class T>void SortAlgorithm::QuickSort(T*data, int l, int r) {
	if (l >= r)return;
	int pivot = data[l], lh, rh;
	QuickSortPartition(data, l, r, lh, rh);
	if (lh > l) QuickSort(data, l, lh);
	if (rh < r) QuickSort(data, rh, r);
}
//************************************
// 全名:  SortAlgorithm::QuickSort
// 功能: 快速排序
// 权限:    public
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int len 序列长度
//************************************
template<class T>void SortAlgorithm::QuickSort(T*data, int len) {
	QuickSort(data, 0, len - 1);
}
//************************************
// 全名:  SortAlgorithm::HeapSort
// 功能: 堆排序
// 权限:    public
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int len 序列长度
//************************************
template<class T>void SortAlgorithm::HeapSort(T*data, int len) {
	MaxHeap<T> heap;
	heap.Build(data, len);
	for (int i = 0; i < len - 1; i++) {
		heap.Pop();
	}
	for (int i = 0; i < len; i++) {
		data[i] = heap.arr[i];
	}
	swapCounter = heap.swapCount;
}
//************************************
// 全名:  SortAlgorithm::MergeSort
// 功能: 归并排序
// 权限:    public
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int l 正在排序区间的左端点
// 参数: int r 正在排序区间的右端点
// 参数: T * aux 辅助数组
//************************************
template<class T>void SortAlgorithm::MergeSort(T*data, int l, int r, T* aux) {
	if (l < r) {
		int mid = (l + r) >> 1;
		MergeSort(data, l, mid, aux);
		MergeSort(data, mid + 1, r, aux);
		int lpos = l, rpos = mid + 1, cur = l;
		while (lpos <= mid && rpos <= r) {
			if (data[lpos] < data[rpos])aux[cur++] = data[lpos++];
			else aux[cur++] = data[rpos++];
			compareCounter++;
		}
		while (lpos <= mid)aux[cur++] = data[lpos++];
		while (rpos <= r)aux[cur++] = data[rpos++];
		for (cur = l; cur <= r; cur++) data[cur] = aux[cur];
	}
}
//************************************
// 全名:  SortAlgorithm::MergeSort
// 功能: 归并排序
// 权限:    public
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int len 要排序序列的长度
//************************************
template<class T>void SortAlgorithm::MergeSort(T*data, int len) {
	T* aux = new T[len];
	MergeSort(data, 0, len - 1, aux);
	delete[] aux;
}
//************************************
// 全名:  SortAlgorithm::RadixSort
// 功能: 基数排序LSD
// 权限:    public
// 返回:   void
// 参数: T * data 要排序的序列
// 参数: int len 要排序序列长度
//************************************
template<class T>void SortAlgorithm::RadixSort(T* data, int len) {
	int maxLen = 0, maxVal = data[0];
	for (int i = 1; i < len; i++) {
		if (data[i] > maxVal)maxVal = data[i];
	}
	while (maxVal) {
		maxLen++;
		maxVal /= 10;
	}
	long long div = 1;
	Queue<int> bucket[10];
	for (int i = 1; i <= maxLen; i++) {
		for (int j = 0; j < len; j++) {
			bucket[((data[j] / div) % 10)].Push(data[j]);
		}
		int cur = 0, curBucket = 0;
		T front;
		while (curBucket < 10) {
			while (!bucket[curBucket].Empty()) {
				bucket[curBucket].Front(front);
				bucket[curBucket].Pop();
				data[cur++] = front;
			}
			curBucket++;
		}
		div *= 10;
	}
}
//************************************
// 全名:  SortAlgorithm::PrintGuidance
// 功能: 打印提示界面，处理输入
// 权限:    public
// 返回:   void
//************************************
void SortAlgorithm::PrintGuidance() {
	std::cout << "**                 排序算法比较                     **" << std::endl;
	std::cout << "======================================================" << std::endl;
	std::cout << "**                 1 --- 冒泡排序                   **" << std::endl;
	std::cout << "**                 2 --- 选择排序                   **" << std::endl;
	std::cout << "**                 3 --- 直接插入排序               **" << std::endl;
	std::cout << "**                 4 --- 希尔排序                   **" << std::endl;
	std::cout << "**                 5 --- 快速排序                   **" << std::endl;
	std::cout << "**                 6 --- 堆排序                     **" << std::endl;
	std::cout << "**                 7 --- 归并排序                   **" << std::endl;
	std::cout << "**                 8 --- 基数排序                   **" << std::endl;
	std::cout << "**                 9 --- 退出程序                   **" << std::endl;
	std::cout << "======================================================" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "请输入要产生的随机数的个数: ";
	int n;
	std::string readIn;
	int timeBegin, timeEnd;

	while (1) {
		while (1) {
			std::cin >> readIn;
			if (isDigitStr(readIn) && readIn != "0") {
				try {
					n = std::stoi(readIn);
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
		try {
			Randomize();
			RandomFill(n);
			break;
		}
		catch (std::bad_array_new_length) {
			std::cout << "输入的数字过大，内存不足，请重新输入" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		catch (std::bad_alloc) {
			std::cout << "输入的数字过大，内存不足，请重新输入" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

	}



	int exitFlag = 0;
	while (1) {
		std::cout << " " << std::endl;
		std::cout << "请选择排序算法:";
		std::cin >> readIn;
		if (!isDigitStr(readIn)) n = 10;
		else if (readIn.size() != 1)n = 10;
		else n = readIn[0] - '0';

		compareCounter = 0;
		swapCounter = 0;
		switch (n) {
		case 1:
			RandomRecover();
			GetTime(timeBegin);
			BubbleSort(arr, size);
			GetTime(timeEnd);
			std::cout << "冒泡排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "冒泡排序交换次数:" << swapCounter << " 次" << std::endl;
			break;
		case 2:
			RandomRecover();
			GetTime(timeBegin);
			SelectSort(arr, size);
			GetTime(timeEnd);
			std::cout << "选择排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "选择排序交换次数:" << swapCounter << " 次" << std::endl;

			break;
		case 3:
			RandomRecover();
			GetTime(timeBegin);
			InsertSort(arr, size);
			GetTime(timeEnd);
			std::cout << "直接插入排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "直接插入排序交换次数:" << swapCounter << " 次" << std::endl;

			break;
		case 4:
			RandomRecover();
			GetTime(timeBegin);
			ShellSort(arr, size);
			GetTime(timeEnd);
			std::cout << "希尔插入排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "希尔插入排序交换次数:" << swapCounter << " 次" << std::endl;

			break;
		case 5:
			RandomRecover();
			GetTime(timeBegin);
			QuickSort(arr, size);
			GetTime(timeEnd);
			std::cout << "快速排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "快速排序交换次数:" << swapCounter << " 次" << std::endl;

			break;
		case 6:
			RandomRecover();
			GetTime(timeBegin);
			HeapSort(arr, size);
			GetTime(timeEnd);
			std::cout << "堆排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "堆排序交换次数:" << swapCounter << " 次" << std::endl;

			break;
		case 7:
			try {
				RandomRecover();
				GetTime(timeBegin);
				MergeSort(arr, size);
				GetTime(timeEnd);
				std::cout << "归并排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
				std::cout << "归并排序比较次数:" << compareCounter << " 次" << std::endl;
			}
			catch (std::bad_alloc) {
				std::cout << "内存空间不足，无法新建辅助数组，归并排序无法进行" << std::endl;
			}


			break;
		case 8:
			try {
				RandomRecover();
				GetTime(timeBegin);
				RadixSort(arr, size);
				GetTime(timeEnd);
				std::cout << "基数排序所用时间:" << timeEnd - timeBegin << " ms" << std::endl;
				std::cout << "基数排序交换次数:" << swapCounter << " 次" << std::endl;
			}
			catch (std::bad_alloc) {
				std::cout << "内存空间不足，排序无法进行。" << std::endl;
			}


			break;
		case 9:
			exitFlag = 1;
			break;
		default:
			std::cout << "请输入有效数字" << std::endl;
		}
		if (exitFlag)break;
	}
#ifdef _WIN32
	system("pause");
#endif
}


int main() {
	SortAlgorithm w;
	w.PrintGuidance();
}
