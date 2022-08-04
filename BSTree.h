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
	//����->����ҵ����ؽڵ�ָ�룬���򷵻ؿ�
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
	//���룬����ɹ�����true�����򷵻�false
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
	//ɾ��->������ڸýڵ㣬��ɾ������true�����򷵻�false
	//ע���β���Node*����
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
			//�ҵ��ýڵ�(root)
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
				//����Ҷ�ӽڵ�����(�������Ҷ���Ϊ��)
				//Ѱ������������С�ڵ�,��ɾ��
				Node* Minright = root->_right;//������һ�����ڣ�����Minright!=nullptr
				while (Minright->_left)
				{
					Minright = Minright->_left;
				}
				K min = Minright->_key;
				_Erase(root->_right, min);//ɾ����������С�ڵ�
				root->_key = min;//���滻ɾ���ڵ�

			}
			return true;
		}
	}
	//�ݹ�������
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
	//���ظ������������
	//(���������ü���ʼ��<=1)
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
	//���ظ�ֵ��������������ǳ��������
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

