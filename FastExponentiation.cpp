#include <stdio.h>
#include <iostream>

using namespace std;

typedef unsigned long ULONG;

ULONG Power(int Base, int Exponent)
{
	if (Exponent == 1)
		return Base;
	else if (Base == 0)
		return 1;
	if (Exponent % 2 == 0)
	{
		ULONG NewBase = Power(Base, Exponent / 2);
		return NewBase * NewBase;
	}
	else
	{
		ULONG NewBase = Power(Base, (Exponent - 1) / 2);
		return (NewBase * NewBase) * Base;
	}
}

//int main(void)
//{
//	int Base = 2;
//	int Exponent = 30;
//	cout << Base << "^" << Exponent << " = " << Power(Base, Exponent) << "\n";
//
//	return 0;
//}