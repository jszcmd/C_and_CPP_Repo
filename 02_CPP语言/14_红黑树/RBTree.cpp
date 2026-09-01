// 代码完善于 2026年9月1日,初次编写于 一周之前 2024年8月27日。

// 红黑树的代码测试和性能分析。

#include "AVLTree.h" // AVL树的实现。
#include "RBTree.h" // 红黑树的实现。
#include <vector>
#include <cstdlib> // srand, rand
#include <ctime> // time
#include <algorithm>
using std::vector;
using std::time;
using std::srand;
using std::rand;
using std::clock;
using std::sort;

// 红黑树的测试函数。
void testKRBTree(const int n, vector<int> v, bool isTestBalance = false)
{
	// ===========================================================
	KRBTree<int> retree;
	// ===============================================================
	cout << "--------------------------------------------------------------" << endl;
	// 红黑树的插入操作的测试。
	size_t start = clock();
	for (auto& e : v)
	{
		retree.insert(e);
	}
	size_t end = clock();
	cout << "红黑树插入时间: " << (end - start) << " ms" << endl;
	cout << "红黑树的高度: " << retree.height() << endl;
	cout << "红黑树是否平衡: " << (retree.isValidRBTree() ? "是" : "否") << endl;
	cout << "红黑树的大小: " << retree.size() << endl;
	// ================================================================
	cout << "--------------------------------------------------------------" << endl;
	// 红黑树的查找操作的测试。
	start = clock();
	for (auto& e : v)
	{
		if (!retree.find(e))
		{
			cout << "红黑树中没有找到: " << e << endl;
		}
	}
	end = clock();
	cout << "红黑树查找时间: " << (end - start) << " ms" << endl;
	// ===============================================================
	cout << "--------------------------------------------------------------" << endl;
	// 红黑树的删除操作的测试。
	start = clock();
	for (auto& e : v)
	{
		retree.erase(e);
		if (isTestBalance && !retree.isValidRBTree())
		{
			cout << "红黑树不平衡!" << endl;
			break;
		}
	}
	end = clock();
	cout << "红黑树删除时间: " << (end - start) << " ms" << endl;
}

// AVL树的测试函数。
void testKAVLTree(const int n, vector<int> v, bool isTestBalance = false)
{
	// ===========================================================
	KAVLTree<int> avltree;
	// ===============================================================
	cout << "--------------------------------------------------------------" << endl;
	// AVL树的插入操作的测试。
	size_t start = clock();
	for (auto& e : v)
	{
		avltree.insert(e);
	}
	size_t end = clock();
	cout << "AVL树插入时间: " << (end - start) << " ms" << endl;
	cout << "AVL树的高度: " << avltree.height() << endl;
	cout << "AVL树是否平衡: " << (avltree.isBalance() ? "是" : "否") << endl;
	cout << "AVL树的大小: " << avltree.size() << endl;
	// ================================================================
	cout << "--------------------------------------------------------------" << endl;
	// AVL树的查找操作的测试。
	start = clock();
	for (auto& e : v)
	{
		if (!avltree.find(e))
		{
			cout << "AVL树中没有找到: " << e << endl;
		}
	}
	end = clock();
	cout << "AVL树查找时间: " << (end - start) << " ms" << endl;
	// ===============================================================
	cout << "--------------------------------------------------------------" << endl;
	// AVL树的删除操作的测试。
	start = clock();
	for (auto& e : v)
	{
		avltree.erase(e);
		if (isTestBalance && !avltree.isBalance())
		{
			cout << "AVL树不平衡!" << endl;
			break;
		}
	}
	end = clock();
	cout << "AVL树删除时间: " << (end - start) << " ms" << endl;
	// ===============================================================
}


int main()
{
	const int n = 100000000; // 测试数据的个数。
	vector<int> v;
	v.reserve(n);
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < n; ++i)
	{
		v.push_back(rand());
	}
	// 随机数据的准备。
	// ===========================================================
	testKRBTree(n, v, false); // 红黑树的测试。
	cout << "===========================================================================================" << endl;
	testKAVLTree(n, v, false); // AVL树的测试。
	return 0;
}