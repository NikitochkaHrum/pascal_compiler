#include "classes.h"

class InOutModule
{
public:
    InOutModule(const char * In, const char * Out="");
    std::pair<std::string, TextPos> GetNextLex();
    bool ready;
private:
    std::string s, cur;
    TextPos pos;
    int idx, comment;
};

const std::pair<std::string, TextPos> END = std::make_pair("", TextPos(INT_MIN, INT_MIN));