#include "BoyerMoore.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iostream>

#define MAX_BUFFER 512

using namespace std;

vector<int> BadCharTable(const string pattern)
{
    size_t patternSize = pattern.size();

    vector<int> bc_table(MAX_BUFFER, patternSize);

    for (int i = 0; i < patternSize; ++i)
    {
        bc_table[(int)pattern[i]] = i;
    }

    return bc_table;
}

vector<int> GoodSuffTable(const string pattern)
{
    size_t patternSize = pattern.size();

	int pattern_point = patternSize;
    int suffix_point = pattern_point + 1;

	vector<int> suf_table(patternSize + 1, 0);
    suf_table[pattern_point] = suffix_point;

	vector<int> skip_table(patternSize + 1, 0);

    while (pattern_point > 0)
    {
        while (suffix_point <= patternSize && pattern[pattern_point - 1] != pattern[suffix_point-1])
        {
            if (skip_table[suffix_point] == 0)
                skip_table[suffix_point] = suffix_point - pattern_point;
            suffix_point = suf_table[suffix_point];
        }
        suf_table[--pattern_point] = --suffix_point;
    }

    suffix_point = suf_table[0];
    
    while (pattern_point < patternSize)
    {
        if (skip_table[pattern_point] == 0)
        {
            skip_table[pattern_point] = suffix_point;
        }
        if (pattern_point++ == suffix_point)
        {
            suffix_point = suf_table[suffix_point];
        }
    }

    for (auto& suf : suf_table)
    {
        cout << suf << ", ";
    }
    for (auto& skip : skip_table)
    {
        cout << skip << ", ";
    }
    cout << "\n";

    return skip_table;
}

int search(const vector<int> bad_table, const vector<int> suf_table, const string H, const string pattern)
{
    const int h_size = H.size();
    const int p_size = pattern.size();

    int begin = 0;

    if (h_size < p_size) return -1;

    while (begin <= h_size - p_size)
    {
        int matched = p_size;

        while (matched > 0 && pattern[matched - 1] == H[begin + (matched - 1)])
        {
            --matched;
        }
        
        if (matched == 0)
            return begin;

        if (bad_table[H[begin + matched]] != p_size)
        {
            begin += max(matched - bad_table[H[begin + matched]], suf_table[matched]);
        }
        else
        {
			begin += max(suf_table[matched], matched);
        }
    }
    return -1;
}


int main()
{
    string FilePath;

    string Text;
    string Pattern;
    int PatternSize = 0;
    int Line = 0;

    cout << "Enter file path: ";
    getline(cin, FilePath);  // 경로 입력


    ifstream fp(FilePath);

    if (!fp.is_open())
    {
        cout << "Cannot open file: " << FilePath << "\n";
        return 1;
    }

    cout << "Enter search pattern: ";
    getline(cin, Pattern);   // 검색 패턴 입력

	transform(Pattern.begin(), Pattern.end(), Pattern.begin(), ::tolower);
    
	const vector<int> bad_table = BadCharTable(Pattern);
	const vector<int> suf_table = GoodSuffTable(Pattern);

    while (getline(fp, Text))
    {
        ++Line;
        transform(Text.begin(), Text.end(), Text.begin(), ::tolower);

		int position = search(bad_table, suf_table, Text, Pattern);

        if (position >= 0)
        {
			cout << "line: " << Line << ", column: " << position + 1 << " : " << Text << "\n";
        }
    }
    fp.close();

    return 0;
}
