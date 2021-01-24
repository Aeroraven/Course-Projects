#include <iostream>
#include <string>
#include <climits> 
template<class Type> class LinkedListNode; //������
template<class Type> class LinkedListIterator; //���������(�α�)
template<class Type> class LinkedList; //�������

template<class Type> class LinkedListIterator {//���������
	friend class LinkedListNode<Type>;
	friend class LinkedList<Type>;
private:
	LinkedListNode<Type>* currentPosition; //�α굱ǰָ��Ľ��
	const LinkedList<Type>* boundLinkedList; //�α����������
public:
	LinkedListIterator(const LinkedList<Type>* host) { //���캯��
		boundLinkedList = host;
		currentPosition = host->head->successor;
	}
	void goNext(int pos) { //�α���β���ƶ�һ��������λ�ã�pos:���ƵĽ��������
		for (int i = 0; i < pos; i++) {
			if (currentPosition == nullptr)break;
			currentPosition = currentPosition->successor;
		}
	}
	Type getData()const { //���ص�ǰ�α�ָ��Ľڵ�����
		return currentPosition->data;
	}
	void reset() { //���α����û�ͷ��
		currentPosition = boundLinkedList->head->successor;
	}
	bool isNullptr()const { //�ж��α굱ǰָ��λ���Ƿ�Ϊ��ָ��
		return currentPosition == nullptr; 
	}
};

template<class Type> class LinkedListNode { //����ڵ�
public:
	Type data; //�洢������ݣ�������
	LinkedListNode<Type> *successor = nullptr; //�洢����̣�ָ����
	LinkedListNode() :successor(nullptr) {}
	LinkedListNode(Type nData, LinkedListNode<Type> *next) :data(nData), successor(next) {}
};

template<class Type> class LinkedList {
	friend class LinkedListIterator<Type>;
private:
	LinkedListNode<Type>* head = nullptr; //ͷָ��
	LinkedListNode<Type>* tail = nullptr; //βָ�루������β�����룩
	int listSize = 0; //�����еĽ������
public:
	LinkedList<Type>() { //���������
		head = new LinkedListNode<Type>;
		tail = head;
	}
	~LinkedList<Type>() {//����������
		clear(false);
	}
	//************************************
	// ȫ��:  LinkedList<Type>::clear
	// ����: ������н�㣨����ͷ�ڵ㣩���ÿ�
	// Ȩ��:    public 
	// ����:   void
	// ����: bool redo Ϊtrueʱ���³�ʼ��Ϊ������
	//************************************
	void clear(bool redo) { 
		LinkedListNode<Type> *cur = head, *curSucc;
		while (1) {
			curSucc = cur->successor;
			delete cur;
			if (curSucc == nullptr) break;//�Ѿ�������β�ˣ�����delete
			cur = curSucc;
		}
		if (redo) { //���³�ʼ��Ϊ������
			head = new LinkedListNode<Type>;
			tail = head;
		}
	}
	//************************************
	// ȫ��:  LinkedList<Type>::pushTail
	// ����: //������β����������
	// Ȩ��:    public 
	// ����:   bool
	// ����: Type data Ҫ���������
	//************************************
	bool pushTail(Type data) { 
		LinkedListNode<Type> *newEl = new LinkedListNode<Type>;
		if (newEl == nullptr)return false; //�޷���̬�½����ʱ������false
		newEl->data = data;
		newEl->successor = nullptr;
		tail->successor = newEl;
		tail = newEl;
		listSize++;
		return true;
	}
	//************************************
	// ȫ��:  LinkedList<Type>::getSize
	// ����: ��ȡ����Ĵ�С
	// Ȩ��:    public 
	// ����:   int
	//************************************
	int getSize() {return listSize;} //��ȡ�����С
};

template<class Type> class LinkedListIntersection { //�����󽻼�
public:
	//************************************
	// ȫ��:  LinkedListIntersection<Type>::getLinkedListIntersection
	// ����: ������
	// Ȩ��:    public 
	// ����:   void
	// ����: const LinkedList<Type> & sourceFirst �������������
	// ����: const LinkedList<Type> & sourceSecond �������������
	// ����: LinkedList<Type> & result ���ؽ��������
	//************************************
	void getLinkedListIntersection(const LinkedList<Type>& sourceFirst, const LinkedList<Type>& sourceSecond, LinkedList<Type>& result) {
		LinkedListIterator<Type> firstIter(&sourceFirst), secondIter(&sourceSecond);
		bool isFirstElement = true;
		Type last;
		//�������α�ָ�����Ϊ�յ�ʱ�򣬼�������
		while (!firstIter.isNullptr()&&!secondIter.isNullptr()) {
			//����һ���α�ָ�����ֵ���ڵڶ������ڶ����α�ڵ�ָ��ǰ�����
			if (firstIter.getData() > secondIter.getData()) secondIter.goNext(1);
			//����2���α�ָ�����ֵ���ڵ�1������1���α�ڵ�ָ��ǰ�����; 
			else if (secondIter.getData() > firstIter.getData())firstIter.goNext(1); 
			//�������ʱ������ǰ�α�ָ�����ֵ����������β�������ҽ������α�ͬʱ����
			else { 
				if (isFirstElement) {
					isFirstElement = false;
					last = firstIter.getData();
				}
				else {
					if (firstIter.getData() == last) { //��ǰԪ������һ���뽻����Ԫ���ظ�����������
						firstIter.goNext(1);
						secondIter.goNext(1);
						continue;
					}
					else {
						last = firstIter.getData(); //��Ԫ�ز��ظ�������ǰԪ����Ϊ����һԪ�ء��ı�ʶ
					}
				}
				result.pushTail(firstIter.getData()); //��Ԫ�ؼ��뽻��
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
	// ȫ��:  Solution::readNum
	// ����: ��ȡ���֣������Ԥ�ڵ��������
	// Ȩ��:    public 
	// ����:   long long ��ȡ������
	// ����: int & stat ״̬��
	//************************************
	long long readNum(int& stat) { 
		stat = 0;
		std::string inputInfo;
		std::cin >> inputInfo;
		int sz = inputInfo.size();
		for (int i = 0; i < sz; i++) {
			if ((inputInfo[i]<'0' || inputInfo[i]>'9')) { //�ж��Ƿ�Ϊ����
				if ((i != 0 && inputInfo[i] == '-') || (inputInfo[i] != '-')) { //�ж��Ƿ�Ϊ�׶˵ĸ���
					stat = 1;//��ǷǷ�
				}
			}
		}
		if (stat == 1)return 0;
		else if (std::stoll(inputInfo) <= -2) {
			stat = 1;
			return 0;
		}
		return std::stoll(inputInfo); //���Ϸ��������ַ���תΪlonglong����
	}
	//************************************
	// ȫ��:  Solution::readIn
	// ����: ��������
	// Ȩ��:    public 
	// ����:   void
	//************************************
	void readIn() {
		long long readCh,last=-2; //������������� 
		int stat;//��������Ϸ��Եı�ʶ
		std::cin.sync_with_stdio(false);
		while (1) {
			readCh = readNum(stat);
			if (stat == 1) { //�����Ԥ�ڵ��ַ�ʱ
				std::cin.ignore(INT_MAX, '\n'); //����cin���������ݣ��ﵽ��������Ч��
				std::cout << "�������������������һ��" << std::endl;
				inputFirst.clear(true); //�ÿ�����
				last = -2;
				continue;
			}
			if (readCh != -1) {
				if (inputFirst.pushTail(readCh) == false) { //�޷��½����ʱ
					std::cout << "�޷��½�����ڵ㣬��ȷ���ڴ��������������һ�С�" << std::endl;
					std::cin.ignore(INT_MAX, '\n');
					inputFirst.clear(true);  //�ÿ�����
					last = -2;
					continue;
				}
				if (readCh < last) {
					std::cout << "�������в������������������һ�С�" << std::endl;
					std::cin.ignore(INT_MAX, '\n');
					inputFirst.clear(true);  //�ÿ�����
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
			if (stat == 1) {//�����Ԥ�ڵ��ַ�ʱ
				std::cin.ignore(INT_MAX, '\n');//����cin���������ݣ��ﵽ��������Ч��
				std::cout << "������������������ڶ���" << std::endl;
				inputSecond.clear(true); //�ÿ�����
				last = -2;
				continue;
			}
			if (readCh != -1) {
				if (inputSecond.pushTail(readCh) == false) {//�޷��½����ʱ
					std::cout << "�޷��½�����ڵ㣬��ȷ���ڴ�������������ڶ��С�" << std::endl;

					inputSecond.clear(true);//�ÿ�����
					last = -2;
					continue;
				}
				if (readCh < last) {
					std::cout << "�������в�����������������ڶ��С�" << std::endl;
					std::cin.ignore(INT_MAX, '\n');
					inputFirst.clear(true);  //�ÿ�����
					last = -2;
					continue;
				}
				last = readCh;
				continue;
			}
			break;
		}
	}
	void solveIntersection() { //������
		LinkedListIntersection<long long> insSol;
		insSol.getLinkedListIntersection(inputFirst, inputSecond, result);
		return;
	}
	//************************************
	// ȫ��:  Solution::outputResult
	// ����: ���������Ľ��
	// Ȩ��:    public 
	// ����:   void
	//************************************
	void outputResult() { //
		if (result.getSize()) { //�жϴ������Ƿ�Ϊ��
			bool isFirst = true; //���ڱ�ʶ�Ƿ�Ϊ��һ�����
			LinkedListIterator<long long> curIter(&result);
			while (!curIter.isNullptr()) {
				if (isFirst) isFirst = false; //Ϊ��һ������ʱ��������ո񣬽���ʶȡfalse
				else std::cout << " "; //���ǵ�һ�����������ʱ������ո�
				std::cout << curIter.getData(); //�����ǰ�α�ָ�������
				curIter.goNext(1);//�α�ָ����һ��λ��
			}
		}
		else std::cout << "NULL"; //����Ϊ��ʱ�����NULL
	}
};
int main() {
	Solution sol;
	sol.readIn(); //��ȡ����
	sol.solveIntersection(); //���н�������
	sol.outputResult(); //������
	std::cout << std::endl;
#ifdef _WIN32
	system("pause");
#endif
	return 0;
}

