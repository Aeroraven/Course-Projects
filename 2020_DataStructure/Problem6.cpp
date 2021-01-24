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
	LinkedList<Type>();//���������
	~LinkedList<Type>();//��������
	void DeleteByPointer(LinkedListNode<Type>* NodePtr); //���ս��ָ��ɾ�����
	void InsertTail(const Type& data); //������β������ڵ�
	void RemoveTail();
	void RemoveFront();
};

template<class Type> class AVLTreeNode { //AVL��㣨���ڳ�Ա��Ϣ�洢��
public:
	bool lazy = false; //����Ƿ�ʧЧ(ʧЧ��㽫������Ԫ�ز���ʱ������)
	Type data;
	int height = 0;
	AVLTreeNode<Type> *leftChild = nullptr, *rightChild = nullptr;
};
template<class Type> class AVLTree {//AVL����������Ϣ���Һ��޸ģ�
public:
	AVLTreeNode<Type>* root = nullptr; //AVL���ڵ�
	~AVLTree<Type>();
	AVLTreeNode<Type>* RotateL(AVLTreeNode<Type>* node); //����
	AVLTreeNode<Type>* RotateR(AVLTreeNode<Type>* node); //����
	AVLTreeNode<Type>* RotateLR(AVLTreeNode<Type>* node); //����-����
	AVLTreeNode<Type>* RotateRL(AVLTreeNode<Type>* node); //����-����
	int GetMaxChildHeight(AVLTreeNode<Type>* node); //��ȡ��������߶�
	int GetBalanceFactor(AVLTreeNode<Type>* node); //��ȡƽ������
	AVLTreeNode<Type>* Insert(const Type& data, AVLTreeNode<Type>* node, AVLTreeNode<Type>*& newNodePtr); //��������(�����ݵ���ڣ��򸲸�����)
	void DeleteLazy(const Type& data); //ʧЧ��㣨�����lazy��
	AVLTreeNode<Type>* Find(const Type& data, AVLTreeNode<Type>* node); //���ҽ�㣬���ؽ��ָ��
	bool isExistent(const Type& data);//����ֵ��Ӧ�ڵ��Ƿ���ڣ�������ʧЧ�ڵ㣩
};

class FamilyMember;

class FamilyTreeNode { //�������Ľ��
public:
	typedef AVLTree<FamilyMember>* SearchStructure;

	AVLTreeNode<FamilyMember> *bstPtr = nullptr;//ָ����Ϣ��ָ��
	LinkedList<FamilyTreeNode*> child; //��Ա�Ķ�Ů
	LinkedListNode<FamilyTreeNode*> *ptrInParent;//�˳�Աλ�ڸ���������е�λ��
	FamilyTreeNode *parent;//���ڵ�

	void NewChild(std::string childName, SearchStructure searchStruct); //�½���Ů
	void Rename(std::string newName, SearchStructure searchStruct);//������
	void Dissolve(SearchStructure searchStruct); //��ɢ����
};
class FamilyMember { //��ͥ��Ա��Ϣ����(����BST���)
public:
	std::string memberName; //��Ա����
	FamilyTreeNode *familyTreePtr; //ָ��������н���ָ��
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



class FamilyTree { //������
public:
	FamilyTreeNode *famRoot = nullptr; //���ڵ�
	AVLTree<FamilyMember> dict; //��Ա�����ṹ

	FamilyTree(); //�������������
	~FamilyTree(); //����������
	FamilyTreeNode* Find(std::string memberName); //���ҳ�Ա�����ؽ��ָ��
	void Main();
};

//���� ����
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
// ȫ��:  LinkedList::DeleteByPointer
// ����: ����������ָ��ɾ���ڵ�
// Ȩ��:    public 
// ����:   void
// ����: LinkedListNode<Type> * NodePtr
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
// ȫ��:  LinkedList::InsertTail
// ����: ������β��������
// Ȩ��:    public 
// ����:   void
// ����: const Type & data
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
// ȫ��:  LinkedList::RemoveTail
// ����: ������ǿգ�ɾ������β�����
// Ȩ��:    public 
// ����:   void
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
// ȫ��:  LinkedList::RemoveFront
// ����: ������ǿգ�ɾ������ͷ�����
// Ȩ��:    public 
// ����:   void
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
//AVL�� ���� (��Ҫ������������
//************************************
// ȫ��:  AVLTree::GetMaxChildHeight
// ����: ��ȡһ����㣬�����������ĸ߶����ֵ
// Ȩ��:    public 
// ����:   int
// ����: AVLTreeNode<Type> * node
//************************************
template<class Type> int AVLTree<Type>::GetMaxChildHeight(AVLTreeNode<Type>* node) {
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return (lch > rch) ? lch : rch;
}
//************************************
// ȫ��:  AVLTree::RotateL
// ����: AVL����
// Ȩ��:    public 
// ����:   *
// ����: AVLTreeNode<Type> * node
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
// ȫ��:  AVLTree::RotateR
// ����: AVL����
// Ȩ��:    public 
// ����:   *
// ����: AVLTreeNode<Type> * node
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
// ȫ��:  AVLTree::RotateRL
// ����: AVL����-����
// Ȩ��:    public 
// ����:   *
// ����: AVLTreeNode<Type> * node
//************************************
template <class Type> AVLTreeNode<Type>* AVLTree<Type>::RotateRL(AVLTreeNode<Type>* node) {
	node->rightChild = RotateR(node->rightChild);
	return RotateL(node);
}
//************************************
// ȫ��:  AVLTree::RotateLR
// ����: AVL����-����
// Ȩ��:    public 
// ����:   *
// ����: AVLTreeNode<Type> * node
//************************************
template <class Type> AVLTreeNode<Type>* AVLTree<Type>::RotateLR(AVLTreeNode<Type>* node) {
	node->leftChild = RotateL(node->leftChild);
	return RotateR(node);
}
//************************************
// ȫ��:  AVLTree::Find
// ����: AVL����
// Ȩ��:    public 
// ����:   *
// ����: const Type & data Ҫ���ҵ�ֵ
// ����: AVLTreeNode<Type> * node ��ǰ���ҵĽ��
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
// ȫ��:  AVLTree::DeleteLazy
// ����: ��AVL�����lazy
// Ȩ��:    public 
// ����:   void
// ����: const Type & data
//************************************
template<class Type> void AVLTree<Type>::DeleteLazy(const Type& data) {
	AVLTreeNode<Type>* res = Find(data, root);
	if (res != nullptr) {
		res->lazy = true;
	}
}
//************************************
// ȫ��:  AVLTree::isExistent
// ����: �ж�һ��ֵ�Ƿ���AVL���д��ڣ������������lazy�Ľ�㣩
// Ȩ��:    public 
// ����:   bool
// ����: const Type & data
//************************************
template<class Type> bool AVLTree<Type>::isExistent(const Type& data) {
	AVLTreeNode<Type>* res = Find(data, root);
	if (res == nullptr) return false;
	if (res->lazy == true) return false;
	return true;
}
//************************************
// ȫ��:  AVLTree::GetBalanceFactor
// ����: ��ȡ���ƽ������
// Ȩ��:    public 
// ����:   int
// ����: AVLTreeNode<Type> * node
//************************************
template<class Type> int AVLTree<Type>::GetBalanceFactor(AVLTreeNode<Type>* node) {
	int lch = (node->leftChild) ? node->leftChild->height : 0;
	int rch = (node->rightChild) ? node->rightChild->height : 0;
	return rch - lch;
}
//************************************
// ȫ��:  AVLTree::Insert
// ����: AVL��������
// Ȩ��:    public 
// ����:   *
// ����: const Type & data Ҫ���������
// ����: AVLTreeNode<Type> * node ��ǰ���ҵĽ��
// ����: AVLTreeNode<Type> * & newNodePtr ����򸲸ǵ�AV�˽��ָ�뷵��
//************************************
template<class Type> AVLTreeNode<Type>* AVLTree<Type>::Insert(const Type& data, AVLTreeNode<Type>* node, AVLTreeNode<Type>*& newNodePtr) {
	//��Ϊ��������ʼ��
	if (root == nullptr) {
		root = new AVLTreeNode<Type>;
		root->data = data;
		newNodePtr = root;
		return root;
	}

	//����Ŀ��
	AVLTreeNode<Type>** insPlace = nullptr;
	if (data == node->data) { //���ǽ��
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

	//���¸߶�
	node->height = GetMaxChildHeight(node) + 1;

	//ƽ�⻯��
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
//��������㣨�����Ա��	����

//************************************
// ȫ��:  FamilyTreeNode::NewChild
// ����: ��Ӷ�Ů
// Ȩ��:    public 
// ����:   void
// ����: std::string childName ��Ů����
// ����: SearchStructure searchStruct ����������Ϣ��AVL��
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
// ȫ��:  FamilyTreeNode::Rename
// ����: ����
// Ȩ��:    public 
// ����:   void
// ����: std::string newName ���ĺ������
// ����: SearchStructure searchStruct ����������Ϣ��AVL��
//************************************
void FamilyTreeNode::Rename(std::string newName, SearchStructure searchStruct) {
	FamilyTreeNode *cur = bstPtr->data.familyTreePtr;
	AVLTreeNode<FamilyMember> *bstPtrRet;

	bstPtr->lazy = true; //ʧЧAVL���

	FamilyMember newMember;
	newMember.memberName = newName;
	newMember.familyTreePtr = cur;
	searchStruct->Insert(newMember, searchStruct->root, bstPtrRet);
	bstPtr = bstPtrRet;
}
//************************************
// ȫ��:  FamilyTreeNode::Dissolve
// ����: ��ɢ��֮Ϊ�������м�ͥ���Ӽ�ͥ
// Ȩ��:    public 
// ����:   void
// ����: SearchStructure searchStruct ����������Ϣ��AVL��
//************************************
void FamilyTreeNode::Dissolve(SearchStructure searchStruct) {
	LinkedList<FamilyTreeNode*> dfsStack;
	LinkedList<FamilyTreeNode*> deleteList;
	FamilyTreeNode *top;
	dfsStack.InsertTail(this);
	while (dfsStack.listSize) {
		top = dfsStack.tail->data;
		dfsStack.RemoveTail();
		//�����ж�Ů��ջ
		for (LinkedListNode<FamilyTreeNode*>* i = top->child.head->succ; i != nullptr; i = i->succ) {
			dfsStack.InsertTail(i->data);
		}
		//�����ǰ��Ů���
		if (top != this) {
			top->parent->child.DeleteByPointer(top->ptrInParent);//�Ӹ��׵Ķ�Ů�������������˽��
			top->bstPtr->lazy = true;//ʧЧ�ö�Ů����Ӧ��bst���
			deleteList.InsertTail(top); //�ͷŽ��
		}
	}
	for (LinkedListNode<FamilyTreeNode*>* i = deleteList.head->succ; i != nullptr; i = i->succ) {
		delete i->data;
	}
	//ɾ������
	if (this->parent) { //�������������£��Ӹ��׵Ķ�Ů�������������˽��
		this->parent->child.DeleteByPointer(this->ptrInParent);
		this->bstPtr->lazy = true;
	}
	delete this;
}

//������ ����
FamilyTree::FamilyTree() {
	famRoot = new FamilyTreeNode();
}
FamilyTree::~FamilyTree() {
	if (famRoot)famRoot->Dissolve(&dict);
	//if (famRoot)delete famRoot;
}
//************************************
// ȫ��:  FamilyTree::Find
// ����: ���Ҽ������ж�Ӧ�����Ľ��
// Ȩ��:    public 
// ����:   FamilyTreeNode*
// ����: std::string memberName ��Ա����
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
// ȫ��:  FamilyTree::Main
// ����: ������
// Ȩ��:    public 
// ����:   void
//************************************
void FamilyTree::Main() {
	using namespace std;
	cout << endl;
	cout << "**\t\t\t���׹���ϵͳ\t\t\t**" << endl;
	cout << "===========================================================" << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t\t**" << endl;
	cout << "**\t\t  A --- ���Ƽ���\t\t\t**" << endl;
	cout << "**\t\t  B --- ��Ӽ�ͥ��Ա\t\t\t**" << endl;
	cout << "**\t\t  C --- ��ɢ�ֲ���ͥ\t\t\t**" << endl;
	cout << "**\t\t  D --- ���ļ�ͥ��Ա����\t\t**" << endl;
	cout << "**\t\t  E --- �˳�����\t\t\t**" << endl;
	cout << "===========================================================" << endl;
	cout << "���Ƚ���һ������:" << endl;
	cout << "���������ȵ�������";
	string readIn, opReadIn, parentReadIn;
	int newChildCnt;
	FamilyTreeNode* curParent;
	cin >> readIn;
	famRoot->NewChild(readIn, &dict);
	cout << "�˼��׵������ǣ�" << famRoot->child.tail->data->bstPtr->data.memberName << endl;
	bool delRoot = false;

	while (1) {
		cout << endl << "��ѡ��Ҫִ�еĲ�����";
		cin >> opReadIn;
		if (opReadIn.size() != 1) {
			cout << "����Ĳ�������Ч��������Ϸ��Ĳ�����" << endl;
			continue;
		}
		switch (opReadIn[0]) {
		case 'A':
			cout << "������Ҫ������ͥ���˵�����:";
			cin >> parentReadIn;
			curParent = Find(parentReadIn); //avl���Ҹ������������ڽ��
			if (curParent == nullptr) {
				cout << "���˲����ڣ�����������" << endl;
				break;
			}
			cout << "������" << curParent->bstPtr->data.memberName << "�Ķ�Ů������";
			cin >> newChildCnt;
			if (newChildCnt > 0) {
				cout << "����������" << curParent->bstPtr->data.memberName << "�Ķ�Ů������";
				for (int i = 0; i < newChildCnt; i++) {
					cin >> readIn;
					if (Find(readIn)) {
						cout << "����Ϊ:" << readIn << "�����Ѿ����ڣ�����Ӳ����Ѿ�������" << endl;
					}
					else {
						curParent->NewChild(readIn, &dict);
					}
					
				}
				if (curParent->child.head->succ != nullptr) {
					cout << curParent->bstPtr->data.memberName << "�ĵ�һ�������ǣ�";
					for (LinkedListNode<FamilyTreeNode*>* i = curParent->child.head->succ; i != nullptr; i = i->succ) {
						cout << i->data->bstPtr->data.memberName << " ";
					}
				}
				else {
					cout << curParent->bstPtr->data.memberName << "û�е�һ�����";
				}
				
			}
			else {
				cout << "�����������Ч" << endl;
			}
			
			cout << endl;
			break;
		case 'B':
			cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�����:";
			cin >> parentReadIn;
			curParent = Find(parentReadIn); //bst���Ҹ������������ڽ��
			if (curParent == nullptr) {
				cout << "���˲����ڣ�����������" << endl;
				break;
			}

			cout << "������Ϊ" << curParent->bstPtr->data.memberName << "����ӵĶ�Ů������";
			cin >> readIn;
			if (Find(readIn)) {
				cout << "����Ϊ" << readIn << "�ĳ�Ա�Ѿ�����,����Ӳ����Ѿ�������" << endl;
			}
			else {
				curParent->NewChild(readIn, &dict);
			}

			if (curParent->child.head->succ != nullptr) {
				cout << curParent->bstPtr->data.memberName << "�ĵ�һ�������ǣ�";
				for (LinkedListNode<FamilyTreeNode*>* i = curParent->child.head->succ; i != nullptr; i = i->succ) {
					cout << i->data->bstPtr->data.memberName << " ";
				}
			}
			else {
				cout << curParent->bstPtr->data.memberName << "û�е�һ�����";
			}
			std::cout << endl;
			break;
		case 'C':
			cout << "������Ҫ��ɢ��ͥ���˵�������";
			cin >> parentReadIn;
			cout << "Ҫ��ɢ��ͥ�����ǣ�" << parentReadIn << endl;
			curParent = Find(parentReadIn); //bst���Ҹ������������ڽ��
			if (curParent == famRoot->child.tail->data) {
				//cout << "" << endl;
				delRoot = true;
			}
			if (curParent == nullptr) {
				cout << "���˲����ڣ�����������" << endl;
				break;
			}
			if (curParent->child.head->succ != nullptr) {
				cout << curParent->bstPtr->data.memberName << "�ĵ�һ�������ǣ�";
				for (LinkedListNode<FamilyTreeNode*>* i = curParent->child.head->succ; i != nullptr; i = i->succ) {
					cout << i->data->bstPtr->data.memberName << " ";
				}
			}
			else {
				cout << curParent->bstPtr->data.memberName << "û�е�һ�����";
			}
			curParent->Dissolve(&dict); //��ɢ��ͥ
			cout << "�ü�ͥ���ѽ�ɢ" << endl;
			if (delRoot) {
				delRoot = false;
				cout << endl;
				cout << "������ԭ����Ϊ���ļ��ױ���ɢ�����ڼ���ϵͳ����Ϊ�գ�����ָ�����׵�������Ϣ��" << endl;
				cout << "���������ȵ�������";
				cin >> readIn;
				famRoot = new FamilyTreeNode;
				famRoot->NewChild(readIn, &dict);
				cout << "�˼��׵������ǣ�" << famRoot->child.tail->data->bstPtr->data.memberName << endl;
			}
			break;
		case 'D':
			cout << "������Ҫ�����������˵�Ŀǰ������";
			cin >> parentReadIn;
			curParent = Find(parentReadIn); //bst���Ҹ������������ڽ��
			if (curParent == nullptr) {
				cout << "���˲����ڣ�����������" << endl;
				break;
			}
			cout << "��������ĺ��������";
			cin >> readIn;
			if (Find(readIn) == nullptr) {
				curParent->Rename(readIn, &dict);
				cout << parentReadIn << "�Ѹ���Ϊ" << readIn << endl;
			}
			else {
				cout << "�����еļ�ͥ��Ա�������˸��������Ѿ�������" << endl;
			}
			
			break;
		case'E':
			return;
			break;
		default:
			cout << "����Ĳ�������Ч��������Ϸ��Ĳ�����" << endl;
		}
	}
}
//������
int main() {
	FamilyTree GenealogyTree;
	GenealogyTree.Main();
	return 0;
}