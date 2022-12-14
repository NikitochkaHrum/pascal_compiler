#pragma once

#include <cstring>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>
#include<map>
#include<iomanip>
#include<iterator>

#pragma warning(disable : 4996)

#pragma comment(linker, "/STACK:16777216")

class TextPos
{
public:
    int line_number, char_number;
    TextPos();
    TextPos(int line_number_, int char_number_);

};

bool operator==(const TextPos a, const TextPos b);
bool operator!=(const TextPos a, const TextPos b);
