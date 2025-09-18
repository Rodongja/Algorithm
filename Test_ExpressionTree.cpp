//#include "ExpressionTree.h"
//
//#include <iostream>
//
//using namespace std;
//
//int main(void)
//{
//	ETNode* Root = nullptr;
//
//	char PostfixExpression[20] = "71*52-/";
//
//	ET_BuildExpressionTree(PostfixExpression, &Root);
//
//	cout << "Preorder ..." << endl;
//	ET_PreorderPrintTree(Root);
//	cout << endl << endl;
//	cout << "Preorder ..." << endl;
//	ET_InorderPrintTree(Root);
//	cout << endl << endl;
//	cout << "Preorder ..." << endl;
//	ET_PostorderPrintTree(Root);
//	cout << endl;
//
//	cout << "Evaulation result : " << ET_Evaluate(Root) << endl;
//
//	ET_DestroyTree(Root);
//
//	return 0;
//}