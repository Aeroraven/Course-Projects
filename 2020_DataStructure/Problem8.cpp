#include <iostream>
#include <string>
#include <climits>
#include <stdexcept>
#include <fstream>

// ����ͼ˵��
// ���ڶ���ͼ����Ӱ����С�������㷨����ȷ�ԣ�����ĺ궨�����һ������/��ֹ����ͼ������
// ������ͼ����ֹʱ������������A��B���Ѿ���ȨΪw�ıߣ���A��B��·����Ϊ1�����·�������̶�Ϊw���޷��޸�
// ������ͼ����ʱ��������������������ֱ�����ߵ���С��Ȩ���ò�������ͨ���ӱ�ʹͼ��Ϊ����ͼʵ��

#define ALLOW_MULTIEDGE false //�Ƿ�������رߣ�����Ϊtrue



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

class VertexInfo; //������Ϣ
template<class Type> class LinkedListNode; //������
template<class Type> class LinkedList; //����
class Edge; //��
template<class Type>class AVLTreeNode; //AVL���
template<class TypeA>class Pair; //���


template<class TypeA>class Pair {
public:
	TypeA a, b;
	bool operator >(Pair<TypeA> p) {
		if (a == p.a)return b > p.b;
		else return a > p.a;
	}
	bool operator <(Pair<TypeA> p) {
		if (a == p.a)return b < p.b;
		else return a < p.a;
	}
	bool operator ==(Pair<TypeA> p) {
		return a == p.a&&b == p.b;
	}
};

template<class Type> class LinkedListNode { // ����ڵ���Ϣ
public:
	Type data;
	LinkedListNode *pred = nullptr, *succ = nullptr;
};
template<class Type> class LinkedList { //������
private:
	LinkedListNode<Type> *head = nullptr, *tail = nullptr; //����ͷβָ��
	int listSize = 0; //�����С
public:
	LinkedList<Type>();
	~LinkedList<Type>();
	LinkedListNode<Type>* GetHead(); //���ͷָ���ַ
	void InsertTail(const Type& data); //������β����������
	void PopTail(); //ɾ������β�����
	LinkedListNode<Type>* GetTail(); //��ȡ����βָ��
	int GetSize(); //��ȡ�����С
	void Clear(); //�������
};

class Edge { // �߶���
public:
	int to, weight; //�ߵ��յ��Ȩֵ
	LinkedListNode<LinkedList<Edge>*> *toLinkedListPtr = nullptr; //���յ������ڽӱ��е�λ��
	AVLTreeNode<VertexInfo> *uInfPtr, *vInfPtr; //�������յ�����AVL����е�ָ��
	bool operator >(Edge p) {
		return weight > p.weight;
	}
	bool operator <(Edge p) {
		return weight < p.weight;
	}
	bool operator ==(Edge p) {
		return weight == p.weight;
	}
};
class VertexInfo { //���涥����Ϣ
public:
	int identity; //������
	std::string alias; //��������
	AVLTreeNode<VertexInfo>  *bstNodePtr = nullptr; //������AVL���н��ĵ�ַ
	LinkedListNode<LinkedList<Edge>*> *linklistNodePtr = nullptr; //�������ڽӱ��д洢�ߵ�����ĵ�ַ
	bool operator <(const VertexInfo& p) {
		return alias < p.alias;
	}
	bool operator ==(const VertexInfo& p) {
		return alias == p.alias;
	}
	bool operator >(const VertexInfo& p) {
		return alias > p.alias;
	}
};
template<class Type>class AVLTreeNode { //AVL���ڵ���Ϣ
public:
	Type data;
	AVLTreeNode *leftChild = nullptr, *rightChild = nullptr;
	int height = 0;
};
template<class Type>class AVLTree { //AVL��
private:
	AVLTreeNode<Type> *root = nullptr; //���ڵ�
	int GetBalanceFactor(AVLTreeNode<Type>* node); //��ȡƽ������
	int GetMaxChildHeight(AVLTreeNode<Type>* node); //��ȡ��������߶�
	AVLTreeNode<Type>* RotationL(AVLTreeNode<Type>* node); //����
	AVLTreeNode<Type>* RotationR(AVLTreeNode<Type>* node); //����
	AVLTreeNode<Type>* RotationLR(AVLTreeNode<Type>* node); //������
	AVLTreeNode<Type>* RotationRL(AVLTreeNode<Type>* node); //������
	AVLTreeNode<Type>* Insert(Type value, AVLTreeNode<Type>* node); //����
public:
	~AVLTree();
	AVLTreeNode<Type>* LastInsertedNode = nullptr; //��һ������Ľ��
	void Insert(const Type& value); //������
	Type Find(Type value, bool &success); //���ҽ��

};
class HashTable { //��ϣ��
private:
	AVLTree<VertexInfo> *bucket; //ɢ�б�
	const int modFactor = 943; //ȡģ������
	int totalCounter = 0; //Ԫ�ظ���
public:
	HashTable();
	~HashTable();
	int GetHashCode(std::string alias); //���һ���ַ�����ɢ��ֵ
	AVLTreeNode<VertexInfo>* Insert(std::string alias); //��ɢ�б��в���һ������
	VertexInfo Find(std::string alias, bool &success); //��ɢ�б��в���һ������
};
class AdjacentTable { //�ڽӱ�
public:
	int vertexCounter = 0; //�������
	LinkedList<LinkedList<Edge>*> table; //�ڽӱ�
	LinkedListNode<LinkedList<Edge>*>* InsertNewNode(); //�½�����
	void AddEdge(LinkedListNode<LinkedList<Edge>*>* u, LinkedListNode<LinkedList<Edge>*>* v, int w, AVLTreeNode<VertexInfo>* uInfPtr, AVLTreeNode<VertexInfo>* vInfPtr); //�½�����
};

template<class Type>class MinHeap { //��С��
public:
	Type *heapArray = nullptr; //����ѵ�����
	int heapSize = 0; //��Ԫ�صĸ���
	void Rebuild(int size); //�������öѵ��������
	void Insert(Type x);//�ڶ��в���Ԫ��
	Type GetTop();//��öѶ�Ԫ��
	void Pop();//ɾ���Ѷ�Ԫ��
	void SiftUp(int node); //���ϵ���
	void SiftDown(int node);//���µ���
	void Swap(Type& x, Type&y);//����Ԫ��
	~MinHeap() { if (heapArray)delete[]heapArray; }
};
class Graph { // ����ͼ����Ϣ
public:
	AdjacentTable adj; //�ڽӱ�(������ΪID��ͼ)
	HashTable dict; //���������ֵ�
	int vertexCounter = 0, edgeCounter = 0;
	void NewNode(std::string alias); //�½��ڵ�
	void AddEdge(std::string u, std::string v, int w, bool showTip = true); //�������
};

class MinSpanningTree { //��С������
public:
	Graph GraphInfo; //����ͼ����Ϣ
	LinkedList<Edge> Result; //������С���������
	AVLTree<Pair<std::string>> MultipleEdgeCheck; //���ڼ���ر�
	bool AnswerStat = false;

	void NewNode(std::string alias); //�½��ڵ�
	void AddEdge(std::string u, std::string w, int v); //�������
	void SolveMST_Prim(std::string startingPoint); //�����С������
	void PrintResult(); //������
	void ClearResult() { Result.Clear(); } //���ý��
};

class ElectricitySystem_Solution { //���ϵͳ
public:
	MinSpanningTree MST; //ͼ�Ĵ������С���������

	void ShowMenu(); //��ʾ�˵�
	void Main(); //������
};




//�����ඨ��
template<class Type> LinkedList<Type>::LinkedList() {
	head = new LinkedListNode<Type>;
	tail = head;
}
template<class Type>LinkedList<Type>::~LinkedList() {
	if (head == nullptr) return;
	LinkedListNode<Type> *cur = head, *curNext = head->succ;
	while (cur != nullptr) {
		curNext = cur->succ;
		delete cur;
		cur = curNext;
	}
	listSize = 0;
}
//************************************
// ȫ��:  LinkedList<Type>::Clear
// ����: ��ղ����³�ʼ������
// Ȩ��:    public 
// ����:   void
//************************************
template<class Type>void LinkedList<Type>::Clear() {
	if (head == nullptr) return;
	LinkedListNode<Type> *cur = head, *curNext = head->succ;
	while (cur != nullptr) {
		curNext = cur->succ;
		delete cur;
		cur = curNext;
	}
	listSize = 0;
	head = new LinkedListNode<Type>;
	tail = head;
}
//************************************
// ȫ��:  LinkedList::InsertTail
// ����: ������β������Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: const Type & data Ԫ�ص�ֵ
//************************************
template<class Type>void LinkedList<Type>::InsertTail(const Type& data) {
	LinkedListNode<Type> *newEl = new LinkedListNode<Type>;
	newEl->pred = tail;
	newEl->succ = nullptr;
	newEl->data = data;
	tail->succ = newEl;
	tail = newEl;
	listSize++;
}
//************************************
// ȫ��:  LinkedList::GetHead
// ����: ��ȡ�����ͷָ��
// Ȩ��:    public 
// ����:   std::*
//************************************
template<class Type>LinkedListNode<Type>* LinkedList<Type>::GetHead() {
	return head;
}
template<class Type>void LinkedList<Type>::PopTail() { //ɾ��β���
	if (tail != head) {
		LinkedListNode<Type>* tailPred = tail->pred;
		tailPred->succ = nullptr;
		delete tail;
		tail = tailPred;
		listSize--;
	}
}
//************************************
// ȫ��:  LinkedList::GetTail
// ����: ��ȡ�����βָ��
// Ȩ��:    public 
// ����:   std::*
//************************************
template<class Type> LinkedListNode<Type>* LinkedList<Type>::GetTail() {
	return tail;
}
//************************************
// ȫ��:  LinkedList::GetSize
// ����: ��ȡ�����С
// Ȩ��:    public 
// ����:   int
//************************************
template<class Type> int LinkedList<Type>::GetSize() {
	return listSize;
}
// AVL ƽ���� ���忪ʼ

//************************************
// ȫ��:  AVLTree::GetBalanceFactor
// ����: ��ȡAVL����ƽ������
// Ȩ��:    private 
// ����:   int
// ����: AVLTreeNode<Type> * node ��ȡƽ�����ӵĽ��
//************************************
template<class Type>int AVLTree<Type>::GetBalanceFactor(AVLTreeNode<Type>* node) { //��ȡƽ������
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return lch - rch;
}
//************************************
// ȫ��:  AVLTree::GetMaxChildHeight
// ����: ��ȡ��������߶�
// Ȩ��:    private 
// ����:   int
// ����: AVLTreeNode<Type> * node ��ȡ�����߶ȵĽ��
//************************************
template<class Type>int AVLTree<Type>::GetMaxChildHeight(AVLTreeNode<Type>* node) { //��ȡ�������߶�
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return (lch > rch) ? lch : rch;
}
//************************************
// ȫ��:  AVLTree::RotationL
// ����: AVL����
// Ȩ��:    private 
// ����:   AVLTreeNode<Type>* ������ĸ��ڵ�
// ����: AVLTreeNode<Type> * node ����������(������)�����
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationL(AVLTreeNode<Type>* node) { //���������� R-R �ͣ�
	AVLTreeNode<Type> *rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	node->height = GetMaxChildHeight(node) + 1;
	rightChild->height = GetMaxChildHeight(rightChild) + 1;
	if (root == node)root = rightChild;
	return rightChild;
}
//************************************
// ȫ��:  AVLTree::RotationR
// ����: AVL ����
// Ȩ��:    private 
// ����:   AVLTreeNode<Type>* ������ĸ��ڵ�
// ����: AVLTreeNode<Type> * node ���������ĸ��ڵ�
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationR(AVLTreeNode<Type>* node) { //����������L-L�ͣ�
	AVLTreeNode<Type> *leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild;
	leftChild->rightChild = node;
	node->height = GetMaxChildHeight(node) + 1;
	leftChild->height = GetMaxChildHeight(node) + 1;
	if (root == node)root = leftChild;
	return leftChild;
}
//************************************
// ȫ��:  AVLTree::RotationLR
// ����: AVL����-����
// Ȩ��:    private 
// ����:   AVLTreeNode<Type>* ��ת��ĸ��ڵ�
// ����: AVLTreeNode<Type> * node ������ת�ĸ��ڵ�
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationLR(AVLTreeNode<Type>* node) { //������ת������ ������L-R��)
	node->leftChild = RotationL(node->leftChild);
	return RotationR(node);
}
//************************************
// ȫ��:  AVLTree::RotationRL
// ����: AVL ����-����
// Ȩ��:    private 
// ����:   AVLTreeNode<Type>* ��ת��ĸ��ڵ�
// ����: AVLTreeNode<Type> * node ������ת�ĸ��ڵ�
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationRL(AVLTreeNode<Type>* node) { //������������������R-L�ͣ�
	node->rightChild = RotationR(node->rightChild);
	return RotationL(node);
}

//************************************
// ȫ��:  AVLTree::Insert
// ����:  AVL ����
// Ȩ��:    public 
// ����:   AVLTreeNode<Type>* ������ĵ�ַ
// ����: Type value Ҫ�����ֵ
// ����: AVLTreeNode<Type> * node ��ǰ���ҵĽ��
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::Insert(Type value, AVLTreeNode<Type>* node) { //������
	//��ʼ������
	if (root == nullptr) {
		root = new AVLTreeNode<Type>;
		root->data = value;
		root->height = 1;
		LastInsertedNode = root;
		return root;
	}

	//����ڵ�
	AVLTreeNode<Type> **insPlace = (value > node->data) ? &(node->rightChild) : &(node->leftChild);
	if ((*insPlace) == nullptr) {
		(*insPlace) = new AVLTreeNode<Type>;
		(*insPlace)->data = value;
		(*insPlace)->height = 1;
		LastInsertedNode = (*insPlace);
	}
	else {
		*insPlace = Insert(value, *insPlace);
	}

	//�������߶�
	node->height = GetMaxChildHeight(node) + 1;

	//����ƽ�����
	int balanceFactor = GetBalanceFactor(node);
	if (balanceFactor == 0 || balanceFactor == 1 || balanceFactor == -1) return node;
	if (balanceFactor > 1 && GetBalanceFactor(node->leftChild) > 0) { //LL�Ͳ�ƽ��-����
		return RotationR(node);
	}
	if (balanceFactor < -1 && GetBalanceFactor(node->rightChild) < 0) { //RR�Ͳ�ƽ��-����
		return RotationL(node);
	}
	if (balanceFactor > 1 && GetBalanceFactor(node->leftChild) < 0) { //LR�Ͳ�ƽ��-�������
		return RotationLR(node);
	}
	if (balanceFactor < -1 && GetBalanceFactor(node->rightChild)>0) {//RL�Ͳ�ƽ��-���Һ���
		return RotationRL(node);
	}
}
//************************************
// ȫ��:  AVLTree::Insert
// ����: AVL ����
// Ȩ��:    public 
// ����:   void
// ����: const Type & value Ҫ�����Ԫ��
//************************************
template<class Type> void AVLTree<Type>::Insert(const Type& value) { //AVL��������-�ⲿ����
	Insert(value, root);
}
//************************************
// ȫ��:  AVLTree::Find
// ����: AVL ����
// Ȩ��:    public 
// ����:   Type ���ҵ���ֵ
// ����: Type value Ҫ���ҵ�ֵ�Ĺؼ���
// ����: bool & success ���ҳɹ�״̬
//************************************
template<class Type> Type AVLTree<Type>::Find(Type value, bool &success) { //����
	success = 1;
	AVLTreeNode<Type> *cur = root;
	while (cur != nullptr) {
		if (value == cur->data)return cur->data;
		if (value > cur->data) cur = cur->rightChild;
		else cur = cur->leftChild;
	}
	success = 0;
	return value;
}
template<class Type> AVLTree<Type>::~AVLTree<Type>() { //����ƽ����
	if (root == nullptr)return;
	LinkedList<AVLTreeNode<Type>*> stack;
	AVLTreeNode<Type>* stackTop;
	stack.InsertTail(root);
	while (stack.GetSize()) {
		stackTop = stack.GetTail()->data;
		stack.PopTail();
		if (stackTop->leftChild != nullptr) stack.InsertTail(stackTop->leftChild);
		if (stackTop->rightChild != nullptr) stack.InsertTail(stackTop->rightChild);
		delete stackTop;
	}
}

//��ϣ��ʼ
HashTable::HashTable() {
	bucket = new AVLTree<VertexInfo>[modFactor];
}
HashTable::~HashTable() {
	if (bucket != nullptr) {
		delete[]bucket;
	}
}
//************************************
// ȫ��:  HashTable::GetHashCode
// ����: ��ȡһ���ַ�����ɢ��ֵ
// Ȩ��:    public 
// ����:   int �ַ�����ɢ��ֵ
// ����: std::string alias ���ڼ�����ַ���
//************************************
int HashTable::GetHashCode(std::string alias) {
	int strSz = alias.length();
	int ret = 0;
	for (int i = 0; i < strSz; i++) {
		ret *= 255;
		ret += (int)alias[i];
		ret %= modFactor;
	}
	return ret;
}
//************************************
// ȫ��:  HashTable::Insert
// ����: ��ϣ�����
// Ȩ��:    public 
// ����:   AVLTreeNode<VertexInfo>* ����󣬸�ֵ���ڵ�ɢ�б�Ķ�ӦHashֵ��AVL���е�AVL����ַ
// ����: std::string alias Ҫ������ַ���
//************************************
AVLTreeNode<VertexInfo>* HashTable::Insert(std::string alias) {
	VertexInfo ins;
	ins.alias = alias;
	ins.identity = totalCounter++;
	int hashcode = GetHashCode(alias);
	bucket[hashcode].Insert(ins);
	bucket[hashcode].LastInsertedNode->data.bstNodePtr = bucket[hashcode].LastInsertedNode;
	return bucket[hashcode].LastInsertedNode;
}
//************************************
// ȫ��:  HashTable::Find
// ����: ��ϣ����ң����ն�������ѯ������Ϣ��
// Ȩ��:    public 
// ����:   VertexInfo ���ҵ��Ķ�����Ϣ
// ����: std::string alias Ҫ���ҵ�ֵ
// ����: bool & success ���ҳɹ�״̬
//************************************
VertexInfo HashTable::Find(std::string alias, bool &success) {
	int hashcode = GetHashCode(alias);
	VertexInfo findInf;
	findInf.alias = alias;
	VertexInfo ret = bucket[hashcode].Find(findInf, success);
	return ret;
}

//�ڽӱ�

//Ϊ����ͼ����Ĳ���ɾ�����ڴ���Ŀ�н�ԭ�ڽӱ��α����ݣ��ĵ�һά��˳������飩��Ϊ����
//ͬʱ��ʹ��Hash��+AVL����Ϊ��ѯ�Ż���AVL����������ڽӱ�ĵ�һά�ж�Ӧ������������
//Ϊ�˱��⼫�����Hash���еĵ�����ṹ�ڼ��˵�Hash��ͻ�����ʱ�临�Ӷȴﵽ��ߣ�����Ŀʵ�ֽ��������ΪAVL��
//����ʵ�ֵ�Ŀ��Ϊ��ʱ�临�Ӷȴ�O(n)�ȶ�������O(logn)
//����Ŀ�е��ڽӱ���Ƕ������ʵ�֣����е�һ�������У�ÿһ�������㴢��һ���������������ʾ�ö���ĳ���
//�����ʵ�ֿ��Բο���Ŀ�ĵ�"8_1950641_������.docx"

//���Ľ��Ƶ�һ������Ϊ����һ�����������������ʾ�Ľ���ڲ��ҽṹ�ж�Ӧ�Ľ���Ϊ��(��Ӧ��)AVL��㡿
//�봫ͳ�ڽӱ���ͬ����������һ����������Ƕ��������Ϊ���ڶ��������������ĳ����յ������

//************************************
// ȫ��:  AdjacentTable::InsertNewNode
// ����: �ڽӱ������㣨�ڵ�һ������β�������㣩
// Ȩ��:    public 
// ����:   LinkedListNode<LinkedList<Edge>*>* ����ĵ�һ������Ľ���ַ
//************************************
LinkedListNode<LinkedList<Edge>*>* AdjacentTable::InsertNewNode() {
	LinkedList<Edge>* w = new LinkedList<Edge>;
	table.InsertTail(w);
	return (table.GetTail());
}
//************************************
// ȫ��:  AdjacentTable::AddEdge
// ����: �ڽӱ���������
// Ȩ��:    public 
// ����:   void
// ����: LinkedListNode<LinkedList<Edge> * > * u ����ڵ�һ�������ж�Ӧ�Ľ���ַ
// ����: LinkedListNode<LinkedList<Edge> * > * v �յ��ڵ�һ�������ж�Ӧ�Ľ���ַ
// ����: int w ��Ȩ
// ����: AVLTreeNode<VertexInfo> * uInfPtr ����AVL����ַ
// ����: AVLTreeNode<VertexInfo> * vInfPtr �յ��AVL����ַ
//************************************
void AdjacentTable::AddEdge(LinkedListNode<LinkedList<Edge>*>* u, LinkedListNode<LinkedList<Edge>*>* v, int w, AVLTreeNode<VertexInfo>* uInfPtr, AVLTreeNode<VertexInfo>* vInfPtr) {
	Edge newEl;
	newEl.weight = w;
	newEl.toLinkedListPtr = v;
	newEl.uInfPtr = uInfPtr;
	newEl.vInfPtr = vInfPtr;
	u->data->InsertTail(newEl);
}

//ͼ�Ĵ���Ͳ���
//************************************
// ȫ��:  Graph::NewNode
// ����: ͼ����ӽڵ�
// Ȩ��:    public 
// ����:   void
// ����: std::string alias
//************************************
void Graph::NewNode(std::string alias) {
	bool succ = false;
	dict.Find(alias, succ); //���Ҹýڵ������Ƿ��Ѿ�����
	if (succ == true) {
		std::cout << "�������:" << alias << "�Ѿ����ڣ��ظ��Ľ�㽫���ᱻ�ظ�����" << std::endl;
		return;
	}

	LinkedListNode<LinkedList<Edge>*>* adjNewPtr = adj.InsertNewNode();
	AVLTreeNode<VertexInfo>* bstNewPtr = dict.Insert(alias);
	AVLTreeNode<VertexInfo>* bstPtr = bstNewPtr;
	bstPtr->data.linklistNodePtr = adjNewPtr;
	vertexCounter++;
}

//************************************
// ȫ��:  Graph::AddEdge
// ����: 
// Ȩ��:    public 
// ����:   void
// ����: std::string u �������
// ����: std::string v �յ�����
// ����: int w ��Ȩ
// ����: bool showTip �Ƿ���ʾ������ʾ��Ϣ
//************************************
void Graph::AddEdge(std::string u, std::string v, int w, bool showTip) {
	bool ust, vst;
	VertexInfo uid = dict.Find(u, ust), vid = dict.Find(v, vst); //ȷ�����������Ƿ���Ч
	if (ust&&vst) {
		edgeCounter++;
		adj.AddEdge((LinkedListNode<LinkedList<Edge>*>*) (uid.linklistNodePtr), (LinkedListNode<LinkedList<Edge>*>*) (vid.linklistNodePtr), w, uid.bstNodePtr, vid.bstNodePtr);
	}
	else {
		if (showTip == false)return;
		if (!ust && !vst) {
			std::cout << "�������:" << u << "��" << v << "�������ڣ�����Ӳ����ѱ�����" << std::endl;
		}
		else if (!ust) {
			std::cout << "�������:" << u << "�����ڣ�����Ӳ����ѱ�����" << std::endl;
		}
		else if (!vst) {
			std::cout << "�������:" << v << "�����ڣ�����Ӳ����ѱ�����" << std::endl;
		}
	}
}


//��
//************************************
// ȫ��:  MinHeap::Rebuild
// ����: �ѣ��ط���ռ䣨���ԭ�жѵ����ݣ������ط����С
// Ȩ��:    public 
// ����:   void
// ����: int size
//************************************
template<class Type> void MinHeap<Type>::Rebuild(int size) {
	if (heapArray != nullptr)delete[]heapArray;
	heapArray = new Type[size + 1];
	heapSize = 0;
}
//************************************
// ȫ��:  MinHeap::GetTop
// ����: ��ȡ�Ѷ�Ԫ��
// Ȩ��:    public 
// ����:   Type
//************************************
template<class Type> Type MinHeap<Type>::GetTop() {
	return heapArray[1];
}
//************************************
// ȫ��:  MinHeap::Insert
// ����: �ѣ�����Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: Type x Ԫ�ص�ֵ
//************************************
template<class Type> void MinHeap<Type>::Insert(Type x) {
	heapArray[++heapSize] = x;
	SiftUp(heapSize);
}
//************************************
// ȫ��:  MinHeap::Pop
// ����: �ѣ������Ѷ�Ԫ��
// Ȩ��:    public 
// ����:   void
//************************************
template<class Type> void MinHeap<Type>::Pop() {
	heapArray[1] = heapArray[heapSize--];
	SiftDown(1);
}
//************************************
// ȫ��:  MinHeap::Swap
// ����: ����Ԫ��
// Ȩ��:    public 
// ����:   void
// ����: Type & x
// ����: Type & y
//************************************
template<class Type> void MinHeap<Type>::Swap(Type& x, Type& y) {
	Type tmp = x;
	x = y;
	y = tmp;
}
//************************************
// ȫ��:  MinHeap::SiftUp
// ����: �ѣ��������ϵ���
// Ȩ��:    public 
// ����:   void
// ����: int node
//************************************
template<class Type> void MinHeap<Type>::SiftUp(int node) {
	int cur = node, curParent = node >> 1;
	while (curParent >= 1) {
		if (heapArray[cur] > heapArray[curParent])break;
		Swap(heapArray[cur], heapArray[curParent]);
		cur = curParent;
		curParent >>= 1;
	}
}
//************************************
// ȫ��:  MinHeap::SiftDown
// ����: �ѣ��������µ���
// Ȩ��:    public 
// ����:   void
// ����: int node
//************************************
template<class Type> void MinHeap<Type>::SiftDown(int node) {
	int cur = node, curChild = node << 1;
	while (curChild <= heapSize) {
		if (curChild != heapSize) {
			if (heapArray[curChild + 1] < heapArray[curChild]) curChild++;
		}
		if (heapArray[curChild] > heapArray[cur])break;
		Swap(heapArray[curChild], heapArray[cur]);
		cur = curChild;
		curChild <<= 1;
	}
}

//��С������

//************************************
// ȫ��:  MinSpanningTree::NewNode
// ����: �½�����
// Ȩ��:    public 
// ����:   void
// ����: std::string alias ��������
//************************************
void MinSpanningTree::NewNode(std::string alias) {
	GraphInfo.NewNode(alias);
}
//************************************
// ȫ��:  MinSpanningTree::AddEdge
// ����: �½����ߣ�ͬʱ����Ƿ񹹳ɶ���ͼ��
// Ȩ��:    public 
// ����:   void
// ����: std::string u �������
// ����: std::string v �յ�����
// ����: int w ��Ȩ
//************************************
void MinSpanningTree::AddEdge(std::string u, std::string v, int w) {
	if (u == v) {
		std::cout << "�����������������ıߣ��˼ӱ߲����ѷ�����" << std::endl;
		return;
	}
	if (!ALLOW_MULTIEDGE) {
		Pair<std::string> InsPair, InsPairRev;
		InsPair.a = u; InsPairRev.a = v;
		InsPair.b = v; InsPairRev.b = u;
		bool InsPairFound, InsPairRevFound;
		MultipleEdgeCheck.Find(InsPair, InsPairFound);
		MultipleEdgeCheck.Find(InsPairRev, InsPairRevFound);
		if (InsPairFound || InsPairFound) {
			std::cout << "��������֮���Ѿ������ߣ�������ĿҪ�����ƣ����ر߲��������ʴ˼ӱ߲����ѷ���" << std::endl;
			return;
		}
		MultipleEdgeCheck.Insert(InsPair);
		MultipleEdgeCheck.Insert(InsPairRev);
		GraphInfo.AddEdge(u, v, w, true);
		GraphInfo.AddEdge(v, u, w, false);
	}
	else {
		GraphInfo.AddEdge(u, v, w, true);
		GraphInfo.AddEdge(v, u, w, false);
	}
}

//************************************
// ȫ��:  MinSpanningTree::SolveMST_Prim
// ����: ʹ�ö��Ż���Prim�����С������
// Ȩ��:    public 
// ����:   void
// ����: std::string startingPoint �������
//************************************
void MinSpanningTree::SolveMST_Prim(std::string startingPoint) {
	//�����߶�
	MinHeap<Edge> Heap;
	Heap.Rebuild(GraphInfo.edgeCounter);
	Edge HeapTop;
	//��ȡ������ڽ��
	bool success;
	VertexInfo startPt = GraphInfo.dict.Find(startingPoint, success);
	if (!success) {
		std::cout << "���㲻����" << std::endl;
		return;
	}
	//����״̬
	bool *visitedStatus = new bool[GraphInfo.vertexCounter];
	for (int i = 0; i < GraphInfo.vertexCounter; i++) visitedStatus[i] = false;
	//��ʼ�����״̬
	visitedStatus[startPt.identity] = true;
	for (LinkedListNode<Edge>*i = (startPt.linklistNodePtr->data)->GetHead()->succ; i != nullptr; i = i->succ) {
		if (visitedStatus[((AVLTreeNode<VertexInfo>*)(i->data.vInfPtr))->data.identity] == false) {
			Heap.Insert(i->data);
		}
	}
	//����MST
	while (Heap.heapSize) {
		HeapTop = Heap.GetTop();
		Heap.Pop();
		if (visitedStatus[((AVLTreeNode<VertexInfo>*)(HeapTop.vInfPtr))->data.identity] == true) {
			continue;
		}
		Result.InsertTail(HeapTop);
		visitedStatus[((AVLTreeNode<VertexInfo>*)(HeapTop.vInfPtr))->data.identity] = true;
		for (LinkedListNode<Edge>*i = HeapTop.toLinkedListPtr->data->GetHead()->succ; i != nullptr; i = i->succ) {
			if (visitedStatus[((AVLTreeNode<VertexInfo>*)(i->data.vInfPtr))->data.identity] == false) {
				Heap.Insert(i->data);
			}
		}
	}

	//�ж���ͨ��
	for (int i = 0; i < GraphInfo.vertexCounter; i++) {
		if (!visitedStatus[i]) {
			std::cout << "��ʾ��ԭͼδ��ͨ��������С��������������" << std::endl;
			delete[] visitedStatus;
			return;
		}
	}
	//�ͷſռ�
	delete[] visitedStatus;
	std::cout << "�Ѿ�����Prim��С������" << std::endl;
	AnswerStat = true;
}
//************************************
// ȫ��:  MinSpanningTree::PrintResult
// ����: �����С���������
// Ȩ��:    public 
// ����:   void
//************************************
void MinSpanningTree::PrintResult() {
	//������
	if (AnswerStat == false) {//���δ����ʱ�Ĵ���
		std::cout << "����������С���������ٲ鿴�����" << std::endl;
		return;
	}
	std::cout << "��С�������Ķ��㼰��Ϊ��" << std::endl << std::endl;
	VertexInfo u, v;
	for (LinkedListNode<Edge>* i = Result.GetHead()->succ; i != nullptr; i = i->succ) {//�����������
		u = ((AVLTreeNode<VertexInfo>*)(i->data.uInfPtr))->data;
		v = ((AVLTreeNode<VertexInfo>*)(i->data.vInfPtr))->data;
		std::cout << u.alias << "-(" << i->data.weight << ")->" << v.alias << "\t";
	}
	std::cout << std::endl;
}

//���ϵͳ
//************************************
// ȫ��:  ElectricitySystem_Solution::ShowMenu
// ����: ���ϵͳ����ʾ�˵�
// Ȩ��:    public 
// ����:   void
//************************************
void ElectricitySystem_Solution::ShowMenu() {
	std::cout << std::endl;
	std::cout << "**\t\t�������ģ��ϵͳ\t\t**" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "**\t\tA --- ������������\t\t**" << std::endl;
	std::cout << "**\t\tB --- ��ӵ����ı�\t\t**" << std::endl;
	std::cout << "**\t\tC --- ������С������\t\t**" << std::endl;
	std::cout << "**\t\tD --- ��ʾ��С������\t\t**" << std::endl;
	std::cout << "**\t\tE --- �˳�  ����\t\t**" << std::endl;
}

//************************************
// ȫ��:  ElectricitySystem_Solution::Main
// ����: ���ϵͳ��������
// Ȩ��:    public 
// ����:   void
//************************************
void ElectricitySystem_Solution::Main() {
	ShowMenu();
	std::string inputOption;
	while (1) {
		std::cout << std::endl;
		std::cout << "��ѡ�������";
		//std::getline(std::cin, inputOption);
		std::cin >> inputOption;
		if (inputOption.length() != 1)continue;

		int newVertexCount, edgeWeight;
		std::string vertexNameA, vertexNameB;
		std::string readIn;
		switch (inputOption[0]) {
		case 'A': //��������
			while (1) {
				std::cout << "�����붥��ĸ���: ";
				std::cin >> readIn;
				if (isDigitStr(readIn)) {
					try {
						newVertexCount = std::stoi(readIn);
					}
					catch (std::out_of_range) {
						std::cout << "���������̫������������" << std::endl;
						continue;
					}
					break;
				}
				std::cout << "����Ĳ�����Ч���֣�����������" << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}


			for (int i = 0; i < newVertexCount; i++) {
				std::cin >> vertexNameA;
				MST.NewNode(vertexNameA);
				MST.AnswerStat = false;
			}

			break;
		case 'B': //������
			std::cout << "����Ҫֹͣ���룬������? ? 0��س��� " << std::endl;
			while (1) {
				std::cout << "�������������㼰��: ";
				std::cin >> vertexNameA >> vertexNameB;
				std::cin >> readIn;

				if (isDigitStr(readIn)) {
					try {
						edgeWeight = std::stoi(readIn);
					}
					catch (std::out_of_range) {
						std::cout << "��Ȩ���������̫������������" << std::endl;
						continue;
					}
				}
				else {
					std::cout << "�ߵ�Ȩֵ����Ĳ���������������������" << std::endl;
					continue;
				}

				if (vertexNameA == "?"&&vertexNameB == "?") {
					break;
				}
				MST.AddEdge(vertexNameA, vertexNameB, edgeWeight);
				MST.AnswerStat = false;
			}
			break;
		case 'C': //������С������
			MST.ClearResult();
			MST.AnswerStat = false;
			std::cout << "��������ʼ����:";
			std::cin >> vertexNameA;
			MST.SolveMST_Prim(vertexNameA);
			break;
		case 'D': //������
			MST.PrintResult();
			break;
		case 'E':
			return;
		default:
			std::cout << "��������Ч��������A~E�еĲ����롣" << std::endl;
		}
	}
	std::cout << std::endl;
}

int main() {
	ElectricitySystem_Solution Solution;
	Solution.Main();
#ifdef _WIN32
	system("pause"); 
#endif
	return 0;
}