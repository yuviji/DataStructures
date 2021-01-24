#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include "Trie.h"

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define ALPHABET_SIZE 64 //26 - alph, 9 - numbers, 37 - specialchars

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;

struct Trie::TrieNode* Trie::GetNode()
{
	TrieNode* pNode = new TrieNode; //Create a temporary node

	if (pNode) //If node is not null
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			pNode->children[i] = NULL; //For each possible character, set each child of node as null
		}
		pNode->bLeafNode = false; //This node is not a leaf node
	}

	return pNode; //Return the node
}


void Trie::InsertNode(TrieNode* root, char* key)
{
	int length = strlen(key); //Get the length of the passed character (key)
	int i = 0; //Used for accessing different indexes of children

	TrieNode* pCrawl = root; //Create a node to "crawl" the different areas of the Trie, starting at head of Trie

	for (int l = 0; l < length; l++) //For each character in the key
	{
		i = CHAR_TO_INDEX(key[l]); //Set the new index to scan as output of current character of key
		pCrawl->children[i] = GetNode(); //Get the node at the crawler's child[i]

		pCrawl = pCrawl->children[i]; //Set crawler as its child[i]
	}

	pCrawl->bLeafNode = true; //Crawler becomes a leaf node
}


bool Trie::SearchNode(TrieNode* root, const char* key)
{
	int i = 0; //Used for accessing different indexes of children
	int length = strlen(key); //Get the length of the passed character (key)

	TrieNode* pCrawl = root; //Create a node to "crawl" the different areas of the Trie, starting at head of Trie

	for (int l = 0; l < length; l++) //For each character in the key
	{
		i = CHAR_TO_INDEX(key[l]); //Set the new index to scan as output of current character of key

		if (pCrawl->children[i])
		{
			pCrawl = pCrawl->children[i]; //If the child[i] isn't null, go to it
		}
		else 
		{
			return false; //It it's null, return false
		}
	}
	return (pCrawl && pCrawl->bLeafNode); //Return the crawler node & its leaf node status
}

void Trie::run()
{
	//The longest word in the English Dictionary is 45 characters: "Pneumonoultramicroscopicsilicovolcanocon"
	char keys[][50] = { "Pneumonoultramicroscopicsilicovolcanocon", "C++", "junkmail@github.com" };
	char output[][20] = { "Not Found In Trie", "Found In Trie" };

	struct Trie::TrieNode* root = GetNode();

	for (int l = 0; l < (int)ARRAY_SIZE(keys); l++)
	{
		InsertNode(root, keys[l]);
	}

	cout << "Pneumonoultramicroscopicsilicovolcanocon" << "......." << output[SearchNode(root, "Pneumonoultramicroscopicsilicovolcanocon")] << endl;
	cout << "GitHub" << "......." << output[SearchNode(root, "GitHub")] << endl;
	cout << "VisualStudio" << "......."  << output[SearchNode(root, "VisualStudio")] << endl;
	cout << "C++" << "......." << output[SearchNode(root, "C++")] << endl;
	cout << "HelloWorld!" << "......." << output[SearchNode(root, "HelloWorld!")] << endl;
	cout << "junkmail@github.com" << "......." << output[SearchNode(root, "junkmail@github.com")] << endl;
}