
#include <iostream>

using namespace std;

template <class K>

struct BSTreeNode
{
	BSTreeNode<K>* left;
	BSTreeNode<K>* right;
	K _key;

	BSTreeNode(const K&key)
		:_key(key)
		,left(nullptr)
		,right(nullptr)
	{}
};

template <class K>
struct BSTree
{
	typedef BSTreeNode<K> Node;

	BSTree()
		:_root(nullptr)
	{}
	void Inoder()
	{
		_Inoder(_root);
	}
	void _Inoder(Node* _root)
	{
		if (_root == nullptr)
			return;
		
		_Inoder(_root->left);
		cout << _root->_key << " ";
		_Inoder(_root->right);
	    
	}
	bool insert(const K& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
		}
		else
		{
			Node* cur = _root;
			Node* parent =nullptr;
			while (cur)
			{
				if (cur->_key < val)
				{
					parent = cur;
					cur = cur->right;
				}
				else if (cur->_key > val)
				{
					parent = cur;
					cur = cur->left;
				}
				else
				{
					return false;
				}
			}

			if (parent->_key < val)
			{
				parent->right = new Node(val);
			}
			if (parent->_key > val)
			{
				parent->left = new Node(val);
			}
			
			
		}
		return true;
	}
	bool erase(const K& val)
	{
		//������Ҫ�ҵ�Ҫɾ���Ľ�㣬���������Ҫ��¼���ڵ�
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_key < val)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (cur->_key > val)
			{
				parent = cur;
				cur = cur->left;
			}
			else//�ҵ�Ҫɾ���Ľ����--cur����Ҫɾ���Ľ��
			{
				//1.������Ϊ��,������Ϊ�½�㣬��Ҫ�й¸����ڵ�
				//�����������ɾ�����Ϊ���ڵ�ʱ
				
				if (cur->right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->left;
					}
					else
					{
						if (parent->left == cur)
						{
							parent->left = cur->left;
						}
						else 
						{
							parent->left = cur->left;
						}
					}

				}
				//2.������Ϊ�գ�������Ϊ�½�㣬��Ҫ�й¸����ڵ�
				else if (cur->left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->right;
					}
					else
					{
						if (parent->left == cur)
						{
							parent->left = cur->right;
						}
						else 
						{
							parent->right = cur->right;
						}
					}
				}
				//3.�������������ڣ��ұ�ķ
				else
				{
					//��ķ����ǰҪɾ���������ҽ��
					Node* leftMax = cur->left;
					Node* parent = cur;
					//���ﲻ�ܸ�nullptr
					while (leftMax->right)
					{
						parent = leftMax;
						leftMax = leftMax->right;
					}
					//�ҵ���ķ�󽻻�
					std::swap(cur->_key, leftMax->_key);

					//ת��Ϊ��������--��Ϊ���ҽ����ҽ��϶�Ϊ��
					//����ڵ���ǹ½�㣬��Ҫ�й�
					if (parent->right == leftMax)
					{
						parent->right = leftMax->left;
					}
					if (parent->left == leftMax)
					{
						parent->left = leftMax->left;
					}

					cur = leftMax;
				}

				delete cur;
				return true;
			}
		}
		return false;
	}
private:

	Node* _root;
};


int main()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	int sz = sizeof(a) / sizeof(a[0]);
	BSTree<int> t;
	for (int i = 0; i < sz; i++)
	{
		t.insert(a[i]);
	}
	
	t.Inoder();
	cout << endl;
	
	/*t.erase(8);
	t.erase(3);
	t.erase(1);*/
	for (auto& e : a)
	{
		t.erase(e);
	}
	t.Inoder();
	cout << endl;


}