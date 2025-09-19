//#include "OpenAddressing.h"
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//	HashTable* HT = OAHT_CreateHashTable(11);
//
//	OAHT_Set(&HT, "MSFT", "Microsoft Corporation");
//	OAHT_Set(&HT, "JAVA", "SunMicrosystems");
//	OAHT_Set(&HT, "REDH", "Red Hat Linux");
//	OAHT_Set(&HT, "APAC", "Apache Org");
//	OAHT_Set(&HT, "MZYMZZ", "Unisys Ops Check"); // APAC¿Í Ãæµ¹
//	OAHT_Set(&HT, "IBM", "IBL Ltd.");
//	OAHT_Set(&HT, "ORCL", "Oracle Corporation");
//	OAHT_Set(&HT, "CSCO", "Cisco Systems, Inc");
//	OAHT_Set(&HT, "GOOG", "Google Inc.");
//	OAHT_Set(&HT, "YHOO", "Yahoo! Inc.");
//	OAHT_Set(&HT, "NOVL", "Novell, Inc.");
//
//	cout << "\n";
//	cout << "Key:" << "MSFT" << ", Value:" << OAHT_Get(HT, "MSFT") << "\n";
//	cout << "Key:" << "JAVA" << ", Value:" << OAHT_Get(HT, "JAVA") << "\n";
//	cout << "Key:" << "REDH" << ", Value:" << OAHT_Get(HT, "REDH") << "\n";
//	cout << "Key:" << "APAC" << ", Value:" << OAHT_Get(HT, "APAC") << "\n";
//	cout << "Key:" << "MZYMZZ" << ", Value:" << OAHT_Get(HT, "MZYMZZ") << "\n";
//	cout << "Key:" << "IBM" << ", Value:" << OAHT_Get(HT, "IBM") << "\n";
//	cout << "Key:" << "ORCL" << ", Value:" << OAHT_Get(HT, "ORCL") << "\n";
//	cout << "Key:" << "CSCO" << ", Value:" << OAHT_Get(HT, "CSCO") << "\n";
//	cout << "Key:" << "GOOG" << ", Value:" << OAHT_Get(HT, "GOOG") << "\n";
//	cout << "Key:" << "YHOO" << ", Value:" << OAHT_Get(HT, "YHOO") << "\n";
//	cout << "Key:" << "NOVL" << ", Value:" << OAHT_Get(HT, "NOVL") << "\n";
//
//	OAHT_DestroyHashTable(HT);
//
//	return 0;
//}