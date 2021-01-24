#include "BTree.h"
#include <iostream>

using namespace std;

BTree::BTree(int minDeg) : m(minDeg), head(NULL) //Constructor for the BTree
{
	//Set minimum degree to the passed degree when initializing tree and set head value to NULL
}

BTN::BTN(int minDeg, bool leaf): m(minDeg), leaf(leaf), numKeys(0)
{
	keys = new int[2*m - 1]; //Create static array to store keys with maximum size (m-1)
	childP = new BTN* [2*m]; //Create static array to store pointers to children with maximum size (m)
}

void BTree::traverse()
{
	if (head)
	{
		head->traverse(); //If a head exists, traverse the tree starting at the head node
	}
}

BTN* BTree::search(int value)
{
	if (!head)
	{
		return NULL; //If there is no head, can't search tree, return NULL
	}
	return head->search(value); //Else, search starting at the head for the value
}

void BTN::traverse()
{
	int i; //Create i for iteration
	for (i = 0; i < numKeys; i++) //Iterate for every key in numKeys (number of keys in the node)
	{
		if (leaf == false) //If it is not a leaf
		{
			childP[i]->traverse(); //Go to index i in child pointer array & recursively traverse that node
		}
		cout << " " << keys[i]; //Print value of the node just traversed
	}
	if (leaf == false)
	{
		childP[i]->traverse(); //Print the subtree rooted with last child
		cout << "|" << endl;
	}
}

BTN* BTN::search(int value)
{
	//Remember that this function is first called by the BTree & the head is passed as the first node to search

	int i = 0; //Create i for iteration
	while (i < numKeys && value > keys[i])
	{
		i++; //When i < number of keys in node & value searched for is > the current value of keys[i]
	}
	if (keys[i] == value)
	{
		return this; //If value found while iterating, return this node
	}
	if (leaf == true)
	{
		return NULL; //If you have reached a leaf node & value not yet found, return a NULL as value was not found in tree
	}
	return childP[i]->search(value); //If you haven't found value yet or reached leaf node, recursively childPointers[i] for value
}

void BTree::insert(int value)
{
	if (!head) //If head doesn't exist
	{
		head = new BTN(m, true); //Create a new node which will be the head & make it leaf node as well since it has no children yet
		head->keys[0] = value; //Set the first key in the head node to be value passed
		head->numKeys = 1; //Increased number of keys in head node to 1
	}
	else
	{
		if (head->numKeys == 2*m-1) //If number of keys in head node has reached maximum
		{
			BTN* newNode = new BTN(m, false); //Create a new child node, setting (m) same as head & leaf node as false since it will have children
			newNode->childP[0] = head; //Set the first child of new node as head
			newNode->splitChild(0, head); //Split the new node
			
			int i = 0; //Create i for iteration
			if (newNode->keys[0] < value)
			{
				i++; //If the new node's first key value is less than value to be inserted, increase i (index value) by 1
			}
			newNode->childP[i]->insertNonFull(value); //Insert the value into the new node's child[i], a non-full node
			head = newNode; //Set the new node as the head of the tree
		}
		else
		{
			head->insertNonFull(value); //If number of keys in head node has not passed maximum, insert into head node which is non-full
		}
	}
}

void BTN::insertNonFull(int value)
{
	int i = numKeys - 1; //Set i to index value of right-most key in node
	if (leaf == true) //If the node is a leaf
	{
		while (i >= 0 && keys[i] > value) //While i is non-negative and & current key value is greater than value to insert
		{
			keys[i + 1] = keys[i]; //Shift the current key in iteration 1 unit to the right
			i--; //Decrease i by 1 to get ready to shift next key in array
		}
		keys[i + 1] = value; //Once location is found to insert the value, insert it in to keys
		numKeys = numKeys + 1; //Increase number of keys in the node by 1
	}
	else //If node is anything but a leaf node (head or normal node)
	{
		while (i >= 0 && keys[i] > value) //While i is non-negative & current key value is greater than value to insert
			i--; //Keep reducing i by 1 until index position to insert new key is found
		if (childP[i + 1]->numKeys == 2*m-1)
		{
			splitChild(i + 1, childP[i + 1]); //If the found child has max number of keys, split it
			if (keys[i + 1] < value)
			{
				i++; //After split, middle key of child node childP[i] becomes parent of 2 new nodes, see which will contain new value
			}
		}
		childP[i + 1]->insertNonFull(value); //If found child is not full, recursively call insertion function to insert into that node
	}
}

void BTN::splitChild(int i, BTN* child)
{
	BTN* split = new BTN(child->m, child->leaf); //New node with same degree and leaf status as passed node
	split->numKeys = (m-1); //Set number of keys in new node to be minimum
	
	for (int j = 0; j < (m-1); j++) 
	{
		//Bring the last (m-1) keys of the passed child to the new split node
		//so that the new split node has minimum amount of keys required
		split->keys[j] = child->keys[j + m]; 
	}
	
	if (child->leaf == false) //If passed child is not a leaf
	{
		//Bring the last (m) children of passed child to new split node
		//because even though the node is split, it will have children
		for (int j = 0; j < m; j++)
			split->childP[j] = child->childP[j + m];
	}
	
	child->numKeys = m - 1; //Reduce the number of keys in the original child that was split
	
	for (int j = numKeys; j >= i + 1; j--)
	{
		//Create space for new child in node that function is called from
		childP[j + 1] = childP[j];
	}
	
	childP[i + 1] = split; //Connect the new split node to the node this function called from by making it a child
	
	for (int j = numKeys - 1; j >= i; j--)
	{
		keys[j + 1] = keys[j]; //Make space in current node for key from passed child node by shifting greater keys right
	}
	keys[i] = child->keys[m - 1]; //Copy the middle key of passed child to the parent node
	numKeys = numKeys + 1;
}

void BTree::run(BTree tree, int arr[])

{
	for (int i = 0; i < 25; i++)
	{
		tree.insert(arr[i]);
	}

	tree.traverse();

	int NumTerms;

	cout << "\nHow many numbers do you want to search for?" << endl;

	cin >> NumTerms;
	
	int searchTerm;
	
	for (int j = 0; j < NumTerms; j++)
	{
		cout << "Type term: ";
		cin >> searchTerm;
		if (tree.search(searchTerm))
		{
			cout << "Present: " << searchTerm << endl;
		}
		else
		{
			cout << "Not Present: " << searchTerm << endl;
		}
	}
}