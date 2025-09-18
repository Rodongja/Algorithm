//#include <stdio.h>
//#include "DisjointSet.h"
//#include <iostream>
//
//using namespace std;
//
//int main(void)
//{
//	int a = 1, b = 2, c = 3, d = 4;
//
//	DisjointSet* Set1 = DS_MakeSet(&a);
//	DisjointSet* Set2 = DS_MakeSet(&b);
//	DisjointSet* Set3 = DS_MakeSet(&c);
//	DisjointSet* Set4 = DS_MakeSet(&d);
//
//	cout << "Set1 == Set2 : " << (DS_FindSet(Set1) == DS_FindSet(Set2)) << endl;
//
//	DS_UnionSet(Set1, Set3);
//	cout << "Set1 == Set3 : " << (DS_FindSet(Set1) == DS_FindSet(Set3)) << endl;
//
//	DS_UnionSet(Set3, Set4);
//	cout << "Set3 == Set4 : " << (DS_FindSet(Set3) == DS_FindSet(Set4)) << endl;
//	return 0;
//}