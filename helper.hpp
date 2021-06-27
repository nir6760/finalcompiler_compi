#ifndef _HELPER
#define _HELPER

#include "bp.hpp"
#include <vector>
#include <unordered_map>
using namespace std;



// class cut_type{// class for value properties
	
//     public:
// 	int val;
//     string type;
//     string ret_type;
// 	string name;
// 	vector<string> params_type;
// 	vector<string> params_names;
// };


class cut_type {
    public:
    string str;
    string place;
    string label;

    bool exist_default =false;


    vector<string> params_type;    /* type of params          */
    vector<string> params_names;    /* type of params          */

    vector<pair<int,BranchLabelIndex>> true_list;
    vector<pair<int,BranchLabelIndex>> false_list;
    vector<pair<int,BranchLabelIndex>> next_list;

    vector<string> cases_labels_vec;
    vector<string> cases_places_vec;
    
    cut_type(){}
    cut_type(string st):str(st){}
    cut_type(string st,  string pla):str(st),place(pla){} // only for expressions
};

#define YYSTYPE cut_type* /* tells bison to use YYSTYPE as cut_type*         */
class SymbolTable{
    public:
    SymbolTable();
    //~SymbolTable();
    void InitPrintFunctions();
    void openScope(bool isWhile, bool isSwitch);
    void closeScope(bool print);
    void addFunc(const string& name, const string& ret_type
    , const vector<string>& params_type, const vector<string>& params_names);
    void insertVarToSymbolTable(const string& name, const string& type);
    void checkWasMain();
    int endComp();
    void mergeVectors(vector<string>& v1, vector<string>& v2);
    void checkValidTypes(const string& t1, const string& t2);
    void checkValidID(const string& name);
    string typeOfSym(const string& name);
    void checkRetType(const string& type);
    void checkVoidRetType();
    void checkUnexpected(const string& unexp);
    void isBool(const string& t);
    void isIntByte(const string& t);
    void checkOverFlowByte(int num);
    void checkFuncDecl(const string& name, const vector<string>& params_types);
    void checkValidNumeric(const string& t1, const string& t2);
    void checkValidCast(const string& t1, const string& t2);
    string findExpType(const string& t1, const string& t2);
    void checkName(const string& name);
    void helperInsertVar(const string& name, const string& type, int offset);
    

    
    

    

    class stype    //class for variable inside symbols 
    {
        public:
        bool is_function;
        bool is_ret = false;
        string name;    /* name of symbol          */
        string type;    /* type of symbol          */
        vector<string> params_type;    /* type of params          */
        vector<string> params_names;    /* type of params          */
        int offset;	 /* offset of symbol          */

        string place; //the location, register or %x or register with adress to memory
        int reg_save; // 0- it is a param (%x), 1- it is a reg with adress to memory, 2- it is a reg that saved the value
        string reg_stack_local_var;
        
        stype(){}

        stype(bool is_func ,const string& n, const string& t,  int of)://for variable or parameter
        is_function(is_func), name(n), type(t),  offset(of) {}

        stype(bool is_func,const string& n, const string& t,const vector<string>& p_type,const vector<string>& p_names,  int of ):
        is_function(is_func), name(n), type(t), params_type(p_type), params_names(p_names),  offset(of) {}//for function
        
       // void editStype(bool is_func,const string& n, const string& t,const vector<string>& p_type,const vector<string>& p_names,  int of );//edit stype for function
    };


    class inside_scope{// class for scope properties
        public:
        int curr_scope;
        vector<stype> symbols_lst;
        bool isWhileScope;
        bool isSwitchScope;

        inside_scope(int scope_num, vector<stype>& symbols, bool isWh, bool isSw ):
        curr_scope(scope_num),symbols_lst(symbols), isWhileScope(isWh), isSwitchScope(isSw) {}
        void IntializeFuncs();
    
    };
    void setPlace(const string& id, const string& reg, int save_reg_type);
    void setRegSave(const string& id, int new_num);
    int getRegSave(const string& id);
    stype* getStype(const string& id);
    string getParamAddPlace(const string& id, int& how_it_saved);
    int getParamOffset(const string& id);
    string getVarType(const string& id);
    string getFuncType(const string& id);

    stype* this_func; //save the current function
    

    private:

    typedef vector<inside_scope> StackScopes;
    //typedef unordered_map<string, stype*> SymbolHash;

    StackScopes stack_scope; //stack of scopes
    //SymbolHash symbol_table_hash; // map for symbol table, should not be used
};







#endif