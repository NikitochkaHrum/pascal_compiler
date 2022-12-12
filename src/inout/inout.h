#pragma once
#include "classes.h"
#include "../exceptions/error_handler.h"

class InOutModule
{
public:
    InOutModule(const char * In, const char * Out="");
    std::pair<std::string, TextPos> GetNextLex();
    bool ready;
    void print_semantic_errors(ErrorHandler h);
private:
    std::string s, cur;
    std::vector<std::string> strs;
    TextPos pos;
    int idx, comment;
};

const std::pair<std::string, TextPos> END_LEXEMS = std::make_pair("", TextPos(INT_MIN, INT_MIN));