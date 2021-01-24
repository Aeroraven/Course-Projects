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
// ȫ��:  isDigitStr
// ����: �ж�һ���ַ����Ƿ�Ϊ�����ַ���
// Ȩ��:    public
// ����:   bool
// ����: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}

template<class T>class LinkedListNode { //������
public:
	LinkedListNode* succ = nullptr; //����ָ����
	T data; //����������
};
template<class T>class Queue { //��ʽ����
private:
	LinkedListNode<T>* head = nullptr, *tail = nullptr; //��ʽ����ͷָ���βָ��
	int size = 0; //����Ԫ�ش�С
public:
	Queue() { head = new LinkedListNode<T>; tail = head; } //���캯��
	void Push(const T& data); //����в���EnQue
	void Pop(); //�����в���DeQue
	void Front(T& data); //��ö���Ԫ��
	bool Empty() { return !size; } //�����п�
};
template<class T>class MaxHeap { //����
private:
public:
	int swapCount = 0; //��������
	T* arr=nullptr;
	int size = 0; //�ѵĴ�С
	~MaxHeap(); //��������
	void SiftDown(int x); //���������µ���
	void Build(T* data, int len); //�ѵĽ���
	void Pop(); //ɾ���Ѷ�
	void Top(T& data); //��öѶ�Ԫ��
};

class SortAlgorithm {
private:
	template<class T>void ShellInsertSort(T* data, int begin, int interval, int len); //ϣ������Ĳ������򲿷�
	template<class T>void MergeSort(T* data, int l, int r, T* aux); //�鲢����
	template<class T>void QuickSort(T* data, int l, int r); //��������
	template<class T>void QsortSwap(T& a, T& b); //Ԫ�ؽ���
	template<class T>void QuickSortPartition(T* data, int l, int r, int& lv, int& rv); //��������Ļ��ֹ���

	unsigned int rand_stat = 15; //�������ֵ
public:
	int* arr = nullptr; //���ڴ�Ŵ���������
	int* arr_backup = nullptr; //���ڱ��ݴ���������
	int size = 0; //�����С
	unsigned long long swapCounter = 0; //��������
	unsigned long long compareCounter = 0; //�Ƚϴ���
	int Random();//!!!!!
	void RandomFill(int x); //������arr����
	void RandomRecover() { for (int i = 0; i < size; i++)arr[i] = arr_backup[i]; } //��arr����ָ���δ�����״̬
	void Randomize() { rand_stat = time(NULL); } //������������
	template<class T>void BubbleSort(T* data, int len); //ð������
	template<class T>void SelectSort(T* data, int len); //ֱ��ѡ������
	template<class T>void InsertSort(T* data, int len); //ֱ�Ӳ�������
	template<class T>void ShellSort(T* data, int len); //ϣ������
	template<class T>void QuickSort(T* data, int len); //��������
	template<class T>void HeapSort(T* data, int len);  //������
	template<class T>void MergeSort(T* data, int len); //�鲢����
	template<class T>void RadixSort(T* data, int len); //����LSD����

	void PrintGuidance(); //��ӡ��ʾ����
	void GetTime(int& ms); //��õ�ǰϵͳʱ��
};

//************************************
// ȫ��:  Queue::Push
// ����: ����в���EnQue
// Ȩ��:    public
// ����:   void
// ����: const T & data
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
// ȫ��:  Queue::Pop
// ����: �����в���DeQue
// Ȩ��:    public
// ����:   void
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
// ȫ��:  Queue::Front
// ����: ��ö���Ԫ��
// Ȩ��:    public
// ����:   void
// ����: T & data ����ֵ
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
// ȫ��:  MaxHeap<T>::SifatDown
// ����: �ѵ����µ���
// Ȩ��:    public
// ����:   void
// ����: int x ���µ�������ʼ���
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
// ȫ��:  MaxHeap::Pop
// ����: ɾ���Ѷ�Ԫ��
// Ȩ��:    public
// ����:   void
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
// ȫ��:  MaxHeap::Top
// ����: ��öѶ�Ԫ��
// Ȩ��:    public
// ����:   void
// ����: T & data ����ֵ
//************************************
template<class T>void MaxHeap<T>::Top(T &data) {
	data = arr[0];
}
//************************************
// ȫ��:  MaxHeap::Build
// ����: ������
// Ȩ��:    public
// ����:   void
// ����: T * data ��ʼԪ��
// ����: int len Ԫ�ظ���
//************************************
template<class T>void MaxHeap<T>::Build(T* data, int len) {
	arr = data;
	if (!arr)return;
	size = len;
	for (int i = (len / 2) - 1; i >= 0; i--)SiftDown(i);
}
//************************************
// ȫ��:  SortAlgorithm::Random
// ����: ���������
// Ȩ��:    public
// ����:   int
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
// ȫ��:  SortAlgorithm::RandomFill
// ����: ������arr����
// Ȩ��:    public
// ����:   void
// ����: int x ����������ֵĸ���
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
// ȫ��:  SortAlgorithm::GetTime
// ����: ��õ�ǰϵͳʱ�䣬���պ������
// Ȩ��:    public
// ����:   void
// ����: int & ms ����ֵ����ǰ�ĺ���ʱ��
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
// ȫ��:  SortAlgorithm::BubbleSort
// ����: ð������
// Ȩ��:    public
// ����:   void
// ����: T * data ����������
// ����: int len ���г���
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
// ȫ��:  SortAlgorithm::SelectSort
// ����: ֱ��ѡ������
// Ȩ��:    public
// ����:   void
// ����: T * data ����������
// ����: int len ���г���
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
// ȫ��:  SortAlgorithm::InsertSort
// ����: ֱ�Ӳ�������
// Ȩ��:    public
// ����:   void
// ����: T * data ����������
// ����: int len ���г���
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
// ȫ��:  SortAlgorithm::ShellInsertSort
// ����: ϣ������������򲿷�
// Ȩ��:    private
// ����:   void
// ����: T * data Ҫ��������� ��ԭ���У�
// ����: int begin ���ڽ�������������е�һ��Ԫ����ԭ�����е��±�
// ����: int interval ������Ԫ�ؼ���ԭ�������±����С���
// ����: int len ԭ���г���
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
// ȫ��:  SortAlgorithm::QsortSwap
// ����: ����Ԫ��
// Ȩ��:    private
// ����:   void
// ����: T & a
// ����: T & b
//************************************
template<class T> void SortAlgorithm::QsortSwap(T& a, T& b) {
	T tmp = b;
	b = a;
	a = tmp;
	swapCounter++;
}
//************************************
// ȫ��:  SortAlgorithm::ShellSort
// ����: ϣ������
// Ȩ��:    public
// ����:   void
// ����: T * data Ҫ���������
// ����: int len ���г���
//************************************
template<class T>void SortAlgorithm::ShellSort(T*data, int len) {
	for (int i = len / 2; i > 0; i /= 2) {
		for (int j = 0; j < i; j++) {
			ShellInsertSort(data, j, i, len);
		}
	}
}
//************************************
// ȫ��:  SortAlgorithm::QuickSortPartition
// ����: ��·���Ż���
// Ȩ��:    private
// ����:   void
// ����: T * data Ҫ���������
// ����: int l ��������������˵�
// ����: int r �������������Ҷ˵�
// ����: int & lv ���ֽ�����С��pivot������������[l,low]���Ҷ˵�
// ����: int & rv ���ֽ��������pivot������������[high,r]����˵�
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
// ȫ��:  SortAlgorithm::QuickSort
// ����: ��������
// Ȩ��:    public
// ����:   void
// ����: T * data Ҫ���������
// ����: int l ����������˵�
// ����: int r ���������Ҷ˵�
//************************************
template<class T>void SortAlgorithm::QuickSort(T*data, int l, int r) {
	if (l >= r)return;
	int pivot = data[l], lh, rh;
	QuickSortPartition(data, l, r, lh, rh);
	if (lh > l) QuickSort(data, l, lh);
	if (rh < r) QuickSort(data, rh, r);
}
//************************************
// ȫ��:  SortAlgorithm::QuickSort
// ����: ��������
// Ȩ��:    public
// ����:   void
// ����: T * data Ҫ���������
// ����: int len ���г���
//************************************
template<class T>void SortAlgorithm::QuickSort(T*data, int len) {
	QuickSort(data, 0, len - 1);
}
//************************************
// ȫ��:  SortAlgorithm::HeapSort
// ����: ������
// Ȩ��:    public
// ����:   void
// ����: T * data Ҫ���������
// ����: int len ���г���
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
// ȫ��:  SortAlgorithm::MergeSort
// ����: �鲢����
// Ȩ��:    public
// ����:   void
// ����: T * data Ҫ���������
// ����: int l ���������������˵�
// ����: int r ��������������Ҷ˵�
// ����: T * aux ��������
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
// ȫ��:  SortAlgorithm::MergeSort
// ����: �鲢����
// Ȩ��:    public
// ����:   void
// ����: T * data Ҫ���������
// ����: int len Ҫ�������еĳ���
//************************************
template<class T>void SortAlgorithm::MergeSort(T*data, int len) {
	T* aux = new T[len];
	MergeSort(data, 0, len - 1, aux);
	delete[] aux;
}
//************************************
// ȫ��:  SortAlgorithm::RadixSort
// ����: ��������LSD
// Ȩ��:    public
// ����:   void
// ����: T * data Ҫ���������
// ����: int len Ҫ�������г���
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
// ȫ��:  SortAlgorithm::PrintGuidance
// ����: ��ӡ��ʾ���棬��������
// Ȩ��:    public
// ����:   void
//************************************
void SortAlgorithm::PrintGuidance() {
	std::cout << "**                 �����㷨�Ƚ�                     **" << std::endl;
	std::cout << "======================================================" << std::endl;
	std::cout << "**                 1 --- ð������                   **" << std::endl;
	std::cout << "**                 2 --- ѡ������                   **" << std::endl;
	std::cout << "**                 3 --- ֱ�Ӳ�������               **" << std::endl;
	std::cout << "**                 4 --- ϣ������                   **" << std::endl;
	std::cout << "**                 5 --- ��������                   **" << std::endl;
	std::cout << "**                 6 --- ������                     **" << std::endl;
	std::cout << "**                 7 --- �鲢����                   **" << std::endl;
	std::cout << "**                 8 --- ��������                   **" << std::endl;
	std::cout << "**                 9 --- �˳�����                   **" << std::endl;
	std::cout << "======================================================" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "������Ҫ������������ĸ���: ";
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
					std::cout << "��������ֹ�������������" << std::endl;
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					continue;
				}

				break;
			}
			std::cout << "����Ĳ�����Ч��������������������" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		try {
			Randomize();
			RandomFill(n);
			break;
		}
		catch (std::bad_array_new_length) {
			std::cout << "��������ֹ����ڴ治�㣬����������" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		catch (std::bad_alloc) {
			std::cout << "��������ֹ����ڴ治�㣬����������" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

	}



	int exitFlag = 0;
	while (1) {
		std::cout << " " << std::endl;
		std::cout << "��ѡ�������㷨:";
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
			std::cout << "ð����������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "ð�����򽻻�����:" << swapCounter << " ��" << std::endl;
			break;
		case 2:
			RandomRecover();
			GetTime(timeBegin);
			SelectSort(arr, size);
			GetTime(timeEnd);
			std::cout << "ѡ����������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "ѡ�����򽻻�����:" << swapCounter << " ��" << std::endl;

			break;
		case 3:
			RandomRecover();
			GetTime(timeBegin);
			InsertSort(arr, size);
			GetTime(timeEnd);
			std::cout << "ֱ�Ӳ�����������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "ֱ�Ӳ������򽻻�����:" << swapCounter << " ��" << std::endl;

			break;
		case 4:
			RandomRecover();
			GetTime(timeBegin);
			ShellSort(arr, size);
			GetTime(timeEnd);
			std::cout << "ϣ��������������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "ϣ���������򽻻�����:" << swapCounter << " ��" << std::endl;

			break;
		case 5:
			RandomRecover();
			GetTime(timeBegin);
			QuickSort(arr, size);
			GetTime(timeEnd);
			std::cout << "������������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "�������򽻻�����:" << swapCounter << " ��" << std::endl;

			break;
		case 6:
			RandomRecover();
			GetTime(timeBegin);
			HeapSort(arr, size);
			GetTime(timeEnd);
			std::cout << "����������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
			std::cout << "�����򽻻�����:" << swapCounter << " ��" << std::endl;

			break;
		case 7:
			try {
				RandomRecover();
				GetTime(timeBegin);
				MergeSort(arr, size);
				GetTime(timeEnd);
				std::cout << "�鲢��������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
				std::cout << "�鲢����Ƚϴ���:" << compareCounter << " ��" << std::endl;
			}
			catch (std::bad_alloc) {
				std::cout << "�ڴ�ռ䲻�㣬�޷��½��������飬�鲢�����޷�����" << std::endl;
			}


			break;
		case 8:
			try {
				RandomRecover();
				GetTime(timeBegin);
				RadixSort(arr, size);
				GetTime(timeEnd);
				std::cout << "������������ʱ��:" << timeEnd - timeBegin << " ms" << std::endl;
				std::cout << "�������򽻻�����:" << swapCounter << " ��" << std::endl;
			}
			catch (std::bad_alloc) {
				std::cout << "�ڴ�ռ䲻�㣬�����޷����С�" << std::endl;
			}


			break;
		case 9:
			exitFlag = 1;
			break;
		default:
			std::cout << "��������Ч����" << std::endl;
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
