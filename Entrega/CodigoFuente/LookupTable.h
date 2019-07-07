#pragma once

#include <string>
#include <vector>
#include "LuaFloat.h"
#include "LuaString.h"
#include "LuaFunction.h"
#include "LuaBoolean.h"
#include "LuaFloat.h"
#include "LuaTable.h"
#include "ast.hpp"
using std::vector;
using std::string;

class LuaObject;

class LookupTable
{
	public:
                void Add(LuaObject* var);
                void update(string varname, LuaObject* value);             
		vector<LuaObject*> & SymbolTable();
                bool existeVar(string varname);
                LuaObject* getVar(string varname);
		
                virtual ~LookupTable();
	private:
		vector<LuaObject*> table;
		void addVar(string varname, double value);
		void addVar(string varname, string value);
		void addFunc(string id, struct ast* funcBody);

};
