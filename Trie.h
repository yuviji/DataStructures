#pragma once
#define ALPHABET_SIZE 64 //26 - alph, 9 - numbers, 37 - specialchars

class Trie
{
public:
	struct TrieNode
	{
		struct TrieNode* children[ALPHABET_SIZE];
		bool bLeafNode;
	};
	struct TrieNode* GetNode();
	void InsertNode(struct TrieNode*, char*);
	bool SearchNode(struct TrieNode*, const char*);
	void run();
};
