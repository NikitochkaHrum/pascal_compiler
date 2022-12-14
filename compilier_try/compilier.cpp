#include "pch.h"
#include "compilier.h"

CCompilier::CCompilier(const char* In, const char* Out) {
    lexer = new CLexer(In, Out);
    handler = new ErrorHandler();
}
 
void CCompilier::Run() {
    auto go = lexer->GetNextToken();
    token = go;

    String^ AsName = "PascalProgram";
    String^ ExeName = "PascalProgram.exe";
    String^ TypeName = "PascalProgram";
    String^ MethodName = "Main";

    // ID сборки
    AssemblyName^ Name = gcnew AssemblyName(AsName);

    // Домен приложения
    AppDomain^ Domain = Threading::Thread::GetDomain();

    // Динамическая сборка
    AssemblyBuilder^ Builder = Domain->DefineDynamicAssembly(Name, AssemblyBuilderAccess::RunAndSave);

    // Модуль в динамической сборке
    ModuleBuilder^ ModuleB = Builder->DefineDynamicModule(ExeName, true);

    // Создание экземпляров классов во время исполнения
    TypeBuilder^ TypeB = ModuleB->DefineType(TypeName, TypeAttributes::Public);

    // Определение метода для динамического класса
    MethodBuilder^ MethodB = TypeB->DefineMethod(
        MethodName, MethodAttributes::Static | MethodAttributes::Public,
        void::typeid, gcnew cli::array<Type^>{});
    
    Gen = MethodB->GetILGenerator();
    
    try {
        ProgramBlock();
    }
    catch (CTokenExpectedException& exc) {
        std::cout << exc.what() << "\n\n";
        return;
    }
    if (handler->get_errors_count() > 0) {
        lexer->InOut->print_semantic_errors(*handler);
        return;
    }
    // чтобы консоль не сразу закрывалась
    Gen->EmitWriteLine(convert_to_mstr("Press any button..."));
    auto readln_method = Console::typeid->GetMethod("ReadLine", gcnew cli::array<Type^>{});
    Gen->Emit(OpCodes::Call, readln_method);
    auto lb = Gen->DeclareLocal(String::typeid);
    Gen->Emit(OpCodes::Stloc, lb);
    // 

    Gen->Emit(OpCodes::Ret);

    Builder->SetEntryPoint(MethodB);

    Type^ MyClass = TypeB->CreateType();

    //Сохраняем в exe
    Builder->Save(ExeName);
}

void CCompilier::emit_op(OperatorType op) {
    switch (op) {
        case OType1:  Gen->Emit(OpCodes::Add); break;   // +
        case OType2:  Gen->Emit(OpCodes::Sub); break;   // -
        case OType3:  Gen->Emit(OpCodes::Mul); break;   // *
        case OType4:  Gen->Emit(OpCodes::Div); break;   // /
        case OType5:  Gen->Emit(OpCodes::Rem); break;   // mod
        case OType6:  Gen->Emit(OpCodes::Div); break;   // div
        case OType7:  Gen->Emit(OpCodes::Ceq); break;   // =
        case OType16: Gen->Emit(OpCodes::Clt); break;   // <
        case OType17: Gen->Emit(OpCodes::Cgt); break;   // >
        case OType20: Gen->Emit(OpCodes::Or);  break;   // or
        case OType21: Gen->Emit(OpCodes::And); break;   // and
        case OType22: Gen->Emit(OpCodes::Not); break;   // not
        case OType15: {                                 // <>
            Gen->Emit(OpCodes::Ceq);
            Gen->Emit(OpCodes::Ldc_I4_0);
            Gen->Emit(OpCodes::Ceq);
        }                                               // <=
        case OType18: {
            Gen->Emit(OpCodes::Cgt);
            Gen->Emit(OpCodes::Ldc_I4_0);
            Gen->Emit(OpCodes::Ceq);
        }
        case OType19: {                                 // >=
            Gen->Emit(OpCodes::Clt);
            Gen->Emit(OpCodes::Ldc_I4_0);
            Gen->Emit(OpCodes::Ceq);
        }
    }
}

String^ CCompilier::convert_to_mstr(std::string s) {
    return marshal_as<String^>(s);
}

Type^ CCompilier::GetType(VarType v) {
    if (v == IntegerType)
        return int::typeid;
    if (v == FloatType)
        return double::typeid;
    if (v == StringType)
        return std::string::typeid;
    return bool::typeid;
}

VarType CCompilier::GetType(Type^ v) {
    if (v == int::typeid)
        return IntegerType;
    if (v == double::typeid)
        return FloatType;
    if (v == std::string::typeid)
        return StringType;
    return BoolType;
}

CToken* CCompilier::GetNextToken() {
    auto go = lexer->GetNextToken();
    return go;
}

void CCompilier::ChangeSign(System::Type^ type) {
    if (type == int::typeid) {
        Gen->Emit(OpCodes::Ldc_I4, -1);
        Gen->Emit(OpCodes::Mul);
    }
    else if (type == double::typeid) {
        Gen->Emit(OpCodes::Ldc_R8, -1);
        Gen->Emit(OpCodes::Mul);
    }
}

void CCompilier::LoadValue(CToken* t) {
    if (t->tt != Constant) {
        return;
    }
    auto our = static_cast<CConstToken*>(token);
    if (our->value->vt == IntegerType) {
        Gen->Emit(OpCodes::Ldc_I4, std::stoi(our->ToString()));
    }
    else if (our->value->vt == FloatType) {
        Gen->Emit(OpCodes::Ldc_R8, std::stod(our->ToString()));
    }
    else if (our->value->vt == StringType) {
        Gen->Emit(OpCodes::Ldstr, convert_to_mstr(our->ToString()));
    }
    else if (our->value->vt == BoolType) {
        Gen->Emit(OpCodes::Ldc_I4, our->ToString() == "true");
    }
}

void CCompilier::DoWriteLn(Type^ t) {
    auto writeln_method = Console::typeid->GetMethod("WriteLine", gcnew cli::array<Type^>{t});
    Gen->Emit(OpCodes::Call, writeln_method);
}

void CCompilier::DoReadLn(CToken* tk) {
    String^ val = convert_to_mstr(tk->ToString());
    Type^ type = vars[val];
    LocalBuilder^ lb = vars_lb[val];

    MethodInfo^ readln_method = Console::typeid->GetMethod("ReadLine", gcnew cli::array<Type^>{});
    Gen->Emit(OpCodes::Call, readln_method);

    MethodInfo^ convert_method = nullptr;

    if (type == int::typeid)
    {
        convert_method = Convert::typeid->GetMethod("ToInt32", gcnew cli::array<Type^>{std::string::typeid});
    }
    else if (type == double::typeid)
    {
        convert_method = Convert::typeid->GetMethod("ToDouble", gcnew cli::array<Type^>{std::string::typeid});
    }
    else if (type == bool::typeid)
    {
        convert_method = Convert::typeid->GetMethod("ToBoolean", gcnew cli::array<Type^>{std::string::typeid});
    }

    if (convert_method != nullptr)
        Gen->Emit(OpCodes::Call, convert_method);
    Gen->Emit(OpCodes::Stloc, lb);
}

void CCompilier::Accept(TokenTp expected_token_type) {
    if (token->tt != expected_token_type)
        throw CTokenExpectedException(expected_token_type, token->pos);
    /*if (expected_token_type == Operator) {
        last_op = from_str_to_operator[token->ToString()];
        (*last_pos_of_op)[last_op] = token->pos;
    }*/
    token = GetNextToken();
}

void CCompilier::Accept(OperatorType expected_operator) {
    if (token->tt != Operator)
        throw CTokenExpectedException(Operator, token->pos);;
    auto our = static_cast<COperatorToken*>(token);
    if (our->value != expected_operator)
        throw CTokenExpectedException(Operator, token->pos);
   /* last_op = expected_operator;
    (*last_pos_of_op)[expected_operator] = token->pos;*/
    token = GetNextToken();
}

void CCompilier::Accept(KeyWordType expected_keyword) {
    if (token->tt != KeyWord)
        throw CTokenExpectedException(KeyWord, token->pos);;
    auto our = static_cast<CKeyWordToken*>(token);
    if (our->value != expected_keyword)
        throw CTokenExpectedException(KeyWord, token->pos);
    token = GetNextToken();
}

void CCompilier::Accept(VarType expected_var_type) {
    if (token->tt != Constant)
        throw CTokenExpectedException(Constant, token->pos);;
    auto our = static_cast<CConstToken*>(token);
    if (our->value->vt != expected_var_type)
        throw CTokenExpectedException(Constant, token->pos);
    token = GetNextToken();
}

void CCompilier::Add_var(std::string& name, VarType type)
{
    if (!vars.ContainsKey(convert_to_mstr(name)))
        vars[convert_to_mstr(name)] = GetType(type);
    else {
        std::string msg = "Переменная с именем `" + name + "` уже была объявлена";
        handler->add_error(msg, token->pos);
    }
    vars_lb[convert_to_mstr(name)] = Gen->DeclareLocal(GetType(type));
}

VarType CCompilier::Derive(VarType left, VarType right, OperatorType op, TextPos pos_for_error) {
    VarType res = DefaultType;
    if (can_cast(left, right))
        res = right;

    if (can_cast(right, left))
        res = left;

    if (res == StringType) {
        // только +, =, <>
        if (op != from_str_to_operator["+"] && op != from_str_to_operator["="] && op != from_str_to_operator["<>"]) {
            std::string error_text = "Данную операцию нельзя применить к этим операндам";
            handler->add_error(error_text, pos_for_error);
        }
    }
    // операции сравнения
    if (op == from_str_to_operator["="]  || op == from_str_to_operator["<>"] || op == from_str_to_operator[">="] ||
        op == from_str_to_operator["<="] || op == from_str_to_operator[">"]  || op == from_str_to_operator["<"]  ||
        op == from_str_to_operator["or"] || op == from_str_to_operator["and"])
        return BoolType;
    return res;
}

void CCompilier::ProgramBlock() {
    Accept(ProgramKW);
    Accept(Identifier);
    Accept(from_str_to_operator[";"]);
    MainBlock();
    Accept(from_str_to_operator["."]);
}

void CCompilier::MainBlock() {
                                    //TODO раздел меток
// if(token->ToString() == from_kw_to_str[ConstKW])
    // ConstBlock();                //Раздел констант
                                 //TODO Раздел типов
    if (token->ToString() == from_kw_to_str[VarKW])
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

void CCompilier::VarBlock() {
    Accept(VarKW);

    SimilarVars(); //Раздел однотипных переменных
    Accept(from_str_to_operator[";"]);

    while (token->tt == Identifier) {
        SimilarVars();
        Accept(from_str_to_operator[";"]);
    }
}

void CCompilier::SimilarVars() {
    std::vector<std::string> vs;
    vs.push_back(token->ToString());
    Accept(Identifier);

    while (token->ToString() == ",") {
        Accept(from_str_to_operator[","]);
        vs.push_back(token->ToString());
        Accept(Identifier);
    }
    Accept(from_str_to_operator[":"]);
    if (token->tt != KeyWord) {
        Accept(KeyWord);
        return;
    }
    auto our = static_cast<CKeyWordToken*>(token);
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
    for (auto v : vs) {
        Add_var(v, my_type);
    }
}

void CCompilier::CompositeOperatorBlock() {
    Accept(BeginKW);
    OperatorBlock();
    Accept(from_str_to_operator[";"]);

    while (token->tt == Identifier || token->ToString() == "begin"
        || token->ToString() == "if" || token->ToString() == "while"
        || token->ToString() == "writeln" || token->ToString() == "readln") {
        OperatorBlock();
        Accept(from_str_to_operator[";"]);
    }
    Accept(EndKW);
}

void CCompilier::OperatorBlock() {
    if (token->tt == Identifier)
        SimpleOperatorBlock();
    else if (token->ToString() == "begin" || token->ToString() == "if" ||
        token->ToString() == "while" || token->ToString() == "writeln" ||
        token->ToString() == "readln")
        ComplicatedOperatorBlock();
}

void CCompilier::SimpleOperatorBlock() {
    AssignOperatorBlock();
}

void CCompilier::AssignOperatorBlock() {
    TextPos ident_pos = token->pos;
    std::string ident = token->ToString();
    Accept(Identifier);
    TextPos op_pos = token->pos;
    Accept(from_str_to_operator[":="]);
    VarType expr_type = Expression();
    if (!vars.ContainsKey(convert_to_mstr(ident))) {
        std::string error_text = "Переменная не была объявлена";
        handler->add_error(error_text, ident_pos);
    }
    else if (!can_cast(expr_type, GetType(vars[convert_to_mstr(ident)]))) {
        std::string error_text = "Вычисленное выражение и переменная имеют разные типы";
        handler->add_error(error_text, op_pos);
    }
    else
        Gen->Emit(OpCodes::Stloc, vars_lb[convert_to_mstr(ident)]);
}

VarType CCompilier::Expression() {
    VarType t1 = SimpleExpression(), t2;
    auto s = token->ToString();
    if (s == "=" || s == "<>" || s == "<" || s == "<=" || s == ">=" || s == ">") {
        OperatorType cur_op = from_str_to_operator[s];
        TextPos op_pos = token->pos;
        Accept(cur_op);
        t2 = SimpleExpression();
        t1 = Derive(t1, t2, cur_op, op_pos);
        s = token->ToString();
        emit_op(cur_op);
    }
    return t1;
}

VarType CCompilier::SimpleExpression() {
    /*if (token->ToString() == "+" || token->ToString() == "-") {
        Accept(from_str_to_operator[token->ToString()]);
    }*/
    VarType t1 = Term(), t2;
    auto s = token->ToString();
    while (s == "+" || s == "-" || s == "or") {
        OperatorType cur_op = from_str_to_operator[s];
        TextPos op_pos = token->pos;
        Accept(cur_op);
        t2 = Term();
        t1 = Derive(t1, t2, cur_op, op_pos);
        s = token->ToString();
        emit_op(cur_op);
    }
    return t1;
}

VarType CCompilier::Term() {
    VarType t1 = Multiplier(), t2;
    auto s = token->ToString();
    while (s == "div" || s == "mod" || s == "and" || token->ToString() == "*" || token->ToString() == "/") {
        OperatorType cur_op = from_str_to_operator[s];
        TextPos op_pos = token->pos;
        Accept(cur_op);
        t2 = Multiplier();
        t1 = Derive(t1, t2, cur_op, op_pos);
        s = token->ToString();
        emit_op(cur_op);
    }
    return t1;
}

VarType CCompilier::Multiplier() {
    OperatorType mem_op = from_str_to_operator["+"];
    if (token->ToString() == "+" || token->ToString() == "-") {
        mem_op = from_str_to_operator[token->ToString()];
        Accept(from_str_to_operator[token->ToString()]);
    }
    std::string ident = token->ToString();
    TextPos mem_pos = token->pos;
    if (token->tt == Identifier) {
        Accept(Identifier);
        if (!vars.ContainsKey(convert_to_mstr(ident))) {
            std::string error_text = "Переменная не была объявлена";
            handler->add_error(error_text, mem_pos);
            return DefaultType;
        }
        else {
            Gen->Emit(OpCodes::Ldloc, vars_lb[convert_to_mstr(ident)]);
            if (mem_op == from_str_to_operator["-"]) {
                ChangeSign(vars[convert_to_mstr(ident)]);
            }
        }
        return GetType(vars[convert_to_mstr(ident)]);
    }
    else if (token->tt == Constant) {
        auto our = static_cast<CConstToken*>(token);
        auto res = our->value->vt;
        LoadValue(token);
        Accept(Constant);
        if (mem_op == from_str_to_operator["-"])
            ChangeSign(GetType(res));
        return res;
    }
    else if (token->ToString() == "(") {
        Accept(from_str_to_operator["("]);
        auto ans = Expression();
        Accept(from_str_to_operator[")"]);
        if (mem_op == from_str_to_operator["-"])
            ChangeSign(GetType(ans));
        return ans;
    }
    else {
        TextPos op_pos = token->pos;
        Accept(from_str_to_operator["not"]);
        auto go = Expression();
        if (!can_cast(go, BoolType)) {
            std::string error_text = "Выражение должно иметь тип Bool";
            handler->add_error(error_text, op_pos);
        }
        emit_op(from_str_to_operator["not"]);
        return BoolType;
    }
}

void CCompilier::ComplicatedOperatorBlock() {
    if (token->ToString() == "begin") {
        CompositeOperatorBlock();
    }
    else if (token->ToString() == "if") { // if block
        ConditionalOperatorBlock();
    }
    else if(token->ToString() == "while"){ // while block
        WhileBlock();
    }
    else if (token->ToString() == "writeln") { //writeln block
        WriteLnBlock();
    }
    else if(token->ToString() == "readln"){ //readln block
        ReadLnBlock();
    }
}

void CCompilier::ConditionalOperatorBlock() {
    Accept(IfKW);
    auto then_ptr = Gen->DefineLabel();
    auto after_ptr = Gen->DefineLabel();
    VarType t = Expression();
    Gen->Emit(OpCodes::Brfalse, then_ptr);
    Accept(ThenKW);
    OperatorBlock();
    Gen->Emit(OpCodes::Br, after_ptr);
    Gen->MarkLabel(then_ptr);
    if (token->ToString() == "else") {
        Accept(ElseKW);
        OperatorBlock();
    }
    Gen->MarkLabel(after_ptr);
}

void CCompilier::WhileBlock() {
    Accept(WhileKW);
    auto cond_ptr = Gen->DefineLabel();
    auto after_ptr = Gen->DefineLabel();
    Gen->MarkLabel(cond_ptr);
    VarType t = Expression();
    Gen->Emit(OpCodes::Brfalse, after_ptr);
    Accept(DoKW);
    OperatorBlock();
    Gen->Emit(OpCodes::Br, cond_ptr);
    Gen->MarkLabel(after_ptr);
}

void CCompilier::WriteLnBlock() {
    Accept(WritelnKW);
    Accept(from_str_to_operator["("]);
    VarType t = Expression();
    Accept(from_str_to_operator[")"]);
    DoWriteLn(GetType(t));
}

void CCompilier::ReadLnBlock() {
    Accept(ReadlnKW);
    Accept(from_str_to_operator["("]);
    CToken* tk = token;
    Accept(Identifier);
    Accept(from_str_to_operator[")"]);
    DoReadLn(tk);
}