#ifndef LCRS_TREE_H	
#define LCRS_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct tagLCRSNode
{
	struct tagLCRSNode* LeftChild;
	//struct LCRSNode* LeftChild; // ���� ������ ���������ʾ� LCRSNode�� ��� �Ұ���
	struct tagLCRSNode* RightSibling;

	ElementType Data;
} LCRSNode;

typedef struct StackItem{
	LCRSNode* Node;
	int Level;
} StackItem;

LCRSNode* LCRS_CreateNode(ElementType NewData);
void LCRS_DestroyNode(LCRSNode* Node);
void LCRS_DestroyTree(LCRSNode* Root);	

void LCRS_AddChild(LCRSNode* ParentNode, LCRSNode* ChildNode);
void LCRS_PrintTree(LCRSNode* Node, int Depth);

void LCRS_PrintNodeAtLevel(LCRSNode* Root, int Level);

#endif