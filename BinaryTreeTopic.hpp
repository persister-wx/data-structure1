#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>
#include<stack>
#include<queue>

template<class T>
class BinaryTree
{
public:

	template<class T>
	struct BinaryTreeNode
	{
		BinaryTreeNode* _left;
		BinaryTreeNode* _right;
		T _val;
		BinaryTreeNode(const T& val)
			:_left(NULL)
			, _right(NULL)
			, _val(val)
		{}
		BinaryTreeNode()
			:_left(NULL)
			, _right(NULL)
		{}
	};

	typedef BinaryTreeNode<T> Node;

	BinaryTree()
		:_root(NULL)
	{}

	//递归插入
	bool InsertR(const T& key)
	{
		return _InsertR(_root, key);
	}


	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool Find(Node* x)
	{
		assert(x);
		return _Find(_root, x);
	}

	Node* Find(const T& val)
	{
		return _Find(_root, val);
	}

	////时间复杂度是O(N^2)
	//Node* GetLastCommonAncestor(Node* x1, Node* x2)
	//{
	//	assert(x1 && x2);
	//	if (_root == NULL)
	//	{
	//		return NULL;
	//	}
	//	return _GetLastCommonAncestor(_root, x1, x2);
	//}

	//时间复杂度为O(N)
	Node* GetLastCommonAncestor(Node* x1, Node* x2)
	{
		assert(x1 && x2);
		stack<Node*> x1paths;
		stack<Node*> x2paths;
		Find(x1, x1paths);
		Find(x2, x2paths);
		while (x1paths.size() != x2paths.size())
		{
			if (x1paths.size() > x2paths.size())
			{
				x1paths.pop();
			}
			else
			{
				x2paths.pop();
			}
		}
		while (!x1paths.empty() && !x2paths.empty() && x1paths.top() != x2paths.top())
		{
			x1paths.pop();
			x2paths.pop();
		}
		if (x1paths.top() == x2paths.top())
		{
			return x1paths.top();
		}
		return NULL;
	}

	bool Find(Node* x, stack<Node*>& paths)
	{
		return _Find(_root, x, paths);
	}

	////时间复杂度：O(N^2)
	//void FindMaxLen(size_t& Maxlen)//不断更新最远距离
	//{
	//	_FindMaxLen(_root, Maxlen);
	//}
	//时间复杂度是O(N)
	size_t FindMaxLen()//不断更新最远距离
	{
		//这里的Maxlen考虑到线程安全的问题，也就是使得下面调用的函数是可重入的（所有将Maxlen给成临时变量而不是全局变量）
		size_t MaxLen = 0;
		_FindMaxLen(_root, MaxLen);
		return MaxLen;
	}

	size_t Height()
	{
		return _Height(_root);
	}

	Node* ReBulidTree(char* pre, char* In, size_t len)
	{
		if (pre == NULL || In == NULL || len <= 0)
		{
			return NULL;
		}
		return _ReBulidTree(pre, In, In + len);//两段区间都是闭区间;
	}

	bool IsCompleteBinaryTree()
	{
		queue<Node*>  q;
		q.push(_root);
		bool tag = true;
		while (!q.empty())
		{
			Node* front = q.front();
			q.pop();
			if (front->_left)
			{
				if (tag == false)
				{
					return false;
				}
				q.push(front->_left);
			}
			else
			{
				tag = false;
			}
			if (front->_right)
			{
				if (tag == false)
				{
					return false;
				}
				q.push(front->_right);
			}
			else
			{
				tag = false;
			}
		}
		return true;
	}

	void Mirror()
	{
		_Mirror(_root);
	}
	//转换为双向链表
	Node* ToDuplexingList()
	{
		Node* prev = NULL;
		_ToDuplexingList(_root,prev);
		Node* cur = _root;
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return cur;//返回单链表的头
	}

private:
	void _ToDuplexingList(Node* cur, Node*& prev)
	{
		if (cur == NULL)
		{
			return ;
		}
		_ToDuplexingList(cur->_left, prev);
		cur->_left = prev;
		if (prev)
		{
			prev->_right = cur;
		}
		prev = cur;
		_ToDuplexingList(cur->_right, prev);
	}

	void  _Mirror(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
	    swap(root->_left, root->_right);
		_Mirror(root->_left);
		_Mirror(root->_right);
	}

	Node* _ReBulidTree(char*& prev,char* In,char* InEnd)
	{
		if (*prev == '\0')//说明子二叉树已经创建成功了
		{
			return NULL;
		}
		Node* newRoot = new Node(*prev);//有两种情况：1.是叶子节点 2.不是叶子节点
		//1.是叶子节点
		if (In == InEnd)
		{
			return newRoot;
		}
		//2.不是叶子节点,这时就可以确定左右子树的区间了
		char* pos = In;
		while (pos != InEnd)
		{
			if (*pos == *prev)
			{
				break;//说明已经找到根节点了
			}
			pos++;
		}
		//这里的pos一定不能等于InEnd
		assert(pos <= InEnd);
		//左右子树可以利用递归去解决
		newRoot->_left = _ReBulidTree(++prev,In, pos - 1);
		newRoot->_right = _ReBulidTree(++prev,pos + 1, InEnd);
		return newRoot;
	}
	

	size_t _FindMaxLen(Node* root, size_t& Maxlen)
	{
		if (root->_left)
			_FindMaxLen(root->_left, Maxlen);
		if (root->_right)
			_FindMaxLen(root->_right, Maxlen);


		size_t leftlen = 0, rightlen = 0;
			leftlen = _Height(root->_left);
			rightlen = _Height(root->_right);
		if (leftlen + rightlen > Maxlen)
		{
			Maxlen = leftlen + rightlen;
		}
		return leftlen > rightlen ? leftlen + 1 : rightlen + 1;
	}

	size_t _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		size_t leftlen = 0, rightlen = 0;
		if (root->_left)
		 leftlen = _Height(root->_left);
		if (root->_right)
		 rightlen = _Height(root->_right);
		return leftlen > rightlen ? leftlen + 1 : rightlen + 1;
	}

	bool _Find(Node* root, Node* x, stack<Node*>& paths)
	{
		if (root == NULL)
		{
			return false;
		}
		paths.push(root);

		if (root == x)
		{
			return true;
		}
		//说明：只要找到就可以直接返回了
		bool l = _Find(root->_left, x, paths);
		if (l == true)
		{
			return true;
		}
		bool r = _Find(root->_right, x, paths);
		if (r == true)
		{
			return true;
		}
			paths.pop();//到这里就说明在一个节点的左右子树中都没有找到，那么就可以pop出该节点，给递归程序的上层返回false
			return false;
	}

	Node* _Find(Node* root, const T& x)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_val == x)
		{
			return root;
		}
		Node* l = _Find(root->_left, x);
		if (l == NULL)
		{
			return _Find(root->_right, x);
		}	
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_val << " ";
		_InOrder(root->_right);
	}
	bool _InsertR(Node*& root, const T& key)
	{
		if (NULL == root)
		{
			root = new Node(key);
			return true;
		}
		if (root->_val > key)
		{
			return _InsertR(root->_left, key);
		}
		else if (root->_val < key)
		{
			return _InsertR(root->_right, key);
		}
		else
		{
			return false;
		}
	}


	Node* _GetLastCommonAncestor(Node* root, Node* x1, Node* x2)
	{
		//在子树中
		if (root == x1 || _root == x2)
		{
			return root;
		}

		bool x1InLeft = false, x1InRight = false, x2InLeft = false, x2InRight = false;
		x1InLeft = _Find(root->_left, x1);
		if (x1InLeft == false)
		{
			x1InRight = _Find(root->_right, x1);
		}
		x2InLeft = _Find(root->_left, x2);
		if (x2InLeft == false)
			x2InRight = _Find(_root->_right, x2);

		if (x1InLeft && x2InRight || x1InRight && x2InLeft)//一个节点在左子树，一个节点在右子树
		{
			return root;
		}
		else if (x1InLeft && x2InLeft)//两个节点都在左子树
		{
			return _GetLastCommonAncestor(root->_left, x1, x2);
		}
		else if (x1InRight && x2InRight)//两个节点都在右子树
		{
			return _GetLastCommonAncestor(root->_right, x1, x2);
		}
	}

	bool _Find(Node* root, Node* x)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root == x)
		{
			return true;
		}
		bool l = _Find(root->_left, x);
		if (l)
			return true;
		return _Find(root->_right, x);
	}

	Node* _root;
};



测试代码如下：
#include"BinaryTree1.h"


void Test()
{
	int array[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0,};

	BinaryTree<int> tree;
	for (size_t index = 0; index < sizeof(array) / sizeof(int); ++index)
	{
		tree.InsertR(array[index]);
	}

	BinaryTree<int>::Node* head = tree.ToDuplexingList();

	tree.Mirror();

	cout << tree.IsCompleteBinaryTree() << endl;
	tree.InOrder();		
	BinaryTree<int>::Node* n1 = tree.Find(0);
	BinaryTree<int>::Node* n2 = tree.Find(4);
	BinaryTree<int>::Node* ancestor = tree.GetLastCommonAncestor(n1, n2);//3
	/*if (ancestor)
	{
		cout << ancestor->_val << " ";
	}*/
	//cout << tree.Height() << endl;
	cout<<tree.FindMaxLen()<<endl;

	char* prev = "123456";
	char* In = "324165";
	BinaryTree<int>::Node* root = tree.ReBulidTree(prev, In, strlen(In));
}


int main()
{
	Test();
	return 0;
}




