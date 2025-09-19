//#include "Chaining.h"
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//	HashTable* HT = CHT_CreateHashTable(12289);
//
//	CHT_Set(HT, "MSFT", "Microsoft Corporation");
//	CHT_Set(HT, "JAVA", "Sun Microsystems");
//	CHT_Set(HT, "REDH", "Red Hart Linux");
//	CHT_Set(HT, "APAC", "Apache Org");
//	CHT_Set(HT, "ZYMZZ", "Unisys Ops Check"); // APAC¿Í Ãæµ¹
//	CHT_Set(HT, "IBM", "IBM Ltd.");
//	CHT_Set(HT, "ORCL", "Oracle Corporation");
//	CHT_Set(HT, "CSCO", "Cisco Systems");
//	CHT_Set(HT, "GOOG", "Google Inc.");
//	CHT_Set(HT, "YHOO", "Yahoo! Inc.");
//	CHT_Set(HT, "NOVL", "Novell, Inc.");
//
//	cout << endl;
//	cout << "Key:" << "MSFT" << ", Value:" << CHT_Get(HT, "MSMT") << "\n";
//	cout << "Key:" << "JAVA" << ", Value:" << CHT_Get(HT, "JAVA") << "\n";
//	cout << "Key:" << "REDH" << ", Value:" << CHT_Get(HT, "REDH") << "\n";
//	cout << "Key:" << "APAC" << ", Value:" << CHT_Get(HT, "APAC") << "\n";
//	cout << "Key:" << "ZYMZZ" << ", Value:" << CHT_Get(HT, "ZYMZZ") << "\n";
//	cout << "Key:" << "IBM" << ", Value:" << CHT_Get(HT, "IBM") << "\n";
//	cout << "Key:" << "ORCL" << ", Value:" << CHT_Get(HT, "ORCL") << "\n";
//	cout << "Key:" << "CSCO" << ", Value:" << CHT_Get(HT, "CSCO") << "\n";
//	cout << "Key:" << "GOOG" << ", Value:" << CHT_Get(HT, "GOOG") << "\n";
//	cout << "Key:" << "YHOO" << ", Value:" << CHT_Get(HT, "YHOO") << "\n";
//	cout << "Key:" << "NOVL" << ", Value:" << CHT_Get(HT, "NOVL") << "\n";
//
//	CHT_DestroyHashTable(HT);
//
//	return 0;
//}