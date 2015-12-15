#pragma once
#include "BinarySearchTree.h"

enum Color
{
	RED,
	BLACK
};


template<typename dataType>
class RedBlackTreeNode
{
public:
	dataType key;
	RedBlackTreeNode *left;
	RedBlackTreeNode *right;
	RedBlackTreeNode *parent;
	Color color;

public:
	RedBlackTreeNode(dataType k = dataType(),  RedBlackTreeNode *l = NULL, RedBlackTreeNode *r = NULL, RedBlackTreeNode *p = NULL, Color c = BLACK): key{k}, left{l}, right{r}, parent{p}, color{c} {}
	RedBlackTreeNode(const RedBlackTreeNode &node): key{node.key}, left{node.left}, right{node.right}, parent{node.parent}, color{node.color} {}
	RedBlackTreeNode &operator=(const RedBlackTreeNode &node) {
		key = node.key;
		left = node.left;
		right = node.right;
		parent = node.parent;
		color = node.color;
		return *this;
	}
	~RedBlackTreeNode() {}
	void print() {
		cout << key << " ";
	}
};

template<class TreeNode>
class RedBlackTree : public BinarySearchTree<TreeNode>
{
private:
	TreeNode *&root;
	TreeNode *&NIL;
public:
	RedBlackTree(): root{BinarySearchTree<TreeNode>::root}, NIL{BinarySearchTree<TreeNode>::NIL} {}
	~RedBlackTree() {}
	void insert(decltype(TreeNode::key) key);
	void remove(decltype(TreeNode::key) key);
	void insert(TreeNode *&T, decltype(TreeNode::key) key, TreeNode *parent);
	void insertFixup(TreeNode *T);

	void remove(TreeNode *T, decltype(TreeNode::key) key);
	void removeFixup(TreeNode *T);

	void leftRotate(TreeNode *T);
	void rightRotate(TreeNode *T);

};

template<class TreeNode>
void RedBlackTree<TreeNode>::insert(decltype(TreeNode::key) key) {
	insert(root, key, NIL);
}
template<class TreeNode>
void RedBlackTree<TreeNode>::remove(decltype(TreeNode::key) key) {
	remove(root, key);
}

template<class TreeNode>
void RedBlackTree<TreeNode>::insert(TreeNode *&T, decltype(TreeNode::key) key, TreeNode *parent) {
	if (T != NIL) {
		if (key < T->key) {
			insert(T->left, key, T);
			T->left->parent = T;
		}
		else if (key > T->key) {
			insert(T->right, key, T);
			T->right->parent = T;
		}
	}
	else {
		T = new TreeNode(key, NIL, NIL, parent, RED);
		insertFixup(T);
	}
}
template<class TreeNode>
void RedBlackTree<TreeNode>::insertFixup(TreeNode *T) {
	TreeNode *uncle = NIL;
	while (T->parent->color == RED)
		if (T->parent == T->parent->parent->left) {
			uncle = T->parent->parent->right;
			if (uncle->color == RED) {
				T->parent->color = BLACK;
				uncle->color = BLACK;
				T->parent->parent->color = RED;
				T = T->parent->parent;
			}
			else {
				if (T == T->parent->right) {
					T = T->parent;
					leftRotate(T);
				}
				T->parent->color = BLACK;
				T->parent->parent->color = RED;
				rightRotate(T->parent->parent);
			}
		}
		else {
			uncle = T->parent->parent->left;
			if (uncle->color == RED) {
				T->parent->color = BLACK;
				uncle->color = BLACK;
				T->parent->parent->color = RED;
				T = T->parent->parent;
			}
			else {
				if (T == T->parent->left) {
					T = T->parent;
					rightRotate(T);
				}
				T->parent->color = BLACK;
				T->parent->parent->color = RED;
				leftRotate(T->parent->parent);
			}
		}
	root->color = BLACK;
}

template<class TreeNode>
void RedBlackTree<TreeNode>::remove(TreeNode *T, decltype(TreeNode::key) key) {
	if (T != NIL) {
		if (key == T->key) {
			TreeNode *replacedNode = NIL;
			Color removed = T->color;
			if (T->left != NIL && T->right != NIL) {
				TreeNode *minimumOfRightSubTree = this->minimum(T->right);
				replacedNode = minimumOfRightSubTree->right;
				removed = minimumOfRightSubTree->color;
				if (minimumOfRightSubTree->parent != T) {
					this->transplant(minimumOfRightSubTree, minimumOfRightSubTree->right);
					minimumOfRightSubTree->right = T->right;
					minimumOfRightSubTree->right->parent = minimumOfRightSubTree;
				}
				this->transplant(T, minimumOfRightSubTree);
				minimumOfRightSubTree->left = T->left;
				minimumOfRightSubTree->left->parent = minimumOfRightSubTree;
				minimumOfRightSubTree->color = T->color;

			}
			else if (T->left != NIL) {
				replacedNode = T->left;
				this->transplant(T, T->left);
			}
			else {
				replacedNode = T->right;
				this->transplant(T, T->right);
			}
			delete T;
			if (removed == BLACK)
				removeFixup(replacedNode);
		}
		else if (key < T->key)
			remove(T->left, key);
		else
			remove(T->right, key);
	}
}

template<class TreeNode>
void RedBlackTree<TreeNode>::removeFixup(TreeNode *T) {

}

template<class TreeNode>
void RedBlackTree<TreeNode>::leftRotate(TreeNode *T) {
	TreeNode *rightChild = T->right;
	T->right = rightChild->left;
	if (rightChild->left != NIL)
		rightChild->left->parent = T;
	rightChild->parent = T->parent;
	if (T->parent == NIL)
		root = rightChild;
	else if (T == T->parent->left)
		T->parent->left = rightChild;
	else
		T->parent->right = rightChild;
	rightChild->left = T;
	T->parent = rightChild;
}

template<class TreeNode>
void RedBlackTree<TreeNode>::rightRotate(TreeNode *T) {
	TreeNode *leftChild = T->left;
	T->left = leftChild->right;
	if (leftChild->right != NIL)
		leftChild->right->parent = T;
	leftChild->parent = T->parent;
	if (T->parent == NIL)
		root = leftChild;
	else if (T == T->parent->left)
		T->parent->left = leftChild;
	else
		T->parent->right = leftChild;
	leftChild->right = T;
	T->parent = leftChild;
}

void insert(int key) {
	insert(root, key);
}

void insert(TreeNode *T, int key) {
	TreeNode *pre = NIL;
	while (T != NIL) {//find the right place
		pre = T;
		if (key < T->key)
			T = T->left;
		else
			T = T->right;
	}
	T = new TreeNode(key, NIL, NIL, pre, RED); //create the node
	if (pre == NIL)//change the root
		root = T;
	else if (T->key < pre->key)
		pre->left = T;
	else
		pre->right = T;
	insertFixup(T);//fixup
}
void insertFixup(TreeNode *T) {
	TreeNode *uncle = NIL;
	while (T->parent->color == RED)
		if (T->parent == T->parent->parent->left) {
			uncle = T->parent->parent->right;
			if (uncle->color == RED) { //case 1.1 -> case X.1/2/3
				T->parent->color = BLACK;
				uncle->color = BLACK;
				T->parent->parent->color = RED;
				T = T->parent->parent;
			}
			else {
				if (T == T->parent->right) { //case 1.2 -> case 1.3
					T = T->parent;
					leftRotate(T);
				}
				T->parent->color = BLACK; //case 1.3 -> END
				T->parent->parent->color = RED;
				rightRotate(T->parent->parent);
			}
		}
		else {
			uncle = T->parent->parent->left;
			if (uncle->color == RED) {//case 2.1 -> case X.1/2/3
				T->parent->color = BLACK;
				uncle->color = BLACK;
				T->parent->parent->color = RED;
				T = T->parent->parent;
			}
			else {
				if (T == T->parent->left) {//case 2.2 -> case 2.3
					T = T->parent;
					rightRotate(T);
				}
				T->parent->color = BLACK;//case 2.3 -> END
				T->parent->parent->color = RED;
				leftRotate(T->parent->parent);
			}
		}
	root->color = BLACK;
}

void remove(int key) {
	remove(root, key);
}
void remove(TreeNode *T, int key) {
	while (T != NIL && T->key != key)//find the right place
		if (key < T->key)
			T = T->left;
		else
			T = T->right;
	if (T != NIL) {//if key is in the tree
		TreeNode *replacedNode = NIL;
		removedColor = T->color;
		if (T->left == NIL) {//if has no left subtree
			replacedNode = T->right;
			transplant(T, T->right);
		}
		else if (T->right == NIL) {//if has no right subtree
			replacedNode = T->left;
			transplant(T, T->left);
		}
		else {//if has two subtree
			TreeNode *minimumOfRightSubTree = minimum(T->right);
			replacedNode = minimumOfRightSubTree->right;
			removedColor = minimumOfRightSubTree->color;
			if (minimumOfRightSubTree->parent != T) {
				transplant(minimumOfRightSubTree, minimumOfRightSubTree->right);
				minimumOfRightSubTree->right = T->right;
				minimumOfRightSubTree->right->parent = minimumOfRightSubTree;
			}
			transplant(T, minimumOfRightSubTree);
			minimumOfRightSubTree->left = T->left;
			minimumOfRightSubTree->left->parent = minimumOfRightSubTree;
			minimumOfRightSubTree->color = T->color;
		}
		delete T;
		if (removedColor == BLACK)
			removeFixup(replacedNode);
	}
}

void removeFixup(TreeNode *T) {
	TreeNode *sibling = NIL;
	while (T != root && T->color == BLACK) {
		if (T == T->parent->left) {
			sibling = T->parent->right;
			if (sibling->color == RED) {//case 1.1 - case 1.2/3/4
				T->parent->color = RED;
				sibling->color = BLACK;
				leftRotate(T->parent);
				sibling = T->parent->right;
			}
			if (sibling->left->color == BLACK && sibling->right->color == BLACK) {//case1.2-> case X.1/2/3/4
				sibling->color = RED;
				T = T->parent;
			}
			else {
				if (T->right->color == BLACK) {//case 1.3 -> case 1.4
					sibling->left->color = BLACK;
					sibling->color = RED;
					rightRotate(sibling);
					sibling = T->parent->right;
				}
				sibling->right->color = BLACK;//case 1.4 -> END
				sibling->color = T->parent->color;
				T->parent->color = BLACK;
				leftRotate(T->parent);
				T = root;
			}
		}
		else {
			sibling = T->parent->left;
			if (sibling->color == RED) {//case 2.1 -> case 2.2/3/4
				sibling->color = BLACK;
				T->parent->color = RED;
				rightRotate(T->parent);
				sibling = T->parent->left;
			}
			if (sibling->left->color == BLACK && sibling->right->color == BLACK) {//case 2.2->case X.1/2/3/4
				sibling->color = RED;
				T = T->parent;
			}
			else {
				if (sibling->left->color == BLACK) {//case 2.3 -> case 2.4
					sibling->right->color = BLACK;
					sibling->color = RED;
					leftRotate(sibling);
					sibling = T->parent->left;
				}
				sibling->left->color = BLACK;//case 2.4 -> END
				sibling->color = T->parent->color;
				T->parent->color = BLACK;
				rightRotate(T->parent);
				T = root;
			}
		}
	}
	T->color = BLACK;
}

void transplant(TreeNode *u, TreeNode *v) {
	v->parent = u->parent;
	if (u->parent == NIL)
		root = v;
	else if (u->parent->left == u)
		u->parent->left = v;
	else u->parent->right = v;
}
