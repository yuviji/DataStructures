#pragma once

//Attributes of a BTree:
//	All leaves will be at same level
//	Left subtree of node will have lesser values than right side of subtree
//	All keys in a node are sorted in increasing order
//	Minimum Degree "m" dependent upon disk block size
//	Children:
//		Number of children in a node is (number of keys in it + 1)
//		So, max number of children in a node is max number of keys + 1, which is (2m)
//		Root node must have atleast 2 child nodes
//	Keys:
//		Maximum number of keys in nodes is (2m-1)
//		Minimum number of keys in nodes (except head & leaves) is (m-1)

class BTN
{
	int* keys;
	int m;
	BTN** childP;
	int numKeys;
	bool leaf;

public:
	BTN(int, bool);
	void insertNonFull(int);
	void splitChild(int, BTN*);
	void traverse();
	BTN* search(int);
friend class BTree;
};

class BTree
{
public:
	BTN* head;
	int m;
	BTree(int);
	void traverse();
	BTN* search(int);
	void insert(int);
	void run(BTree, int[]);
};