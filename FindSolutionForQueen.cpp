#include <iostream>
#include <vector>

using namespace std;

void PrintSolution(vector<int>& Columns, int NumberOfQueens);
int IsThreatened(vector<int>& Columns, int NewRow);
void FindSolutionForQueen(vector<int>& Columns, int Row, int NumberOfQueens, int* SolutionCount);

void PrintSolution(vector<int>& Columns, int NumberOfQueens)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < NumberOfQueens; i++)
	{
		for (j = 0; j < NumberOfQueens; j++)
		{
			if(Columns[i] == j)
				cout << " Q ";
			else
				cout << " . ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int IsThreatened(vector<int>& Columns, int NewRow)
{
	int CurrentRow = 0;
	int Threatened = 0;

	while (CurrentRow < NewRow)
	{
		if(Columns[NewRow] == Columns[CurrentRow] || abs(Columns[NewRow] - Columns[CurrentRow]) == abs(NewRow - CurrentRow))
		{
			Threatened = 1;
			break;
		}
		CurrentRow++;
	}
	return Threatened;
}

void FindSolutionForQueen(vector<int>& Columns, int Row, int NumberOfQueens, int* SolutionCount)
{
	if (IsThreatened(Columns, Row))
		return;
	if (Row == NumberOfQueens - 1)
	{
		cout << "Solution #" << ++(*SolutionCount) << " : \n";
		PrintSolution(Columns, NumberOfQueens);
	}
	else
	{
		int i;

		for (i = 0; i < NumberOfQueens; i++)
		{
			Columns[Row + 1] = i;
			FindSolutionForQueen(Columns, Row + 1, NumberOfQueens, SolutionCount);
		}
	}
}

int main()
{
	int i = 0;
	int NumberOfQueens = 0;
	int SolutionCount = 0;
	
	cin >> NumberOfQueens;
	
	vector<int> Columns(NumberOfQueens, 0);

	for(i=0; i<NumberOfQueens; i++)
	{
		Columns[0] = i;
		FindSolutionForQueen(Columns, 0, NumberOfQueens, &SolutionCount);
	}

	return 0;
}