#include "LCRSTree.h"
#include "LinkedListStack.h"

LCRSNode* LCRS_CreateNode(ElementType NewData)
{
    LCRSNode* NewNode = (LCRSNode*)malloc(sizeof(LCRSNode));

	NewNode->LeftChild = NULL;
	NewNode->RightSibling = NULL;
	NewNode->Data = NewData;

    return NewNode;
}

void LCRS_DestroyNode(LCRSNode* Node)
{
	free(Node);
}

void LCRS_DestroyTree(LCRSNode* Root)
{
	if(Root->RightSibling != NULL)
	{
		LCRS_DestroyTree(Root->RightSibling);
	}

	if(Root->LeftChild != NULL)
	{
		LCRS_DestroyTree(Root->LeftChild);
	}
	Root->LeftChild = NULL;
	Root->RightSibling = NULL;

	LCRS_DestroyNode(Root);
}

void LCRS_AddChild(LCRSNode* ParentNode, LCRSNode* ChildNode)
{
	if(ParentNode->LeftChild == NULL)
	{
		ParentNode->LeftChild = ChildNode;
	}
	else
	{
		LCRSNode* TempNode = ParentNode->LeftChild;
		while(TempNode->RightSibling != NULL)
		{
			TempNode = TempNode->RightSibling;
		}
		TempNode->RightSibling = ChildNode;
	}
}

void LCRS_PrintTree(LCRSNode* Node, int Depth)
{
	int i = 0;
	for (i = 0; i < Depth - 1; i++)
	{
		printf("   ");
	}

	if(Depth > 0)
	{
		printf("└─ ");
	}

	printf("%c\n", Node->Data);

	if(Node->LeftChild != NULL)
	{
		LCRS_PrintTree(Node->LeftChild, Depth + 1);
	}
	if(Node->RightSibling != NULL)
	{
		LCRS_PrintTree(Node->RightSibling, Depth);
	}
}

void LCRS_PrintNodeAtLevel(LCRSNode* Root, int Level)
{
	if (!Root) return;

	if (Level == 0) {
		printf("%c\n", Root->Data); // 목표 레벨이면 출력
	}
	else {
		// 왼쪽 자식으로 내려가면서 레벨 -1
		LCRS_PrintNodeAtLevel(Root->LeftChild, Level - 1);
	}

	// 같은 레벨의 오른쪽 형제도 탐색
	LCRS_PrintNodeAtLevel(Root->RightSibling, Level);
}
