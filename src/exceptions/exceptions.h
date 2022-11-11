#pragma once
#include "../lexer/classes.h"

class CTokenExpectedException : public std::exception {
private:
    char * msg;
public:
    CTokenExpectedException();
    CTokenExpectedException(TokenType tt, TextPos position);
    char * what();
};