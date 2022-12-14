#include "pch.h"
#include "exceptions.h"

CTokenExpectedException::CTokenExpectedException() {
    msg = "CTokenExpectedException";
}

CTokenExpectedException::CTokenExpectedException(TokenTp tt, TextPos position) : std::exception() {
    std::string pos_str = "Line " + std::to_string(position.line_number + 1) + ", Char " + std::to_string(position.char_number + 1) + "\n";
    std::string what_expected;
    switch (tt) {
    case Constant: {
        what_expected = "Const";
        break;
    }
    case Identifier: {
        what_expected = "Identifier";
        break;
    }
    case KeyWord: {
        what_expected = "KeyWord";
        break;
    }
    case Operator: {
        what_expected = "Operator";
        break;
    }
    default: {
        what_expected = "another Token Type";
        break;
    }
    }
    msg = "Expected " + what_expected + " on " + pos_str;
}

std::string CTokenExpectedException::what() {
    return msg;
}