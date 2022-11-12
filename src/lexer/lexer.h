#pragma once
#include "classes.h"
#include <memory>

class CLexer
{
public:
    std::unique_ptr<InOutModule> InOut;
    CLexer(const char * In, const char * Out="");
    std::unique_ptr<CToken> GetNextToken();
    void test();
};