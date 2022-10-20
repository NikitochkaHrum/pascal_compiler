#include "lexer.h"
#include "classes.h"

CLexer::CLexer(const char * In, const char * Out){
    InOut = std::make_unique<InOutModule>(In, Out);
}

std::unique_ptr<CToken> CLexer::GetNextToken(){
    auto lexem = InOut->GetNextLex();
    while(lexem.first == " " && lexem != END_LEXEMS){
        lexem = InOut->GetNextLex();
    }
    if(lexem == END_LEXEMS) return nullptr;

    auto low_lexem = make_low(lexem.first);
    for(const auto& [k, v] : from_str_to_kw){
        if(k==low_lexem)
            return std::make_unique<CKeyWordToken>(lexem.second, lexem.first);
    }

    for(const auto& [k, v] : from_str_to_operator){
        if(k==low_lexem)
            return std::make_unique<COperatorToken>(lexem.second, lexem.first);
    }
    bool can = false;
    try {
        auto smth = stof(lexem.first);
        can=true;
    }
    catch(std::invalid_argument& e){ }
    if(!can && !(low_lexem[0]==low_lexem[low_lexem.length()-1] && low_lexem[0]=='"') && low_lexem!="true" && low_lexem!="false")
        return std::make_unique<CIdentToken>(lexem.second, lexem.first);
    return std::make_unique<CConstToken>(lexem.second, lexem.first);
}

int main(){
    auto Lexer = std::make_unique<CLexer>("/home/pna/Documents/study/pascal_compiler/input.txt", "/home/pna/Documents/study/pascal_compiler/output.txt");
    
    auto t = Lexer->GetNextToken();
    while(t){
        switch(t->tt){
            case Constant:{
                std::cout << t->ToString() << '\n';
                std::cout << "\tConstant on pos " << t->pos.line_number << ' ' << t->pos.char_number << '\n';
                std::cout << "\tVar Type = ";
                auto help = static_cast<CConstToken*>(t.get());
                switch (help->value->vt){
                case IntegerType:{
                    std::cout << "Int\n";
                    break;
                }
                case FloatType:{
                    std::cout << "Float\n";
                    break;
                }
                case StringType:{
                    std::cout << "Int\n";
                    break;
                }
                case BoolType:{
                    std::cout << "Bool\n";
                    break;
                }
                }
                std::cout << '\n';
                break;
            }
            case Identifier:{
                std::cout << t->ToString() << '\n';
                std::cout << "\tIdentifier on pos " << t->pos.line_number << ' ' << t->pos.char_number << "\n\n";
                break;
            }
            case KeyWord:{
                std::cout << t->ToString() << '\n';
                std::cout << "\tKeyWord on pos " << t->pos.line_number << ' ' << t->pos.char_number << "\n\n";
                break;
            }
            case Operator:{
                std::cout << t->ToString() << '\n';
                std::cout << "\tOperator on pos " << t->pos.line_number << ' ' << t->pos.char_number << "\n\n";
                break;
            }
        }
        t = Lexer->GetNextToken();
    }
}