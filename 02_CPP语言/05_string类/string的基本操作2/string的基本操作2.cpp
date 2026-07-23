// 代码写于 2026年07月14日
// 笔记写于 2026年07月23日
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// string的基本操作2
// string类 ==> 管理字符的数组。
// 可以对它进行增删改查等操作。


// ===============================================================================================================
// 增加

// -------------------------------------- 1.尾部插入。

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	string s1("Hello");
//	string s2(" I'm fine.");
//	s1.push_back(' '); // 在字符串末尾添加一个字符。
//	// push_back插入一个字符。
//	s1.append("World"); // 在字符串末尾添加一个字符串。
//	// append插入一个字符串。
//	cout << "s1: " << s1 << endl; // 输出Hello World
//	// += 运算符可以插入一个字符/字符串/string对象。
//	s1 += '!';
//	s1 += " How are you?";
//	s1 += s2;
//	cout << "s1: " << s1 << endl; // 输出Hello World! How are you? I'm fine.
//	cout << "==============================================" << endl;
//	s1.resize(40, 'A');
//	cout << "s1: " << s1 << endl; // 输出Hello World! How are you?A
//	return 0;
//}


// -------------------------------------- 2.任意位置插入。
// insert() ==> 在任意位置插入字符或者字符串。

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	cout << "=============================================" << endl;
//	string s1("Hello");
//	cout << "s1: " << s1 << endl; 
//	cout << "=============================================" << endl;
//	s1.insert(s1.begin(), '0'); 
//	// 插入单个字符c
//	// 第一个参数参数为迭代器。
//	// 第二个参数为要插入的字符。 要使用单引号。
//	cout << "s1: " << s1 << endl; 
//	cout << "=============================================" << endl;
//	s1.insert(2, "_world"); // 插入s指向的以空字符结尾的C字符串副本
//	// 插入字符串。
//	// 第一个参数为要插入的位置的下标。
//	// 第二个参数为要插入的字符串。
//	cout << "s1: " << s1 << endl; 
//	cout << "=============================================" << endl;
//	return 0;
//}
//=============================================
//s1: Hello
//=============================================
//s1 : 0Hello
//=============================================
//s1 : 0H_worldello
//=============================================


// -------------------------------------- 3.operator+ 和 operator+= 

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//// 尽量使用 operator+= 来拼接字符串,因为它不会产生临时对象,效率更高。
//int main()
//{
//	string s1("Hello");
//	string res = s1 + " world"; 
//	// operator+ 重载了字符串的拼接操作,并返回拼接后的对象。
//	string res2 = (s1 += " world"); 
//	// operator+= 重载了字符串的拼接操作,并返回拼接后的对象的引用。
//	cout << res << endl; // Hello world
//	cout << res2 << endl; // Hello world
//}


// ===============================================================================================================
// 删除。

//// -------------------------------------- 删除所有的有效字符,清空字符串。 ==> clear()
//// 删除所有的有效字符,清空字符串。 ==> clear()
//// clear() : 删除所有的有效字符,清空字符串。
//// clear() : 清空字符串,只是把size这些变成0了,但是不改变容量。
//
//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	string s1("Hello world");
//	cout << "s1: " << s1 << endl; // 输出Hello
//	cout << "s1.size(): " << s1.size() << endl; // 输出11
//	cout << "s1.capacity(): " << s1.capacity() << endl; // 输出15
//	s1.clear(); // 删除所有的有效字符,清空字符串。
//	cout << "s1: " << s1 << endl; // 输出空字符串
//	cout << "s1.size(): " << s1.size() << endl; // 输出0
//	cout << "s1.capacity(): " << s1.capacity() << endl; // 输出15
//	return 0;
//}


// -------------------------------------- 删除指定位置的字符。
// erase 作用：删除字符串内指定字符，会减小有效长度 size ()，一共3 种重载形式。

//// 重载1：下标版本
//string& erase(size_t pos = 0, size_t len = npos);
//// 删除从pos开始的len个字符。
//// 参数1: pos 开始位置
//// 参数2: len 删除的字符数量 (缺省为npos，表示删除到字符串末尾)
//
//// 重载2：单个迭代器
//iterator erase(iterator p);
//// 删除迭代器p指向的单个字符
//// 参数1: p 迭代器，指向要删除的字符
//// 返回值: 返回指向被删除字符的下一个字符的迭代器
//
//// 重载3：区间迭代器 [first, last)
//iterator erase(iterator first, iterator last);
//// 删除迭代器first和last之间的所有字符
//// 参数1: first 迭代器，指向要删除的第一个字符
//// 参数2: last 迭代器，指向要删除的最后一个字符的下一个位置

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	cout << "=============================================" << endl;
//	string s1("Hello world");
//	// 删除从下标6开始的5个字符
//	s1.erase(6, 5); // 删除从下标6开始的5个字符
//	cout << "s1: " << s1 << endl; // 输出Hello
//	cout << "---------------------------------------------" << endl;
//	// len参数缺省，表示删除到字符串末尾
//	s1.erase(1); // 删除从下标5开始的所有字符。
//	cout << "s1: " << s1 << endl; // 输出H
//	cout << "=============================================" << endl;
//
//	cout << "=============================================" << endl;
//	// 删除迭代器指向的单个字符
//	string s2("Hello world");
//	s2.erase(s2.begin()); // 删除迭代器指向的单个字符
//	cout << "s2: " << s2 << endl; // 输出ello world
//	cout << "=============================================" << endl;
//
//	cout << "=============================================" << endl;
//	// 删除迭代器first和last之间的所有字符
//	string s3("Hello world");
//	s3.erase(s3.begin() + 1, s3.begin() + 5); // 删除迭代器first和last之间的所有字符
//	cout << "s3: " << s3 << endl; // 输出
//	cout << "=============================================" << endl;
//
//	return 0;
//}


// ===============================================================================================================
// 修改。

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	string s1("Hello");  // 创建一个string对象s1，并初始化为"Hello"
//	s1 += " world!"; // += 一个字符串
//	cout << s1 << endl; // 支持输出操作符<<。
//	cout << "================================" << endl;
//
//	// for + [] 遍历并修改。
//	for (size_t i = 0; i < s1.size(); ++i)
//	{
//		s1[i] += 1;
//		cout << s1[i] << " "; // 支持下标操作符[]。
//	}
//	cout << endl;
//	cout << "================================" << endl;
//
//	// 普通的迭代器遍历。 可以修改。
//	string::iterator it = s1.begin(); 
//	while (it != s1.end()) 
//	{
//		*it += 1; // 修改字符。
//		cout << *it << " "; 
//		++it; 
//	}
//	cout << endl;
//	cout << "================================" << endl;
//
//	// for 可以修改。
//	for (auto& e : s1)
//	{
//		e -= 2; // 修改字符。
//		cout << e << " "; // 直接访问每一个字符。
//	}
//	cout << endl;
//	cout << "================================" << endl;
//	return 0;
//}


// ===============================================================================================================
// 查询。

// find() ==> 查找字符串中某个字符或者子串的位置。
// rfind() ==> 从后往前查找字符串中某个字符或者子串的位置。


// -------------------------- 1. 取出文件名的后缀名

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//// size_t find (char c, size_t pos = 0) const;
//// 参数1: c 要查找的字符
//// 参数2: pos 从pos这个位置开始查找,缺省为0,表示从头开始查找。
//// 返回值: 
////     查找到返回字符在字符串中的下标位置,
////     如果没有查找到,返回string::npos(无符号整形的最大值)
//
//// substr(size_t pos = 0, size_t len = npos) const;
//// 参数1: pos 从pos这个位置开始取出字符,缺省为0,表示从头开始取出。
//// 参数2: len 取出len个字符,缺省为npos,表示取出从pos到末尾的所有字符。
//// 功能: 
////     从pos这个位置开始,取出len个字符,
////     如果len没有指定,则取出从pos到末尾的所有字符.
//
//int main()
//{
//	string s1("string.cpp");
//	string s2("string.c");
//	string s3("string.h");
//	size_t pos1 = s1.find("."); // 查找第一个'.'的位置
//	if (pos1 != string::npos)
//	{
//		cout << s1.substr(pos1 + 1) << endl;
//	}
//	size_t pos2 = s2.find(".");
//	if (pos2 != string::npos)
//	{
//		cout << s2.substr(pos2 + 1) << endl;
//	}
//	size_t pos3 = s3.find(".");
//	if (pos3 != string::npos)
//	{
//		cout << s3.substr(pos3 + 1) << endl;
//	}
//	
//	string s4("string.cpp.zip.tar");
//	size_t pos4 = s4.find("."); 
//	if (pos4 != string::npos)
//	{
//		cout << s4.substr(pos4 + 1) << endl;
//	}
//
//	return 0;
//}


// -------------------------- 取出文件名的后缀名 
// ==> 从后往前查找最后一个'.'的位置,把'.'后面的内容取出来。

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//void get_file_extension(const string& filename)
//{
//	size_t pos = filename.rfind("."); // 查找最后一个'.'的位置
//	if (pos != string::npos)
//	{
//		cout << "文件名: " << filename.substr(0, pos) << endl; // 文件名
//		cout << "后缀名: " << filename.substr(pos + 1) << endl; // 后缀名
//	}
//	else
//	{
//		cout << "文件名: " << filename << endl; // 文件名
//		cout << "没有后缀名" << endl;
//	}
//}
//
//int main()
//{
//	string s1("string.cpp");
//	string s2("string.c");
//	string s3("string.h");
//	string s4("string.cpp.zip.tar");
//	get_file_extension(s1);
//	cout << "==============================================" << endl;
//	get_file_extension(s2);
//	cout << "==============================================" << endl;
//	get_file_extension(s3);
//	cout << "==============================================" << endl;
//	get_file_extension(s4);
//	return 0;
//}


//// -------------------------- 分离URL中的协议、域名和资源名称。
//
//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//// 分离出: 协议,域名,资源名称。
//void split_url(const string& url)
//{
//	size_t index1 = url.find("://");
//	if (index1 != string::npos)
//	{
//		cout << "协议:" << url.substr(0, index1) << endl; // 协议
//	}
//	size_t index2 = url.find("/", index1 + 3); // 从index1 + 3的位置开始查找第一个'/'的位置"
//	if (index2 != string::npos)
//	{
//		cout << "域名:" << url.substr(index1 + 3, index2 - (index1 + 3)) << endl; // 域名
//	}
//	cout << "资源名称:" << url.substr(index2 + 1) << endl; // 资源名称
//}
//
//int main()
//{
//	string url("https://cplusplus.com/reference/string/string/find/");
//	// 网址: 协议 + 域名 + 资源名称。
//	// 协议: https
//	// 域名: cplusplus.com <==> IP地址
//	split_url(url);
//
//	return 0;
//}


// ===============================================================================================================
// string字符串和C_string。

// string类内部维护了一个字符数组,可以通过c_str()获取这个字符数组的首地址。
// c_str() ==> 获取string对象内部的字符数组的首地址。
// 这个字符数组是以'\0'结尾的,可以直接当作C语言的字符串使用。
// 返回值: const char* ==> 返回string对象内部的字符数组的首地址。


//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	string s1("Hello");
//	const char* str = s1.c_str(); // 获取string对象内部的字符数组的首地址。
//	cout << "======================================================" << endl;
//	cout << "使用C语言的方式输出字符串: " << endl;
//	cout << str << endl; // 输出Hello
//	// 直接输出const char* ，输出字符数组。
//	cout << "-------------------------------------" << endl;
//	// 获取字符数组的首地址,使用C语言的遍历方式。
//	while (*str)
//	{
//		cout << *str << " "; // 解引用指针，获取字符。
//		++str; // 指针自增，指向下一个字符。
//	}
//	cout << endl;
//	cout << "======================================================" << endl;
//	cout << "使用C++的方式输出字符串: " << endl;
//	cout << s1 << endl; // 调用string重载的的operator<<，输出string对象。
//	// 调用string重载的的operator<<，输出string对象。
//	return 0;
//}

// ------------------------------------------------- 区别。


//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	string s1("Hello");
//	s1.resize(100); // 改变字符串的大小为100,多余的字符用'\0'填充。
//	s1[99] = 'A'; // 修改最后一个字符为'A'。
//	const char* str = s1.c_str(); // 获取string对象内部的字符数组的首地址。
//
//	cout << "======================================================" << endl;
//	cout << "使用C语言的方式输出字符串: " << endl;
//	cout << str << endl; // 输出Hello
//	cout << "======================================================" << endl;
//	cout << "使用C++的方式输出字符串: " << endl;
//	cout << s1 << endl; // 调用string重载的的operator<<，输出string对象。
//
//	return 0;
//}


// ----------------------------------------------------- 编码器、可见字符和不可见字符。

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//int main()
//{
//	// 编码的本质: 映射。
//
//	// -------------------------------------------
//	// ASCII码表 ==> 早期计算只需要表示英文。
//	// ASCII码表 值和字母标点的映射关系。 
//	// ASCII码表中有可见字符和不可见字符。
//	// 标准的ASCII码表中有128个字符,值从0到127。
//	// 扩展的ASCII码表中有256个字符,值从0到255。
//
//	
//	for (int i = 0; i < 256; ++i)
//	{
//		cout << i << "<-->" << (char)i << "   ";
//	}
//
//	return 0;
//}



//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//
//int main()
//{
//	// 编码表: 值和表示的符号(字母或者文字)
//	// unicode ==> 计算机科学领域里的一项业界标准,包括字符集,编码方案。
//	// utf-8 utf-16 utf-32 ==> unicode的编码方案。
//	// Linux 下常用的中文编码集 utf-8
//	// Windows 下常用的中文编码集 GBK
//
//	// VS2026编译器: ==> 推荐使用GBK。
//
//	char ch_str[] = "中国";
//	cout << sizeof(ch_str) << endl; // 5 个字节。
//	// sizeof() ==> 计算数组的大小,包括'\0'。
//	cout << strlen(ch_str) << endl; // 4 个字节。
//	// strlen() ==> 计算字符串的长度,不包括'\0'。
//
//	// 同音字编码到一起。
//	ch_str[3] = -7;
//	cout << ch_str << endl; 
//	ch_str[3] = -8;
//	cout << ch_str << endl;
//	ch_str[3] = -9;
//	cout << ch_str << endl;
//
//	return 0;
//}



// ===============================================================================================================
// string类的其他的重载。


// ------------------------ 大小比较。

//#include <iostream>
//#include <string> // string类头文件
//using std::cout;
//using std::endl;
//using std::string; // string类
//
//// 尽量使用 operator+= 来拼接字符串,因为它不会产生临时对象,效率更高。
//int main()
//{
//	string s1("Hello");
//	string res = s1 + " world";
//	// operator+ 重载了字符串的拼接操作,并返回拼接后的对象。
//	string res2 = (s1 += " world");
//	// operator+= 重载了字符串的拼接操作,并返回拼接后的对象的引用。
//	cout << res << endl; // Hello world
//	cout << res2 << endl; // Hello world
//
//	string s2("abcd");
//	string s3("bbcd");
//	cout << (s2 < s3) << endl; // string对象和string对象比较
//	cout << (s2 < "bbcd") << endl; // string对象和const char*比较
//	cout << ("abcd" < s3) << endl; // const char*和string对象比较
//}


// ------------------------------ cin 和 getline()。

//// 字符串的最后一个单词的长度。
//// https://www.nowcoder.com/practice/8c949ea5f36f422594b306a2300315da?tpId=37&&tqId=21224&rp=5&ru=/activity/oj&qru=/ta/huawei/question-ranking
//#include <iostream>
//#include <string>
//using std::cout;
//using std::cin;
//using std::endl;
//using std::string;
//
//// scanf()和cin遇到空格换行就结束了。
//int main()
//{
//	string s;
//	//cin >> s; // 遇到空格、换行都结束。
//	getline(cin, s); // 遇到换行才结束。
//	size_t last_space = s.rfind(' '); // 查找最后一个空格的位置
//	cout << s.size() - (last_space + 1) << endl; // 输出最后一个单词的长度
//	return 0;
//}


// ===============================================================================================================
// 练习题：

// 练习题1：
// 125. 验证回文串
// https://leetcode.cn/problems/valid-palindrome/

//#include <string>
//using std::string;
//class Solution
//{
//public:
//    bool isPalindrome(string s)
//    {
//        // 将字符中的所有的大写字母都转成小写。
//		for (auto& c : s)
//		{
//			if (c >= 'A' && c <= 'Z')
//			{
//				c += 32; // 转成小写。
//			}
//		}
//		int begin = 0, end = s.size() - 1;
//		while (begin < end)
//		{
//			while ((begin < end) && (!IsCharOrNumber(s[begin])))
//			{
//				++begin;
//			}
//			// begin指向的字符是字母或者数字。
//			while ((begin < end) && (!IsCharOrNumber(s[end])))
//			{
//				--end;
//			}
//			// end指向的字符是字母或者数字。
//			if (s[begin] != s[end]) // 如果不相等,不是回文串。
//			{
//				return false;
//			}
//			++begin; // begin指向下一个字符。
//			--end; // end指向前一个字符。
//		}
//		return true;
//    }
//private:
//	inline bool IsCharOrNumber(char c) // 判断是否是字母或者数字
//	{
//		if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//};


// 练习题2：
// 415. 字符串相加
// https://leetcode.cn/problems/add-strings/


//#include <string>
//using std::string;
//class Solution
//{
//public:
//    string addStrings(string num1, string num2)
//    {
//        // 从后往前倒着遍历,中间需要一个进位。
//		int next = 0; // 进位
//        int end1 = num1.size() - 1, end2 = num2.size() - 1;
//        int val1 = 0, val2 = 0;
//        string s1;
//        while (end1 >= 0 || end2 >= 0)
//        {
//            val1 = 0, val2 = 0;
//            if (end1 >= 0)
//            {
//				val1 = num1[end1] - '0'; // 字符转数字
//            }
//            if (end2 >= 0)
//            {
//				val2 = num2[end2] - '0'; // 字符转数字
//            }
//			int res = val1 + val2 + next; // 当前位的和
//            if (res > 9)
//            {
//                res -= 10;
//                next = 1;
//            }
//            else 
//            {
//                next = 0;
//            }
//            // 头插入。
//			s1.insert(s1.begin(), res + '0'); // 数字转字符
//            --end1;
//            --end2;
//        }
//		if (next == 1) // 处理最后的进位。
//		{
//			s1.insert(s1.begin(), '1'); // 进位
//		}
//		return s1;
//    }
//};


//#include <string>
//#include <algorithm> // reverse
//using std::string;
//using std::reverse; // reverse() 反转字符串。
//class Solution
//{
//public:
//    string addStrings(string num1, string num2)
//    {
//        // 从后往前倒着遍历,中间需要一个进位。
//        int next = 0; // 进位
//        int end1 = num1.size() - 1, end2 = num2.size() - 1;
//        int val1 = 0, val2 = 0;
//        string s1;
//        while (end1 >= 0 || end2 >= 0)
//        {
//            val1 = 0, val2 = 0;
//            if (end1 >= 0)
//            {
//                val1 = num1[end1] - '0'; // 字符转数字
//            }
//            if (end2 >= 0)
//            {
//                val2 = num2[end2] - '0'; // 字符转数字
//            }
//            int res = val1 + val2 + next; // 当前位的和
//            if (res > 9)
//            {
//                res -= 10;
//                next = 1;
//            }
//            else
//            {
//                next = 0;
//            }
//            s1 += (res + '0'); // += 追加到字符串末尾
//            --end1;
//            --end2;
//        }
//        if (next == 1) // 处理最后的进位。
//        {
//			s1 += '1'; // 进位
//        }
//		reverse(s1.begin(), s1.end()); // 反转字符串
//        return s1;
//    }
//};


// 练习题3：
// 字符串相乘。
// https://leetcode.cn/problems/multiply-strings/description/


// 超出时间限制。
#include <string>
using std::string;
class Solution
{
public:
    string multiply(string num1, string num2)
    {
		string i("0"); // 空串。
        string one("1");
		string res("0");
		int len1 = num1.size(), len2 = num2.size();
		if (num1 == "0" || num2 == "0")
		{
			return "0";
		}
		// num1 * num2 = num2 + num2 + ... + num2 ,,, (num1 次)
		if (len1 < len2) // 循环加 len1 次。
        {
            while (i != num1)
            {
				i = addStrings(i, one); // i++,循环。
				res = addStrings(res, num2);
            }
        }
        else // 循环加 len2 次。
        {
            while (i != num2)
            {
				i = addStrings(i, one); // i++,循环。
				res = addStrings(res, num1);
            }
        }
		return res;
    }

private:
    string addStrings(string num1, string num2)
    {
        // 从后往前倒着遍历,中间需要一个进位。
        int next = 0; // 进位
        int end1 = num1.size() - 1, end2 = num2.size() - 1;
        int val1 = 0, val2 = 0;
        string s1;
        while (end1 >= 0 || end2 >= 0)
        {
            val1 = 0, val2 = 0;
            if (end1 >= 0)
            {
                val1 = num1[end1] - '0'; // 字符转数字
            }
            if (end2 >= 0)
            {
                val2 = num2[end2] - '0'; // 字符转数字
            }
            int res = val1 + val2 + next; // 当前位的和
            if (res > 9)
            {
                res -= 10;
                next = 1;
            }
            else
            {
                next = 0;
            }
            s1 += (res + '0');
            --end1;
            --end2;
        }
        if (next == 1) // 处理最后的进位。
        {
			s1 += '1'; // 进位
        }
		reverse(s1.begin(), s1.end()); // 反转字符串
        return s1;
    }
};