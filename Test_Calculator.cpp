//#include <stdio.h>
//#include <string.h>
//#include "Calculator.h"
//
//int main(void)
//{
//	char InfixExpression[100];
//	char PostfixExpression[100];
//	
//	double Result = 0.0;
//
//	memset(InfixExpression, 0, sizeof(InfixExpression));
//	memset(PostfixExpression, 0, sizeof(PostfixExpression));
//
//	printf("Enter Infix Expression:");
//	scanf_s("%99s", InfixExpression, (unsigned)_countof(InfixExpression));
//
//	GetPostfix(InfixExpression, PostfixExpression);
//
//	printf("Infix:%s\nPostfix:%s\n", InfixExpression, PostfixExpression);
//
//	Result = Calculate(PostfixExpression);
//	
//	printf("Infix:%s\nPostfix:%s\n", InfixExpression, PostfixExpression);
//	printf("Calculation Result: %f\n", Result);
//
//	return 0;
//}