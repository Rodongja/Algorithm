#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

BSTNode* BST_CreateNode(ElementType NewData)
{
    BSTNode* NewNode = new BSTNode;
    NewNode->Left = nullptr;
    NewNode->Right = nullptr;
    NewNode->Data = NewData;
    
    return NewNode;
}

void BST_DestroyNode(BSTNode* Node)
{
    delete Node;
}

void BST_DestroyTree(BSTNode* Tree)
{
    //if (Tree->Right != NULL)
    //    BST_DestroyNode(Tree->Right);

    //if (Tree->Left != NULL)
    //    BST_DestroyNode(Tree->Left);

    //Tree->Left = nullptr;
    //Tree->Right = nullptr;
    //BST_DestroyNode(Tree);

    if (Tree == nullptr)
        return;
    BST_DestroyTree(Tree->Left);
    BST_DestroyTree(Tree->Right);
    BST_DestroyNode(Tree);
}

BSTNode* BST_SearchNode(BSTNode* Tree, ElementType Target)
{
    if (Tree == nullptr)
        return nullptr;

    if (Tree->Data == Target)
        return Tree;
    else if (Tree->Data > Target)
        return BST_SearchNode(Tree->Left, Target);
    else
        return BST_SearchNode(Tree->Right, Target);
}

BSTNode* BST_SearchMinNode(BSTNode* Tree)
{
    if (Tree == nullptr)
        return nullptr;
    if (Tree->Left == nullptr)
        return Tree;
    else
        return BST_SearchMinNode(Tree->Left);
}

void BST_InsertNode(BSTNode* Tree, BSTNode* Child)
{
    if (Tree->Data < Child->Data)
    {
        if (Tree->Right == nullptr)
            Tree->Right = Child;
        else
            BST_InsertNode(Tree->Right, Child);
    }

    else if (Tree->Data > Child->Data)
    {
        if (Tree->Left == nullptr)
            Tree->Left = Child;
        else
            BST_InsertNode(Tree->Left, Child);
    }
}

BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target)
{
    BSTNode* Removed = nullptr;

    if (Tree == nullptr)
    {
        return nullptr;
    }

    if (Tree->Data > Target)
    {
        Removed = BST_RemoveNode(Tree->Left, Tree, Target);
    }
    else if(Tree->Data < Target)
    {
        Removed = BST_RemoveNode(Tree->Right, Tree, Target);
    }
    else
    {
        Removed = Tree;

        // 단말 노드(리프 노드), 부모와 연결끊고 delete
        if (Tree->Left == nullptr && Tree->Right == nullptr)
        {
            if (Parent->Left = Tree)
            {
                Parent->Left = nullptr;
            }
            else
            {
                Parent->Right = nullptr;
            }
            
            // 노드의 delete는 호출자가 직접 BST_DestroyNode로 호출하도록 설계함
        }
        else
        {
            // 자식이 둘인 노드, 오른쪽 자식에서 최소값 노드를 찾아 대체하고 원래 최소값 노드는 삭제
            if (Tree->Left != nullptr && Tree->Right != nullptr)
            {
                BSTNode* MinNode = BST_SearchMinNode(Tree->Right);
                MinNode = BST_RemoveNode(Tree, nullptr, MinNode->Data);
                Tree->Data = MinNode->Data;
            }
            // 자식이 하나인 노드, 자식과 부모를 연결하고 삭제
            else
            {
                BSTNode* Temp = nullptr;
                if (Tree->Left != nullptr)
                {
                    Temp = Tree->Left;
                }
                else
                {
                    Temp = Tree->Right;
                }

                if (Parent->Left == Tree)
                    Parent->Left = Temp;
                else
                    Parent->Right = Temp;
            }
        }
    }
    return Removed;
}


void BST_InorderPrintTree(BSTNode* Node)
{
    if (Node == nullptr)
        return;

    BST_InorderPrintTree(Node->Left);

    cout << Node->Data << " ";

    BST_InorderPrintTree(Node->Right);
}
