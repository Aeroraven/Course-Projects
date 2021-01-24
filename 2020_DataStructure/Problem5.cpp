#include <iostream>
#include <string>
#include <climits> 
#include <stdexcept> 
//************************************
// ȫ��:  isDigitStr
// ����: �ж�һ���ַ����Ƿ�ֻ��������
// Ȩ��:    public 
// ����:   bool
// ����: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}
class LinkedListNode { //����ڵ�
public:
	int data = -1;
	LinkedListNode *successor = nullptr, *predecessor = nullptr; //��̺�ǰ��
};
class LinkedList { //����
private:
	LinkedListNode *head = nullptr; //ͷָ��
	LinkedListNode *tail = nullptr; //βָ��
	int listSize = 0;

public:
	enum LinkedListException {
		LLExcept_SUCCESS, //�ɹ�
		LLExcept_ALLOCATE_FAILURE, //�½��ڵ�ʧ��
		LLExcept_EMPTY_LINKEDLIST, //������
		LLExcept_INIT_FAILURE, //��ʼ��ʧ��
		LLExcept_INVALID_ARUGMENT //��Ч����
	};
	LinkedList();
	~LinkedList();
	void InsertTail(int data, int& errId);
	void RemoveFront(int& errId);
	void Find(int pos, int& result, int& errId);
	void FindReversed(int revPos, int& result, int& errId);
	int Size();

};
class Queue { //����
private:
	LinkedList List;
public:
	enum QueueException {
		QExcept_SUCCESS, //�ɹ�
		QExcept_LINKEDLIST_EXCEPTION, //����������
		QExcept_EMPTY_QUEUE, //�ն���
	};
	void GetFront(int& result, int& errId); 
	void Pop(int& errId);
	void Push(int data, int& errId);
	bool Empty();
};

class BankService_Solution { //����ҵ����Ŀ
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
// ȫ��:  LinkedList::InsertTail
// ����: ������β������Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: int data Ҫ���������
// ����: int & errId ״̬
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
// ȫ��:  LinkedList::RemoveFront
// ����: ɾ������ͷ����Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: int & errId ״̬��
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
// ȫ��:  LinkedList::Find
// ����: ��������ָ��λ�õ�Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: int pos λ��
// ����: int & result ���صĽ��
// ����: int & errId ״̬
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
// ȫ��:  LinkedList::FindReversed
// ����: ��β����������ָ��λ�õ�Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: int revPos λ��
// ����: int & result ���صĽ��
// ����: int & errId ״̬
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
// ȫ��:  Queue::GetFront
// ����: ��ö���Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: int & result ����ֵ
// ����: int & errId ״̬��
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
// ȫ��:  Queue::Pop
// ����: �����У�DeQue)
// Ȩ��:    public 
// ����:   void
// ����: int & errId
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
// ȫ��:  Queue::Push
// ����: ����У�EnQue)
// Ȩ��:    public 
// ����:   void
// ����: int data
// ����: int & errId
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
// ȫ��:  Queue::Empty
// ����: �ж϶����Ƿ�Ϊ��
// Ȩ��:    public 
// ����:   bool
//************************************
bool Queue::Empty() {
	return (List.Size() == 0);
}

//************************************
// ȫ��:  BankService_Solution::Solve
// ����: ����ҵ���������
// Ȩ��:    public 
// ����:   void
//************************************
void BankService_Solution::Solve() {

	Queue First, Second;
	std::string readIn;
	int n, *data, status;
	//����Nֵ
	while (1) {
		bool temp = true;
		std::cin >> readIn;
		if (isDigitStr(readIn) && readIn != "0") {
			try {
				n = std::stoi(readIn);
			}
			catch (std::out_of_range) {
				std::cout << "��������̫������������" << std::endl;
				temp = false;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				continue;
			}
			break;
		}
		std::cout << "������������ֲ���������������������" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	n = std::stoi(readIn);

	//����˿ͱ��
	data = new int[n];
	if (data==nullptr) {
		std::cout << "�����ڴ治�㣡" << std::endl;
		return;
	}
	bool validFlag = true;
	while (1) {
		validFlag = true;
		for (int i = 0; i < n; i++) {
			std::cin >> readIn;
			if (!isDigitStr(readIn)) {
				std::cout << "��������Ĳ������֡��������������й˿ͱ��" << std::endl;
				validFlag = false;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				break;
			}
			data[i] = std::stoi(readIn);
		}
		if (validFlag)break;
	}
	//�����
	for (int i = 0; i < n; i++) {
		if (data[i] & 1) {
			First.Push(data[i], status);
		}
		else {
			Second.Push(data[i], status);
		}
		if (status != 0) {
			std::cout << "�����ڴ治�㣬���в����޷����У�" << std::endl;
			return;
		}
	}
	int tempFirst, tempSecond;
	//�����������AB���ǿգ��ȴ�A�е���1��Ԫ�أ���A�ǿգ��ٵ���һ��Ԫ�أ�ͬʱ��B�е���һ��Ԫ��
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
	//��A�ǿգ���˳��A��Ԫ�����
	while (!First.Empty()) {
		First.GetFront(tempFirst, status); First.Pop(status);
		std::cout << tempFirst << " ";

	}
	//��B�ǿգ���˳��B��Ԫ�����
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
