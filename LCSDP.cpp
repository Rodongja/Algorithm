#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

typedef struct structLCSTable
{
	vector<vector<int>> Data;
}LCSTable;

int LCS(string X, string Y, int i, int j, LCSTable* Table)
{
	int m = 0;
	int n = 0;

	for(m = 0; m <= i; m++)
		Table->Data[m][0] = 0;

	for (n = 0; n <= j; n++)
		Table->Data[0][n] = 0;

	for (m = 1; m <= i; m++)
	{
		for (n = 1; n <= j; n++)
		{
			if (X[m - 1] == Y[n - 1])
			{
				Table->Data[m][n] = Table->Data[m - 1][n - 1] + 1;
			}
			else
			{
				if (Table->Data[m][n - 1] >= Table->Data[m - 1][n])
				{
					Table->Data[m][n]= Table->Data[m][n - 1];
				}
				else
				{
					Table->Data[m][n] = Table->Data[m - 1][n];
				}
			}
		}
	}

	return Table->Data[i][j];
}

void LCS_TraceBack(string X, string Y, int m, int n, LCSTable* Table, string& LCS)
{
	if (m == 0 || n == 0)
	{
		return;
	}

	if (X[m - 1] == Y[n - 1])
	{
		LCS_TraceBack(X, Y, m - 1, n - 1, Table, LCS);
		LCS += X[m - 1];
	}
	else if (Table->Data[m - 1][n] >= Table->Data[m][n - 1])
	{
		LCS_TraceBack(X, Y, m - 1, n, Table, LCS);
	}
	else
	{
		LCS_TraceBack(X, Y, m, n - 1, Table, LCS);
	}
}

void LCS_PrintTable(LCSTable* Table, const string& X, const string& Y, int LEN_X, int LEN_Y)
{
	// 상단 헤더
	cout << "    "; // 왼쪽 여백
	for (int j = 0; j < LEN_Y; j++)
	{
		cout << Y[j] << " ";
	}
	cout << "\n";

	// 테이블
	for (int i = 0; i <= LEN_X; i++)
	{
		if (i == 0)
			cout << "  "; // 첫 행 왼쪽 여백
		else
			cout << X[i - 1] << " "; // 첫 열

		for (int j = 0; j <= LEN_Y; j++)
		{
			cout << Table->Data[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	string X = "GOOD MORNING.";
	string Y = "GUTEN MORGEN.";
	string Result;

	int LEN_X = X.length();
	int LEN_Y = Y.length();

	int i = 0;
	int Length = 0;

	LCSTable Table;

	Table.Data.resize(LEN_X + 1, vector<int>(LEN_Y + 1, 0));

	Length = LCS(X, Y, LEN_X, LEN_Y, &Table);

	LCS_PrintTable(&Table, X, Y, LEN_X, LEN_Y);

	size_t TableSize = sizeof(Table.Data[LEN_X][LEN_Y] + 1);
	Result.resize(TableSize, 0);

	LCS_TraceBack(X, Y, LEN_X, LEN_Y, &Table, Result);

	cout << "\n" << "LCS:\"" << Result << "\"(Length:" << Length << ")\n";

	return 0;
}