#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

void PrintSearchResult(int SearchTarget, BSTNode* Result)
{
	if (Result != nullptr)
	{
		cout << "Found : " << Result->Data << endl;
	}
	else
	{
		cout << "Not Found : " << SearchTarget << endl;
	}
}
//
//int main()
//{
//	BSTNode* Tree = BST_CreateNode(123);
//	BSTNode* Node = nullptr;
//
//	BST_InsertNode(Tree, BST_CreateNode(22));
//	BST_InsertNode(Tree, BST_CreateNode(9918));
//	BST_InsertNode(Tree, BST_CreateNode(424));
//	BST_InsertNode(Tree, BST_CreateNode(17));
//	BST_InsertNode(Tree, BST_CreateNode(3));
//
//	BST_InsertNode(Tree, BST_CreateNode(98));
//	BST_InsertNode(Tree, BST_CreateNode(34));
//
//	BST_InsertNode(Tree, BST_CreateNode(760));
//	BST_InsertNode(Tree, BST_CreateNode(317));
//	BST_InsertNode(Tree, BST_CreateNode(1));
//
//	int SearchTarget = 17;
//	Node = BST_SearchNode(Tree, SearchTarget);
//	PrintSearchResult(SearchTarget, Node);
//
//	BST_InorderPrintTree(Tree);
//	cout << endl;
//
//	cout << "Removing 98..." << endl;
//
//	Node = BST_RemoveNode(Tree, nullptr, 98);
//	BST_DestroyNode(Node);
//
//	BST_InorderPrintTree(Tree);
//	cout << endl;
//
//	cout << "Inserting 111..." << endl;
//
//	BST_InsertNode(Tree, BST_CreateNode(111));
//	BST_InorderPrintTree(Tree);
//	cout << endl;
//
//	BST_DestroyTree(Tree);
//
//	return 0;
//}