#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}

	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 * TODO: Implement Destructor
	 */
	~BST() {
	    //cout << "TODO: Implement Destructor" << endl;
		destroyTree(_root);
		//cout << "Nodes count: " << count << endl;
	}

	void destroyTree(Node<T>* pTree) // post-order traversal- l, r, process
	{
		if (pTree != nullptr)
		{
			destroyTree(pTree->left);
			destroyTree(pTree->right);
			//cout<<"deleting "<<pTree->value<<endl;
			delete pTree;
		}
	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	/**
	 * Print the nodes level by level, starting from the root
	 * TODO: Implement printLevelOrder
	 */
	void printLevelOrder() {
		// cout << "TODO: Implement printLevelOrder" << endl;

		int h = height();
		
		for (int i = 1; i <= h + 1; i++)
		{
			printCurLevel(_root, i);
			cout << endl;
		}

		//cout << endl;
	}

	void printCurLevel(Node<T>* pTree, int level)
	{
		if (pTree == nullptr)
		{
			return;
		}

		if (level == 1)
		{
			cout << pTree->value << " ";
		}
		else if (level > 1)
		{
			printCurLevel(pTree->left, level - 1);
			printCurLevel(pTree->right, level - 1);
			//cout << endl;
		}
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	/**
	 * Print the maximum path in this tree
	 * TODO: Implement printMaxPath
	 */
	void printMaxPath() {
		// cout << "TODO: Implement printMaxPath" << endl;
		vector<T> result = maxPathHelper(_root);
		int n = result.size();

		cout << result[n - 1] << " ";

		for (int i = n -2; i >= 0; i--)
		{
			cout << result[i] << " ";
		}
	}

	vector<T> maxPathHelper(Node<T>* pTree)
	{
		if (pTree == nullptr)
		{
			vector<T> empty = {};
			return empty;
		}

		vector<T> r = maxPathHelper(pTree->right);
		vector<T> l = maxPathHelper(pTree->left);

		if (l.size() > r.size())
		{
			l.push_back(pTree->value);
		}
		else
		{
			r.push_back(pTree->value);
		}

		if (l.size() > r.size())
		{
			return l;
		}
		else
		{
			return r;
		}
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	/**
	 * Find if the BST contains the value
	 * TODO: Implement contains
	 */
	bool contains(T val) {
	    //cout << "TODO: Implement contains" << endl;
		//return numeric_limits<T>::min();
		bool success = false;
		Node<T>* pCur = _root;

		while (pCur->value != val)
		{
			if (pCur != nullptr)
			{
				if (pCur->value > val)
				{
					pCur = pCur->left;
				}
				else
				{
					pCur = pCur->right;
				}

				if (pCur == nullptr)
				{
					return false;
				}
			}
		}

		if (pCur->value == val)
		{
			success = true;
		}

		return success;
	}
};

#endif