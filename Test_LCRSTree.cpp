//#include "LCRSTree.h"
//
//int main(void)
//{
//	LCRSNode* Root = LCRS_CreateNode('A');
//	LCRSNode* B = LCRS_CreateNode('B');
//	LCRSNode* C = LCRS_CreateNode('C');
//	LCRSNode* D = LCRS_CreateNode('D');
//	LCRSNode* E = LCRS_CreateNode('E');
//	LCRSNode* F = LCRS_CreateNode('F');
//	LCRSNode* G = LCRS_CreateNode('G');
//	LCRSNode* H = LCRS_CreateNode('H');
//	LCRSNode* I = LCRS_CreateNode('I');
//	LCRSNode* J = LCRS_CreateNode('J');
//	LCRSNode* K = LCRS_CreateNode('K');
//
//	LCRS_AddChild(Root, B);
//	LCRS_AddChild(B, C);
//	LCRS_AddChild(B, D);
//	LCRS_AddChild(D, E);
//	LCRS_AddChild(D, F);
//
//	LCRS_AddChild(Root, G);
//	LCRS_AddChild(G, H);
//
//	LCRS_AddChild(Root, I);
//	LCRS_AddChild(I, J);
//	LCRS_AddChild(J, K);
//
//	LCRS_PrintTree(Root, 0);
//
//
//	LCRS_PrintNodeAtLevel(Root, 2);
//
//	LCRS_DestroyNode(Root);
//
//	return 0;
//}