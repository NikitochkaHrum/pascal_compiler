#include <bits/stdc++.h>

class TextPos
{
public:
    int line_number, char_number;
    TextPos();
    TextPos(int line_number_, int char_number_);
    bool operator==(TextPos b);
};
