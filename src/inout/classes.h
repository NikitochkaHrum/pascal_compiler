#pragma once
#include <bits/stdc++.h>

class TextPos
{
public:
    int line_number, char_number;
    TextPos();
    TextPos(int line_number_, int char_number_);
    
};

bool operator==(const TextPos a, const TextPos b);
bool operator!=(const TextPos a, const TextPos b);
