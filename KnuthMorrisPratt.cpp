#include "KnuthMorrisPratt.h"
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int KnuthMorrisPratt(string Text, size_t TextSize, int Start, string Pattern, int PatternSize)
{
	int i = Start;
	int j = 0;
	int Position = -1;

	vector<int> Border(PatternSize + 1);

	Preprocess(Pattern, PatternSize, Border);

	while (i < TextSize)
	{
		while (j >= 0 && Text[i] != Pattern[j])
			j = Border[j];

		++i;
		++j;

		if (j == PatternSize)
		{
			Position = i - j;
			break;
		}
	}

	return Position;
}

void Preprocess(string Pattern, size_t PatternSize, vector<int>& Border)
{
	int i = 0; 
	int j = -1;

	Border[0] = -1;

	while (i < PatternSize)
	{
		while (j > -1 && Pattern[i] != Pattern[j])
			j = Border[j];
		++i;
		++j;

		Border[i] = j;
	}
}
