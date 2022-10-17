#include "classes.h"

CConstToken::CConstToken(TextPos position, std::string lexem){
    tt = Constant;
    pos = position;
    int x1;
    try {
        x1 = stoi(lexem);
        value = new CIntVariant(x1);
        return;
    }
    catch(std::invalid_argument& e){ }
    float x2;
    try {
        x2 = stof(lexem);
        value = new CFloatVariant(x2);
        return;
    }
    catch(std::invalid_argument& e){ }
    value = new CStringVariant(lexem);
}

std::string CConstToken::ToString(){
    return value->ToString();
}

CIdentToken::CIdentToken(TextPos position, std::string lexem){
    tt = Identifier;
    pos = position;
    value=lexem;
}
std::string CIdentToken::ToString(){
    return value;
}

CKeyWordToken::CKeyWordToken(TextPos position, std::string lexem){
    tt = KeyWord;
    pos = position;
    std::string help = lexem;
    std::transform(help.begin(), help.end(), help.begin(), [](unsigned char c){ return std::tolower(c); });
    value = from_str_to_kw[help];
}

std::string CKeyWordToken::ToString(){
    return from_kw_to_str[value];
}

CIntVariant::CIntVariant(int value){
    this->value=value;
    vt = Int;
}

std::string CIntVariant::ToString(){
    return std::to_string(value);
}

CFloatVariant::CFloatVariant(float value){
    this->value=value;
    vt = Float;
}

std::string CFloatVariant::ToString(){
    return std::to_string(value);
}

CStringVariant::CStringVariant(std::string value){
    this->value=value;
    vt = String;
}

std::string CStringVariant::ToString(){
    return value;
}

CBoolVariant::CBoolVariant(bool value){
    this->value=value;
    vt = Bool;
}

std::string CStringVariant::ToString(){
    return value;
}

CLexer::CLexer(const char * In, const char * Out=""){
    InOut = new InOutModule(In, Out);
}