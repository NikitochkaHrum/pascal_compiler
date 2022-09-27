#include <bits/stdc++.h>
#include "classes.h"

TextPos::TextPos(){
    line_number = 0;
    char_number = 0;
}

TextPos::TextPos(int line_number_, int char_number_){
    line_number = line_number_;
    char_number = char_number_;
}