#pragma once

// 代码完善于 2026年9月1日,初次编写于 一周之前 2024年8月27日。

// VS2026编译器下面
#include <iostream> // cout, endl
#include <utility> // pair, make_pair, swap
#include <xutility> // max
#include <algorithm> 
#include <memory> // swap
using std::cout;
using std::endl; 
using std::pair; 
using std::make_pair; 
using std::swap;
using std::max;

/*
 * 红黑树(Red-Black Tree):
 * 本质: 一种近似平衡的二叉搜索树。
 *
 * 基本特点:
 * 1. 满足二叉搜索树性质。
 * 2. 每个节点增加颜色字段，颜色只能是 RED 或 BLACK。
 * 3. 通过颜色约束控制平衡，使最长路径不超过最短路径的 2 倍。
 *
 * 红黑树性质:
 * 1. 每个节点不是红色就是黑色。
 * 2. 根节点必须是黑色。
 * 3. 红色节点的孩子必须是黑色，即不能有连续红色节点。
 * 4. 任意节点到其所有后代 NULL 节点的路径上，黑色节点数量相同。
 * 5. NULL 节点看作黑色叶子节点。
 *
 * 为什么最长路径不超过最短路径的 2 倍:
 * 1. 性质4保证每条路径黑色节点数量相同。
 * 2. 性质3保证红色节点不能连续出现。
 * 3. 最短路径可以认为是全黑路径。
 * 4. 最长路径最多是红黑交替路径。
 * 5. 所以最长路径 <= 2 * 最短路径。
 *
 * 时间复杂度:
 * 插入、删除、查找、修改都是 O(log N)。
 *
 * AVL树和红黑树对比:
 * 1. AVL树是严格平衡的二叉搜索树，要求左右子树高度差不超过 1。
 * 2. 红黑树是近似平衡的二叉搜索树，只要求最长路径不超过最短路径的 2 倍。
 * 3. 理论上 AVL 查询效率略高。
 * 4. 实际上两者都是 O(log N)，差距很小。
 * 5. 红黑树旋转次数通常更少，插入删除效率更稳定。
 * 6. 工程中红黑树应用更广，如 map、set 等。
 *
 * 插入规则:
 * 1. 空树插入: 新节点作为根节点，并染成黑色。
 * 2. 父节点是黑色: 直接插入红色节点，结束。
 * 3. 父节点是红色: 祖父节点一定存在，且一定是黑色。
 *    此时关键看叔叔节点:
 *    a. 叔叔存在且为红色:
 *       父亲和叔叔变黑，祖父变红，然后继续向上处理。
 *    b. 叔叔不存在或叔叔为黑色:
 *       通过旋转加变色解决连续红色节点问题。
 */

// 红黑树的颜色枚举类型。
enum Color
{
	RED, // 红色
	BLACK // 黑色
};

// =========================================================================================================================
// =========================================================================================================================
// =========================================================================================================================
// key模型的红黑树。

/*
 * KRBTree<K> 对外接口:
 * KRBTree()                         : 构造空红黑树。参数: 无。返回值: 无。
 * bool insert(const K& key)         : 插入 key。参数: key。返回值: 成功 true，key 已存在 false。
 * bool erase(const K& key)          : 删除 key。参数: key。返回值: 成功 true，key 不存在 false。
 * Node* find(const K& key)          : 查找 key。参数: key。返回值: 找到返回节点指针，否则 nullptr。
 * void inorder()                    : 中序遍历打印。参数: 无。返回值: 无。
 * bool isValidRBTree()              : 检查红黑树性质。参数: 无。返回值: 合法 true，否则 false。
 * int height()                      : 获取树高度。参数: 无。返回值: 树高。
 * int size()                        : 获取节点个数。参数: 无。返回值: 节点数量。
 */

// key模型的红黑树节点。
template <class K>
class KRBTreeNode
{
public:
	KRBTreeNode<K>* _left;
	KRBTreeNode<K>* _right;
	KRBTreeNode<K>* _parent;
	Color _color; // 颜色
	K _key; // 数据域。

	// 构造函数。
	KRBTreeNode(const K& key = K(), Color color = RED)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _color(color) // 默认颜色为红色。
		, _key(key)
	{}

	bool isLeaf() // 判断是否是叶子节点。
	{
		return _left == nullptr && _right == nullptr;
	}
	bool isOnlyLeft() // 判断是否只有左子树。
	{
		return _left != nullptr && _right == nullptr;
	}
	bool isOnlyRight() // 判断是否只有右子树。
	{
		return _left == nullptr && _right != nullptr;
	}

};

// key模型的红黑树。
template <class K>
class KRBTree
{
public:
	typedef KRBTreeNode<K> Node;
	KRBTree() : _root(nullptr), _size(0) {} // 构造函数。

	bool insert(const K& key) // 插入函数。
	{
		// 1. 先按照二叉搜索树的规则插入节点。
		if (_root == nullptr)
		{
			_root = new Node(key, BLACK); // 根节点必须为黑色。
			_size++;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key) // 左边找
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) // 右边找
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; // 不允许插入重复的键。
			}
		}
		cur = new Node(key, RED); // 新插入的节点给红色的好。
		cur->_parent = parent;
		if ((parent->_key) < (cur->_key))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		// 插入成功。
		// -----------------------------------------------------

		while (parent && (parent->_color == RED))
		{
			// 红黑树的条件关键看叔叔。
			Node* grandparent = parent->_parent; // 爷爷节点。
			// 找到叔叔节点。
			Node* uncle = nullptr;
			if (parent == grandparent->_left)
			{
				uncle = grandparent->_right; // 叔叔是爷爷的右孩子。
				// 情况1: 叔叔存在,且为红色。
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK; // 父亲和叔叔变黑。
					grandparent->_color = RED; // 爷爷变红。
					// 继续往上处理。
					cur = grandparent;
					parent = cur->_parent;
				}
				else // 叔叔不存在或者为黑色。
				{
					// 情况3: 双旋 --> 变成单旋。
					if (cur == parent->_right)
					{
						RotateL(parent); // parent的位置左单旋。
						swap(cur, parent); // 交换cur和parent。
					}
					// 情况2: 单旋。(也有可能是第3种情况变过来的)
					RotateR(grandparent);
					grandparent->_color = RED;
					parent->_color = BLACK;
					break;
				}
			}
			else // parent == grandparent->_right
			{
				uncle = grandparent->_left; // 叔叔是爷爷的左孩子。
				if (uncle && uncle->_color == RED) // 情况1: 叔叔存在,且为红色。
				{
					parent->_color = uncle->_color = BLACK; // 父亲和叔叔变黑。
					grandparent->_color = RED; // 爷爷变红。
					// 继续往上处理。
					cur = grandparent;
					parent = cur->_parent;
				}
				else // 叔叔不存在或者为黑色。
				{
					// 情况3: 双旋 --> 变成单旋。
					if (cur == parent->_left)
					{
						RotateR(parent); // parent的位置右单旋。
						swap(cur, parent); // 交换cur和parent。
					}
					// 情况2: 单旋。(也有可能是第3种情况变过来的)
					RotateL(grandparent);
					grandparent->_color = RED;
					parent->_color = BLACK;
					break;
				}
			}
		}
		_root->_color = BLACK; // 根节点必须为黑色。
		_size++;
		return true;
	}

	// 删除函数。
	bool erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (key < (cur->_key)) // 左边找
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > (cur->_key)) // 右边找
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break; // 找到了要删除的节点
			}
		}
		if (cur == nullptr)
		{
			return false; // 没有找到要删除的节点
		}
		// ------------------------------------------------------------------------
		// 找到了要删除的节点,开始。删除节点。
		if ((cur->_left != nullptr) && (cur->_right != nullptr)) // cur有左右子树。
		{
			Node* parentRightMin = cur;
			Node* rightMin = cur->_right;
			while (rightMin->_left)
			{
				parentRightMin = rightMin;
				rightMin = rightMin->_left;
			}
			cur->_key = rightMin->_key; // 把右子树的最小节点的值赋给cur。
			parent = parentRightMin; // 更新外部的parent变量。
			cur = rightMin;
		} // cur有左右子树 ==> 把cur换成,最多只有一个节点的位置。

		if ((cur->isOnlyLeft()) || (cur->isOnlyRight())) // 要删除的节点有一个子节点。
		{
			Node* child = (cur->_left != nullptr) ? cur->_left : cur->_right;
			cur->_key = child->_key;
			cur->_color = BLACK; // 保险起见。
			cur->_left = cur->_right = nullptr;
			cur = child; // 删除cur。
		}
		else // 要删除的是叶子节点。 //else if (cur->isLeaf()) // 要删除的是叶子节点。
		{
			if (isRedNode(cur)) // 情况2：删除的是叶子节点 2.1：要删除的叶子节点是红色
			{
				; // 直接删除,删除以后无需做任何调整
			}
			else // 情况2：删除的是叶子节点 2.2：要删除的叶子节点是黑色
			{
				if (parent == nullptr) // 删除的是根节点,且是黑色叶子节点
				{
					_root = nullptr;
					delete cur;
					cur = nullptr;
					_size--;
					return true;
				}
				Node* doubleBlack = cur; // 双黑节点。
				parent = doubleBlack->_parent; // 更新父节点。
				Node* sibling = (doubleBlack == parent->_left) ? (parent->_right) : (parent->_left); // 更新兄弟节点。
				while (parent != nullptr)
				{
					if (isRedNode(sibling)) // 2.2.1：兄弟是红色
					{
						// 父兄变色,朝双黑旋转,保持双黑继续调整
						parent->_color = RED;
						sibling->_color = BLACK;
						// 朝双黑旋转
						if (doubleBlack == parent->_left)
						{
							RotateL(parent);
						}
						else
						{
							RotateR(parent);
						}
						// 保持双黑继续调整
						parent = doubleBlack->_parent;
						sibling = (doubleBlack == parent->_left) ? (parent->_right) : (parent->_left);
					}
					else // 2.2.2：兄弟是黑色 
					{
						// 2.2.2.2：兄弟节点的孩子都是黑色的
						if ((isBlackNode(sibling->_left)) && (isBlackNode(sibling->_right)))
						{
							sibling->_color = RED; // 兄弟变红。
							if (parent == _root) // 父节点是根节点
							{
								break; // 直接把双黑节点变成单黑节点
							}
							else if (parent->_color == RED) // 父节点是红色
							{
								parent->_color = BLACK; // 父节点变黑。
								break;
							}
							else
							{
								doubleBlack = doubleBlack->_parent; // 双黑节点上移。
								parent = doubleBlack->_parent; // 更新父节点。
								sibling = (doubleBlack == parent->_left) ? (parent->_right) : (parent->_left); // 更新兄弟节点。
							}
						}
						else // 2.2.2.1：兄弟节点至少有一个红色的孩子
						{
							Node* sibling_L = sibling->_left;
							Node* sibling_R = sibling->_right;
							if (sibling == parent->_left) // L型
							{
								// s是p的左节点;s的左边是黑的,s的右边是红的 LR
								if ((isBlackNode(sibling_L)) && (isRedNode(sibling_R)))
								{
									sibling_R->_color = parent->_color; // r的颜色变成p的颜色.
									parent->_color = BLACK; // p变黑。
									RotateL(sibling); //s的位置左单旋。
									RotateR(parent); // p的位置右单旋。
									break; // 双黑节点变成单黑节点。
								}
								else // LL型
								{
									sibling_L->_color = sibling->_color; // r的颜色变成s的颜色
									sibling->_color = parent->_color; // s的颜色变成p的颜色
									parent->_color = BLACK;
									RotateR(parent); // 右单旋转。
									break; // 双黑节点变成单黑节点。
								}
							}
							else // sibling == parent->_right  R型
							{
								if ((isRedNode(sibling_L)) && (isBlackNode(sibling_R)))
								{
									sibling_L->_color = parent->_color; // r的颜色变成p的颜色.
									parent->_color = BLACK; // p变黑。
									RotateR(sibling); //s的位置右单旋。
									RotateL(parent); // p的位置左单旋。
									break; // 双黑节点变成单黑节点。
								}
								else
								{
									sibling_R->_color = sibling->_color; // r的颜色变成s的颜色
									sibling->_color = parent->_color; // s的颜色变成p的颜色
									parent->_color = BLACK;
									RotateL(parent); // 左单旋转。
									break; // 双黑节点变成单黑节点。
								}
							}
						}
					}
				}
			}
		}
		// =======================================================================
		// 删除并释放cur节点。
		if (cur->_parent)
		{
			(cur->_parent->_left == cur) ? (cur->_parent->_left = nullptr) : (cur->_parent->_right = nullptr);
		}
		else
		{
			_root = nullptr;
		}
		if (_root) // 根节点存在的话,必须是黑色的。
		{
			_root->_color = BLACK; // 根节点必须为黑色。
		}
		delete cur;
		cur = nullptr;
		_size--;
		return true;
	}

	// 查找函数。
	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < (cur->_key))
			{
				cur = cur->_left;
			}
			else if (key > (cur->_key))
			{
				cur = cur->_right;
			}
			else
			{
				return cur; // 找到节点。
			}
		}
		return nullptr; // 没有找到节点。
	}


	void inorder() // 中序遍历。
	{
		_InOrder(_root);
		cout << endl;
	}

	// 验证红黑树的性质。
	bool isValidRBTree()
	{
		Node* pRoot = _root;
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;

		// 检测根节点是否满足情况
		if (BLACK != pRoot->_color)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}

		// 获取任意一条路径中黑色节点的个数
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
				blackCount++;
			pCur = pCur->_left;
		}

		// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}

	// 计算树的高度。
	int height()
	{
		return _Height(_root);
	}

	// 获取树的大小。
	int size()
	{
		return _size;
	}

private:
	Node* _root; // 根节点。
	int _size; // 树的大小。

	// 红节点: 不为空且颜色为红色
	bool isRedNode(Node* node)
	{
		return node != nullptr && node->_color == RED;
	}

	// 黑节点: 为空或者颜色为黑色
	bool isBlackNode(Node* node)
	{
		return ((node == nullptr) || (node->_color == BLACK));
	}

	// 左单旋。
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right; // 右子树
		Node* subRL = subR->_left; // 右子树的左子树
		Node* GrandParent = parent->_parent; // 父节点的父节点
		int flag = 0;
		if (GrandParent)
		{
			if (GrandParent->_left == parent)
			{
				flag = -1; // parent是GrandParent的左子树
			}
			else
			{
				flag = 1; // parent是GrandParent的右子树
			}
		}
		else
		{
			flag = 0; // 根节点
		}
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		parent->_parent = subR;
		if (flag == -1)
		{
			GrandParent->_left = subR;
			subR->_parent = GrandParent;
		}
		else if (flag == 1)
		{
			GrandParent->_right = subR;
			subR->_parent = GrandParent;
		}
		else
		{
			_root = subR; // 根节点
			subR->_parent = nullptr;
		}
	}

	// 右单旋。
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left; // 左子树
		Node* subLR = subL->_right; // 左子树的右子树
		Node* GrandParent = parent->_parent; // 父节点的父节点
		int flag = 0;
		if (GrandParent)
		{
			if (GrandParent->_left == parent)
			{
				flag = -1; // parent是GrandParent的左子树
			}
			else
			{
				flag = 1; // parent是GrandParent的右子树
			}
		}
		else
		{
			flag = 0; // 根节点
		}
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		if (flag == -1)
		{
			GrandParent->_left = subL;
			subL->_parent = GrandParent;
		}
		else if (flag == 1)
		{
			GrandParent->_right = subL;
			subL->_parent = GrandParent;
		}
		else
		{
			_root = subL; // 根节点
			subL->_parent = nullptr;
		}
	}

	// 中序遍历的子函数。
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	// 验证红黑树的性质的子函数。
	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		// 走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}

		// 统计黑色节点的个数
		if (BLACK == pRoot->_color)
			k++;

		// 检测当前节点与其双亲是否都为红色
		Node* pParent = pRoot->_parent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}

		return _IsValidRBTree(pRoot->_left, k, blackCount) && _IsValidRBTree(pRoot->_right, k, blackCount);
	}

	// 计算树的高度的子函数。
	int _Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return max(leftHeight, rightHeight) + 1;
	}

};


// =========================================================================================================================
// =========================================================================================================================
// =========================================================================================================================
// key : value模型的红黑树。

/*
 * KVRBTree<K, V> 对外接口:
 * KVRBTree()                        : 构造空 key-value 红黑树。参数: 无。返回值: 无。
 * bool insert(const pair<K, V>& kv) : 插入键值对。参数: kv。返回值: 成功 true，key 已存在 false。
 * bool erase(const K& key)          : 按 key 删除。参数: key。返回值: 成功 true，key 不存在 false。
 * Node* find(const K& key)          : 按 key 查找。参数: key。返回值: 找到返回节点指针，否则 nullptr。
 * void inorder()                    : 中序遍历打印 key。参数: 无。返回值: 无。
 * bool isValidRBTree()              : 检查红黑树性质。参数: 无。返回值: 合法 true，否则 false。
 * int height()                      : 获取树高度。参数: 无。返回值: 树高。
 * int size()                        : 获取节点个数。参数: 无。返回值: 节点数量。
 */

// key : value模型的红黑树节点。
template <class K, class V>
class KVRBTreeNode
{
public:
	KVRBTreeNode<K, V>* _left;
	KVRBTreeNode<K, V>* _right;
	KVRBTreeNode<K, V>* _parent;
	Color _color; // 颜色
	pair<K, V> _kv; // 数据域。

	// 构造函数。
	KVRBTreeNode(const pair<K, V>& kv, Color color = RED)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _color(color) // 默认颜色为红色。
		, _kv(kv) {}

	bool isLeaf() // 判断是否是叶子节点。
	{
		return _left == nullptr && _right == nullptr;
	}
	bool isOnlyLeft() // 判断是否只有左子树。
	{
		return _left != nullptr && _right == nullptr;
	}
	bool isOnlyRight() // 判断是否只有右子树。
	{
		return _left == nullptr && _right != nullptr;
	}

};

// key : value模型的红黑树。
template <class K, class V>
class KVRBTree
{
public:
	typedef KVRBTreeNode<K, V> Node;
	KVRBTree() : _root(nullptr), _size(0) {} // 构造函数。

	bool insert(const pair<K, V>& kv) // 插入函数。
	{
		// 1. 先按照二叉搜索树的规则插入节点。
		if (_root == nullptr)
		{
			_root = new Node(kv, BLACK); // 根节点必须为黑色。
			_size++;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first) // 左边找
			{
				parent = cur; 
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first) // 右边找
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; // 不允许插入重复的键。
			}
		}
		cur = new Node(kv, RED); // 新插入的节点给红色的好。
		cur->_parent = parent;
		if ((parent->_kv.first) < (cur->_kv.first))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		// 插入成功。
		// -----------------------------------------------------

		while (parent && (parent->_color == RED))
		{
			// 红黑树的条件关键看叔叔。
			Node* grandparent = parent->_parent; // 爷爷节点。
			// 找到叔叔节点。
			Node* uncle = nullptr;
			if (parent == grandparent->_left) 
			{
				uncle = grandparent->_right; // 叔叔是爷爷的右孩子。
				// 情况1: 叔叔存在,且为红色。
				if (uncle && uncle->_color == RED) 
				{
					parent->_color = uncle->_color = BLACK; // 父亲和叔叔变黑。
					grandparent->_color = RED; // 爷爷变红。
					// 继续往上处理。
					cur = grandparent; 
					parent = cur->_parent; 
				}
				else // 叔叔不存在或者为黑色。
				{
					// 情况3: 双旋 --> 变成单旋。
					if (cur == parent->_right)
					{
						RotateL(parent); // parent的位置左单旋。
						swap(cur, parent); // 交换cur和parent。
					}
					// 情况2: 单旋。(也有可能是第3种情况变过来的)
					RotateR(grandparent);
					grandparent->_color = RED;
					parent->_color = BLACK;
					break; 
				}
			}
			else // parent == grandparent->_right
			{
				uncle = grandparent->_left; // 叔叔是爷爷的左孩子。
				if (uncle && uncle->_color == RED) // 情况1: 叔叔存在,且为红色。
				{
					parent->_color = uncle->_color = BLACK; // 父亲和叔叔变黑。
					grandparent->_color = RED; // 爷爷变红。
					// 继续往上处理。
					cur = grandparent;
					parent = cur->_parent;
				}
				else // 叔叔不存在或者为黑色。
				{
					// 情况3: 双旋 --> 变成单旋。
					if (cur == parent->_left)
					{
						RotateR(parent); // parent的位置右单旋。
						swap(cur, parent); // 交换cur和parent。
					}
					// 情况2: 单旋。(也有可能是第3种情况变过来的)
					RotateL(grandparent);
					grandparent->_color = RED;
					parent->_color = BLACK;
					break;
				}
			}
		}
		_root->_color = BLACK; // 根节点必须为黑色。
		_size++;
		return true;
	}

	// 删除函数。
	bool erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (key < (cur->_kv.first)) // 左边找
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > (cur->_kv.first)) // 右边找
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break; // 找到了要删除的节点
			}
		}
		if (cur == nullptr)
		{
			return false; // 没有找到要删除的节点
		}
		// ------------------------------------------------------------------------
		// 找到了要删除的节点,开始。删除节点。
		if ((cur->_left != nullptr) && (cur->_right != nullptr)) // cur有左右子树。
		{
			Node* parentRightMin = cur;
			Node* rightMin = cur->_right;
			while (rightMin->_left)
			{
				parentRightMin = rightMin;
				rightMin = rightMin->_left;
			}
			cur->_kv = rightMin->_kv; // 把右子树的最小节点的值赋给cur。
			parent = parentRightMin; // 更新外部的parent变量。
			cur = rightMin;
		} // cur有左右子树 ==> 把cur换成,最多只有一个节点的位置。
		
		if ((cur->isOnlyLeft()) || (cur->isOnlyRight())) // 要删除的节点有一个子节点。
		{
			Node* child = (cur->_left != nullptr) ? cur->_left : cur->_right;
			cur->_kv = child->_kv;
			cur->_color = BLACK; // 保险起见。
			cur->_left = cur->_right = nullptr;
			cur = child; // 删除cur。
		}
		else // 要删除的是叶子节点。 //else if (cur->isLeaf()) // 要删除的是叶子节点。
		{
			if (isRedNode(cur)) // 情况2：删除的是叶子节点 2.1：要删除的叶子节点是红色
			{
				; // 直接删除,删除以后无需做任何调整
			}
			else // 情况2：删除的是叶子节点 2.2：要删除的叶子节点是黑色
			{
				if (parent == nullptr) // 删除的是根节点,且是黑色叶子节点
				{
					_root = nullptr;
					delete cur;
					cur = nullptr;
					_size--;
					return true;
				}
				Node* doubleBlack = cur; // 双黑节点。
				parent = doubleBlack->_parent; // 更新父节点。
				Node* sibling = (doubleBlack == parent->_left) ? (parent->_right) : (parent->_left); // 更新兄弟节点。
				while (parent != nullptr)
				{
					if (isRedNode(sibling)) // 2.2.1：兄弟是红色
					{
						// 父兄变色,朝双黑旋转,保持双黑继续调整
						parent->_color = RED;
						sibling->_color = BLACK;
						// 朝双黑旋转
						if (doubleBlack == parent->_left)
						{
							RotateL(parent);
						}
						else
						{
							RotateR(parent);
						}
						// 保持双黑继续调整
						parent = doubleBlack->_parent;
						sibling = (doubleBlack == parent->_left) ? (parent->_right) : (parent->_left);
					}
					else // 2.2.2：兄弟是黑色 
					{
						// 2.2.2.2：兄弟节点的孩子都是黑色的
						if ((isBlackNode(sibling->_left)) && (isBlackNode(sibling->_right)))
						{
							sibling->_color = RED; // 兄弟变红。
							if (parent == _root) // 父节点是根节点
							{
								break; // 直接把双黑节点变成单黑节点
							}
							else if (parent->_color == RED) // 父节点是红色
							{
								parent->_color = BLACK; // 父节点变黑。
								break;
							}
							else 
							{
								doubleBlack = doubleBlack->_parent; // 双黑节点上移。
								parent = doubleBlack->_parent; // 更新父节点。
								sibling = (doubleBlack == parent->_left) ? (parent->_right) : (parent->_left); // 更新兄弟节点。
							}
						}
						else // 2.2.2.1：兄弟节点至少有一个红色的孩子
						{
							Node* sibling_L = sibling->_left;
							Node* sibling_R = sibling->_right;
							if (sibling == parent->_left) // L型
							{
								// s是p的左节点;s的左边是黑的,s的右边是红的 LR
								if ((isBlackNode(sibling_L)) && (isRedNode(sibling_R)))
								{
									sibling_R->_color = parent->_color; // r的颜色变成p的颜色.
									parent->_color = BLACK; // p变黑。
									RotateL(sibling); //s的位置左单旋。
									RotateR(parent); // p的位置右单旋。
									break; // 双黑节点变成单黑节点。
								}
								else // LL型
								{
									sibling_L->_color = sibling->_color; // r的颜色变成s的颜色
									sibling->_color = parent->_color; // s的颜色变成p的颜色
									parent->_color = BLACK;
									RotateR(parent); // 右单旋转。
									break; // 双黑节点变成单黑节点。
								}
							}
							else // sibling == parent->_right  R型
							{
								if ((isRedNode(sibling_L)) && (isBlackNode(sibling_R)))
								{
									sibling_L->_color = parent->_color; // r的颜色变成p的颜色.
									parent->_color = BLACK; // p变黑。
									RotateR(sibling); //s的位置右单旋。
									RotateL(parent); // p的位置左单旋。
									break; // 双黑节点变成单黑节点。
								}
								else
								{
									sibling_R->_color = sibling->_color; // r的颜色变成s的颜色
									sibling->_color = parent->_color; // s的颜色变成p的颜色
									parent->_color = BLACK;
									RotateL(parent); // 左单旋转。
									break; // 双黑节点变成单黑节点。
								}
							}
						}
					}
				}
			}
		}
		// =======================================================================
		// 删除并释放cur节点。
		if (cur->_parent)
		{
			(cur->_parent->_left == cur) ? (cur->_parent->_left = nullptr) : (cur->_parent->_right = nullptr);
		}
		else
		{
			_root = nullptr;
		}
		if (_root) // 根节点存在的话,必须是黑色的。
		{
			_root->_color = BLACK; // 根节点必须为黑色。
		}
		delete cur;
		cur = nullptr;
		_size--;
		return true;
	}

	// 查找函数。
	Node* find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < (cur->_kv.first))
			{
				cur = cur->_left;
			}
			else if (key > (cur->_kv.first))
			{
				cur = cur->_right;
			}
			else
			{
				return cur; // 找到节点。
			}
		}
		return nullptr; // 没有找到节点。
	}
	

	void inorder() // 中序遍历。
	{
		_InOrder(_root);
		cout << endl;
	}

	// 验证红黑树的性质。
	bool isValidRBTree()
	{
		Node* pRoot = _root;
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;

		// 检测根节点是否满足情况
		if (BLACK != pRoot->_color)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}

		// 获取任意一条路径中黑色节点的个数
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
				blackCount++;
			pCur = pCur->_left;
		}

		// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}

	// 计算树的高度。
	int height()
	{
		return _Height(_root);
	}

	// 获取树的大小。
	int size()
	{
		return _size;
	}

private:
	Node* _root; // 根节点。
	int _size; // 树的大小。

	// 红节点: 不为空且颜色为红色
	bool isRedNode(Node* node)
	{
		return node != nullptr && node->_color == RED;
	}

	// 黑节点: 为空或者颜色为黑色
	bool isBlackNode(Node* node)
	{
		return ((node == nullptr) || (node->_color == BLACK));
	}

	// 左单旋。
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right; // 右子树
		Node* subRL = subR->_left; // 右子树的左子树
		Node* GrandParent = parent->_parent; // 父节点的父节点
		int flag = 0;
		if (GrandParent)
		{
			if (GrandParent->_left == parent)
			{
				flag = -1; // parent是GrandParent的左子树
			}
			else
			{
				flag = 1; // parent是GrandParent的右子树
			}
		}
		else
		{
			flag = 0; // 根节点
		}
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		parent->_parent = subR;
		if (flag == -1)
		{
			GrandParent->_left = subR;
			subR->_parent = GrandParent;
		}
		else if (flag == 1)
		{
			GrandParent->_right = subR;
			subR->_parent = GrandParent;
		}
		else
		{
			_root = subR; // 根节点
			subR->_parent = nullptr;
		}
	}

	// 右单旋。
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left; // 左子树
		Node* subLR = subL->_right; // 左子树的右子树
		Node* GrandParent = parent->_parent; // 父节点的父节点
		int flag = 0;
		if (GrandParent)
		{
			if (GrandParent->_left == parent)
			{
				flag = -1; // parent是GrandParent的左子树
			}
			else
			{
				flag = 1; // parent是GrandParent的右子树
			}
		}
		else
		{
			flag = 0; // 根节点
		}
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		if (flag == -1)
		{
			GrandParent->_left = subL;
			subL->_parent = GrandParent;
		}
		else if (flag == 1)
		{
			GrandParent->_right = subL;
			subL->_parent = GrandParent;
		}
		else
		{
			_root = subL; // 根节点
			subL->_parent = nullptr;
		}
	}

	// 中序遍历的子函数。
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << "\"" << root->_kv.first << "\" : \"" << root->_kv.second << "\" , ";
		_InOrder(root->_right);
	}

	// 验证红黑树的性质的子函数。
	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		// 走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}

		// 统计黑色节点的个数
		if (BLACK == pRoot->_color)
			k++;

		// 检测当前节点与其双亲是否都为红色
		Node* pParent = pRoot->_parent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}

		return _IsValidRBTree(pRoot->_left, k, blackCount) &&_IsValidRBTree(pRoot->_right, k, blackCount);
	}

	// 计算树的高度的子函数。
	int _Height(Node* root) 
	{
		if (root == nullptr)
		{
			return 0;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return max(leftHeight, rightHeight) + 1;
	}

};
