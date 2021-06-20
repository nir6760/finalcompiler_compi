#ifndef COMP_H
#define COMP_H
#include "helper.hpp"
#include "bp.hpp"

class Comp {
    private:
    CodeBuffer& buffer;
    SymbolTable& table;
    int count_regs;
    //props * emitBinopLine(props& reg1, const std::string& op, props& reg2);
    //int stringCounter;

    public:
    Comp(SymbolTable& t);
    string getNextReg();
    string getTypeString(const string& type);
    cut_type* handle_decl(cut_type*&  sym_type,string& id, cut_type* assign_to);
    cut_type * handle_func(const string& type, const string& id,
     const vector<string>& params_type, const vector<string>& params_names );
    void end_func();
    void handle_funcBP(cut_type* func, cut_type* statement);
    cut_type* handle_one_statment(cut_type* statement);
    void allocateStack(string reg); 
    cut_type* handle_statments(cut_type* statements, cut_type* statement);
    // void resetReg() { regCounter = 0;};
    // props * handleBinop(props & exp1, std::string & op, props & exp2);
    // props * handleNum(std::string & num);
    // props * handleByte(std::string & num);
    // props * handleCall(std::string & id, std::vector<props*> params);
    // props * handleRet(props * prop);

    // props * handleAssignment(std::string& id, props * prop);
    // props * handleId(std::string& id);
    // props * handleBoolen(bool param);
    // props * handleNot(props* prop);
    // props * handleOr(props* prop1, props* prop2);
    // props * handleAnd(props* prop1, props* prop2);
    // props * handleIf(props* exp, props* true_state, props* false_state);
    // props * handleString(std::string str);
    // props * handleRelOp(props* prop1, props* prop2, std::string op);
    // props * handleWhile(props* exp, props* statement, vector<pair<int,BranchLabelIndex>>& next_list);
    // props * handleContinue(props* exp);
    // props * handleBreak(vector<pair<int,BranchLabelIndex>>& next_list);
    
    // props * handleSet(int low, int high);
    // props * handleInSet(props * exp, props * set);
    // props * handleCast(props * set);


    // void setCheckBoundaries(const std::string& reg, int low, int high, std::string value_reg, std::string op);
    // void zeroSet(std::string reg, int low, int high);
    // void copySet(std::string reg, std::string set_reg);
    // void changeSetValue(std::string set_reg, std::string op_str, std::string value_reg, int low);
    // void checkDivZero(const std::string& reg);
    // void handleFuncEnd();
    // void handleFuncBpatch(props* func, props* statement);
    // std::string handleBoolToReg(props* prop);


};
#endif


