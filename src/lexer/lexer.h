#pragma once
#include "classes.h"
#include <memory>

using CTokenPtr = std::unique_ptr<CToken>;

class CLexer
{
public:
    std::unique_ptr<InOutModule> InOut;
    CLexer(const char * In, const char * Out="");
    CTokenPtr GetNextToken();
};