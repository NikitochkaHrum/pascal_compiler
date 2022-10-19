#include "lexer.h"

CLexer::CLexer(const char * In, const char * Out){
    InOut = std::make_unique<InOutModule>(In, Out);
}

CTokenPtr CLexer::GetNextToken(){
    
}