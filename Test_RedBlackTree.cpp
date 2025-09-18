#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

RBTNode* Nil;

//int main()
//{
//	RBTNode* Tree = nullptr;
//	RBTNode* Node = nullptr;
//
//	Nil = RBT_CreateNode(0);
//	Nil->Color = RBTNode::BLACK;
//
//	while (1)
//	{
//		int cmd = 0;
//		int param = 0;
//		string buffer;
//		
//
//		cout << "Enter command number :" << endl;
//		cout << "(1) Create a node, (2) Remove a node, (3) Search a Node" << endl;
//		cout << "(4) Display Tree, (5) quit" << endl;
//		cout << "command number:";
//
//		getline(cin, buffer);
//		istringstream(buffer) >> cmd;
//
//		if (cmd < 1 || cmd > 5)
//		{
//			cout << "Invalid command number." << endl;
//			continue;
//		}
//		else if (cmd == 4)
//		{
//			RBT_PrintTree(Tree, 0, 0);
//			cout << endl;
//			continue;
//		}
//		else if (cmd == 5)
//		{
//			break;
//		}
//
//		cout << "Enter parameter (1~200) :" << endl;
//		
//		getline(cin, buffer);
//		istringstream(buffer) >> param;
//
//		if (param < 1 || param > 200)
//		{
//			cout << "Invalid parameter." << param << endl;
//			continue;
//		}
//
//		switch (cmd)
//		{
//		case 1:
//			RBT_InsertNode(&Tree, RBT_CreateNode(param));
//			break;
//		case 2:
//			Node = RBT_RemoveNode(&Tree, param);
//
//			if (Node == nullptr)
//			{
//				cout << "Not found node to delete:" << param << endl;
//			}
//			else
//			{
//				RBT_DestroyNode(Node);
//			}
//			break;
//
//		case 3:
//			Node = RBT_SearchNode(Tree, param);
//
//			if (Node == nullptr)
//				cout << "Not found node:" << param << endl;
//			else
//				cout << "Found Node: " << Node->Data << "(Color:" << (Node->Color == RBTNode::RED ? "RED" : "BLACK") << ")" << endl;
//			break;
//		}
//		cout << endl;
//	}
//	RBT_DestroyTree(Tree);
//	return 0;
//}