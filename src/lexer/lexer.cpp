#include "lexer.h"

CLexer::CLexer(const char * In, const char * Out){
    InOut = new InOutModule(In, Out);
}

CToken * CLexer::GetNextToken(){
    
}