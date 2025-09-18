#include "RedBlackTree.h"
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

extern RBTNode* Nil;

void RBT_DestroyTree(RBTNode* Tree)
{
    if (Tree->Right != Nil)
        RBT_DestroyTree(Tree->Right);
    if (Tree->Left != Nil)
        RBT_DestroyTree(Tree->Left);

    Tree->Left = Nil;
    Tree->Right = Nil;

    RBT_DestroyNode(Tree);
}

RBTNode* RBT_CreateNode(ElementType NewData)
{
    RBTNode* NewNode = new RBTNode;
    NewNode->Parent = nullptr;
    NewNode->Left = nullptr;
    NewNode->Right = nullptr;
    NewNode->Data = NewData;
    NewNode->Color = RBTNode::BLACK;

    return NewNode;
}

void RBT_DestroyNode(RBTNode* Node)
{
    delete Node;
}

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target)
{
    if (Tree == Nil)
        return nullptr;

    if (Tree->Data > Target)
        return RBT_SearchNode(Tree->Left, Target);
    else if (Tree->Data < Target)
        return RBT_SearchNode(Tree->Right, Target);
    else
        return Tree;
}

RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{
    if (Tree == Nil)
        return Nil;

    if (Tree->Left == Nil)
        return Tree;
    else
        return RBT_SearchMinNode(Tree->Left);
}

void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode)
{
    RBT_InsertNodeHelper(Tree, NewNode);
    
    NewNode->Color = RBTNode::RED;
    NewNode->Left = Nil;
    NewNode->Right = Nil;

    RBT_RebuildAfterInsert(Tree, NewNode);
}

void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode)
{
    if ((*Tree) == nullptr)
    {
        (*Tree) = NewNode;
    }

    if ((*Tree)->Data < NewNode->Data)
    {
        if ((*Tree)->Right == Nil)
        {
            (*Tree)->Right = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            RBT_InsertNodeHelper(&(*Tree)->Right, NewNode);
    }
    else if ((*Tree)->Data > NewNode->Data)
    {
        if ((*Tree)->Left == Nil)
        {
            (*Tree)->Left = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);
    }
}

RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data)
{
    RBTNode* Removed = nullptr;
    RBTNode* Successor = nullptr;
    RBTNode* Target = RBT_SearchNode((*Root), Data);
    
    if (Target == nullptr)
    {
        return nullptr;
    }

    // 자식노드가 0~1개일 때
    if (Target->Left == Nil || Target->Right == Nil)
    {
        Removed = Target;
    }
    else
    {
        Removed = RBT_SearchMinNode(Target->Right);
        Target->Data = Removed->Data;
    }

    // 삭제한 Successor노드의 오른쪽이 Nil이면 Nil을 가져오고, 오른쪽에 자식 노드가 있었으면 자식 노드를 가져옴
    Successor = Removed->Right;

    Successor->Parent = Removed->Parent;

    if (Removed->Parent == nullptr)
        (*Root) = Successor;
    else
    {
        if (Removed == Removed->Parent->Left)
            Removed->Parent->Left = Successor;
        else
            Removed->Parent->Right = Successor;
    }

    if (Removed->Color == RBTNode::BLACK)
        RBT_RebuildAfterRemove(Root, Successor);

    return Removed;
}

void RBT_RebuildAfterInsert(RBTNode** Root, RBTNode* X)
{
    while (X != (*Root) && X->Parent->Color == RBTNode::RED)
    {
        if (X->Parent == X->Parent->Parent->Left)
        {
            RBTNode* Uncle = X->Parent->Parent->Right;
            if (Uncle->Color == RBTNode::RED)
            {
                X->Parent->Color = RBTNode::BLACK;
                Uncle->Color = RBTNode::BLACK;
                X->Parent->Parent->Color = RBTNode::RED;

                X = X->Parent->Parent;
            }
            else
            {
                if (X == X->Parent->Right)
                {
                    X = X->Parent;
                    RBT_RotateLeft(Root, X);
                }
                X->Parent->Color = RBTNode::BLACK;
                X->Parent->Parent->Color = RBTNode::RED;

                RBT_RotateRight(Root, X->Parent->Parent);
            }
        }
        else
        {
            RBTNode* Uncle = X->Parent->Parent->Left;
            if (Uncle->Color == RBTNode::RED)
            {
                X->Parent->Color = RBTNode::BLACK;
                Uncle->Color = RBTNode::BLACK;
                X->Parent->Parent->Color = RBTNode::RED;

                X = X->Parent->Parent;
            }
            else
            {
                if (X == X->Parent->Left)
                {
                    X = X->Parent;
                    RBT_RotateRight(Root, X);
                }

                X->Parent->Color = RBTNode::BLACK;
                X->Parent->Parent->Color = RBTNode::RED;
                RBT_RotateLeft(Root, X->Parent->Parent);
            }
        }
    }
    (*Root)->Color = RBTNode::BLACK;
}

void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor)
{
    RBTNode* Sibling = nullptr;

    while (Successor->Parent != nullptr && Successor->Color == RBTNode::BLACK)
    {
        if (Successor == Successor->Parent->Left)
        {
            Sibling = Successor->Parent->Right;

            if (Sibling->Color == RBTNode::RED)
            {
                Sibling->Color = RBTNode::BLACK;
                Successor->Parent->Color = RBTNode::RED;
                RBT_RotateLeft(Root, Successor->Parent);
            }
            else
            {
                if (Sibling->Left->Color == RBTNode::BLACK && Sibling->Right->Color == RBTNode::BLACK)
                {
                    Sibling->Color = RBTNode::RED;
                    Successor = Successor->Parent;
                }
                else
                {
                    if (Sibling->Left->Color == RBTNode::RED)
                    {
                        Sibling->Left->Color = RBTNode::BLACK;
                        Sibling->Color = RBTNode::RED;

                        RBT_RotateRight(Root, Sibling);
                        Sibling = Successor->Parent->Right;
                    }

                    Sibling->Color = Successor->Parent->Color;
                    Successor->Parent->Color = RBTNode::BLACK;
                    Sibling->Right->Color = RBTNode::BLACK;
                    RBT_RotateLeft(Root, Successor->Parent);
                    Successor = (*Root);
                }
            }
        }
        else
        {
            Sibling = Successor->Parent->Left;

            if (Sibling->Color == RBTNode::RED)
            {
                Sibling->Color = RBTNode::BLACK;
                Successor->Parent->Color = RBTNode::RED;
                RBT_RotateRight(Root, Successor->Parent);
            }
            else
            {
                if (Sibling->Right->Color == RBTNode::BLACK && Sibling->Left->Color == RBTNode::BLACK)
                {
                    Sibling->Color = RBTNode::RED;
                    Successor = Successor->Parent;
                }
                else
                {
                    if (Sibling->Right->Color == RBTNode::RED)
                    {
                        Sibling->Right->Color = RBTNode::BLACK;
                        Sibling->Color = RBTNode::RED;

                        RBT_RotateLeft(Root, Sibling);
                        Sibling = Successor->Parent->Left;
                    }

                    Sibling->Color = Successor->Parent->Color;
                    Successor->Parent->Color = RBTNode::BLACK;
                    Sibling->Left->Color = RBTNode::BLACK;
                    RBT_RotateRight(Root, Successor->Parent);
                    Successor = (*Root);
                }
            }
        }
    }
}

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount)
{
    int i = 0;
    char c = 'X';
    int v = -1;
    string cnt;

    if (Node == nullptr || Node == Nil)
        return;

    if (Node->Color == RBTNode::BLACK)
        BlackCount++;

    if (Node->Parent != nullptr)
    {
        v = Node->Parent->Data;

        if (Node->Parent->Left == Node)
            c = 'L';

        else
            c = 'R';
    }

    if (Node->Left == Nil && Node->Right == Nil)
        cnt = "------- " + to_string(BlackCount);
    else
        cnt = "";

    for (i = 0; i < Depth; i++)
        cout << "  ";

    cout << Node->Data << " " << (Node->Color == RBTNode::RED ? "RED" : "BLACK") << " [" << c << "," << v << "] " << cnt << endl;

    RBT_PrintTree(Node->Left, Depth + 1, BlackCount);
    RBT_PrintTree(Node->Right, Depth + 1, BlackCount);
}

void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent)
{
    RBTNode* RightChild = Parent->Right;

    Parent->Right = RightChild->Left;

    if (RightChild->Left != Nil)
        RightChild->Left->Parent = Parent;

    RightChild->Parent = Parent->Parent;

    if (Parent->Parent == nullptr)
        (*Root) = RightChild;
    else
    {
        if (Parent == Parent->Parent->Left)
            Parent->Parent->Left = RightChild;
        else
            Parent->Parent->Right = RightChild;
    }

    RightChild->Left = Parent;
    Parent->Parent = RightChild;
}

void RBT_RotateRight(RBTNode** Root, RBTNode* Parent)
{
    RBTNode* LeftChild = Parent->Left;
    
    Parent->Left = LeftChild->Right;

    if (LeftChild->Right != Nil)
        LeftChild->Right->Parent = Parent;

    LeftChild->Parent = Parent->Parent;

    if (Parent->Parent == nullptr)
        (*Root) = LeftChild;
    else
    {
        if (Parent == Parent->Parent->Left)
            Parent->Parent->Left = LeftChild;
        else
            Parent->Parent->Right = LeftChild;
    }

    LeftChild->Right = Parent;
    Parent->Parent = LeftChild;
}
