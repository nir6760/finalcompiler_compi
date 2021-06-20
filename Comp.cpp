#include "Comp.hpp"
#include <iostream>
//constractor
Comp::Comp(SymbolTable& t) :buffer(CodeBuffer::instance()), table(t){

    buffer.emitGlobal("declare i32 @printf(i8*, ...)");
    buffer.emitGlobal("declare void @exit(i32)");
    buffer.emitGlobal("@.int_specifier = constant [4 x i8] c\"%d\\0A\\00\"");
    buffer.emitGlobal("@.str_specifier = constant [4 x i8] c\"%s\\0A\\00\"");
    buffer.emitGlobal("@.div_zero_str = private unnamed_addr constant [23 x i8] c\"Error division by zero\\00\", align 1");
    buffer.emit("define void @printi(i32) {\n"
                "  %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0\n"
                "  call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)\n"
                "  ret void\n"
                "}");

    buffer.emit("define void @print(i8*) {\n"
                "  %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0\n"
                "  call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)\n"
                "  ret void\n"
                "}");
}

//return the right lllvm type
string Comp::getTypeString(const string& type) {
    if (type == "INT") return "i32";
    if (type == "BYTE") return "i32";
    if (type == "BOOL") return  "i32";
    if (type == "STRING") return  "i8*";
    return "void";
}

//declare var at llvm, need to be with symbol table on stack
cut_type* Comp::handle_decl(cut_type*&  sym_type,string& id, cut_type* assign_to){
    auto property2 = new cut_type();
    //string label = buffer.genLabel();
    if (nullptr != assign_to && assign_to->str != "BOOL"){
        //property2->label = assign_to->label;
        //buffer.bpatch(assign_to->next_list, label);
    } else {
        //property2->label = label;
    }

    auto reg = getNextReg();
    string func_stack_reg = table.this_func->reg_stack_local_var;
    int param_offset = table.getParamOffset(id);
    string address_str = reg + " = getelementptr i32, i32* " + func_stack_reg + ", " + getTypeString(sym_type->str) + " " + to_string(param_offset);
    buffer.emit(address_str);
    string store_str = "store " + getTypeString(sym_type->str) + " 0, i32* " + reg;
    buffer.emit(store_str);

    table.setPlace(id, reg, 1); //needs to check if it is in %x or in stack, this reg has the address for the variable in memory stack
    // %ptr = alloca i32
    // store i32 3, i32* %ptr
    string place;
    cut_type default_property;
    if (assign_to == nullptr) {
        default_property.str = sym_type->str;
        default_property.place = "0"; //default for bool 
        assign_to = &default_property;
        place = "0";
    }
    else {
        place = assign_to->place;
        // if (assign_to->str == "BOOL"){
        //     place = handleBoolToReg(assign_to);
        // }
            
    }

    // string store_str = "store " + getTypeString(sym_type->str) + " " + place + ", " +  getTypeString(sym_type->str) + "* " + reg;
    // buffer.emit(store_str);
    
    //auto row_num = buffer.emit("br label @");
    //property2->next_list.emplace_back(row_num, FIRST);
    return property2;
}
//emit allocate 50 i32 for local variables at function begining
void Comp::allocateStack(string reg){
    string size_reg = getNextReg();
    buffer.emit(size_reg + " = add i32 50, 0");
    buffer.emit(reg + " = alloca i32, i32 " + size_reg);
}

// declare function at llvm
cut_type * Comp::handle_func(const string& type, const string& id,
     const vector<string>& params_type, const vector<string>& params_names ){
         //function define
    string res = "define ";
    res += getTypeString(type) + " @" + id + "(";
    for (auto param_type : params_type) {
        //res += getTypeString(std::get<0>(param)) + " " + std::get<2>(param) + ", ";
        res += getTypeString(param_type) + ", ";
    }
    if (!params_type.empty()) {
        res.erase(res.size() - 1);
        res.erase(res.size() - 1);
    }
    res += ") {";

    buffer.emit(res);
    string allocate_stack_reg = getNextReg();
    allocateStack(allocate_stack_reg); //allocate 50 i32 on stack for local variables
    table.this_func->reg_stack_local_var = allocate_stack_reg;


    // connect %x to currect param
    int i = 0;
    for (auto param_name : params_names) {

        table.setPlace(param_name, "%"+ to_string(i), 0);
       
    }

    auto property = new cut_type();
    //auto loc = buffer.emit("br label @");
    //property->next_list.emplace_back(loc, FIRST);
    return property;
 }
//generate register name by counting
string Comp::getNextReg() {
    return string("%reg_") + to_string(count_regs++);
}


void Comp::end_func(){
    buffer.emit("}");
}

void Comp::handle_funcBP(cut_type* func, cut_type* statement){
    buffer.bpatch(func->next_list, statement->label);
}

//handle Statments rule
cut_type* Comp::handle_one_statment(cut_type* statement) {
    auto property = new cut_type();
    property->label=statement->label;
    string label = buffer.genLabel();

    buffer.bpatch(statement->next_list, label);
    property->next_list = statement->next_list;
    return property;
}

cut_type* Comp::handle_statments(cut_type* statements, cut_type* statement) {
    auto property = new cut_type();
    // property->label = statements->label;

    // buffer.bpatch(statements->next_list, statement->label);
    property->next_list = statement->next_list;
    return property;
}