#ifndef __BSTREE_H__
#define __BSTREE_H__
#include<iostream>
using namespace std;
template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;
	BSTreeNode(const K& key)
		:_key(key)
		, _left(nullptr)
		, _right(nullptr)
	{}
};
template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
private:
	Node* _root;
private:
	//查找->如果找到返回节点指针，否则返回空
	Node* _Find(Node* root, const K& key)
	{
		if (root == nullptr)
			return nullptr;
		if (root->_left < key)
			return _Find(root->_right, key);
		else if (root->_right > key)
			return _Find(root->_left, key);
		else
			return root;
	}
	//插入，插入成功返回true，否则返回false
	bool _Insert(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key < key)
			return _Insert(root->_right, key);
		else if (root->_key > key)
			return _Insert(root->_left, key);
		else
			return false;

	}
	//删除->如果存在该节点，则删除返回true。否则返回false
	//注意形参是Node*引用
	bool _Erase(Node*& root, const K& key)
	{
		if (root == nullptr)
			return false;
		if (root->_key > key)
		{
			return _Erase(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Erase(root->_right, key);
		}
		else
		{
			//找到该节点(root)
			if (root->_left == nullptr)
			{
				Node* del = root;
				root = root->_right;
				delete del;
			}
			else if (root->_right == nullptr)
			{
				Node* del = root;
				root = root->_left;
				delete del;
			}
			else
			{
				//不是叶子节点的情况(即有左右都不为空)
				//寻找右子树的最小节点,并删除
				Node* Minright = root->_right;//右子树一定存在，所以Minright!=nullptr
				while (Minright->_left)
				{
					Minright = Minright->_left;
				}
				K min = Minright->_key;
				_Erase(root->_right, min);//删除右子树最小节点
				root->_key = min;//并替换删除节点

			}
			return true;
		}
	}
	//递归销毁树
	void _Destory(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
	//返回该树的树根深拷贝
	//(该树的引用计数始终<=1)
	Node* _Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;
		Node* newRoot = new Node(root->key);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);
		delete root;
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
public:
	BSTree()
		:_root(nullptr)
	{}
	BSTree(const BSTree<K>& t)
	{
		_root = _Copy(t._root);
	}
	//重载赋值运算符，但会存在浅拷贝问题
	BSTree<K>& operator=(const BSTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}
	~BSTree()
	{
		_Destory(_root);
		_root = nullptr;
	}

	Node* Find(const K& key)
	{
		return _Find(_root, key);
	}
	bool Erase(const K& key)
	{
		return _Erase(_root, key);
	}
	bool Insert(const K& key)
	{
		return _Insert(_root, key);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
};


#endif // !__BSTREE_H__

