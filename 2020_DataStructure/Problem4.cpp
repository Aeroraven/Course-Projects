#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

#define NumberType Fraction
#define ComplexNumType double

class Complex { //复数
public:
	ComplexNumType real, imag;
	Complex() :real(0), imag(0) {}
	Complex(ComplexNumType r, ComplexNumType i) :real(r), imag(i) {}
	Complex operator + (const Complex& p) const {
		return Complex(real + p.real, imag + p.imag);
	}
	Complex operator - (const Complex& p)const {
		return Complex(real - p.real, imag - p.imag);
	}
	Complex operator *(const Complex& p)const {
		return Complex(real*p.real - imag * p.imag, real*p.imag + imag * p.real);
	}
};

template<class Type> class LinkedListNode { //双向链表节点
public:
	Type data; //表达式内容
	LinkedListNode *pred = nullptr, *succ = nullptr; //链表前驱和后继
};
template<class Type> class LinkedList {
public:
	LinkedListNode<Type> *head = nullptr; //链表头部
	LinkedListNode<Type> *tail = nullptr; //链表尾部
	int listSize = 0; //链表中的元素个数
	LinkedList(); //构造空链表	
	~LinkedList(); //析构空链表
	void InsertTail(const Type& result); //在链表尾部插入
	void InsertFront(const Type& result);
	void GetTail(Type& result); //获取链表尾部数据
	void GetFront(Type& result);
	void DeleteTail(); //删除链表尾部数据
	void DeleteFront();
	int GetSize(); //获取链表大小
};
template<class Type> class Stack { //栈
public:
	LinkedList<Type> List;
	void Pop(); //弹出栈顶元素
	void Push(const Type& data); //在栈顶压入元素
	int GetSize(); //获取栈大小
	void GetTop(Type& result); //获取栈顶元素
	Type GetTop(); //获取栈顶元素
};
class BigInteger { //数值存储
public:
	typedef LinkedListNode<char> BIntDigit;

	bool negative = false, allocated = false;
	BIntDigit *digits = nullptr, *tail = nullptr;//数位链表的头尾结点指针
	int dSize = 0; //数位数量

	~BigInteger();
	BigInteger();
	BigInteger(const BigInteger& p);
	BigInteger(int p);

	const BigInteger& operator =(const BigInteger& p);

	void Print() const;
	void Demolition();
	void InsertTail(char digit);
	void InsertFront(char digit);
	void RemoveTail();
	void RemoveFront();

	BigInteger Add(const BigInteger& p)const; //绝对值加法
	BigInteger Subtract(const BigInteger &p)const; //绝对值减法
	BigInteger SingleMulti(char p)const; //绝对值乘法（1位数）[已经废弃]
	BigInteger Multiplication(const BigInteger &p)const; //绝对值乘法
	BigInteger IntegerDivision(const BigInteger &p)const; //绝对值整除
	BigInteger Modulus(const BigInteger& p)const; //绝对值取模
	BigInteger DecimalLeftMove(int x)const; //乘10
	BigInteger DecimalRightMove(int x)const;//除以10
	BigInteger BinRMoveOne()const; //除以2
	BigInteger FastPow(const BigInteger &p) const; //绝对值快速乘幂
	BigInteger AbsoluteCopy() const; //绝对值副本
	BigInteger Pow(const BigInteger &p) const; //乘幂运算

	void DecimalDivision(const BigInteger &p, BigInteger& intRet, BigInteger& decRet, int accuracy = 2)const; //小数除法

	void SelfSquare();
	void SelfAdd(const BigInteger& p);
	void SelfMulti(const BigInteger& x);

	bool isLargerThan(const BigInteger &p)const;
	bool isSmallerThan(const BigInteger &p)const;
	bool isEqual(const BigInteger &p)const;
	bool isLargerThanOrEqual(const BigInteger &p)const;
	bool isSmallerThanOrEqual(const BigInteger &p)const;

	bool isOdd() const;
	bool isZero() const;

	BigInteger operator -()const;
	BigInteger operator +()const;

	BigInteger operator + (const BigInteger& p)const;
	BigInteger operator - (const BigInteger& p)const;
	BigInteger operator * (const BigInteger& p)const;
	BigInteger operator / (const BigInteger& p)const;
	BigInteger operator % (const BigInteger& p)const;

	bool operator > (const BigInteger& p)const;
	bool operator < (const BigInteger& p)const;
	bool operator == (const BigInteger& p)const;
	bool operator != (const BigInteger& p)const;
	bool operator >= (const BigInteger& p)const;
	bool operator <= (const BigInteger& p)const;

	BigInteger& operator +=(const BigInteger& p);
	BigInteger& operator -=(const BigInteger& p);
	BigInteger& operator *=(const BigInteger& p);
	BigInteger& operator /=(const BigInteger& p);
	BigInteger& operator %=(const BigInteger& p);

	friend std::ostream& operator << (std::ostream& op, const BigInteger& x);
	void FastPrint();
};
class FastFourierTransformation { //FFT
public:
	const double PI = acos(-1.0);
	void transformation(Complex *polyItem, int length, int inverse); //变换过程
	BigInteger polynomialMulti(const BigInteger& a, const BigInteger& b); //多项式乘法
};
class Fraction { //分数储存
protected:
	BigInteger numerator, denominator;
	BigInteger Gcd(const BigInteger& x, const BigInteger& y)const;
public:
	friend BigInteger;
	~Fraction();
	Fraction();
	Fraction(const Fraction& p);
	Fraction(int x);

	void Reduction();
	Fraction operator -()const;
	Fraction operator +()const;

	Fraction operator + (const Fraction& p)const;
	Fraction operator - (const Fraction& p)const;
	Fraction operator * (const Fraction& p)const;
	Fraction operator / (const Fraction& p)const;
	Fraction operator % (const Fraction& p)const;

	bool operator > (const Fraction& p)const;
	bool operator < (const Fraction& p)const;
	bool operator == (const Fraction& p)const;
	bool operator != (const Fraction& p)const;
	bool operator >= (const Fraction& p)const;
	bool operator <= (const Fraction& p)const;

	Fraction& operator +=(const Fraction& p);
	Fraction& operator -=(const Fraction& p);
	Fraction& operator *=(const Fraction& p);
	Fraction& operator /=(const Fraction& p);
	Fraction& operator %=(const Fraction& p);

	friend std::ostream& operator << (std::ostream& op, const Fraction& x);
	Fraction Pow(const Fraction& p, int &stat);
	BigInteger FindRoot(const BigInteger& p, const BigInteger& q, int &stat);
	Fraction FindEstimatedRoot(const BigInteger &p, const BigInteger &q, int &stat);
	bool isInteger() { return denominator == 1; }
	void FastPrint(bool useDecimal = false, int decimalAccuracy = 2);
};
class ExpressionElement { //表达式元素
public:
	bool legalFlag = true;
	bool isOperator = false; //存储的内容是否是运算符
	NumberType number = NumberType(); //存储操作数
	char operatorType; //存储运算符
	ExpressionElement() :legalFlag(true), isOperator(false) {};
	ExpressionElement(char op) {
		isOperator = true;
		operatorType = op;
	}
	~ExpressionElement() {
		number.~NumberType();
	}
	ExpressionElement(const ExpressionElement &p) {
		this->legalFlag = p.legalFlag;
		this->isOperator = p.isOperator;
		if (p.isOperator) {
			this->operatorType = p.operatorType;
		}
		else {
			this->number = p.number;
		}
	}
	const ExpressionElement& operator =(const ExpressionElement &p) {
		this->legalFlag = p.legalFlag;
		this->isOperator = p.isOperator;
		if (p.isOperator) {
			this->operatorType = p.operatorType;
		}
		else {
			this->number = p.number;
		}
		return *this;
	}
};


class ExpressionCalculator { //计算器
private:
	void char2num(const char *data, int begin, int end, NumberType& result, int& stat); //将char字符串转为数字

public:
	void solve(const char *data); //求解表达式
	void mainLoop(); //循环
};


//Static

void BigInteger::InsertTail(char digit) {
	if (allocated) {
		BIntDigit *nEl = new BIntDigit;
		nEl->pred = tail;
		nEl->data = digit;
		tail->succ = nEl;
		tail = nEl;
		dSize++;
	}
}
void BigInteger::InsertFront(char digit) {
	if (allocated) {
		if (dSize) {
			BIntDigit *nEl = new BIntDigit;
			nEl->succ = digits->succ;
			nEl->pred = digits;
			nEl->data = digit;
			digits->succ->pred = nEl;
			digits->succ = nEl;
			dSize++;
		}
		else {
			BIntDigit *nEl = new BIntDigit;
			nEl->pred = digits;
			nEl->data = digit;
			digits->succ = nEl;
			tail = nEl;
			dSize++;
		}

	}
}
void BigInteger::RemoveTail() {
	if (allocated) {
		tail = tail->pred;
		delete tail->succ;
		tail->succ = nullptr;
		dSize--;
	}
}
void BigInteger::RemoveFront() {
	if (allocated) {
		if (dSize == 1) *this = 0;
		else {
			digits->succ = digits->succ->succ;
			delete digits->succ->pred;
			digits->succ->pred = digits;
			dSize--;
		}
	}
}
void BigInteger::Demolition() {
	BIntDigit *cur = digits, *curNext;
	if (allocated) {
		while (1) {
			curNext = cur->succ;
			delete cur;
			if (!curNext)break;
			cur = curNext;
		}
		allocated = false;
		dSize = 0;
	}
}
BigInteger::~BigInteger() {
	Demolition();
}
BigInteger::BigInteger() {
	if (allocated)Demolition();
	digits = new BIntDigit;
	digits->succ = new BIntDigit;
	digits->succ->pred = digits;
	digits->succ->data = 0;
	tail = digits->succ;
	dSize = 1;
	allocated = true;
	negative = false;
}

BigInteger::BigInteger(const BigInteger& p) {
	if (allocated)Demolition();
	digits = new BIntDigit;
	tail = digits;
	BIntDigit *nEl;
	for (BIntDigit *i = p.digits->succ; i != nullptr; i = i->succ) {
		nEl = new BIntDigit;
		nEl->pred = tail;
		nEl->data = i->data;
		tail->succ = nEl;
		tail = nEl;
	}
	dSize = p.dSize;
	allocated = true;
	negative = p.negative;
}
BigInteger::BigInteger(int p) {
	if (allocated)Demolition();
	if (p < 0)p = -p, negative = true;
	else negative = false;
	digits = new BIntDigit;
	allocated = true;
	tail = digits;
	if (p == 0) {
		InsertTail(0);
		return;
	}
	while (p) {
		InsertTail(p % 10);
		p /= 10;
	}
}
const BigInteger& BigInteger::operator =(const BigInteger& p) {
	if (allocated)Demolition();
	digits = new BIntDigit;
	tail = digits;
	BIntDigit *nEl;
	for (BIntDigit *i = p.digits->succ; i; i = i->succ) {
		nEl = new BIntDigit;
		nEl->pred = tail;
		nEl->data = i->data;
		tail->succ = nEl;
		tail = nEl;
	}
	dSize = p.dSize;
	allocated = true;
	negative = p.negative;
	return *this;
}

void BigInteger::Print()const {
	if (allocated) {
		if (negative)std::cout << "-";
		for (BIntDigit *i = tail; i != digits; i = i->pred) {
			std::cout << (int)i->data;
		}
	}
	std::cout << std::endl;
}
//运算操作
BigInteger BigInteger::Add(const BigInteger& p)const {
	BigInteger ret;
	ret.RemoveTail();
	BIntDigit *cur1 = this->digits->succ, *cur2 = p.digits->succ;
	char curDigit = 0;
	bool carry = false;
	while (cur1 != nullptr&&cur2 != nullptr) {
		curDigit = cur1->data + cur2->data + carry;
		carry = (curDigit >= 10);
		curDigit -= 10 * carry;
		ret.InsertTail(curDigit);
		cur1 = cur1->succ;
		cur2 = cur2->succ;
	}
	while (cur1 != nullptr) {
		curDigit = cur1->data + carry;
		carry = (curDigit >= 10);
		curDigit -= 10 * carry;
		ret.InsertTail(curDigit);
		cur1 = cur1->succ;
	}
	while (cur2 != nullptr) {
		curDigit = cur2->data + carry;
		carry = (curDigit >= 10);
		curDigit -= 10 * carry;
		ret.InsertTail(curDigit);
		cur2 = cur2->succ;
	}
	if (carry) ret.InsertTail(1);
	return ret;
}
void BigInteger::SelfAdd(const BigInteger& p) {
	BIntDigit *cur1 = this->digits->succ, *cur2 = p.digits->succ;
	char curDigit = 0, temp = 0;
	bool carry = false;
	while (cur1 != nullptr&&cur2 != nullptr) {
		cur1->data += cur2->data + carry;
		if (cur1->data >= 10) {
			carry = true;
			cur1->data -= 10;
		}
		else carry = false;
		cur1 = cur1->succ;
		cur2 = cur2->succ;
	}
	while (cur1 != nullptr) {
		cur1->data += carry;
		if (cur1->data >= 10) {
			carry = true;
			cur1->data -= 10;
		}
		else carry = false;
		cur1 = cur1->succ;
	}
	while (cur2 != nullptr) {
		temp = cur2->data + carry;
		if (temp >= 10) {
			carry = true;
			temp -= 10;
		}
		else carry = false;
		this->InsertTail(temp);
		cur2 = cur2->succ;
	}
	if (carry)this->InsertTail(1);
}
BigInteger BigInteger::Subtract(const BigInteger& p)const {
	BigInteger ret;
	ret.RemoveTail();
	BIntDigit *cur1 = this->digits->succ, *cur2 = p.digits->succ;
	char curDigit = 0;
	bool decomp = false;
	while (cur1 != nullptr&&cur2 != nullptr) {
		curDigit = cur1->data - cur2->data - (decomp );
		decomp = (curDigit < 0);
		if (decomp) curDigit += 10;
		ret.InsertTail(curDigit);
		cur1 = cur1->succ;
		cur2 = cur2->succ;
	}
	while (cur1 != nullptr) {
		curDigit = cur1->data - (decomp );
		decomp = (curDigit < 0);
		if (decomp) curDigit += 10;
		ret.InsertTail(curDigit);
		cur1 = cur1->succ;
	}
	while (ret.tail->data == 0 && ret.dSize > 1) ret.RemoveTail();
	return ret;
}
BigInteger BigInteger::SingleMulti(char p)const {
	BigInteger ret;
	ret.RemoveTail();
	BIntDigit *cur1 = this->digits->succ;
	char curDigit, carry = 0;
	while (cur1) {
		curDigit = cur1->data*p + carry;
		carry = (curDigit / 10);
		curDigit %= 10;
		ret.InsertTail(curDigit);
		cur1 = cur1->succ;
	}
	if (carry) ret.InsertTail(carry);
	return ret;
}
BigInteger BigInteger::DecimalLeftMove(int x)const {
	if (x == 0)return *this;
	BigInteger ret;
	ret = *this;
	while (x-- && !ret.isZero())ret.InsertFront(0);
	return ret;
}
BigInteger BigInteger::DecimalRightMove(int x)const {
	if (x == 0)return *this;
	BigInteger ret;
	ret = *this;
	while (x--)ret.RemoveFront();
	return ret;
}
BigInteger BigInteger::Multiplication(const BigInteger &p)const {
	//点值乘法
	FastFourierTransformation fft;
	return fft.polynomialMulti(*this, p);

	//系数乘法
	BigInteger ret;
	BIntDigit *cur1 = p.digits->succ;
	register int dg = 0;
	while (cur1) {
		ret = ret.Add(SingleMulti(cur1->data).DecimalLeftMove(dg++));
		cur1 = cur1->succ;
	}
	return ret;
}
void BigInteger::SelfSquare() {
	BigInteger org = *this, ret; *this = 0;
	BIntDigit *cur2 = org.digits->succ, *cur1;
	register int dg = 0;
	char curDigit, carry = 0;
	while (cur2) {
		char p = cur2->data;
		ret = 0;
		ret.RemoveTail();
		cur1 = org.digits->succ;
		carry = 0;
		while (cur1) {
			curDigit = cur1->data*p + carry;
			carry = (curDigit / 10);
			curDigit %= 10;
			ret.InsertTail(curDigit);
			cur1 = cur1->succ;
		}
		if (carry) ret.InsertTail(carry);
		SelfAdd(ret.DecimalLeftMove(dg++));
		cur2 = cur2->succ;
	}
}
void BigInteger::SelfMulti(const BigInteger& x) {
	BigInteger org = *this, ret; *this = 0;
	BIntDigit *cur2 = org.digits->succ, *cur1;
	register int dg = 0;
	char curDigit, carry = 0;
	while (cur2) {
		char p = cur2->data;
		ret = 0;
		ret.RemoveTail();
		cur1 = x.digits->succ;
		carry = 0;
		while (cur1) {
			curDigit = cur1->data*p + carry;
			carry = (curDigit / 10);
			curDigit %= 10;
			ret.InsertTail(curDigit);
			cur1 = cur1->succ;
		}
		if (carry) ret.InsertTail(carry);
		SelfAdd(ret.DecimalLeftMove(dg++));
		cur2 = cur2->succ;
	}
}
bool BigInteger::isLargerThan(const BigInteger &p)const {
	if (dSize > p.dSize)return true;
	else if (dSize < p.dSize)return false;
	else {
		BIntDigit *cur1 = tail, *cur2 = p.tail;
		while (cur1 != digits && cur2 != p.digits) {
			if (cur1->data > cur2->data)return true;
			else if (cur1->data < cur2->data) return false;
			cur1 = cur1->pred;
			cur2 = cur2->pred;
		}
	}
	return false;
}
bool BigInteger::isSmallerThan(const BigInteger &p) const {
	if (dSize > p.dSize)return false;
	else if (dSize < p.dSize)return true;
	else {
		BIntDigit *cur1 = tail, *cur2 = p.tail;
		while (cur1 != digits && cur2 != p.digits) {
			if (cur1->data > cur2->data)return false;
			else if (cur1->data < cur2->data) return true;
			cur1 = cur1->pred;
			cur2 = cur2->pred;
		}
	}
	return false;
}
bool BigInteger::isEqual(const BigInteger &p)const {
	if (dSize > p.dSize)return false;
	else if (dSize < p.dSize)return false;
	else {
		BIntDigit *cur1 = tail, *cur2 = p.tail;
		while (cur1 != digits && cur2 != p.digits) {
			if (cur1->data > cur2->data)return false;
			else if (cur1->data < cur2->data) return false;
			cur1 = cur1->pred;
			cur2 = cur2->pred;
		}
	}
	return true;
}

bool BigInteger::isLargerThanOrEqual(const BigInteger &p)const {
	if (dSize > p.dSize)return true;
	else if (dSize < p.dSize)return false;
	else {
		BIntDigit *cur1 = tail, *cur2 = p.tail;
		while (cur1 != digits && cur2 != p.digits) {
			if (cur1->data > cur2->data)return true;
			else if (cur1->data < cur2->data) return false;
			cur1 = cur1->pred;
			cur2 = cur2->pred;
		}
	}
	return true;
}
bool BigInteger::isSmallerThanOrEqual(const BigInteger &p) const {
	if (dSize > p.dSize)return false;
	else if (dSize < p.dSize)return true;
	else {
		BIntDigit *cur1 = tail, *cur2 = p.tail;
		while (cur1 != digits && cur2 != p.digits) {
			if (cur1->data > cur2->data)return false;
			else if (cur1->data < cur2->data) return true;
			cur1 = cur1->pred;
			cur2 = cur2->pred;
		}
	}
	return true;
}
BigInteger BigInteger::IntegerDivision(const BigInteger &p)const {
	BigInteger ret, divisor = p, dividend = *this;
	ret.RemoveTail();
	int qSize = (dSize - p.dSize > 0) ? (dSize - p.dSize) : 0;
	char cur = 0;
	divisor = divisor.DecimalLeftMove(qSize);
	while (qSize >= 0) {
		cur = 0;
		while (dividend.isLargerThanOrEqual(divisor)) {
			dividend = dividend.Subtract(divisor);
			cur++;
		}
		divisor = divisor.DecimalRightMove(1);
		ret.InsertFront(cur);
		qSize--;
	}
	while (!ret.tail->data  && ret.dSize > 1) ret.RemoveTail();
	return ret;
}
void BigInteger::DecimalDivision(const BigInteger &p, BigInteger &intRet, BigInteger &decRet, int accuracy)const {
	BigInteger ret, divisor = p, dividend = *this;
	ret.RemoveTail();
	int qSize = (dSize - p.dSize > 0) ? (dSize - p.dSize) : 0;
	bool isValid = false;
	char cur = 0;
	divisor = divisor.DecimalLeftMove(qSize);
	while (qSize >= 0) {
		cur = 0;
		while (dividend.isLargerThanOrEqual(divisor)) {
			dividend = dividend.Subtract(divisor);
			cur++;
		}
		divisor = divisor.DecimalRightMove(1);
		ret.InsertFront(cur);
		qSize--;
	}
	while (!ret.tail->data  && ret.dSize > 1) ret.RemoveTail();
	intRet = ret;
	ret = 0;
	ret.RemoveTail();
	divisor = p;
	for (int i = 1; i <= accuracy; i++) {
		if (dividend.isZero() == false)dividend.InsertFront(0);
		else break;

		cur = 0;
		while (dividend.isLargerThanOrEqual(divisor)) {
			dividend = dividend.Subtract(divisor);
			cur++;
		}
		ret.InsertFront(cur);
		if (cur)isValid = true;
		if (!isValid)i--;
	}
	decRet = ret;
}
BigInteger BigInteger::BinRMoveOne()const {
	BigInteger ret, dividend = *this;
	ret.RemoveTail();
	char remain = 0;
	BIntDigit *cur = dividend.tail;
	while (cur != dividend.digits) {
		remain += cur->data;
		ret.InsertFront(remain >> 1);
		remain = (remain & 1) * 10;
		cur = cur->pred;
	}
	while (!ret.tail->data  && ret.dSize > 1) ret.RemoveTail();
	return ret;
}
BigInteger BigInteger::Modulus(const BigInteger &p) const {
	BigInteger ret, divisor = p, dividend = *this;
	ret.RemoveTail();
	int qSize = (dSize - p.dSize > 0) ? (dSize - p.dSize) : 0;
	char cur = 0;
	divisor = divisor.DecimalLeftMove(qSize);
	while (qSize >= 0) {
		cur = 0;
		while (dividend.isLargerThanOrEqual(divisor)) {
			dividend = dividend.Subtract(divisor);
			cur++;
		}
		divisor = divisor.DecimalRightMove(1);
		ret.InsertFront(cur);
		qSize--;
	}
	while (1) {
		if (ret.tail->data == 0 && ret.dSize > 1) {
			ret.RemoveTail();
		}
		else {
			break;
		}
	}
	return dividend;
}
bool BigInteger::isOdd()const {
	if (allocated) {
		return (digits->succ->data & 1);
	}
	return false;
}
bool BigInteger::isZero()const {
	if (allocated) {
		return (!digits->succ->data  && dSize == 1);
	}
	return false;
}
BigInteger BigInteger::FastPow(const BigInteger &p) const {
	BigInteger power = p, base = *this, result = 1;
	FastFourierTransformation fft;
	while (power.digits->succ->data || power.dSize != 1) {
		if (power.digits->succ->data & 1)result = fft.polynomialMulti(result, base);
		power = power.BinRMoveOne();
		base = fft.polynomialMulti(base, base);
	}
	return result;
}
//运算定义
BigInteger BigInteger::operator +(const BigInteger& p)const {
	BigInteger ret;
	if (!negative && !p.negative) {
		ret = (*this).Add(p);
	}
	else if (negative&&p.negative) {
		ret = (*this).Add(p);
		ret.negative = true;
	}
	else if (negative && !p.negative) {
		if (isLargerThan(p)) {
			ret = Subtract(p);
			ret.negative = true;
		}
		else {
			ret = p.Subtract(*this);
			ret.negative = false;
		}
	}
	else if (!negative && p.negative) {
		if (isLargerThan(p)) {
			ret = Subtract(p);
			ret.negative = false;
		}
		else {
			ret = p.Subtract(*this);
			ret.negative = true;
		}
	}
	if (ret.isZero()) {
		ret.negative = false;
	}
	return ret;
}
BigInteger BigInteger::operator +()const {
	return *this;
}
BigInteger BigInteger::operator -()const {
	BigInteger ret;
	ret = *this;
	ret.negative = !ret.negative;
	if (ret.isZero())ret.negative = false;
	return ret;
}
BigInteger BigInteger::operator -(const BigInteger& p)const {
	return (*this) + (-p);
}

BigInteger BigInteger::operator *(const BigInteger& p)const {
	BigInteger ret;
	ret = Multiplication(p);
	ret.negative = (negative != p.negative);
	if (ret.isZero()) ret.negative = false;
	return ret;
}
BigInteger BigInteger::operator /(const BigInteger& p)const {
	BigInteger ret;
	ret = IntegerDivision(p);
	ret.negative = (negative != p.negative);
	if (ret.isZero()) ret.negative = false;
	return ret;
}
BigInteger BigInteger::operator%(const BigInteger& x)const {
	return (*this) - ((*this) / x)*x;
}
bool BigInteger::operator>(const BigInteger& x)const {
	if (!negative && !x.negative) return isLargerThan(x);
	if (negative&&x.negative) return isSmallerThan(x);
	if (!negative && x.negative) return true;
	if (negative && !x.negative) return false;
	return true;
}
bool BigInteger::operator<(const BigInteger& x)const {
	if (!negative && !x.negative) return isSmallerThan(x);
	if (negative&&x.negative) return isLargerThan(x);
	if (!negative && x.negative) return false;
	if (negative && !x.negative) return true;
	return true;
}
bool BigInteger::operator==(const BigInteger& x)const {
	if (negative != x.negative)return false;
	return isEqual(x);
}
bool BigInteger::operator>=(const BigInteger& x)const {
	return ((*this) > x) || ((*this) == x);
}
bool BigInteger::operator<=(const BigInteger& x)const {
	return ((*this) < x) || ((*this) == x);
}
bool BigInteger::operator!=(const BigInteger& x)const {
	return !((*this) == x);
}
BigInteger& BigInteger::operator+=(const BigInteger& x) {
	*this = *this + x; return *this;
}
BigInteger& BigInteger::operator-=(const BigInteger& x) {
	*this = *this - x; return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger& x) {
	*this = *this * x; return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger& x) {
	*this = *this / x; return *this;
}
BigInteger& BigInteger::operator%=(const BigInteger& x) {
	*this = *this % x; return *this;
}
std::ostream& operator << (std::ostream& op, const BigInteger& x) {
	if (x.negative)op << "-";
	for (BigInteger::BIntDigit *i = x.tail; i != x.digits; i = i->pred) {
		op << (int)i->data;
	}
	return op;
}
void BigInteger::FastPrint() {
	if (negative)printf("%c", '-');
	for (BIntDigit *i = tail; i != digits; i = i->pred) {
		printf("%d", i->data);
	}
}
BigInteger BigInteger::Pow(const BigInteger &p) const {
	BigInteger ret;
	ret = FastPow(p);
	if (p > 0) {
		ret.negative = (negative&&p.isOdd());
	}
	else if (p < 0) {
		ret = BigInteger(1) / ret;
	}
	return ret;
}
BigInteger BigInteger::AbsoluteCopy()const {
	BigInteger ret = *this;
	ret.negative = false;
	return ret;
}
//分数类开始
BigInteger Fraction::Gcd(const BigInteger& x, const BigInteger& y)const {
	BigInteger a = x, b = y, temp;
	while (!b.isZero()) {
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}
Fraction::~Fraction() {
	numerator.~BigInteger();
	denominator.~BigInteger();
}
Fraction::Fraction(const Fraction&p) {
	numerator = p.numerator;
	denominator = p.denominator;
}
Fraction::Fraction(int x) {
	numerator = x;
	denominator = 1;
}
Fraction::Fraction() {
	numerator = 0;
	denominator = 1;
}
void Fraction::Reduction() {
	BigInteger gcd = Gcd(numerator.AbsoluteCopy(), denominator.AbsoluteCopy());
	numerator = numerator / gcd;
	denominator = denominator / gcd;
	if (numerator.negative^denominator.negative) {
		numerator.negative = true;
		denominator.negative = false;
	}
	else {
		numerator.negative = false;
		denominator.negative = false;
	}
}
//分数运算符开始
Fraction Fraction::operator-()const {
	Fraction ret = *this;
	ret.numerator = -ret.numerator;
	return ret;
}
Fraction Fraction::operator+()const {
	return *this;
}
Fraction Fraction::operator+(const Fraction& p)const {
	Fraction ret;
	ret.denominator = denominator * p.denominator;
	ret.numerator = numerator * p.denominator + p.numerator*denominator;
	ret.Reduction();
	return ret;
}
Fraction Fraction::operator-(const Fraction& p)const {
	return (*this) + (-p);
}
Fraction Fraction::operator*(const Fraction& p)const {
	Fraction ret;
	ret.denominator = denominator * p.denominator;
	ret.numerator = numerator * p.numerator;
	ret.Reduction();
	return ret;
}
Fraction Fraction::operator/(const Fraction& p)const {
	Fraction ret;
	ret.denominator = denominator * p.numerator;
	ret.numerator = numerator * p.denominator;
	ret.Reduction();
	return ret;
}
Fraction Fraction::operator%(const Fraction& p)const {
	Fraction ret;
	ret.denominator = 1;
	ret.numerator = numerator % p.numerator;
	

	return ret;
}
bool Fraction::operator>(const Fraction& p)const {
	Fraction tmp = (*this) - p;
	return (tmp.numerator > 0);
}
bool Fraction::operator<(const Fraction& p)const {
	Fraction tmp = p - (*this);
	return (tmp.numerator > 0);
}
bool Fraction::operator==(const Fraction& p)const {
	Fraction tmp = p - (*this);
	return (tmp.numerator == 0);
}
bool Fraction::operator!=(const Fraction& p)const {
	Fraction tmp = p - (*this);
	return (tmp.numerator != 0);
}
bool Fraction::operator<=(const Fraction& p)const {
	Fraction tmp = p - (*this);
	return (tmp.numerator >= 0);
}
bool Fraction::operator>=(const Fraction& p)const {
	Fraction tmp = (*this) - p;
	return (tmp.numerator >= 0);
}
Fraction& Fraction::operator+=(const Fraction& x) {
	*this = *this + x; return *this;
}
Fraction& Fraction::operator-=(const Fraction& x) {
	*this = *this - x; return *this;
}
Fraction& Fraction::operator*=(const Fraction& x) {
	*this = *this * x; return *this;
}
Fraction& Fraction::operator/=(const Fraction& x) {
	*this = *this / x; return *this;
}
Fraction& Fraction::operator%=(const Fraction& x) {
	*this = *this % x; return *this;
}
std::ostream& operator << (std::ostream& op, const Fraction& x) {
	op << x.numerator;
	if (x.denominator != 1) {
		op << "/" << x.denominator;
	}
	return op;
}
BigInteger Fraction::FindRoot(const BigInteger& p, const BigInteger&q, int &stat) { //寻找精确根
	stat = 1;
	BigInteger L = 0, R = p.AbsoluteCopy(), mid = 0, V, Q = q.AbsoluteCopy(), P = p.AbsoluteCopy();
	while (L <= R) {
		mid = L;
		mid.SelfAdd(R);
		mid = mid.BinRMoveOne();
		V = mid.FastPow(Q);
		if (P > V)L = mid + 1;
		else if (P < V)R = mid - 1;
		else {
			if (q.isOdd() == true && p.negative == true) {
				if (p == -V)return -mid;
				else {
					stat = 0;
					return 0;
				}
			}
			else if (q.isOdd() == false && p.negative == true) {
				stat = 0;
				return 0;
			}
			else {
				return mid;
			}
		}
	}
	stat = 0;
	return 0;
}
Fraction Fraction::FindEstimatedRoot(const BigInteger& p, const BigInteger&q, int &stat) { //无理根的近似
	stat = 1;
	if (p.negative&&q.isOdd() == false) {
		stat = 0;
		return 0;
	}
	Fraction L(0), R, Mid, MidRes, CompareThreshold, Diff, P;
	//设定精度阈值
	CompareThreshold.numerator = 1;
	CompareThreshold.denominator = 100000000;
	//开始二分查找
	R.numerator = p.AbsoluteCopy();
	R.denominator = 1;
	P.denominator = 1;
	P.numerator = p;
	while (L <= R) {
		Mid = (L + R) / 2;
		MidRes.denominator = Mid.denominator.FastPow(q);
		MidRes.numerator = Mid.numerator.FastPow(q);
		Diff = MidRes - P;
		if (Diff > CompareThreshold) {
			R = Mid;
		}
		else if (Diff < -CompareThreshold) {
			L = Mid;
		}
		else {
			return Mid;
		}
	}
	stat = 0;
	return 0;
}
Fraction Fraction::Pow(const Fraction& p, int &stat) {
	Fraction ret;
	BigInteger m = p.numerator.AbsoluteCopy(), n = p.denominator;
	bool isNegative = p.numerator.negative;
	ret.numerator = numerator.Pow(m);
	ret.denominator = denominator.Pow(m);
	int numRootStat, denRootStat;
	BigInteger numRoot, denRoot;
	if (n != 1) {
		numRoot = FindRoot(ret.numerator, n, numRootStat);
		denRoot = FindRoot(ret.denominator, n, denRootStat);
	}
	else {
		numRootStat = 1;
		denRootStat = 1;
		numRoot = ret.numerator;
		denRoot = ret.denominator;
	}
	if (numRootStat&&denRootStat) {//如果可以查找到精确根则返回精确值
		stat = 1;
		ret.numerator = numRoot;
		ret.denominator = denRoot;
		if (isNegative == true && ret.numerator != 0) {
			ret.numerator = denRoot;
			ret.denominator = numRoot;
		}
		return ret;
	}
	else {//否则继续查找估计值
		Fraction numEstRoot, denEstRoot, result;
		numEstRoot = FindEstimatedRoot(ret.numerator, n, numRootStat);
		denEstRoot = FindEstimatedRoot(ret.denominator, n, denRootStat);
		if (numRootStat&&denRootStat) {
			result = numEstRoot / denEstRoot;
			if (isNegative) {
				result = Fraction(1) / result;
			}
			if ((ret.numerator.negative == true || ret.denominator.negative == true) && n.isOdd() == true) {
				result = -result;
			}
			stat = 2;
			return result;
		}
	}
	stat = 0;
	return 0;
}
void Fraction::FastPrint(bool useDecimal, int decimalAccuracy) {
	if (!useDecimal) {
		numerator.FastPrint();
		if (denominator != 1)printf("%c", '/'), denominator.FastPrint();
	}
	else {
		BigInteger intr, decr;
		numerator.DecimalDivision(denominator, intr, decr, decimalAccuracy);
		if (numerator.negative) {
			printf("%c", '-');
		}
		intr.FastPrint();
		printf("%c", '.');
		decr.FastPrint();
	}
}
//FFT 定义
void FastFourierTransformation::transformation(Complex *polyItem, int length, int inverse) {
	if (length == 1)return;
	Complex *aItem = new Complex[length >> 1], *bItem = new Complex[length >> 1];
	for (int i = 0; i < length; i += 2)aItem[i >> 1] = polyItem[i], bItem[i >> 1] = polyItem[i + 1];
	transformation(aItem, length >> 1, inverse);
	transformation(bItem, length >> 1, inverse);
	Complex unitRoot = { cos(2.0*PI / (double)length),(double)(inverse)*sin(2.0*PI / (double)length) };
	Complex base = { 1.0,0.0 };
	length >>= 1;
	for (int i = 0; i < length; base = base * unitRoot, i++) {
		polyItem[i] = aItem[i] + base * bItem[i];
		polyItem[i + length] = aItem[i] - base * bItem[i];
	}
	delete[] aItem;
	delete[] bItem;
}
BigInteger FastFourierTransformation::polynomialMulti(const BigInteger& a, const BigInteger& b) {
	BigInteger ret; ret.RemoveTail();
	Complex *polyA, *polyB;
	int arrayLen = 1;
	//链表转数组
	while (arrayLen < a.dSize + b.dSize)arrayLen <<= 1;
	polyA = new Complex[arrayLen];
	polyB = new Complex[arrayLen];
	int cur = 0;
	for (int i = 0; i < arrayLen; i++) {
		polyA[i].real = 0;
		polyA[i].imag = 0;
		polyB[i].real = 0;
		polyB[i].imag = 0;
	}
	for (BigInteger::BIntDigit* i = a.digits->succ; i != nullptr; i = i->succ, cur++) {
		polyA[cur].real = (ComplexNumType)(i->data);
		polyA[cur].imag = 0;
	}
	cur = 0;
	for (BigInteger::BIntDigit* i = b.digits->succ; i != nullptr; i = i->succ, cur++) {
		polyB[cur].real = (ComplexNumType)(i->data);
		polyB[cur].imag = 0;
	}
	//DFT
	transformation(polyA, arrayLen, 1);
	transformation(polyB, arrayLen, 1);
	//点值乘法
	for (int i = 0; i < arrayLen; i++) {
		polyA[i] = polyA[i] * polyB[i];
	}
	//IDFT
	transformation(polyA, arrayLen, -1);
	//处理进位
	int *resultTemp = new int[arrayLen];
	int carry = 0;
	for (int i = 0; i < arrayLen; i++) {
		resultTemp[i] = (int)((double)(polyA[i].real / arrayLen + 0.5)) + carry;
		if (resultTemp[i] >= 10) {
			carry = resultTemp[i] / 10;
			resultTemp[i] %= 10;
		}
		else {
			carry = 0;
		}
		ret.InsertTail((char)resultTemp[i]);
	}
	delete[]resultTemp;
	delete[]polyA;
	delete[]polyB;
	if (carry)ret.InsertTail(carry);
	while (!ret.tail->data  && ret.dSize > 1) ret.RemoveTail();
	return ret;
}
//链表开始
template<class Type> LinkedList<Type>::LinkedList() {
	head = new LinkedListNode<Type>;
	tail = head;
	listSize = 0;
}
template<class Type> void LinkedList<Type>::InsertTail(const Type& result) {
	LinkedListNode<Type> *newElement = new LinkedListNode<Type>; // [Warning]
	if (newElement != nullptr) {
		newElement->data = result;
		newElement->pred = tail;
		newElement->succ = nullptr;
		tail->succ = newElement;
		tail = newElement;
		listSize++;
	}
}
template<class Type> void LinkedList<Type>::InsertFront(const Type& result) {
	LinkedListNode<Type> *newElement = new LinkedListNode<Type>; // [Warning]
	newElement->data = result;
	newElement->succ = head->succ;
	newElement->pred = head;
	head->succ = newElement;
	if (!listSize)tail = newElement;
	listSize++;
}
template<class Type> void LinkedList<Type>::GetTail(Type& result) {
	if (listSize) {
		result = tail->data;
	}
}
template<class Type> void LinkedList<Type>::GetFront(Type& result) {
	if (listSize) {
		result = head->succ->data;
	}
}
template<class Type> void LinkedList<Type>::DeleteTail() {
	if (listSize) {
		LinkedListNode<Type> *temp = tail->pred;
		delete tail;
		tail = temp;
		temp->succ = nullptr;
		listSize--;
	}
}
template<class Type> void LinkedList<Type>::DeleteFront() {
	if (listSize) {
		LinkedListNode<Type> *temp = head->succ;
		head->succ = head->succ->succ;
		if (head->succ != nullptr) {
			head->succ->pred = head;
		}
		delete temp;
		listSize--;
	}
}
//************************************
// 全名:  LinkedList::GetSize
// 功能: 
// 权限:    public 
// 返回:   int
//************************************
template<class Type> int LinkedList<Type>::GetSize() {
	return listSize;
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

//栈
//************************************
// 全名:  Stack::Pop
// 功能:  出栈，但不返回值
// 权限:    public 
// 返回:   void
//************************************
template<class Type> void Stack<Type>::Pop() {
	if (List.GetSize()) {
		List.DeleteFront();
	}
}
//************************************
// 全名:  Stack::Push
// 功能: 入栈
// 权限:    public 
// 返回:   void
// 参数: const Type & data 要入栈的元素
//************************************
template<class Type> void Stack<Type>::Push(const Type& data) {
	List.InsertFront(data);
}
//************************************
// 全名:  Stack::GetTop
// 功能: 获取栈顶元素，栈空不操作
// 权限:    public 
// 返回:   void
// 参数: Type & result 栈顶元素返回
//************************************
template<class Type> void Stack<Type>::GetTop(Type& result) {
	List.GetFront(result);
}
//************************************
// 全名:  Stack::GetTop
// 功能: 获取栈顶元素
// 权限:    public 
// 返回:   Type 栈顶元素值
//************************************
template<class Type> Type Stack<Type>::GetTop() {
	Type ret;
	List.GetFront(ret);
	return ret;
}
//************************************
// 全名:  Stack::GetSize
// 功能: 获取栈大小
// 权限:    public 
// 返回:   int
//************************************
template<class Type> int Stack<Type>::GetSize() {
	return List.GetSize();
}
//算术表达式
//************************************
// 全名:  ExpressionCalculator::char2num
// 功能: 表达式计算器，字符串转数字
// 权限:    private 
// 返回:   void
// 参数: const char * data 源字符串
// 参数: int begin 字符串起始位置
// 参数: int end 字符串终止位置（包含)
// 参数: NumberType & result 返回结果
// 参数: int & stat 成功状态
//************************************
void ExpressionCalculator::char2num(const char *data, int begin, int end, NumberType& result, int& stat) {
	NumberType integerPart = 0, decimalPart = 0, decimalCounter = 1;
	int frontOperator = 0, illegalFlag = 0, curPart = 0;
	stat = 0;
	for (int i = begin; i <= end; i++) {
		if (data[i] == '+') {
			if (i != begin)illegalFlag = 1; //单目运算符不在数字首位，返回错误1
			if (frontOperator == 0)frontOperator = 1;
			else illegalFlag = 1;
		}
		else if (data[i] == '-') {
			if (i != begin)illegalFlag = 1;//单目运算符不在数字首位，返回错误1
			else if (frontOperator == 0)frontOperator = 2;
			else illegalFlag = 1;
		}
		else if (data[i] == '.') {
			if (curPart == 1) {
				illegalFlag = 2; //出现2个小数点，返回错误2
			}
			else {
				if (i == begin) {
					illegalFlag = 3; //在数字首端出现小数点，返回错误3
				}
				else if (i == begin + 1 && data[begin] == '+') {
					illegalFlag = 3; //在单目运算符后出现小数点，返回错误3
				}
				else if (i == begin + 1 && data[begin] == '-') {
					illegalFlag = 3; //在单目运算符后出现小数点，返回错误3
				}
				else {
					curPart = 1; //进入小数读取
				}
			}
		}
		else if (data[i] >= '0'&&data[i] <= '9') {
			if (curPart == 0) {
				integerPart *= 10;
				integerPart += (data[i] - '0');
			}
			else {
				decimalPart *= 10;
				decimalPart += (data[i] - '0');
				decimalCounter *= 10;
			}
		}
		else {
			illegalFlag = 4; //出现非法字符，返回错误4
		}
		if (illegalFlag) {
			stat = illegalFlag;
			return;
		}
	}
	result = integerPart + decimalPart / decimalCounter;
	if (frontOperator == 2)result = -result;
}
//************************************
// 全名:  ExpressionCalculator::solve
// 功能: 表达式计算器，求解主过程
// 权限:    public 
// 返回:   void
// 参数: const char * data 用于计算的表达式
//************************************
void ExpressionCalculator::solve(const char *data) {
	LinkedList<ExpressionElement> expItem;
	ExpressionElement insertTemp;
	NumberType expTemp;
	int length = strlen(data);
	int lastType = 0; //1-数字,2-左括号,3-右括号,4-运算符,5-单目运算符
	int lastType2 = 2; //1-加减，2-其他
	int curBegin = 0, curEnd = 0, stat, lbracket = 0;
	bool warning_IrrationalNum = false; //无理数提示
	//检测空串
	if (!length) {
		std::cout << "输入不合法: 输入为空" << std::endl;
		return;
	}
	//检测括号匹配
	for (int i = 0; i < length; i++) {
		if (data[i] == '(') lbracket++;
		else if (data[i] == ')') {
			if (lbracket)lbracket--;
			else {
				std::cout << "输入不合法: 括号不匹配" << std::endl;
				return;
			}
		}
	}
	if (lbracket) {
		std::cout << "输入不合法: 括号不匹配" << std::endl;
		return;
	}
	//检测运算符顺序，转换表达式
	for (int i = 0; i < length; i++) {
		if (data[i] >= '0'&&data[i] <= '9') {
			if (lastType == 1 || lastType == 5) {
				//if (lastType == 1) {
				curEnd++;
			}
			else {
				curBegin = i;
				curEnd = i;
			}
			lastType = 1;
		}
		else if (data[i] == '.') {
			if (lastType == 1) {
				curEnd++;
			}
			else {
				std::cout << "输入不合法: 小数点位置有误" << std::endl;
				return;
			}
			if (i < length - 1) {
				if (data[i + 1]<'0' || data[i + 1]>'9') {
					std::cout << "输入不合法: 小数点后应该跟随数字" << std::endl;
					return;
				}
			}
			if (i == length - 1) {
				std::cout << "输入不合法: 小数点后应该跟随数字,而不是将小数点放于表达式末尾" << std::endl;
				return;
			}
		}
		else if (data[i] == '(') {
			if (lastType == 1) {
				char2num(data, curBegin, curEnd, expTemp, stat);
				if (stat) {
					std::cout << "输入不合法: 字符输入有误 5" << std::endl;
					return;
				}
				insertTemp.isOperator = false;
				insertTemp.number = expTemp;
				insertTemp.legalFlag = true;
				expItem.InsertTail(insertTemp);
				expItem.InsertTail(ExpressionElement('*'));
				expItem.InsertTail(ExpressionElement('('));
			}
			else if (lastType == 3) {
				expItem.InsertTail(ExpressionElement('*'));
				expItem.InsertTail(ExpressionElement('('));
			}
			else if (lastType == 5) {
				insertTemp.isOperator = false;
				insertTemp.number = 0;
				insertTemp.legalFlag = true;
				//expItem.InsertTail(insertTemp);
				//expItem.InsertTail(ExpressionElement(data[i - 1]));
				expItem.InsertTail(ExpressionElement('('));
			}
			else {
				expItem.InsertTail(ExpressionElement('('));
			}
			lastType = 2;
		}
		else if (data[i] == ')') {
			if (lastType == 1) {
				char2num(data, curBegin, curEnd, expTemp, stat);
				if (stat) {
					std::cout << "输入不合法: 字符输入有误 4" << std::endl;
					return;
				}
				insertTemp.isOperator = false;
				insertTemp.number = expTemp;
				insertTemp.legalFlag = true;
				expItem.InsertTail(insertTemp);

				expItem.InsertTail(ExpressionElement(')'));
				lastType = 3;
			}
			else if (lastType == 3) {
				expItem.InsertTail(ExpressionElement(')'));
				lastType = 3;
			}
			else {
				std::cout << "输入不合法: 括号内表达式不完整" << std::endl;
				return;
			}
		}
		else if (data[i] == '+' || data[i] == '-') {
			if (lastType == 2 || lastType == 0) {
				if (lastType == 0 && data[i] == '-') {
					insertTemp.isOperator = false;
					insertTemp.number = 0;
					insertTemp.legalFlag = true;
					expItem.InsertTail(ExpressionElement('R')); //单目运算负号
					curBegin = i + 1;
					lastType = 5;
					if (length > 1) {
						if (data[i + 1] == '+' || data[i + 1] == '-') {
							std::cout << "输入不合法: 表达式首部错误" << std::endl;
							return;
						}
					}
				}
				else {
					if (data[i] == '+') {
						lastType2 = 1;
						lastType = 5;
						curBegin = i;
						curEnd = i;
						lastType = 5;
					}
					else {
						lastType = 5;
						expItem.InsertTail(ExpressionElement('R')); //单目运算负号
						curBegin = i + 1;
						curEnd = i;
					}

				}
			}
			else if (lastType == 4) {
				if (lastType2 == 1 || lastType2 == 2) {
					if (data[i] == '+') {
						lastType = 5;
						curBegin = i;
						curEnd = i;
						lastType = 5;
					}
					else {
						lastType = 5;
						expItem.InsertTail(ExpressionElement('R')); //单目运算负号
						curBegin = i + 1;
						curEnd = i;
					}
				}
				else {
					std::cout << "输入不合法: 单目运算符错误" << std::endl;
					return;
				}
			}
			else if (lastType == 5) {
				std::cout << "输入不合法: 单目运算符后不能接单目运算符" << std::endl;
				return;
			}
			else if (lastType == 1) {

				char2num(data, curBegin, curEnd, expTemp, stat);
				if (stat) {
					std::cout << "输入不合法: 字符输入有误 3 " << std::endl;
					return;
				}
				insertTemp.isOperator = false;
				insertTemp.number = expTemp;
				insertTemp.legalFlag = true;
				expItem.InsertTail(insertTemp);
				expItem.InsertTail(ExpressionElement(data[i]));
				lastType = 4;
				lastType2 = 1;

			}
			else {
				expItem.InsertTail(ExpressionElement(data[i]));
				lastType = 4;
				lastType2 = 1;
			}
		}
		else if (data[i] == '*' || data[i] == '/' || data[i] == '^' || data[i] == '%') {
			if (lastType == 5) {
				std::cout << "输入不合法: 双目运算符不能跟于单目运算符后" << std::endl;
				return;
			}
			else if (lastType == 0) {
				std::cout << "输入不合法: 表达式开头不允许有双目运算符" << std::endl;
				return;
			}
			else if (lastType == 2) {
				std::cout << "输入不合法: 左括号右侧第一字符不允许为双目运算符" << std::endl;
				return;
			}
			else if (lastType == 4) {
				std::cout << "输入不合法: 双目运算符右侧第一字符不允许为双目运算符" << std::endl;
				return;
			}
			else if (lastType == 1) {
				char2num(data, curBegin, curEnd, expTemp, stat);
				if (stat) {
					std::cout << "输入不合法: 字符输入有误 2" << std::endl;
					return;
				}
				insertTemp.isOperator = false;
				insertTemp.number = expTemp;
				insertTemp.legalFlag = true;
				expItem.InsertTail(insertTemp);

				expItem.InsertTail(ExpressionElement(data[i]));
				lastType = 4;
				lastType2 = 2;

			}
			else {
				expItem.InsertTail(ExpressionElement(data[i]));
				lastType = 4;
				lastType2 = 2;
			}
		}
		else {
			std::cout << "输入不合法: 包含不合法的字符（除运算符、数字之外的字符）" << std::endl;
			return;
		}

		
	}
	if (lastType == 1) {
		char2num(data, curBegin, curEnd, expTemp, stat);
		if (stat) {
			std::cout << "输入不合法: 字符输入有误 1" << std::endl;
			return;
		}
		insertTemp.isOperator = false;
		insertTemp.number = expTemp;
		insertTemp.legalFlag = true;
		expItem.InsertTail(insertTemp);
	}
	if (lastType == 5) {
		std::cout << "输入不合法: 单目运算符错误" << std::endl;
		return;
	}
	if (lastType == 4) {
		std::cout << "输入不合法: 缺少操作数" << std::endl;
		return;
	}
	
	//转换为RPN表达式
	LinkedList<ExpressionElement> resultList;//结果链表
	Stack<ExpressionElement> opStack;//符号栈
	ExpressionElement stackTop;
	opStack.Push(ExpressionElement('('));
	expItem.InsertTail(ExpressionElement(')'));
	for (LinkedListNode<ExpressionElement> *i = expItem.head->succ; i != nullptr; i = i->succ) {
		if (i->data.isOperator) {
			if (i->data.operatorType == '(') {
				opStack.Push(i->data);
			}
			else if (i->data.operatorType == '^') {
				while (1) {
					opStack.GetTop(stackTop);
					if (stackTop.operatorType == '^') {
						break; //如果乘方运算优先级从左往右，将break注释，并且取消下两行注释
						//resultList.InsertTail(stackTop);
						//opStack.Pop();
					}
					else {
						break;
					}
				}
				opStack.Push(i->data);
			}
			else if (i->data.operatorType == 'R') {
				while (1) {
					opStack.GetTop(stackTop);
					//if (stackTop.operatorType == '^' || stackTop.operatorType == 'R') {
					if (stackTop.operatorType == 'R') {
						resultList.InsertTail(stackTop);
						opStack.Pop();
					}
					else {
						break;
					}
				}
				opStack.Push(i->data);
			}
			else if (i->data.operatorType == '*' || i->data.operatorType == '/' || i->data.operatorType == '%') {
				while (1) {
					opStack.GetTop(stackTop);
					if (stackTop.operatorType == '^' || stackTop.operatorType == '*' || stackTop.operatorType == '/' ||
						stackTop.operatorType == '%' || stackTop.operatorType == 'R') {
						resultList.InsertTail(stackTop);
						opStack.Pop();
					}
					else {
						break;
					}
				}
				opStack.Push(i->data);
			}
			else if (i->data.operatorType == '+' || i->data.operatorType == '-') {
				while (1) {
					opStack.GetTop(stackTop);
					if (stackTop.operatorType == '^' || stackTop.operatorType == '*' || stackTop.operatorType == '/' ||
						stackTop.operatorType == '%' || stackTop.operatorType == '+' || stackTop.operatorType == '-' || stackTop.operatorType == 'R') {
						resultList.InsertTail(stackTop);
						opStack.Pop();
					}
					else {
						break;
					}
				}
				opStack.Push(i->data);
			}
			else if (i->data.operatorType == ')') {
				while (1) {
					opStack.GetTop(stackTop);
					if (stackTop.operatorType == '(') {
						opStack.Pop();
						break;
					}
					else {
						resultList.InsertTail(stackTop);
						opStack.Pop();
					}
				}
			}
		}
		else {
			resultList.InsertTail(i->data);
		}
	}

	
	//计算RPN表达式
	Stack<ExpressionElement> rpnStack;
	ExpressionElement operand[2], tmpResult;
	tmpResult.isOperator = false;
	for (LinkedListNode<ExpressionElement> *i = resultList.head->succ; i != nullptr; i = i->succ) {
		if (i->data.isOperator == false) {
			rpnStack.Push(i->data);
		}
		else {
			rpnStack.GetTop(operand[1]); rpnStack.Pop();
			if (i->data.operatorType != 'R') {
				if (!rpnStack.GetSize()) {
					std::cout << "输入不合法：操作数不足" << std::endl;
					return;
				}
				rpnStack.GetTop(operand[0]);
				rpnStack.Pop();
			}
			switch (i->data.operatorType) {
			case '+':
				tmpResult.number = operand[0].number + operand[1].number;
				rpnStack.Push(tmpResult);
				break;

			case '-':
				tmpResult.number = operand[0].number - operand[1].number;
				rpnStack.Push(tmpResult);
				break;
			case 'R': //单目运算负号
				tmpResult.number = -operand[1].number;
				rpnStack.Push(tmpResult);
				break;
			case '*':
				tmpResult.number = operand[0].number * operand[1].number;
				rpnStack.Push(tmpResult);
				break;
			case '/':
				if (operand[1].number == 0) {
					std::cout << "输入不合法：除数为0" << std::endl;
					return;
				}
				tmpResult.number = operand[0].number / operand[1].number;
				rpnStack.Push(tmpResult);
				break;
			case '%':
				if (operand[1].number == 0) {
					std::cout << "输入不合法：取余运算中出现模0" << std::endl;
					return;
				}
				if (operand[1].number.isInteger() == false || operand[0].number.isInteger() == false) {
					std::cout << "输入不合法：无法对非整数的数字进行取模运算" << std::endl;
					return;
				}
				tmpResult.number = operand[0].number % operand[1].number;
				rpnStack.Push(tmpResult);
				break;
			case '^':
				if (operand[1].number == 0 && operand[0].number == 0) {
					std::cout << "输入不合法：指数和底数同时为0" << std::endl;
				}
				else if (operand[1].number < 0 && operand[0].number == 0) {
					std::cout << "输入不合法：除数为0" << std::endl;
					return;
				}
				else {
					int stat;
					tmpResult.number = operand[0].number.Pow(operand[1].number, stat);
					if (stat == 0) {
						std::cout << "运算不支持：乘幂运算后，结果无法使用实数表示" << std::endl;
						return;
					}
					else if (stat == 2) {
						warning_IrrationalNum = true;
					}
					rpnStack.Push(tmpResult);
				}

				break;
			}
		}
	}
	//显示警告
	if (warning_IrrationalNum) {
		std::cout << "提示:运算过程中出现无理数，已经作近似处理，精度可能有损失" << std::endl << std::endl;
	}
	//返回答案
	ExpressionElement answer;
	rpnStack.GetTop(answer);
	answer.number.FastPrint();
	if (!answer.number.isInteger()) {
		std::cout << "(小数结果:";
		answer.number.FastPrint(true, 8);
		std::cout << ")";
	}

}
//************************************
// 全名:  ExpressionCalculator::mainLoop
// 功能: 表达式计算器，主过程
// 权限:    public 
// 返回:   void
//************************************
void ExpressionCalculator::mainLoop() {
	std::string readIn;
	while (1) {
		readIn = "";
		std::cout << "输入表达式:" << std::endl;
		std::getline(std::cin, readIn);
		solve(readIn.c_str());
		while (1) {
			std::cout << std::endl << "是否继续 (y,n)? ";
			std::getline(std::cin, readIn);
			if (readIn == "y" || readIn == "Y") {
				std::cout << std::endl;
				break;
			}
			else if (readIn == "n" || readIn == "N") {
				return;
			}
		}
	}
}
void calcCaller() {
	ExpressionCalculator instance;
	instance.mainLoop();
}
int main() {
	calcCaller();
	return 0;
}