// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "BST.h"
#include "AVLTree.h"
#include "BTree.h"
#include "Trie.h"

int main()
{
    using namespace std;

    cout << "Select which Data Structure to run: " << endl;
    cout << "1. Binary Search Tree \n2. AVL Tree \n3. BTree \n4. Trie" << endl;
    int choice;
    cin >> choice;
    
    int arr[25] = { 0, 6, 10, 100, 200, 237, 4, 65, 13, 45, 2, 432, 65, 123, 432, 543, 123, 145, 453, 212, 321, 5, 234, 54, 18 };

    //Binary Search Tree
    if (choice == 1)
    {
        BST tree;
        tree.run(tree, arr);
    }

    //AVL Tree
    else if (choice == 2)
    {
        AVLTree tree;
        tree.run(tree, arr);
    }

    //BTree
    else if (choice == 3)
    {
        BTree tree(3);
        tree.run(tree, arr);
    }
    
    //Trie
    else if (choice == 4)
    {
        Trie tree;
        tree.run();
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file