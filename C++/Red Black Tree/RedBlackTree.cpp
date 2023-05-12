#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

template <typename T, typename U>
class NodeT {
public:
	NodeT() {
	}
	NodeT(T k, U v) {
		key = k;
		value = v;
	}
	T key;
	U value;
	NodeT* left = NULL;
	NodeT* right = NULL;
	NodeT* parent = NULL;
	bool isBlack = false;
};
template <typename T, typename U>
class RedBlackTree {
public:

	RedBlackTree() {
		root = NULL;
		siz = 0;
	}
	RedBlackTree(const RedBlackTree& bst) {

		queue<NodeT<T,U>*> g;
		g.push(bst.root);
		siz = 0;
		while (!g.empty())
		{
			int size = g.size();

			for (int i = 0; i < size; i++)
			{
				NodeT<T, U>* nodeptr = g.front();

				if (nodeptr->left != NULL) {
					g.push(nodeptr->left);
				}

				if (nodeptr->right != NULL) {
					g.push(nodeptr->right);
				}
				this->ninsert(nodeptr->key, nodeptr->value); siz++;
				searchnd(nodeptr->key)->isBlack = nodeptr->isBlack;
				g.pop();
			}
		}
	}

	~RedBlackTree() {
		clear(root);
		root = nullptr;
	}

	RedBlackTree& operator= (const RedBlackTree& bst) {

		std::queue<NodeT<T, U>*> g;
		g.push(bst.root);

		while (!g.empty())
		{
			int size = g.size();

			for (int i = 0; i < size; i++)
			{
				NodeT<T, U>* nodeptr = g.front();

				if (nodeptr->left != NULL) {
					g.push(nodeptr->left);
				}

				if (nodeptr->right != NULL) {
					g.push(nodeptr->right);
				}
				this->ninsert(nodeptr->key, nodeptr->value); siz++;
				searchnd(nodeptr->key)->isBlack = nodeptr->isBlack;
				g.pop();
			}
		}
		return *this;

	}

	bool insert(T k, U v) {
		NodeT<T, U>* y, *x = ninsert(k, v);
		if (x == NULL) {
			return false;
		}
		siz++;
		while ((x != root) && (x->parent->isBlack == false)) {
			y = x->parent->parent->right; //x’s “uncle”
			if (y == NULL) {// create a temporary leaf node in place of uncle
				NodeT<T, U> a;
				y = &a;
				y->isBlack = true; 
				
			}
			if (x->parent == x->parent->parent->left) { // parent is a left child
				
					if ((y->isBlack == false) ) {//case 1
						x->parent->isBlack = true;
					
							y->isBlack = true;

						x->parent->parent->isBlack = false;
						x = x->parent->parent;
					}
					else {
						if (x == x->parent->right) { //case 2 if true case 3 if not

							x = x->parent;
							lr(x);
						}
						x->parent->isBlack = true;
						x->parent->parent->isBlack = false;
						rr(x->parent->parent);

					}
					
			}			
			else { //parent is a right child
				y = x->parent->parent->left; //x’s “uncle”
				if (y == NULL) { // create a temporary leaf node in place of uncle
					NodeT<T, U> a;
					y = &a;
					y->isBlack = true; 

				}
				if ((y->isBlack == false) ) {//case 1
					x->parent->isBlack = true;
					
						y->isBlack = true;

					x->parent->parent->isBlack = false;
					x = x->parent->parent;
				}
				else{ 
					if (x == x->parent->left) { //case 2 if true case 3 if not
						x = x->parent;
						lr(x);
					}
					x->parent->isBlack = true;
					x->parent->parent->isBlack = false;
					lr(x->parent->parent);
				}
				
			}
		}
		root->isBlack = true;
		
		return true;
	}
	

	bool remove(T k) {
		NodeT<T, U>* x,*y, *z = searchnd(k);
		if (z == NULL) {
			return false;
		}
		siz--;
		y = z;
		bool ogcolor = y->isBlack;
		if (z->left == NULL) {
			x = z->right;
			rbswap(z, z->right);
		}
		else if (z->right == NULL) {
			x = z->left;
			rbswap(z, z->left);
		}
		else {
			y = successor(z);
			ogcolor = y->isBlack;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbswap(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rbswap(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->isBlack = z->isBlack;
		}
		if (z == z->parent->right) {
			z->parent->right = NULL;
		}
		else {
			z->parent->left = NULL;
		}
		delete z;
		if (ogcolor == true && x!=NULL) {
			rbFix(x);
		}
	}
								

	bool search(T value) const {
		NodeT<T, U>* p = root;
		while (p != nullptr) {
			if (value == p->key) {
				return true;
			}
			else if (value < p->key) {
				p = p->left;
			}
			else {
				p = p->right;
			}
		}
		return false;
	}
	vector<U> search(T min, T max)  {
		vector<U> list;
		if (root == NULL) 
			return list;
		
		inOrderSearch(min, max,root,list);
		return list;
	}
	
	vector<U> values() {
		vector<U> list;
		if (root == NULL)
			return list;
		 inOrderValues(root, list);
		 return list;
	}
	
	vector<T> keys()  {
		vector<T> list;
		if (root == NULL)
			return list;
		inOrderKeys(root, list);
		return list;
	}
	
	int size() const {
		return siz;
	}
	NodeT<T, U>* getRoot() const {
		return root;
	}
	void print() const
	{
			std::queue<NodeT<T, U>*> g;
			g.push(root);

			while (!g.empty())
			{
				int size = g.size();

				for (int i = 0; i < size; i++)
				{
					NodeT<T, U>* nodeptr = g.front();

					if (nodeptr->left != NULL) {
						g.push(nodeptr->left);
					}

					if (nodeptr->right != NULL) {
						g.push(nodeptr->right);
					}
					cout << nodeptr->key;
					if (nodeptr->isBlack == false)
						cout << '-';
					cout << " ";
					g.pop();
				}
				cout << endl;
			}
			cout << endl;
			cout << endl;
	}
	
	void inOrderPrint() const
	{
		inOrderPrint(root);
	}

	
	private:
		NodeT<T, U>* root;
		int siz;	

		//helper methods
		NodeT<T, U>* ninsert(T k, U v) { //normal insert
			NodeT<T, U>* newNode = new NodeT<T, U>(k, v);

			if (root == NULL) {
				root = newNode;
				return newNode;
			}

			NodeT<T, U>* parent = root;
			NodeT<T, U>* next = root;
			if (search(k) == false) { //non-empty and key dosen't already exist
				   // Find parent of new node
				while (next != NULL) {
					parent = next;
					if (k < parent->key) {
						next = parent->left;
					}
					else {
						next = parent->right;
					}
				}
				// Insert new node
				if (k < parent->key) {
					parent->left = newNode;
					newNode->parent = parent;
				}
				else {
					parent->right = newNode;
					newNode->parent = parent;
				}
				return newNode;
			}
			return NULL;
		}
		void lr(NodeT<T, U>* x) { //left rotation
			NodeT<T, U>* y;
			y = x->right;
			if (y == NULL) {
				return;
			}

			x->right = y->left;
			if (y->left != NULL) {
				y->left->parent = x;
				// y
			}
			y->parent = x->parent;
			if (x->parent == NULL)
				root = y;
			else if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;





		}
		void rr(NodeT<T, U>* x) {//right rotation
			NodeT<T, U>* y = x->left;
			if (y == NULL) {
				return;
			}
			x->left = y->right;
			if (y->right != NULL) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
				root = y;
			}
			else if (x == x->parent->right) {
				x->parent->right = y;
			}
			else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;

		}
		void clear(NodeT<T, U>* nd)
		{
			siz = 0;
			if (nd != nullptr) {
				clear(nd->left);
				clear(nd->right);
				delete nd;
			}
		}
		NodeT<T, U>* successor(NodeT<T, U>* x)
		{
			if (x->right != NULL) {
				x = x->right;
			}
			while (x->left != NULL) {
				x = x->left;
			}
			return x;
		}

		// find the predecessor of a given node
		NodeT<T, U>* predecessor(NodeT<T, U>* x) {
			if (x->left != NULL) {
				x = x->left;
			}
			while (x->right != NULL) {
				x = x->right;
			}
			return x;
		}

		void rbswap(NodeT<T, U>* u, NodeT<T, U>* v) {
			if (v == NULL) {
				return;
			}

			if (u->parent == nullptr) {
				root = v;
			}
			else if (u == u->parent->left) {
				u->parent->left = v;
			}
			else {
				u->parent->right = v;
			}
			v->parent = u->parent;
		}
		void rbFix(NodeT<T, U>* x) {
			NodeT<T, U>* y;
			while ((x != root) && (x->isBlack = true)) {
				if (x == x->parent->left) {  //x is left child
					y = x->parent->right; //x’s sibling
					if (y == NULL) { // create a temporary leaf node in place of uncle
						NodeT<T, U> a;
						y = &a;
						y->isBlack = true;
					}
					if (y->isBlack == false) {
						y->isBlack = true;
						x->parent->isBlack = false;//p was black
						lr(x->parent);
						y = x->parent->right;
					}
					if ((y->left->isBlack == true) && (y->right->isBlack == true)) {
						y->isBlack = false;
						x = x->parent;//and into while again …
					}

					else {
						if (y->right->isBlack == true) {
							y->left->isBlack = true;
							y->isBlack = false;
							rr(y);
							y = x->parent->right;
						}
						y->isBlack = x->parent->isBlack;
						x->parent->isBlack = true;
						y->right->isBlack = true;
						lr(x->parent);
						x = root;
					}


				}
				else {
					y = x->parent->left;
					if (y == NULL) { // create a temporary leaf node in place of uncle
						NodeT<T, U> a;
						y = &a;
						y->isBlack = true;
					}
					if (y->isBlack == false) {

						y->isBlack = true;
						x->parent->isBlack = false;
						rr(x->parent);
						y = x->parent->left;
					}
					if (y->left->isBlack == true && y->right->isBlack == true) {

						y->isBlack = false;
						x = x->parent;
					}
					else {
						if (y->left->isBlack == true) {

							y->right->isBlack = true;
							y->isBlack = false;
							lr(y);
							y = x->parent->left;
						}


						y->isBlack = x->parent->isBlack;
						x->parent->isBlack = true;
						y->left->isBlack = true;
						rr(x->parent);
						x = root;
					}
				}

			}

			x->isBlack = true;

		}

		NodeT<T, U>* searchnd(T value) const {
			NodeT<T, U>* p = root;
			while (p != nullptr) {
				if (value == p->key) {
					return p;
				}
				else if (value < p->key) {
					p = p->left;
				}
				else {
					p = p->right;
				}
			}
			return NULL;
		}
		void inOrderSearch(T small, T big, NodeT<T, U>* nd, vector<U>& list) {

			if (nd != NULL) {
				inOrderSearch(small, big, nd->left, list);
				if ((nd->key >= small) && (nd->key <= big)) {
					list.push_back(nd->value);
				}
				inOrderSearch(small, big, nd->right, list);
			}
		}
		void inOrderValues(NodeT<T, U>* nd, vector<U>& list) {

			if (nd != nullptr) {
				inOrderValues(nd->left, list);
				list.push_back(nd->value);
				inOrderValues(nd->right, list);
			}

		}

		void inOrderKeys(NodeT<T, U>* nd, vector<T>& list) {

			if (nd != nullptr) {
				inOrderKeys(nd->left, list);
				list.push_back(nd->key);
				inOrderKeys(nd->right, list);
			}

		}

		void inOrderPrint(NodeT<T, U>* nd) const
		{
			if (nd != nullptr) {
				inOrderPrint(nd->left);
				cout << nd->key << endl;
				inOrderPrint(nd->right);
			}
		}
};