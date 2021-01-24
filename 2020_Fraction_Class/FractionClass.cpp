#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
using namespace std;

//************************************
// 类名：fraction
// 功能: 分数类，实现分数之间的加减乘除通分、取负、倒数、约分与逻辑判断等运算
// 作者: 
// 学号: 
//************************************
class fraction {
private:
	//  大整数类，用于存储较大整数 
	class bigInteger { //(之前几个小数乘起来、几个分数加起来分母直接超过 unsigned long long 了)
	public:
		~bigInteger();
		bigInteger(const string& x);
		bigInteger(int x);
		bigInteger(long x);
		bigInteger(long long x);
		bigInteger(const char* x);
		bigInteger(char* x);
		bigInteger(const bigInteger& x);
		bigInteger();

		const bigInteger& operator =(const bigInteger& x);
		bigInteger operator +(const bigInteger& x);
		bigInteger operator -(const bigInteger& x);
		bigInteger operator *(const bigInteger& x);
		bigInteger operator /(const bigInteger& x);
		bigInteger operator %(const bigInteger& x);
		bigInteger operator -();
		bigInteger operator +();
		bigInteger& operator+=(const bigInteger& x);
		bigInteger& operator-=(const bigInteger& x);
		bigInteger& operator*=(const bigInteger& x);
		bigInteger& operator/=(const bigInteger& x);
		bigInteger& operator%=(const bigInteger& x);

		bool operator>(const bigInteger& x);
		bool operator<(const bigInteger& x);
		bool operator==(const bigInteger& x);
		bool operator!=(const bigInteger& x);
		bool operator>=(const bigInteger& x);
		bool operator<=(const bigInteger& x);

		string toString();
		string divisionDecimal(const bigInteger& dividend, const bigInteger& divisor,int accuracy);

	private:
		//bigInteger 除法计算结果 
		struct bigIntegerDivision {
			//bigInteger 除法计算结果:整除部分指针
			bigInteger* div;
			//bigInteger 除法计算结果:余数部分指针
			bigInteger* mod;

			void deallocate();
		};

		//bigInteger 大数数位存储数组
		int* digits;
		//bigInteger 数字正负号
		int sign;
		//bigInteger 数字位数
		int size;
		//bigInteger 大数数位存储数组非空状态
		bool allocateStatus;

		void read(const string& x);
		void read(long long x);
		void print();
		void allocate(int requestSize);
		void reallocate(int requestSize);
		void deallocate();
		bigInteger getAbs();
		bigInteger absoluteAddition(const bigInteger& addendFirst, const bigInteger& addendSecond);
		bigInteger absoluteSubtraction(const bigInteger& minuend, const bigInteger& subtrahend);
		bigInteger absoluteMultiplication(const bigInteger& multiplierFirst, const bigInteger& multiplierSecond);
		bigInteger absoluteLeftMove(const bigInteger& x, int reqSize); //十进制下，不是二进制
		bigInteger absoluteRightMove(const bigInteger& x, int reqSize); //十进制下，不是二进制
		bigIntegerDivision absoluteDivision(const bigInteger& dividend, const bigInteger& divisor);
		string absoluteDivisionDecimal(const bigInteger& dividend, const bigInteger& divisor, int accuracy);
		int absoluteComparison(const bigInteger&x, const bigInteger& y);
		string ll2string(long long x);
		bool isZero();
	};
public:
	//bigInteger 别名
	typedef bigInteger bInt;
	fraction inverse(bool selfAlteration = true);
	fraction reciprocal(bool selfAlteration = true);
	fraction reduction(bool selfAlteration = true);
	template<typename ostreamTypeName=ostream>void print(ostreamTypeName& outputStream=cout);
	void synchronizeDenominator(fraction& sourceFirst, fraction& sourceSecond);

	string toDecimalString(int accuracy=5);

	fraction();
	fraction(const string& x);
	fraction(double x);
	fraction(const char* x);
	fraction(long long x);
	fraction(long x);
	fraction(int x);
	fraction(int x, int y);
	fraction(const fraction& x);

	void operator & (fraction& x);
	fraction operator + (const fraction& x);
	fraction operator * (const fraction& x);
	fraction operator - (const fraction& x);
	fraction operator / (const fraction& x);
	fraction operator -();
	fraction operator +();
	fraction operator + (double x);
	fraction operator * (double x);
	fraction operator - (double x);
	fraction operator / (double x);
	fraction& operator += (const fraction& x);
	fraction& operator -= (const fraction& x);
	fraction& operator *= (const fraction& x);
	fraction& operator /= (const fraction& x);

	friend fraction operator + (double x, const fraction& y);
	friend fraction operator - (double x, const fraction& y);
	friend fraction operator * (double x, const fraction& y);
	friend fraction operator / (double x, const fraction& y);

	bool operator > (const fraction& x);
	bool operator < (const fraction& x);
	bool operator >= (const fraction& x);
	bool operator <= (const fraction& x);
	bool operator == (const fraction& x);
	bool operator != (const fraction& x);

	friend ostream& operator << (ostream& op, const fraction& x);
	friend istream& operator >> (istream& ip, fraction& x);

protected:
	
private:
	//fraction 分数 分子
	bInt numerator;
	//fraction 分数 分母
	bInt denominator;

	fraction(const bInt& x, const bInt& y);

	void loadFromStr(const char* p, bool doReduction = true);
	void loadFromStr2(const char* p, bool doReduction = false);
	bool judgeStrType(const char* p);
	inline bInt gcd(bInt x, bInt y);
	inline bInt lcm(bInt x, bInt y);
	
};


//************************************************************************
// 		fraction::bigInteger 类
//		构造函数和析构函数
//************************************************************************

fraction::bigInteger::bigInteger(const string& x) :allocateStatus(0) { read(x); }
fraction::bigInteger::bigInteger(long long x) : allocateStatus(0) { read(x); }
fraction::bigInteger::bigInteger(int x) : allocateStatus(0) { read((long long)x); }
fraction::bigInteger::bigInteger(long x) : allocateStatus(0) { read((long long)x); }
fraction::bigInteger::bigInteger(const char* x) : allocateStatus(0) { read(string(x, x + strlen(x))); }
fraction::bigInteger::bigInteger(char* x) : allocateStatus(0) { read(string(x, x + strlen(x))); }
fraction::bigInteger::bigInteger() : allocateStatus(0) { read(0); }

//bigInteger 深复制
fraction::bigInteger::bigInteger(const bigInteger& x) : allocateStatus(0) {
	this->sign = x.sign;
	this->size = x.size;
	reallocate(x.size);
	for (int i = 0; i < x.size; i++) this->digits[i] = x.digits[i];
}
//bigInteger 析构函数
fraction::bigInteger::~bigInteger() { if (allocateStatus)deallocate(); } //delete 从new生成的digits指针

//************************************************************************
// 		fraction::bigInteger 类
//		算术运算符重载
//************************************************************************

fraction::bigInteger fraction::bigInteger::operator+(const bigInteger& x) {
	const bigInteger& y = (*this);
	bigInteger ret=bigInteger(0);
	if (y.sign == 1 && x.sign == 1) return this->absoluteAddition(x, y);
	if (y.sign == -1 && x.sign == -1) {
		ret = this->absoluteAddition(x, y);
		ret = -ret;
		return ret;
	}
	if (y.sign == -1 && x.sign == 1) {
		if (((bigInteger)x).getAbs() > ((bigInteger)y).getAbs()) {
			ret = this->absoluteSubtraction(x, y);
			return ret;
		}
		else {
			ret = this->absoluteSubtraction(y, x);
			ret = -ret;
			return ret;
		}
	}
	if (y.sign == 1 && x.sign == -1) {
		if (((bigInteger)x).getAbs() > ((bigInteger)y).getAbs()) {
			ret = this->absoluteSubtraction(x, y);
			ret = -ret;
			return ret;
		}
		else {
			ret = this->absoluteSubtraction(y, x);
			return ret;
		}
	}
	return ret; 
}
fraction::bigInteger fraction::bigInteger::operator-(const bigInteger& x) { return (*this) + (-(bigInteger)x); }
fraction::bigInteger fraction::bigInteger::operator*(const bigInteger& x) {
	bigInteger ret;
	ret = this->absoluteMultiplication(*this, x);
	ret.sign = x.sign*(*this).sign;
	if (ret.isZero()) ret.sign = 1;
	return ret;
}
fraction::bigInteger fraction::bigInteger::operator/(const bigInteger& x) {
	bigIntegerDivision ret = absoluteDivision(*this, x);
	bigInteger rets = *ret.div;
	int retSign = (this->sign)*x.sign;
	rets.sign = retSign;
	ret.deallocate();
	return rets;
}
fraction::bigInteger fraction::bigInteger::operator%(const bigInteger& x) {
	return (*this) - ((*this) / x)*x;
}

fraction::bigInteger fraction::bigInteger::operator-() {
	bigInteger ret = (*this);
	ret.sign = (ret.sign == 1) ? -1 : 1;
	if (ret.isZero() == true) ret.sign = 1;
	return ret;
}
fraction::bigInteger fraction::bigInteger::operator+() {
	return (*this);
}

//************************************************************************
// 		fraction::bigInteger 类
//		关系运算符重载
//************************************************************************

bool fraction::bigInteger::operator>(const bigInteger& x) {
	const bigInteger& y = (*this);
	if (y.sign == 1 && x.sign == 1) {
		return (absoluteComparison(y, x) == 1);
	}
	if (y.sign == -1 && x.sign == 1) {
		return 0;
	}
	if (y.sign == 1 && x.sign == -1) {
		if (absoluteComparison(y, x) != 0) return 1;
		else return 0;
	}
	if (y.sign == -1 && x.sign == -1) {
		return (absoluteComparison(x, y) == 1);
	}
	return 0; 
}
bool fraction::bigInteger::operator<(const bigInteger& x) { return (bigInteger)x > (*this); }
bool fraction::bigInteger::operator==(const bigInteger& x) {
	if (((bigInteger)x).isZero() && this->isZero())return true;
	if (x.sign == this->sign && absoluteComparison(x, *this) == 0) return true;
	return false;
}
bool fraction::bigInteger::operator!=(const bigInteger& x) { return !((*this) == x); }
bool fraction::bigInteger::operator>=(const bigInteger& x) { return ((*this) > x) || ((*this) == x); }
bool fraction::bigInteger::operator<=(const bigInteger& x) { return ((*this) < x) || ((*this) == x); }

//************************************************************************
// 		fraction::bigInteger 类
//		赋值运算符重载
//************************************************************************

//bigInteger 赋值运算符(=)重载 [深复制]
const fraction::bigInteger& fraction::bigInteger::operator=(const bigInteger& x) {
	deallocate();
	this->sign = x.sign;
	this->size = x.size;
	allocate(x.size);
	for (int i = 0; i < x.size; i++) {
		this->digits[i] = x.digits[i];
	}
	return *this;
}
fraction::bigInteger& fraction::bigInteger::operator+=(const bigInteger& x) { *this = *this + x; return *this; }
fraction::bigInteger& fraction::bigInteger::operator-=(const bigInteger& x) { *this = *this - x; return *this; }
fraction::bigInteger& fraction::bigInteger::operator*=(const bigInteger& x) { *this = *this * x; return *this; }
fraction::bigInteger& fraction::bigInteger::operator/=(const bigInteger& x) { *this = *this / x; return *this; }
fraction::bigInteger& fraction::bigInteger::operator%=(const bigInteger& x) { *this = *this % x; return *this; }

//************************************************************************
// 		fraction::bigInteger 类
//		其他成员函数
//************************************************************************

//************************************
// 函数功能：bigInteger 清空除法结果中整数和余数指针指向的对象
//************************************
void fraction::bigInteger::bigIntegerDivision::deallocate() {
		delete div;
		delete mod;
}

//************************************
// 函数功能：bigInteger 分配存储数位的指针
// 参数:requestSize: (int)所需存储的数字位数
//************************************
void fraction::bigInteger::allocate(int requestSize) {
	digits = new int[requestSize + 1];
	allocateStatus = true; 
}

//************************************
// 函数功能：bigInteger 删除存储数位的指针指向的内容
//************************************
void fraction::bigInteger::deallocate() {
	delete[]digits;
	allocateStatus = false; 
}

//************************************
// 函数功能：bigInteger 再分配存储数位的指针
// 参数:requestSize: (int)所需存储的数字位数
//************************************
void fraction::bigInteger::reallocate(int requestSize) {
	if (allocateStatus)deallocate();
	allocate(requestSize); 
}

//************************************
// 函数功能：bigInteger 数字转换为STL String
// 参数: x: (long long)需要转换的数字
// 返回值: (string) 与数字对应的string字符串
//************************************
string fraction::bigInteger::ll2string(long long x) {
	ostringstream oss;
	oss << x;
	return oss.str();
}

//************************************
// 函数功能：bigInteger 读取数字字符串并赋值给对象自身
// 参数: x: (const string&) 需要对*this赋值的内容
//************************************
void fraction::bigInteger::read(const string& x) {
	int strLen = x.length(), stop = 0, allocateSize;
	if (x[0] == '-') sign = -1, stop = 1;
	else sign = 1;
	allocateSize = strLen - stop;
	reallocate(allocateSize);
	size = allocateSize;
	for (int i = strLen - 1, j = 0; i >= stop; i--, j++) {
		digits[j] = (int)(x[i] - '0');
	}
	if (isZero())sign = 1;
}

//************************************
// 函数功能：bigInteger 读取数字变量内容并赋值给对象自身
// 参数: x: (long long) 需要对*this赋值的内容
//************************************
void fraction::bigInteger::read(long long x) {
	read(ll2string(x)); 
}

//************************************
// 函数功能：bigInteger 输出数字
//************************************
void fraction::bigInteger::print() {
	if (sign == -1) cout << "-";
	for (int i = size - 1; i >= 0; i--) {
		cout << digits[i] << "";
	}
}

//************************************
// 函数功能：bigInteger 判断该对象存储的数字是否为0
// 返回值: (bool) 数字是否为0，是则返回true
//************************************
bool fraction::bigInteger::isZero() {
	if (allocateStatus) {
		if (digits[0] == 0 && size == 1) {
			return true;
		}
	}
	return false;
}

//************************************
// 函数功能：bigInteger 返回对象的取绝对值的副本
// 返回值: (fraction::bigInteger) 取绝对值后的对象副本
//************************************
fraction::bigInteger fraction::bigInteger::getAbs() {
	bigInteger ret = (*this);
	ret.sign = 1;
	return ret;
}

//************************************
// 函数功能：bigInteger 对两个对象进行加法计算(舍弃对象中的正负号设定)
// 参数:
// addentFirst: (const bigInteger&) 加法运算的加数
// addendSecond: (const bigInteger&) 加法运算的加数
// 返回值: (fraction::bigInteger) 对两个对象的绝对值部分相加后的结果
//************************************
fraction::bigInteger fraction::bigInteger::absoluteAddition(const bigInteger& addentFirst, const bigInteger& addendSecond) {
	int maxSize = (addentFirst.size > addendSecond.size) ? addentFirst.size : addendSecond.size;
	int* ret = new int[maxSize + 1];
	int carry = 0, xCurrentDigit = 0, yCurrentDigit = 0, digitSum = 0, retSize = maxSize;
	for (int i = 0; i <= maxSize; i++) {
		if (i < addendSecond.size) { xCurrentDigit = addendSecond.digits[i]; }
		else { xCurrentDigit = 0; }
		if (i < addentFirst.size) { yCurrentDigit = addentFirst.digits[i]; }
		else { yCurrentDigit = 0; }
		digitSum = xCurrentDigit + yCurrentDigit + carry;
		if (digitSum >= 10) { carry = 1; digitSum -= 10; ret[i] = digitSum; }
		else { carry = 0; ret[i] = digitSum; }
	}
	if (ret[maxSize])retSize++;

	bigInteger rets;
	rets.sign = 1;
	rets.size = retSize;
	rets.reallocate(retSize);
	for (int i = 0; i < retSize; i++) rets.digits[i] = ret[i];
	delete[]ret;
	return rets;
}


//************************************
// 函数功能：bigInteger 对两个对象进行减法计算(舍弃对象中的正负号设定)
// 参数:
// minuend: (const bigInteger&) 运算的被减数
// subtrahend: (const bigInteger&) 运算的减数
// 返回值: (fraction::bigInteger) 对两个对象的绝对值部分相减后的结果
//************************************
fraction::bigInteger fraction::bigInteger::absoluteSubtraction(const bigInteger& minuend, const bigInteger& subtrahend) {
	int maxSize = (subtrahend.size > minuend.size) ? subtrahend.size : minuend.size;
	int* ret = new int[maxSize + 1];
	int decomposition = 0, xCurrentDigit = 0, yCurrentDigit = 0, digitSum = 0, validBegin = 0;
	for (int i = 0; i < maxSize; i++) {
		if (i < minuend.size) { xCurrentDigit = minuend.digits[i]; }
		else { xCurrentDigit = 0; }

		if (i < subtrahend.size) { yCurrentDigit = subtrahend.digits[i]; }
		else { yCurrentDigit = 0; }

		digitSum = xCurrentDigit - yCurrentDigit - decomposition;
		if (digitSum < 0) { decomposition = 1; digitSum += 10; ret[i] = digitSum; }
		else { decomposition = 0; ret[i] = digitSum; }
	}
	for (int i = maxSize - 1; i >= 0; i--) {
		if (ret[i]) {
			validBegin = i;
			break;
		}
	}
	bigInteger rets;
	rets.sign = 1;
	rets.size = validBegin + 1;
	rets.reallocate(validBegin + 1);
	for (int i = 0; i <= validBegin; i++) rets.digits[i] = ret[i];
	delete[] ret;
	return rets;
}


//************************************
// 函数功能：bigInteger 比较两个对象的绝对值大小
// 参数:
// x: (const bigInteger&) 第一个数
// y: (const bigInteger&) 第二个数
// 返回值: (int) 若第一个数字绝对值大，返回1；相等，返回0，第一个数字绝对值小，返回-1
//************************************
int fraction::bigInteger::absoluteComparison(const bigInteger& x, const bigInteger& y) {
	int maxSize = (y.size > x.size) ? y.size : x.size;
	int xCurrentDigit, yCurrentDigit;
	for (int i = maxSize - 1; i >= 0; i--) {
		if (i < x.size) { xCurrentDigit = x.digits[i]; }
		else { xCurrentDigit = 0; }
		if (i < y.size) { yCurrentDigit = y.digits[i]; }
		else { yCurrentDigit = 0; }
		if (xCurrentDigit > yCurrentDigit) return 1;
		if (yCurrentDigit > xCurrentDigit)return -1;
	}
	return 0;
}


//************************************
// 函数功能：bigInteger 对两个对象进行乘法计算(舍弃对象中的正负号设定)
// 参数:
// x: (const bigInteger&) 运算的乘数
// y: (const bigInteger&) 运算的乘数
// 返回值: (fraction::bigInteger) 对两个对象的绝对值部分相乘后的结果
//************************************
fraction::bigInteger fraction::bigInteger::absoluteMultiplication(const bigInteger& multiplierFirst, const bigInteger& multiplierSecond) {
	int maxSize = multiplierFirst.size + multiplierSecond.size;
	int** ret = new int*[multiplierSecond.size];
	int* retSum = new int[maxSize];
	for (int i = 0; i < multiplierSecond.size; i++) {
		ret[i] = new int[maxSize];
	}
	for (int i = 0; i < multiplierSecond.size; i++) {
		for (int j = 0; j < maxSize; j++) {
			ret[i][j] = 0;
		}
	}
	for (int i = 0; i < maxSize; i++) retSum[i] = 0;
	int carry = 0;
	for (int i = 0; i < multiplierSecond.size; i++) {
		for (int j = 0; j < multiplierFirst.size; j++) {
			ret[i][j + i] = multiplierFirst.digits[j] * multiplierSecond.digits[i] + carry;
			carry = (int)ret[i][j + i] / 10;
			ret[i][j + i] = ret[i][j + i] - carry * 10;
		}
		ret[i][multiplierFirst.size + i] = carry;
		carry = 0;
	}
	for (int i = 0; i < maxSize; i++) {
		for (int j = 0; j < multiplierSecond.size; j++) {
			retSum[i] += ret[j][i];
		}
	}
	carry = 0;
	for (int i = 0; i < maxSize; i++) {
		retSum[i] += carry;
		carry = (int)retSum[i] / 10;
		retSum[i] -= carry * 10;
	}
	int validBegin = 0;
	for (int i = maxSize - 1; i >= 0; i--) {
		if (retSum[i]) {
			validBegin = i;
			break;
		}
	}
	bigInteger rets;
	rets.size = validBegin + 1;
	rets.sign = 1;
	rets.reallocate(rets.size);
	for (int i = 0; i <= validBegin; i++) rets.digits[i] = retSum[i];
	for (int i = 0; i < multiplierSecond.size; i++) delete[]ret[i];
	delete[]ret;
	delete[]retSum;
	return rets;
}
//************************************
// 函数功能：bigInteger 返回对对象乘上10的多次方后的结果(舍弃对象中的正负号设定)
// 参数:
// x: (const bigInteger&) 运算的基数
// reqSize: (int) 需要乘上的10的幂次
// 返回值: (fraction::bigInteger) 返回对对象乘上10的多次方后的结果的绝对值
//************************************
fraction::bigInteger fraction::bigInteger::absoluteLeftMove(const bigInteger& x, int reqSize) {
	bigInteger ret;
	ret.size = x.size + reqSize;
	ret.sign = 1;
	ret.reallocate(ret.size);
	for (int i = 0; i < reqSize; i++) ret.digits[i] = 0;
	for (int i = reqSize; i < ret.size; i++) ret.digits[i] = x.digits[i - reqSize];
	return ret;
}

//************************************
// 函数功能：bigInteger 返回对对象初以10的多次方后的结果(舍弃对象中的正负号设定)
// 参数:
// x: (const bigInteger&) 运算的基数
// reqSize: (int) 需要乘上的10的幂次的相反数
// 返回值: (fraction::bigInteger) 返回对对象初以10的多次方后的结果的绝对值
//************************************
fraction::bigInteger fraction::bigInteger::absoluteRightMove(const bigInteger& x, int reqSize) {
	bigInteger ret;
	ret.size = ((x.size - reqSize) > 0) ? (x.size - reqSize) : 0;
	ret.sign = 1;
	ret.reallocate(ret.size);
	for (int i = reqSize; i < x.size; i++) ret.digits[i - reqSize] = x.digits[i];
	return ret;
}

//************************************
// 函数功能：bigInteger 返回对象的绝对值除法运算时得到的商和余数
// 参数:
// dividend: (const bigInteger&) 运算的被除数(取绝对值)
// divisor: (const bigInteger&) 运算的除数(取绝对值)
// 返回值: (fraction::bigInteger::bigIntegerDivision) 指针的集合，返回对象的绝对值除法运算时得到的商(*div)和余数(*mod)的指针
//************************************
fraction::bigInteger::bigIntegerDivision fraction::bigInteger::absoluteDivision(const bigInteger& dividend, const bigInteger& divisor) {
	bigIntegerDivision rets;
	rets.div = new bigInteger;
	rets.mod = new bigInteger;
	bigInteger dividendAbs = dividend, divisorAbs = divisor, divisorM;
	dividendAbs.sign = 1;
	divisorAbs.sign = 1;
	int maxSize = dividend.size;
	int* ret = new int[maxSize];
	for (int i = 0; i < maxSize; i++)ret[i] = 0;
	int quotientPosition = dividendAbs.size - divisorAbs.size;
	for (int i = quotientPosition; i >= 0; i--) {
		divisorM = absoluteLeftMove(divisorAbs, i);
		while (dividendAbs >= divisorM) {
			ret[i]++;
			dividendAbs = dividendAbs - divisorM;
		}
	}
	int validBegin = 0;
	for (int i = maxSize - 1; i >= 0; i--) {
		if (ret[i]) {
			validBegin = i;
			break;
		}
	}
	rets.div->size = validBegin + 1;
	rets.div->sign = 1;
	rets.div->reallocate(rets.div->size);
	for (int i = 0; i <= validBegin; i++) rets.div->digits[i] = ret[i];
	*rets.mod = dividendAbs;
	delete[]ret;
	return rets;
}

//************************************
// 函数功能：bigInteger 返回对象的绝对值除法运算时的小数结果(结果下取整),可用于fraction中结果的验证
// 参数:
// dividend: (const bigInteger&) 运算的被除数(取绝对值)
// divisor: (const bigInteger&) 运算的除数(取绝对值)
// accuracy: (int) 结果精度(保留位数)
// 返回值: (std::string) 小数的结果
//************************************
string fraction::bigInteger::absoluteDivisionDecimal(const bigInteger& dividend, const bigInteger& divisor,int accuracy) {
	bigIntegerDivision integerResult = absoluteDivision(dividend, divisor);
	bigInteger dividendSource = *(integerResult.mod),  dividendM = dividendSource;
	bigInteger integerPart = *(integerResult.div);
	integerResult.deallocate();

	int* decimalPartResult = new int[accuracy];
	for (int i = 0; i < accuracy; i++) {
		dividendM = absoluteLeftMove(dividendM, 1);
		decimalPartResult[i] = 0;
		while (dividendM >= divisor) {
			decimalPartResult[i]++;
			dividendM -= divisor;
		}
	}
	string ret = integerPart.toString();
	ret += ".";
	for (int i = 0; i < accuracy; i++) ret += (char)(decimalPartResult[i] + '0');
	return ret;
}

//************************************
// 函数功能：bigInteger 返回对象的除法运算时的小数结果(结果下取整),可用于fraction中结果的验证
// 参数:
// dividend: (const bigInteger&) 运算的被除数
// divisor: (const bigInteger&) 运算的除数
// accuracy: (int) 结果精度(保留位数)
// 返回值: (std::string) 小数的结果
//************************************
string fraction::bigInteger::divisionDecimal(const bigInteger& dividend, const bigInteger& divisor,int accuracy) {
	int isNegative = ((dividend.sign == -1) ^ (divisor.sign == -1));
	string ret = "";
	if (isNegative) ret += "-";
	ret += absoluteDivisionDecimal(dividend, divisor, accuracy);
	return ret;
}


//************************************
// 函数功能：bigInteger 将大数对象转换为STLString
// 返回值: (std::string) 将数位数组代表的数字转化为字符串的结果
//************************************
string fraction::bigInteger::toString() {
	string ret = "", retap;
	char tmp;
	if (sign == -1)ret.append("-");
	for (int i = size - 1; i >= 0; i--) {
		tmp = (char)(digits[i] + '0');
		retap = string(1,tmp);
		ret.append(retap);
	}
	return ret;
}

//************************************************************************
// 		fraction  类
//		构造函数
//************************************************************************

fraction::fraction() :numerator(0), denominator(1) {}
fraction::fraction(int x) : numerator(x), denominator(1) {}
fraction::fraction(long x) : numerator(x), denominator(1) {}
fraction::fraction(long long x) : numerator(x), denominator(1) {}
fraction::fraction(double x) {
	ostringstream oss;
	oss.precision(12);
	oss << x;
	loadFromStr(oss.str().data(), true);
}
fraction::fraction(const char* x) { judgeStrType(x) ? loadFromStr2(x) : loadFromStr(x); }
fraction::fraction(const string& x) { judgeStrType(x.data()) ? loadFromStr2(x.data()) : loadFromStr(x.data()); }
fraction::fraction(int x, int y) :numerator(x), denominator(y) {}
fraction::fraction(const fraction::bigInteger& x, const fraction::bigInteger& y) : numerator(x), denominator(y) {
	if ((bigInteger)y < 0) {
		numerator = -(bigInteger)x;
		denominator = -(bigInteger)y;
	}
}
fraction::fraction(const fraction& x) : numerator(x.numerator), denominator(x.denominator) {}


//************************************************************************
// 		fraction  类
//		其他成员函数
//************************************************************************


//************************************
// 函数功能：fraction 对对象中的分数取相反数
// 参数: selfAlteration: (bool) 取反是否改变对象的值,若为false，仅返回相反数；若为true，在返回相反数的同时对对象自身的分数取负。默认值为true
// 返回值: （fraction) 返回取相反数后的分数结果
//************************************
fraction fraction::inverse(bool selfAlteration) {
	fraction ret = *this;
	ret.numerator = -numerator;
	if(selfAlteration) numerator = -numerator; 
	return ret;
}


//************************************
// 函数功能：fraction 对对象中的分数取倒数
// 参数:  selfAlteration: (bool) 求倒数是否改变对象的值,若为false，仅返回倒数；若为true，在返回倒数的同时对对象自身的分数取倒数。默认值为true
// 返回值: （fraction) 返回取倒数后的分数结果
//************************************
fraction fraction::reciprocal(bool selfAlteration) {
	fraction ret = *this;
	bInt tmp = ret.numerator;
	ret.numerator = ret.denominator;
	ret.denominator = tmp;
	if (ret.denominator < bInt(0)) {
		ret.denominator = -ret.denominator;
		ret.numerator = -ret.numerator;
	}
	if (selfAlteration) *this = ret;
	return ret;
}

//************************************
// 函数功能：fraction 对对象中的分数进行约分
// 参数:  selfAlteration: (bool) 约分是否改变对象的值,若为false，仅返回最简分数；若为true，在返回最简分数的同时对对象自身的分数约分。默认值为true
// 返回值: （fraction) 返回约分后的分数结果
//************************************
fraction fraction::reduction(bool selfAlteration) {
	fraction ret = *this;
	bInt numeratorAbs = (ret.numerator < bInt(0)) ? -ret.numerator : ret.numerator;
	bInt denominatorAbs = (ret.denominator < bInt(0)) ? -ret.denominator : ret.denominator;
	bInt gcdValue = gcd(numeratorAbs, denominatorAbs);
	ret.numerator = ret.numerator / gcdValue;
	ret.denominator = ret.denominator / gcdValue;
	if (selfAlteration) *this = ret;
	return ret;
}

//************************************
// 函数功能：fraction 对对象中的分数进行输出
// 参数: outputStream: (T&) 输出流的引用, T默认为std::ostream, 参数默认值取std::cout
//************************************
template<typename ostreamTypeName>void fraction::print(ostreamTypeName& outputStream) {
	if (denominator == bInt(0)) outputStream <<" 分母为0，结果无效";
	else outputStream << numerator.toString() << "/" << denominator.toString();
}

//************************************
// 函数功能：fraction 通分(普通函数形式)
// 参数:
// sourceFirst: (fraction&) 参与运算的数字
// sourceSecond: (fraction&) 参与运算的数字
//************************************
void fraction::synchronizeDenominator(fraction& sourceFirst, fraction& sourceSecond) {
	sourceFirst & sourceSecond;
}


//************************************
// 函数功能：fraction 取两个大数(bigInteger)的最大公约数
// 参数:
// x: (fraction::bigInteger) 参与运算的数字
// y: (fraction::bigInteger) 参与运算的数字
// 返回值: （fraction::bigInteger) 两个大数的最大公约数
//************************************
inline fraction::bInt fraction::gcd(bInt x, bInt y) {
	bInt temp;
	while (y>0) {
		temp = x % y;
		x = y;
		y = temp;
	}
	return x;
}

//************************************
// 函数功能：fraction 取两个大数(bigInteger)的最小公倍数
// 参数:
// x: (fraction::bigInteger) 参与运算的数字
// y: (fraction::bigInteger) 参与运算的数字
// 返回值: （fraction::bigInteger) 两个大数的最小公倍数
//************************************
inline fraction::bInt fraction::lcm(bInt x, bInt y) {
	return x * y / gcd(x, y);
}

//************************************
// 函数功能：fraction 将小数字符串代表的分数赋值给对象
// 参数:
// sourceString: (const char*) 小数字符串
// doReduction: (bool) 是否对结果进行约分,默认为true
//************************************
void fraction::loadFromStr(const char* sourceString, bool doReduction) { 
	bInt numeratorValue = 0, decimalSize = 1;
	int len = strlen(sourceString);
	bool negative = false, findDot = false;
	for (int i = len - 1; i != 0; i--) {
		if (sourceString[i] == '.') {
			findDot = true;
			break;
		}
		decimalSize *= bInt(10);
	}
	if (!findDot)decimalSize = 1;
	for (int i = 0; i < len; i++) {
		if (sourceString[i] == '-') {
			negative = true;
			continue;
		}
		if (sourceString[i] == '+' || sourceString[i] == '(' || sourceString[i] == ')' || sourceString[i] == '.') continue;
		numeratorValue = numeratorValue * bInt(10) + (bInt)((long long)(sourceString[i] - '0'));
	}
	numerator = negative ? -numeratorValue : numeratorValue;
	denominator = decimalSize;
	if (doReduction)reduction();
}

//************************************
// 函数功能：fraction 将分数字符串代表的分数赋值给对象，分母和分子支持小数
// 参数:
// sourceString: (const char*) 分数字符串
// doReduction: (bool) 是否对结果进行约分,默认为false
//************************************
void fraction::loadFromStr2(const char* sourceString, bool doReduction) {
	int i = 0, len = strlen(sourceString);
	bInt lr = 0, lrx = 0, rr = 0, rrx = 0, newNume = 0, newDeno = 0;
	bool negative = false;
	for (; sourceString[i] != '/'; i++) {
		lr += lrx;
		if (sourceString[i] == '-') {
			negative = true;
			continue;
		}
		if (sourceString[i] == '+' || sourceString[i] == '(' || sourceString[i] == ')')continue;
		if (sourceString[i] == '.') {
			lrx = 1;
			continue;
		}
		newNume = newNume * 10 + (bInt)((long long)(sourceString[i] - '0'));
		
	}
	for (i++; i < len; i++) {
		rr += rrx;
		if (sourceString[i] == '-') {
			negative = !negative;
			continue;
		}
		if (sourceString[i] == '+' || sourceString[i] == '(' || sourceString[i] == ')')continue;
		if (sourceString[i] == '.') {
			rrx = 1;
			continue;
		}
		newDeno = newDeno * 10 + bInt((long long)(sourceString[i] - '0'));
	}
	if (lr > rr) {
		for (int j = 1; bInt(j) <= (lr - rr); j++)  newDeno *= 10;

	}
	else if (rr > lr) {
		for (int j = 1; bInt(j) <= (rr - lr); j++) newNume *= 10;
	}
	numerator = negative ? -newNume : newNume;
	denominator = newDeno;
	if (doReduction)reduction();
}

//************************************
// 函数功能：fraction 判断一个字符串类型是分数还是普通的小数串
// 参数: sourceString: (const char*) 需要进行判定的字符串
// 返回值: (bool) 若为分数字符串(允许分子分母有小数)，返回true；若为小数字符串，返回false
//************************************
bool fraction::judgeStrType(const char* sourceString) {
	return (strstr(sourceString, "/") != NULL);
}

//************************************
// 函数功能：fraction 将分数结果转化为小数 (便于与普通计算器进行结果比对)
// 参数:  accuracy: (int) 可选，小数的精度。默认值为5
// 返回值: (std::string) 分数的小数表示形式
//************************************
string fraction::toDecimalString(int accuracy) {
	string ret = numerator.divisionDecimal(numerator, denominator,accuracy);
	return ret;
}

//************************************
// 函数名称：fraction::operator &
// 函数功能：fraction 通分运算
// 参数: x: (fraction&) 对此参数和this进行通分
//************************************
void fraction::operator & (fraction& x) {
	bInt lcmValue = lcm(this->denominator, x.denominator);
	bInt a = lcmValue / (this->denominator);
	bInt b = lcmValue / x.denominator;
	this->numerator *= a;	x.numerator *= b;
	this->denominator = lcmValue;	x.denominator = lcmValue;
}

//************************************************************************
// 		fraction  类
//		算术运算符重载
//************************************************************************

fraction fraction::operator + (const fraction& x) {
	bInt lcmValue = lcm(this->denominator, x.denominator);
	bInt a = lcmValue / (this->denominator);
	bInt b = lcmValue / x.denominator;
	bInt newNumerator = this->numerator*a + (bInt)(x.numerator) * b;
	bInt newDenominator = lcmValue;
	fraction result(newNumerator, newDenominator);
	result.reduction();
	return result;
}
fraction fraction::operator - (const fraction& x) {
	fraction tmp(x);
	tmp.numerator = -tmp.numerator;
	fraction result = *this + tmp;
	result.reduction();
	return result;
}
fraction fraction::operator *(const fraction& x) {
	fraction tmp(this->numerator*x.numerator, this->denominator*x.denominator);
	tmp.reduction();
	return tmp;
}
fraction fraction::operator /(const fraction& x) {
	fraction tmp(this->numerator*x.denominator, this->denominator*x.numerator);
	tmp.reduction();
	return tmp;
}
fraction fraction::operator -() { fraction result(-(this->numerator), this->denominator); return result; }
fraction fraction::operator +() { fraction result(this->numerator, this->denominator); return result; }

fraction fraction::operator +(double x) { fraction x2 = fraction(x); return *this + x2; }
fraction fraction::operator -(double x) { fraction x2 = fraction(x); return *this - x2; }
fraction fraction::operator *(double x) { fraction x2 = fraction(x); return *this * x2; }
fraction fraction::operator /(double x) { fraction x2 = fraction(x); return *this / x2; }

fraction operator + (double x, const fraction& y) { fraction x1 = fraction(x); return x1 + y; }
fraction operator - (double x, const fraction& y) { fraction x1 = fraction(x); return x1 - y; }
fraction operator * (double x, const fraction& y) { fraction x1 = fraction(x); return x1 * y; }
fraction operator / (double x, const fraction& y) { fraction x1 = fraction(x); return x1 / y; }

//************************************************************************
// 		fraction  类
//		关系运算符重载
//************************************************************************

bool fraction::operator > (const fraction& x) { return (*this - x).numerator > bInt(0); }
bool fraction::operator < (const fraction& x) { return (*this - x).numerator < bInt(0); }
bool fraction::operator >= (const fraction& x) { return (*this - x).numerator >= bInt(0); }
bool fraction::operator <= (const fraction& x) { return (*this - x).numerator <= bInt(0); }
bool fraction::operator == (const fraction& x) { return (*this - x).numerator == bInt(0); }
bool fraction::operator != (const fraction& x) { return !(*this == x); }

//************************************************************************
// 		fraction  类
//		赋值运算符重载
//************************************************************************

fraction& fraction::operator +=(const fraction& x) { (*this) = (*this) + x;  return (*this); }
fraction& fraction::operator -=(const fraction& x) { (*this) = (*this) - x;  return (*this); }
fraction& fraction::operator *=(const fraction& x) { (*this) = (*this) * x;  return (*this); }
fraction& fraction::operator /=(const fraction& x) { (*this) = (*this) / x;  return (*this); }

//************************************************************************
// 		fraction  类
//		输出流重载
//************************************************************************
ostream& operator << (ostream& op, const fraction& x) {
	if (((fraction)x).denominator == fraction::bInt(0)) op << " 分母为0，结果无效";
	else op << ((fraction)x).numerator.toString() << "/" << ((fraction)x).denominator.toString();
	return op;
}
//************************************************************************
// 		fraction  类
//		输入流重载
//************************************************************************
istream& operator >> (istream& ip, fraction& x) {
	string tmp;
	ip >> tmp; x = fraction(tmp);
	return ip;
}

//************************************************************************
// 		fraction 类的测试过程
//************************************************************************

//fraction 测试类 (记录用户的输入与控制台输出到文件，避免main()中重复内容过多）
class fractionTest {
public:
	ofstream output,outputSimple,inputRec;
	bool outputStat, outputSimpleStat, inputRecStat;
	int rtnVal(int x) {
		return x; 
	} 
	//************************************
	// 将文字同时输出到控制台与文件
	//************************************
	template <typename T,int isExplicit = 0> void print(T outputInfo, bool endWithCRLF = true, bool hideConsoleOutput = false) {
		if (endWithCRLF) {
			if (rtnVal(isExplicit) != 2 && output.fail() == false )output << outputInfo << endl;
			if (!hideConsoleOutput)cout << outputInfo << endl;
			if (rtnVal(isExplicit) && outputSimple.fail() == false )outputSimple << outputInfo << endl;
		}
		else {
			if (rtnVal(isExplicit) != 2 && output.fail() == false)output << outputInfo;
			if (!hideConsoleOutput)cout << outputInfo;
			if (rtnVal(isExplicit) && outputSimple.fail() == false)outputSimple << outputInfo ;
		}
	}
	//************************************
	// 输出当前是第caseId次测试的标识，用于分隔
	//************************************
	void switchTestCase(int caseId) {
		print<string,1>("");
		print<string, 1>("******************************************************");
		print<string, 1>("		测试 #", false);
		print<int, 1>(caseId);
		print<string, 1>("******************************************************");
		inputRec << "####### Test Case - #"<< caseId<< " 输入变量的值 ########" << endl;
	}
	//************************************
	// 对储存完整输出的文件输出流对象设定文件
	//************************************
	void setOutputFile(string filePath) {
		output.open(filePath);
		if(output.fail()==false)outputStat = 1; 
	}
	//************************************
	// 对储存简明输出的文件输出流对象设定文件
	//************************************
	void setSimpleOutputFile(string filePath) {
		outputSimple.open(filePath);
		if(outputSimple.fail()==false)outputSimpleStat = 1;
	}
	//************************************
	// 对储存输入记录的文件输出流对象设定文件
	//************************************
	void setInputRecordFile(string filePath) {
		inputRec.open(filePath);
		if(inputRec.fail()==false)inputRecStat = 1; 
	}
	//************************************
	// 读取输入，并将【变量的值】写入输入记录
	//************************************
	template <typename T, typename T2 = string> void read(T2 description, T& destination) {
		cout << description;
		while (!(cin >> destination)) {
			cin.clear();
			while (cin.get() != '\n')continue;
			cout << "	输入无效，请重新输入:";
		}
		print<string>("", false, true);
		print<T2>(description, false, true);
		print<string>("【输入】:", false, true);
		print<T>(destination, true, true);
		inputRec << destination << endl;
	}
	//************************************
	// 读取输入，并将变量的值写入输入记录(指针类型)
	//************************************
	template <typename T, typename T2 = string> void readPtr(T2 description, T destination) {
		cout << description;
		cin >> destination;
		cin.clear();
		print<string>("", false, true);
		print<T2>(description, false, true);
		print<string>("【输入】:", false, true);
		print<T>(destination, true, true);
		inputRec << destination << endl;
	}
	//************************************
	// 输出操作ID
	//************************************
	void showOperationId() {
		cout << "操作id:\n1-取负\n2-取倒数\n3-约分" << endl;
		cout << "4-加减乘除运算\n5-通分" << endl;
		cout << "6-关系比较\n7-输入输出(double 和 字符串) 和 显示输出函数测试\n0-结束" << endl;
	}
	//************************************
	// 关闭文件输出流
	//************************************
	void fileClose(){
		if (outputStat)output.close();
		if (inputRecStat)inputRec.close();
		if (outputSimpleStat)outputSimple.close();
	}
	//************************************
	// 读取fraction, 避免main()中的重复内容过多
	//************************************
	void fractionReadIn(fraction& fractionAcceptant, double& doubleAcceptant, string& stringAcceptant, char* charPtrAcceptant, string prefix="输入:",bool testReadAndPrint =false) {
		int typeSelected;
		if (testReadAndPrint) {
			read<int>("	确定输入类型 (double为1，string为2, char*为3, 通过重载输入流为4): ", typeSelected);
			print<string, 2>(prefix, false, true);
			if (typeSelected == 1) {
				read<double>("	输入分数(double,仅允许小数): ", doubleAcceptant);
				print<double, 2>(doubleAcceptant, false, true);
				fractionAcceptant = doubleAcceptant;
			}
			else if (typeSelected == 2) {
				read<string>("	输入分数(string,允许小数和分数): ", stringAcceptant);
				fractionAcceptant = stringAcceptant;
				print<string, 2>(stringAcceptant, false, true);
			}
			else if (typeSelected == 3) {
				readPtr<char*>("	输入分数(char*,允许小数和分数): ", charPtrAcceptant);
				fractionAcceptant = charPtrAcceptant;
				print<char*, 2>(charPtrAcceptant, false, true);
			}
			else if (typeSelected == 4) {
				read<fraction>("	输入分数(fraction,允许小数和分数): ", fractionAcceptant);
				print<fraction, 2>(fractionAcceptant, false, true);
			}
			print<string, 2>(" [ ", false, true);
			print<fraction, 2>(fractionAcceptant, false, true);
			print<string, 2>(" ]", true, true);
		}
		else {
			print<string, 2>(prefix, false, true);
			read<string>("	输入一个分数(小数或分数型均可): ", stringAcceptant);
			fractionAcceptant = stringAcceptant;
			print<string, 2>(stringAcceptant, false, true);
			print<string, 2>(" [ ", false, true);
			print<fraction, 2>(fractionAcceptant, false, true);
			print<string, 2>(" ]", true, true);
		}
	}
};  

//main 函数 (测试主过程)
int main() {
	fraction expr[10]; //创建分数类(fraction)的对象
	fractionTest fTest;
	fTest.setOutputFile("fraction_output_full.txt"); //完整输出内容：所有 控制台输出 与 用户输入
	fTest.setInputRecordFile("fraction_input_record.txt");//完整输入内容：所有 用户输入
	fTest.setSimpleOutputFile("fraction_output_explicit.txt");//简明输出内容：重要的控制台输出 与 输入

	int nextOperation, operationCounts = 0, readOperator=0;
	double readDouble[3];
	string readString[3];
	char** readCharPtr = new char*[3];
	bool comparisonResult;
	for (int i = 0; i < 3; i++) readCharPtr[i] = new char[1000]; //初始化用于读取的char*数组

	//开始测试
	fTest.showOperationId();
	while (1) {
		fTest.switchTestCase(++operationCounts);
		fTest.read<int>("输入需要的操作id:", nextOperation);
		if (!nextOperation) break;
		switch (nextOperation) {

		// 1 - 取负运算（inverse）测试 
		case 1:
			fTest.print<string,1>("测试：分数取负");
			fTest.print<string>("输入进行取负的分数:");
			fTest.fractionReadIn(expr[0], readDouble[0], readString[0], readCharPtr[0]);

			expr[0].inverse();//取负运算

			fTest.print<string,1>("");
			fTest.print<string,1>("取负(inverse)结果为:", false);
			fTest.print<fraction,1>(expr[0]);
			break;

		// 2 - 取倒数（reciprocal）测试
		case 2:
			fTest.print<string,1>("测试：分数取倒数");
			fTest.print<string>("输入进行取倒数的分数:");
			fTest.fractionReadIn(expr[0], readDouble[0], readString[0], readCharPtr[0]);

			expr[0].reciprocal(); //倒数运算

			fTest.print<string,1>("");
			fTest.print<string,1>("倒数(reciprocal)结果为:", false);
			fTest.print<fraction,1>(expr[0]);
			break;

		// 3 - 约分（reduction）测试
		case 3:
			fTest.print<string,1>("测试：分数约分");
			fTest.print<string>("输入进行约分的分数:");
			fTest.fractionReadIn(expr[0], readDouble[0], readString[0], readCharPtr[0]);

			expr[0].reduction(); //约分运算

			fTest.print<string,1>("");
			fTest.print<string,1>("约分(reduction)结果为:", false);
			fTest.print<fraction,1>(expr[0]);
			break;

		// 4 - 加减乘除运算
		case 4:
			fTest.print<string,1>("测试：加减乘除运算 (按步执行)");
			fTest.print<string>("输入初始值:");
			fTest.fractionReadIn(expr[0], readDouble[0], readString[0], readCharPtr[0],"初始值	");
			while (1) {
				fTest.read<int>("输入需要的运算ID:+(1) -(2) *(3) /(4) 取负(5) 倒数(6) 约分(7) 通分(8) 终止(0) :\n	运算符ID:", readOperator);
				if (!readOperator) break;
				switch (readOperator) {
				case 1:
					fTest.print<string>("+：输入加数:");
					fTest.fractionReadIn(expr[1], readDouble[1], readString[1], readCharPtr[1],"+	");
					expr[0] = expr[0] + expr[1];
					break;
				case 2:
					fTest.print<string>("-：输入减数:");
					fTest.fractionReadIn(expr[1], readDouble[1], readString[1], readCharPtr[1], "-	");
					expr[0] = expr[0] - expr[1];
					break;
				case 3:
					fTest.print<string>("*：输入乘数:");
					fTest.fractionReadIn(expr[1], readDouble[1], readString[1], readCharPtr[1],  "*	");
					expr[0] = expr[0] * expr[1];
					break;
				case 4:
					fTest.print<string>("/：输入除数:");
					fTest.fractionReadIn(expr[1], readDouble[1], readString[1], readCharPtr[1],  "/	");
					expr[0] = expr[0] / expr[1];
					break;
				case 5:
					fTest.print<string,1>("执行 取负");
					expr[0] = -expr[0];
					break;
				case 6:
					fTest.print<string,1>("执行 倒数");
					expr[0].reciprocal();
					break;
				case 7:
					fTest.print<string,1>("执行 约分");
					expr[0].reduction();
					break;
				case 8:
					fTest.print<string>("通分，输入另一个分数用于通分:");
					fTest.fractionReadIn(expr[1], readDouble[1], readString[1], readCharPtr[1],"与数通分	");
					expr[0] & expr[1];
					break;
				}
				fTest.print<string>("此步骤完成后结果:", false);
				fTest.print<fraction>(expr[0]);
				fTest.print<string>("");
			}
			fTest.print<string,1>("最终结果是:", false);
			fTest.print<fraction,1>(expr[0]);
			break;

		// 5 - 通分
		case 5:
			fTest.print<string,1>("测试:分数通分");
			fTest.print<string>("输入第1个分数 / 共2个:");
			fTest.fractionReadIn(expr[0], readDouble[0], readString[0], readCharPtr[0]);
			fTest.print<string>("输入第2个分数 / 共2个:");
			fTest.fractionReadIn(expr[1], readDouble[1], readString[1], readCharPtr[1]);

			expr[0] & expr[1]; //通分运算

			fTest.print<string,1>("");
			fTest.print<string,1>("通分后，第1个分数结果为:", false);
			fTest.print<fraction,1>(expr[0]);
			fTest.print<string,1>("通分后，第2个分数结果为:", false);
			fTest.print<fraction,1>(expr[1]);
			break;

		// 6 - 关系运算比较
		case 6:
			fTest.print<string,1>("测试:关系运算 (大小于，等于不等于):");
			fTest.print<string>("输入第1个分数 / 共2个:");
			fTest.fractionReadIn(expr[0], readDouble[0], readString[0], readCharPtr[0]);
			fTest.read<int>("输入关系运算符ID:>(1),<(2),>=(3),<=(4),==(5),!=(6):\n	运算符ID:",readOperator);
			fTest.print<string>("输入第2个分数 / 共2个:");
			fTest.fractionReadIn(expr[1], readDouble[1], readString[1], readCharPtr[1]);
			
			switch (readOperator){
			case 1:
				comparisonResult = expr[0] > expr[1];
				fTest.print<string, 2>("运算符:>", true, true);
				break;
			case 2:
				comparisonResult = expr[0] < expr[1];
				fTest.print<string, 2>("运算符:<", true, true);
				break;
			case 3:
				comparisonResult = expr[0] >= expr[1];
				fTest.print<string, 2>("运算符:>=", true, true);
				break;
			case 4:
				comparisonResult = expr[0] <= expr[1];
				fTest.print<string, 2>("运算符:<=", true, true);
				break;
			case 5:
				comparisonResult = expr[0] == expr[1];
				fTest.print<string, 2>("运算符:==", true, true);
				break;
			case 6:
				comparisonResult = expr[0] != expr[1];
				fTest.print<string, 2>("运算符:!=", true, true);
				break;
			default:
				fTest.print<string, 2>("使用的运算符ID无效", true, true);
				comparisonResult = 0;
			}
			fTest.print<string,1>("");
			fTest.print<string,1>("比较结果为：");
			fTest.print<string,1>(comparisonResult ? "True" : "False");
			break;
		//7 - 测试输入输出(double 和字符串类型)
		case 7:
			fTest.print<string, 1>("测试:输入和输出");
			fTest.print<string>("输入一个分数:");
			fTest.fractionReadIn(expr[0], readDouble[0], readString[0], readCharPtr[0],"输入:",true);

			fTest.print<string, 1>("");
			fTest.print<string, 1>("显示函数的输出结果为：");

			expr[0].print(); //输出到控制台
			expr[0].print<ofstream>(fTest.output); //将显示函数的输出结果输出到 输出文件
			expr[0].print<ofstream>(fTest.outputSimple); //将显示函数的输出结果输出到 简要输出文件

			fTest.print<string, 1>("");
			break;
		default:
			fTest.print<string, 1>("测试: 无效");
		}
	}
	fTest.print<string,1>("测试结束");

	//释放new得到的变量，关闭文件
	for (int i = 0; i < 3; i++) delete[] readCharPtr[i];
	delete[] readCharPtr;
	fTest.fileClose();
	return 0;
}