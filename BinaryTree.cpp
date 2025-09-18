#include "BinaryTree.h"
#include <iostream>

using namespace std;

SBTNode* SBT_CreateNode(ElementType NewData)
{
	SBTNode* NewNode = new SBTNode();
	NewNode->Left = nullptr;
	NewNode->Right = nullptr;
	NewNode->Data = NewData;
	
	return NewNode;
}

void SBT_DestroyNode(SBTNode* Node)
{
	delete Node;
}

void SBT_DestroyTree(SBTNode* Root)
{
	if (Root == nullptr)
		return;

	// 후위 순회 방식으로 모든 노드를 해제
	SBT_DestroyTree(Root->Left);
	SBT_DestroyNode(Root->Right);
	SBT_DestroyNode(Root);
}

void SBT_PreorderPrintTree(SBTNode* Node)
{
	if(Node == nullptr)
		return;
	cout << " " << Node->Data;
	SBT_PreorderPrintTree(Node->Left);
	SBT_PreorderPrintTree(Node->Right);
}

void SBT_InorderPrintTree(SBTNode* Node)
{
	if (Node == nullptr)
		return;
	SBT_InorderPrintTree(Node->Left);
	cout << " " << Node->Data;
	SBT_InorderPrintTree(Node->Right);
}

void SBT_PostorderPrintTree(SBTNode* Node)
{
	if (Node == nullptr)
		return;
	SBT_PostorderPrintTree(Node->Left);
	SBT_PostorderPrintTree(Node->Right);
	cout << " " << Node->Data;
}
