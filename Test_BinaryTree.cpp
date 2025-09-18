//#include "BinaryTree.h"
//#include <iostream>
//
//using namespace std;
//
//int main(void)
//{
//	SBTNode* A = SBT_CreateNode('A');
//	SBTNode* B = SBT_CreateNode('B');
//	SBTNode* C = SBT_CreateNode('C');
//	SBTNode* D = SBT_CreateNode('D');
//	SBTNode* E = SBT_CreateNode('E');
//	SBTNode* F = SBT_CreateNode('F');
//	SBTNode* G = SBT_CreateNode('G');
//
//	A->Left = B;
//	B->Left = C;
//	B->Right = D;
//
//	A->Right = E;
//	E->Left = F;
//	E->Right = G;
//
//	cout << "PreOrder: " << endl;;
//	SBT_PreorderPrintTree(A);
//	cout << endl << endl;
//
//
//	cout << "InOrder: " << endl;;
//	SBT_InorderPrintTree(A);
//	cout << endl << endl;
//
//
//	cout << "PostOrder: " << endl;;
//	SBT_PostorderPrintTree(A);
//	cout << endl << endl;
//
//	SBT_DestroyTree(A);
//
//	return 0;
//}