#include "helper.hpp"
#include "hw3_output.hpp"
#include <iostream>
using namespace std;
using namespace output;
#define BYTE_EDGE 255
extern int yylineno;

int global_offset = 0;
int number_of_while = 0;
int number_of_switch = 0;
//SymbolTable::stype* this_func = new SymbolTable::stype();
bool was_main = false;

bool checkIsItMain(const string& name, const string& ret_type, const vector<string>& params_type);

SymbolTable::SymbolTable(){
	//this_func = new SymbolTable::stype();
    InitPrintFunctions();
}

// SymbolTable::~SymbolTable(){
// 	delete this_func;
// }

// edit stype for the current function
// void SymbolTable::stype::editStype(bool is_func,const string& n, const string& t,const vector<string>& p_type,const vector<string>& p_names,  int of ){
// 	is_function=is_func;
// 	name=n;
// 	type=t;
// 	params_type=p_type;
// 	params_names=p_names;
// 	offset=of; 
// }

// check if the symbol allready exists
void SymbolTable::checkName(const string& name){ 
	stype* suspect = getStype(name);
	if (suspect != nullptr) {
		errorDef(yylineno, name);
		//delete this_func;
		exit(1);
	}
}


//open new scope
void SymbolTable::openScope(bool isWhile, bool isSwitch){ 
	vector<stype> empty_vec;
    inside_scope sc(global_offset, empty_vec, isWhile, isSwitch);
    if(isWhile){
        ++number_of_while;
    }
	if(isSwitch){
		++number_of_switch;
	}
    stack_scope.push_back(sc);

}

//close scope and print
void SymbolTable::closeScope(bool print = true) {
	inside_scope& sc = stack_scope.back();
	if(print){
		endScope();
	}
	for (auto& symbol : sc.symbols_lst) {
		if (print){
			if (symbol.is_function){
				printID(symbol.name, symbol.offset, makeFunctionType(symbol.type, symbol.params_type));
			} 
			else{
				printID(symbol.name, symbol.offset, symbol.type);
			}				
		}
		//symbol_table_hash.erase(symbol.name);
	}
	global_offset = sc.curr_scope;
	if (sc.isWhileScope){
		--number_of_while;
	}
	if (sc.isSwitchScope){
		--number_of_switch;
	}
	stack_scope.pop_back();
}

// init print and print and global scope
void SymbolTable::InitPrintFunctions() { 
	openScope(false,false);
	addFunc("print", "VOID", {"STRING"}, {"print_val_name"});
	closeScope(false);
	addFunc("printi", "VOID", {"INT"}, {"printi_val_name"});
	closeScope(false);
	
}
//check if Main was valid decleared and close the global scope
void SymbolTable::checkWasMain() { 
	if (!was_main) {
		errorMainMissing();
		delete this_func;
		exit(1);
	}
}
//check if Main was valid decleared and close the global scope
bool checkIsItMain(const string& name, const string& ret_type, const vector<string>& params_type) { 
	if ("main" == name && "VOID" == ret_type && params_type.empty())
		return true;
	return false;
}
//add function to symbol table and open scope for it
void SymbolTable::addFunc(const string& name, const string& ret_type, const vector<string>& params_type, const vector<string>& params_names) {
	
	checkName(name);
	
    //this_func->editStype(true, name, ret_type, params_type, params_names, 0); 

	stype* curr_func_temp = new stype(true,name, ret_type,params_type,params_names,  0);
	
	stack_scope.back().symbols_lst.push_back(*curr_func_temp);

	this_func = &(stack_scope.back().symbols_lst.back());

	delete curr_func_temp;
	
	//symbol_table_hash[name] = *this_func;
	*getStype(name) = (stack_scope.back().symbols_lst.back());
	openScope(false,false);
    int i=0;
	for (auto& p_name : params_names) {
		i++;
		helperInsertVar(p_name, params_type[i-1], -i);
	}
	if (checkIsItMain(name, ret_type, params_type)){
		if(was_main){
			errorMainMissing();
			//delete this_func;
			exit(1);
		}
		else{
			was_main = true;
		}
	}
	
		
		
}

// insert var to symbol table
void SymbolTable::insertVarToSymbolTable(const string& name, const string& type) {
	helperInsertVar(name, type, global_offset++);
}

// helper for insert var to symbol table
void SymbolTable::helperInsertVar(const string& name, const string& type, int offset) {

	checkName(name);
    stype var(false, name, type, offset);
	stack_scope.back().symbols_lst.push_back(var);
	//symbol_table_hash[name] = var;
	
	*getStype(name) = (stack_scope.back().symbols_lst.back());

}


//end global scope and compilation process
int SymbolTable::endComp(){
	closeScope(true);
	//delete this_func; //in the destructor
	return 0;
}


//merge 2 vectors to the first one
void SymbolTable::mergeVectors(vector<string>& v1, vector<string>& v2){
    v1.insert(v1.end(),v2.begin(),v2.end());
}

//check if types are valid in the action
void SymbolTable::checkValidTypes(const string& t1, const string& t2) { 
	if (t1 != t2 && !(t1 == "INT" && t2 == "BYTE")) {
		errorMismatch(yylineno);
		//delete this_func;
		exit(1);
	}
}

// check if id was not define
void SymbolTable::checkValidID(const string& name) {
	stype* suspect = getStype(name);
	if (suspect == nullptr||
	suspect->is_function){
		 
		errorUndef(yylineno, name);
				
		//delete this_func;
		exit(1);
	}
	
}

//return the type of the decleared function
string SymbolTable::typeOfSym(const string& name){ 
	return getStype(name)->type;
}

//check if the return type is identical to what was decleared in the function
void SymbolTable::checkRetType(const string& type) {
	if(this_func->type=="VOID"){
		errorMismatch(yylineno);
		//delete this_func;
		exit(1);
	}
	checkValidTypes(this_func->type, type);
	this_func->is_ret = true;
}

//check if the return type is void
void SymbolTable::checkVoidRetType() {
	if(this_func->type!="VOID"){
		errorMismatch(yylineno);
		//delete this_func;
		exit(1);
	}
}

// check for unexpected break or continue
void SymbolTable::checkUnexpected(const string& unexp) {
	if(unexp == "CONTINUE"){
		if (number_of_while == 0){
			errorUnexpectedContinue(yylineno);
			//delete this_func;
			exit(1);
		}
	}
	if(unexp == "BREAK"){
		if (number_of_while == 0 && number_of_switch == 0){
			errorUnexpectedBreak(yylineno);
			//delete this_func;
			exit(1);
		}
	}
}

//check if type is bool
void SymbolTable::isBool(const string& t) { 
	if (t != "BOOL") {
		errorMismatch(yylineno);
		//delete this_func;
		exit(1);
	}
}

void SymbolTable::isIntByte(const string& t) { //check if type is int or byte
	if (t != "INT" && t != "BYTE"  ) {
		errorMismatch(yylineno);
		//delete this_func;
		exit(1);
	}
}

// check if byte is overflow
void SymbolTable::checkOverFlowByte(int num) { 
	if (num > BYTE_EDGE) {
		errorByteTooLarge(yylineno, to_string(num));
		//delete this_func;
		exit(1);
	}
}

// check if function was decleared and if its valid call
void SymbolTable::checkFuncDecl(const string& func_name, const vector<string>& params_names) { 
	
	stype* suspect = getStype(func_name);
	
	if (suspect == nullptr|| !suspect->is_function) {
		
		errorUndefFunc(yylineno, func_name);
		//delete this_func;
		exit(1);
	}

	stype& f = *(suspect);
	
	if (f.params_names.size() != params_names.size()) {
		errorPrototypeMismatch(yylineno, func_name, f.params_type);
		
		//delete this_func;
		exit(1);
	}

	for (unsigned int i =0; i < params_names.size(); ++i) {

		string param_type = params_names[i];
	
		if (f.params_type[i] != param_type && !(f.params_type[i] == "INT" && param_type == "BYTE")) {
			errorPrototypeMismatch(yylineno, func_name, f.params_type);
			//delete this_func;
			exit(1);
		}
	}

}

// find the if they both numerics
void SymbolTable::checkValidNumeric(const string& t1, const string& t2) {
	if ((t1 == "INT" || t1 == "BYTE") &&
		(t2 == "INT" || t2 == "BYTE")) 
		return;
	errorMismatch(yylineno);
	//delete this_func;
	exit(1);
}

//check if the casting is valid
void SymbolTable::checkValidCast(const string& t1, const string& t2) { 
	if (t1 == "BYTE" && t2 == "INT") {
		errorMismatch(yylineno);
		//delete this_func;
		exit(1);
	}
	
}

// find the currect type of the exp
string SymbolTable::findExpType(const string& t1, const string& t2) { 
	if (t1 == "INT" || t2 == "INT") {
		return "INT";
	} else {
		return "BYTE";
	}
}

//get the this id Stype
SymbolTable::stype* SymbolTable::getStype(const string& id){
	
	for (auto it = stack_scope.rbegin(); it != stack_scope.rend(); ++it){
		auto& inside_scope_symmbols = it->symbols_lst;
		
		for (auto it2 = inside_scope_symmbols.rbegin(); it2 != inside_scope_symmbols.rend(); ++it2){
			
			if (it2->name == id){
				return &(*it2);
				
			}
			
			
		}
	}


	// cout<<"**************************************************  getStype screwd!!!!!! nulptr return\n\n\n\n\n";
	// exit(0); 
	
    return nullptr;
}

//get the offset inside the scope of the param
int SymbolTable::getParamOffset(const string& id){
	try{
			auto suspect = getStype(id);
			return suspect->offset;
		}
		catch(...){
			cout << "Didnt find the symbol.\n";
			return 0;
		}
}

//get the offset inside the scope of the param
string SymbolTable::getParamAddPlace(const string& id, int& how_it_saved){
	try{
		auto suspect = getStype(id);
		how_it_saved = suspect->reg_save;
		return suspect->place;
	}
	catch(...){
		cout << "Didnt find the symbol.\n";
		return "-1";
	}
}

//set the place (name of the register with the address or %x) for the symbol
void SymbolTable::setPlace(const string& id, const string& reg, int save_reg_type){
	//save_reg_type: 0- it is a param (%x), 1- it is a reg with adress to memory, 2- it is a reg that saved the value
	try{
		SymbolTable::stype* s = getStype(id);
		s->place = reg;
		s->reg_save = save_reg_type;
	}
	catch(...){
		cout << "Didnt find the symbol.\n";
	}
}

//set the place (name of the register with the address or %x) for the symbol
void SymbolTable::setRegSave(const string& id, int new_num){
	
	try{
		getStype(id)->reg_save = new_num;
	}
	catch(...){
		cout << "Didnt find the symbol.\n";
	}
}

//set the place (name of the register with the address or %x) for the symbol
int SymbolTable::getRegSave(const string& id){
	try{
		return getStype(id)->reg_save;
	}
	catch(...){
		cout << "Didnt find the symbol.\n";
		return -1;
	}
}

//gets the symbol type
string SymbolTable::getVarType(const string& id){
	try{
		return getStype(id)->type;
	}
	catch(...){
		cout << "Didnt find the symbol.\n";
		return "-1";
	}
}

//gets the symbol type
string SymbolTable::getFuncType(const string& id){
	try{
		for (auto it = stack_scope.rbegin(); it != stack_scope.rend(); ++it){
		auto& inside_scope_symmbols = it->symbols_lst;
		for (auto it2 = inside_scope_symmbols.rbegin(); it2 != inside_scope_symmbols.rend(); ++it2){
			if (it2->name == id && it2->is_function){
				return it2->type;
			} 
		}
	}
	
    return nullptr;
	}
	catch(...){
		cout << "Didnt find the symbol.\n";
		return "-1";
	}
}




