#include "compilier.h"

CCompilier::CCompilier(const char * In, const char * Out){
    lexer = std::make_unique<CLexer>(In, Out);
    handler = std::make_unique<ErrorHandler>();
}

void CCompilier::Run(){
    token = lexer->GetNextToken();
    try{
        ProgramBlock();
    }
    catch(CTokenExpectedException& exc){
        std::cout << exc.what() << "\n\n";
    }
    lexer->InOut->print_semantic_errors(*handler.get());
}

std::unique_ptr<CToken> CCompilier::GetNextToken(){
    return lexer->GetNextToken();
}

void CCompilier::Accept(TokenType expected_token_type){
    if(token->tt!=expected_token_type)
        throw CTokenExpectedException(expected_token_type, token->pos);
    if(expected_token_type==Operator){
        last_op = from_str_to_operator[token->ToString()];
        last_pos_of_op[last_op] = token->pos;
    }
    token = GetNextToken();
}

void CCompilier::Accept(OperatorType expected_operator){
    if(token->tt!=Operator)
        throw CTokenExpectedException(Operator, token->pos);;
    auto our = static_cast<COperatorToken*>(token.get());
    if(our->value!=expected_operator)
        throw CTokenExpectedException(Operator, token->pos);
    last_op = expected_operator;
    last_pos_of_op[expected_operator] = token->pos;
    token = GetNextToken();
}

void CCompilier::Accept(KeyWordType expected_keyword){
    if(token->tt!=KeyWord)
        throw CTokenExpectedException(KeyWord, token->pos);;
    auto our = static_cast<CKeyWordToken*>(token.get());
    if(our->value!=expected_keyword)
        throw CTokenExpectedException(KeyWord, token->pos);
    token = GetNextToken();
}

void CCompilier::Accept(VarType expected_var_type){
    if(token->tt!=Constant)
        throw CTokenExpectedException(Constant, token->pos);;
    auto our = static_cast<CConstToken*>(token.get());
    if(our->value->vt!=expected_var_type)
        throw CTokenExpectedException(Constant, token->pos);
    token = GetNextToken();
}

void CCompilier::Add_var(std::string& name, VarType type)
{
	if (vars.find(name) == vars.end())
		vars[name] = type;
	else {
        std::string msg = "Переменная с именем `" + name + "` уже была объявлена";
		handler->add_error(msg, token->pos);
	}
}

VarType CCompilier::Derive (VarType left, VarType right, OperatorType op, TextPos pos_for_error){
    VarType res = DefaultType;
    if(can_cast(left, right))
        res = right;
    
    if(can_cast(right, left))
        res = left;
    
	if (res == StringType) {
		// только +, =, <>
		if (op != from_str_to_operator["+"] && op != from_str_to_operator["="] && op!=from_str_to_operator["<>"]) {
			std::string error_text = "Данную операцию нельзя применить к этим операндам";
			handler->add_error(error_text, pos_for_error);
		}
	}
    // операции сравнения
	if (op == from_str_to_operator["="] || op == from_str_to_operator["<>"] || op == from_str_to_operator[">="] ||
		op == from_str_to_operator["<="] || op == from_str_to_operator[">"] || op == from_str_to_operator["<"] ||
		op == from_str_to_operator["or"] || op == from_str_to_operator["and"])
		return BoolType;
	return res;
}

void CCompilier::ProgramBlock(){
    Accept(ProgramKW);
    Accept(Identifier);
    Accept(from_str_to_operator[";"]);
    MainBlock();
    Accept(from_str_to_operator["."]);
}

void CCompilier::MainBlock(){
                                     //TODO раздел меток
    // if(token->ToString() == from_kw_to_str[ConstKW])
        // ConstBlock();                //Раздел констант
                                     //TODO Раздел типов
    if(token->ToString() == from_kw_to_str[VarKW])
        VarBlock();                  //Раздел переменных
                                     //TODO Раздел процедур и функций
    CompositeOperatorBlock();        //Раздел операторов
}

// void CCompilier::ConstBlock(){
//     Accept(ConstKW);
//     Accept(Identifier);
//     Accept(from_str_to_operator["="]);
//     Accept(Constant);
//     Accept(from_str_to_operator[";"]);
//     while(token->tt==Identifier){
//         Accept(Identifier);
//         Accept(from_str_to_operator["="]);
//         Accept(Constant);
//         Accept(from_str_to_operator[";"]);
//     }
// }

void CCompilier::VarBlock(){
    Accept(VarKW);

    SimilarVars(); //Раздел однотипных переменных
    Accept(from_str_to_operator[";"]);

    while(token->tt == Identifier){
        SimilarVars();
        Accept(from_str_to_operator[";"]);
    }
}

void CCompilier::SimilarVars(){
    std::vector<std::string> vs;
    vs.push_back(token->ToString());
    Accept(Identifier);

    while(token->ToString()==","){
        Accept(from_str_to_operator[","]);
        vs.push_back(token->ToString());
        Accept(Identifier);
    }
    Accept(from_str_to_operator[":"]);
    if(token->tt!=KeyWord){
        Accept(KeyWord);
        return;
    }
    auto our = static_cast<CKeyWordToken*>(token.get());
    auto my_type_kw = our->value;
    VarType my_type;
    switch (my_type_kw)
    {
    case IntegerKW:
        my_type = IntegerType;
        break;
    case FloatKW:
        my_type = FloatType;
        break;
    case StringKW:
        my_type = StringType;
        break;
    case BoolKW:
        my_type = BoolType;
        break;
    default:
        my_type = DefaultType;
        break;
    }
    Accept(my_type_kw);
    for(auto v: vs){
        Add_var(v, my_type);
    }
}   

void CCompilier::CompositeOperatorBlock(){
    Accept(BeginKW);
    OperatorBlock();
    Accept(from_str_to_operator[";"]);

    while(token->tt==Identifier || token->ToString()=="begin"
         || token->ToString()=="if"){
        OperatorBlock();
        Accept(from_str_to_operator[";"]);
    }
    Accept(EndKW);
}

void CCompilier::OperatorBlock(){
    if(token->tt==Identifier)
        SimpleOperatorBlock();
    else if(token->ToString()=="begin" || token->ToString()=="if")
        ComplicatedOperatorBlock();
}

void CCompilier::SimpleOperatorBlock(){
    AssignOperatorBlock();
}

void CCompilier::AssignOperatorBlock(){
    TextPos ident_pos = token->pos;
    std::string ident = token->ToString();
    Accept(Identifier);
    Accept(from_str_to_operator[":="]);
    VarType expr_type = Expression();
    if (vars.find(ident) == vars.end()) {
		std::string error_text = "Переменная не была объявлена";
		handler->add_error(error_text, ident_pos);
	}
    else if (!can_cast(expr_type, vars[ident])) {
        // TODO: вывод ошибки
        std::string error_text = "Вычисленное выражение и переменная имеют разные типы";
        handler->add_error(error_text, last_pos_of_op[from_str_to_operator[":="]]);
    }
}

VarType CCompilier::Expression(){
    VarType t1 = SimpleExpression(), t2;
    auto s = token->ToString();
    if(s == "=" || s == "<>" || s == "<" || s=="<=" || s==">=" || s==">"){
        OperatorType cur_op = from_str_to_operator[s];
        Accept(cur_op);
        t2 = SimpleExpression();
		t1 = Derive(t1, t2, cur_op, last_pos_of_op[cur_op]);
        s=token->ToString();
    }
    return t1;
}

VarType CCompilier::SimpleExpression(){
    if(token->ToString() == "+" || token->ToString() == "-"){
        Accept(from_str_to_operator[token->ToString()]);
    }
    VarType t1 = Term(), t2;
    auto s = token->ToString();
    while(s=="+" || s=="-" || s=="or"){
        OperatorType cur_op = from_str_to_operator[s];
        Accept(cur_op);
        t2 = Term();
        t1 = Derive(t1, t2, cur_op, last_pos_of_op[cur_op]);
        s=token->ToString();
    }
    return t1;
}

VarType CCompilier::Term(){
    VarType t1 = Multiplier(), t2;
    auto s = token->ToString();
    while(s=="div" || s=="mod" || s=="and" || token->ToString()=="*" || token->ToString()=="/"){
        OperatorType cur_op = from_str_to_operator[s];
        Accept(cur_op);
        t2 = Multiplier();
        t1 = Derive(t1, t2, cur_op, last_pos_of_op[cur_op]);
        s = token->ToString();
    }
    return t1;
}

VarType CCompilier::Multiplier(){
    std::string ident = token->ToString();
	TextPos mem_pos = token->pos;
    if(token->tt==Identifier){
        Accept(Identifier);
        if (vars.find(ident) == vars.end()){
			std::string error_text = "Переменная не была объявлена";
		    handler->add_error(error_text, mem_pos);
			return DefaultType;
		}
		return vars[ident];
    }
    else if(token->tt==Constant){
        auto our = static_cast<CConstToken*>(token.get());
        // не кастится vt
        Accept(Constant);
        return our->value->vt;
    }
    else if(token->ToString()=="("){
        Accept(from_str_to_operator["("]);
        auto ans = Expression();
        Accept(from_str_to_operator[")"]);
        return ans;
    }
    else{
        Accept(from_str_to_operator["not"]);
        auto go = Expression();
        if (!can_cast(go, BoolType)) {
			std::string error_text = "Выражение должно иметь тип Bool";
			handler->add_error(error_text, last_pos_of_op[from_str_to_operator["not"]]);
		}
        return BoolType;
    }
}

void CCompilier::ComplicatedOperatorBlock(){
    if(token->ToString()=="begin"){
        CompositeOperatorBlock();
    }
    else{ // if block
        ConditionalOperatorBlock();
    }
}

void CCompilier::ConditionalOperatorBlock(){
    Accept(IfKW);
    Expression();
    Accept(ThenKW);
    OperatorBlock();
    if(token->ToString()=="else"){
        Accept(ElseKW);
        OperatorBlock();
    }
}

int main(){
    auto compilier = std::make_unique<CCompilier>("/home/pna/Documents/study/pascal_compiler/input.txt", "/home/pna/Documents/study/pascal_compiler/output.txt");
    compilier->Run();
}