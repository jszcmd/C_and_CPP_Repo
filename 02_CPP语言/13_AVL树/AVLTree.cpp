// 2026年8月25日

// 代码完成于2026年8月31日,初次写于一星期以前左右2026年8月25日。

/*
* KAVLTree 对外接口:
* KAVLTree()                  : 构造空 AVL 树。参数: 无。返回值: 无。
* bool insert(const K& key)   : 插入 key。参数: key。返回值: 成功 true，key 已存在 false。
* bool erase(const K& key)    : 删除 key。参数: key。返回值: 成功 true，key 不存在 false。
* bool find(const K& key)     : 查找 key。参数: key。返回值: 找到 true，否则 false。
* int size()                  : 获取节点个数。参数: 无。返回值: 节点数量。
* int height()                : 获取树高度。参数: 无。返回值: 树高。
* void inOrder()              : 中序遍历打印。参数: 无。返回值: 无。
* bool isBalance()            : 检查 AVL 平衡性质。参数: 无。返回值: 平衡 true，否则 false。
*/

/*
* KVAVLTree 对外接口:
* KVAVLTree()                         : 构造空 key-value AVL 树。参数: 无。返回值: 无。
* bool insert(const pair<K, V>& kv)   : 插入键值对。参数: kv。返回值: 成功 true，key 已存在 false。
* bool erase(const K& key)            : 按 key 删除。参数: key。返回值: 成功 true，key 不存在 false。
* bool find(const K& key)             : 按 key 查找。参数: key。返回值: 找到 true，否则 false。
* void inOrder()                      : 中序遍历打印。参数: 无。返回值: 无。
* bool isBalance()                    : 检查 AVL 平衡性质。参数: 无。返回值: 平衡 true，否则 false。
* int height()                        : 获取树高度。参数: 无。返回值: 树高。
* int size()                          : 获取节点个数。参数: 无。返回值: 节点数量。
*/

#include "AVLTree.h" // AVL树的实现。
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

void testKAVLTree(const int n, bool isOrdered = false)
{
	vector <int> v;
	v.reserve(n);
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < n; ++i)
	{
		v.push_back(rand());
	}
	if (isOrdered)
	{
		sort(v.begin(), v.end());
	}
	// 随机数据的准备。
	// ===========================================================
	KAVLTree<int> myset;

	// ===============================================================
	// AVL树的插入操作的测试。
	size_t start = clock();
	for (auto& e : v)
	{
		myset.insert(e);
	}
	size_t end = clock();
	cout << "AVL树插入时间: " << (end - start) << " ms" << endl;
	cout << "AVL树的高度: " << myset.height() << endl;
	cout << "AVL树是否平衡: " << (myset.isBalance() ? "是" : "否") << endl;
	cout << "AVL树的大小: " << myset.size() << endl;
	// ================================================================
	// AVL树的查找操作的测试。
	start = clock();
	for (auto& e : v)
	{
		if (!myset.find(e))
		{
			cout << "AVL树中没有找到: " << e << endl;
		}
	}
	end = clock();
	cout << "AVL树查找时间: " << (end - start) << " ms" << endl;
	// ===============================================================
	// AVL树的删除操作的测试。
	start = clock();
	for (auto& e : v)
	{
		myset.erase(e);
		if (!myset.isBalance())
		{
			cout << "AVL树不平衡!" << endl;
			break;
		}
		//cout << myset.size() << " ";
	}
	end = clock();
	cout << "AVL树删除时间: " << (end - start) << " ms" << endl;
	// ===============================================================
}

void testKVAVLTree(const int n, bool isOrdered = false)
{
	vector <int> v;
	v.reserve(n);
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < n; ++i)
	{
		v.push_back(rand());
	}
	if (isOrdered)
	{
		sort(v.begin(), v.end());
	}
	// 随机数据的准备。
	// ===========================================================
	KVAVLTree<int, int> dict;
	// ===============================================================
	// AVL树的插入操作的测试。
	size_t start = clock();
	for (auto& e : v)
	{
		dict.insert(make_pair(e, e));
	}
	size_t end = clock();
	cout << "AVL树插入时间: " << (end - start) << " ms" << endl;
	cout << "AVL树的高度: " << dict.height() << endl;
	cout << "AVL树是否平衡: " << (dict.isBalance() ? "是" : "否") << endl;
	cout << "AVL树的大小: " << dict.size() << endl;
	// ================================================================
	// AVL树的查找操作的测试。
	start = clock();
	for (auto& e : v)
	{
		if (!dict.find(e))
		{
			cout << "AVL树中没有找到: " << e << endl;
		}
	}
	end = clock();
	cout << "AVL树查找时间: " << (end - start) << " ms" << endl;
	// ===============================================================
	// AVL树的删除操作的测试。
	start = clock();
	for (auto& e : v)
	{
		dict.erase(e);
		if (!dict.isBalance())
		{
			cout << "AVL树不平衡!" << endl;
			break;
		}
	}
	end = clock();
	cout << "AVL树删除时间: " << (end - start) << " ms" << endl;
}

int main()
{
	const int n = 10000;
	cout << "K模型的AVL树的测试,并且验证是否平衡。" << endl;
	cout << "========================================================" << endl;
	testKAVLTree(n, false);
	// K模型的AVL树。
	cout << "========================================================" << endl;
	//testKVAVLTree(n, false);
	return 0;
}
