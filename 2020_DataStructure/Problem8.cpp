#include <iostream>
#include <string>
#include <climits>
#include <stdexcept>
#include <fstream>

// 多重图说明
// 由于多重图并不影响最小生成树算法的正确性，下面的宏定义给出一个允许/禁止多重图的设置
// 当多重图被禁止时，若两个顶点A和B间已经有权为w的边，则A和B间路径数为1的最短路径将被固定为w，无法修改
// 当多重图允许时，允许缩短两个顶点间的直接连边的最小边权，该操作可以通过加边使图成为多重图实现

#define ALLOW_MULTIEDGE false //是否允许多重边，是则为true



//************************************
// 全名:  isDigitStr
// 功能: 判断一个字符串是否是数字字符串
// 权限:    public 
// 返回:   bool
// 参数: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}

class VertexInfo; //顶点信息
template<class Type> class LinkedListNode; //链表结点
template<class Type> class LinkedList; //链表
class Edge; //边
template<class Type>class AVLTreeNode; //AVL结点
template<class TypeA>class Pair; //点对


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

template<class Type> class LinkedListNode { // 链表节点信息
public:
	Type data;
	LinkedListNode *pred = nullptr, *succ = nullptr;
};
template<class Type> class LinkedList { //链表类
private:
	LinkedListNode<Type> *head = nullptr, *tail = nullptr; //链表头尾指针
	int listSize = 0; //链表大小
public:
	LinkedList<Type>();
	~LinkedList<Type>();
	LinkedListNode<Type>* GetHead(); //获得头指针地址
	void InsertTail(const Type& data); //在链表尾部插入内容
	void PopTail(); //删除链表尾部结点
	LinkedListNode<Type>* GetTail(); //获取链表尾指针
	int GetSize(); //获取链表大小
	void Clear(); //清空链表
};

class Edge { // 边对象
public:
	int to, weight; //边的终点和权值
	LinkedListNode<LinkedList<Edge>*> *toLinkedListPtr = nullptr; //边终点所在邻接表中的位置
	AVLTreeNode<VertexInfo> *uInfPtr, *vInfPtr; //边起点和终点所在AVL结点中的指针
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
class VertexInfo { //储存顶点信息
public:
	int identity; //顶点编号
	std::string alias; //顶点名称
	AVLTreeNode<VertexInfo>  *bstNodePtr = nullptr; //顶点在AVL树中结点的地址
	LinkedListNode<LinkedList<Edge>*> *linklistNodePtr = nullptr; //顶点在邻接表中存储边的链表的地址
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
template<class Type>class AVLTreeNode { //AVL数节点信息
public:
	Type data;
	AVLTreeNode *leftChild = nullptr, *rightChild = nullptr;
	int height = 0;
};
template<class Type>class AVLTree { //AVL树
private:
	AVLTreeNode<Type> *root = nullptr; //根节点
	int GetBalanceFactor(AVLTreeNode<Type>* node); //获取平衡因子
	int GetMaxChildHeight(AVLTreeNode<Type>* node); //获取最大子树高度
	AVLTreeNode<Type>* RotationL(AVLTreeNode<Type>* node); //左旋
	AVLTreeNode<Type>* RotationR(AVLTreeNode<Type>* node); //右旋
	AVLTreeNode<Type>* RotationLR(AVLTreeNode<Type>* node); //左右旋
	AVLTreeNode<Type>* RotationRL(AVLTreeNode<Type>* node); //右左旋
	AVLTreeNode<Type>* Insert(Type value, AVLTreeNode<Type>* node); //插入
public:
	~AVLTree();
	AVLTreeNode<Type>* LastInsertedNode = nullptr; //上一个插入的结点
	void Insert(const Type& value); //插入结点
	Type Find(Type value, bool &success); //查找结点

};
class HashTable { //哈希表
private:
	AVLTree<VertexInfo> *bucket; //散列表
	const int modFactor = 943; //取模的质数
	int totalCounter = 0; //元素个数
public:
	HashTable();
	~HashTable();
	int GetHashCode(std::string alias); //获得一个字符串的散列值
	AVLTreeNode<VertexInfo>* Insert(std::string alias); //在散列表中插入一个顶点
	VertexInfo Find(std::string alias, bool &success); //在散列表中查找一个顶点
};
class AdjacentTable { //邻接表
public:
	int vertexCounter = 0; //顶点个数
	LinkedList<LinkedList<Edge>*> table; //邻接表
	LinkedListNode<LinkedList<Edge>*>* InsertNewNode(); //新建顶点
	void AddEdge(LinkedListNode<LinkedList<Edge>*>* u, LinkedListNode<LinkedList<Edge>*>* v, int w, AVLTreeNode<VertexInfo>* uInfPtr, AVLTreeNode<VertexInfo>* vInfPtr); //新建连边
};

template<class Type>class MinHeap { //最小堆
public:
	Type *heapArray = nullptr; //储存堆的数组
	int heapSize = 0; //堆元素的个数
	void Rebuild(int size); //重新设置堆的最大容量
	void Insert(Type x);//在堆中插入元素
	Type GetTop();//获得堆顶元素
	void Pop();//删除堆顶元素
	void SiftUp(int node); //向上调整
	void SiftDown(int node);//向下调整
	void Swap(Type& x, Type&y);//交换元素
	~MinHeap() { if (heapArray)delete[]heapArray; }
};
class Graph { // 储存图的信息
public:
	AdjacentTable adj; //邻接表(以整数为ID的图)
	HashTable dict; //顶点名称字典
	int vertexCounter = 0, edgeCounter = 0;
	void NewNode(std::string alias); //新建节点
	void AddEdge(std::string u, std::string v, int w, bool showTip = true); //添加连边
};

class MinSpanningTree { //最小生成树
public:
	Graph GraphInfo; //储存图的信息
	LinkedList<Edge> Result; //储存最小生成树结果
	AVLTree<Pair<std::string>> MultipleEdgeCheck; //用于检查重边
	bool AnswerStat = false;

	void NewNode(std::string alias); //新建节点
	void AddEdge(std::string u, std::string w, int v); //添加连边
	void SolveMST_Prim(std::string startingPoint); //求解最小生成树
	void PrintResult(); //输出结果
	void ClearResult() { Result.Clear(); } //重置结果
};

class ElectricitySystem_Solution { //造价系统
public:
	MinSpanningTree MST; //图的储存和最小生成树求解

	void ShowMenu(); //显示菜单
	void Main(); //主界面
};




//链表类定义
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
// 全名:  LinkedList<Type>::Clear
// 功能: 清空并重新初始化链表
// 权限:    public 
// 返回:   void
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
// 全名:  LinkedList::InsertTail
// 功能: 在链表尾部插入元素
// 权限:    public 
// 返回:   void
// 参数: const Type & data 元素的值
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
// 全名:  LinkedList::GetHead
// 功能: 获取链表表头指针
// 权限:    public 
// 返回:   std::*
//************************************
template<class Type>LinkedListNode<Type>* LinkedList<Type>::GetHead() {
	return head;
}
template<class Type>void LinkedList<Type>::PopTail() { //删除尾结点
	if (tail != head) {
		LinkedListNode<Type>* tailPred = tail->pred;
		tailPred->succ = nullptr;
		delete tail;
		tail = tailPred;
		listSize--;
	}
}
//************************************
// 全名:  LinkedList::GetTail
// 功能: 获取链表表尾指针
// 权限:    public 
// 返回:   std::*
//************************************
template<class Type> LinkedListNode<Type>* LinkedList<Type>::GetTail() {
	return tail;
}
//************************************
// 全名:  LinkedList::GetSize
// 功能: 获取链表大小
// 权限:    public 
// 返回:   int
//************************************
template<class Type> int LinkedList<Type>::GetSize() {
	return listSize;
}
// AVL 平衡树 定义开始

//************************************
// 全名:  AVLTree::GetBalanceFactor
// 功能: 获取AVL结点的平衡因子
// 权限:    private 
// 返回:   int
// 参数: AVLTreeNode<Type> * node 获取平衡因子的结点
//************************************
template<class Type>int AVLTree<Type>::GetBalanceFactor(AVLTreeNode<Type>* node) { //获取平衡因子
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return lch - rch;
}
//************************************
// 全名:  AVLTree::GetMaxChildHeight
// 功能: 获取最大子树高度
// 权限:    private 
// 返回:   int
// 参数: AVLTreeNode<Type> * node 获取子树高度的结点
//************************************
template<class Type>int AVLTree<Type>::GetMaxChildHeight(AVLTreeNode<Type>* node) { //获取子树最大高度
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return (lch > rch) ? lch : rch;
}
//************************************
// 全名:  AVLTree::RotationL
// 功能: AVL左旋
// 权限:    private 
// 返回:   AVLTreeNode<Type>* 左旋后的根节点
// 参数: AVLTreeNode<Type> * node 左旋操作的(子树的)根结点
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationL(AVLTreeNode<Type>* node) { //左旋（对于 R-R 型）
	AVLTreeNode<Type> *rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	node->height = GetMaxChildHeight(node) + 1;
	rightChild->height = GetMaxChildHeight(rightChild) + 1;
	if (root == node)root = rightChild;
	return rightChild;
}
//************************************
// 全名:  AVLTree::RotationR
// 功能: AVL 右旋
// 权限:    private 
// 返回:   AVLTreeNode<Type>* 右旋后的根节点
// 参数: AVLTreeNode<Type> * node 右旋操作的根节点
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationR(AVLTreeNode<Type>* node) { //右旋（对于L-L型）
	AVLTreeNode<Type> *leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild;
	leftChild->rightChild = node;
	node->height = GetMaxChildHeight(node) + 1;
	leftChild->height = GetMaxChildHeight(node) + 1;
	if (root == node)root = leftChild;
	return leftChild;
}
//************************************
// 全名:  AVLTree::RotationLR
// 功能: AVL左旋-右旋
// 权限:    private 
// 返回:   AVLTreeNode<Type>* 旋转后的根节点
// 参数: AVLTreeNode<Type> * node 进行旋转的根节点
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationLR(AVLTreeNode<Type>* node) { //先左旋转后右旋 （对于L-R型)
	node->leftChild = RotationL(node->leftChild);
	return RotationR(node);
}
//************************************
// 全名:  AVLTree::RotationRL
// 功能: AVL 右旋-左旋
// 权限:    private 
// 返回:   AVLTreeNode<Type>* 旋转后的根节点
// 参数: AVLTreeNode<Type> * node 进行旋转的根节点
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::RotationRL(AVLTreeNode<Type>* node) { //先右旋后左旋（对于R-L型）
	node->rightChild = RotationR(node->rightChild);
	return RotationL(node);
}

//************************************
// 全名:  AVLTree::Insert
// 功能:  AVL 插入
// 权限:    public 
// 返回:   AVLTreeNode<Type>* 插入结点的地址
// 参数: Type value 要插入的值
// 参数: AVLTreeNode<Type> * node 当前查找的结点
//************************************
template<class Type>AVLTreeNode<Type>* AVLTree<Type>::Insert(Type value, AVLTreeNode<Type>* node) { //结点插入
	//初始化空树
	if (root == nullptr) {
		root = new AVLTreeNode<Type>;
		root->data = value;
		root->height = 1;
		LastInsertedNode = root;
		return root;
	}

	//插入节点
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

	//更新树高度
	node->height = GetMaxChildHeight(node) + 1;

	//树的平衡调整
	int balanceFactor = GetBalanceFactor(node);
	if (balanceFactor == 0 || balanceFactor == 1 || balanceFactor == -1) return node;
	if (balanceFactor > 1 && GetBalanceFactor(node->leftChild) > 0) { //LL型不平衡-右旋
		return RotationR(node);
	}
	if (balanceFactor < -1 && GetBalanceFactor(node->rightChild) < 0) { //RR型不平衡-左旋
		return RotationL(node);
	}
	if (balanceFactor > 1 && GetBalanceFactor(node->leftChild) < 0) { //LR型不平衡-先左后右
		return RotationLR(node);
	}
	if (balanceFactor < -1 && GetBalanceFactor(node->rightChild)>0) {//RL型不平衡-先右后左
		return RotationRL(node);
	}
}
//************************************
// 全名:  AVLTree::Insert
// 功能: AVL 插入
// 权限:    public 
// 返回:   void
// 参数: const Type & value 要插入的元素
//************************************
template<class Type> void AVLTree<Type>::Insert(const Type& value) { //AVL树结点插入-外部调用
	Insert(value, root);
}
//************************************
// 全名:  AVLTree::Find
// 功能: AVL 查找
// 权限:    public 
// 返回:   Type 查找到的值
// 参数: Type value 要查找的值的关键码
// 参数: bool & success 查找成功状态
//************************************
template<class Type> Type AVLTree<Type>::Find(Type value, bool &success) { //查找
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
template<class Type> AVLTree<Type>::~AVLTree<Type>() { //析构平衡树
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

//哈希表开始
HashTable::HashTable() {
	bucket = new AVLTree<VertexInfo>[modFactor];
}
HashTable::~HashTable() {
	if (bucket != nullptr) {
		delete[]bucket;
	}
}
//************************************
// 全名:  HashTable::GetHashCode
// 功能: 获取一个字符串的散列值
// 权限:    public 
// 返回:   int 字符串的散列值
// 参数: std::string alias 用于计算的字符串
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
// 全名:  HashTable::Insert
// 功能: 哈希表插入
// 权限:    public 
// 返回:   AVLTreeNode<VertexInfo>* 插入后，该值所在的散列表的对应Hash值的AVL树中的AVL结点地址
// 参数: std::string alias 要插入的字符串
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
// 全名:  HashTable::Find
// 功能: 哈希表查找（按照顶点名查询顶点信息）
// 权限:    public 
// 返回:   VertexInfo 查找到的顶点信息
// 参数: std::string alias 要查找的值
// 参数: bool & success 查找成功状态
//************************************
VertexInfo HashTable::Find(std::string alias, bool &success) {
	int hashcode = GetHashCode(alias);
	VertexInfo findInf;
	findInf.alias = alias;
	VertexInfo ret = bucket[hashcode].Find(findInf, success);
	return ret;
}

//邻接表

//为方便图顶点的插入删除，在此项目中将原邻接表（课本内容）的第一维从顺序表（数组）改为链表
//同时，使用Hash表+AVL树作为查询优化，AVL树结点链向邻接表的第一维中对应顶点的链表对象。
//为了避免极端情况Hash表中的单链表结构在极端的Hash冲突情况下时间复杂度达到最高，故项目实现将单链表改为AVL树
//上述实现的目的为将时间复杂度从O(n)稳定降低至O(logn)
//即项目中的邻接表由嵌套链表实现，其中第一层链表中，每一个链表结点储存一个子链表，子链表表示该顶点的出边
//具体的实现可以参考项目文档"8.docx"

//下文将称第一层链表为【第一层链表】，该链表结点表示的结点在查找结构中对应的结点称为【(对应的)AVL结点】
//与传统邻接表相同的链表，即第一层链表中内嵌的链表，称为【第二层链表】（即结点的出边终点的链表）

//************************************
// 全名:  AdjacentTable::InsertNewNode
// 功能: 邻接表，插入结点（在第一层链表尾部插入结点）
// 权限:    public 
// 返回:   LinkedListNode<LinkedList<Edge>*>* 插入的第一层链表的结点地址
//************************************
LinkedListNode<LinkedList<Edge>*>* AdjacentTable::InsertNewNode() {
	LinkedList<Edge>* w = new LinkedList<Edge>;
	table.InsertTail(w);
	return (table.GetTail());
}
//************************************
// 全名:  AdjacentTable::AddEdge
// 功能: 邻接表，插入连边
// 权限:    public 
// 返回:   void
// 参数: LinkedListNode<LinkedList<Edge> * > * u 起点在第一层链表中对应的结点地址
// 参数: LinkedListNode<LinkedList<Edge> * > * v 终点在第一层链表中对应的结点地址
// 参数: int w 边权
// 参数: AVLTreeNode<VertexInfo> * uInfPtr 起点的AVL结点地址
// 参数: AVLTreeNode<VertexInfo> * vInfPtr 终点的AVL结点地址
//************************************
void AdjacentTable::AddEdge(LinkedListNode<LinkedList<Edge>*>* u, LinkedListNode<LinkedList<Edge>*>* v, int w, AVLTreeNode<VertexInfo>* uInfPtr, AVLTreeNode<VertexInfo>* vInfPtr) {
	Edge newEl;
	newEl.weight = w;
	newEl.toLinkedListPtr = v;
	newEl.uInfPtr = uInfPtr;
	newEl.vInfPtr = vInfPtr;
	u->data->InsertTail(newEl);
}

//图的储存和查找
//************************************
// 全名:  Graph::NewNode
// 功能: 图，添加节点
// 权限:    public 
// 返回:   void
// 参数: std::string alias
//************************************
void Graph::NewNode(std::string alias) {
	bool succ = false;
	dict.Find(alias, succ); //查找该节点名称是否已经存在
	if (succ == true) {
		std::cout << "结点名称:" << alias << "已经存在，重复的结点将不会被重复加入" << std::endl;
		return;
	}

	LinkedListNode<LinkedList<Edge>*>* adjNewPtr = adj.InsertNewNode();
	AVLTreeNode<VertexInfo>* bstNewPtr = dict.Insert(alias);
	AVLTreeNode<VertexInfo>* bstPtr = bstNewPtr;
	bstPtr->data.linklistNodePtr = adjNewPtr;
	vertexCounter++;
}

//************************************
// 全名:  Graph::AddEdge
// 功能: 
// 权限:    public 
// 返回:   void
// 参数: std::string u 起点名称
// 参数: std::string v 终点名称
// 参数: int w 边权
// 参数: bool showTip 是否显示操作提示信息
//************************************
void Graph::AddEdge(std::string u, std::string v, int w, bool showTip) {
	bool ust, vst;
	VertexInfo uid = dict.Find(u, ust), vid = dict.Find(v, vst); //确定顶点名称是否有效
	if (ust&&vst) {
		edgeCounter++;
		adj.AddEdge((LinkedListNode<LinkedList<Edge>*>*) (uid.linklistNodePtr), (LinkedListNode<LinkedList<Edge>*>*) (vid.linklistNodePtr), w, uid.bstNodePtr, vid.bstNodePtr);
	}
	else {
		if (showTip == false)return;
		if (!ust && !vst) {
			std::cout << "结点名称:" << u << "与" << v << "均不存在，此添加操作已被忽略" << std::endl;
		}
		else if (!ust) {
			std::cout << "结点名称:" << u << "不存在，此添加操作已被忽略" << std::endl;
		}
		else if (!vst) {
			std::cout << "结点名称:" << v << "不存在，此添加操作已被忽略" << std::endl;
		}
	}
}


//堆
//************************************
// 全名:  MinHeap::Rebuild
// 功能: 堆，重分配空间（清除原有堆的内容），并重分配大小
// 权限:    public 
// 返回:   void
// 参数: int size
//************************************
template<class Type> void MinHeap<Type>::Rebuild(int size) {
	if (heapArray != nullptr)delete[]heapArray;
	heapArray = new Type[size + 1];
	heapSize = 0;
}
//************************************
// 全名:  MinHeap::GetTop
// 功能: 获取堆顶元素
// 权限:    public 
// 返回:   Type
//************************************
template<class Type> Type MinHeap<Type>::GetTop() {
	return heapArray[1];
}
//************************************
// 全名:  MinHeap::Insert
// 功能: 堆，插入元素
// 权限:    public 
// 返回:   void
// 参数: Type x 元素的值
//************************************
template<class Type> void MinHeap<Type>::Insert(Type x) {
	heapArray[++heapSize] = x;
	SiftUp(heapSize);
}
//************************************
// 全名:  MinHeap::Pop
// 功能: 堆，弹出堆顶元素
// 权限:    public 
// 返回:   void
//************************************
template<class Type> void MinHeap<Type>::Pop() {
	heapArray[1] = heapArray[heapSize--];
	SiftDown(1);
}
//************************************
// 全名:  MinHeap::Swap
// 功能: 交换元素
// 权限:    public 
// 返回:   void
// 参数: Type & x
// 参数: Type & y
//************************************
template<class Type> void MinHeap<Type>::Swap(Type& x, Type& y) {
	Type tmp = x;
	x = y;
	y = tmp;
}
//************************************
// 全名:  MinHeap::SiftUp
// 功能: 堆，自下向上调整
// 权限:    public 
// 返回:   void
// 参数: int node
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
// 全名:  MinHeap::SiftDown
// 功能: 堆，自上向下调整
// 权限:    public 
// 返回:   void
// 参数: int node
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

//最小生成树

//************************************
// 全名:  MinSpanningTree::NewNode
// 功能: 新建顶点
// 权限:    public 
// 返回:   void
// 参数: std::string alias 顶点名称
//************************************
void MinSpanningTree::NewNode(std::string alias) {
	GraphInfo.NewNode(alias);
}
//************************************
// 全名:  MinSpanningTree::AddEdge
// 功能: 新建连边（同时检查是否构成多重图）
// 权限:    public 
// 返回:   void
// 参数: std::string u 起点名称
// 参数: std::string v 终点名称
// 参数: int w 边权
//************************************
void MinSpanningTree::AddEdge(std::string u, std::string v, int w) {
	if (u == v) {
		std::cout << "不允许出现自身到自身的边，此加边操作已放弃。" << std::endl;
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
			std::cout << "两个顶点之间已经有连边，由于项目要求限制，多重边不被允许，故此加边操作已放弃" << std::endl;
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
// 全名:  MinSpanningTree::SolveMST_Prim
// 功能: 使用堆优化的Prim求解最小生成树
// 权限:    public 
// 返回:   void
// 参数: std::string startingPoint 起点名称
//************************************
void MinSpanningTree::SolveMST_Prim(std::string startingPoint) {
	//建立边堆
	MinHeap<Edge> Heap;
	Heap.Rebuild(GraphInfo.edgeCounter);
	Edge HeapTop;
	//获取起点所在结点
	bool success;
	VertexInfo startPt = GraphInfo.dict.Find(startingPoint, success);
	if (!success) {
		std::cout << "顶点不存在" << std::endl;
		return;
	}
	//访问状态
	bool *visitedStatus = new bool[GraphInfo.vertexCounter];
	for (int i = 0; i < GraphInfo.vertexCounter; i++) visitedStatus[i] = false;
	//初始点更新状态
	visitedStatus[startPt.identity] = true;
	for (LinkedListNode<Edge>*i = (startPt.linklistNodePtr->data)->GetHead()->succ; i != nullptr; i = i->succ) {
		if (visitedStatus[((AVLTreeNode<VertexInfo>*)(i->data.vInfPtr))->data.identity] == false) {
			Heap.Insert(i->data);
		}
	}
	//构建MST
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

	//判断连通性
	for (int i = 0; i < GraphInfo.vertexCounter; i++) {
		if (!visitedStatus[i]) {
			std::cout << "提示：原图未连通，求解的最小生成树不完整。" << std::endl;
			delete[] visitedStatus;
			return;
		}
	}
	//释放空间
	delete[] visitedStatus;
	std::cout << "已经生成Prim最小生成树" << std::endl;
	AnswerStat = true;
}
//************************************
// 全名:  MinSpanningTree::PrintResult
// 功能: 输出最小生成树结果
// 权限:    public 
// 返回:   void
//************************************
void MinSpanningTree::PrintResult() {
	//结果输出
	if (AnswerStat == false) {//结果未生成时的处理
		std::cout << "请先生成最小生成树后，再查看结果。" << std::endl;
		return;
	}
	std::cout << "最小生成树的顶点及边为：" << std::endl << std::endl;
	VertexInfo u, v;
	for (LinkedListNode<Edge>* i = Result.GetHead()->succ; i != nullptr; i = i->succ) {//遍历结果链表
		u = ((AVLTreeNode<VertexInfo>*)(i->data.uInfPtr))->data;
		v = ((AVLTreeNode<VertexInfo>*)(i->data.vInfPtr))->data;
		std::cout << u.alias << "-(" << i->data.weight << ")->" << v.alias << "\t";
	}
	std::cout << std::endl;
}

//造价系统
//************************************
// 全名:  ElectricitySystem_Solution::ShowMenu
// 功能: 造价系统，显示菜单
// 权限:    public 
// 返回:   void
//************************************
void ElectricitySystem_Solution::ShowMenu() {
	std::cout << std::endl;
	std::cout << "**\t\t电网造价模拟系统\t\t**" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "**\t\tA --- 创建电网顶点\t\t**" << std::endl;
	std::cout << "**\t\tB --- 添加电网的边\t\t**" << std::endl;
	std::cout << "**\t\tC --- 构造最小生成树\t\t**" << std::endl;
	std::cout << "**\t\tD --- 显示最小生成树\t\t**" << std::endl;
	std::cout << "**\t\tE --- 退出  程序\t\t**" << std::endl;
}

//************************************
// 全名:  ElectricitySystem_Solution::Main
// 功能: 造价系统，主过程
// 权限:    public 
// 返回:   void
//************************************
void ElectricitySystem_Solution::Main() {
	ShowMenu();
	std::string inputOption;
	while (1) {
		std::cout << std::endl;
		std::cout << "请选择操作：";
		//std::getline(std::cin, inputOption);
		std::cin >> inputOption;
		if (inputOption.length() != 1)continue;

		int newVertexCount, edgeWeight;
		std::string vertexNameA, vertexNameB;
		std::string readIn;
		switch (inputOption[0]) {
		case 'A': //建立顶点
			while (1) {
				std::cout << "请输入顶点的个数: ";
				std::cin >> readIn;
				if (isDigitStr(readIn)) {
					try {
						newVertexCount = std::stoi(readIn);
					}
					catch (std::out_of_range) {
						std::cout << "输入的数字太大，请重新输入" << std::endl;
						continue;
					}
					break;
				}
				std::cout << "输入的不是有效数字，请重新输入" << std::endl;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}


			for (int i = 0; i < newVertexCount; i++) {
				std::cin >> vertexNameA;
				MST.NewNode(vertexNameA);
				MST.AnswerStat = false;
			}

			break;
		case 'B': //建立边
			std::cout << "（若要停止输入，请输入? ? 0后回车） " << std::endl;
			while (1) {
				std::cout << "请输入两个顶点及边: ";
				std::cin >> vertexNameA >> vertexNameB;
				std::cin >> readIn;

				if (isDigitStr(readIn)) {
					try {
						edgeWeight = std::stoi(readIn);
					}
					catch (std::out_of_range) {
						std::cout << "边权输入的数字太大，请重新输入" << std::endl;
						continue;
					}
				}
				else {
					std::cout << "边的权值输入的不是正整数，请重新输入" << std::endl;
					continue;
				}

				if (vertexNameA == "?"&&vertexNameB == "?") {
					break;
				}
				MST.AddEdge(vertexNameA, vertexNameB, edgeWeight);
				MST.AnswerStat = false;
			}
			break;
		case 'C': //构造最小生成树
			MST.ClearResult();
			MST.AnswerStat = false;
			std::cout << "请输入起始顶点:";
			std::cin >> vertexNameA;
			MST.SolveMST_Prim(vertexNameA);
			break;
		case 'D': //输出结果
			MST.PrintResult();
			break;
		case 'E':
			return;
		default:
			std::cout << "操作码无效，请输入A~E中的操作码。" << std::endl;
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
