#include "pch.h"
#include "inout_classes.h"

TextPos::TextPos() {
    line_number = 0;
    char_number = 0;
}

TextPos::TextPos(int line_number_, int char_number_) {
    line_number = line_number_;
    char_number = char_number_;
}

bool operator==(const TextPos a, const TextPos b) {
    return a.line_number == b.line_number && a.char_number == b.char_number;
}
bool operator!=(const TextPos a, const TextPos b) {
    return !(a == b);
}