#include<iostream>
#include<string>
template<class Type> class LinkedListNode {
public:
	Type data;
	LinkedListNode<Type> *pred = nullptr, *succ = nullptr;
};
template<class Type> class LinkedList {
public:
	LinkedListNode<Type> *head = nullptr, *tail = nullptr;
	int listSize = 0;
	LinkedList<Type>();//构造空链表
	~LinkedList<Type>();//析构链表
	void DeleteByPointer(LinkedListNode<Type>* NodePtr); //按照结点指针删除结点
	void InsertTail(const Type& data); //在链表尾部插入节点
	void RemoveTail();
	void RemoveFront();
};

template<class Type> class AVLTreeNode { //AVL结点（用于成员信息存储）
public:
	bool lazy = false; //结点是否被失效(失效结点将在有新元素插入时被覆盖)
	Type data;
	int height = 0;
	AVLTreeNode<Type> *leftChild = nullptr, *rightChild = nullptr;
};
template<class Type> class AVLTree {//AVL树（用于信息查找和修改）
public:
	AVLTreeNode<Type>* root = nullptr; //AVL根节点
	~AVLTree<Type>();
	AVLTreeNode<Type>* RotateL(AVLTreeNode<Type>* node); //左旋
	AVLTreeNode<Type>* RotateR(AVLTreeNode<Type>* node); //右旋
	AVLTreeNode<Type>* RotateLR(AVLTreeNode<Type>* node); //左旋-右旋
	AVLTreeNode<Type>* RotateRL(AVLTreeNode<Type>* node); //右旋-左旋
	int GetMaxChildHeight(AVLTreeNode<Type>* node); //获取最大子树高度
	int GetBalanceFactor(AVLTreeNode<Type>* node); //获取平衡因数
	AVLTreeNode<Type>* Insert(const Type& data, AVLTreeNode<Type>* node, AVLTreeNode<Type>*& newNodePtr); //插入数据(若数据点存在，则覆盖数据)
	void DeleteLazy(const Type& data); //失效结点（仅标记lazy）
	AVLTreeNode<Type>* Find(const Type& data, AVLTreeNode<Type>* node); //查找结点，返回结点指针
	bool isExistent(const Type& data);//查找值对应节点是否存在（不包括失效节点）
};

class FamilyMember;

class FamilyTreeNode { //家谱树的结点
public:
	typedef AVLTree<FamilyMember>* SearchStructure;

	AVLTreeNode<FamilyMember> *bstPtr = nullptr;//指向信息的指针
	LinkedList<FamilyTreeNode*> child; //成员的儿女
	LinkedListNode<FamilyTreeNode*> *ptrInParent;//此成员位于父结点链表中的位置
	FamilyTreeNode *parent;//父节点

	void NewChild(std::string childName, SearchStructure searchStruct); //新建儿女
	void Rename(std::string newName, SearchStructure searchStruct);//重命名
	void Dissolve(SearchStructure searchStruct); //解散子树
};
class FamilyMember { //家庭成员信息储存(用于BST结点)
public:
	std::string memberName; //成员姓名
	FamilyTreeNode *familyTreePtr; //指向家族树中结点的指针
	bool operator == (const FamilyMember& p)const {
		return memberName == p.memberName;
	}
	bool operator > (const FamilyMember& p) const {
		return memberName > p.memberName;
	}
	bool operator < (const FamilyMember& p) const {
		return memberName < p.memberName;
	}
};



class FamilyTree { //家谱树
public:
	FamilyTreeNode *famRoot = nullptr; //根节点
	AVLTree<FamilyMember> dict; //成员搜索结构

	FamilyTree(); //构造家谱树空树
	~FamilyTree(); //析构家谱树
	FamilyTreeNode* Find(std::string memberName); //查找成员，返回结点指针
	void Main();
};

//链表 定义
template<class Type> LinkedList<Type>::LinkedList() {
	head = new LinkedListNode<Type>;
	tail = head;
}
template<class Type> LinkedList<Type>::~LinkedList() {
	if (head == nullptr)return;
	LinkedListNode<Type> *cur = head, *curNext;
	while (1) {
		curNext = cur->succ;
		delete cur;
		if (curNext == nullptr)break;
		cur = curNext;
	}
}
//************************************
// 全名:  LinkedList::DeleteByPointer
// 功能: 按照链表结点指针删除节点
// 权限:    public 
// 返回:   void
// 参数: LinkedListNode<Type> * NodePtr
//************************************
template<class Type> void LinkedList<Type>::DeleteByPointer(LinkedListNode<Type>* NodePtr) {
	LinkedListNode<Type> *pred, *succ;
	pred = NodePtr->pred;
	succ = NodePtr->succ;
	pred->succ = succ;
	if (succ != nullptr) {
		succ->pred = pred;
	}
	else {
		tail = pred;
	}
	listSize--;
}
//************************************
// 全名:  LinkedList::InsertTail
// 功能: 在链表尾部插入结点
// 权限:    public 
// 返回:   void
// 参数: const Type & data
//************************************
template<class Type> void LinkedList<Type>::InsertTail(const Type& data) {
	LinkedListNode<Type>* newEl = new LinkedListNode<Type>;
	newEl->data = data;
	newEl->pred = tail;
	newEl->succ = nullptr;
	tail->succ = newEl;
	tail = newEl;
	listSize++;
}
//************************************
// 全名:  LinkedList::RemoveTail
// 功能: 若链表非空，删除链表尾部结点
// 权限:    public 
// 返回:   void
//************************************
template<class Type> void LinkedList<Type>::RemoveTail() {
	LinkedListNode<Type>* pred = tail->pred;
	if (listSize == 0)return;
	pred->succ = nullptr;
	delete tail;
	tail = pred;
	listSize--;
}
//************************************
// 全名:  LinkedList::RemoveFront
// 功能: 若链表非空，删除链表头部结点
// 权限:    public 
// 返回:   void
//************************************
template<class Type> void LinkedList<Type>::RemoveFront() {
	if (listSize) {
		LinkedListNode<Type>* temp = head->succ;
		head->succ = head->succ->succ;
		if (head->succ != nullptr) {
			head->succ->pred = head;
		}
		delete temp;
		listSize--;
	}
}
//AVL树 定义 (需要析构！！！）
//************************************
// 全名:  AVLTree::GetMaxChildHeight
// 功能: 获取一个结点，的左右子树的高度最大值
// 权限:    public 
// 返回:   int
// 参数: AVLTreeNode<Type> * node
//************************************
template<class Type> int AVLTree<Type>::GetMaxChildHeight(AVLTreeNode<Type>* node) {
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return (lch > rch) ? lch : rch;
}
//************************************
// 全名:  AVLTree::RotateL
// 功能: AVL左旋
// 权限:    public 
// 返回:   *
// 参数: AVLTreeNode<Type> * node
//************************************
template<class Type> AVLTreeNode<Type>* AVLTree<Type>::RotateL(AVLTreeNode<Type>* node) {
	AVLTreeNode<Type>* rc = node->rightChild;
	node->rightChild = rc->leftChild;
	rc->leftChild = node;
	if (root == node) {
		root = rc;
	}
	node->height = GetMaxChildHeight(node) + 1;
	rc->height = GetMaxChildHeight(rc) + 1;
	return rc;
}
//************************************
// 全名:  AVLTree::RotateR
// 功能: AVL右旋
// 权限:    public 
// 返回:   *
// 参数: AVLTreeNode<Type> * node
//************************************
template<class Type> AVLTreeNode<Type>* AVLTree<Type>::RotateR(AVLTreeNode<Type>* node) {
	AVLTreeNode<Type>* lc = node->leftChild;
	node->leftChild = lc->rightChild;
	lc->rightChild = node;
	if (root == node) {
		root = lc;
	}
	node->height = GetMaxChildHeight(node) + 1;
	lc->height = GetMaxChildHeight(lc) + 1;
	return lc;
}
//************************************
// 全名:  AVLTree::RotateRL
// 功能: AVL右旋-左旋
// 权限:    public 
// 返回:   *
// 参数: AVLTreeNode<Type> * node
//************************************
template <class Type> AVLTreeNode<Type>* AVLTree<Type>::RotateRL(AVLTreeNode<Type>* node) {
	node->rightChild = RotateR(node->rightChild);
	return RotateL(node);
}
//************************************
// 全名:  AVLTree::RotateLR
// 功能: AVL左旋-右旋
// 权限:    public 
// 返回:   *
// 参数: AVLTreeNode<Type> * node
//************************************
template <class Type> AVLTreeNode<Type>* AVLTree<Type>::RotateLR(AVLTreeNode<Type>* node) {
	node->leftChild = RotateL(node->leftChild);
	return RotateR(node);
}
//************************************
// 全名:  AVLTree::Find
// 功能: AVL查找
// 权限:    public 
// 返回:   *
// 参数: const Type & data 要查找的值
// 参数: AVLTreeNode<Type> * node 当前查找的结点
//************************************
template<class Type> AVLTreeNode<Type>* AVLTree<Type>::Find(const Type& data, AVLTreeNode<Type>* node) {
	if (node == nullptr)return nullptr;
	if (data > node->data) {
		if (node->rightChild == nullptr) return nullptr;
		return Find(data, node->rightChild);
	}
	else if (data < node->data) {
		if (node->leftChild == nullptr) return nullptr;
		return Find(data, node->leftChild);
	}
	else {
		return node;
	}
}
//************************************
// 全名:  AVLTree::DeleteLazy
// 功能: 对AVL结点标记lazy
// 权限:    public 
// 返回:   void
// 参数: const Type & data
//************************************
template<class Type> void AVLTree<Type>::DeleteLazy(const Type& data) {
	AVLTreeNode<Type>* res = Find(data, root);
	if (res != nullptr) {
		res->lazy = true;
	}
}
//************************************
// 全名:  AVLTree::isExistent
// 功能: 判断一个值是否在AVL树中存在（不包括被标记lazy的结点）
// 权限:    public 
// 返回:   bool
// 参数: const Type & data
//************************************
template<class Type> bool AVLTree<Type>::isExistent(const Type& data) {
	AVLTreeNode<Type>* res = Find(data, root);
	if (res == nullptr) return false;
	if (res->lazy == true) return false;
	return true;
}
//************************************
// 全名:  AVLTree::GetBalanceFactor
// 功能: 获取结点平衡因子
// 权限:    public 
// 返回:   int
// 参数: AVLTreeNode<Type> * node
//************************************
template<class Type> int AVLTree<Type>::GetBalanceFactor(AVLTreeNode<Type>* node) {
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return rch - lch;
}
//************************************
// 全名:  AVLTree::Insert
// 功能: AVL插入数据
// 权限:    public 
// 返回:   *
// 参数: const Type & data 要插入的数据
// 参数: AVLTreeNode<Type> * node 当前查找的结点
// 参数: AVLTreeNode<Type> * & newNodePtr 插入或覆盖的AV了结点指针返回
//************************************
template<class Type> AVLTreeNode<Type>* AVLTree<Type>::Insert(const Type& data, AVLTreeNode<Type>* node, AVLTreeNode<Type>*& newNodePtr) {
	//若为空树，初始化
	if (root == nullptr) {
		root = new AVLTreeNode<Type>;
		root->data = data;
		newNodePtr = root;
		return root;
	}

	//查找目标
	AVLTreeNode<Type>** insPlace = nullptr;
	if (data == node->data) { //覆盖结点
		node->data = data;
		node->lazy = false;
		newNodePtr = node;
		return root;
	}
	if (data < node->data) {
		insPlace = &(node->leftChild);
	}
	else if (data > node->data) {
		insPlace = &(node->rightChild);
	}
	if (*insPlace == nullptr) {
		*insPlace = new AVLTreeNode<Type>;
		(*insPlace)->data = data;
		(*insPlace)->lazy = false;
		(*insPlace)->height = 1;
		newNodePtr = (*insPlace);
	}
	else {
		(*insPlace) = Insert(data, *insPlace, newNodePtr);
	}

	//更新高度
	node->height = GetMaxChildHeight(node) + 1;

	//平衡化树
	int bf = -GetBalanceFactor(node);
	if (bf == 0 || bf == -1 || bf == 1)return node;
	else if (bf > 1 && -GetBalanceFactor(node->leftChild) > 0) {
		return RotateR(node);
	}
	else if (bf < -1 && -GetBalanceFactor(node->rightChild) < 0) {
		return RotateL(node);
	}
	else if (bf > 1 && -GetBalanceFactor(node->leftChild) < 0) {
		return RotateLR(node);
	}
	else if (bf < -1 && -GetBalanceFactor(node->rightChild)>0) {
		return RotateRL(node);
	}
	return nullptr;
}
template<class Type> AVLTree<Type>::~AVLTree() {
	LinkedList<AVLTreeNode<Type>*> nodeList;
	AVLTreeNode<Type>* queueTop;
	if (root == nullptr)return;
	nodeList.InsertTail(root);
	while (nodeList.listSize) {
		queueTop = nodeList.head->succ->data;
		nodeList.RemoveFront();
		if (queueTop->leftChild)nodeList.InsertTail(queueTop->leftChild);
		if (queueTop->rightChild)nodeList.InsertTail(queueTop->rightChild);
		delete queueTop;
	}
}
//家谱树结点（家族成员）	定义

//************************************
// 全名:  FamilyTreeNode::NewChild
// 功能: 添加儿女
// 权限:    public 
// 返回:   void
// 参数: std::string childName 儿女名称
// 参数: SearchStructure searchStruct 保存姓名信息的AVL树
//************************************
void FamilyTreeNode::NewChild(std::string childName, SearchStructure searchStruct) {
	FamilyTreeNode *newEl = new FamilyTreeNode;
	FamilyMember bstIns;
	AVLTreeNode<FamilyMember> *bstPtrRet;
	child.InsertTail(newEl);
	child.tail->data->ptrInParent = child.tail;

	bstIns.memberName = childName;
	bstIns.familyTreePtr = child.tail->data;
	searchStruct->Insert(bstIns, searchStruct->root, bstPtrRet);
	child.tail->data->bstPtr = bstPtrRet;
	child.tail->data->parent = this;
}

//************************************
// 全名:  FamilyTreeNode::Rename
// 功能: 更名
// 权限:    public 
// 返回:   void
// 参数: std::string newName 更改后的名称
// 参数: SearchStructure searchStruct 保存姓名信息的AVL树
//************************************
void FamilyTreeNode::Rename(std::string newName, SearchStructure searchStruct) {
	FamilyTreeNode *cur = bstPtr->data.familyTreePtr;
	AVLTreeNode<FamilyMember> *bstPtrRet;

	bstPtr->lazy = true; //失效AVL结点

	FamilyMember newMember;
	newMember.memberName = newName;
	newMember.familyTreePtr = cur;
	searchStruct->Insert(newMember, searchStruct->root, bstPtrRet);
	bstPtr = bstPtrRet;
}
//************************************
// 全名:  FamilyTreeNode::Dissolve
// 功能: 解散以之为根的所有家庭和子家庭
// 权限:    public 
// 返回:   void
// 参数: SearchStructure searchStruct 保存姓名信息的AVL树
//************************************
void FamilyTreeNode::Dissolve(SearchStructure searchStruct) {
	LinkedList<FamilyTreeNode*> dfsStack;
	LinkedList<FamilyTreeNode*> deleteList;
	FamilyTreeNode *top;
	dfsStack.InsertTail(this);
	while (dfsStack.listSize) {
		top = dfsStack.tail->data;
		dfsStack.RemoveTail();
		//将所有儿女入栈
		for (LinkedListNode<FamilyTreeNode*>* i = top->child.head->succ; i != nullptr; i = i->succ) {
			dfsStack.InsertTail(i->data);
		}
		//清除当前儿女结点
		if (top != this) {
			top->parent->child.DeleteByPointer(top->ptrInParent);//从父亲的儿女结点链表中清除此结点
			top->bstPtr->lazy = true;//失效该儿女结点对应的bst结点
			deleteList.InsertTail(top); //释放结点
		}
	}
	for (LinkedListNode<FamilyTreeNode*>* i = deleteList.head->succ; i != nullptr; i = i->succ) {
		delete i->data;
	}
	//删除自身
	if (this->parent) { //非树根的条件下，从父亲的儿女结点链表中清除此结点
		this->parent->child.DeleteByPointer(this->ptrInParent);
		this->bstPtr->lazy = true;
	}
	delete this;
}

//家族树 定义
FamilyTree::FamilyTree() {
	famRoot = new FamilyTreeNode();
}
FamilyTree::~FamilyTree() {
	if (famRoot)famRoot->Dissolve(&dict);
	//if (famRoot)delete famRoot;
}
//************************************
// 全名:  FamilyTree::Find
// 功能: 查找家谱树中对应姓名的结点
// 权限:    public 
// 返回:   FamilyTreeNode*
// 参数: std::string memberName 成员姓名
//************************************
FamilyTreeNode* FamilyTree::Find(std::string memberName) {
	FamilyMember searchMember;
	searchMember.memberName = memberName;
	AVLTreeNode<FamilyMember> *bstRet = dict.Find(searchMember, dict.root);
	if (bstRet == nullptr)return nullptr;
	if (bstRet->lazy == true) return nullptr;
	return bstRet->data.familyTreePtr;
}

//************************************
// 全名:  FamilyTree::Main
// 功能: 主过程
// 权限:    public 
// 返回:   void
//************************************
void FamilyTree::Main() {
	using namespace std;
	cout << endl;
	cout << "**\t\t\t家谱管理系统\t\t\t**" << endl;
	cout << "===========================================================" << endl;
	cout << "**\t\t请选择要执行的操作：\t\t\t**" << endl;
	cout << "**\t\t  A --- 完善家谱\t\t\t**" << endl;
	cout << "**\t\t  B --- 添加家庭成员\t\t\t**" << endl;
	cout << "**\t\t  C --- 解散局部家庭\t\t\t**" << endl;
	cout << "**\t\t  D --- 更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\t  E --- 退出程序\t\t\t**" << endl;
	cout << "===========================================================" << endl;
	cout << "首先建立一个家谱:" << endl;
	cout << "请输入祖先的姓名：";
	string readIn, opReadIn, parentReadIn;
	int newChildCnt;
	FamilyTreeNode* curParent;
	cin >> readIn;
	famRoot->NewChild(readIn, &dict);
	cout << "此家谱的祖先是：" << famRoot->child.tail->data->bstPtr->data.memberName << endl;
	bool delRoot = false;

	while (1) {
		cout << endl << "请选择要执行的操作：";
		cin >> opReadIn;
		if (opReadIn.size() != 1) {
			cout << "输入的操作码无效，请输入合法的操作码" << endl;
			continue;
		}
		switch (opReadIn[0]) {
		case 'A':
			cout << "请输入要建立家庭的人的姓名:";
			cin >> parentReadIn;
			curParent = Find(parentReadIn); //avl查找该姓名的人所在结点
			if (curParent == nullptr) {
				cout << "此人不存在，请重新输入" << endl;
				break;
			}
			cout << "请输入" << curParent->bstPtr->data.memberName << "的儿女人数：";
			cin >> newChildCnt;
			if (newChildCnt > 0) {
				cout << "请依次输入" << curParent->bstPtr->data.memberName << "的儿女姓名：";
				for (int i = 0; i < newChildCnt; i++) {
					cin >> readIn;
					if (Find(readIn)) {
						cout << "姓名为:" << readIn << "的人已经存在，此添加操作已经被忽略" << endl;
					}
					else {
						curParent->NewChild(readIn, &dict);
					}
					
				}
				if (curParent->child.head->succ != nullptr) {
					cout << curParent->bstPtr->data.memberName << "的第一代子孙是：";
					for (LinkedListNode<FamilyTreeNode*>* i = curParent->child.head->succ; i != nullptr; i = i->succ) {
						cout << i->data->bstPtr->data.memberName << " ";
					}
				}
				else {
					cout << curParent->bstPtr->data.memberName << "没有第一代子孙。";
				}
				
			}
			else {
				cout << "输入的数字无效" << endl;
			}
			
			cout << endl;
			break;
		case 'B':
			cout << "请输入要添加儿子（或女儿）的人的姓名:";
			cin >> parentReadIn;
			curParent = Find(parentReadIn); //bst查找该姓名的人所在结点
			if (curParent == nullptr) {
				cout << "此人不存在，请重新输入" << endl;
				break;
			}

			cout << "请输入为" << curParent->bstPtr->data.memberName << "新添加的儿女姓名：";
			cin >> readIn;
			if (Find(readIn)) {
				cout << "姓名为" << readIn << "的成员已经存在,此添加操作已经被忽略" << endl;
			}
			else {
				curParent->NewChild(readIn, &dict);
			}

			if (curParent->child.head->succ != nullptr) {
				cout << curParent->bstPtr->data.memberName << "的第一代子孙是：";
				for (LinkedListNode<FamilyTreeNode*>* i = curParent->child.head->succ; i != nullptr; i = i->succ) {
					cout << i->data->bstPtr->data.memberName << " ";
				}
			}
			else {
				cout << curParent->bstPtr->data.memberName << "没有第一代子孙。";
			}
			std::cout << endl;
			break;
		case 'C':
			cout << "请输入要解散家庭的人的姓名：";
			cin >> parentReadIn;
			cout << "要解散家庭的人是：" << parentReadIn << endl;
			curParent = Find(parentReadIn); //bst查找该姓名的人所在结点
			if (curParent == famRoot->child.tail->data) {
				//cout << "" << endl;
				delRoot = true;
			}
			if (curParent == nullptr) {
				cout << "此人不存在，请重新输入" << endl;
				break;
			}
			if (curParent->child.head->succ != nullptr) {
				cout << curParent->bstPtr->data.memberName << "的第一代子孙是：";
				for (LinkedListNode<FamilyTreeNode*>* i = curParent->child.head->succ; i != nullptr; i = i->succ) {
					cout << i->data->bstPtr->data.memberName << " ";
				}
			}
			else {
				cout << curParent->bstPtr->data.memberName << "没有第一代子孙。";
			}
			curParent->Dissolve(&dict); //解散家庭
			cout << "该家庭现已解散" << endl;
			if (delRoot) {
				delRoot = false;
				cout << endl;
				cout << "由于以原祖先为根的家谱被解散，现在家谱系统祖先为空，请您指定家谱的祖先信息。" << endl;
				cout << "请输入祖先的姓名：";
				cin >> readIn;
				famRoot = new FamilyTreeNode;
				famRoot->NewChild(readIn, &dict);
				cout << "此家谱的祖先是：" << famRoot->child.tail->data->bstPtr->data.memberName << endl;
			}
			break;
		case 'D':
			cout << "请输入要更改姓名的人的目前姓名：";
			cin >> parentReadIn;
			curParent = Find(parentReadIn); //bst查找该姓名的人所在结点
			if (curParent == nullptr) {
				cout << "此人不存在，请重新输入" << endl;
				break;
			}
			cout << "请输入更改后的姓名：";
			cin >> readIn;
			if (Find(readIn) == nullptr) {
				curParent->Rename(readIn, &dict);
				cout << parentReadIn << "已更名为" << readIn << endl;
			}
			else {
				cout << "与已有的家庭成员重名，此更名操作已经被放弃" << endl;
			}
			
			break;
		case'E':
			return;
			break;
		default:
			cout << "输入的操作码无效，请输入合法的操作码" << endl;
		}
	}
}
//主程序
int main() {
	FamilyTree GenealogyTree;
	GenealogyTree.Main();
	return 0;
}