#include "AVLTree.h"
#include <iostream>

using namespace std;

AVLTree::AVLTree() //Constructor
{
}

bool AVLTree::addNum(int value) //Main function to add new value to tree
{
	bstNode* newNode = BST::addToBST(value, &head); //Create and add new node to tree with current node as head & value as passed value
	
	if (newNode) //If new node is not null
	{
		int nodeBalance = GetBalance(head); //Get balance factor of the head node

		//Left: if balance factor > 1 (left side has more nodes than right) & value added to left subtree of head's left child
		if (nodeBalance > 1 && value < head->left->value)
		{
			cout << 1 << endl;
			head = RotateRight(head); //Perform right rotation on head to balance tree
			return true;
		}

		//Right: if balance factor < -1 (right side has more nodes than left) & value added to right subtree of head's right child
		else if (nodeBalance < -1 && value > head->right->value)
		{
			cout << 2 << endl;
			head = RotateLeft(head); //Perform left rotation on head to balance tree
			return true;
		}

		//Right Left: if more nodes on right than left & value added to left subtree of head's right child
		else if (nodeBalance < -1 && value < head->right->value)
		{
			head->right = RotateRight(head); //Perform right rotation on head's right child to get a left case
			head = RotateLeft(head); //Perform left rotation on head
			return true;
		}

		//Left Right: if more nodes on left than right & value added to right subtree of head's left child
		else if (nodeBalance > 1 && value > head->left->value)
		{
			head->left = RotateLeft(head); //Perform left rotation on head's left child to get a right case
			head = RotateRight(head); //Perform right rotation on head
			return true;
		}
	}
	return false;
}

bool AVLTree::IsBalanced()
{
	return (abs(GetBalance(head)) <= 1); //Return if absolute value of balance of tree between 0-1 (tree is balanced)
}

BST::bstNode* AVLTree::RotateLeft(bstNode* currentNode)
{
	cout << "RotateLeft " << currentNode->value << endl; //Print node's value which is being rotated left
	bstNode* right = currentNode->right; //Create temporary node which is the passed node's right child
	bstNode* leftofright = right->left; //Create temporary node which is the temporary right's left child
	right->left = currentNode; //Set temporary right's left child as passed node
	currentNode->right = leftofright; //Set (now right's left child)'s right child as original right's left node
	return right; //Return new head, passed node's right child
}

BST::bstNode* AVLTree::RotateRight(bstNode* currentNode)
{
	cout << "RotateRight " << currentNode->value << endl; //Print node's value which is being rotated right
	bstNode* left = currentNode->left; //Create temporary node which is the passed node's left child
	bstNode* rightofleft = left->right; //Create temporary node which is the temporary left's right child
	left->right = currentNode; //Set temporary lefts's right child as passed node
	currentNode->left = rightofleft; //Set (now left's right child)'s left child as original left's right node
	return left; //Return new head, passed node's left child
}

int AVLTree::GetHeight(bstNode* currentNode)
{
	if (!currentNode) //If current node is null, return height as 0
	{
		return 0;
	}
	int leftHeight = GetHeight(currentNode->left); //Recursively get height of passed node's left
	int rightHeight = GetHeight(currentNode->right); //Recursively get height of passed node's right
	//Print height of the node followed by individual left and right child heights
	cout << "Height for Node " << currentNode->value << ", left child height " << leftHeight << ", right child height " << rightHeight << endl;
	return 1 + max(leftHeight, rightHeight); //Height = larger of left or right child heights + 1 (for the node itself)
}

int AVLTree::GetBalance(bstNode* currentNode)
{
	if (!currentNode) //If current node is null, return balance factor of 0
	{
		return 0;
	}
	int balance = GetHeight(currentNode->left) - GetHeight(currentNode->right); //Balance = height of left node - height of right node
	cout << "Balance for Node " << currentNode->value << ", balance is " << balance << endl; //Print balance factor current node
	return balance; //Return the balance factor
}

void AVLTree::run(AVLTree tree, int arr[])
{
	for (int i = 0; i < 25; i++)
	{
		tree.addNum(arr[i]); //Add each element of array to tree
	}
	tree.head; //Initialize head of tree
	tree.bstDisplay(tree.head); //Display tree with first node as head of tree
	if (tree.IsBalanced()) 
	{ 
		cout << "Tree is balanced" << endl; //Print if the tree is balanced
	}
	else
	{
		cout << "Tree is unbalanced" << endl; //Print if the tree is not balanced
	}
}