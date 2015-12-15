#pragma once
#include <iostream>
#include <exception>

using namespace std;

template<typename dataType>
class BinarySearchTreeNode
{
public:
	dataType key;
	BinarySearchTreeNode *left;
	BinarySearchTreeNode *right;
	BinarySearchTreeNode *parent;
public:
	BinarySearchTreeNode(dataType _key = dataType{} , BinarySearchTreeNode *_left = NULL, BinarySearchTreeNode *_right = NULL, BinarySearchTreeNode *_parent = NULL): key{_key}, left{_left}, right{_right}, parent{_parent} {}
	BinarySearchTreeNode(const BinarySearchTreeNode &node): key{node.key}, left{node.left}, right{node.right}, parent{node.parent} {}
	BinarySearchTreeNode &operator=(const BinarySearchTreeNode &node) {
		key = node.key;
		left = node.left;
		right = node.right;
		parent = node.parent;
		return *this;
	}

	~BinarySearchTreeNode() {}
	void print() {
		cout << key << " ";
	}
};

template<class TreeNode>
class BinarySearchTree
{
protected:
	TreeNode *NIL;
	TreeNode *root;
public:
	BinarySearchTree(): NIL{new TreeNode}, root{NIL} {
		cout << "enter the number of nodes and the node to insert" << endl;
		int num;
		cin >> num;
		decltype(TreeNode::key)  key;
		while (num-- != 0) {
			cin >> key;
			insert(key);
		}
	}

	virtual ~BinarySearchTree() {
		makeEmpty(root);
		delete NIL;
	}

	decltype(TreeNode::key) maximum();
	decltype(TreeNode::key) minimum();
	void preorder();
	void inorder();
	void postorder();
	bool search(decltype(TreeNode::key) key);
	void virtual insert(decltype(TreeNode::key) key);
	void virtual remove(decltype(TreeNode::key) key);

protected:
	void makeEmpty(TreeNode *T);
	TreeNode *maximum(TreeNode *T);
	TreeNode *minimum(TreeNode *T);
	void preorder(TreeNode *T);
	void inorder(TreeNode *T);
	void postorder(TreeNode *T);
	void visit(TreeNode *T);
	bool search(TreeNode *T, decltype(TreeNode::key) key);
	void virtual insert(TreeNode *&T, decltype(TreeNode::key) key);
	void virtual remove(TreeNode *T, decltype(TreeNode::key) key);
	void transplant(TreeNode *u, TreeNode *v);

	TreeNode *successor(TreeNode *node);
	TreeNode *predecessor(TreeNode *node);
};

template<class TreeNode>
decltype(TreeNode::key) BinarySearchTree<TreeNode>::maximum() {
	try {
		if (root != NIL)
			return maximum(root)->key;
		else
			throw logic_error("Tree is empty, can not find maximum\n");
	} catch (const logic_error &e) {
		cerr << e.what();
	}
}

template<class TreeNode>
decltype(TreeNode::key) BinarySearchTree<TreeNode>::minimum() {
	try {
		if (root != NIL)
			return minimum(root)->key;
		else
			throw logic_error("Tree is empty, can not find minimum\n");
	} catch (const logic_error &e) {
		cerr << e.what();
	}
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::preorder() {
	preorder(root);
	cout << endl;
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::inorder() {
	inorder(root);
	cout << endl;
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::postorder() {
	postorder(root);
	cout << endl;
}

template<class TreeNode>
bool BinarySearchTree<TreeNode>::search(decltype(TreeNode::key) key) {
	return search(root, key);
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::insert(decltype(TreeNode::key) key) {
	insert(root, key);
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::remove(decltype(TreeNode::key) key) {
	remove(root, key);
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::makeEmpty(TreeNode *T) {
	if (T != NIL) {
		makeEmpty(T->left);
		makeEmpty(T->right);
		delete T;
		T = NIL;
	}
}

template<class TreeNode>
TreeNode *BinarySearchTree<TreeNode>::maximum(TreeNode *T) {
	while (T != NIL && T->right != NIL)
		T = T->right;
	return T;
}

template<class TreeNode>
TreeNode *BinarySearchTree<TreeNode>::minimum(TreeNode *T) {
	while (T != NIL && T->left != NIL)
		T = T->left;
	return T;
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::preorder(TreeNode *T) {
	if (T != NIL) {
		visit(T);
		preorder(T->left);
		preorder(T->right);
	}
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::inorder(TreeNode *T) {
	if (T != NIL) {
		inorder(T->left);
		visit(T);
		inorder(T->right);
	}
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::postorder(TreeNode *T) {
	if (T != NIL) {
		postorder(T->left);
		postorder(T->right);
		visit(T);
	}
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::visit(TreeNode *T) {
	if (T != NIL)
		T->print();
}

template<class TreeNode>
bool BinarySearchTree<TreeNode>::search(TreeNode *T, decltype(TreeNode::key) key) {
	if (T != NIL) {
		if (key == T->key)
			return true;
		else if (key < T->key)
			return search(T->left, key);
		else
			return search(T->right, key);
	}
	else
		return false;
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::insert(TreeNode *&T, decltype(TreeNode::key) key) {
	if (T != NIL) {
		if (key < T->key) {
			insert(T->left, key);
			T->left->parent = T;
		}
		else if (key > T->key) {
			insert(T->right, key);
			T->right->parent = T;
		}
	}
	else {
		T = new TreeNode(key, NIL, NIL, NIL);
	}
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::remove(TreeNode *T, decltype(TreeNode::key) key) {//cause we have parent member variable, so we don't need to use TreeNode * &T to store the info about the relationship bewtween *T and *T's parent(left child or right child)
	if (T != NIL) {
		if (key == T->key) {
			if (T->left == NIL) {
				transplant(T, T->right);
			}
			else if (T->right == NIL) {
				transplant(T, T->left);
			}
			else {
				TreeNode *minimumOfRightSubTree = minimum(T->right);
				if (minimumOfRightSubTree->parent != T) {
					transplant(minimumOfRightSubTree, minimumOfRightSubTree->right);
					minimumOfRightSubTree->right = T->right;
					minimumOfRightSubTree->right->parent = minimumOfRightSubTree;
				}
				transplant(T, minimumOfRightSubTree);
				minimumOfRightSubTree->left = T->left;
				minimumOfRightSubTree->left->parent = minimumOfRightSubTree;
			}
			delete T;
		}
		else if (key < T->key)
			remove(T->left, key);
		else
			remove(T->right, key);
	}
}

template<class TreeNode>
void BinarySearchTree<TreeNode>::transplant(TreeNode *u, TreeNode *v) {
	if (u->parent == NIL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NIL)
		v->parent = u->parent;
}


template<class TreeNode>
TreeNode *BinarySearchTree<TreeNode>::successor(TreeNode *node) {
	TreeNode *T = node->right;
	while (T->left != NIL)
		T = T->left;
	return T;
}

template<class TreeNode>
TreeNode *BinarySearchTree<TreeNode>::predecessor(TreeNode *node) {
	TreeNode *T = node->left;
	while (T->right != NIL)
		T = T->right;
	return T;
}
