
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
		//首先需要找到要删除的结点，这个过程需要记录父节点
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
			else//找到要删除的结点了--cur就是要删除的结点
			{
				//1.右子树为空,左子树为孤结点，需要托孤给父节点
				//特殊情况：当删除结点为根节点时
				
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
				//2.左子树为空，右子树为孤结点，需要托孤给父节点
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
				//3.左右子树都存在，找保姆
				else
				{
					//保姆：当前要删除结点的最右结点
					Node* leftMax = cur->left;
					Node* parent = cur;
					//这里不能给nullptr
					while (leftMax->right)
					{
						parent = leftMax;
						leftMax = leftMax->right;
					}
					//找到保姆后交换
					std::swap(cur->_key, leftMax->_key);

					//转化为上面问题--因为最右结点的右结点肯定为空
					//那左节点就是孤结点，需要托孤
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