#include "Comp.hpp"
#include <iostream>
#include <algorithm>
#include <utility>  
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

//returns the right lllvm type
string Comp::llvm_type(const string& type) {
    if (type == "INT" || type == "BYTE" || type == "BOOL"){
        return "i32";
    } 
    if( type == "STRING")
        return "i8*";
    return "void";
}

// prepare jump to next
void  Comp::closingExp(cut_type* property){
    
    int next_br = buffer.emit("br label @");
    property->next_list.push_back(make_pair(next_br, FIRST));
}

//declares var at llvm, need to be with symbol table on stack
cut_type* Comp::handle_decl(cut_type*&  sym_type,string& id, cut_type* assign_to){
    auto property2 = new cut_type(id);
    string label = buffer.genLabel();
    if (nullptr != assign_to && assign_to->str != "BOOL"){

        property2->label = assign_to->label;
        buffer.bpatch(assign_to->next_list, label); //nothing happen if it is bool
    } else {

        property2->label = label;
    }

    auto adress_reg = generete_reg() + "_adress_" + id;
    string func_stack_reg = table.this_func->reg_stack_local_var;
    int param_offset = table.getParamOffset(id);
    string address_str = adress_reg + " = getelementptr i32, i32* " + func_stack_reg + ", " + llvm_type(sym_type->str) + " " + to_string(param_offset);
    buffer.emit(address_str);

    if (assign_to != nullptr) {
        string place_to_take_val_from = assign_to->place;
        if(assign_to->str == "BOOL") // if it is a bool, i must go to him with true/false list
            place_to_take_val_from = reg_bool_after_choice(assign_to);
        
        buffer.emit("store " + llvm_type(assign_to->str) + " " + place_to_take_val_from + ", " +  llvm_type(assign_to->str) + "* " + adress_reg);
        table.setPlace(id, adress_reg, 1);
    }
    else{
        buffer.emit("store " + llvm_type(sym_type->str) + " 0, i32* " + adress_reg);

        table.setPlace(id, adress_reg, 1); //needs to check if it is in %x or in stack, this reg has the address for the variable in memory stack

        
    }


    closingExp(property2);
    return property2;
}
//emit allocate 50 i32 for local variables at function begining
void Comp::allocateStack(string reg){
    string size_reg = generete_reg();
    buffer.emit(size_reg + " = add i32 50, 0");
    buffer.emit(reg + " = alloca i32, i32 " + size_reg);
}

// declares function at llvm
cut_type * Comp::handle_func(const string& type, const string& id,
     const vector<string>& params_type, const vector<string>& params_names ){
         //function define
    string res = "define ";
    res += llvm_type(type) + " @" + id + "(";
    for (auto param_type : params_type) {
        //res += llvm_type(std::get<0>(param)) + " " + std::get<2>(param) + ", ";
        res += llvm_type(param_type) + ", ";
    }
    if (!params_type.empty()) {
        res.erase(res.size() - 1);
        res.erase(res.size() - 1);
    }
    res += ") {";

    buffer.emit(res);
    string allocate_stack_reg = generete_reg() + "_currStackAdd";
    allocateStack(allocate_stack_reg); //allocate 50 i32 on stack for local variables
    table.this_func->reg_stack_local_var = allocate_stack_reg;


    // connect %x to currect param
    int i = 0;
    for (auto param_name : params_names) {

        table.setPlace(param_name, "%"+ to_string(i), 0);
        i++;
       
    }

    auto property = new cut_type();
    
    closingExp(property);
    return property;
 }
//generate register name by counting
string Comp::generete_reg() {
    return string("%reg_") + to_string(count_regs++);
}

//handles the end of function
void Comp::end_func(cut_type* this_func,cut_type* statem){

    if(!table.this_func->is_ret){ 
        string label = buffer.genLabel();
        buffer.bpatch(statem->next_list, label); //the last statment didnt have where to go

        if(table.this_func->type == "VOID")
            buffer.emit("ret void"); //there is no return in some return function
        else
             buffer.emit("ret i32 0"); //there is no return in some return function

    }
    buffer.bpatch(this_func->next_list, statem->label);
    buffer.emit("}");
}

void Comp::handle_funcBP(cut_type* func, cut_type* statement){
    buffer.bpatch(func->next_list, statement->label);
}

//handles Statments rule
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

    property->label = statements->label;
    buffer.bpatch(statements->next_list, statement->label);
    
    property->next_list = statement->next_list;
    return property;
}

// check division by zero
void Comp::checkZeroDiv(const string& r){
    vector<pair<int,BranchLabelIndex>> next_list;

    string cmp_reg = generete_reg();
    buffer.emit(cmp_reg + " = icmp eq i32 0, " + r);
    auto loc = buffer.emit("br i1 " + cmp_reg + ", label @, label @");
    auto zero_label = buffer.genLabel();
    auto div_str_reg = generete_reg();
    buffer.emit(div_str_reg + " = " + "getelementptr inbounds [23 x i8], [23 x i8]* @.div_zero_str, i64 0, i64 0");
    buffer.emit("call void @print(i8* " + div_str_reg + ")");
    buffer.emit("call void @exit(i32 0)");

    int usless_br = buffer.emit("br label @");

    auto not_zero = buffer.genLabel();

    buffer.bpatch(CodeBuffer::makelist({loc, FIRST}), zero_label);
    buffer.bpatch(CodeBuffer::makelist({loc, SECOND}), not_zero);
    buffer.bpatch(CodeBuffer::makelist({usless_br, FIRST}), not_zero);
}

cut_type* Comp::expBin(cut_type& r1, const string& op, cut_type& r2){
    auto property = new cut_type();
    property->label = r1.label;

    auto my_label = buffer.genLabel();
    
    if (property->label.empty()){
        property->label = my_label;
    } 
    buffer.bpatch(r1.next_list, r2.label);
    buffer.bpatch(r2.next_list, my_label);


    if (op == "sdiv"){
        checkZeroDiv(r2.place);
    }

    property->str = "BYTE";
    if (r1.str == "INT" || r2.str == "INT"){
        property->str = "INT";
    }


    string place_r1 = r1.place;
    string place_r2 = r2.place;
    property->place = generete_reg();
    buffer.emit(property->place + " = " + op + " i32 " + place_r1 + ", " + place_r2);

    if(property->str == "BYTE") {
        i32_to_byte(*property);
        
    }

    
    closingExp(property);

    return property;
}
// convert i32 to i8 (int to byte)
void Comp::i32_to_byte(cut_type& from){
    string trunc = generete_reg();
    string after_zext = generete_reg();
    buffer.emit(trunc + " = trunc i32 "+ from.place + " to i8");
    buffer.emit(after_zext + " = zext i8 "+ trunc + " to i32");
    from.place = after_zext;

}




// convert i32 to i1 (int to bool)
void Comp::i32_to_i1(cut_type& from){
    string trunc = generete_reg();
    string after_zext = generete_reg();
    buffer.emit(trunc + " = trunc i32 "+ from.place + " to i8");
    buffer.emit(after_zext + " = zext i8 "+ trunc + " to i32");
    from.place = after_zext;

}

//handles symbols
cut_type* Comp::handle_id(cut_type* id) {
    //todo: if its a param 
    
    auto property = new cut_type();
    property->label = buffer.genLabel();
    
    property->str = table.getVarType(id->str);
    
    int offset = table.getParamOffset(id->str);

    int how_it_saved;
    string reg_place = table.getParamAddPlace(id->str , how_it_saved);

    string new_reg;
    if(how_it_saved == 1) // it is on stack
    {   
        new_reg = generete_reg() + "_loadID_"+id->str;
        buffer.emit(new_reg + " = load " + llvm_type(property->str) + ", " + llvm_type(property->str) + "* " +reg_place);
    }
    else // it is on some register
        new_reg = reg_place;

    string id_type = table.getVarType(id->str);
    if (id_type == "BOOL") {
        string cmp_reg = generete_reg() + "_bool";
        buffer.emit(cmp_reg + " = trunc i32 "+ new_reg + " to i1");
        int row_num = buffer.emit("br i1 " + cmp_reg + ", label @, label @");
        property->true_list.push_back(make_pair(row_num, FIRST));
        property->false_list.push_back(make_pair(row_num, SECOND));
    }
    else {
        property->place = new_reg;
        closingExp(property);
    }
    return property;
}

//handles strings
cut_type *Comp::handle_str(string str) {

    auto property = new cut_type();
    property->str = "STRING";
    property->label = buffer.genLabel();
    string str_name = "@.str" + to_string(count_str++);

    str.erase(0, 1); // delet firt"
    str.erase(str.size() - 1); //delete last "
    int st_size= str.size() + 1;
    
    buffer.emitGlobal(str_name + " = private unnamed_addr constant [" + to_string(st_size) + " x i8] c\"" + str + "\\00\", align 1");

    property->place = generete_reg();
    //property->reg_save = 1;
    buffer.emit(property->place + " = " + "getelementptr inbounds [" +to_string(st_size) + " x i8], [" + to_string(st_size) + " x i8]* " + str_name + ", i64 0, i64 0");
    closingExp(property);
    
    return property;
}

//handles assigment without declaration command
cut_type *Comp::handle_ass(string &id, cut_type* property) {
    
    auto property2 = new cut_type();

    property2->label = property->label;
    buffer.bpatch(property->next_list, buffer.genLabel());
    string reg = table.getStype(id)->place;//place;
    
   

    string place = property->place;
    if (property->str == "BOOL"){
        place = reg_bool_after_choice(property);(property);
    }
   
    buffer.emit("store " + llvm_type(property->str) + " " + place + ", " +  llvm_type(property->str) + "* " + reg);

    closingExp(property2);

    return property2;
}

// handles call command
cut_type * Comp::handle_call(string & id, vector<cut_type*> curr_call_exps){
    auto property = new cut_type();
    
    reverse(curr_call_exps.begin(), curr_call_exps.end()); 

    property->label = buffer.genLabel();
    for (int i=0;i<curr_call_exps.size();i++)
    {
        if (curr_call_exps[i]->str == "BOOL") {
            curr_call_exps[i]->place = reg_bool_after_choice(curr_call_exps[i]);
        }
        else {
            buffer.emit("br label %" + curr_call_exps[i]->label);
            string label = buffer.genLabel();
            buffer.bpatch(curr_call_exps[i]->next_list, label);
        }
    }

    string ret_type = table.getFuncType(id);
    string who_to_call = "";
    if ("VOID" != ret_type) {
        string call_reg = generete_reg();
        property->place = call_reg;
        who_to_call += call_reg + " = ";
    }//buffer.emit("call void @print(i8* " + div_str_reg + ")");
    who_to_call += "call "+ llvm_type(ret_type) + " @" + id + " ( ";
    for (auto& param : curr_call_exps) {
        who_to_call += llvm_type(param->str) + " " +param->place + ", " ;
    }

    if (who_to_call.size() > 0 ) {//delete last ", "
        who_to_call.erase(who_to_call.size() - 1);
        who_to_call.erase(who_to_call.size() - 1);
    }

    who_to_call += " )";
    buffer.emit(who_to_call);

    if (ret_type == "BOOL") {
        auto temp_reg = generete_reg();
        buffer.emit(temp_reg + " = trunc i32 "+ property->place + " to i1");
        auto loc = buffer.emit("br i1 " + temp_reg + ", label @, label @");
        property->true_list.emplace_back(loc, FIRST);
        property->false_list.emplace_back(loc, SECOND);
    }else {
        closingExp(property);
    }

    property->str = ret_type;
    return property;
}
// handles the ret command
cut_type* Comp::handle_return(cut_type* ret){
    cut_type* new_ret = new cut_type();

    string label = buffer.genLabel();

    if (ret == nullptr){
    // it is a void function
        new_ret->label = label;
        buffer.emit("ret void");
    } 
    else{
        if(!table.this_func->is_ret){ 
            buffer.emit("ret i32 0"); //there is no return in some return function, 

        }
        else{
            new_ret->label = ret->label; // so block befor ret block will go to load ret  
            string place_of_ret = ret->place;
            if (ret->str == "BOOL"){
                place_of_ret = reg_bool_after_choice(ret);
            } 
            buffer.bpatch(ret->next_list, label); //bpatch from where ret loaded to ret block
            buffer.emit("ret " + llvm_type(ret->str) + " " + place_of_ret);   
        }
        
    }   

    return new_ret;
}

//implicit cast, byte to int
cut_type* Comp::handle_cast(cut_type* cast){
    // probably I dont need this function
    cut_type* after_cast = new cut_type();

    string label = buffer.genLabel();

    i32_to_byte(*cast);
    buffer.bpatch(cast->next_list, label); //bpatch from where ret loaded to ret block  

    return after_cast;
}
//handles bool type like true or false
cut_type* Comp::bool_val(int val) {
    cut_type* ret = new cut_type();
    ret->str = "BOOL"; 
    ret->label = buffer.genLabel();
    int loc = buffer.emit("br label @");
    if (val == 1){ //val is TRUE
        ret->true_list.push_back(make_pair(loc, FIRST));  //true_list
    } else {//FALSE
        ret->false_list.emplace_back(make_pair(loc, FIRST)); //false_list
    };

    return ret;
}

//make a register which have the value 
string Comp::reg_bool_after_choice(cut_type* booly) {
    buffer.emit("br label %" + booly->label); 
    string aftet_lists_reg = generete_reg();
    string true_label = buffer.genLabel();
    int back_path_for_true =  buffer.emit("br label @");
    string false_label = buffer.genLabel();
    int back_path_for_false =  buffer.emit("br label @");

    string after_choice_label = buffer.genLabel();
    buffer.emit(aftet_lists_reg + " = phi i32 [  1, %" + true_label + "], [  0, %" + false_label + "]");

    buffer.bpatch(booly->true_list, true_label);
    buffer.bpatch(booly->false_list, false_label);

    buffer.bpatch(buffer.makelist({back_path_for_true, FIRST}), after_choice_label);
    buffer.bpatch(buffer.makelist({back_path_for_false, FIRST}), after_choice_label);

    return aftet_lists_reg;
}

//handles not case
cut_type* Comp::handle_not(cut_type* exp) {
    cut_type* res = new cut_type();

    res->str = exp->str;
    res->place = exp->place;
    res->label = exp->label;

    res->true_list = exp->false_list;//switch true and false
    res->false_list = exp->true_list;
    res->next_list = exp->next_list;
    return res;
}
//handles or case
cut_type* Comp::handle_or(cut_type* exp1, cut_type* exp2) {
    cut_type* res = new cut_type();
    res->str = "BOOL";
    res->label = exp1->label; //start at exp1
    res->true_list = buffer.merge(exp1->true_list, exp2->true_list); //if exp1 or exp2 true than its ok
    
    buffer.bpatch(exp1->false_list, exp2->label); // if exp1 false than check exp2
    res->false_list = exp2->false_list;
    return res;
}
//handles and case
cut_type* Comp::handle_and(cut_type* exp1, cut_type* exp2) {
    cut_type* res = new cut_type();
    res->str = "BOOL";
    res->label = exp1->label;
    res->false_list = buffer.merge(exp1->false_list, exp2->false_list);//false is false
    buffer.bpatch(exp1->true_list, exp2->label);//needs 2 true
    res->true_list = exp2->true_list;
    return res;
}
//handles relop case
cut_type* Comp::handle_relop_equalop(cut_type* exp1,string op, cut_type* exp2) {
    string op_llvm = "";
    if (op == "==") 
        op_llvm = "eq";
    else if (op == "!=")
         op_llvm = "ne";
    else if (op == ">")
         op_llvm =  "sgt";
    else if (op == "<") 
        op_llvm =  "slt";
    else if (op == ">=")
         op_llvm =  "sge";
    else if (op == "<=") 
        op_llvm =  "sle";

    cut_type* res = new cut_type();

    res->str = "BOOL";
    res->label = exp1->label;
    string my_label = buffer.genLabel();
    buffer.bpatch(exp1->next_list, exp2->label);
    buffer.bpatch(exp2->next_list, my_label);

    string exp1_reg = exp1->place;
    string exp2_reg = exp2->place;
    string after_cmp = generete_reg();

    buffer.emit(after_cmp + " = icmp " + op_llvm + " i32 " + exp1_reg + ", " + exp2_reg);
    int row_num = buffer.emit("br i1 " + after_cmp + ", label @, label @");
    res->true_list.push_back(make_pair(row_num, FIRST));
    res->false_list.push_back(make_pair(row_num, SECOND));

    return res;
}
//handles if, without else
cut_type* Comp::handle_only_if(cut_type* exp, cut_type* statment) {
    cut_type* res = new cut_type();
    res->label = exp->label;

    buffer.bpatch(exp->true_list, statment->label);

    res->next_list = buffer.merge(statment->next_list, exp->false_list);
    
    return res;
}
//handles if else
cut_type* Comp::handle_if_else(cut_type* exp, cut_type* if_statem, cut_type* else_statem) {
    
    cut_type* res = new cut_type();
    res->label = exp->label;
    buffer.bpatch(exp->true_list, if_statem->label);

    res->next_list = buffer.merge(if_statem->next_list, else_statem->next_list);
    buffer.bpatch(exp->false_list, else_statem->label);


    return res;
}
//handles while
cut_type* Comp::handle_while(cut_type* exp, cut_type* statment, cut_type* curr_break_exp) {
    cut_type* res = new cut_type();
    res->label = exp->label;    //exp is first block

    if(curr_break_exp != nullptr)
        res->next_list = buffer.merge(curr_break_exp->next_list, exp->false_list);
    else
        res->next_list = buffer.merge(curr_break_exp->next_list, exp->false_list);

    buffer.bpatch(exp->true_list, statment->label);
    buffer.bpatch(statment->next_list, exp->label);

    return res;
}
//handles continue
cut_type* Comp::handle_continue(cut_type* exp) {
    cut_type* res = new cut_type();
    res->label = buffer.genLabel();
    
    buffer.emit("br label %" + exp->label); //jump back to the begining of this while

    return res;
}
//handles break
cut_type* Comp::handle_break(cut_type* exp) {
    
    cut_type* res = new cut_type();
    res->label = buffer.genLabel();
        //buffer.emit("************************");

    int row_num = buffer.emit("br label @" ); //skip this part

    res->next_list.push_back(make_pair(row_num, FIRST));

    return res;
}

//handles specific Case
cut_type* Comp::handle_casedeal(cut_type* num,cut_type* statem) {
    cut_type* res = new cut_type();
    res->label = statem->label;
    res->place = num->place;
    res->next_list = statem->next_list;
    return res;
}
//handles one Case from caselist
cut_type* Comp::handle_caselist_one(cut_type* this_case) {
    cut_type* res = new cut_type();
    res->cases_labels_vec.push_back(this_case->label);
    res->cases_places_vec.push_back(this_case->place);


    res->exist_default = this_case->exist_default;
    return res;
}
//handles caselist
cut_type* Comp::handle_caselist(cut_type* this_case, cut_type* caselist) {
    cut_type* res = new cut_type();
    res->cases_labels_vec = caselist->cases_labels_vec;
    res->cases_labels_vec.push_back(this_case->label);
    
    res->cases_places_vec = caselist->cases_places_vec;
    res->cases_places_vec.push_back(this_case->place);

    res->next_list = buffer.merge(caselist->next_list, this_case->next_list);

    res->exist_default = this_case->exist_default || caselist->exist_default;
    return res;
}

//handles default case
cut_type* Comp::handle_default_case(cut_type* def) {
    cut_type* res = new cut_type();
    
    //res->cases_labels_vec = def->cases_labels_vec;
    res->cases_labels_vec.push_back(def->label);
    
    //res->cases_places_vec = caselist->cases_places_vec;
    res->cases_places_vec.push_back(def->place);


    res->exist_default = true;
    return res;
}

//handles default case
cut_type* Comp::handle_switch(cut_type* exp, cut_type* caselist) {
    cut_type* res = new cut_type();
    string new_label =buffer.genLabel();
    res->label = new_label;
    
    buffer.bpatch(exp->next_list, new_label);
    
    int row_num;
    string new_case_label;
    int i =0;
    buffer.emit("*********************** here" );
    while(!caselist->cases_places_vec.empty()){
        
        if(i != 0){
            new_case_label =buffer.genLabel();
            buffer.bpatch(res->next_list, new_case_label);
        }
        
        
        string curr_val_place = caselist->cases_places_vec.back();
        caselist->cases_places_vec.pop_back();

        string curr_label_case = caselist->cases_labels_vec.back();
        caselist->cases_labels_vec.pop_back();


        if (caselist->exist_default && caselist->cases_places_vec.size() == 1){
            
            row_num = buffer.emit("br label %" + curr_label_case );
            break; 
        }

        string after_cmp = generete_reg() + "_case_" + to_string(i);
        buffer.emit(after_cmp + " = icmp eq i32 " + exp->place + ", " + curr_val_place);
        row_num = buffer.emit("br i1 " + after_cmp + ", label " + curr_label_case + ", label @");
       
        res->next_list.push_back(make_pair(row_num, SECOND));
        i++;

        
    }

    

    string end_label = buffer.genLabel();
    buffer.bpatch(res->next_list, end_label);
    row_num = buffer.emit("br label @" ); 
    res->next_list.push_back(make_pair(row_num, FIRST));
    res->next_list = buffer.merge(caselist->next_list, res->next_list);
    
    return res;
}
