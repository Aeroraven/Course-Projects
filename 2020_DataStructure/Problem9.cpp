#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <climits>
#include <stdexcept>
#include <fstream>
#include <cmath>
//其他函数
//************************************
// 全名:  isDigitStr
// 功能: 判断string是否是数字字符串
// 权限:    public
// 返回:   bool 是否是数字字符串
// 参数: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}

//类开始
template<typename Type>class LinkedListNode; //链表结点
template<typename Type>class LinkedList; //链表
template<typename Type>class LinkedListIterator; //链表迭代器

template<typename Type>class LinkedListNode {
public:
	Type data; //数据域
	LinkedListNode<Type> *succ = nullptr; //指针域
};
template<typename Type>class LinkedList {
private:
	LinkedListNode<Type> *head = nullptr, *tail = nullptr; //头尾指针
	int size = 0; //链表大小
public:
	friend class LinkedListIterator<Type>;
	LinkedList();
	~LinkedList();
	bool PushBack(const Type& data); //尾端插入
	bool PushFront(const Type& data); //前端插入
	bool PopFront(); //前端弹出
	int Size() { return size; } //链表大小
	LinkedListIterator<Type> GetIterator(); //获得链表迭代器
};
template<typename Type>class LinkedListIterator {
private:
	LinkedList<Type> *boundList; //关联的链表
	LinkedListNode<Type> *cur; //指向的结点
public:
	LinkedListIterator(LinkedList<Type>* linklist);
	bool GoNext(); //下一结点
	bool Reset(); //重置指针到头节点的下一结点
	bool GetValue(Type& result); //获得当前结点指针域
	bool isNull(); //当前结点判空
};
template<typename Type>class Stack {
private:
	LinkedList<Type> linkedStack; //链式栈内容
public:
	bool Push(const Type& p); //入栈
	bool Pop(); //出栈
	bool Top(Type& p); //获得栈顶
	bool Empty(); //判断栈空
};

template<typename Type>class Queue {
private:
	LinkedList<Type> linkedQueue; //链式队列内容
public:
	bool Push(const Type& p); //入队列（EnQue）
	bool Pop(); //出队列（DeQue）
	bool Front(Type& p); //队列前端
	bool Empty(); //队列判空
};

class HashTableElement {
public:
	std::string OriginalChar;
	int Index;
};
class HashTable { //Hash表
private:
	const int ModulusFactor = 947;
	LinkedList<HashTableElement> *HashList; //散列表
public:
	HashTable();
	~HashTable();
	bool Get(std::string CompareString, int& Index); //散列表按照字符串搜索
	bool Set(std::string InsertString, int Index); //散列表储存（字符串，整数）对
	int GetKey(std::string Dest); //散列表获取字符串对应的整数
};
class DispatchInfo { //分配信息
public:
	int Weekday; //开课的日期
	int TimeBegin, TimeEnd; //开课的节数
};
class CourseInfo { //课程信息
public:
	std::string Identity; //课程编号
	std::string Name; //课程名称
	int Length; //课时数
	int AvailLength; //剩余课时数
	int Semester; //开课学期
	LinkedList<std::string> PrerequisiteStrings; //先修课程字符串
	LinkedList<int> Prerequisites; //先修课程
	LinkedList<int> PrerequisitesRelationId;
	LinkedList<int> Successors; //后继课程
	LinkedList<int> SuccessorsRelationId;

	int AvailSemEnd, AvailSemStart;
};
class CourseDispatchSolution {
public:
	int Weekdays, CoursesPerDay, Courses, InitStat = 0; //基础信息
	int **courseTable; //课程表
	LinkedList<DispatchInfo> *details; //课程的各个小课信息
	CourseDispatchSolution() {}
	CourseDispatchSolution(const CourseDispatchSolution& x);
	const CourseDispatchSolution& operator =(const CourseDispatchSolution& x);

	void Init(int weekdays, int coursesPerDay, int courses); //初始化
	void AttachDispatchInfo(int courseId, int weekdays, int begin, int end); //添加课程的一个上课时段
	void Demolition(); //删除课程分配方案
	~CourseDispatchSolution() { Demolition(); }
};


class OverallCourseDispatchSol {
public:
	int semesterCounter = 0, initStat = 0;
	CourseDispatchSolution *semesterPlan = nullptr; //每个学期的课程表
	int* courseSem = nullptr; //每个课程的学期
	int courseCnt = 0;

	OverallCourseDispatchSol() {};
	OverallCourseDispatchSol(const OverallCourseDispatchSol& x);
	const OverallCourseDispatchSol& operator =(const OverallCourseDispatchSol& x);
	void init(int semCounter, int courseCounter, CourseDispatchSolution *dspSol, int *cSem); //初始化
	~OverallCourseDispatchSol();
};



class CourseArrangeSystem {
public:
	const int semesterCount = 8; //学期数
	const int semesterMaxTime = 50; //学期课时数
	const int semesterWeekdays = 5; //学期每周教学日数目
	const int semesterLessonsPerDay = 10; //每天课时数
	const int semesterLessonsInterval = 4; //大课数目
	const int semesterLessonsIntervalDuration[4] = { 2,3,2,3 }; //大课时长
	const int semesterLessonsIntervalBegin[4] = { 0,2,5,7 }; //大课起始课时
	#ifdef _WIN32
	const int outputColumnSpacings = 30; //输出文件列间距
	#else
    const int outputColumnSpacings = 40; //输出文件列间距
	#endif
private:
	LinkedList<std::string> courseArrangeInput; //储存输入
	CourseInfo *course = nullptr; //课程信息数组
	HashTable courseIdDict; //课程编号字典
	std::ifstream fin; //输入文件流
	std::ofstream fout; //输出文件流
	int courseCount = 0; //课程数
	int *topoInDegree = nullptr, *topoInDegree2 = nullptr, *topoRevInd = nullptr; //结点入度
	int *dispatchSemester = nullptr; //各个课程所在学期-数组
	int *visited = nullptr, *leastSemBak = nullptr;//用于DFS，标记访问状态
	int *semUsedTime = nullptr; //在DFS过程中，该学期已用课时数
	int fixedCourses = 0; //已经固定开课学期的课程数
	Stack<int> *leastSem = nullptr; //在DFS过程中，该课程的最早开课学期
	LinkedList<int> *semContent = nullptr;//每个学期的内容
	OverallCourseDispatchSol currentBestPlan; //当前较优解
	int *relationPreq = nullptr, *relationSucc = nullptr; //先修关系对
	int relationCount = 0, relationLdCur = 0;
public:
	int *semesterCourseLimit; //每个学期的设定的开设课程数量
	int *semesterUsedCourse; //在DFS过程中，该学期已经分配的课程数
public:
	std::string outputFileStr;
	~CourseArrangeSystem();
	int ReadCourses(); //读取文件，初步处理读取的信息
	void OutputSpacings(int x); //输出空格
	int TopologicalSearch(); //课程分配到学期
	int TopologicalSearch(int semester, int curCourse);//课程分配到学期（拓扑+DFS搜索）
	void DetailedDispatch();//在每个学期内分配课程，得到暂行解

	long long GetEvaluationValue(const OverallCourseDispatchSol& x); //评估函数
	int GetRandomAdjacentSolution(const OverallCourseDispatchSol& x, OverallCourseDispatchSol& result, int extFunc = 0); //获得邻域内的另一个随机解
	void SimulatedAnnealing(int GRASFunc = 0); //优化暂行解，模拟退火

	void Print(OverallCourseDispatchSol p);//将解输出
	void PrintBest() { Print(currentBestPlan); } //将最优解输出

	int CheckTopologicalAvailability();//判断输入信息的排课可行性（包括先修关系判环）
	void PreUnload() { if (!fout.fail())fout.close(); } //关闭输出文件流
	void SetEachSemesterLimit(); //指定每一个学期的开课数
};



//***********定义开始***********


//完整分配方案
//************************************
// 全名:  OverallCourseDispatchSol::OverallCourseDispatchSol
// 功能: 复制构造函数重载（深复制)
// 权限:    public
// 返回:
// 参数: const OverallCourseDispatchSol & x
//************************************
OverallCourseDispatchSol::OverallCourseDispatchSol(const OverallCourseDispatchSol& x) {
	if (initStat) delete[] semesterPlan, delete[] courseSem;
	semesterPlan = new CourseDispatchSolution[x.semesterCounter];
	courseSem = new int[x.courseCnt];
	courseCnt = x.courseCnt;
	semesterCounter = x.semesterCounter;
	for (int i = 0; i < x.semesterCounter; i++) {
		semesterPlan[i] = x.semesterPlan[i];
	}
	for (int i = 0; i < x.courseCnt; i++) {
		courseSem[i] = x.courseSem[i];
	}
	initStat = 1;
}
//************************************
// 全名:  OverallCourseDispatchSol::operator=
// 功能: 赋值运算重载（深复制)
// 权限:    public
// 返回:   const OverallCourseDispatchSol&
// 参数: const OverallCourseDispatchSol & x
//************************************
const OverallCourseDispatchSol& OverallCourseDispatchSol::operator =(const OverallCourseDispatchSol& x) {
	if (initStat) {
		delete[] semesterPlan;
		delete[] courseSem;
	}
	semesterPlan = new CourseDispatchSolution[x.semesterCounter];
	courseSem = new int[x.courseCnt];
	courseCnt = x.courseCnt;
	semesterCounter = x.semesterCounter;
	for (int i = 0; i < x.semesterCounter; i++) {
		semesterPlan[i] = x.semesterPlan[i];
	}
	for (int i = 0; i < x.courseCnt; i++) {
		courseSem[i] = x.courseSem[i];
	}
	initStat = 1;
	return *this;
}
//************************************
// 全名:  OverallCourseDispatchSol::init
// 功能: 初始化总体排课方案对象
// 权限:    public
// 返回:   void
// 参数: int semCounter 学期数
// 参数: int courseCounter 课程数
// 参数: CourseDispatchSolution * dspSol 每学期的排课方案
// 参数: int * cSem 每个课程所在学期
//************************************
void OverallCourseDispatchSol::init(int semCounter, int courseCounter, CourseDispatchSolution *dspSol, int *cSem) {
	initStat = 1;
	courseCnt = courseCounter;
	semesterCounter = semCounter;
	courseSem = new int[courseCounter];
	semesterPlan = new CourseDispatchSolution[semCounter];
	for (int i = 0; i < semesterCounter; i++) {
		semesterPlan[i] = dspSol[i];
	}
	for (int i = 0; i < courseCnt; i++) {
		courseSem[i] = cSem[i] - 1;
	}
}
//************************************
// 全名:  OverallCourseDispatchSol::~OverallCourseDispatchSol
// 功能: 析构函数
// 权限:    public
// 返回:
//************************************
OverallCourseDispatchSol::~OverallCourseDispatchSol() {
	if (!semesterPlan)delete[]semesterPlan;
	if (!courseSem)delete[]courseSem;
}
//分配方案
//************************************
// 全名:  CourseDispatchSolution::Demolition
// 功能: 删除对象中new的指针
// 权限:    public
// 返回:   void
//************************************
void CourseDispatchSolution::Demolition() {
	InitStat = 0;
	for (int i = 0; i < Weekdays; i++) delete[] courseTable[i];
	delete[]courseTable;
	delete[] details;
}
//************************************
// 全名:  CourseDispatchSolution::operator=
// 功能: 赋值运算重载（深复制）
// 权限:    public
// 返回:   const CourseDispatchSolution&
// 参数: const CourseDispatchSolution & x
//************************************
const CourseDispatchSolution& CourseDispatchSolution::operator =(const CourseDispatchSolution& x) {
	if (InitStat == 1)Demolition();
	DispatchInfo t;
	Init(x.Weekdays, x.CoursesPerDay, x.Courses);
	for (int i = 0; i < x.Courses; i++) {
		for (LinkedListIterator<DispatchInfo> j = x.details[i].GetIterator(); !j.isNull(); j.GoNext()) {
			j.GetValue(t);
			AttachDispatchInfo(i, t.Weekday, t.TimeBegin, t.TimeEnd);
		}
	}
	return *this;
}
//************************************
// 全名:  CourseDispatchSolution::CourseDispatchSolution
// 功能: 复制构造重载（深复制)
// 权限:    public
// 返回:
// 参数: const CourseDispatchSolution & x
//************************************
CourseDispatchSolution::CourseDispatchSolution(const CourseDispatchSolution& x) {
	if (InitStat == 1)Demolition();
	DispatchInfo t;
	Init(x.Weekdays, x.CoursesPerDay, x.Courses);
	for (int i = 0; i < x.Courses; i++) {
		for (LinkedListIterator<DispatchInfo> j = x.details[i].GetIterator(); !j.isNull(); j.GoNext()) {
			j.GetValue(t);
			AttachDispatchInfo(i, t.Weekday, t.TimeBegin, t.TimeEnd);
		}
	}
}
//************************************
// 全名:  CourseDispatchSolution::Init
// 功能: 单学期排课方案对象初始化
// 权限:    public
// 返回:   void
// 参数: int weekdays 教学日数目
// 参数: int coursesPerDay 每日课程
// 参数: int courses 课程数量
//************************************
void CourseDispatchSolution::Init(int weekdays, int coursesPerDay, int courses) {
	Weekdays = weekdays;
	CoursesPerDay = coursesPerDay;
	Courses = courses;
	InitStat = 1;
	courseTable = new int*[weekdays + 1];
	for (int i = 0; i < weekdays; i++) {
		courseTable[i] = new int[coursesPerDay + 1];
		for (int j = 0; j < coursesPerDay; j++) {
			courseTable[i][j] = -1;
		}
	}
	details = new LinkedList<DispatchInfo>[courses + 1];
}
//************************************
// 全名:  CourseDispatchSolution::AttachDispatchInfo
// 功能: 添加课程的一个小的上课时间
// 权限:    public
// 返回:   void
// 参数: int courseId 课程编号（在course数组中的下标）
// 参数: int weekdays 开课在星期几
// 参数: int begin 开课起始时间
// 参数: int end 开课终止时间
//************************************
void CourseDispatchSolution::AttachDispatchInfo(int courseId, int weekdays, int begin, int end) {
	DispatchInfo ins;
	ins.TimeBegin = begin; ins.TimeEnd = end;
	ins.Weekday = weekdays;
	details[courseId].PushBack(ins);
	for (int i = begin; i <= end; i++) {
		courseTable[weekdays][i] = courseId;
	}

}
//链表
template<class Type> LinkedList<Type>::LinkedList() {
	head = new LinkedListNode<Type>;
	tail = head;
}
template<class Type> LinkedList<Type>::~LinkedList() {
	LinkedListNode<Type> *tmp = head, *tmpNext;
	if (tmp == nullptr)return;
	while (1) {
		tmpNext = tmp->succ;
		delete tmp;
		if (tmpNext == nullptr)return;
		tmp = tmpNext;
	}
}
//************************************
// 全名:  LinkedList::PushBack
// 功能: 在链表尾部插入元素
// 权限:    public
// 返回:   bool
// 参数: const Type & data
//************************************
template<class Type> bool LinkedList<Type>::PushBack(const Type& data) {
	int c = 5;
	LinkedListNode<Type> *newElement = new LinkedListNode<Type>;
	if (newElement == nullptr) return false;
	tail->succ = newElement;
	newElement->data = data;
	newElement->succ = nullptr;
	tail = newElement;
	size++;
	return true;
}
//************************************
// 全名:  LinkedList::PushFront
// 功能: 在链表头部插入元素
// 权限:    public
// 返回:   bool
// 参数: const Type & data
//************************************
template<class Type> bool LinkedList<Type>::PushFront(const Type& data) {
	LinkedListNode<Type> *newElement = new LinkedListNode<Type>;
	if (newElement == nullptr) return false;
	newElement->data = data;
	newElement->succ = head->succ;
	head->succ = newElement;
	if (tail == head)tail = newElement;
	size++;
	return true;
}
//************************************
// 全名:  LinkedList::PopFront
// 功能: 弹出链表头部元素
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool LinkedList<Type>::PopFront() {
	if (head == tail)return false;
	LinkedListNode<Type> *tmp = head->succ->succ;
	delete head->succ;
	head->succ = tmp;
	if (head->succ == nullptr) tail = head;
	size--;
	return true;
}


//************************************
// 全名:  LinkedList::GetIterator
// 功能: 获得链表的迭代器
// 权限:    public
// 返回:
//************************************
template<class Type> LinkedListIterator<Type> LinkedList<Type>::GetIterator() {
	return LinkedListIterator<Type>(this);
}

//链表游标
template<class Type> LinkedListIterator<Type>::LinkedListIterator(LinkedList<Type>* linklist) {
	boundList = linklist;
	cur = (linklist->head) ? linklist->head->succ : nullptr;
}
//************************************
// 全名:  LinkedListIterator::GoNext
// 功能: 将游标指向下一结点
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool LinkedListIterator<Type>::GoNext() {
	if (cur == nullptr)return false;
	cur = cur->succ;
	return true;
}
//************************************
// 全名:  LinkedListIterator::Reset
// 功能: 重置链表迭代器
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool LinkedListIterator<Type>::Reset() {
	cur = (boundList->head) ? boundList->head->succ : nullptr;
	return true;
}
//************************************
// 全名:  LinkedListIterator::GetValue
// 功能: 获得当前节点的值
// 权限:    public
// 返回:   bool
// 参数: Type & result 返回值
//************************************
template<class Type> bool LinkedListIterator<Type>::GetValue(Type& result) {
	if (cur == nullptr)return false;
	result = cur->data;
	return true;
}
//************************************
// 全名:  LinkedListIterator::isNull
// 功能: 判断当前链表结点是否为空
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool LinkedListIterator<Type>::isNull() {
	return cur == nullptr;
}
//链式栈
//************************************
// 全名:  Stack::Empty
// 功能: 判断栈空
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool Stack<Type>::Empty() {
	return linkedStack.Size() == 0;
}
//************************************
// 全名:  Stack::Push
// 功能: 入栈
// 权限:    public
// 返回:   bool
// 参数: const Type & p 入栈元素
//************************************
template<class Type> bool Stack<Type>::Push(const Type& p) {
	return linkedStack.PushFront(p);
}
//************************************
// 全名:  Stack::Pop
// 功能: 出栈
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool Stack<Type>::Pop() {
	return linkedStack.PopFront();
}
//************************************
// 全名:  Stack::Top
// 功能: 获得栈顶元素
// 权限:    public
// 返回:   bool
// 参数: Type & p
//************************************
template<class Type>bool Stack<Type>::Top(Type& p) {
	LinkedListIterator<Type> iter = linkedStack.GetIterator();
	return iter.GetValue(p);
}

//链式队列

//************************************
// 全名:  Queue::Empty
// 功能: 判断队列空
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool Queue<Type>::Empty() {
	return linkedQueue.Size() == 0;
}
//************************************
// 全名:  Queue::Push
// 功能: 入队列
// 权限:    public
// 返回:   bool
// 参数: const Type & p
//************************************
template<class Type> bool Queue<Type>::Push(const Type& p) {
	return linkedQueue.PushBack(p);
}
//************************************
// 全名:  Queue::Pop
// 功能: 出队列
// 权限:    public
// 返回:   bool
//************************************
template<class Type> bool Queue<Type>::Pop() {
	return linkedQueue.PopFront();
}
//************************************
// 全名:  Queue::Front
// 功能: 获得队首元素
// 权限:    public
// 返回:   bool
// 参数: Type & p 返回值
//************************************
template<class Type>bool Queue<Type>::Front(Type& p) {
	LinkedListIterator<Type> iter = linkedQueue.GetIterator();
	return iter.GetValue(p);
}
//哈希表
HashTable::HashTable() {
	HashList = new LinkedList<HashTableElement>[ModulusFactor];
}
HashTable::~HashTable() {
	if (HashList != nullptr) delete[] HashList;
}
//************************************
// 全名:  HashTable::GetKey
// 功能: 获得字符串的Hash
// 权限:    public
// 返回:   int
// 参数: std::string Dest
//************************************
int HashTable::GetKey(std::string Dest) {
	int ret = 0, sz = Dest.size();
	for (int i = 0; i < sz; i++) {
		ret += Dest[i];
		ret %= ModulusFactor;
	}
	return ret;
}
//************************************
// 全名:  HashTable::Set
// 功能: 保存关系对
// 权限:    public
// 返回:   bool
// 参数: std::string InsertString
// 参数: int Index 与其对应的数值
//************************************
bool HashTable::Set(std::string InsertString, int Index) {
	int hashKey = GetKey(InsertString);
	HashList[hashKey].PushBack({ InsertString,Index });
	return true;
}
//************************************
// 全名:  HashTable::Get
// 功能: 根据字符串，获得关系对的数值部分
// 权限:    public
// 返回:   bool
// 参数: std::string CompareString 用于查找的字符串
// 参数: int & Index 返回的其对应的数值（不是Hash）
//************************************
bool HashTable::Get(std::string CompareString, int& Index) {
	int hashKey = GetKey(CompareString);
	LinkedListIterator<HashTableElement> lstIter = HashList[hashKey].GetIterator();
	HashTableElement tmp;
	for (; !lstIter.isNull(); lstIter.GoNext()) {
		lstIter.GetValue(tmp);
		if (tmp.OriginalChar == CompareString) {
			Index = tmp.Index;
			return true;
		}
	}
	return false;
}

//课程安排系统
CourseArrangeSystem::~CourseArrangeSystem() {

	if (course)delete[] course;
	if (topoInDegree)delete[] topoInDegree;
	if (topoInDegree2)delete[] topoInDegree2;
	if (topoRevInd)delete[] topoRevInd;
	if (dispatchSemester)delete[] dispatchSemester;
	if (visited)delete[] visited;
	if (leastSem)delete[] leastSem;
	if (leastSemBak)delete[] leastSemBak;
	if (semUsedTime)delete[] semUsedTime;
	if (semContent)delete[] semContent;
}
//************************************
// 全名:  CourseArrangeSystem::ReadCourses
// 功能: 读取课程信息
// 权限:    public
// 返回:   int
//************************************
int CourseArrangeSystem::ReadCourses() {
	fin.open("input.txt");
	fout.open("output.txt");
	int incompleteLineFlag = 0;
	int invalidLenFlag = 0;
	int invalidSemFlag = 0;
	std::string readInFile = "input.txt";
	if (fin.fail()) {
		std::string customFile;
		std::cout << " 默认输入文件无法打开，若想使用自定义的输入文件，请在下方输入文件地址（放弃操作输入-1）：" << std::endl;
		std::cout << " 文件地址：";
		while (1) {
			std::getline(std::cin, customFile);
			readInFile = customFile;
			if (customFile == "-1") {
				std::cout << std::endl << "【信息】操作已经被手动放弃。\n\n排课已终止，若想继续排课，请重启本软件。" << std::endl;

				return 2;
			}
			fin.open(customFile.c_str());
			if (!fin.fail())break;
			std::cout << std::endl;
			std::cout << " 给定输入文件无法打开，若想使用其他输入文件，请在下方输入文件地址（放弃操作输入-1）：" << std::endl;
			std::cout << " 文件地址：";
		}

	}
	if (fout.fail()) {
		//std::cout << "【错误】文件错误：输出文件output.txt无法访问。\n\n排课已终止，若想继续排课，请重启本软件。" << std::endl;
		//return 2;
		std::string customFile;
		std::cout << std::endl << " 默认输出文件无法打开，若想使用自定义的输出文件，请在下方输入文件地址（放弃操作输入-1）：" << std::endl;
		std::cout << " 文件地址：";
		while (1) {
			std::getline(std::cin, customFile);
			if (customFile == "-1") {
				std::cout << std::endl << "【信息】操作已经被手动放弃。\n\n排课已终止，若想继续排课，请重启本软件。" << std::endl;
				return 2;
			}
			else if (customFile == readInFile) {
				std::cout << std::endl;
				std::cout << " 给定文件为输入文件，不建议用于排课结果输出，若想使用其他输出文件，请在下方输入文件地址（放弃操作输入-1）：" << std::endl;
				std::cout << " 文件地址：";
				continue;
			}
			fout.open(customFile.c_str());
			if (!fout.fail())break;
			std::cout << std::endl;
			std::cout << " 给定输出文件无法打开，若想使用其他输出文件，请在下方输入文件地址（放弃操作输入-1）：" << std::endl;
			std::cout << " 文件地址：";
		}
		outputFileStr = customFile;
	}
	else {
		outputFileStr = "output.txt";
	}
	std::string strBuffer;
	while (!fin.eof()) {
		std::getline(fin, strBuffer);
		courseArrangeInput.PushBack(strBuffer);
		courseCount++;
	}
	course = new CourseInfo[courseCount];
	topoInDegree = new int[courseCount];
	topoInDegree2 = new int[courseCount];
	topoRevInd = new int[courseCount];
	dispatchSemester = new int[courseCount];
	visited = new int[courseCount];
	leastSemBak = new int[courseCount];
	leastSem = new Stack<int>[courseCount];
	semUsedTime = new int[semesterCount + 1];
	semContent = new LinkedList<int>[semesterCount + 1];
	semesterUsedCourse = new int[semesterCount];

	if (!(course&&topoInDegree&&topoInDegree2&&topoRevInd&&dispatchSemester&&visited&&leastSemBak&&leastSem&&semUsedTime&&semContent)) {
		std::cout << "【错误】文件错误：内存不足。\n\n排课已终止，若想继续排课，请保证可用内存后继续." << std::endl;
		return 5;
	}


	for (int i = 0; i < courseCount; i++) {
		topoInDegree[i] = 0;
		topoInDegree2[i] = 0;
		topoRevInd[i] = 0;
		dispatchSemester[i] = 0;
		visited[i] = 0;
		leastSemBak[i] = 0;
		leastSem[i].Push(0);
		course[i].AvailSemEnd = 0;
		course[i].AvailSemStart = 0;
	}
	for (int i = 0; i <= semesterCount; i++) {
		semUsedTime[i] = 0;
		semesterUsedCourse[i] = 0;
	}
	LinkedListIterator<std::string> iter = courseArrangeInput.GetIterator();
	for (int i = 0; !iter.isNull(); iter.GoNext(), i++) {
		std::stringstream splitter;
		iter.GetValue(strBuffer);
		if(strBuffer==""||strBuffer=="\r")continue;

		splitter << strBuffer;

		if (!(splitter >> course[i].Identity)) {
			incompleteLineFlag = i + 1;
			break;
		}
		if (!(splitter >> course[i].Name)) {
			incompleteLineFlag = i + 1;
			break;
		}
		std::string numStrTemp;
		if (!(splitter >> numStrTemp)) {//course[i].Length
			incompleteLineFlag = i + 1;
			break;
		}
		if (!isDigitStr(numStrTemp.c_str())) {
			invalidLenFlag = i + 1;
			break;
		}
		else {
			course[i].Length = std::stoi(numStrTemp);
			if (course[i].Length == 0) {
				invalidLenFlag = i + 1;
				break;
			}
		}


		if (!(splitter >> numStrTemp)) {
			incompleteLineFlag = i + 1;
			break;
		}
		if (!isDigitStr(numStrTemp.c_str())) {
			invalidSemFlag = i + 1;
			break;
		}
		else {
			course[i].Semester = std::stoi(numStrTemp);
			if (course[i].Semester<0 || course[i].Semester>semesterCount) {
				invalidSemFlag = i + 1;
				break;
			}
		}


		course[i].AvailLength = course[i].Length;
		while (splitter >> strBuffer) {
			course[i].PrerequisiteStrings.PushBack(strBuffer);
			relationCount++;
		}
		int tmp;
		if (!courseIdDict.Get(course[i].Identity, tmp)) {
			courseIdDict.Set(course[i].Identity, i);
		}
		else {
			std::cout << "【错误】文件错误：在输入的课程信息文件中，第" << i + 1 << "行的课程，课号存在冲突\n\n排课已终止，若想继续排课，请修正输入文件错误后继续." << std::endl;
			return 6;
		}

	}
	if (incompleteLineFlag) {
		if (incompleteLineFlag == 1) {
			std::cout << "【错误】文件错误：在输入的课程信息文件中，第" << incompleteLineFlag << "行，数据不完整或格式有误\n(请保证输入文件内容不为空)。\n\n排课已终止，若想继续排课，请修正输入文件错误后继续." << std::endl;
		}
		else {
			std::cout << "【错误】文件错误：在输入的课程信息文件中，第" << incompleteLineFlag << "行，数据不完整或格式有误\n(若该行为行末空行，请删除行末换行回车)。\n\n排课已终止，若想继续排课，请修正输入文件错误后继续." << std::endl;
		}
		return 3;
	}
	if (invalidLenFlag) {
		std::cout << "【错误】文件错误：在输入的课程信息文件中，第" << invalidLenFlag << "行，课程长度不合法。\n\n排课已终止，若想继续排课，请修正输入文件错误后继续." << std::endl;
		return 4;
	}
	if (invalidSemFlag) {
		std::cout << "【错误】文件错误：在输入的课程信息文件中，第" << invalidSemFlag << "行，开课学期不合法。\n\n排课已终止，若想继续排课，请修正输入文件错误后继续." << std::endl;
		return 5;
	}

	relationPreq = new int[relationCount];
	relationSucc = new int[relationCount];

	int temp;
	for (int i = 0; i < courseCount; i++) {
		HashTable preqHashList;
		for (LinkedListIterator<std::string> j = course[i].PrerequisiteStrings.GetIterator(); !j.isNull(); j.GoNext()) {
			j.GetValue(strBuffer);

			if (courseIdDict.Get(strBuffer, temp) == false) {
				std::cout << "【错误】文件错误：在输入的课程信息文件中，课程" << course[i].Identity << "的先修课" << strBuffer << "无法在课程信息中找到对应条目。\n\n排课已终止，若想继续排课，请修正输入文件错误后继续." << std::endl;

				delete[] relationPreq;
				delete[] relationSucc;

				return 4;
			}
			int iPreqTemp;
			if (preqHashList.Get(strBuffer, iPreqTemp)) {
				std::cout << "【错误】文件错误：在输入的课程信息文件中，课程" << course[i].Identity << "的先修课信息存在重复（同一先修课出现2次或以上）。\n\n排课已终止，若想继续排课，请修正输入文件错误后继续." << std::endl;

				delete[] relationPreq;
				delete[] relationSucc;
				return 5;
			}
			preqHashList.Set(strBuffer, temp);

			course[i].Prerequisites.PushBack(temp);
			course[i].PrerequisitesRelationId.PushBack(relationLdCur);
			relationPreq[relationLdCur] = temp;
			relationSucc[relationLdCur] = i;
			topoInDegree[i]++;
			topoInDegree2[i]++;
			topoRevInd[temp]++;
			course[temp].Successors.PushBack(i);
			course[temp].SuccessorsRelationId.PushBack(relationLdCur++);
		}
	}


	return 0;
}
//************************************
// 全名:  CourseArrangeSystem::CheckTopologicalAvailability
// 功能:  检查排课可行性
// 权限:    public
// 返回:   int
//************************************
int CourseArrangeSystem::CheckTopologicalAvailability() {
	bool hasCircle = false;
	int *vis = new int[courseCount], t, p, viscnt = 0;
	Queue<int> q;
	for (int i = 0; i < courseCount; i++) {
		vis[i] = 0;
		course[i].AvailSemEnd = semesterCount;
		if (course[i].Semester != 0) {
			course[i].AvailSemEnd = course[i].Semester;
			course[i].AvailSemStart = course[i].Semester;
		}
		if (topoInDegree2[i] == 0) {
			q.Push(i);
			viscnt++;
			vis[i] = true;
		}
	}
	while (!q.Empty()) {
		q.Front(t); q.Pop();
		for (LinkedListIterator<int> i = course[t].Successors.GetIterator(); !i.isNull(); i.GoNext()) {
			i.GetValue(p);
			topoInDegree2[p]--;
			if (topoInDegree2[p] == 0 && !vis[p]) {
				vis[p] = 1;
				viscnt++;
				course[p].AvailSemStart = course[t].AvailSemStart + 1;
				q.Push(p);
			}
		}
	}
	if (viscnt != courseCount) {
		return 1;
	}

	viscnt = 0;
	for (int i = 0; i < courseCount; i++) {
		vis[i] = 0;
		if (topoRevInd[i] == 0) {
			q.Push(i);
			viscnt++;
			vis[i] = true;
		}
	}
	while (!q.Empty()) {
		q.Front(t); q.Pop();
		for (LinkedListIterator<int> i = course[t].Prerequisites.GetIterator(); !i.isNull(); i.GoNext()) {
			i.GetValue(p);
			topoRevInd[p]--;
			if (topoRevInd[p] == 0 && !vis[p]) {
				vis[p] = 1;
				viscnt++;
				course[p].AvailSemEnd = course[t].AvailSemEnd - 1;
				q.Push(p);
			}
		}
	}
	for (int i = 0; i < courseCount; i++) {
		if (course[i].AvailSemEnd < course[i].AvailSemStart) {
			return 2;
		}
		if (course[i].Length > semesterMaxTime) {
			return 3;
		}
	}
	return 0;
}
//************************************
// 全名:  CourseArrangeSystem::TopologicalSearch
// 功能: 排课开始
// 权限:    public
// 返回:   int
//************************************
int CourseArrangeSystem::TopologicalSearch() {
	for (int i = 0; i < courseCount; i++) {//预先安排学期已经确定的课程，减少DFS递归深度
		if (course[i].Semester != 0) {
			semUsedTime[course[i].Semester] += course[i].Length;
			semContent[course[i].Semester].PushFront(i);
			visited[i] = 1;
			dispatchSemester[i] = course[i].Semester;
			fixedCourses++;
			semesterUsedCourse[course[i].Semester - 1]++;
		}
	}
	int a = TopologicalSearch(1, 0);
	if (a == 0) {
		std::cout << "【错误】排课：给定课表无法在" << semesterCount << "学期内安排完毕。\n\n 排课终止，若想重新排课，请修改课程信息后重启此系统。\n" << std::endl;
	}
	return a;
}
//************************************
// 全名:  CourseArrangeSystem::TopologicalSearch
// 功能: 将课程分配到每个学期
// 权限:    public
// 返回:   int
// 参数: int semester 学期
// 参数: int curCourse 已分配课程数
//************************************
int CourseArrangeSystem::TopologicalSearch(int semester, int curCourse) {
	if (semester > semesterCount + 1) return 0;
	if (semester == semesterCount + 1 && curCourse != courseCount - fixedCourses) { return 0; }
	if (semUsedTime[semester] > semesterMaxTime) return 0;
	if (semester == semesterCount + 1 && curCourse == courseCount - fixedCourses) {
		DetailedDispatch();
		return 1;
	}

	int succ, lsm;
	if (semesterCourseLimit[semester - 1] == -1 || (semesterCourseLimit[semester - 1] != -1 && semesterCourseLimit[semester - 1] > semesterUsedCourse[semester - 1])) {
		for (int i = 0; i < courseCount; i++) {
			if (visited[i] == 0 && semester > course[i].AvailSemEnd) {
				return 0;
			}

			if (course[i].Semester == 0 || course[i].Semester == semester) {
				leastSem[i].Top(lsm);
				if (topoInDegree[i] == 0 && semester >= lsm && !visited[i]) {
					for (LinkedListIterator<int> j = course[i].Successors.GetIterator(); !j.isNull(); j.GoNext()) {
						j.GetValue(succ);
						topoInDegree[succ]--;
						leastSem[succ].Push(semester + 1);
					}
					semUsedTime[semester] += course[i].Length;
					semContent[semester].PushFront(i);
					visited[i] = 1;
					dispatchSemester[i] = semester;
					semesterUsedCourse[semester - 1]++;

					int s = TopologicalSearch(semester, curCourse + 1);

					semesterUsedCourse[semester - 1]--;
					dispatchSemester[i] = 0;
					semContent[semester].PopFront();
					semUsedTime[semester] -= course[i].Length;
					visited[i] = 0;
					for (LinkedListIterator<int> j = course[i].Successors.GetIterator(); !j.isNull(); j.GoNext()) {
						j.GetValue(succ);
						topoInDegree[succ]++;
						leastSem[succ].Pop();
					}
					if (s == 1)return 1;
				}

			}
		}
	}

	if (semesterCourseLimit[semester - 1] == -1 || (semesterCourseLimit[semester - 1] != -1 && semesterCourseLimit[semester - 1] == semesterUsedCourse[semester - 1])) {
		return TopologicalSearch(semester + 1, curCourse);
	}
	else {
		return 0;
	}

}
//************************************
// 全名:  CourseArrangeSystem::DetailedDispatch
// 功能: 在每学期内分配课程
// 权限:    public
// 返回:   void
//************************************
void CourseArrangeSystem::DetailedDispatch() {
	CourseDispatchSolution *result = new CourseDispatchSolution[semesterCount + 1]; //用于存放初始解
	int **occupied = new int*[semesterWeekdays]; //第i天，第j节课是否被占用
	int *getWeekday = new int[2 * semesterWeekdays + 1];//下一次尝试排课的日期
	for (int i = 0; i <= 2 * semesterWeekdays; i++) {
		getWeekday[i] = i * 2 % semesterWeekdays;
	}

	for (int i = 0; i < semesterWeekdays; i++) {
		occupied[i] = new int[semesterLessonsInterval];
		for (int j = 0; j < semesterLessonsInterval; j++) {
			occupied[i][j] = 0;
		}
	}
	for (int i = 0; i <= semesterCount; i++) {
		result[i].Init(semesterWeekdays, semesterLessonsPerDay, courseCount);
	}
	int curCourse;
	for (int i = 1; i <= semesterCount; i++) {
		for (int j = 0; j < semesterWeekdays; j++) {
			for (int k = 0; k < semesterLessonsInterval; k++) {
				occupied[j][k] = 0;
			}
		}
		for (LinkedListIterator<int> j = semContent[i].GetIterator(); !j.isNull(); j.GoNext()) {
			j.GetValue(curCourse);
			int *occupiedWeekdays=new int [semesterWeekdays];
			int sFlag = 0;
			for (int k = 0; k <= 2 * semesterWeekdays; k++) {
				for (int l = semesterLessonsInterval-1; l >=0; l--) {
					sFlag = 0;
					//优先分配三节课
					if (!occupied[getWeekday[k]][l] && course[curCourse].AvailLength >= 3 && semesterLessonsIntervalDuration[l] == 3) {
						occupied[getWeekday[k]][l] = 1;
						course[curCourse].AvailLength -= 3;

						result[i].AttachDispatchInfo(curCourse, getWeekday[k], semesterLessonsIntervalBegin[l], semesterLessonsIntervalBegin[l] + 2);
						sFlag = 1;
						break;
					}
					if (sFlag == 1)break;
					//再分配两节课
					if (!occupied[getWeekday[k]][l] && course[curCourse].AvailLength >= 2 && semesterLessonsIntervalDuration[l] == 2) {
						occupied[getWeekday[k]][l] = 1;
						course[curCourse].AvailLength -= 2;
						result[i].AttachDispatchInfo(curCourse, getWeekday[k], semesterLessonsIntervalBegin[l], semesterLessonsIntervalBegin[l] + 1);
						sFlag = 1;
						break;
					}
					if (sFlag == 1)break;
				}
			}
			delete[]occupiedWeekdays;
		}
		//分配单节课，保证课程不在相邻两天开设
		int *occupiedByCurCourse = new int[semesterWeekdays];
		for (LinkedListIterator<int> j = semContent[i].GetIterator(); !j.isNull(); j.GoNext()) {
			j.GetValue(curCourse);
			if (course[curCourse].AvailLength == 0)break;
			for (int k = 0; k < semesterWeekdays; k++) {
				occupiedByCurCourse[k] = 0;
			}
			for (int k = 0; k < semesterWeekdays; k++) {
				for (int l = 0; l < semesterLessonsPerDay; l++) {
					if (result[i].courseTable[k][l] == curCourse) {
						occupiedByCurCourse[k] = 1;
						occupiedByCurCourse[(k + semesterWeekdays - 1) % semesterWeekdays] = 1;
						occupiedByCurCourse[(k + 1) % semesterWeekdays] = 1;
					}
				}
			}
			for (int k = 0; k < semesterWeekdays; k++) {
				if (occupiedByCurCourse[k])continue;
				if (course[curCourse].AvailLength == 0)break;
				for (int l = 0; l < semesterLessonsPerDay; l++) {
					if (course[curCourse].AvailLength == 0)break;
					if (result[i].courseTable[k][l] == -1) {
						course[curCourse].AvailLength--;
						result[i].AttachDispatchInfo(curCourse, k, l, l);
					}
				}
			}
		}
		delete[] occupiedByCurCourse;
		//最后分配单节课，不保证课程不在相邻两天开设
		for (LinkedListIterator<int> j = semContent[i].GetIterator(); !j.isNull(); j.GoNext()) {
			j.GetValue(curCourse);
			if (course[curCourse].AvailLength == 0)break;
			for (int k = 0; k < semesterWeekdays; k++) {
				if (course[curCourse].AvailLength == 0)break;
				for (int l = 0; l < semesterLessonsPerDay; l++) {
					if (course[curCourse].AvailLength == 0)break;
					if (result[i].courseTable[k][l] == -1) {
						course[curCourse].AvailLength--;
						result[i].AttachDispatchInfo(curCourse, k, l, l);
					}
				}
			}
		}
	}
	currentBestPlan.init(semesterCount, courseCount, &result[1], dispatchSemester);
	delete[] result;
}
//************************************
// 全名:  CourseArrangeSystem::OutputSpacings
// 功能: 输出空格
// 权限:    public
// 返回:   void
// 参数: int x 空格数
//************************************
void CourseArrangeSystem::OutputSpacings(int x) {
	for (int i = 0; i < x; i++)fout << " ";
}


//************************************
// 全名:  CourseArrangeSystem::GetEvaluationValue
// 功能: 评估排课方案的优良度
// 权限:    public
// 返回:   long long
// 参数: const OverallCourseDispatchSol & x
//************************************
long long CourseArrangeSystem::GetEvaluationValue(const OverallCourseDispatchSol& x) {
	long long TotalEval = 0;

	long long DistributionEval = 0;
	long long courseCounter = 0;
	for (int i = 0; i < x.semesterCounter; i++) {
		courseCounter = x.semesterPlan[i].Weekdays*x.semesterPlan[i].CoursesPerDay;
		for (int j = 0; j < x.semesterPlan[i].Weekdays; j++) {
			for (int k = 0; k < x.semesterPlan[i].CoursesPerDay; k++) {
				if (x.semesterPlan[i].courseTable[j][k] != -1) {
					courseCounter--;
				}
			}
		}
		DistributionEval += courseCounter * courseCounter;
	}
	TotalEval += DistributionEval;
	long long ShatterIndex = 0;
	int diff;
	for (int i = 0; i < x.semesterCounter; i++) {
		for (int j = 0; j < x.semesterPlan[i].Courses; j++) {
			diff = x.semesterPlan[i].details[i].Size() - (course[i].Length / 3 + (course[i].Length % 3 !=0));
			ShatterIndex += diff * diff * 20000;
		}
	}
	TotalEval += ShatterIndex;
	return -TotalEval;
}

//************************************
// 全名:  CourseArrangeSystem::GetRandomAdjacentSolution
// 功能: 获得当前解的邻域内随机解
// 权限:    public
// 返回:   int
// 参数: const OverallCourseDispatchSol & x 当前解
// 参数: OverallCourseDispatchSol & result 新解返回值
// 参数: int extFunc
//************************************
int CourseArrangeSystem::GetRandomAdjacentSolution(const OverallCourseDispatchSol& x, OverallCourseDispatchSol& result, int extFunc) {
	result = x;
	int r = rand() % 1;
	if (r == 0) {
		int randCourseId;
		while (1) {
			randCourseId = rand() % courseCount;
			if (semesterCourseLimit[x.courseSem[randCourseId]] != -1) {
				if (rand() % 2 == 0) {
					//std::cout << "RETURN::" << randCourseId <<" Disp"<< dispatchSemester[randCourseId] << std::endl;
					return 0;
				}
			}
			else {
				break;
			}
		}
		//std::cout << "W::" << randCourseId << " Disp" << x.courseSem[randCourseId] << std::endl;


		int orgSem = x.courseSem[randCourseId], newSem;

		int succ;
		int *AvailSem = nullptr, AvailSemPos = 0, *PlaceWeekday = nullptr;
		int *AvailSemCounterArr = nullptr, AvailSemCounter = semesterCount;
		AvailSemCounterArr = new int[semesterCount];
		for (int i = 0; i < semesterCount; i++)AvailSemCounterArr[i] = 1;
		AvailSemCounterArr[x.courseSem[randCourseId]] = 0; AvailSemCounter--;
		if (course[randCourseId].Semester == 0 && extFunc == 0) {
			for (LinkedListIterator<int> i = course[randCourseId].Successors.GetIterator(); !i.isNull(); i.GoNext()) {
				i.GetValue(succ);
				for (int j = x.courseSem[succ]; j < semesterCount; j++) {
					if (AvailSemCounterArr[j] == 1) {
						AvailSemCounterArr[j] = 0;
						AvailSemCounter--;
					}
				}
			}
			for (int k = 0; k < semesterCount; k++) {
				if (AvailSemCounterArr[k] == 1 && semesterCourseLimit[k] != -1) {
					AvailSemCounterArr[k] = 0;
					AvailSemCounter--;
				}
			}
			if (AvailSemCounter == 0)return 0;

			AvailSem = new int[AvailSemCounter];
			for (int i = 0; i < semesterCount; i++) {
				if (AvailSemCounterArr[i] == 1) {
					AvailSem[AvailSemPos++] = i;
				}
			}
			newSem = AvailSem[rand() % AvailSemCounter];
			delete[] AvailSem;
		}
		else {
			newSem = orgSem;
		}
		delete[]AvailSemCounterArr;
		//删除原有学期信息
		DispatchInfo t;
		for (LinkedListIterator<DispatchInfo> i = result.semesterPlan[orgSem].details[randCourseId].GetIterator(); !i.isNull(); i.GoNext()) {
			i.GetValue(t);
			for (int j = t.TimeBegin; j <= t.TimeEnd; j++) {
				result.semesterPlan[orgSem].courseTable[t.Weekday][j] = -1;
			}
		}
		while (result.semesterPlan[orgSem].details[randCourseId].Size())result.semesterPlan[orgSem].details[randCourseId].PopFront();

		//在新学期分配此课程
		int *getWeekday = new int[2 * semesterWeekdays + 1];
		int disturbance = rand() % 5;
		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			getWeekday[i] = (i * 2 + disturbance) % semesterWeekdays;
		}
		int **occupied = new int*[semesterWeekdays]; //大课在新学期的占用状态
		for (int i = 0; i < semesterWeekdays; i++) {
			occupied[i] = new int[semesterLessonsInterval];
			for (int j = 0; j < semesterLessonsInterval; j++) {
				occupied[i][j] = 0;
			}
		}
		for (int i = 0; i < semesterWeekdays; i++) {
			for (int j = 0; j < semesterLessonsInterval; j++) {
				for (int k = semesterLessonsIntervalBegin[j]; k < semesterLessonsIntervalBegin[j] + semesterLessonsIntervalDuration[j]; k++) {
					if (result.semesterPlan[newSem].courseTable[i][k] != -1) {
						occupied[i][j] = 1;
					}
				}
			}
		}
		course[randCourseId].AvailLength = course[randCourseId].Length;
		PlaceWeekday = new int[semesterWeekdays];
		for (int i = 0; i < semesterWeekdays; i++) {
			PlaceWeekday[i] = 0;
		}
		//优先分配两节课和三节课

		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			if (PlaceWeekday[getWeekday[i]] == 1)continue;
			for (int j = semesterLessonsInterval - 1; j >= 0; j--) {
				if (!occupied[getWeekday[i]][j] && course[randCourseId].AvailLength >= 3 && semesterLessonsIntervalDuration[j] == 3) {
					occupied[getWeekday[i]][j] = 1;
					course[randCourseId].AvailLength -= 3;
					result.semesterPlan[newSem].AttachDispatchInfo(randCourseId, getWeekday[i], semesterLessonsIntervalBegin[j], semesterLessonsIntervalBegin[j] + 2);
					PlaceWeekday[getWeekday[i]] = 1;
					PlaceWeekday[(getWeekday[i] + 1) % semesterWeekdays] = 1;
					PlaceWeekday[(getWeekday[i] + semesterWeekdays - 1) % semesterWeekdays] = 1;

					break;
				}
			}
		}
		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			if (PlaceWeekday[getWeekday[i]] == 1)continue;
			for (int j = semesterLessonsInterval - 1; j >= 0; j--) {
				if (!occupied[getWeekday[i]][j] && course[randCourseId].AvailLength >= 2 && semesterLessonsIntervalDuration[j] == 2) {
					occupied[getWeekday[i]][j] = 1;
					course[randCourseId].AvailLength -= 2;
					result.semesterPlan[newSem].AttachDispatchInfo(randCourseId, getWeekday[i], semesterLessonsIntervalBegin[j], semesterLessonsIntervalBegin[j] + 1);
					PlaceWeekday[getWeekday[i]] = 1;
					PlaceWeekday[(getWeekday[i] + 1) % semesterWeekdays] = 1;
					PlaceWeekday[(getWeekday[i] + semesterWeekdays - 1) % semesterWeekdays] = 1;

					break;
				}
			}
		}
		//之后分配单节课
		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			if (course[randCourseId].AvailLength == 0)break;
			if (PlaceWeekday[getWeekday[i]] == 1)continue;
			for (int j = 0; j < semesterLessonsPerDay; j++) {
				if (course[randCourseId].AvailLength == 0)break;
				if (result.semesterPlan[newSem].courseTable[getWeekday[i]][j] == -1) {
					course[randCourseId].AvailLength--;
					result.semesterPlan[newSem].AttachDispatchInfo(randCourseId, getWeekday[i], j, j);
				}
			}
		}

		//按照尽量不分在同一天的原则继续分配
		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			for (int j = semesterLessonsInterval - 1; j >= 0; j--) {
				if (!occupied[getWeekday[i]][j] && course[randCourseId].AvailLength >= 3 && semesterLessonsIntervalDuration[j] == 3) {
					occupied[getWeekday[i]][j] = 1;
					course[randCourseId].AvailLength -= 3;
					result.semesterPlan[newSem].AttachDispatchInfo(randCourseId, getWeekday[i], semesterLessonsIntervalBegin[j], semesterLessonsIntervalBegin[j] + 2);
					PlaceWeekday[getWeekday[i]] = 1;
					break;
				}
			}
		}
		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			if (PlaceWeekday[getWeekday[i]] == 1)continue;
			for (int j = semesterLessonsInterval - 1; j >= 0; j--) {
				if (!occupied[getWeekday[i]][j] && course[randCourseId].AvailLength >= 2 && semesterLessonsIntervalDuration[j] == 2) {
					occupied[getWeekday[i]][j] = 1;
					course[randCourseId].AvailLength -= 2;
					result.semesterPlan[newSem].AttachDispatchInfo(randCourseId, getWeekday[i], semesterLessonsIntervalBegin[j], semesterLessonsIntervalBegin[j] + 1);
					PlaceWeekday[getWeekday[i]] = 1;
					break;
				}
			}
		}
		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			if (course[randCourseId].AvailLength == 0)break;
			for (int j = 0; j < semesterLessonsPerDay; j++) {
				if (course[randCourseId].AvailLength == 0)break;
				if (result.semesterPlan[newSem].courseTable[getWeekday[i]][j] == -1) {
					course[randCourseId].AvailLength--;
					result.semesterPlan[newSem].AttachDispatchInfo(randCourseId, getWeekday[i], j, j);
				}
			}
		}
		delete[]PlaceWeekday;
		delete[]getWeekday;
		//结束分配
		result.courseSem[randCourseId] = newSem;
		if (course[randCourseId].AvailLength > 0) {
			result = x;
		}

		for (int i = 0; i < semesterWeekdays; i++) {
			delete[] occupied[i];
		}
		delete[] occupied;
		return 0;
	}
	return 0;
}
//************************************
// 全名:  CourseArrangeSystem::SimulatedAnnealing
// 功能: 优化
// 权限:    public
// 返回:   void
// 参数: int GRASFunc
//************************************
void CourseArrangeSystem::SimulatedAnnealing(int GRASFunc) {
	long long Temperature = 2000000, TemperatureLBound = 100; //初始温度和温度下限，若速度优先，精度要求较低，可以调低初始温度。
	long long Diff;
	double CooldownRate = 0.996; //冷却速度，若速度优先，精度要求较低，可以调低此数值。
	OverallCourseDispatchSol cur = currentBestPlan, attempt;
	OverallCourseDispatchSol best = currentBestPlan;
	while (Temperature > TemperatureLBound) {
		attempt = cur;
		GetRandomAdjacentSolution(cur, attempt, GRASFunc);
		Diff = GetEvaluationValue(attempt) - GetEvaluationValue(cur);
		if (Diff > 0) {
			if (GetEvaluationValue(attempt) > GetEvaluationValue(best)) {
				best = attempt;
			}
			cur = attempt;
		}
		else {
			int wT = (int)(exp((double)Diff / (double)Temperature) * 1000.0);
			int rT = rand() % 1000;
			if (wT > rT) {
				cur = attempt;
				//std::cout << "Accept" << std::endl;
			}
		}
		Temperature = (long long)((double)Temperature*CooldownRate);
	}
	currentBestPlan = best;
}

int stlex_Strlen(std::string source, int asciiWeight=1, int nonAsciiWeight=2, int encoding=0) {
#ifndef _WIN32
		const char* cdata = source.data();
		const char* i;
		unsigned char cur;
		if (!cdata) return 0;
		int ret = 0, len = source.length();
		for (i = cdata; (i - cdata) < len && (*i) != '\0';) {
			cur = (unsigned char)(*i);
			if (cur < 128) {
				i++; ret += asciiWeight;
			}
			else if (cur < 192) {
				i++;
			}
			else if (cur < 224) {
				i += 2; ret += nonAsciiWeight;
			}
			else if (cur < 240) {
				i += 3; ret += nonAsciiWeight;
			}
			else {
				i += 4; ret += nonAsciiWeight;
			}
		}
		return ret;
#else
		int ret = 0, len = source.length();
		char cur;
		const char* cdata=source.data();
		const char* i;
		for (i = cdata; (i - cdata) < len && (*i) != '\0';) {
			cur = (char)(*i);
			if (cur & 128) {
				i += 2;
				ret += nonAsciiWeight;
			}
			else {
				i++;
				ret += asciiWeight;
			}
		}
		return ret;
#endif

	return 0;
}
//************************************
// 全名:  CourseArrangeSystem::Print
// 功能: 输出解
// 权限:    public
// 返回:   void
// 参数: OverallCourseDispatchSol p
//************************************
void CourseArrangeSystem::Print(OverallCourseDispatchSol p) {
	CourseDispatchSolution w;
	fout << "【若出现格式错乱，请关闭文本编辑器的“自动换行”功能】" << std::endl << std::endl;
	for (int i = 0; i < semesterCount; i++) {
		fout << "【第" << i + 1 << "学期】" << std::endl;
		for (int j = 0; j < semesterWeekdays; j++) {
			fout << "| <星期" << j + 1 << ">";
			#ifdef _WIN32
			OutputSpacings(outputColumnSpacings - 9);
			#else
            OutputSpacings(outputColumnSpacings - 9);
			#endif
		}
		fout << std::endl;
		w = p.semesterPlan[i];
		for (int j = 0; j < semesterLessonsPerDay; j++) {
			for (int k = 0; k < semesterWeekdays; k++) {
				if (w.courseTable[k][j] >= 0) {
					std::string strTemp = "| " + std::string("(") + course[w.courseTable[k][j]].Identity + ")" + course[w.courseTable[k][j]].Name;
					if (strTemp.length() >= outputColumnSpacings - 4) {
						strTemp = strTemp.substr(0, outputColumnSpacings - 4) + "... ";
					}
					fout << strTemp;
					OutputSpacings(outputColumnSpacings - stlex_Strlen(course[w.courseTable[k][j]].Name) - 4 - stlex_Strlen(course[w.courseTable[k][j]].Identity));
				}
				else {
					fout << "| (无课程)";
					#ifdef _WIN32
                    OutputSpacings(outputColumnSpacings - 10);
                    #else
                    OutputSpacings(outputColumnSpacings - 10);
                    #endif
				}
			}
			fout << std::endl;
		}
		fout << std::endl;
	}
}
//************************************
// 全名:  CourseArrangeSystem::SetEachSemesterLimit
// 功能: 输入每一学期的课程限制
// 权限:    public
// 返回:   void
//************************************
void CourseArrangeSystem::SetEachSemesterLimit() {
	std::cout << " 请在一行中输入" << semesterCount << "个学期，每个学期的开课数，用空格分隔。（-1 表示不对此学期限制）" << std::endl;
	semesterCourseLimit = new int[semesterCount];
	std::string intRead, intRead2;
	std::stringstream ost;
	while (1) {
		int autoDispatchFlag = false;
		std::getline(std::cin, intRead);
		ost.clear();
		ost << intRead;
		for (int i = 0; i < 8; i++) {
			if (ost >> intRead2) {
				if (isDigitStr(intRead2) == false && intRead2 != "-1") {
					std::cout << std::endl << "第" << i + 1 << "学期的课程数无效。请重新输入所有数据。";
					continue;
				}
				else {
					semesterCourseLimit[i] = std::stoi(intRead2);
					if (semesterCourseLimit[i] == -1)autoDispatchFlag = true;
				}
			}
			else {
				std::cout << std::endl << "第" << i + 1 << "学期的课时数未输入。请重新输入所有数据。";
				continue;
			}
		}

		int tw = 0, iflag = 0;
		for (int i = 0; i < semesterCount; i++) {
			tw = 0;
			for (int j = 0; j < courseCount; j++) {
				if (course[j].Semester == i + 1)tw++;
			}
			if (semesterCourseLimit[i] != -1 && semesterCourseLimit[i] < tw) {
				iflag = 1;
				std::cout << std::endl << " 由于排课信息设定，第"<<i+1<<"学期至少有"<<tw<<"门课程要开设。请重新输入所有数据。"<<std::endl;
				break;
			}
		}
		if (iflag != 0)continue;
		if (!autoDispatchFlag) {
			int sum = 0;
			for (int i = 0; i < semesterCount; i++) {
				sum += semesterCourseLimit[i];
			}

			if (sum != courseCount) {
				std::cout << std::endl << " 每学期所开的课程数之和与课程总数不等。请重新输入所有数据。" << std::endl;
				continue;
			}
		}
		break;

	}

}
//**********主程序**************
#include <time.h>

void CASCall() {
	srand(time(NULL)); rand();
	CourseArrangeSystem CAS;
	std::cout << "********************************************" << std::endl << std::endl;
	std::cout << "\t欢迎使用排课系统!" << std::endl << std::endl;
	std::cout << "********************************************" << std::endl << std::endl;
	std::cout << " 1. 课程信息文件每行格式如下:[课号] [课程名称] [课时数] [开课学期] 先修课1课号 ... 先修课n课号" << std::endl;
	std::cout << "    (上述带括号项为必选项)" << std::endl;
	std::cout << " 2. 默认输入文件为input.txt，默认输出文件为output.txt。不可访问时，您可自行指定输入或输出文件。" << std::endl;
	std::cout << " 3. 如果课程信息文件中有空行（包括行末的回车），请删除空行后再允许此系统" << std::endl;
	std::cout << " 4. 排课按照" << CAS.semesterCount << "个学期，每天" << CAS.semesterLessonsPerDay << "课时,一周上课" << CAS.semesterWeekdays << "天为标准，进行排课" << std::endl;
	std::cout << " 5. 请保证课程信息的先修关系合法、课时数和开课学期信息合法。" << std::endl;
	std::cout << std::endl << "********************************************" << std::endl << std::endl;
	int w;
	if (!CAS.ReadCourses()) {
		if (!(w = CAS.CheckTopologicalAvailability())) {
			std::cout << std::endl;
			CAS.SetEachSemesterLimit();
			std::cout << std::endl;
			std::cout << " 课程安排开始..." << std::endl << std::endl;
			if (CAS.TopologicalSearch() != 0) {
				std::cout << " 正在优化课程安排，请稍后..." << std::endl << std::endl;
				CAS.SimulatedAnnealing();
				CAS.PrintBest();

				std::cout << " 课程安排已经完成！课程安排方案已经储存于" << CAS.outputFileStr << "中" << std::endl << std::endl;
			}
		}
		else {
			switch (w) {
			case 1:
				std::cout << "【错误】课程信息非法：存在两门课程互为先修课。" << std::endl << std::endl;
				break;
			case 2:
				std::cout << "【错误】课程信息非法：在给定先修关系和开课学期下，存在课程无法进行安排" << std::endl << std::endl;
				break;
			case 3:
				std::cout << "【错误】课程信息非法：存在课程课时过长（大于学期课时总数）" << std::endl << std::endl;
				break;
			}
			std::cout << "请修改课程信息后，重新启动排课系统。" << std::endl << std::endl;

		}
		CAS.PreUnload();
	}
	else {
		std::cout << "" << std::endl << std::endl;
	}
#ifdef _WIN32
	system("pause");
#endif
}

int main() {
	CASCall();
	return 0;
}
