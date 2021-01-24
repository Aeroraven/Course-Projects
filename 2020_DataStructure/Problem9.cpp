#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <climits>
#include <stdexcept>
#include <fstream>
#include <cmath>
//��������
//************************************
// ȫ��:  isDigitStr
// ����: �ж�string�Ƿ��������ַ���
// Ȩ��:    public
// ����:   bool �Ƿ��������ַ���
// ����: std::string argv
//************************************
bool isDigitStr(std::string argv) {
	for (int i = 0; i < argv.length(); i++)if (!(argv[i] >= '0'&&argv[i] <= '9'))return false;
	return true;
}

//�࿪ʼ
template<typename Type>class LinkedListNode; //������
template<typename Type>class LinkedList; //����
template<typename Type>class LinkedListIterator; //���������

template<typename Type>class LinkedListNode {
public:
	Type data; //������
	LinkedListNode<Type> *succ = nullptr; //ָ����
};
template<typename Type>class LinkedList {
private:
	LinkedListNode<Type> *head = nullptr, *tail = nullptr; //ͷβָ��
	int size = 0; //�����С
public:
	friend class LinkedListIterator<Type>;
	LinkedList();
	~LinkedList();
	bool PushBack(const Type& data); //β�˲���
	bool PushFront(const Type& data); //ǰ�˲���
	bool PopFront(); //ǰ�˵���
	int Size() { return size; } //�����С
	LinkedListIterator<Type> GetIterator(); //������������
};
template<typename Type>class LinkedListIterator {
private:
	LinkedList<Type> *boundList; //����������
	LinkedListNode<Type> *cur; //ָ��Ľ��
public:
	LinkedListIterator(LinkedList<Type>* linklist);
	bool GoNext(); //��һ���
	bool Reset(); //����ָ�뵽ͷ�ڵ����һ���
	bool GetValue(Type& result); //��õ�ǰ���ָ����
	bool isNull(); //��ǰ����п�
};
template<typename Type>class Stack {
private:
	LinkedList<Type> linkedStack; //��ʽջ����
public:
	bool Push(const Type& p); //��ջ
	bool Pop(); //��ջ
	bool Top(Type& p); //���ջ��
	bool Empty(); //�ж�ջ��
};

template<typename Type>class Queue {
private:
	LinkedList<Type> linkedQueue; //��ʽ��������
public:
	bool Push(const Type& p); //����У�EnQue��
	bool Pop(); //�����У�DeQue��
	bool Front(Type& p); //����ǰ��
	bool Empty(); //�����п�
};

class HashTableElement {
public:
	std::string OriginalChar;
	int Index;
};
class HashTable { //Hash��
private:
	const int ModulusFactor = 947;
	LinkedList<HashTableElement> *HashList; //ɢ�б�
public:
	HashTable();
	~HashTable();
	bool Get(std::string CompareString, int& Index); //ɢ�б����ַ�������
	bool Set(std::string InsertString, int Index); //ɢ�б��棨�ַ�������������
	int GetKey(std::string Dest); //ɢ�б��ȡ�ַ�����Ӧ������
};
class DispatchInfo { //������Ϣ
public:
	int Weekday; //���ε�����
	int TimeBegin, TimeEnd; //���εĽ���
};
class CourseInfo { //�γ���Ϣ
public:
	std::string Identity; //�γ̱��
	std::string Name; //�γ�����
	int Length; //��ʱ��
	int AvailLength; //ʣ���ʱ��
	int Semester; //����ѧ��
	LinkedList<std::string> PrerequisiteStrings; //���޿γ��ַ���
	LinkedList<int> Prerequisites; //���޿γ�
	LinkedList<int> PrerequisitesRelationId;
	LinkedList<int> Successors; //��̿γ�
	LinkedList<int> SuccessorsRelationId;

	int AvailSemEnd, AvailSemStart;
};
class CourseDispatchSolution {
public:
	int Weekdays, CoursesPerDay, Courses, InitStat = 0; //������Ϣ
	int **courseTable; //�γ̱�
	LinkedList<DispatchInfo> *details; //�γ̵ĸ���С����Ϣ
	CourseDispatchSolution() {}
	CourseDispatchSolution(const CourseDispatchSolution& x);
	const CourseDispatchSolution& operator =(const CourseDispatchSolution& x);

	void Init(int weekdays, int coursesPerDay, int courses); //��ʼ��
	void AttachDispatchInfo(int courseId, int weekdays, int begin, int end); //��ӿγ̵�һ���Ͽ�ʱ��
	void Demolition(); //ɾ���γ̷��䷽��
	~CourseDispatchSolution() { Demolition(); }
};


class OverallCourseDispatchSol {
public:
	int semesterCounter = 0, initStat = 0;
	CourseDispatchSolution *semesterPlan = nullptr; //ÿ��ѧ�ڵĿγ̱�
	int* courseSem = nullptr; //ÿ���γ̵�ѧ��
	int courseCnt = 0;

	OverallCourseDispatchSol() {};
	OverallCourseDispatchSol(const OverallCourseDispatchSol& x);
	const OverallCourseDispatchSol& operator =(const OverallCourseDispatchSol& x);
	void init(int semCounter, int courseCounter, CourseDispatchSolution *dspSol, int *cSem); //��ʼ��
	~OverallCourseDispatchSol();
};



class CourseArrangeSystem {
public:
	const int semesterCount = 8; //ѧ����
	const int semesterMaxTime = 50; //ѧ�ڿ�ʱ��
	const int semesterWeekdays = 5; //ѧ��ÿ�ܽ�ѧ����Ŀ
	const int semesterLessonsPerDay = 10; //ÿ���ʱ��
	const int semesterLessonsInterval = 4; //�����Ŀ
	const int semesterLessonsIntervalDuration[4] = { 2,3,2,3 }; //���ʱ��
	const int semesterLessonsIntervalBegin[4] = { 0,2,5,7 }; //�����ʼ��ʱ
	#ifdef _WIN32
	const int outputColumnSpacings = 30; //����ļ��м��
	#else
    const int outputColumnSpacings = 40; //����ļ��м��
	#endif
private:
	LinkedList<std::string> courseArrangeInput; //��������
	CourseInfo *course = nullptr; //�γ���Ϣ����
	HashTable courseIdDict; //�γ̱���ֵ�
	std::ifstream fin; //�����ļ���
	std::ofstream fout; //����ļ���
	int courseCount = 0; //�γ���
	int *topoInDegree = nullptr, *topoInDegree2 = nullptr, *topoRevInd = nullptr; //������
	int *dispatchSemester = nullptr; //�����γ�����ѧ��-����
	int *visited = nullptr, *leastSemBak = nullptr;//����DFS����Ƿ���״̬
	int *semUsedTime = nullptr; //��DFS�����У���ѧ�����ÿ�ʱ��
	int fixedCourses = 0; //�Ѿ��̶�����ѧ�ڵĿγ���
	Stack<int> *leastSem = nullptr; //��DFS�����У��ÿγ̵����翪��ѧ��
	LinkedList<int> *semContent = nullptr;//ÿ��ѧ�ڵ�����
	OverallCourseDispatchSol currentBestPlan; //��ǰ���Ž�
	int *relationPreq = nullptr, *relationSucc = nullptr; //���޹�ϵ��
	int relationCount = 0, relationLdCur = 0;
public:
	int *semesterCourseLimit; //ÿ��ѧ�ڵ��趨�Ŀ���γ�����
	int *semesterUsedCourse; //��DFS�����У���ѧ���Ѿ�����Ŀγ���
public:
	std::string outputFileStr;
	~CourseArrangeSystem();
	int ReadCourses(); //��ȡ�ļ������������ȡ����Ϣ
	void OutputSpacings(int x); //����ո�
	int TopologicalSearch(); //�γ̷��䵽ѧ��
	int TopologicalSearch(int semester, int curCourse);//�γ̷��䵽ѧ�ڣ�����+DFS������
	void DetailedDispatch();//��ÿ��ѧ���ڷ���γ̣��õ����н�

	long long GetEvaluationValue(const OverallCourseDispatchSol& x); //��������
	int GetRandomAdjacentSolution(const OverallCourseDispatchSol& x, OverallCourseDispatchSol& result, int extFunc = 0); //��������ڵ���һ�������
	void SimulatedAnnealing(int GRASFunc = 0); //�Ż����н⣬ģ���˻�

	void Print(OverallCourseDispatchSol p);//�������
	void PrintBest() { Print(currentBestPlan); } //�����Ž����

	int CheckTopologicalAvailability();//�ж�������Ϣ���ſο����ԣ��������޹�ϵ�л���
	void PreUnload() { if (!fout.fail())fout.close(); } //�ر�����ļ���
	void SetEachSemesterLimit(); //ָ��ÿһ��ѧ�ڵĿ�����
};



//***********���忪ʼ***********


//�������䷽��
//************************************
// ȫ��:  OverallCourseDispatchSol::OverallCourseDispatchSol
// ����: ���ƹ��캯�����أ����)
// Ȩ��:    public
// ����:
// ����: const OverallCourseDispatchSol & x
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
// ȫ��:  OverallCourseDispatchSol::operator=
// ����: ��ֵ�������أ����)
// Ȩ��:    public
// ����:   const OverallCourseDispatchSol&
// ����: const OverallCourseDispatchSol & x
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
// ȫ��:  OverallCourseDispatchSol::init
// ����: ��ʼ�������ſη�������
// Ȩ��:    public
// ����:   void
// ����: int semCounter ѧ����
// ����: int courseCounter �γ���
// ����: CourseDispatchSolution * dspSol ÿѧ�ڵ��ſη���
// ����: int * cSem ÿ���γ�����ѧ��
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
// ȫ��:  OverallCourseDispatchSol::~OverallCourseDispatchSol
// ����: ��������
// Ȩ��:    public
// ����:
//************************************
OverallCourseDispatchSol::~OverallCourseDispatchSol() {
	if (!semesterPlan)delete[]semesterPlan;
	if (!courseSem)delete[]courseSem;
}
//���䷽��
//************************************
// ȫ��:  CourseDispatchSolution::Demolition
// ����: ɾ��������new��ָ��
// Ȩ��:    public
// ����:   void
//************************************
void CourseDispatchSolution::Demolition() {
	InitStat = 0;
	for (int i = 0; i < Weekdays; i++) delete[] courseTable[i];
	delete[]courseTable;
	delete[] details;
}
//************************************
// ȫ��:  CourseDispatchSolution::operator=
// ����: ��ֵ�������أ���ƣ�
// Ȩ��:    public
// ����:   const CourseDispatchSolution&
// ����: const CourseDispatchSolution & x
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
// ȫ��:  CourseDispatchSolution::CourseDispatchSolution
// ����: ���ƹ������أ����)
// Ȩ��:    public
// ����:
// ����: const CourseDispatchSolution & x
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
// ȫ��:  CourseDispatchSolution::Init
// ����: ��ѧ���ſη��������ʼ��
// Ȩ��:    public
// ����:   void
// ����: int weekdays ��ѧ����Ŀ
// ����: int coursesPerDay ÿ�տγ�
// ����: int courses �γ�����
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
// ȫ��:  CourseDispatchSolution::AttachDispatchInfo
// ����: ��ӿγ̵�һ��С���Ͽ�ʱ��
// Ȩ��:    public
// ����:   void
// ����: int courseId �γ̱�ţ���course�����е��±꣩
// ����: int weekdays ���������ڼ�
// ����: int begin ������ʼʱ��
// ����: int end ������ֹʱ��
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
//����
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
// ȫ��:  LinkedList::PushBack
// ����: ������β������Ԫ��
// Ȩ��:    public
// ����:   bool
// ����: const Type & data
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
// ȫ��:  LinkedList::PushFront
// ����: ������ͷ������Ԫ��
// Ȩ��:    public
// ����:   bool
// ����: const Type & data
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
// ȫ��:  LinkedList::PopFront
// ����: ��������ͷ��Ԫ��
// Ȩ��:    public
// ����:   bool
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
// ȫ��:  LinkedList::GetIterator
// ����: �������ĵ�����
// Ȩ��:    public
// ����:
//************************************
template<class Type> LinkedListIterator<Type> LinkedList<Type>::GetIterator() {
	return LinkedListIterator<Type>(this);
}

//�����α�
template<class Type> LinkedListIterator<Type>::LinkedListIterator(LinkedList<Type>* linklist) {
	boundList = linklist;
	cur = (linklist->head) ? linklist->head->succ : nullptr;
}
//************************************
// ȫ��:  LinkedListIterator::GoNext
// ����: ���α�ָ����һ���
// Ȩ��:    public
// ����:   bool
//************************************
template<class Type> bool LinkedListIterator<Type>::GoNext() {
	if (cur == nullptr)return false;
	cur = cur->succ;
	return true;
}
//************************************
// ȫ��:  LinkedListIterator::Reset
// ����: �������������
// Ȩ��:    public
// ����:   bool
//************************************
template<class Type> bool LinkedListIterator<Type>::Reset() {
	cur = (boundList->head) ? boundList->head->succ : nullptr;
	return true;
}
//************************************
// ȫ��:  LinkedListIterator::GetValue
// ����: ��õ�ǰ�ڵ��ֵ
// Ȩ��:    public
// ����:   bool
// ����: Type & result ����ֵ
//************************************
template<class Type> bool LinkedListIterator<Type>::GetValue(Type& result) {
	if (cur == nullptr)return false;
	result = cur->data;
	return true;
}
//************************************
// ȫ��:  LinkedListIterator::isNull
// ����: �жϵ�ǰ�������Ƿ�Ϊ��
// Ȩ��:    public
// ����:   bool
//************************************
template<class Type> bool LinkedListIterator<Type>::isNull() {
	return cur == nullptr;
}
//��ʽջ
//************************************
// ȫ��:  Stack::Empty
// ����: �ж�ջ��
// Ȩ��:    public
// ����:   bool
//************************************
template<class Type> bool Stack<Type>::Empty() {
	return linkedStack.Size() == 0;
}
//************************************
// ȫ��:  Stack::Push
// ����: ��ջ
// Ȩ��:    public
// ����:   bool
// ����: const Type & p ��ջԪ��
//************************************
template<class Type> bool Stack<Type>::Push(const Type& p) {
	return linkedStack.PushFront(p);
}
//************************************
// ȫ��:  Stack::Pop
// ����: ��ջ
// Ȩ��:    public
// ����:   bool
//************************************
template<class Type> bool Stack<Type>::Pop() {
	return linkedStack.PopFront();
}
//************************************
// ȫ��:  Stack::Top
// ����: ���ջ��Ԫ��
// Ȩ��:    public
// ����:   bool
// ����: Type & p
//************************************
template<class Type>bool Stack<Type>::Top(Type& p) {
	LinkedListIterator<Type> iter = linkedStack.GetIterator();
	return iter.GetValue(p);
}

//��ʽ����

//************************************
// ȫ��:  Queue::Empty
// ����: �ж϶��п�
// Ȩ��:    public
// ����:   bool
//************************************
template<class Type> bool Queue<Type>::Empty() {
	return linkedQueue.Size() == 0;
}
//************************************
// ȫ��:  Queue::Push
// ����: �����
// Ȩ��:    public
// ����:   bool
// ����: const Type & p
//************************************
template<class Type> bool Queue<Type>::Push(const Type& p) {
	return linkedQueue.PushBack(p);
}
//************************************
// ȫ��:  Queue::Pop
// ����: ������
// Ȩ��:    public
// ����:   bool
//************************************
template<class Type> bool Queue<Type>::Pop() {
	return linkedQueue.PopFront();
}
//************************************
// ȫ��:  Queue::Front
// ����: ��ö���Ԫ��
// Ȩ��:    public
// ����:   bool
// ����: Type & p ����ֵ
//************************************
template<class Type>bool Queue<Type>::Front(Type& p) {
	LinkedListIterator<Type> iter = linkedQueue.GetIterator();
	return iter.GetValue(p);
}
//��ϣ��
HashTable::HashTable() {
	HashList = new LinkedList<HashTableElement>[ModulusFactor];
}
HashTable::~HashTable() {
	if (HashList != nullptr) delete[] HashList;
}
//************************************
// ȫ��:  HashTable::GetKey
// ����: ����ַ�����Hash
// Ȩ��:    public
// ����:   int
// ����: std::string Dest
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
// ȫ��:  HashTable::Set
// ����: �����ϵ��
// Ȩ��:    public
// ����:   bool
// ����: std::string InsertString
// ����: int Index �����Ӧ����ֵ
//************************************
bool HashTable::Set(std::string InsertString, int Index) {
	int hashKey = GetKey(InsertString);
	HashList[hashKey].PushBack({ InsertString,Index });
	return true;
}
//************************************
// ȫ��:  HashTable::Get
// ����: �����ַ�������ù�ϵ�Ե���ֵ����
// Ȩ��:    public
// ����:   bool
// ����: std::string CompareString ���ڲ��ҵ��ַ���
// ����: int & Index ���ص����Ӧ����ֵ������Hash��
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

//�γ̰���ϵͳ
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
// ȫ��:  CourseArrangeSystem::ReadCourses
// ����: ��ȡ�γ���Ϣ
// Ȩ��:    public
// ����:   int
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
		std::cout << " Ĭ�������ļ��޷��򿪣�����ʹ���Զ���������ļ��������·������ļ���ַ��������������-1����" << std::endl;
		std::cout << " �ļ���ַ��";
		while (1) {
			std::getline(std::cin, customFile);
			readInFile = customFile;
			if (customFile == "-1") {
				std::cout << std::endl << "����Ϣ�������Ѿ����ֶ�������\n\n�ſ�����ֹ����������ſΣ��������������" << std::endl;

				return 2;
			}
			fin.open(customFile.c_str());
			if (!fin.fail())break;
			std::cout << std::endl;
			std::cout << " ���������ļ��޷��򿪣�����ʹ�����������ļ��������·������ļ���ַ��������������-1����" << std::endl;
			std::cout << " �ļ���ַ��";
		}

	}
	if (fout.fail()) {
		//std::cout << "�������ļ���������ļ�output.txt�޷����ʡ�\n\n�ſ�����ֹ����������ſΣ��������������" << std::endl;
		//return 2;
		std::string customFile;
		std::cout << std::endl << " Ĭ������ļ��޷��򿪣�����ʹ���Զ��������ļ��������·������ļ���ַ��������������-1����" << std::endl;
		std::cout << " �ļ���ַ��";
		while (1) {
			std::getline(std::cin, customFile);
			if (customFile == "-1") {
				std::cout << std::endl << "����Ϣ�������Ѿ����ֶ�������\n\n�ſ�����ֹ����������ſΣ��������������" << std::endl;
				return 2;
			}
			else if (customFile == readInFile) {
				std::cout << std::endl;
				std::cout << " �����ļ�Ϊ�����ļ��������������ſν�����������ʹ����������ļ��������·������ļ���ַ��������������-1����" << std::endl;
				std::cout << " �ļ���ַ��";
				continue;
			}
			fout.open(customFile.c_str());
			if (!fout.fail())break;
			std::cout << std::endl;
			std::cout << " ��������ļ��޷��򿪣�����ʹ����������ļ��������·������ļ���ַ��������������-1����" << std::endl;
			std::cout << " �ļ���ַ��";
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
		std::cout << "�������ļ������ڴ治�㡣\n\n�ſ�����ֹ����������ſΣ��뱣֤�����ڴ�����." << std::endl;
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
			std::cout << "�������ļ�����������Ŀγ���Ϣ�ļ��У���" << i + 1 << "�еĿγ̣��κŴ��ڳ�ͻ\n\n�ſ�����ֹ����������ſΣ������������ļ���������." << std::endl;
			return 6;
		}

	}
	if (incompleteLineFlag) {
		if (incompleteLineFlag == 1) {
			std::cout << "�������ļ�����������Ŀγ���Ϣ�ļ��У���" << incompleteLineFlag << "�У����ݲ��������ʽ����\n(�뱣֤�����ļ����ݲ�Ϊ��)��\n\n�ſ�����ֹ����������ſΣ������������ļ���������." << std::endl;
		}
		else {
			std::cout << "�������ļ�����������Ŀγ���Ϣ�ļ��У���" << incompleteLineFlag << "�У����ݲ��������ʽ����\n(������Ϊ��ĩ���У���ɾ����ĩ���лس�)��\n\n�ſ�����ֹ����������ſΣ������������ļ���������." << std::endl;
		}
		return 3;
	}
	if (invalidLenFlag) {
		std::cout << "�������ļ�����������Ŀγ���Ϣ�ļ��У���" << invalidLenFlag << "�У��γ̳��Ȳ��Ϸ���\n\n�ſ�����ֹ����������ſΣ������������ļ���������." << std::endl;
		return 4;
	}
	if (invalidSemFlag) {
		std::cout << "�������ļ�����������Ŀγ���Ϣ�ļ��У���" << invalidSemFlag << "�У�����ѧ�ڲ��Ϸ���\n\n�ſ�����ֹ����������ſΣ������������ļ���������." << std::endl;
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
				std::cout << "�������ļ�����������Ŀγ���Ϣ�ļ��У��γ�" << course[i].Identity << "�����޿�" << strBuffer << "�޷��ڿγ���Ϣ���ҵ���Ӧ��Ŀ��\n\n�ſ�����ֹ����������ſΣ������������ļ���������." << std::endl;

				delete[] relationPreq;
				delete[] relationSucc;

				return 4;
			}
			int iPreqTemp;
			if (preqHashList.Get(strBuffer, iPreqTemp)) {
				std::cout << "�������ļ�����������Ŀγ���Ϣ�ļ��У��γ�" << course[i].Identity << "�����޿���Ϣ�����ظ���ͬһ���޿γ���2�λ����ϣ���\n\n�ſ�����ֹ����������ſΣ������������ļ���������." << std::endl;

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
// ȫ��:  CourseArrangeSystem::CheckTopologicalAvailability
// ����:  ����ſο�����
// Ȩ��:    public
// ����:   int
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
// ȫ��:  CourseArrangeSystem::TopologicalSearch
// ����: �ſο�ʼ
// Ȩ��:    public
// ����:   int
//************************************
int CourseArrangeSystem::TopologicalSearch() {
	for (int i = 0; i < courseCount; i++) {//Ԥ�Ȱ���ѧ���Ѿ�ȷ���Ŀγ̣�����DFS�ݹ����
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
		std::cout << "�������ſΣ������α��޷���" << semesterCount << "ѧ���ڰ�����ϡ�\n\n �ſ���ֹ�����������ſΣ����޸Ŀγ���Ϣ��������ϵͳ��\n" << std::endl;
	}
	return a;
}
//************************************
// ȫ��:  CourseArrangeSystem::TopologicalSearch
// ����: ���γ̷��䵽ÿ��ѧ��
// Ȩ��:    public
// ����:   int
// ����: int semester ѧ��
// ����: int curCourse �ѷ���γ���
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
// ȫ��:  CourseArrangeSystem::DetailedDispatch
// ����: ��ÿѧ���ڷ���γ�
// Ȩ��:    public
// ����:   void
//************************************
void CourseArrangeSystem::DetailedDispatch() {
	CourseDispatchSolution *result = new CourseDispatchSolution[semesterCount + 1]; //���ڴ�ų�ʼ��
	int **occupied = new int*[semesterWeekdays]; //��i�죬��j�ڿ��Ƿ�ռ��
	int *getWeekday = new int[2 * semesterWeekdays + 1];//��һ�γ����ſε�����
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
					//���ȷ������ڿ�
					if (!occupied[getWeekday[k]][l] && course[curCourse].AvailLength >= 3 && semesterLessonsIntervalDuration[l] == 3) {
						occupied[getWeekday[k]][l] = 1;
						course[curCourse].AvailLength -= 3;

						result[i].AttachDispatchInfo(curCourse, getWeekday[k], semesterLessonsIntervalBegin[l], semesterLessonsIntervalBegin[l] + 2);
						sFlag = 1;
						break;
					}
					if (sFlag == 1)break;
					//�ٷ������ڿ�
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
		//���䵥�ڿΣ���֤�γ̲����������쿪��
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
		//�����䵥�ڿΣ�����֤�γ̲����������쿪��
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
// ȫ��:  CourseArrangeSystem::OutputSpacings
// ����: ����ո�
// Ȩ��:    public
// ����:   void
// ����: int x �ո���
//************************************
void CourseArrangeSystem::OutputSpacings(int x) {
	for (int i = 0; i < x; i++)fout << " ";
}


//************************************
// ȫ��:  CourseArrangeSystem::GetEvaluationValue
// ����: �����ſη�����������
// Ȩ��:    public
// ����:   long long
// ����: const OverallCourseDispatchSol & x
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
// ȫ��:  CourseArrangeSystem::GetRandomAdjacentSolution
// ����: ��õ�ǰ��������������
// Ȩ��:    public
// ����:   int
// ����: const OverallCourseDispatchSol & x ��ǰ��
// ����: OverallCourseDispatchSol & result �½ⷵ��ֵ
// ����: int extFunc
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
		//ɾ��ԭ��ѧ����Ϣ
		DispatchInfo t;
		for (LinkedListIterator<DispatchInfo> i = result.semesterPlan[orgSem].details[randCourseId].GetIterator(); !i.isNull(); i.GoNext()) {
			i.GetValue(t);
			for (int j = t.TimeBegin; j <= t.TimeEnd; j++) {
				result.semesterPlan[orgSem].courseTable[t.Weekday][j] = -1;
			}
		}
		while (result.semesterPlan[orgSem].details[randCourseId].Size())result.semesterPlan[orgSem].details[randCourseId].PopFront();

		//����ѧ�ڷ���˿γ�
		int *getWeekday = new int[2 * semesterWeekdays + 1];
		int disturbance = rand() % 5;
		for (int i = 0; i <= 2 * semesterWeekdays; i++) {
			getWeekday[i] = (i * 2 + disturbance) % semesterWeekdays;
		}
		int **occupied = new int*[semesterWeekdays]; //�������ѧ�ڵ�ռ��״̬
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
		//���ȷ������ڿκ����ڿ�

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
		//֮����䵥�ڿ�
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

		//���վ���������ͬһ���ԭ���������
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
		//��������
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
// ȫ��:  CourseArrangeSystem::SimulatedAnnealing
// ����: �Ż�
// Ȩ��:    public
// ����:   void
// ����: int GRASFunc
//************************************
void CourseArrangeSystem::SimulatedAnnealing(int GRASFunc) {
	long long Temperature = 2000000, TemperatureLBound = 100; //��ʼ�¶Ⱥ��¶����ޣ����ٶ����ȣ�����Ҫ��ϵͣ����Ե��ͳ�ʼ�¶ȡ�
	long long Diff;
	double CooldownRate = 0.996; //��ȴ�ٶȣ����ٶ����ȣ�����Ҫ��ϵͣ����Ե��ʹ���ֵ��
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
// ȫ��:  CourseArrangeSystem::Print
// ����: �����
// Ȩ��:    public
// ����:   void
// ����: OverallCourseDispatchSol p
//************************************
void CourseArrangeSystem::Print(OverallCourseDispatchSol p) {
	CourseDispatchSolution w;
	fout << "�������ָ�ʽ���ң���ر��ı��༭���ġ��Զ����С����ܡ�" << std::endl << std::endl;
	for (int i = 0; i < semesterCount; i++) {
		fout << "����" << i + 1 << "ѧ�ڡ�" << std::endl;
		for (int j = 0; j < semesterWeekdays; j++) {
			fout << "| <����" << j + 1 << ">";
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
					fout << "| (�޿γ�)";
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
// ȫ��:  CourseArrangeSystem::SetEachSemesterLimit
// ����: ����ÿһѧ�ڵĿγ�����
// Ȩ��:    public
// ����:   void
//************************************
void CourseArrangeSystem::SetEachSemesterLimit() {
	std::cout << " ����һ��������" << semesterCount << "��ѧ�ڣ�ÿ��ѧ�ڵĿ��������ÿո�ָ�����-1 ��ʾ���Դ�ѧ�����ƣ�" << std::endl;
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
					std::cout << std::endl << "��" << i + 1 << "ѧ�ڵĿγ�����Ч�������������������ݡ�";
					continue;
				}
				else {
					semesterCourseLimit[i] = std::stoi(intRead2);
					if (semesterCourseLimit[i] == -1)autoDispatchFlag = true;
				}
			}
			else {
				std::cout << std::endl << "��" << i + 1 << "ѧ�ڵĿ�ʱ��δ���롣�����������������ݡ�";
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
				std::cout << std::endl << " �����ſ���Ϣ�趨����"<<i+1<<"ѧ��������"<<tw<<"�ſγ�Ҫ���衣�����������������ݡ�"<<std::endl;
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
				std::cout << std::endl << " ÿѧ�������Ŀγ���֮����γ��������ȡ������������������ݡ�" << std::endl;
				continue;
			}
		}
		break;

	}

}
//**********������**************
#include <time.h>

void CASCall() {
	srand(time(NULL)); rand();
	CourseArrangeSystem CAS;
	std::cout << "********************************************" << std::endl << std::endl;
	std::cout << "\t��ӭʹ���ſ�ϵͳ!" << std::endl << std::endl;
	std::cout << "********************************************" << std::endl << std::endl;
	std::cout << " 1. �γ���Ϣ�ļ�ÿ�и�ʽ����:[�κ�] [�γ�����] [��ʱ��] [����ѧ��] ���޿�1�κ� ... ���޿�n�κ�" << std::endl;
	std::cout << "    (������������Ϊ��ѡ��)" << std::endl;
	std::cout << " 2. Ĭ�������ļ�Ϊinput.txt��Ĭ������ļ�Ϊoutput.txt�����ɷ���ʱ����������ָ�����������ļ���" << std::endl;
	std::cout << " 3. ����γ���Ϣ�ļ����п��У�������ĩ�Ļس�������ɾ�����к��������ϵͳ" << std::endl;
	std::cout << " 4. �ſΰ���" << CAS.semesterCount << "��ѧ�ڣ�ÿ��" << CAS.semesterLessonsPerDay << "��ʱ,һ���Ͽ�" << CAS.semesterWeekdays << "��Ϊ��׼�������ſ�" << std::endl;
	std::cout << " 5. �뱣֤�γ���Ϣ�����޹�ϵ�Ϸ�����ʱ���Ϳ���ѧ����Ϣ�Ϸ���" << std::endl;
	std::cout << std::endl << "********************************************" << std::endl << std::endl;
	int w;
	if (!CAS.ReadCourses()) {
		if (!(w = CAS.CheckTopologicalAvailability())) {
			std::cout << std::endl;
			CAS.SetEachSemesterLimit();
			std::cout << std::endl;
			std::cout << " �γ̰��ſ�ʼ..." << std::endl << std::endl;
			if (CAS.TopologicalSearch() != 0) {
				std::cout << " �����Ż��γ̰��ţ����Ժ�..." << std::endl << std::endl;
				CAS.SimulatedAnnealing();
				CAS.PrintBest();

				std::cout << " �γ̰����Ѿ���ɣ��γ̰��ŷ����Ѿ�������" << CAS.outputFileStr << "��" << std::endl << std::endl;
			}
		}
		else {
			switch (w) {
			case 1:
				std::cout << "�����󡿿γ���Ϣ�Ƿ����������ſγ̻�Ϊ���޿Ρ�" << std::endl << std::endl;
				break;
			case 2:
				std::cout << "�����󡿿γ���Ϣ�Ƿ����ڸ������޹�ϵ�Ϳ���ѧ���£����ڿγ��޷����а���" << std::endl << std::endl;
				break;
			case 3:
				std::cout << "�����󡿿γ���Ϣ�Ƿ������ڿγ̿�ʱ����������ѧ�ڿ�ʱ������" << std::endl << std::endl;
				break;
			}
			std::cout << "���޸Ŀγ���Ϣ�����������ſ�ϵͳ��" << std::endl << std::endl;

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
