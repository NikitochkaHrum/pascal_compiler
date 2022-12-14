#pragma once
#include "lexer_classes.h"

class CTokenExpectedException : public std::exception {
private:
    std::string msg;
public:
    CTokenExpectedException();
    CTokenExpectedException(TokenTp tt, TextPos position);
    std::string what();
};