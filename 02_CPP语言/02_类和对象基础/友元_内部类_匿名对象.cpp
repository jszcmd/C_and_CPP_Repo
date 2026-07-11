// CPP中的类: 友元，内部类，匿名对象，还有3个练习题。
// 代码写于2026年7月10日
// 博客写于: https://juejin.cn/post/7661085673139470363

// =====================================================================================================================
// 友元: 类外面去访问类里面的私有或者保护成员的一种方式。
// 1.使用友元函数访问和修改类的私有成员。

//#include <iostream>
//using std::cout;
//using std::endl;
//
//class Date
//{
//	friend void func(Date& d); // 声明友元函数
//	// 告诉编译器，func是Date类的友元函数，可以访问Date类的私有成员。
//public:
//
//	Date(int year, int month, int day) // 构造函数
//		: _year(year)
//		, _month(month)
//		, _day(day) 
//	{}
//
//	void Print() const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//// 现在我的这个函数就想要访问d的私有成员_year。
//void func(Date& d)
//{
//	d._year = 2028;
//	cout << d._year << endl;
//}
//
//int main()
//{
//	cout << "=====================================================" << endl;
//	Date d1(2026, 7, 10);
//	d1.Print();
//	cout << "======================================================" << endl;
//	func(d1); // 调用友元函数,可以访问d1的私有成员_year。
//	d1.Print();
//	return 0;
//}

// =====================================================================================================================
// 友元函数实现: cout << 自定义类型

// ***********************************************************************************
// 1.在自定义类型的类里面重载<<运算符
// 但是这个不符合习惯,因为cout是左操作数,自定义类型是右操作数。

// cout 是标准库std命名里面的一个ostream类型的全局对象。
// cout 的类型是ostream

//#include <iostream>
//
//using std::cout;
//using std::endl;
//using std::ostream; // 使用ostream类。
//
//class Date
//{
//public:
//	Date(int year, int month, int day) // 构造函数
//		: _year(year)
//		, _month(month)
//		, _day(day) 
//	{}
//
//	void Print() const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//
//	// 重载<<运算符 <==> 调用: d1.operator<<(cout);
//	// 这样的情况下: d1 是左操作数,cout是右操作数。d1 << cout; 
//	void operator<<(ostream& out) // void operator<<(Date* this, ostream& out)
//	{
//		out << _year << "---" << _month << "---" << _day << endl;
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	cout << "======================================================" << endl;
//	// cout << 内置类型。
//	int a = 100;
//	cout << "a = " << a << endl;
//	cout << "======================================================" << endl;
//	Date d1(2026, 7, 10);
//	d1.operator<<(cout); // 调用方式1: 对象.方法()
//	d1 << cout; // 调用方式2: 对象 << 参数
//	// d1 是左操作数，cout是右操作数。d1.operator<<(cout); 
//	// 这样调用是可以的，但是不符合习惯。
//
//	return 0;
//}


// ***********************************************************************************
// 2.解决方法:写入到类外面,加上友元函数声明

//#include <iostream>
//
//using std::cout;
//using std::endl;
//using std::ostream; // 使用ostream类。
//
//class Date
//{
//
//	friend void operator<<(ostream& out, const Date& date_obj); // 声明友元函数
//	// operator<<(cout,date_obj) <==> cout 是左操作数，date_obj是右操作数。
//public:
//	Date(int year, int month, int day) // 构造函数
//		: _year(year)
//		, _month(month)
//		, _day(day) 
//	{}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//// 可以调用: operator<<(cout, date_obj); // cout 是左操作数，date_obj是右操作数。
//// 这里不改变date_obj的值,所以可以加上const修饰符。
//void operator<<(ostream& out,const Date& date_obj)
//{
//	out << date_obj._year << "年-" << date_obj._month << "月-" << date_obj._day <<"日" << endl;
//}
//
//int main()
//{
//	Date d1(2026, 7, 10);
//	cout << "======================================================" << endl;
//	// 调用operator<<函数输出。
//	operator<<(cout, d1); // 调用方式1: 函数名(参数1, 参数2)
//	cout << "======================================================" << endl;
//	cout << d1; // 调用方式2: cout << d1;
//	cout << "======================================================" << endl;
//	// 自定义的类型,可以支持链式输出。
//	int i = 520, j = 1314;
//	cout << "输出:" << i << j << endl;
//	cout << "=======================================================" << endl;
//
//	return 0;
//}


// ***********************************************************************************
// 3.优化: 支持链式输出

// cout 是标准库std命名里面的一个ostream类型的全局对象。
// cout 的类型是ostream
// cin 的类型是istream

//#include <iostream>
//
//using std::cout;
//using std::endl;
//using std::ostream; // 使用ostream类。
//
//class Date
//{
//	friend ostream& operator<<(ostream& out, const Date& date_obj); // 声明友元函数
//public:
//	Date(int year, int month, int day) // 构造函数
//		: _year(year)
//		, _month(month)
//		, _day(day)
//	{}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//ostream& operator<<(ostream& out, const Date& date_obj)
//{
//	out << date_obj._year << "年-" << date_obj._month << "月-" << date_obj._day << "日" << endl;
//	return out; // 返回cout对象的引用, 这样可以实现链式输出。
//}
//
//int main()
//{
//	cout << "======================================================" << endl;
//	// 内置类型的链式输出。
//	int i = 250, j = 250;
//	cout << i << j << endl;
//	cout << "======================================================" << endl;
//	// 自定义类型的链式输出。
//	Date d1(2026, 7, 10);
//	Date d2(2024, 6, 10);
//	cout << "自定义类型的链式输出:" << endl;
//	cout << d1 << d2;
//	cout << "======================================================" << endl;
//	// 自定义类型和内置类型的混合的链式输出。
//	cout << i << d1 << j << d2 << endl; // 链式输出
//
//	return 0;
//}

// ***********************************************************************************
// 4. 为什么cout能识别不同的类型。

//#include <iostream>
//using std::cout;
//using std::endl;
//
//int main()
//{
//	int x = 1;
//	double y = 1.11;
//	cout << x << endl; // cout.operator<<(&cout ,int val);
//	cout << y << endl; // cout.operator<<(&cout ,double val);
//	// C++ 的cout 可以实现不同类型的输出 <==> 函数的重载
//	// 为什么能够自动识别类型 <==> 函数的重载
//	return 0;
//}

// =====================================================================================================================
// 友元函数实现: 实现 cin >> d1 >> d2; 也就是链式输入

//#include <iostream>
//
//// cout 是标准库std命名里面的一个ostream类型的全局对象。
//// cin 是标准库std命名里面的一个istream类型的全局对象.
//// cout 的类型是ostream
//// cin 的类型是istream
//
//using std::cout;
//using std::endl;
//using std::cin;
//using std::ostream;
//using std::istream;
//
//class Date
//{
//	friend ostream& operator<<(ostream& out, const Date& date_obj); // 声明友元函数
//	friend istream& operator>>(istream& in, Date& date_obj); // 声明友元函数
//public:
//	Date(int year = 0, int month = 0, int day = 0) // 构造函数
//		: _year(year)
//		, _month(month)
//		, _day(day)
//	{}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//ostream& operator<<(ostream& out, const Date& date_obj)
//{
//	out << date_obj._year << "年-" << date_obj._month << "月-" << date_obj._day << "日" << endl;
//	return out; // 返回cout对象的引用
//}
//
//// 都是以空格,或者是换行作为分隔符的。
//// Date& date_obj 这里要加引用,要修改date_obj的值,所以不能加const修饰符。
//istream& operator>>(istream& in, Date& date_obj)
//{
//	in >> date_obj._year >> date_obj._month >> date_obj._day;
//	return in; // 返回cin对象的引用, 这样可以实现链式输入。
//}
//
//
//int main()
//{
//	cout << "======================================================" << endl;
//	Date d1;
//	Date d2;
//	// 使用空格,换行符都可以分割。
//	cin >> d1 >> d2; // 链式输入
//	cout << d1 << d2; // 链式输出
//	cout << "======================================================" << endl;
//	return 0;
//}


// =====================================================================================================================
// 友元类.

//class Date; // 前置声明
//
//class Time
//{
//    friend class Date; // 声明日期类为时间类的友元类，则在日期类中就直接访问Time类中的私有成员变量
//public:
//    Time(int hour = 0, int minute = 0, int second = 0)
//        : _hour(hour)
//        , _minute(minute)
//        , _second(second)
//    {}
//
//private:
//    int _hour;
//    int _minute;
//    int _second;
//};
//
//class Date
//{
//public:
//    Date(int year = 1900, int month = 1, int day = 1)
//        : _year(year)
//        , _month(month)
//        , _day(day)
//    {}
//
//    void SetTimeOfDate(int hour, int minute, int second) // 直接访问时间类私有的成员变量
//    {
//        _t._hour = hour;
//        _t._minute = minute;
//        _t._second = second;
//    }
//
//private:
//    int _year;
//    int _month;
//    int _day;
//    Time _t;
//};


// =====================================================================================================================
// 内部类: 在类里面定义的类,称为内部类,也称为嵌套类。

//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//    class B
//    {
//    public:
//        void foo(const A& a)
//        {
//            cout << k << endl;
//            cout << a.h << endl;
//        }
//    };
//	// B 天生就是 A 的友元类,所以 B 可以访问 A 的私有成员。
//
//private:
//    static int k;
//    int h;
//};
//
//int A::k = 1;
//
//int main()
//{
//	A::B b; // 创建 A 的内部类 B 的对象 b
//    b.foo(A());
//
//    return 0;
//}


// =====================================================================================================================
// 匿名对象

//#include <iostream>
//using namespace std;
//
//class Solution
//{
//public:
//    Solution()
//    {
//		cout << "Solution()构造函数被调用" << endl;
//    }
//    ~Solution()
//    {
//		cout << "~Solution()析构函数被调用" << endl;
//    }
//    int sum_solution(int target)
//    {
//        return target;
//    }
//};
//
//int main()
//{
//	cout << "=================================" << endl;
//    Solution s1; // s1的声明周期在main函数里面。
//    s1.sum_solution(10);
//	cout << "=================================" << endl;
//	//Solution(); // 匿名对象, 也就是没有名字的对象, 只能使用一次, 不能重复使用。
//	Solution().sum_solution(20); // 只有我这一行会使用这个创建对象,别人不需要使用。
//	// 这个匿名对象的生命周期在这一行代码执行完毕之后就会被销毁。
//	cout << "=================================" << endl;
//	return 0;
//}


// =====================================================================================================================
// 练习题1: 计算日期到天数的转换
// https://www.nowcoder.com/practice/769d45d455fe40b385ba32f97e7bcded?tpId=37&&tqId=21296&rp=1&ru=/activity/oj&qru=/ta/huawei/question-ranking

// ***********************************************************************************
// 1. 处理一次输入输出

//#include <iostream>
//using namespace std;
//
//int main()
//{
//	static int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//	int year, month, day;
//	cin >> year >> month >> day;
//	int n = 0;
//
//	// 累加从1月到month-1月的天数
//	for (int i = 1; i < month; ++i) 
//	{
//		n += daysInMonth[i];
//	}
//
//	n += day; // 累加上month月的天数
//
//	// 考虑闰年,并且月份大于2月的情况。
//	if (month > 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
//	{
//		n += 1; // 如果是闰年且月份大于2月，则加一天
//	}
//
//	cout << n << endl;
//
//	return 0;
//}


// ***********************************************************************************
// 2. 处理多次输入输出

//#include <iostream>
//using namespace std;
//
//int main()
//{
//	static int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//	int year, month, day;
//	int n = 0;
//	// 这样可以不断的接收输入,直到按 ctrl + c 结束输入。
//    while (cin >> year >> month >> day) // 注意 while 处理多个 case
//    {
//		n = 0; // 清0.
//
//		// 累加从1月到month-1月的天数
//		for (int i = 1; i < month; ++i)
//		{
//			n += daysInMonth[i];
//		}
//		
//		n += day; // 累加上month月的天数
//		// 考虑闰年,并且月份大于2月的情况。
//		if (month > 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
//		{
//			n += 1; // 如果是闰年且月份大于2月，则加一天
//		}
//		cout << n << endl;
//    }
//	return 0;
//}

// ***********************************************************************************
// 3. 优化 + 完善。

//#include <iostream>
//using namespace std;
//
//inline bool IsLeapYear(int year)
//{
//	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
//}
//
//int GetMonthDay(int year, int month) // 获取某年某月的天数
//{
//	if (year == 0 && month == 0) // 年月都为0,表示默认值,返回0
//		return 0; // 返回0天
//	if (month < 1 || month > 12) // 月份不合法
//		return -1; // 返回-1表示月份不合法
//	static int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // 每个月的天数
//	if (month == 2 && IsLeapYear(year)) // 如果是2月且是闰年,只有29天
//		return 29; // 返回29天
//	return daysInMonth[month]; // 返回对应月份的天数
//}
//
//int main()
//{
//	static int daysInMonthSum[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
//	int year, month, day;
//	int n = 0;
//    while (cin >> year >> month >> day) // 注意 while 处理多个 case
//    {
//		if ((year >= 0) && (month >= 0 && month <= 12) && (day >= 0 && day <= GetMonthDay(year, month)))
//		{
//			n = 0; // 清0.
//			n += daysInMonthSum[month - 1]; // 累加从1月到month-1月的天数
//			n += day; // 累加上month月的天数
//			if (month > 2 && IsLeapYear(year))
//			{
//				n += 1; //闰年且月份大于2月，则加一天
//			}
//			cout << n << endl;
//		}
//		else
//		{
//			cout << "日期输入错误!" << endl;
//		}
//    }
//	return 0;
//}


// =====================================================================================================================
// 练习题2:

//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//	A()
//	{
//		cout << "A()构造函数被调用" << endl;
//	}
//	~A()
//	{
//		cout << "~A()析构函数被调用" << endl;
//	}
//private:
//
//};
//
//class B
//{
//public:
//	B()
//	{
//		cout << "B()构造函数被调用" << endl;
//	}
//	~B()
//	{
//		cout << "~B()析构函数被调用" << endl;
//	}
//private:
//
//};
//
//class C
//{
//public:
//	C()
//	{
//		cout << "C()构造函数被调用" << endl;
//	}
//	~C()
//	{
//		cout << "~C()析构函数被调用" << endl;
//	}
//private:
//
//};
//
//class D
//{
//public:
//	D()
//	{
//		cout << "D()构造函数被调用" << endl;
//	}
//	~D()
//	{
//		cout << "~D()析构函数被调用" << endl;
//	}
//private:
//
//};
//
//C c; // 全局对象
//int main()
//{
//	A a;
//	B b;
//	// 在main结束的时候析构。
//
//	static D d; // 局部的静态对象,第一次到这个地方的时候,才会初始化它。
//	// d在main之前就定义了,在main函数之后就会被调用析构函数。
//	// 但是它的声明周期是全局的,整个main期间都在,程序结束之后的时候才会被析构。
//}
//// 局部对象先析构,全局对象和静态对象再析构。
//
////C()构造函数被调用
////A()构造函数被调用
////B()构造函数被调用
////D()构造函数被调用
////~B()析构函数被调用
////~A()析构函数被调用
////~D()析构函数被调用
////~C()析构函数被调用


// =====================================================================================================================
// 练习题3: 调用了多少次拷贝构造函数。

// 优化都发生在返回和传参时。

// ***********************************************************************************
// 案例1: 

//#include <iostream>
//using namespace std;
//
//int n = 0; // 全局变量, 用来统计拷贝构造函数被调用的次数。
//
//class Widget
//{
//public:
//	Widget() // 默认构造函数
//	{
//		/*cout << "Widget()构造函数被调用" << endl;*/
//	}
//	Widget(const Widget& other) // 拷贝构造函数
//	{
//		n += 1; // 每次调用拷贝构造函数,就加1
//		cout << "Widget(const Widget&)拷贝构造函数被调用" << endl;
//	}
//private:
//};
//
//Widget func(Widget u) // 传值调用拷贝构造函数 + 1
//{
//	Widget v(u); // 调用拷贝构造函数 + 1
//	Widget w = v; // 调用拷贝构造函数 + 1
//	return w; // 返回值调用拷贝构造函数 + 1
//}
//
//int main()
//{
//	Widget x; // 默认构造函数
//	Widget y = func(x); // 3 次。
//	// 理论上来说会发生 5 次拷贝构造函数的调用,但是编译器会进行优化,所以实际只发生了3次拷贝构造函数的调用。
//	cout << "================================================" << endl;
//	cout << "n  = " << n << endl; // 输出拷贝构造函数被调用的次数
//	return 0;
//}
////Widget(const Widget&)拷贝构造函数被调用
////Widget(const Widget&)拷贝构造函数被调用
////Widget(const Widget&)拷贝构造函数被调用
////================================================
////n = 3


// ***********************************************************************************
// 案例2: 

//#include <iostream>
//using namespace std;
//
//int n = 0; // 全局变量, 用来统计拷贝构造函数被调用的次数。
//
//class Widget
//{
//public:
//	Widget() // 默认构造函数
//	{
//		/*cout << "Widget()构造函数被调用" << endl;*/
//	}
//	Widget(const Widget& other) // 拷贝构造函数
//	{
//		n += 1; // 每次调用拷贝构造函数,就加1
//		cout << "Widget(const Widget&)拷贝构造函数被调用" << endl;
//	}
//private:
//};
//
//Widget func(Widget u) // 传值调用拷贝构造函数 + 1
//{
//	Widget v(u); // 调用拷贝构造函数 + 1
//	Widget w = v; // 调用拷贝构造函数 + 1
//	return w; // 返回值调用拷贝构造函数 + 1
//}
//
//int main()
//{
//	Widget x; // 默认构造函数
//	Widget y = func(func(x)); // 5 次。
//	// 理论上来说会发生 9 次拷贝构造函数的调用,但是编译器会进行优化,所以实际只发生了5次拷贝构造函数的调用。
//	cout << "================================================" << endl;
//	cout << "n  = " << n << endl; // 输出拷贝构造函数被调用的次数
//	return 0;
//}
////Widget(const Widget&)拷贝构造函数被调用
////Widget(const Widget&)拷贝构造函数被调用
////Widget(const Widget&)拷贝构造函数被调用
////Widget(const Widget&)拷贝构造函数被调用
////Widget(const Widget&)拷贝构造函数被调用
////================================================
////n = 5
