#pragma once
#include "classes.h"

class CLexer
{
public:
    InOutModule * InOut;
    CLexer(const char * In, const char * Out="");
    CToken * GetNextToken();
};