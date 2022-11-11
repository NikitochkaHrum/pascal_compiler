#pragma once
#include "../exceptions/exceptions.h"
#include "../lexer/lexer.h"

class CCompilier
{
private:
    std::unique_ptr<CLexer> lexer = nullptr;
    std::unique_ptr<CToken> token = nullptr;
    std::unique_ptr<CToken> GetNextToken();
public:
    CCompilier(const char * In, const char * Out="");
    void Accept(std::unique_ptr<CToken> expected_token);
};