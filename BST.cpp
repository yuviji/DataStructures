#include "BST.h"
#include <iostream>

using namespace std;

BST::BST() : head(NULL)
{
}

BST::bstNode::bstNode(int value) : value(value), right(NULL), left(NULL)
{
}

bool BST::addNum(int value)
{
	return BST::addToBST(value, &head);
}

BST::bstNode* BST::addToBST(int value, bstNode** currentNode)
{
	if (*currentNode == NULL)
	{
		*currentNode = new bstNode(value);
		return *currentNode;
	}
	else if (value > (*currentNode)->value)
	{
		return addToBST(value, &((*currentNode)->right));
	}
	else if (value < (*currentNode)->value)
	{
		return addToBST(value, &((*currentNode)->left));
	}
	return NULL;
}

void BST::printNodes()
{
	cout << "R = ";
	bstDisplay(head);
}

void BST::bstDisplay(bstNode* rootNode)
{
	if (rootNode)
	{
		cout << rootNode->value << endl;
		if (rootNode->left)
		{
			cout << rootNode->value << " <- ";
			bstDisplay(rootNode->left);
		}
		if (rootNode->right)
		{
			cout << rootNode->value << " -> ";
			bstDisplay(rootNode->right);
		}
	}
}

void BST::run(BST tree, int arr[])
{
	for (int i = 0; i < 25; i++)
	{
		tree.addNum(arr[i]);
	}

	tree.head;
	tree.bstDisplay(tree.head);
}