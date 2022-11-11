#include "exceptions.h"

CTokenExpectedException::CTokenExpectedException(){
    std::string my = "CTokenExpectedException";
    msg = &my[0];
}

CTokenExpectedException::CTokenExpectedException(TokenType tt, TextPos position) : std::exception(){
    std::string pos_str = "Line " + std::to_string(position.line_number) + ", Char " + std::to_string(position.char_number) + "\n";
    std::string what_expected;
    switch(tt){
        case Constant:{
            what_expected = "Const";
        }
        case Identifier:{
            what_expected = "Ientifier";
        }
        case KeyWord:{
            what_expected = "KeyWord";
        }
        case Operator:{
            what_expected ="Operator";
        }
        default:{
            what_expected ="another Token Type";
        }
    }
    std::string my = "Expected " + what_expected + " on " + pos_str;
    msg = &my[0];
}

char * CTokenExpectedException::what(){
    return msg;
}