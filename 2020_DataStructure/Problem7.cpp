#include <iostream>
#include<string>
#include <climits>
#include <stdexcept>
//************************************
// ȫ��:  isDigitStr
// ����: �ж�һ���ַ����ǲ��������ַ���
// Ȩ��:    public 
// ����:   bool
// ����: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}
class MinimumHeap { //��С��
private:
	int *heapArray = nullptr, heapSize = 0, heapCapacity = 0; //SizeΪ��ǰ��С��CapacityΪ�������
	void swap(int& x, int &y); //Ԫ�ؽ���
	void siftUp(int node); //��С�ѣ��ڵ����ϸ���
	void siftDown(int node); //��С�ѣ����¸���
public:
	enum MinimunHeapException {
		MinHeapExcept_SUCCESS, //�����ɹ�
		MinHeapExcept_ALLOCATE_FAILURE, //��̬����ռ�ʧ��
		MinHeapExcept_EXCEED_CAPACITY, //����ڵ㳬���������
		MinHeapExcept_EMPTY_HEAP //�ն��޷��ԶѶ�Ԫ�ؽ��в���
	};
	void build(int *data, int size, int maxSize, int& errorId); //��ʼ����������С��
	void insert(int data, int& errorId); //��һ���µĽڵ������С����
	void top(int& result, int& errorId); //��ȡ��С�ѶѶ���Ԫ��
	void pop(int& errorId); //������С�ѶѶ���Ԫ��
	int getSize(int& errorId); //��ȡ��С�ѵĵ�ǰ��С
	~MinimumHeap(); //��������
};

class WoodSplitting { //��������
public:
	MinimumHeap Heap; //������С��
	int *data; //���������
	int length; //�������ݵ��ܴ�С
	int answer; //���Ž��ֵ

	bool readData(); //��ȡ����
	void solution(); //���ͷ���
};

//��С�ѣ���Ա����

//************************************
// ȫ��:  MinimumHeap::swap
// ����: ����Ԫ��
// Ȩ��:    private 
// ����:   void
// ����: int & x
// ����: int & y
//************************************
void MinimumHeap::swap(int& x, int &y) {
	int t = x;
	x = y;
	y = t;
}
//************************************
// ȫ��:  MinimumHeap::siftUp
// ����: �����ϵ���
// Ȩ��:    private 
// ����:   void
// ����: int node
//************************************
void MinimumHeap::siftUp(int node) {
	int cur = node, curParent = ((node + 1) >> 1) - 1;
	int temp = heapArray[cur];
	while (curParent>=0) {
		if (temp < heapArray[curParent]) { //����ǰ�ڵ��ֵС���丸�ڵ㣬�򽻻�
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
// ȫ��:  MinimumHeap::siftDown
// ����: �����µ���
// Ȩ��:    private 
// ����:   void
// ����: int node
//************************************
void MinimumHeap::siftDown(int node) {
	int cur = node, curChild = (node << 1)+1;
	int temp = heapArray[node];
	while (curChild < heapSize) {
		if (curChild < heapSize-1) {
			if (heapArray[curChild + 1] < heapArray[curChild])curChild++; //����һ���ֵܽڵ�ֵ��С�����л�����һ���ڵ�
		}
		if (temp <= heapArray[curChild]) { //������ڵ��ֵС���ӽڵ����Сֵ������ѳ������˳�
			break;
		}
		else { //���򽻻������ӽڵ�ĶѼ���ά��
			heapArray[cur] = heapArray[curChild];
			cur = curChild;
			curChild =(curChild<<1)+1;
		}
	}
	heapArray[cur] = temp;
}
//************************************
// ȫ��:  MinimumHeap::build
// ����: ������
// Ȩ��:    public 
// ����:   void
// ����: int * data ��ʼ����
// ����: int size ��ʼ��С
// ����: int maxSize �ѵ��������
// ����: int & errorId ״̬��
//************************************
void MinimumHeap::build(int *data, int size, int maxSize, int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (size > maxSize) { //���������ݵĴ�С��������������򷵻�ʧ��
		errorId = MinHeapExcept_EXCEED_CAPACITY;
		return;
	}
	heapArray = new int[maxSize + 1];
	if (heapArray == nullptr) { //�������޷��������򷵻�ʧ����Ϣ
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
// ȫ��:  MinimumHeap::insert
// ����: ����з�������
// Ȩ��:    public 
// ����:   void
// ����: int data
// ����: int & errorId
//************************************
void MinimumHeap::insert(int data, int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (heapSize == heapCapacity) { //��������������������򷵻�ʧ����Ϣ
		errorId = MinHeapExcept_EXCEED_CAPACITY;
		return;
	}
	heapArray[heapSize] = data;
	siftUp(heapSize);
	heapSize++;
}
//************************************
// ȫ��:  MinimumHeap::top
// ����: ��öѶ�
// Ȩ��:    public 
// ����:   void
// ����: int & result
// ����: int & errorId
//************************************
void MinimumHeap::top(int& result, int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (!heapSize) { //��Ϊ�նѣ����ش�����Ϣ
		errorId = MinHeapExcept_EMPTY_HEAP;
		return;
	}
	result = heapArray[0];
	return;
}
//************************************
// ȫ��:  MinimumHeap::pop
// ����: ɾ���Ѷ�
// Ȩ��:    public 
// ����:   void
// ����: int & errorId
//************************************
void MinimumHeap::pop(int& errorId) {
	errorId = MinHeapExcept_SUCCESS;
	if (!heapSize) { //��Ϊ�նѣ����ش�����Ϣ
		errorId = MinHeapExcept_EMPTY_HEAP;
		return;
	}
	swap(heapArray[0], heapArray[heapSize-1]);
	heapSize--;
	siftDown(0);
}
//************************************
// ȫ��:  MinimumHeap::getSize
// ����: ��öѵĴ�С
// Ȩ��:    public 
// ����:   int
// ����: int & errorId
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

//������������Ա����

//************************************
// ȫ��:  WoodSplitting::readData
// ����: ��ȡ����
// Ȩ��:    public 
// ����:   bool
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
	try{
		data = new int[length];
	}
	catch (std::bad_array_new_length) {
		std::cout << "�ڴ治�㣬�뱣֤�ڴ����������д˳���" << std::endl;
		return false;
	}
	catch (std::bad_alloc) {
		std::cout << "�ڴ治�㣬�뱣֤�ڴ����������д˳���" << std::endl;
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
					std::cout << "��������ֹ�����������������ľͷ������ֵ��" << std::endl;
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					validFlag = false;
				}
				
			}
			else {
				std::cout << "��������ݲ�������������������������ľͷ������ֵ��" << std::endl;
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
// ȫ��:  WoodSplitting::solution
// ����: �������
// Ȩ��:    public 
// ����:   void
//************************************
void WoodSplitting::solution() {
	int stat;
	int smallestFirst, smallestSecond;
	answer = 0;
	try {
		Heap.build(data, length, length, stat);
	}
	catch(std::bad_alloc){
		std::cout << "�ڴ治�㣬�뱣֤�ڴ����������д˳���" << std::endl;
		return ;
	}
	catch (std::bad_array_new_length) {
		std::cout << "�ڴ治�㣬�뱣֤�ڴ����������д˳���" << std::endl;
		return;
	}
	
	while (Heap.getSize(stat) > 1) { //ÿ�δӶ���ȡ������СԪ�غϲ��󣬶�����У�ֱ�����н�ʣһ��Ԫ��
		Heap.top(smallestFirst, stat);
		Heap.pop(stat);
		Heap.top(smallestSecond, stat);
		Heap.pop(stat);
		answer += smallestFirst + smallestSecond;  //�ϲ�ľͷ���ȵĴ���
		Heap.insert(smallestFirst + smallestSecond, stat); //���ϲ���ĳ��Ȳ������
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
