#pragma once
class BST
{
public:
	class bstNode
	{
	public:
		bstNode(int);
		int value;
		bstNode* right;
		bstNode* left;
	};

	BST();
	bstNode* head;
	bstNode* addToBST(int, bstNode**);
	bool addNum(int);
	void bstDisplay(bstNode*);
	void printNodes();
	void run(BST, int[]);
};