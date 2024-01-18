/* Jesus Galindo*/

#ifndef BSTREEINT_H
#define BSTREEINT_H

#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

using namespace std;

// Binary Search Tree class
template <typename DATATYPE, typename KEYTYPE>
class BSTree 
{
	private:
		Node<DATATYPE, KEYTYPE>* root; // main root node for start of tree
		void addNode(KEYTYPE key, Node<DATATYPE, KEYTYPE>* leaf, DATATYPE& data); // addnode to add actors/movies
		Node<DATATYPE, KEYTYPE>* deleteNode(Node<DATATYPE, KEYTYPE>* node, KEYTYPE key); // user needs to be able to delete a data type
		void freeNode(Node<DATATYPE, KEYTYPE>* leaf);
		Node<DATATYPE, KEYTYPE>* findNode(KEYTYPE key, Node<DATATYPE, KEYTYPE>* node); // find a node for user

	public:
		BSTree<DATATYPE, KEYTYPE>(); // constructor for empty tree
		~BSTree<DATATYPE, KEYTYPE>();
		Node<DATATYPE, KEYTYPE>* Root() { return root; }
		void setRoot(Node<DATATYPE, KEYTYPE>* _root) { root = _root; } // change root of tree
		void addNode(KEYTYPE key, DATATYPE& data); // add new node for tree
		Node<DATATYPE, KEYTYPE>* findNode(KEYTYPE key); 
		//void replaceData(Node<DATATYPE, KEYTYPE>* node, int key, DATATYPE _data);
		void actorSearch(Node<DATATYPE, KEYTYPE>* node, int field, std::string key, bool complete); 
		void movieSearch(Node<DATATYPE, KEYTYPE>* node, int field, std::string key, bool complete);
		void print(ostream& out, const DATATYPE& data);  
		bool contains(Node<DATATYPE, KEYTYPE>* root, int key); 
		void deleteNode(KEYTYPE key);
		void nodesDataVec(vector <DATATYPE>& list, Node<DATATYPE, KEYTYPE>* node); 
		void storeTreeNodes(Node<DATATYPE, KEYTYPE>* root, vector<Node<DATATYPE, KEYTYPE>*>& nodes);
		Node<DATATYPE, KEYTYPE>* buildBalancedTreeTool(vector<Node<DATATYPE, KEYTYPE>*>& nodes, int start, int end);
		Node<DATATYPE, KEYTYPE>* buildBalancedTree(Node<DATATYPE, KEYTYPE>* root);
		Node<DATATYPE, KEYTYPE>* min(Node<DATATYPE, KEYTYPE>* node);
		Node<DATATYPE, KEYTYPE>* max(Node<DATATYPE, KEYTYPE>* node);
};

//To be used in conjunction with BSTree.h and Node.h
//When you modify this, please add your name and list any changes that you made
//A few member functions have been left blank so you, the student can implemement

/*Template Directions: #include "BSTREEInt.hpp"
but do NOT compile it (or add it to the project)*/

// Constructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::BSTree() {
	root = nullptr;
}

// Destructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::~BSTree()
{
	if (root != nullptr)
		freeNode(root);
}

// Free the node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::freeNode(Node<DATATYPE, KEYTYPE>* leaf)
{
	if (leaf != NULL) 
	{
		freeNode(leaf->Left());
		freeNode(leaf->Right());
		delete leaf;
	}

}

// Add a node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, DATATYPE& data)
{
	if (Root() == nullptr)
	{
		Node<DATATYPE, KEYTYPE>* newNodePtr = new Node<DATATYPE, KEYTYPE>;
		newNodePtr->setKey(key);
		newNodePtr->setData(data); 
		root = newNodePtr;
		root->setParent(root);

	}
	else
		addNode(key, root, data); 
}

// Add a node (private)
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, Node<DATATYPE, KEYTYPE>* leaf, DATATYPE& data) // travel via recursion and check childs by comparing key to node and add a new node to desired side
{
	if (key < leaf->Key()) 
	{
		if (leaf->Left() != nullptr)  
		{ 
			addNode(key, leaf->Left(), data);
		}
		else 
		{
			Node<DATATYPE, KEYTYPE>* newNodePtr = new Node<DATATYPE, KEYTYPE>;
			leaf->setLeft(newNodePtr);
			leaf->Left()->setKey(key);
			leaf->Right()->setData(data); 
			(leaf->Left())->setParent(leaf);
		}
	}
	else if (key >= leaf->Key()) 
	{
		if (leaf->Right() != nullptr) 
		{ 
			addNode(key, leaf->Right(), data); 
		}
		else 
		{
			Node<DATATYPE, KEYTYPE>* newNodePtr = new Node<DATATYPE, KEYTYPE>;
			leaf->setRight(newNodePtr);  
			leaf->Right()->setKey(key);
			leaf->Right()->setData(data);   
			(leaf->Right())->setParent(leaf); 
		}
	}

}

template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE>* BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key) 
{
	return findNode(key, root);
}

// Find a node
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE>* BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key, Node<DATATYPE, KEYTYPE>* node) // find node function search via key and traverse to specified path with recursion
{
	if (node == NULL || (node->Key() == key ))
	{
		return node;
	}
	if (node->Key() < key)
	{
		return findNode(key, node->Right()); 
	}
	else
	{
		return findNode(key, node->Left());  
	}
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::actorSearch(Node<DATATYPE, KEYTYPE>* node, int field, std::string key, bool complete) // inorder traverse to search for actor
{
	if (!node)
	{
		return;
	}
	actorSearch(node->Left(), field, key, complete);
	if (complete == true)
	{
		if (field == 0)
		{
			if (node->Data().containsName(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 1)
		{
			if (node->Data().containsYear(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 2)
		{
			if (node->Data().containsAward(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 3)
		{
			if (node->Data().containsWinner(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 4)
		{
			if (node->Data().containsFilm(key))
			{
				node->Data().printAct(std::cout);
			}
		}
	}
	if(complete == false)
	{
		if (field == 0)
		{
			if (node->Data().containsPName(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 1)
		{
			if (node->Data().containsPYear(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 2)
		{
			if (node->Data().containsPAward(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 3)
		{
			if (node->Data().containsPWinner(key))
			{
				node->Data().printAct(std::cout);
			}
		}
		if (field == 4)
		{
			if (node->Data().containsPFilm(key))
			{
				node->Data().printAct(std::cout);
			}
		}
	}
	actorSearch(node->Right(), field, key, complete); 
}


template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::movieSearch(Node<DATATYPE, KEYTYPE>* node, int field, std::string key, bool complete) // inorder traverse to search for movie
{
	if (!node)
	{
		return;
	}
	movieSearch(node->Left(), field, key, complete);
	if (complete == true)
	{
		if (field == 0)
		{
			if (node->Data().containsName(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 1)
		{
			if (node->Data().containsYear(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 2)
		{
			if (node->Data().containsNom(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 3)
		{
			if (node->Data().containsRating(key))
			{
				node->Data().printFilm(std::cout); 
			}
		}
		if (field == 4)
		{
			if (node->Data().containsDuration(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 5)
		{
			if (node->Data().containsGenre(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 6)
		{
			if (node->Data().containsRelease(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 7)
		{
			if (node->Data().containsMeta(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 8)
		{
			if (node->Data().containsSyn(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
	}
	if (complete == false)
	{
		if (field == 0)
		{
			if (node->Data().containsPName(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 1)
		{
			if (node->Data().containsPYear(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 2)
		{
			if (node->Data().containsPNom(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 3)
		{
			if (node->Data().containsPRating(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 4)
		{
			if (node->Data().containsPDuration(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 5)
		{
			if (node->Data().containsPGenre(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 6)
		{
			if (node->Data().containsPRelease(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 7)
		{
			if (node->Data().containsPMeta(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
		if (field == 8)
		{
			if (node->Data().containsPSyn(key))
			{
				node->Data().printFilm(std::cout);
			}
		}
	}
	movieSearch(node->Right(), field, key, complete);
}


template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::print(ostream& out, const DATATYPE& data)
{
	out << data.number << "\t" << data.name << endl;
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::deleteNode(KEYTYPE key)
{
	setRoot(deleteNode(Root(), key));
}

//deleteNode (Private)
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE>* BSTree<DATATYPE, KEYTYPE>::deleteNode(Node<DATATYPE, KEYTYPE>* aRoot, KEYTYPE value)
{

	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */

	// base case
	if (aRoot == nullptr) return aRoot;

	// If the key to be deleted is smaller than the aRoot's key,
	// then it lies in left subtree
	if (value < aRoot->Key())
		aRoot->setLeft(deleteNode(aRoot->Left(), value));

	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else if (value > aRoot->Key())
		aRoot->setRight(deleteNode(aRoot->Right(), value));  

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node with only one child or no child
		if (aRoot->Left() == nullptr)
		{
			Node<DATATYPE, KEYTYPE>* temp = aRoot->Right();
			delete aRoot;
			return temp;
		}
		else if (aRoot->Right() == nullptr)
		{
			Node<DATATYPE, KEYTYPE>* temp = aRoot->Left();
			delete aRoot;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		Node<DATATYPE, KEYTYPE>* temp = min(aRoot->Right());

		// Copy the inorder successor's content to this node
		aRoot->setKey(temp->Key());
		aRoot->setData(temp->Data()); 

		// Delete the inorder successor
		aRoot->setRight(deleteNode(aRoot->Right(), temp->Key()));
	}
	return aRoot;
}
template <typename DATATYPE, typename KEYTYPE>
bool BSTree<DATATYPE, KEYTYPE>::contains(Node<DATATYPE, KEYTYPE>* root, int key)
{
	if (!root)
	{
		return false;
	}
	if (key == root->Key())
	{
		return true;
	}
	if (key < root->Key())
	{
		return contains(root->Left(), key);
	} 
	return contains(root->Right(), key);
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::nodesDataVec(std::vector <DATATYPE>& list, Node<DATATYPE, KEYTYPE>* node)
{
	if (!node)
	{
		return;
	}
	nodesDataVec(list, node->Left());
	list.push_back(node->Data()); 
	nodesDataVec(list, node->Right());
}

// Find the node with min key
// Traverse the left sub-BSTree recursively
// till left sub-BSTree is empty to get min
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE>* BSTree<DATATYPE, KEYTYPE>::min(Node<DATATYPE, KEYTYPE>* node)
{
	Node<DATATYPE, KEYTYPE>* current = node;

	/* loop down to find the leftmost leaf */
	while (current->Left() != nullptr)
		current = current->Left();

	return current;
}

// Find the node with max key
// Traverse the right sub-BSTree recursively
// till right sub-BSTree is empty to get max
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE>* BSTree<DATATYPE, KEYTYPE>::max(Node<DATATYPE, KEYTYPE>* node)
{
	Node<DATATYPE, KEYTYPE>* tempNode = node;
	if (node == nullptr)
	{
		tempNode = nullptr;
	}
	else if (node->Right())
	{
		tempNode = max(node->Right());
	}
	else
	{
		tempNode = node;
	}

	return tempNode;
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::storeTreeNodes(Node<DATATYPE, KEYTYPE>* root, vector<Node<DATATYPE, KEYTYPE>*>& nodes) // store nodes into vector via inorder
{
	if (!root)
	{
		return;
	}
	storeTreeNodes(root->Left(), nodes);
	nodes.push_back(root);
	storeTreeNodes(root->Right(), nodes);
}

/* Recursive function to construct binary tree */
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE>* BSTree<DATATYPE, KEYTYPE>::buildBalancedTreeTool(vector<Node<DATATYPE, KEYTYPE>*>& nodes, int start, int end) // create a new balanced tree from sorted vector of nodes by constantly cutting half the list and assigning middle node
{
	if (start > end)
	{
		return nullptr;
	}
	int mid = (start + end) / 2; // find middle index of vector
	Node<DATATYPE, KEYTYPE>* root = nodes[mid]; // set root as middle node from list

	root->setLeft(buildBalancedTreeTool(nodes, start, mid - 1)); // set right to middle position of mid and end
	root->setRight(buildBalancedTreeTool(nodes, mid + 1, end)); // set left to middle position of start and mid

	return root;
}

template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE>* BSTree<DATATYPE, KEYTYPE>::buildBalancedTree(Node<DATATYPE, KEYTYPE>* root) // function to call tools to make balanced tree
{
	vector<Node<DATATYPE, KEYTYPE>*> nodes;
	storeTreeNodes(root, nodes);

	int end = nodes.size() - 1; // last index of list
	return buildBalancedTreeTool(nodes, 0, end); // make tree and pass start and end index
}


#endif