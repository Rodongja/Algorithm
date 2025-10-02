#pragma once

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int KnuthMorrisPratt(string Text, size_t TextSize, int Start, string Pattern, int PatternSize);

void Preprocess(string Pattern, size_t PatternSize, vector<int>& Border);