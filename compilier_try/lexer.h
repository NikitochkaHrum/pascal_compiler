#pragma once
#include "lexer_classes.h"
#include <memory>

class CLexer
{
public:
    std::unique_ptr<InOutModule> InOut;
    CLexer(const char* In, const char* Out = "");
    CToken* GetNextToken();
    void test();
};