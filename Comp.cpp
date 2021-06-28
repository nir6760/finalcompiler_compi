#include "Comp.hpp"
#include <iostream>
#include <algorithm>
#include <utility>  
//constractor
Comp::Comp(SymbolTable& t) :code_bp(CodeBuffer::instance()), sym_table(t){

    code_bp.emitGlobal("declare i32 @printf(i8*, ...)");
    code_bp.emitGlobal("declare void @exit(i32)");
    code_bp.emitGlobal("@.int_specifier = constant [4 x i8] c\"%d\\0A\\00\"");
    code_bp.emitGlobal("@.str_specifier = constant [4 x i8] c\"%s\\0A\\00\"");
    code_bp.emitGlobal("@.div_zero_str = private unnamed_addr constant [23 x i8] c\"Error division by zero\\00\", align 1");
    code_bp.emit("define void @printi(i32) {\n"
                "  %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0\n"
                "  call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)\n"
                "  ret void\n"
                "}");

    code_bp.emit("define void @print(i8*) {\n"
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
    
    int next_br = code_bp.emit("br label @");
    property->next_list.push_back(make_pair(next_br, FIRST));
}

//declares var at llvm, need to be with symbol sym_table on stack
cut_type* Comp::handle_decl(cut_type*&  sym_type,string& id, cut_type* assign_to){
    cut_type* res = new cut_type(id);
    string label = code_bp.genLabel();
    if (nullptr != assign_to && assign_to->str != "BOOL"){

        res->label = assign_to->label;
        code_bp.bpatch(assign_to->next_list, label); //nothing happen if it is bool
    } else {

        res->label = label;
    }

    auto adress_reg = generete_reg() + "_adress_" + id;
    string func_stack_reg = sym_table.this_func->reg_stack_local_var;
    int param_offset = sym_table.getParamOffset(id);
    string address_str = adress_reg + " = getelementptr i32, i32* " + func_stack_reg + ", " + llvm_type(sym_type->str) + " " + to_string(param_offset);
    code_bp.emit(address_str);

    if (assign_to != nullptr) {
        string place_to_take_val_from = assign_to->place;
        if(assign_to->str == "BOOL") // if it is a bool, i must go to him with true/false list
            place_to_take_val_from = reg_bool_after_choice(assign_to);
        
        code_bp.emit("store " + llvm_type(assign_to->str) + " " + place_to_take_val_from + ", " +  llvm_type(assign_to->str) + "* " + adress_reg);
        sym_table.setPlace(id, adress_reg, 1);
    }
    else{
        code_bp.emit("store " + llvm_type(sym_type->str) + " 0, i32* " + adress_reg);

        sym_table.setPlace(id, adress_reg, 1); //needs to check if it is in %x or in stack, this reg has the address for the variable in memory stack

        
    }


    closingExp(res);
    return res;
}
//emit allocate 50 i32 for local variables at function begining
void Comp::allocateStack(string reg){
    string size_reg = generete_reg();
    code_bp.emit(size_reg + " = add i32 50, 0");
    code_bp.emit(reg + " = alloca i32, i32 " + size_reg);
}

// declares function at llvm
cut_type * Comp::handle_func(const string& type, const string& id,
     const vector<string>& params_type, const vector<string>& params_names ){
         //function define
    string res_ins = "define ";
    res_ins += llvm_type(type) + " @" + id + "(";
    for (auto param_type : params_type) {
        res_ins += llvm_type(param_type) + ", ";
    }
    if (!params_type.empty()) {
        res_ins.erase(res_ins.size() - 1);
        res_ins.erase(res_ins.size() - 1);
    }
    res_ins += ") {";

    code_bp.emit(res_ins);
    string allocate_stack_reg = generete_reg() + "_currStackAdd";
    allocateStack(allocate_stack_reg); //allocate 50 i32 on stack for local variables
    sym_table.this_func->reg_stack_local_var = allocate_stack_reg;


    // connect %x to currect param
    int i = 0;
    for (auto param_name : params_names) {

        sym_table.setPlace(param_name, "%"+ to_string(i), 0);
        i++;
       
    }

    cut_type* res = new cut_type();
    
    closingExp(res);
    return res;
 }
//generate register name by counting
string Comp::generete_reg() {
    return string("%reg_") + to_string(count_regs++);
}

//handles the end of function
void Comp::end_func(cut_type* this_func,cut_type* statem){
    code_bp.bpatch(this_func->next_list, statem->label); //going in
    
    

    //if(!sym_table.this_func->is_ret){ 
    if(true){
        string label = code_bp.genLabel();
            //going out
        if(statem->str == "BOOL"){
            code_bp.bpatch(statem->true_list, label);
            code_bp.bpatch(statem->false_list, label);
        }else{
             

            code_bp.bpatch(statem->next_list, label); //the last statment didnt have where to go
        }
        

        if(sym_table.this_func->type == "VOID")
            code_bp.emit("ret void"); //there is no return in some return function
        else
             code_bp.emit("ret i32 0"); //there is no return in some return function

    }
    
    
    
    code_bp.emit("}");
}



//handles Statments rule
cut_type* Comp::handle_one_statment(cut_type* statement) {
    cut_type* res = new cut_type();
    res->label=statement->label;
    string label = code_bp.genLabel();

    code_bp.bpatch(statement->next_list, label);
    res->next_list = statement->next_list;

    res->true_list = statement->true_list;
    res->false_list = statement->false_list;
    res->str = statement->str;
    return res;
}

cut_type* Comp::handle_statments(cut_type* statements, cut_type* statement) {
    cut_type* res = new cut_type();

    res->label = statements->label;
     if(statements->str == "BOOL"){
            code_bp.bpatch(statements->true_list, statement->label);
            code_bp.bpatch(statements->false_list, statement->label);
        }else{
            code_bp.bpatch(statements->next_list, statement->label); //the last statment didnt have where to go
        }
    //code_bp.bpatch(statements->next_list, statement->label);
    
    res->next_list = statement->next_list;

    res->true_list = statement->true_list;
    res->false_list = statement->false_list;
    res->str = statement->str;

    return res;
}

// check division by zero
void Comp::check_div_by_zero(const string& r){
    vector<pair<int,BranchLabelIndex>> next_list;

    string cmp_reg = generete_reg();
    code_bp.emit(cmp_reg + " = icmp eq i32 0, " + r);
    auto loc = code_bp.emit("br i1 " + cmp_reg + ", label @, label @");
    auto zero_label = code_bp.genLabel();
    auto div_str_reg = generete_reg();
    code_bp.emit(div_str_reg + " = " + "getelementptr inbounds [23 x i8], [23 x i8]* @.div_zero_str, i64 0, i64 0");
    code_bp.emit("call void @print(i8* " + div_str_reg + ")");
    code_bp.emit("call void @exit(i32 0)");

    int no_land_br = code_bp.emit("br label @");

    string not_zero = code_bp.genLabel();

    code_bp.bpatch(code_bp.makelist({loc, FIRST}), zero_label);
    code_bp.bpatch(code_bp.makelist({loc, SECOND}), not_zero);
    code_bp.bpatch(code_bp.makelist({no_land_br, FIRST}), not_zero);
}
//return the result after binop action
cut_type* Comp::exp_binop(cut_type& r1, const string& op, cut_type& r2){
    cut_type* res = new cut_type();
    res->label = r1.label;

    string my_label = code_bp.genLabel();
    
    if (res->label.empty()){
        res->label = my_label;
    } 
    
    code_bp.bpatch(r1.next_list, r2.label);
    code_bp.bpatch(r2.next_list, my_label);


    if (op == "sdiv"){
        check_div_by_zero(r2.place);
    }

    res->str = "BYTE";
    if (r1.str == "INT" || r2.str == "INT"){
        res->str = "INT";
    }


    string place_r1 = r1.place;
    string place_r2 = r2.place;
    res->place = generete_reg();
    code_bp.emit(res->place + " = " + op + " i32 " + place_r1 + ", " + place_r2);

    if(res->str == "BYTE") {
        i32_to_byte(*res);
        
    }

    
    closingExp(res);

    return res;
}
// convert i32 to i8 (int to byte)
void Comp::i32_to_byte(cut_type& from){
    string trunc = generete_reg();
    string after_zext = generete_reg();
    code_bp.emit(trunc + " = trunc i32 "+ from.place + " to i8");
    code_bp.emit(after_zext + " = zext i8 "+ trunc + " to i32");
    from.place = after_zext;

}




// convert i32 to i1 (int to bool)
void Comp::i32_to_i1(cut_type& from){
    string trunc = generete_reg();
    string after_zext = generete_reg();
    code_bp.emit(trunc + " = trunc i32 "+ from.place + " to i8");
    code_bp.emit(after_zext + " = zext i8 "+ trunc + " to i32");
    from.place = after_zext;

}

//handles symbols
cut_type* Comp::handle_id(cut_type* id) {
    //todo: if its a param 
    
    cut_type*  res = new cut_type();
    res->label = code_bp.genLabel();
    
    res->str = sym_table.getVarType(id->str);
    
    int offset = sym_table.getParamOffset(id->str);

    int how_it_saved;
    string reg_place = sym_table.getParamAddPlace(id->str , how_it_saved);

    string new_reg;
    if(how_it_saved == 1) // it is on stack
    {   
        new_reg = generete_reg() + "_loadID_"+id->str;
        code_bp.emit(new_reg + " = load " + llvm_type(res->str) + ", " + llvm_type(res->str) + "* " +reg_place);
    }
    else // it is on some register
        new_reg = reg_place;

    string id_type = sym_table.getVarType(id->str);
    if (id_type == "BOOL") {
        string cmp_reg = generete_reg() + "_bool";
        code_bp.emit(cmp_reg + " = trunc i32 "+ new_reg + " to i1");
        int row_num = code_bp.emit("br i1 " + cmp_reg + ", label @, label @");
        res->true_list.push_back(make_pair(row_num, FIRST));
        res->false_list.push_back(make_pair(row_num, SECOND));
    }
    else {
        res->place = new_reg;
        closingExp(res);
    }
    return res;
}

//handles strings
cut_type *Comp::handle_str(string str) {

    cut_type* res = new cut_type();
    res->str = "STRING";
    res->label = code_bp.genLabel();
    string str_name = "@.str" + to_string(count_str++);

    str.erase(0, 1); // delet firt"
    str.erase(str.size() - 1); //delete last "
    int st_size= str.size() + 1;
    
    code_bp.emitGlobal(str_name + " = private unnamed_addr constant [" + to_string(st_size) + " x i8] c\"" + str + "\\00\", align 1");

    res->place = generete_reg();
    code_bp.emit(res->place + " = " + "getelementptr inbounds [" +to_string(st_size) + " x i8], [" + to_string(st_size) + " x i8]* " + str_name + ", i64 0, i64 0");
    closingExp(res);
    
    return res;
}

//handles assigment without declaration command
cut_type *Comp::handle_ass(string &id, cut_type* assign_to) {
    
    cut_type* res = new cut_type();

    res->label = assign_to->label;
    code_bp.bpatch(assign_to->next_list, code_bp.genLabel());
    string reg = sym_table.getStype(id)->place;//place;
    
   

    string place = assign_to->place;
    if (assign_to->str == "BOOL"){
        place = reg_bool_after_choice(assign_to);
    }
   
    code_bp.emit("store " + llvm_type(assign_to->str) + " " + place + ", " +  llvm_type(assign_to->str) + "* " + reg);

    closingExp(res);

    return res;
}

// handles call command
cut_type * Comp::handle_call(string & id, vector<cut_type*> curr_call_exps){
    cut_type* res = new cut_type();
    
    reverse(curr_call_exps.begin(), curr_call_exps.end()); 

    res->label = code_bp.genLabel();
    for (int i=0;i<curr_call_exps.size();i++)
    {
        if (curr_call_exps[i]->str == "BOOL") {
            curr_call_exps[i]->place = reg_bool_after_choice(curr_call_exps[i]);
        }
        else {
            code_bp.emit("br label %" + curr_call_exps[i]->label);
            string label = code_bp.genLabel();
            code_bp.bpatch(curr_call_exps[i]->next_list, label);
        }
    }

    string ret_type = sym_table.getFuncType(id);
    string who_to_call = "";
    if ("VOID" != ret_type) {
        string call_reg = generete_reg();
        res->place = call_reg;
        who_to_call += call_reg + " = ";
    }//code_bp.emit("call void @print(i8* " + div_str_reg + ")");
    who_to_call += "call "+ llvm_type(ret_type) + " @" + id + " ( ";
    for (auto& param : curr_call_exps) {
        who_to_call += llvm_type(param->str) + " " +param->place + ", " ;
    }

    if (who_to_call.size() > 0 && !curr_call_exps.empty()) {//delete last ", "
        who_to_call.erase(who_to_call.size() - 1);
        who_to_call.erase(who_to_call.size() - 1);
    }

    who_to_call += " )";
    code_bp.emit(who_to_call);

    if (ret_type == "BOOL") {
        auto temp_reg = generete_reg();
        code_bp.emit(temp_reg + " = trunc i32 "+ res->place + " to i1");
        int row_num = code_bp.emit("br i1 " + temp_reg + ", label @, label @");
        res->true_list.push_back(make_pair(row_num, FIRST));
        res->false_list.push_back(make_pair(row_num, SECOND));
    }else {
        closingExp(res);
    }

    res->str = ret_type;
    return res;
}
// handles the ret command
cut_type* Comp::handle_return(cut_type* ret){
    cut_type* new_ret = new cut_type();

    string label = code_bp.genLabel();

    if (ret == nullptr){
    // it is a void function
        new_ret->label = label;
        code_bp.emit("ret void");
    } 
    else{
        if(!sym_table.this_func->is_ret){ 
            code_bp.emit("ret i32 0"); //there is no return in some return function, 

        }
        else{
            new_ret->label = ret->label; // so block befor ret block will go to load ret  
            string place_of_ret = ret->place;
            if (ret->str == "BOOL"){
                place_of_ret = reg_bool_after_choice(ret);
            } 
            code_bp.bpatch(ret->next_list, label); //bpatch from where ret loaded to ret block
            code_bp.emit("ret " + llvm_type(ret->str) + " " + place_of_ret);   
        }
        
    }   

    return new_ret;
}

//implicit cast, byte to int
cut_type* Comp::handle_cast(cut_type* cast){
    // probably I dont need this function
    cut_type* after_cast = new cut_type();

    string label = code_bp.genLabel();

    i32_to_byte(*cast);
    code_bp.bpatch(cast->next_list, label); //bpatch from where ret loaded to ret block  

    return after_cast;
}
//handles bool type like true or false
cut_type* Comp::bool_val(int val) {
    cut_type* ret = new cut_type();
    ret->str = "BOOL"; 
    ret->label = code_bp.genLabel();
    int loc = code_bp.emit("br label @");
    if (val == 1){ //val is TRUE
        ret->true_list.push_back(make_pair(loc, FIRST));  //true_list
    } else {//FALSE
        ret->false_list.emplace_back(make_pair(loc, FIRST)); //false_list
    };

    return ret;
}

//make a register which have the value 
string Comp::reg_bool_after_choice(cut_type* booly) {
    code_bp.emit("br label %" + booly->label); 
    string aftet_lists_reg = generete_reg();
    string true_label = code_bp.genLabel();
    int back_path_for_true =  code_bp.emit("br label @");
    string false_label = code_bp.genLabel();
    int back_path_for_false =  code_bp.emit("br label @");

    string after_choice_label = code_bp.genLabel();
    code_bp.emit(aftet_lists_reg + " = phi i32 [  1, %" + true_label + "], [  0, %" + false_label + "]");

    code_bp.bpatch(booly->true_list, true_label);
    code_bp.bpatch(booly->false_list, false_label);

    code_bp.bpatch(code_bp.makelist({back_path_for_true, FIRST}), after_choice_label);
    code_bp.bpatch(code_bp.makelist({back_path_for_false, FIRST}), after_choice_label);

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
    res->true_list = code_bp.merge(exp1->true_list, exp2->true_list); //if exp1 or exp2 true than its ok
    
    code_bp.bpatch(exp1->false_list, exp2->label); // if exp1 false than check exp2
    res->false_list = exp2->false_list;
    return res;
}
//handles and case
cut_type* Comp::handle_and(cut_type* exp1, cut_type* exp2) {
    cut_type* res = new cut_type();
    res->str = "BOOL";
    res->label = exp1->label;
    res->false_list = code_bp.merge(exp1->false_list, exp2->false_list);//false is false
    code_bp.bpatch(exp1->true_list, exp2->label);//needs 2 true
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
    string my_label = code_bp.genLabel();
    code_bp.bpatch(exp1->next_list, exp2->label);
    code_bp.bpatch(exp2->next_list, my_label);

    string exp1_reg = exp1->place;
    string exp2_reg = exp2->place;
    string after_cmp = generete_reg();

    code_bp.emit(after_cmp + " = icmp " + op_llvm + " i32 " + exp1_reg + ", " + exp2_reg);
    int row_num = code_bp.emit("br i1 " + after_cmp + ", label @, label @");
    res->true_list.push_back(make_pair(row_num, FIRST));
    res->false_list.push_back(make_pair(row_num, SECOND));

    return res;
}
//handles if, without else
cut_type* Comp::handle_only_if(cut_type* exp, cut_type* statment) {
    cut_type* res = new cut_type();
    res->label = exp->label;

    code_bp.bpatch(exp->true_list, statment->label);

    res->next_list = code_bp.merge(statment->next_list, exp->false_list);
    
    return res;
}
//handles if else
cut_type* Comp::handle_if_else(cut_type* exp, cut_type* if_statem, cut_type* else_statem) {
    
    cut_type* res = new cut_type();
    res->label = exp->label;
    code_bp.bpatch(exp->true_list, if_statem->label);

    res->next_list = code_bp.merge(if_statem->next_list, else_statem->next_list);
    code_bp.bpatch(exp->false_list, else_statem->label);


    return res;
}
//handles while
cut_type* Comp::handle_while(cut_type* exp, cut_type* statment, cut_type* curr_break_exp) {
    cut_type* res = new cut_type();
    res->label = exp->label;    //exp is first block

    if(curr_break_exp != nullptr)
        res->next_list = code_bp.merge(curr_break_exp->next_list, exp->false_list);

    code_bp.bpatch(exp->true_list, statment->label);
    code_bp.bpatch(statment->next_list, exp->label);

    return res;
}
//handles continue
cut_type* Comp::handle_continue(cut_type* exp) {
    cut_type* res = new cut_type();
    res->label = code_bp.genLabel();
    
    code_bp.emit("br label %" + exp->label); //jump back to the begining of this while

    return res;
}
//handles break
cut_type* Comp::handle_break(cut_type* this_break) {
    
    cut_type* res = new cut_type();
    res->label = code_bp.genLabel();
        //code_bp.emit("************************");

    int row_num = code_bp.emit("br label @" ); //skip this part

    this_break->next_list.push_back(make_pair(row_num, FIRST));

    return res;
}

//handles specific Case
cut_type* Comp::handle_casedeal(cut_type* num,cut_type* statem) {


    
    cut_type* res = new cut_type();

    

    res->label = statem->label;
    res->str = num->str; //his string number 
    res->next_list = statem->next_list;
    return res;
}
//handles one Case from caselist
cut_type* Comp::handle_caselist_one(cut_type* this_case) {
    cut_type* res = new cut_type();


    res->cases_labels_vec.push_back(this_case->label);
    res->cases_str_num_vec.push_back(this_case->str);

    res->next_list = this_case->next_list;
    
    res->exist_default = this_case->exist_default;
    return res;
}
//handles caselist
cut_type* Comp::handle_caselist(cut_type* this_case, cut_type* caselist) {
    cut_type* res = new cut_type();
    if(!this_case->next_list.empty()){ //there is no break in this case
        code_bp.bpatch(this_case->next_list, caselist->cases_labels_vec.back());
    }
    res->cases_labels_vec = caselist->cases_labels_vec;
    res->cases_labels_vec.push_back(this_case->label);
    
    res->cases_str_num_vec = caselist->cases_str_num_vec;
    res->cases_str_num_vec.push_back(this_case->str);


    
    res->next_list = code_bp.merge(caselist->next_list, this_case->next_list);

    res->exist_default = this_case->exist_default || caselist->exist_default;
    return res;
}

//handles default case
cut_type* Comp::handle_default_case(cut_type* def) {
    cut_type* res = new cut_type();
    
    //res->cases_labels_vec = def->cases_labels_vec;
    res->cases_labels_vec.push_back(def->label);
    
    //res->cases_str_num_vec = caselist->cases_str_num_vec;
    res->cases_str_num_vec.push_back(def->str);
    res->next_list = def->next_list;

    res->exist_default = true;
    return res;
}

//handles default case
cut_type* Comp::handle_switch(cut_type* exp, cut_type* caselist, cut_type* switch_breaks) {
    cut_type* res = new cut_type();
    
    res->label = exp->label;
    string new_label =code_bp.genLabel();
    code_bp.bpatch(exp->next_list, new_label);
    
    int row_num;
    string new_case_label;
    int i =0;
    //cout<<caselist->next_list.size()<<"  ***********\n\n";
    while(!caselist->cases_str_num_vec.empty()){
        
        if(i != 0){
            new_case_label =code_bp.genLabel();
            code_bp.bpatch(res->next_list, new_case_label);
        }
        
        
        string curr_str_num = caselist->cases_str_num_vec.back();
        caselist->cases_str_num_vec.pop_back();

        string curr_label_case = caselist->cases_labels_vec.back();
        caselist->cases_labels_vec.pop_back();


        if (caselist->exist_default && caselist->cases_str_num_vec.size() == 0){
            // only for default
            row_num = code_bp.emit("br label %" + curr_label_case );
            break; 
        }
        string this_case_val_reg = generete_reg() + "_case_val_" + to_string(i);
        code_bp.emit(this_case_val_reg + " = add i32 " + curr_str_num + ", 0");

        string after_cmp = generete_reg() + "_case_" + to_string(i);
        code_bp.emit(after_cmp + " = icmp eq i32 " + exp->place + ", " + this_case_val_reg);
        row_num = code_bp.emit("br i1 " + after_cmp + ", label %" + curr_label_case + ", label @");
       
        res->next_list.push_back(make_pair(row_num, SECOND));
        i++;

        
    }

    

    string end_label = code_bp.genLabel();
    code_bp.bpatch(res->next_list, end_label);
    row_num = code_bp.emit("br label @" ); 
    res->next_list.push_back(make_pair(row_num, FIRST));

    res->next_list = code_bp.merge(switch_breaks->next_list, res->next_list);

    if(!caselist->next_list.empty()){ //there is no break in this case
        res->next_list = code_bp.merge(caselist->next_list, res->next_list);
    }
    //res->next_list = code_bp.merge(caselist->next_list, res->next_list);
    
    return res;
}
