#include <iostream>
#include <fstream>
#include <string>

#include "KnuthMorrisPratt.h"

using namespace std;

int main()
{
	string FilePath; 

	string Text;
	string Pattern;
	int PatternSize = 0;
	int Line = 0;

	cout << "Enter file path: ";
	getline(cin, FilePath);  // ��� �Է�

	PatternSize = Pattern.size();

	ifstream fp(FilePath);

	if (!fp.is_open())
	{
		cout << "Cannot open file: " << FilePath << "\n";
		return 1;
	}

	cout << "Enter search pattern: ";
	getline(cin, Pattern);   // �˻� ���� �Է�

	PatternSize = Pattern.size();

	while (getline(fp,Text))
	{
		int Position = KnuthMorrisPratt(Text, Text.size(), 0, Pattern, PatternSize);

		++Line;

		if (Position >= 0)
		{
			cout << "line:" << Line << ", column:" << Position + 1 << " : " << Text << "\n";
		}
	}

	fp.close();

	return 0;
}