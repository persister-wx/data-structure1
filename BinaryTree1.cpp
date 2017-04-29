#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<deque>

template<class T>
struct BinTreeNode
{
	BinTreeNode(const T& value)
	:_data(value)
	, _pLeft(NULL)
	, _pRight(NULL)
	{}

	T _data;
	BinTreeNode<T>* _pLeft;
	BinTreeNode<T>* _pRight;
};

template<class T>
class BinaryTree
{
public:
	typedef BinTreeNode<T> Node;
	BinaryTree()
		:_pRoot(NULL)
	{}
	//构造函数
	BinaryTree(char *array, size_t size, const T& invalid)
	{
		size_t index = 0;
		_CreatBinaryTree(array, size, index, invalid,_pRoot);
	}

	//拷贝构造函数
	BinaryTree(const BinaryTree<T>& bt)
	{
		_pRoot = _CopyBinaryTree(bt._pRoot);
	}
	

	//赋值运算符重载
	BinaryTree<T>& operator=(BinaryTree<T>& bt)
	{
		if (this != &bt)//防止自赋值
		{
			//释放旧空间
			_DestoryNode(_pRoot);
			//赋值
			_pRoot = bt._CopyBinaryTree(bt._pRoot);
		}
		return *this;
	}

	//前序遍历:根节点-->左子树-->右子树
	void PreOrder()
	{
		_PreOrder(_pRoot);
		cout << endl;
	}

	//中序遍历：左子树-->根节点--->右子树
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}

	//后序遍历：左子树-->右子树-->根节点
	void PostOrder()
	{
		_PostOrder(_pRoot);
		cout << endl;

	}
	//层序遍历
	void LevelOrder()
	{
		_LevelOrder(_pRoot);
		cout << endl;
	}

	Node* Find(const T& value)
	{
		return _Find(_pRoot, value);
	}

	//查找父节点
	/*Node* Parent(const T& value)
	{
		if (_pRoot == NULL)
		{
			return NULL;
		}
		_Parent(_pRoot,value);
	}
*/
	
	//计算二叉树叶子节点的个数
	int Size()
	{
		int sum = 0;
		return _Size( sum, _pRoot);
	}

	//计算二叉树的高度：1.如果根节点为空 --》高度为0
	//2.根节点不为空 计算左子树的高度  计算右子树的高度  返回两者中的较大值
	int Height()
	{
		return _Height(_pRoot);
	}
	

	//判断两个二叉树是否相等
	friend bool operator ==(BinaryTree<char>& bt1, BinaryTree<char>& bt2);

	~BinaryTree()
	{
		_DestoryNode(_pRoot);
	}
//--------------------------------------------------------保护成员函数
protected:
	int _Size(int& sum,Node* pRoot)
	{
		if (pRoot)
		{
			sum++;
			_Size(sum, pRoot->_pLeft);
			_Size(sum, pRoot->_pRight);
		}
		return sum;
	}

	int _Height(Node* pRoot)
	{
		if (pRoot == NULL)
		{
			return 0;
		}
		int i = _Height(pRoot->_pLeft);
		int j = _Height(pRoot->_pRight);
		return i < j ? j + 1 : i + 1;
	}

	//创建二叉树
	void _CreatBinaryTree(char* array, size_t size, size_t& index, const T& invalid, Node* & _pRoot)
	{
		if (index < size && *(array + index) != invalid)
		{
			//先创建根节点
			_pRoot = new Node(array[index]);
			//创建根的左子树
			_CreatBinaryTree(array, size, ++index, invalid, _pRoot->_pLeft);
			//创建根的右子树
			_CreatBinaryTree(array, size, ++index, invalid, _pRoot->_pRight);
		}
	}

	Node* _CopyBinaryTree(const Node* pRoot)
	{
		Node* pNewNode = NULL;
		if (pRoot)
		{
			//1.拷贝根节点
			pNewNode = new Node(pRoot->_data);
			//2.拷贝左子树
			pNewNode->_pLeft = _CopyBinaryTree(pRoot->_pLeft);
			//3.拷贝右子树
			pNewNode->_pRight = _CopyBinaryTree(pRoot->_pRight);
		}
		return pNewNode;
	}

	//前序遍历
	void _PreOrder(Node* pRoot)
	{
		if (pRoot)
		{
			cout << pRoot->_data << " ";
			_PreOrder(pRoot->_pLeft);
			_PreOrder(pRoot->_pRight);
		}
	}

	//中序遍历
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);

			cout << pRoot->_data << " ";
			
			_InOrder(pRoot->_pRight);
		}
	}

	//后序遍历
	void _PostOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_PostOrder(pRoot->_pLeft);
			_PostOrder(pRoot->_pRight);
			cout << pRoot->_data << " ";
		}
	}

	//层序遍历
	void _LevelOrder(Node* pRoot)
	{
		if (NULL == pRoot)
		{
			return;
		}
		else if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
		{
			cout << pRoot->_data << endl;
		}
		else
		{
			deque<Node*> d;
			d.push_back(pRoot);
			while (!d.empty())
			{
				Node* cur = d.front();
				cout << cur->_data << " ";
				d.pop_front();
				if (cur->_pLeft)
				{
					d.push_back(cur->_pLeft);
				}
				if (cur->_pRight)
				{
					d.push_back(cur->_pRight);
				}
			}
		}
	}

	//查找具体的节点(有问题，还需在二叉搜索树中给出查找方法）
	/*Node* _Find(Node* pRoot, const T& value)
	{
		if (pRoot)
		{
			if (pRoot->_data == value)
			{
				return pRoot;
			}
			return _Find(pRoot->_pLeft, value);
			return _Find(pRoot->_pRight, value);
		}
		return NULL;
	}*/

	//注意：释放节点只能选择后序遍历,只有这样才不会丢失未释放的节点
	void _DestoryNode(Node*& pRoot)
	{
		if (pRoot)
		{
			_DestoryNode(pRoot->_pLeft);
			
			_DestoryNode(pRoot->_pRight);

			delete pRoot;
			pRoot = NULL;
		}
	}

private:
	Node* _pRoot;
};


//1。根节点为空  2.根节点不为空，根节点数据相等，左子树相等且右子树相等  3.其他
bool Equal(BinTreeNode<char>* pRoot1, BinTreeNode<char>* pRoot2)
{
	if (pRoot1 == NULL && pRoot2 == NULL)
	{
		return true;
	}
	else if (pRoot1 != NULL && pRoot2 != NULL && pRoot1->_data == pRoot2->_data && Equal(pRoot1->_pLeft, pRoot2->_pLeft) /
		Equal(pRoot1->_pRight, pRoot2->_pRight))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator ==(BinaryTree<char>& bt1, BinaryTree<char>& bt2)
{
	return Equal(bt1._pRoot, bt2._pRoot);
}

void Test1()
{
	char* str = "124###35##6";
	BinaryTree<char > bt(str, strlen(str), '#');
	bt.LevelOrder();
	cout << bt.Size() << endl;
	cout << bt.Height() << endl;
	/*BinTreeNode<char >* pos = bt.Find('6');
	if (pos)
	{
		cout << pos->_data << endl;
	}*/
	////bt.PreOrder();
	////bt.InOrder();
	//bt.PostOrder();
	//BinaryTree<char > bt2(bt);
	////bt2.PreOrder();
	////bt2.InOrder();
	//bt.PostOrder();
	//BinaryTree<char > bt3;
	//bt3 = bt2;
	//bt3.PostOrder();

}

void Test2()
{
	char* str = "124###35##6";
	BinaryTree<char > bt(str, strlen(str), '#');
	bt.LevelOrder();
	BinaryTree<char> bt2(bt);
	cout <<( bt == bt2) << endl;
	BinaryTree<char> bt3;
	cout << (bt3 == bt) << endl;
}

int main()
{
	Test2();
	return 0;
}


