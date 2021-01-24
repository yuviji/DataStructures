#pragma once
#include "BST.h"
class AVLTree : public BST
{
public:
	AVLTree();
	bool IsBalanced();
	void run(AVLTree, int[]);
	bool addNum(int);
	bstNode* RotateLeft(bstNode*);
	bstNode* RotateRight(bstNode*);
	int GetHeight(bstNode*);
	int GetBalance(bstNode*);
};