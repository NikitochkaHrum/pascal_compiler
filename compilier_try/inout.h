#pragma once
#include "inout_classes.h"
#include "error_handler.h"

class InOutModule
{
public:
    InOutModule(const char* In, const char* Out = "");
    std::pair<std::string, TextPos> GetNextLex();
    bool ready;
    void print_semantic_errors(ErrorHandler h);
private:
    std::string s, cur;
    std::vector<std::string> strs;
    TextPos pos;
    int idx, comment, quotes;
};

const std::pair<std::string, TextPos> END_LEXEMS = std::make_pair("", TextPos(INT_MIN, INT_MIN));