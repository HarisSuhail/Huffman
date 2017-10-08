//Inclusion model followed.

#ifndef BINARY_TREE_H
#define BINARY_TREE_H
template <class T>
class Tree;


template <class T>
class node{

	friend class Tree<T>;
private:
	node* left, *right, *parent;
	T data;
public:
	node()
	{
		left = right = parent = NULL;

	}
	~node()
	{

		//delete left; delete right; delete parent;
	}

	node(node* left, node* right)
	{
		this->left = left;
		this->right = right;

	}
	node(node* parent)
	{
		this->parent = parent;
	}
	void setData(T data)  //sets data equal to the argument
	{
		this->data = data;
	}
	T getData()  //returns the data
	{
		return this->data;
	}


};



template <class T>
class Tree{
private:
	node<T>* root;
	node<T>* current;
public:
	Tree()
	{
		root = current = NULL;
	}

	void reset()  //sets current equal to root
	{
		current = root;
	}
	void moveLeft()  //moves the current pounter to its left child
	{
		current = current->left;
	}
	void moveRight()  //moves the current pointer to its right child
	{
		current = current->right;
	}
	T getData()  //returns current's data
	{

		return current->data;
	}

	bool isLeaf()  //returns true if current is pointing towards a leaf node
	{
		if (current->left == NULL && current->right == NULL)
		{
			return true;
		}
		return false;
	}

	~Tree()
	{
		clear(root);
	}

	Tree(const Tree& t)
	{

		root = new node<T>();
		root = copyTree(t.root);

	}
	void operator = (Tree& t)  //operator = is being overloaded
	{

		root = new node<T>();
		root = copyTree(t.root);
	}
	T link(node<T>* t, node<T>* cpy)
	{
		cpy->right = NULL;
		cpy->left = NULL;
		if (t->right != NULL)
		{
			cpy->right = new node<T>();
			cpy->right->data = link(t->right, cpy->right);
		}
		if (t->left != NULL)
		{
			cpy->left = new node<T>();
			cpy->left->data = link(t->left, cpy->left);
		}
		return t->data;

	}

	node<T>* copyTree(node<T>* root)  //copies one tree into another
	{
		node<T>* copyNode = NULL;
		if (root)
		{
			copyNode = new node<T>();
			copyNode->data = root->data;
			copyNode->left = copyTree(root->left);
			copyNode->right = copyTree(root->right);
		}
		return copyNode;
	}

	void clear(node<T>* d)  //clears the whole tree
	{
		root = NULL;
		if (d == NULL) return;
		clear(d->right);
		clear(d->left);
		delete d;
	}

	T getRootData()  //gives the data of the root
	{
		return root->data;
	}


	//makes the first argument the left subtree and the second argument the right subtree of the tree whose function is called
	void mergeTrees(Tree& left, Tree& right)
	{


		if (root == NULL)
			root = new node<T>();
		root->left = left.root;
		root->right = right.root;
		left.root = NULL;
		right.root = NULL;

	}

	void setRootData(T data)  //Sets data of root
	{
		root = new node<T>();
		root->data = data;
	}

	void addSingleItem(T data)  //Adds a single item
	{
		if (root == NULL)
		{
			root = new node<T>();
			root->data = data;
			root->parent = NULL;
			root->left = NULL;
			root->right = NULL;
		}
	}

	void traverse()  //Traverses the whole tree
	{
		cout << "Start From Root.";
		traverse_utility(root);

	}
	
	string getCode(int eof)
	{
		string t = getCode_utility( root, true);
		reverse(t.begin(), t.end());
		return t;
	}
	string getCode(char x)
	{
		string t = getCode_utility(x, root, true);
		reverse(t.begin(), t.end());
		return t;
	}


	string getCode_utility( node<T>* nde, bool LoR)
	{
		if (nde == NULL) return "";
		string t;


		t = getCode_utility( nde->left, false) + getCode_utility( nde->right, true);

		if (nde->data == 1 || t != "")
		{
			
			if (nde == root) return t + "";
			return t + (LoR ? "1" : "0");
		}
		return t;




	}



	string getCode_utility(char x, node<T>* nde, bool LoR)
	{
		if (nde == NULL) return "";
		string t;


		t = getCode_utility(x, nde->left, false) + getCode_utility(x, nde->right, true);

		if (nde->data == x || t != "")
		{
			if (nde == root) return t + "";
			return t + (LoR ? "1" : "0");
		}
		return t;




	}




	void traverse_utility(node<T>* d)  //Traversal logic
	{

		if (d == NULL) return;
		cout << "Go Left\n";
		traverse_utility(d->left);
		cout << "Go Back...Print: ";
		cout << d->data << " ";
		cout << "Go right\n";
		traverse_utility(d->right);
		cout << "Go back\n";
	}


	bool operator < (Tree & t)  //operator < is being overloaded
	{
		return this->root->data < t.root->data;

	}
	bool operator >(Tree & t)  //operator > is being overloaded
	{
		return this->root->data > t.root->data;

	}




	friend ostream& operator << <>(ostream &, Tree<T>&);
};

template <class T>
ostream& operator << (ostream & out, Tree<T>& tree)  //operator << is being overloaded
{
	tree.traverse();
	return out;
}

#endif