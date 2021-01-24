#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <climits>
//����ڵ�
template<class Type> class LinkedListNode {
public:
	Type data; //��������ֵ
	LinkedListNode<Type> *successor = nullptr; //�����̣�nullptr��Ϊ����β
};

//����ģ����
template<class Type> class LinkedList {
private:
	LinkedListNode<Type> *head = nullptr;
	int listSize = 0;
public:
	enum LinkedListException {
		LLE_SUCCESS,  //��������ɹ�
		LLE_ALLOCATE_FAILURE, //����̬�½��ڵ�ʧ��
		LLE_INSERTION_EXCEEDING_RANGE, //�������λ�ó�����Χ
		LLE_NOT_FOUND, //�����ѯδ�ҵ�
		LLE_UNKNOWN //��������
	};
	// ���캯�����½�������
	LinkedList<Type>() {
		head = new LinkedListNode<Type>;
	}
	// ����������ɾ�����нڵ�
	~LinkedList<Type>() {
		LinkedListNode<Type> *cur = head, *curNext;
		while (1) {
			curNext = cur->successor;
			delete cur;
			if (curNext == nullptr) {
				break;
			}
			cur = curNext;
		}
	}
	//
	//************************************
	// ȫ��:  LinkedList<Type>::Insert
	// ����: ��ָ��λ�ò�������ڵ㣬ԭλ�ú�Ԫ������ƶ�
	// Ȩ��:    public 
	// ����:   void
	// ����: Type data ���������
	// ����: int insertPosition �����λ��
	// ����: int & errorInfo ����ɹ�״̬
	//************************************
	void Insert(Type data, int insertPosition, int& errorInfo) {
		errorInfo = LLE_SUCCESS;
		LinkedListNode<Type> *i = head->successor, *i_pred = head;
		int curPos = 1;
		for (; i != nullptr; i = i->successor, curPos++, i_pred = i_pred->successor) {
			if (curPos == insertPosition) {
				LinkedListNode<Type> *newElement = new LinkedListNode<Type>;
				if (newElement) {
					newElement->data = data;
					newElement->successor = i;
					i_pred->successor = newElement;
					listSize++;
					return;
				}
				else {
					errorInfo = LLE_ALLOCATE_FAILURE;
					return;
				}
			}
		}
		if (listSize + 1 == insertPosition) {
			LinkedListNode<Type> *newElement = new LinkedListNode<Type>;
			if (!newElement) {
				errorInfo = LLE_ALLOCATE_FAILURE;
				return;
			}
			newElement->data = data;
			newElement->successor = nullptr;
			i_pred->successor = newElement;
			listSize++;
			return;
		}

		errorInfo = LLE_UNKNOWN;
		return;

	}
	//************************************
	// ȫ��:  LinkedList::FindFirst
	// ����: ����Ҫ����������е�һ������Ҫ���Ԫ��(�������Ա����)
	// Ȩ��:    public 
	// ����:   void
	// ����: bool(PType:: * compareFunction) ����ָ�룬�����жϵ�ǰλ�õ������Ƿ���ϸ���Ҫ��
	// ����: CType standardArgv �����жϵı�׼ֵ
	// ����: Type & returnValue ���ܷ�����Ϣ�Ķ���
	// ����: PType * pInstancePtr ��Ա����ָ�������Ķ���
	// ����: int & errorInfo �����ɹ�״̬
	//************************************
	template<class CType, class PType> void FindFirst(bool(PType::*compareFunction)(Type, CType), CType standardArgv, Type& returnValue, PType* pInstancePtr, int& errorInfo = LLE_SUCCESS) {
		errorInfo = LLE_SUCCESS;
		LinkedListNode<Type> *i = head->successor;
		for (; i != nullptr; i = i->successor) {
			if ((pInstancePtr->*compareFunction)(i->data, standardArgv) == true) {
				returnValue = i->data;
				return;
			}
		}
		errorInfo = LLE_NOT_FOUND;
		return;
	}
	//************************************
	// ȫ��:  LinkedList::FindAll
	// ����: ����Ҫ�������������������Ҫ���Ԫ�أ��������һ������(�������Ա����)
	// Ȩ��:    public 
	// ����:   void
	// ����: bool��PType:: * compareFunction������ָ�룬�����жϵ�ǰλ�õ������Ƿ���ϸ���Ҫ��
	// ����: CType standardArgv �����жϵı�׼ֵ
	// ����: LinkedList<Type> & returnValue ���ܷ�����Ϣ�Ķ���
	// ����: PType * pInstancePtr ��Ա����ָ�������Ķ���
	// ����: int & errorInfo �����ɹ�״̬
	//************************************
	template<class CType, class PType> void FindAll(bool(PType::*compareFunction)(Type, CType), CType standardArgv, LinkedList<Type>& returnValue, PType* pInstancePtr, int& errorInfo = LLE_SUCCESS) {
		errorInfo = LLE_SUCCESS;
		bool isFound = false;
		LinkedListNode<Type> *i = head->successor;
		for (; i != nullptr; i = i->successor) {
			if ((pInstancePtr->*compareFunction)(i->data, standardArgv) == true) {
				returnValue.Insert(i->data, returnValue.Size() + 1, errorInfo);
				if (errorInfo)return;
				isFound = true;
			}
		}
		if (!isFound) {
			errorInfo = LLE_NOT_FOUND;
		}
	}
	//************************************
	// ȫ��:  LinkedList::DeleteFirst
	// ����: ɾ����һ������Ҫ�������ڵ�Ԫ�أ��������Ա������
	// Ȩ��:    public 
	// ����:   void
	// ����: bool��PType:: * compareFunction�� ����ָ�룬�����жϵ�ǰλ�õ������Ƿ���ϸ���Ҫ��
	// ����: CType standardArgv  �����жϵı�׼ֵ
	// ����: PType * pInstancePtr  ��Ա����ָ�������Ķ���
	// ����: int & errorInfo �����ɹ�״̬
	//************************************
	template<class CType, class PType> void DeleteFirst(bool(PType::*compareFunction)(Type, CType), CType standardArgv, PType* pInstancePtr, int& errorInfo = LLE_SUCCESS) {
		errorInfo = LLE_SUCCESS;
		LinkedListNode<Type> *i = head->successor, *i_pred = head;
		for (; i != nullptr; i = i->successor, i_pred = i_pred->successor) {
			if ((pInstancePtr->*compareFunction)(i->data, standardArgv) == true) {
				i_pred->successor = i->successor;
				delete i;
				listSize--;
				return;
			}
		}
		errorInfo = LLE_NOT_FOUND;
		return;
	}

	//************************************
	// ȫ��:  LinkedList::DeleteAll
	// ����:ɾ����������Ҫ�������ڵ�Ԫ�أ��������Ա������
	// Ȩ��:    public 
	// ����:   void
	// ����: bool��PType:: * compareFunction�� ����ָ�룬�����жϵ�ǰλ�õ������Ƿ���ϸ���Ҫ��
	// ����: CType standardArgv  �����жϵı�׼ֵ
	// ����: PType * pInstancePtr  ��Ա����ָ�������Ķ���
	// ����: int & errorInfo �����ɹ�״̬
	//************************************
	template<class CType, class PType> void DeleteAll(bool(PType::*compareFunction)(Type, CType), CType standardArgv, PType* pInstancePtr, int& errorInfo = LLE_SUCCESS) {
		errorInfo = LLE_SUCCESS;
		bool isFound = false;
		LinkedListNode<Type> *i = head->successor, *i_pred = head;
		for (; i != nullptr; i = i->successor, i_pred = i_pred->successor) {
			if ((pInstancePtr->*compareFunction)(i->data, standardArgv) == true) {
				i_pred->successor = i->successor;
				delete i;
				listSize--;
				isFound = true;
			}
		}
		if (!isFound)errorInfo = LLE_NOT_FOUND;
		return;
	}


	//************************************
	// ȫ��:  LinkedList::ConditionalModify
	// ����: �޸ĵ�һ������������ָ������������ڵ������ֵ���������Ա������
	// Ȩ��:    public 
	// ����:   void
	// ����: bool(PType:: * compareFunction) ����ָ�룬�����жϵ�ǰλ�õ������Ƿ���ϸ���Ҫ��
	// ����: CType standardArgv �����жϵı�׼ֵ
	// ����: Type newValue Ҫ���µ���Ϣ
	// ����: PType * pInstancePtr ��Ա����ָ�������Ķ���
	// ����: bool onlyModifyFirst �Ƿ�ֻ�޸ĵ�һ�����ҵ���Ԫ��
	// ����: int & errorInfo �����ɹ�״̬
	//************************************
	template<class CType, class PType> void ConditionalModify(bool(PType::*compareFunction)(Type, CType), CType standardArgv, Type newValue, PType* pInstancePtr, bool onlyModifyFirst = true, int& errorInfo = LLE_SUCCESS) {
		errorInfo = LLE_SUCCESS;
		bool isFound = false;
		LinkedListNode<Type> *i = head->successor;
		for (; i != nullptr; i = i->successor) {
			if ((pInstancePtr->*compareFunction)(i->data, standardArgv) == true) {
				isFound = true;
				i->data = newValue;
				if (onlyModifyFirst)return; //��ָ���޸ĵ�һ���ڵ㣬���˳�����
			}
		}
		if (!isFound)errorInfo = LLE_NOT_FOUND;
	}

	//************************************
	// ȫ��:  LinkedList::Scan
	// ����: ��������ڵ㣬����ÿһ��Ԫ�أ�ִ�и�����ĳ���ĳ����Ա����
	// Ȩ��:    public 
	// ����:   void
	// ����: void(PType:: * scanFunction)����ָ�룬Ҫ��ÿһ��������������ִ�еĲ���
	// ����: PType * pInstancePtr ��Ա����ָ�������Ķ���
	//************************************
	template<class PType> void Scan(void(PType::*scanFunction)(Type), PType* pInstancePtr) {
		LinkedListNode<Type> *i = head->successor;
		for (; i != nullptr; i = i->successor) {
			(pInstancePtr->*scanFunction)(i->data);
		}
	}

	//************************************
	// ȫ��:  LinkedList<Type>::Size
	// ����: ��ȡ����ڵ�����
	// Ȩ��:    public 
	// ����:   int ����ڵ�����
	//************************************
	int Size() {
		return listSize;
	}
};

class ExamMember {
public:
	std::string examIdentity; //��������
	std::string name; //��������
	bool gender; //�Ա�Ů��Ϊ0������1
	int age; //����
	std::string examType; //�������
};

//����ϵͳ��
class ExamSystem {
public:
	
	LinkedList<ExamMember> examList; //���濼��ϵͳ���ݵ�����
	enum ExamSystemException { //����ϵͳ�����쳣
		ESE_INSERTION_FAILURE, //�����쳣������ʧ��
		ESE_INSERTION_CONFILCT, //�����쳣������Ԫ�س�ͻ���翼���ظ���
		ESE_INPUT_INVALID, //�����쳣���Ƿ�����
		ESE_DELETE_FAILURE, //�����쳣��ɾ��ʧ�� 
		ESE_NOT_FOUND, //�����쳣����Ϣδ�ҵ�
		ESE_MODIFY_FAILURE, //�����쳣���޸�ʧ��
		ESE_INSERTION_POS_FAILURE,
		ESE_MODIFY_STUID_CONFLICT,
	};

	enum ExamSystemDescription { //��������ID����ӦsystemDescriptions
		ESD_SYSTEM_INIT,
		ESD_INSERTION_FAILURE,
		ESD_INSERTION_CONFLICT,
		ESD_EXCEPTION_INPUT_INVALID,
		ESD_INPUT_MEMBER_COUNT,
		ESD_INPUT_GUIDANCE,
		ESD_SHOW_TABLE_HEADER,
		ESD_SHOW_CHOOSE_OPTIONS,
		ESD_SHOW_CHOOSE_OPTIONS_CUR,
		ESD_INSERT_POSITION,
		ESD_DELETE_IDENTITY,
		ESD_DELETE_FAILURE,
		ESD_NOT_FOUND,
		ESD_ITEM_DELETED_REVIEW,
		ESD_FIND_IDENTITY,
		ESD_FIND_RESULT,
		ESD_MODIFY_IDENTITY,
		ESD_MODIFY_SUCCESS,
		ESD_MODIFY_FAILURE,
		ESD_IDENTITY_CONFLICT_WARNING,
		ESD_INVALID_OPERATION_CODE,
		ESD_INSERT_INVALID_POSITION,
		ESD_MODIFY_STUID_CONFLICT

	};
	const std::string systemDescriptions[35] = { //�����������ݣ���ExamSystemDescription��ֵ��Ӧ
		"�����뽨��������Ϣϵͳ!",
		"���ݲ���ʧ��",
		"�ÿ����Ѿ����ڣ����������룡",
		"������Ϸ���Ϣ!",
		"�����뿼������: ",
		"���������뿼���Ŀ��š��������Ա����估�������!",
		"����\t����\t�Ա�\t����\t�������",
		"��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������",
		"��ѡ����Ҫ���еĲ���:",
		"��������Ҫ���뿼����λ��:",
		"������Ҫɾ�������Ŀ���",
		"ɾ��ʧ��",
		"δ��ѯ���ÿ�����Ϣ",
		"��ɾ���Ŀ�����Ϣ��:",
		"������Ҫ���ҿ����Ŀ���:",
		"��ѯ������ϢΪ:",
		"������Ҫ�޸Ŀ����Ŀ���",
		"�޸ĳɹ�",
		"�޸�ʧ��",
		"Ҫ����Ŀ������������Ԫ�����ظ�,����������:",
		"����Ĳ����벻����,����������:",
		"����λ�ò��Ϸ�������������",
		"�޸ĺ󿼺���Ϣ��ͻ�������Ѿ������ԡ���Ҫ�����޸ģ������ڲ�������ѡ��4��"
	};

	void ES_ErrorHandle(int errorId); //�쳣����
	void ES_Insert(ExamMember insMember, int insPos); //��ָ��λ�ò����¿����������ݺ���
	bool ES_JudgeByExamId(ExamMember compareArgument, std::string examId); //�ж������е�ĳ��Ԫ�ؿ����Ƿ����ѯҪ����ͬ
	void ES_DeleteById(std::string examId);//���ݿ���ɾ������
	void ES_FindById(std::string examId); //���ݿ��Ų�ѯ������Ϣ
	void ES_ModifyById(std::string examIdentity, ExamMember insMember); //���ݿ����޸Ŀ�����Ϣ
	void ES_ShowDetailedTable(); //��ӡ�������
	void ES_ShowUserInterface(); //������

	void ES_InputMember(ExamMember& object);//����һ�����Ϣ�����ڼ�������Ϸ��ԣ�
	void ES_InputInteger(int& object);//����һ�����������ڼ�������Ϸ��ԣ�
	void ES_PrintMember(ExamMember object); //��ӡһ��������Ϣ�����ڱ�������
};

//����ϵͳ�ඨ��
//************************************
// ȫ��:  ExamSystem::ES_ErrorHandle
// ����:  �����쳣���
// Ȩ��:    public 
// ����:   void
// ����: int errorId
//************************************
void ExamSystem::ES_ErrorHandle(int errorId) {
	switch (errorId) {
	case ESE_INPUT_INVALID:
		std::cout << systemDescriptions[ESD_EXCEPTION_INPUT_INVALID] << std::endl;
		break;
	case ESE_INSERTION_FAILURE:
		std::cout << systemDescriptions[ESD_INSERTION_FAILURE] << std::endl;
		break;
	case ESE_DELETE_FAILURE:
		std::cout << systemDescriptions[ESD_DELETE_FAILURE] << std::endl;
		break;
	case ESE_NOT_FOUND:
		std::cout << systemDescriptions[ESD_NOT_FOUND] << std::endl;
		break;
	case ESE_MODIFY_FAILURE:
		std::cout << systemDescriptions[ESD_MODIFY_FAILURE] << std::endl;
		break;
	case ESE_INSERTION_POS_FAILURE:
		std::cout << systemDescriptions[ESD_INSERT_INVALID_POSITION] << std::endl;
		break;
	case ESE_MODIFY_STUID_CONFLICT:
		std::cout << systemDescriptions[ESD_MODIFY_STUID_CONFLICT] << std::endl;
		break;
	}
}
//************************************
// ȫ��:  ExamSystem::ES_ModifyById
// ����: ���ݿ������Ÿ��¿�����Ϣ
// Ȩ��:    public 
// ����:   void
// ����: std::string examIdentity ��������
// ����: ExamMember insMember	Ҫ���µ���Ϣ
//************************************
void ExamSystem::ES_ModifyById(std::string examIdentity, ExamMember insMember) {
	int stat;
	ExamMember examMemberTemp2;
	int statTmp;
	examList.FindFirst(&ExamSystem::ES_JudgeByExamId, insMember.examIdentity, examMemberTemp2, this, statTmp);
	if (statTmp != LinkedList<ExamSystem>::LLE_NOT_FOUND) {
		ES_ErrorHandle(ESE_MODIFY_STUID_CONFLICT);
		return;
	}

	examList.ConditionalModify(&ExamSystem::ES_JudgeByExamId, examIdentity, insMember, this, false, stat);
	if (stat) {
		ES_ErrorHandle(ESE_MODIFY_FAILURE);
	}
	else {
		std::cout << systemDescriptions[ESD_MODIFY_SUCCESS] << std::endl;
	}
}
//************************************
// ȫ��:  ExamSystem::ES_Insert
// ����: ���뿼����Ϣ
// Ȩ��:    public 
// ����:   void
// ����: ExamMember insMember Ҫ����Ŀ�����Ϣ
// ����: int insPos ����λ��
//************************************
void ExamSystem::ES_Insert(ExamMember insMember, int insPos) {
	int stat = 0;
	examList.Insert(insMember, insPos, stat);
	if (stat) {
		if (stat == LinkedList<ExamSystem>::LLE_UNKNOWN) {
			ES_ErrorHandle(ESE_INSERTION_POS_FAILURE);
		}
		ES_ErrorHandle(ESE_INSERTION_FAILURE);
	}
}
//************************************
// ȫ��:  ExamSystem::ES_FindById
// ����: ���ݿ������Ų������������Ϣ
// Ȩ��:    public 
// ����:   void
// ����: std::string examId Ҫ���ҵĿ�������
//************************************
void ExamSystem::ES_FindById(std::string examId) {
	int stat = 0;
	LinkedList<ExamMember> foundList;
	examList.FindAll(&ExamSystem::ES_JudgeByExamId, examId, foundList, this, stat);
	if (stat) {
		ES_ErrorHandle(ESE_NOT_FOUND);
		return;
	}
	else {
		std::cout << systemDescriptions[ESD_FIND_RESULT] << std::endl;
		foundList.Scan(&ExamSystem::ES_PrintMember, this);
	}
}
//************************************
// ȫ��:  ExamSystem::ES_DeleteById
// ����: ���ݿ�������ɾ��������Ϣ
// Ȩ��:    public 
// ����:   void
// ����: std::string examId ��������
//************************************
void ExamSystem::ES_DeleteById(std::string examId) {
	int stat = 0;
	LinkedList<ExamMember> foundList;
	examList.FindAll(&ExamSystem::ES_JudgeByExamId, examId, foundList, this, stat);
	if (stat) {
		ES_ErrorHandle(ESE_NOT_FOUND);
		return;
	}
	examList.DeleteFirst(&ExamSystem::ES_JudgeByExamId, examId, this, stat);
	if (stat) {
		ES_ErrorHandle(ESE_DELETE_FAILURE);
	}
	else {
		std::cout << systemDescriptions[ESD_ITEM_DELETED_REVIEW] << std::endl;
		foundList.Scan(&ExamSystem::ES_PrintMember, this);
	}
}
//************************************
// ȫ��:  ExamSystem::ES_InputInteger
// ����: ����һ����Ȼ���������Ϸ���
// Ȩ��:    public 
// ����:   void
// ����: int & object Ҫ����������Ϣ�ı���
//************************************
void ExamSystem::ES_InputInteger(int& object) {
	std::string readIn;
	bool illegalFlag = false;
	while (1) {
		illegalFlag = false;
		std::getline(std::cin, readIn);
		int sz = readIn.size();
		for (int i = 0; i < sz; i++) {
			if (!(readIn[i] <= '9'&&readIn[i] >= '0')) {
				illegalFlag = true;
				break;
			}
		}
		if (sz == 0) {
			illegalFlag = true;
		}
		if (illegalFlag) {
			ES_ErrorHandle(ESE_INPUT_INVALID);
		}
		else {
			object = std::stoi(readIn);
			return;
		}
	}
}
//************************************
// ȫ��:  ExamSystem::ES_InputMember
// ����: ����һ��������Ϣ��Ŀ�������Ϸ���
// Ȩ��:    public 
// ����:   void
// ����: ExamMember & object Ҫ����������Ϣ�ı���
//************************************
void ExamSystem::ES_InputMember(ExamMember& object) {
	std::string readInfo;
	std::string splitInfo[7];
	int cur = 0;
	int stringSize = 0;
	bool lastIsSpace = true;
	while (1) {
		for (int i = 0; i < 7; i++) {
			splitInfo[i] = "";
		}

		cur = 0;
		lastIsSpace = true;
		std::getline(std::cin, readInfo);
		stringSize = readInfo.size();
		for (int i = 0; i < stringSize; i++) {
			if (readInfo[i] == ' ') {
				if (lastIsSpace == false) {
					cur++;
					if (cur >= 6) {
						ES_ErrorHandle(ESE_INPUT_INVALID);
						continue;
					}
					lastIsSpace = true;
				}
			}
			else {
				lastIsSpace = false;
				if (cur >= 6) {
					ES_ErrorHandle(ESE_INPUT_INVALID);
					continue;
				}
				splitInfo[cur] += readInfo[i];
			}
		}
		if (((cur == 4) || (cur == 5 && splitInfo[5].size() == 0)) == false) {
			ES_ErrorHandle(ESE_INPUT_INVALID);
			continue;
		}
		//������
		object.examIdentity = splitInfo[0];
		//��������
		object.name = splitInfo[1];
		//����������
		object.examType = splitInfo[4];
		//�����Ա�
		if (splitInfo[2] == "��") {
			object.gender = 1;
		}
		else if (splitInfo[2] == "Ů") {
			object.gender = 0;
		}
		else {
			ES_ErrorHandle(ESE_INPUT_INVALID);
			continue;
		}
		//��������
		int ageIllegalFlag = false;
		for (int i = 0; i < splitInfo[3].size(); i++) {
			if (!(splitInfo[3][i] >= '0'&&splitInfo[3][i] <= '9')) {
				ageIllegalFlag = true;
				break;
			}
		}
		if (ageIllegalFlag) {
			ES_ErrorHandle(ESE_INPUT_INVALID);
			continue;
		}
		else {
			object.age = std::stoi(splitInfo[3]);
			break;
		}
	}
	return;
}

//************************************
// ȫ��:  ExamSystem::ES_PrintMember
// ����: ���������Ϣ
// Ȩ��:    public 
// ����:   void
// ����: ExamMember object ��������
//************************************
void ExamSystem::ES_PrintMember(ExamMember object) {
	char* p = (char*)((object.gender) ? "��" : "Ů");
	std::cout << object.examIdentity << "\t" << object.name << "\t" << p << "\t" << object.age << "\t" << object.examType << std::endl;
}
//************************************
// ȫ��:  ExamSystem::ES_ShowDetailedTable
// ����: ���ͳ����Ϣ
// Ȩ��:    public 
// ����:   void
//************************************
void ExamSystem::ES_ShowDetailedTable() {
	std::cout << systemDescriptions[ESD_SHOW_TABLE_HEADER] << std::endl;
	examList.Scan(&ExamSystem::ES_PrintMember, this);
}
//************************************
// ȫ��:  ExamSystem::ES_JudgeByExamId
// ����: �����жϿ������Ӧ�Ŀ��������Ƿ�һ��
// Ȩ��:    public 
// ����:   bool
// ����: ExamMember compareArgument ��������
// ����: std::string examId �����жϵĿ���
//************************************
bool ExamSystem::ES_JudgeByExamId(ExamMember compareArgument, std::string examId) {
	return compareArgument.examIdentity == examId;
}

//************************************
// ȫ��:  ExamSystem::ES_ShowUserInterface
// ����:  �û���������
// Ȩ��:    public 
// ����:   void
//************************************
void ExamSystem::ES_ShowUserInterface() {
	int examMemberCounter, statTmp;
	ExamMember examMemberTemp, examMemberTemp2;
	std::string stuId, conflictOption;
	std::cout << systemDescriptions[ESD_SYSTEM_INIT] << std::endl;
	std::cout << systemDescriptions[ESD_INPUT_MEMBER_COUNT];
	ES_InputInteger(examMemberCounter);
	std::cout << systemDescriptions[ESD_INPUT_GUIDANCE] << std::endl << std::endl;
	for (int i = 0; i < examMemberCounter; i++) {
		while (1) {
			ES_InputMember(examMemberTemp);
			examList.FindFirst(&ExamSystem::ES_JudgeByExamId, examMemberTemp.examIdentity, examMemberTemp2, this, statTmp);
			if (statTmp == LinkedList<ExamSystem>::LLE_NOT_FOUND) {
				ES_Insert(examMemberTemp, examList.Size() + 1);
				break;
			}
			else {
				std::cout << systemDescriptions[ESD_IDENTITY_CONFLICT_WARNING] << std::endl;
				continue;
			}
		}
	}
	ES_ShowDetailedTable();
	std::cout << systemDescriptions[ESD_SHOW_CHOOSE_OPTIONS] << std::endl;
	//��ѭ��
	int operationId;
	bool exitFlag = false;
	bool firstLoop = true;

	while (1) {
		std::cout << std::endl;
		if (firstLoop) firstLoop = false;
		else {
			if (operationId >= 0 && operationId <= 5) {
				ES_ShowDetailedTable();
			}
		}
		std::cout << systemDescriptions[ESD_SHOW_CHOOSE_OPTIONS_CUR];
		ES_InputInteger(operationId);
		switch (operationId) {
		case 0: //�˳�
			exitFlag = true;
			break;
		case 1: //����
			int insertPos;
			std::cout << systemDescriptions[ESD_INSERT_POSITION];
			ES_InputInteger(insertPos);
			if (insertPos <= 0 || insertPos > examList.Size() + 1) {
				ES_ErrorHandle(ESE_INSERTION_POS_FAILURE);
				break;
			}
			while (1) {
				std::cout << systemDescriptions[ESD_INPUT_GUIDANCE] << std::endl;
				ES_InputMember(examMemberTemp);
				examList.FindFirst(&ExamSystem::ES_JudgeByExamId, examMemberTemp.examIdentity, examMemberTemp2, this, statTmp);
				if (statTmp == LinkedList<ExamSystem>::LLE_NOT_FOUND) {
					ES_Insert(examMemberTemp, insertPos);
					break;
				}
				else {
					std::cout << systemDescriptions[ESD_IDENTITY_CONFLICT_WARNING] << std::endl;
					std::getline(std::cin, conflictOption);
					if (conflictOption == "Y" || conflictOption == "y") {
						ES_Insert(examMemberTemp, insertPos);
						break;
					}
					continue;
				}
			}
			break;
		case 2: //ɾ��
			std::cout << systemDescriptions[ESD_DELETE_IDENTITY];
			std::getline(std::cin, stuId);
			ES_DeleteById(stuId);
			break;
		case 3: //����
			std::cout << systemDescriptions[ESD_FIND_IDENTITY];
			std::getline(std::cin, stuId);
			ES_FindById(stuId);
			break;
		case 4://�޸�
			std::cout << systemDescriptions[ESD_MODIFY_IDENTITY];
			std::getline(std::cin, stuId);
			examList.FindFirst(&ExamSystem::ES_JudgeByExamId, stuId , examMemberTemp2, this, statTmp);
			if (statTmp == LinkedList<ExamSystem>::LLE_NOT_FOUND) {
				ES_ErrorHandle(ESE_NOT_FOUND);
				break;
			}
			std::cout << systemDescriptions[ESD_INPUT_GUIDANCE] << std::endl;
			ES_InputMember(examMemberTemp);
			ES_ModifyById(stuId, examMemberTemp);
			break;
		case 5://ͳ��
			ES_ShowDetailedTable();
			break;
		default:
			std::cout << systemDescriptions[ESD_INVALID_OPERATION_CODE] << std::endl;
			break;
		}
		if (exitFlag)break;
	}
}
//������
int main()
{
	ExamSystem ExamSystemInstance;
	ExamSystemInstance.ES_ShowUserInterface();
	return 0;
}
