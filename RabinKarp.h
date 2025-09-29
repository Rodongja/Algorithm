#pragma once
int RabinKarp(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);

int Hash(char* String, int Size);
int ReHash(char* String, int Start, int Size, int HashPrev, int Coefficient);