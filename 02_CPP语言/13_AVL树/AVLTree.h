#pragma once

// 代码完成于2026年8月31日,初次写于一星期以前左右。

// VS2026编译器下面。
#include <iostream> // cout, endl
#include <utility> // pair, make_pair
#include <cstdlib> // VS2026中abs()函数的头文件。
#include <xutility> // VS2026中max()函数的头文件。
#include <algorithm> // max。
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::max;
using std::abs; 

/*
 * AVL树插入和删除说明:
 *
 * AVL树本质上是二叉搜索树，但要求任意节点的左右子树高度差不超过 1。
 * 因此插入、删除后，都可能需要向上更新平衡因子，并通过旋转恢复平衡。
 *
 * 一、插入操作:
 * 1. 先按二叉搜索树规则查找插入位置。
 *    key 小于当前节点，向左走；key 大于当前节点，向右走；
 *    key 相等说明已存在，插入失败，返回 false。
 *
 * 2. 找到空位置后创建新节点，并连接到 parent 的左孩子或右孩子位置，
 *    同时设置新节点的父指针。
 *
 * 3. 插入后，从 parent 开始向上更新平衡因子:
 *    插入到左子树，parent->_bf--；
 *    插入到右子树，parent->_bf++。
 *
 * 4. 更新后分三种情况:
 *    parent->_bf == 0:
 *      子树高度不再增加，调整结束。
 *
 *    parent->_bf == 1 或 parent->_bf == -1:
 *      子树高度增加，继续向上更新。
 *
 *    parent->_bf == 2 或 parent->_bf == -2:
 *      当前节点失衡，需要旋转，旋转后插入调整结束。
 *
 * 5. 插入失衡旋转类型:
 *    parent->_bf == 2:
 *      右右型: RotateL(parent)
 *      右左型: RotateRL(parent)
 *
 *    parent->_bf == -2:
 *      左左型: RotateR(parent)
 *      左右型: RotateLR(parent)
 *
 * 二、删除操作:
 * 1. 先按二叉搜索树规则查找要删除的节点。
 *    找不到返回 false。
 *
 * 2. 如果要删除的节点有两个孩子:
 *    找右子树最小节点 rightMin，用 rightMin 的值覆盖当前节点，
 *    然后把真正要删除的节点改为 rightMin。
 *    此时问题转化为删除一个最多只有一个孩子的节点。
 *
 * 3. 使用 p 记录替代 cur 位置的节点:
 *    cur 有左孩子，p = cur->_left；
 *    否则 p = cur->_right。
 *    如果 cur 是叶子节点，则 p == nullptr。
 *
 * 4. 将 cur 从树中摘下:
 *    cur 是根节点: _root = p；
 *    cur 是父节点左孩子: parent->_left = p；
 *    cur 是父节点右孩子: parent->_right = p；
 *    如果 p 不为空，还要更新 p->_parent。
 *
 * 5. 删除后，从 parent 开始向上更新平衡因子:
 *    左子树变矮，parent->_bf++；
 *    右子树变矮，parent->_bf--。
 *
 * 6. 更新后分三种情况:
 *    parent->_bf == 1 或 parent->_bf == -1:
 *      子树高度没有继续变矮，调整结束。
 *
 *    parent->_bf == 0:
 *      子树高度继续变矮，继续向上更新。
 *
 *    parent->_bf == 2 或 parent->_bf == -2:
 *      当前节点失衡，需要旋转。
 *
 * 7. 删除失衡旋转类型:
 *    parent->_bf == 2:
 *      subR->_bf == 1  : 右右型，RotateL(parent)，继续向上更新。
 *      subR->_bf == 0  : 删除特有情况，RotateL(parent)，调整结束。
 *      subR->_bf == -1 : 右左型，RotateRL(parent)，继续向上更新。
 *
 *    parent->_bf == -2:
 *      subL->_bf == -1 : 左左型，RotateR(parent)，继续向上更新。
 *      subL->_bf == 0  : 删除特有情况，RotateR(parent)，调整结束。
 *      subL->_bf == 1  : 左右型，RotateLR(parent)，继续向上更新。
 *
 * 插入和删除区别:
 * 1. 插入时，在第一个失衡节点旋转后，调整通常结束。
 * 2. 删除时，旋转后子树高度可能继续变矮，可能还要继续向上调整。
 *
 * 时间复杂度:
 * 插入、删除、查找均为 O(log N)。
 */

// ==========================================================================================================================
// 一: K模型的AVL树。
// ==========================================================================================================================

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


// key模型的AVL树的节点。
template <class K>
class KAVLTreeNode
{
public:
	KAVLTreeNode<K>* _left; // 左
	KAVLTreeNode<K>* _right; // 右
	KAVLTreeNode<K>* _parent; // 父
	int _bf; // 平衡因子
	K _key; // 键
	KAVLTreeNode(const K& key = K()) // 构造函数。
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
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


template <class K>
class KAVLTree
{
public:
	typedef KAVLTreeNode<K> Node;
	KAVLTree() : _root(nullptr), _size(0) {} // 构造函数。

	// AVL树的插入操作。
	bool insert(const K& key) // 插入函数。
	{
		// =====================================================================
		// (1). 先按照搜索二叉树的规则进行插入。
		if (_root == nullptr)
		{
			_root = new Node(key);
			++(this->_size); // 节点个数加1。
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key) // 去左边找。
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) // 去右边找。
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; // 不允许插入重复的键值对。
			}
		}
		cur = new Node(key);
		if (key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent; // 连接parent

		// =====================================================================
		// (2). 更新祖先节点的平衡因子。
		// (3). 如果出现不平衡,就进行旋转处理。
		while (parent)
		{
			// (2). 更新祖先节点的平衡因子。
			if (cur == parent->_left) // cur是parent的左子树
			{
				parent->_bf--;
			}
			else // cur是parent的右子树
			{
				parent->_bf++;
			}
			// (3). 如果出现不平衡,就进行旋转处理。 
			if (parent->_bf == 0)
			{
				break; // 高度没有变,不影响上层。
			}
			else if ((parent->_bf == 1) || (parent->_bf == -1))
			{
				cur = parent;
				parent = parent->_parent; // 继续向上。
			}
			else if ((parent->_bf == 2) || (parent->_bf == -2))
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (cur->_bf == -1)
					{
						RotateRL(parent);
					}
				}
				else // (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (cur->_bf == 1)
					{
						RotateLR(parent);
					}
				}
				break; 
			}
		}
		++(this->_size); // 节点个数加1。
		return true;
	}
	
	// AVL树的删除操作。
	bool erase(const K& key) // 删除函数。
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < (cur->_key))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > (cur->_key))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}
		if (cur == nullptr) // 没有找到。
		{
			return false;
		}
		// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		// 找到了。 cur 就是我们最后要删除的节点。
		Node* p = nullptr;  // 删除cur以后,替代cur位置的节点
		int replacement_of_cur = 0;
		// replacement_of_cur cur和parent节点的关系。
		// replacement_of_cur = 0, cur和parent节点的左节点。
		// replacement_of_cur = 1, cur和parent节点的右节点。
		if ((cur->_left != nullptr) && (cur->_right != nullptr)) // cur有左右子树。
		{
			Node* parentRightMin = cur;
			Node* rightMin = cur->_right;
			while (rightMin->_left)
			{
				parentRightMin = rightMin;
				rightMin = rightMin->_left;
			}
			cur->_key = rightMin->_key; // 替换。
			parent = parentRightMin; // 更新外部的parent变量。
			cur = rightMin;
		} // cur有左右子树 ==> 把cur换成,最多只有一个节点的位置。
		if (cur->_left != nullptr) // cur只有左子树。
		{
			p = cur->_left;
		}
		else // cur只有右子树。或者 cur是叶子。
		{
			p = cur->_right;
			// cur只有右子树,使用cur的右边代替cur的位置。
			// cur是叶子节点,也使用cur的右边代替cur的位置,左右都是NULL,效果是一样的。
		}
		if (parent == nullptr) // cur是根节点
		{
			//this->_root = nullptr; // 只需要把_root置为空,后面释放cur即可。
			this->_root = p;
			if (p)
			{
				p->_parent = nullptr;
			}
		}
		else
		{
			if (cur == (parent->_left)) // cur是parent的左孩子。
			{
				parent->_left = p;
				replacement_of_cur = 0; // 删除掉的是parent的左孩子
			}
			else // cur是parent的右孩子。
			{
				parent->_right = p;
				replacement_of_cur = 1; // 删除掉的是parent的右孩子。
			}
			if (p != nullptr) // 如果replacement不为空,更新它的父亲指针。
			{
				p->_parent = parent; // 更新 replacement 的父指针
			}
			// 删除完成。
			// ==================================================================================
			// ============================== 向上更新平衡因子 =====================================
			int Isfirst = 1;
			while (parent != nullptr)
			{
				if (Isfirst)
				{
					if (replacement_of_cur == 0) // cur是parent的左子树。
					{
						parent->_bf++; // 左子树删除的,bf++
					}
					else
					{
						parent->_bf--;
					}
					Isfirst = 0;
				}
				else
				{
					if (p == parent->_left)
					{
						parent->_bf++; // 左子树删除的,bf++
					}
					else
					{
						parent->_bf--;
					}
				}
				if ((parent->_bf == 1) || (parent->_bf == -1))
				{
					break; // 高度没有变化。
				}
				else if (parent->_bf == 0) // 高度变矮了,继续向上更新。
				{
					p = parent;
					parent = parent->_parent;
				}
				else // parent->_bf == 2 或者 parent->_bf == -2。
				{
					if (parent->_bf == 2)
					{
						Node* subR = parent->_right;
						if (subR->_bf == 1) // 左单旋处理。
						{
							// 对parent的位置进行左单旋转。
							RotateL(parent);
							// 树的高度减小,需要继续向上更新。
							p = subR;
							parent = subR->_parent;
						}
						else if (subR->_bf == 0)
						{
							RotateL(parent);
							parent->_bf = 1;
							subR->_bf = -1;
							break; // 树的高度没有变。
						}
						else // subR->_bf == -1。
						{
							Node* subRL = subR->_left;
							RotateRL(parent);
							p = subRL;
							parent = subRL->_parent;
						}
					}
					else // parent->_bf == -2
					{
						Node* subL = parent->_left;
						if (subL->_bf == -1)
						{
							RotateR(parent);
							p = subL;
							parent = subL->_parent;
						}
						else if (subL->_bf == 0)
						{
							RotateR(parent);
							parent->_bf = -1;
							subL->_bf = 1;
							break;
						}
						else 
						{
							Node* subLR = subL->_right;
							RotateLR(parent);
							p = subLR;
							parent = subLR->_parent;
						}
					}
				}
			}
		}
		delete cur; // 释放。
		cur = nullptr; // 置空。
		--(this->_size);
		return true;
	}

	// AVL树的查找操作。
	bool find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				return true; // 找到了。
			}
		}
		return false; // 没有找到。
	}

	int size() // 节点个数
	{
		return _size;
	}
	 
	int height() // 树的高度
	{
		return _Height(_root);
	}

	void inOrder() // 中序遍历
	{
		_InOrder(_root);
		cout << endl;
	}

	bool isBalance() // 判断是否是平衡二叉树。
	{
		return IsBalance(_root);
	}

private:
	Node* _root = nullptr; // 根节点。
	int _size = 0; // 节点个数。

	void RotateL(Node* parent) // 左单旋
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
		else // parent是根节点。
		{
			flag = 0; // 根节点
		}
		parent->_right = subRL;
		if (subRL) // subRL不为空,则连接parent
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
		parent->_bf = subR->_bf = 0; // 更新平衡因子
	}

	void RotateR(Node* parent) // 右单旋
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
		else // parent是根节点。
		{
			flag = 0; // 根节点
		}
		parent->_left = subLR;
		if (subLR) // subLR不为空,则连接parent
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
		parent->_bf = subL->_bf = 0; // 更新平衡因子
	}

	void RotateRL(Node* parent) // 右左双旋。
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf_subRL = subRL->_bf;
		RotateR(subR);
		RotateL(parent);
		if (bf_subRL == -1) // 在b插入。// 或者在c删除。
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf_subRL == 1) // 在c插入。// 或者是在b删除。
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else // subRL是新插入的节点。
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
	}

	void RotateLR(Node* parent) // 左右双旋
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf_subLR = subLR->_bf;
		RotateL(subL);
		RotateR(parent);
		if (bf_subLR == -1) // 在b插入。
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf_subLR == 1) // 在c插入。
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else // subLR是新插入的节点。
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}
	
	int _Height(Node* root) // 计算树的高度的子函数
	{
		if (root == nullptr)
		{
			return 0;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return max(leftHeight, rightHeight) + 1;
	}

	void _InOrder(Node* root) // 中序遍历的子函数
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	bool IsBalance(Node* root) // 判断是否是平衡二叉树的子函数
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		if (abs(leftHeight - rightHeight) > 1)
		{
			return false;
		}
		return IsBalance(root->_left) && IsBalance(root->_right);
	}

};


// ==========================================================================================================================
// ==========================================================================================================================
// ==========================================================================================================================

// ============================================================================================
// KVAVLTree 接口说明（KV模型）
// ============================================================================================

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

// KV模型的AVL树的节点。
template <class K, class V>
class KVAVLTreeNode
{
public:
	KVAVLTreeNode<K, V>* _left; // 左
	KVAVLTreeNode<K, V>* _right; // 右
	KVAVLTreeNode<K, V>* _parent; // 父
	int _bf; // 平衡因子
	pair<K, V> _kv; // 键值对

	KVAVLTreeNode(const pair<K, V>& kv = pair<K, V>())
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
		, _kv(kv)
	{}

};

// KV模型的AVL树。
template <class K, class V>
class KVAVLTree
{
public:
	typedef KVAVLTreeNode<K, V> Node;
	KVAVLTree() : _root(nullptr) {} // 构造函数。

	bool insert(const pair<K, V>& kv) // 插入函数。
	{
		// =====================================================================
		// 1. 先按照搜索二叉树的规则进行插入。
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < (cur->_kv.first)) // 去左边找。
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > (cur->_kv.first)) // 去右边找。
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; // 不允许插入重复的键值对。
			}
		}
		cur = new Node(kv);
		if (kv.first < (parent->_kv.first))
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent; // 连接parent

		// =====================================================================
		// 2. 更新平衡因子。
		while (parent)
		{
			if (cur == parent->_left) // cur是parent的左子树
			{
				parent->_bf--;
			}
			else // cur是parent的右子树
			{
				parent->_bf++;
			}
			// 1. 更新完以后,如果parent->_bf == 0,表示parent的高度没有变,后面就不会影响上面的祖先了。
			if (parent->_bf == 0)
			{
				break;
			}
			// 2. 更新完parent的bf,如果parent-->bf == 1或者-1,说明parent的高度变高了,继续往上更新。
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent; // 继续向上。
			}
			// 3. 更新完parent的bf,如果parent-->bf == 2或者-2,说明parent的子树出现了不平衡,需要旋转处理。
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2) // 右子树高
				{
					if (parent->_right->_bf == 1) // RR型 -> 左单旋
					{
						RotateL(parent);
					}
					else if (parent->_right->_bf == -1) // RL型 -> 右左双旋
					{
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2) // 左子树高
				{
					if (parent->_left->_bf == -1) // LL型 -> 右单旋
					{
						RotateR(parent);
					}
					else if (parent->_left->_bf == 1) // LR型 -> 左右双旋
					{
						RotateLR(parent);
					}
				}
				break;
				// 旋转完成之后,parent所在的树就恢复到了,插入之前的高度
				// 如果是子树,对上层影响,更新结束。
			}
		}
		++(this->_size); // 节点个数加1。
		return true;
	}

	bool erase(const K& key) // 删除函数。
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (key < (cur->_kv.first))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > (cur->_kv.first))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}
		if (cur == nullptr) // 没有找到。
		{
			return false;
		}
		Node* p = nullptr;  // 删除cur以后,替代cur位置的节点
		int cur_of_parent = 0; // replacement_of_cur cur和parent节点的关系。
		if ((cur->_left != nullptr) && (cur->_right != nullptr)) // cur有左右子树。
		{
			Node* parentRightMin = cur;
			Node* rightMin = cur->_right;
			while (rightMin->_left)
			{
				parentRightMin = rightMin;
				rightMin = rightMin->_left;
			}
			cur->_kv.first = rightMin->_kv.first; // 替换。
			cur->_kv.second = rightMin->_kv.second; // 替换。
			parent = parentRightMin; // 更新外部的parent变量。
			cur = rightMin;
		} // cur有左右子树 ==> 把cur换成,最多只有一个节点的位置。
		if (cur->_left != nullptr) // cur只有左子树。
		{
			p = cur->_left;
		}
		else // cur只有右子树。或者 cur是叶子。
		{
			p = cur->_right;
			// cur只有右子树,使用cur的右边代替cur的位置。
			// cur是叶子节点,也使用cur的右边代替cur的位置,左右都是NULL,效果是一样的。
		}
		if (parent == nullptr) // 处理只有1个节点,或者只有2个节点的情况。
		{
			_root = p;
			if (p)
			{
				p->_parent = nullptr;
			}
		}
		else
		{
			if (cur == (parent->_left)) // cur是parent的左孩子。
			{
				parent->_left = p;
				cur_of_parent = 0; // 删除掉的是parent的左孩子
			}
			else // cur是parent的右孩子。
			{
				parent->_right = p;
				cur_of_parent = 1; // 删除掉的是parent的右孩子。
			}
			if (p != nullptr) // 如果replacement不为空,更新它的父亲指针。
			{
				p->_parent = parent; // 更新 replacement 的父指针
			}
			// 删除完成。
			// ==================================================================================
			// ============================== 向上更新平衡因子 =====================================
			int Isfirst = 1;
			while (parent != nullptr)
			{
				if (Isfirst)
				{
					if (cur_of_parent == 0) // cur是parent的左子树。
					{
						parent->_bf++; // 左子树删除的,bf++
					}
					else
					{
						parent->_bf--;
					}
					Isfirst = 0;
				}
				else
				{
					if (p == parent->_left)
					{
						parent->_bf++; // 左子树删除的,bf++
					}
					else
					{
						parent->_bf--;
					}
				}
				if ((parent->_bf == 1) || (parent->_bf == -1))
				{
					break; // 高度没有变化。
				}
				else if (parent->_bf == 0) // 高度变矮了,继续向上更新。
				{
					p = parent;
					parent = parent->_parent;
				}
				else // parent->_bf == 2 或者 parent->_bf == -2。
				{
					if (parent->_bf == 2)
					{
						Node* subR = parent->_right;
						if (subR->_bf == 1) // 左单旋处理。
						{
							// 对parent的位置进行左单旋转。
							RotateL(parent);
							// 树的高度减小,需要继续向上更新。
							p = subR;
							parent = subR->_parent;
						}
						else if (subR->_bf == 0)
						{
							RotateL(parent);
							parent->_bf = 1;
							subR->_bf = -1;
							break; // 树的高度没有变。
						}
						else // subR->_bf == -1。
						{
							Node* subRL = subR->_left;
							RotateRL(parent);
							p = subRL;
							parent = subRL->_parent;
						}
					}
					else // parent->_bf == -2
					{
						Node* subL = parent->_left;
						if (subL->_bf == -1)
						{
							RotateR(parent);
							p = subL;
							parent = subL->_parent;
						}
						else if (subL->_bf == 0)
						{
							RotateR(parent);
							parent->_bf = -1;
							subL->_bf = 1;
							break;
						}
						else
						{
							Node* subLR = subL->_right;
							RotateLR(parent);
							p = subLR;
							parent = subLR->_parent;
						}
					}
				}
			}
		}
		delete cur;
		--(this->_size);
		return true;
	}

	bool find(const K& key) // 查找函数。
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
				return true; // 找到了。
			}
		}
		return false; // 没有找到。
	}

	void inOrder() // 中序遍历
	{
		_InOrder(_root);
		cout << endl;
	}

	bool isBalance() // 判断是否是平衡二叉树。
	{
		return IsBalance(_root);
	}

	int height() // 树的高度
	{
		return _Height(_root);
	}

	int size() // 节点个数
	{
		return _size;
	}

private:
	Node* _root; // 根节点
	int _size; // 节点个数

	void RotateL(Node* parent) // 左单旋
	{
		// 处理左右子节点
		Node* subR = parent->_right; // 右子树
		Node* subRL = subR->_left; // 右子树的左子树
		Node* GrandParent = parent->_parent; // 父节点的父节点
		int flag = 0;
		// falg = 0 表示parent是根节点,没有父节点
		// flag = -1 表示parent是GrandParent的左子树
		// flag = 1 表示parent是GrandParent的右子树
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
		parent->_bf = subR->_bf = 0; // 更新平衡因子
	}

	void RotateR(Node* parent) // 右单旋
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
		parent->_bf = subL->_bf = 0; // 更新平衡因子
	}

	void RotateRL(Node* parent) // 右左旋转
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf_subRL = subRL->_bf;
		RotateR(subR);
		RotateL(parent);
		if (bf_subRL == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf_subRL == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else // subRL是新插入的节点。
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
	}

	void RotateLR(Node* parent) // 左右旋转
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf_subLR = subLR->_bf;
		RotateL(subL); // 左单旋。
		RotateR(parent); // 右单旋。
		if (bf_subLR == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf_subLR == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else // subLR是新插入的节点
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}

	void _InOrder(Node* root) // 中序遍历的子函数
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}

	bool IsBalance(Node* root) // 判断是否是平衡二叉树的子函数
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		if (abs(leftHeight - rightHeight) > 1)
		{
			return false;
		}
		return IsBalance(root->_left) && IsBalance(root->_right);
	}

	int _Height(Node* root) // 计算树的高度的子函数
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