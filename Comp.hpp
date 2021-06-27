#ifndef COMP_H
#define COMP_H
#include "helper.hpp"
#include "bp.hpp"

class Comp {
    private:
    CodeBuffer& buffer;
    SymbolTable& table;
    int count_regs = 0;
    int count_str = 0;
    //props * emitBinopLine(props& reg1, const std::string& op, props& reg2);
    //int stringCounter;

    public:
    Comp(SymbolTable& t);
    string generete_reg();
    string llvm_type(const string& type);
    cut_type* handle_decl(cut_type*&  sym_type,string& id, cut_type* assign_to);
    cut_type * handle_func(const string& type, const string& id,
     const vector<string>& params_type, const vector<string>& params_names );
    void end_func(cut_type* this_func,cut_type* statem);
    void handle_funcBP(cut_type* func, cut_type* statement);
    cut_type* handle_one_statment(cut_type* statement);
    void allocateStack(string reg); 
    cut_type* handle_statments(cut_type* statements, cut_type* statement);
    string getRegForVar(cut_type& r1);
    cut_type * handle_str(string str);
    cut_type* handle_id(cut_type* id);
    cut_type* expBin(cut_type& r1, const string& op, cut_type& r2);
    void checkZeroDiv(const string& r);
    cut_type* handle_ass(string &id, cut_type* property);
    cut_type* handle_call(string & id, vector<cut_type*> curr_call_exps);
    void closingExp(cut_type* property);
    cut_type* handle_return(cut_type* ret);
    void i32_to_byte(cut_type& from);
    void i32_to_i1(cut_type& from);
    cut_type* handle_cast(cut_type* cast);
    cut_type* bool_val(int val);
    string reg_bool_after_choice(cut_type* booly);
    cut_type* handle_not(cut_type* exp);
    cut_type* handle_or(cut_type* exp1, cut_type* exp2);
    cut_type* handle_and(cut_type* exp1, cut_type* exp2);
    cut_type* handle_relop_equalop(cut_type* exp1,string op, cut_type* exp2);
    cut_type* handle_only_if(cut_type* exp, cut_type* statment);
    cut_type* handle_if_else(cut_type* exp, cut_type* if_statem, cut_type* else_statem);

    cut_type* handle_while(cut_type* exp, cut_type* statment, cut_type* curr_break_exp);
    cut_type* handle_continue(cut_type* exp);
    cut_type* handle_break(cut_type* exp);
    cut_type* handle_casedeal(cut_type* num,cut_type* statem);
    cut_type* handle_caselist_one(cut_type* this_case);
    cut_type* handle_caselist(cut_type* this_case, cut_type* caselist);
    cut_type* handle_default_case(cut_type* def);
    cut_type* handle_switch(cut_type* exp, cut_type* caselist);

    // props * handleWhile(props* exp, props* statement, vector<pair<int,BranchLabelIndex>>& next_list);
    // props * handleContinue(props* exp);
    // props * handleBreak(vector<pair<int,BranchLabelIndex>>& next_list);
    



};
#endif


