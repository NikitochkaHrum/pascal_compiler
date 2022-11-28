#pragma once
#include "../lexer/classes.h"

class CTokenExpectedException : public std::exception {
private:
    std::string msg;
public:
    CTokenExpectedException();
    CTokenExpectedException(TokenType tt, TextPos position);
    std::string what();
};