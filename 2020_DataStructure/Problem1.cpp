#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <climits>
//链表节点
template<class Type> class LinkedListNode {
public:
	Type data; //链表数据值
	LinkedListNode<Type> *successor = nullptr; //链表后继，nullptr则为链表尾
};

//链表模板类
template<class Type> class LinkedList {
private:
	LinkedListNode<Type> *head = nullptr;
	int listSize = 0;
public:
	enum LinkedListException {
		LLE_SUCCESS,  //链表操作成功
		LLE_ALLOCATE_FAILURE, //链表动态新建节点失败
		LLE_INSERTION_EXCEEDING_RANGE, //链表插入位置超出范围
		LLE_NOT_FOUND, //链表查询未找到
		LLE_UNKNOWN //其他错误
	};
	// 构造函数：新建空链表
	LinkedList<Type>() {
		head = new LinkedListNode<Type>;
	}
	// 析构函数：删除所有节点
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
	// 全名:  LinkedList<Type>::Insert
	// 功能: 在指定位置插入链表节点，原位置后元素向后移动
	// 权限:    public 
	// 返回:   void
	// 参数: Type data 插入的数据
	// 参数: int insertPosition 插入的位置
	// 参数: int & errorInfo 插入成功状态
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
	// 全名:  LinkedList::FindFirst
	// 功能: 按照要求查找链表中第一个满足要求的元素(对于类成员函数)
	// 权限:    public 
	// 返回:   void
	// 参数: bool(PType:: * compareFunction) 函数指针，用于判断当前位置的数据是否符合给定要求
	// 参数: CType standardArgv 用于判断的标准值
	// 参数: Type & returnValue 接受返回信息的对象
	// 参数: PType * pInstancePtr 成员函数指针所属的对象
	// 参数: int & errorInfo 操作成功状态
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
	// 全名:  LinkedList::FindAll
	// 功能: 按照要求查找链表中所有满足要求的元素，结果返回一个链表(对于类成员函数)
	// 权限:    public 
	// 返回:   void
	// 参数: bool（PType:: * compareFunction）函数指针，用于判断当前位置的数据是否符合给定要求
	// 参数: CType standardArgv 用于判断的标准值
	// 参数: LinkedList<Type> & returnValue 接受返回信息的对象
	// 参数: PType * pInstancePtr 成员函数指针所属的对象
	// 参数: int & errorInfo 操作成功状态
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
	// 全名:  LinkedList::DeleteFirst
	// 功能: 删除第一个满足要求的链表节点元素（对于类成员函数）
	// 权限:    public 
	// 返回:   void
	// 参数: bool（PType:: * compareFunction） 函数指针，用于判断当前位置的数据是否符合给定要求
	// 参数: CType standardArgv  用于判断的标准值
	// 参数: PType * pInstancePtr  成员函数指针所属的对象
	// 参数: int & errorInfo 操作成功状态
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
	// 全名:  LinkedList::DeleteAll
	// 功能:删除所有满足要求的链表节点元素（对于类成员函数）
	// 权限:    public 
	// 返回:   void
	// 参数: bool（PType:: * compareFunction） 函数指针，用于判断当前位置的数据是否符合给定要求
	// 参数: CType standardArgv  用于判断的标准值
	// 参数: PType * pInstancePtr  成员函数指针所属的对象
	// 参数: int & errorInfo 操作成功状态
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
	// 全名:  LinkedList::ConditionalModify
	// 功能: 修改第一个或所有满足指定条件的链表节点的数据值（对于类成员函数）
	// 权限:    public 
	// 返回:   void
	// 参数: bool(PType:: * compareFunction) 函数指针，用于判断当前位置的数据是否符合给定要求
	// 参数: CType standardArgv 用于判断的标准值
	// 参数: Type newValue 要更新的信息
	// 参数: PType * pInstancePtr 成员函数指针所属的对象
	// 参数: bool onlyModifyFirst 是否只修改第一个查找到的元素
	// 参数: int & errorInfo 操作成功状态
	//************************************
	template<class CType, class PType> void ConditionalModify(bool(PType::*compareFunction)(Type, CType), CType standardArgv, Type newValue, PType* pInstancePtr, bool onlyModifyFirst = true, int& errorInfo = LLE_SUCCESS) {
		errorInfo = LLE_SUCCESS;
		bool isFound = false;
		LinkedListNode<Type> *i = head->successor;
		for (; i != nullptr; i = i->successor) {
			if ((pInstancePtr->*compareFunction)(i->data, standardArgv) == true) {
				isFound = true;
				i->data = newValue;
				if (onlyModifyFirst)return; //若指定修改第一个节点，则退出函数
			}
		}
		if (!isFound)errorInfo = LLE_NOT_FOUND;
	}

	//************************************
	// 全名:  LinkedList::Scan
	// 功能: 遍历链表节点，对于每一个元素，执行给定的某类的某个成员函数
	// 权限:    public 
	// 返回:   void
	// 参数: void(PType:: * scanFunction)函数指针，要对每一个链表结点数据域执行的操作
	// 参数: PType * pInstancePtr 成员函数指针所属的对象
	//************************************
	template<class PType> void Scan(void(PType::*scanFunction)(Type), PType* pInstancePtr) {
		LinkedListNode<Type> *i = head->successor;
		for (; i != nullptr; i = i->successor) {
			(pInstancePtr->*scanFunction)(i->data);
		}
	}

	//************************************
	// 全名:  LinkedList<Type>::Size
	// 功能: 获取链表节点数量
	// 权限:    public 
	// 返回:   int 链表节点数量
	//************************************
	int Size() {
		return listSize;
	}
};

class ExamMember {
public:
	std::string examIdentity; //考生考号
	std::string name; //考生姓名
	bool gender; //性别，女生为0，男生1
	int age; //年龄
	std::string examType; //考试类别
};

//考试系统类
class ExamSystem {
public:
	
	LinkedList<ExamMember> examList; //储存考试系统数据的链表
	enum ExamSystemException { //考试系统操作异常
		ESE_INSERTION_FAILURE, //操作异常：插入失败
		ESE_INSERTION_CONFILCT, //操作异常：插入元素冲突（如考号重复）
		ESE_INPUT_INVALID, //操作异常：非法输入
		ESE_DELETE_FAILURE, //操作异常：删除失败 
		ESE_NOT_FOUND, //操作异常：信息未找到
		ESE_MODIFY_FAILURE, //操作异常：修改失败
		ESE_INSERTION_POS_FAILURE,
		ESE_MODIFY_STUID_CONFLICT,
	};

	enum ExamSystemDescription { //文字描述ID，对应systemDescriptions
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
	const std::string systemDescriptions[35] = { //文字描述内容，与ExamSystemDescription的值对应
		"首先请建立考生信息系统!",
		"数据插入失败",
		"该考号已经存在，请重新输入！",
		"请输入合法信息!",
		"请输入考生人数: ",
		"请依次输入考生的考号、姓名、性别、年龄及报考类别!",
		"考号\t姓名\t性别\t年龄\t报考类别",
		"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）",
		"请选择您要进行的操作:",
		"请输入你要插入考生的位置:",
		"请输入要删除考生的考号",
		"删除失败",
		"未查询到该考生信息",
		"你删除的考生信息是:",
		"请输入要查找考生的考号:",
		"查询到的信息为:",
		"请输入要修改考生的考号",
		"修改成功",
		"修改失败",
		"要插入的考生考号与表中元素有重复,请重新输入:",
		"输入的操作码不存在,请重新输入:",
		"插入位置不合法，请重新输入",
		"修改后考号信息冲突，操作已经被忽略。若要重新修改，请在在操作码中选择4。"
	};

	void ES_ErrorHandle(int errorId); //异常处理
	void ES_Insert(ExamMember insMember, int insPos); //在指定位置插入新考生，旧数据后移
	bool ES_JudgeByExamId(ExamMember compareArgument, std::string examId); //判断链表中的某个元素考号是否与查询要求相同
	void ES_DeleteById(std::string examId);//根据考号删除考生
	void ES_FindById(std::string examId); //根据考号查询考生信息
	void ES_ModifyById(std::string examIdentity, ExamMember insMember); //根据考号修改考生信息
	void ES_ShowDetailedTable(); //打印完整表格
	void ES_ShowUserInterface(); //主操作

	void ES_InputMember(ExamMember& object);//输入一项考生信息（用于检验输入合法性）
	void ES_InputInteger(int& object);//输入一个整数（用于检验输入合法性）
	void ES_PrintMember(ExamMember object); //打印一个考生信息，用于遍历链表
};

//考试系统类定义
//************************************
// 全名:  ExamSystem::ES_ErrorHandle
// 功能:  处理异常情况
// 权限:    public 
// 返回:   void
// 参数: int errorId
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
// 全名:  ExamSystem::ES_ModifyById
// 功能: 根据考生考号更新考生信息
// 权限:    public 
// 返回:   void
// 参数: std::string examIdentity 考生考号
// 参数: ExamMember insMember	要更新的信息
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
// 全名:  ExamSystem::ES_Insert
// 功能: 插入考生信息
// 权限:    public 
// 返回:   void
// 参数: ExamMember insMember 要插入的考生信息
// 参数: int insPos 插入位置
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
// 全名:  ExamSystem::ES_FindById
// 功能: 根据考生考号查找输出考生信息
// 权限:    public 
// 返回:   void
// 参数: std::string examId 要查找的考生考号
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
// 全名:  ExamSystem::ES_DeleteById
// 功能: 根据考生考号删除考生信息
// 权限:    public 
// 返回:   void
// 参数: std::string examId 考生考号
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
// 全名:  ExamSystem::ES_InputInteger
// 功能: 输入一个自然数，并检查合法性
// 权限:    public 
// 返回:   void
// 参数: int & object 要接受输入信息的变量
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
// 全名:  ExamSystem::ES_InputMember
// 功能: 输入一条考生信息条目，并检查合法性
// 权限:    public 
// 返回:   void
// 参数: ExamMember & object 要接受输入信息的变量
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
		//处理考号
		object.examIdentity = splitInfo[0];
		//处理姓名
		object.name = splitInfo[1];
		//处理考试类型
		object.examType = splitInfo[4];
		//处理性别
		if (splitInfo[2] == "男") {
			object.gender = 1;
		}
		else if (splitInfo[2] == "女") {
			object.gender = 0;
		}
		else {
			ES_ErrorHandle(ESE_INPUT_INVALID);
			continue;
		}
		//处理年龄
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
// 全名:  ExamSystem::ES_PrintMember
// 功能: 输出考生信息
// 权限:    public 
// 返回:   void
// 参数: ExamMember object 考生对象
//************************************
void ExamSystem::ES_PrintMember(ExamMember object) {
	char* p = (char*)((object.gender) ? "男" : "女");
	std::cout << object.examIdentity << "\t" << object.name << "\t" << p << "\t" << object.age << "\t" << object.examType << std::endl;
}
//************************************
// 全名:  ExamSystem::ES_ShowDetailedTable
// 功能: 输出统计信息
// 权限:    public 
// 返回:   void
//************************************
void ExamSystem::ES_ShowDetailedTable() {
	std::cout << systemDescriptions[ESD_SHOW_TABLE_HEADER] << std::endl;
	examList.Scan(&ExamSystem::ES_PrintMember, this);
}
//************************************
// 全名:  ExamSystem::ES_JudgeByExamId
// 功能: 根据判断考号与对应的考生对象是否一致
// 权限:    public 
// 返回:   bool
// 参数: ExamMember compareArgument 考生对象
// 参数: std::string examId 用于判断的考号
//************************************
bool ExamSystem::ES_JudgeByExamId(ExamMember compareArgument, std::string examId) {
	return compareArgument.examIdentity == examId;
}

//************************************
// 全名:  ExamSystem::ES_ShowUserInterface
// 功能:  用户操作界面
// 权限:    public 
// 返回:   void
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
	//主循环
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
		case 0: //退出
			exitFlag = true;
			break;
		case 1: //插入
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
		case 2: //删除
			std::cout << systemDescriptions[ESD_DELETE_IDENTITY];
			std::getline(std::cin, stuId);
			ES_DeleteById(stuId);
			break;
		case 3: //查找
			std::cout << systemDescriptions[ESD_FIND_IDENTITY];
			std::getline(std::cin, stuId);
			ES_FindById(stuId);
			break;
		case 4://修改
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
		case 5://统计
			ES_ShowDetailedTable();
			break;
		default:
			std::cout << systemDescriptions[ESD_INVALID_OPERATION_CODE] << std::endl;
			break;
		}
		if (exitFlag)break;
	}
}
//主程序
int main()
{
	ExamSystem ExamSystemInstance;
	ExamSystemInstance.ES_ShowUserInterface();
	return 0;
}
