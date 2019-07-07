#ifndef SCOPE_H
#define	SCOPE_H

#include <vector>
#include "LookupTable.h"
#include <stdlib.h>
using std::vector;

class LookupTable;
class ast;

class Scope 
{    
private:
    
    vector<LookupTable*> stack;    
    static Scope* instance;
    Scope();
    
public:
    static Scope* getInstance();  
    virtual ~Scope();

    //void Add(ast* ptr);
    vector<LuaObject*> atom_exp(ast* exp);
    void push();
    void pop();
    //Retorna el nivel del scope que esta la variable con varname
    //Nivel 0 es global, luego aumenta de a 1
    //Si retorna -1 entonces la variable no existe
    int getLevelScope(string varname);
    bool existeEnScopeActual(string varname);
    void addLocal(string varname, LuaObject* value);
    void addGlobal(string varname, LuaObject* value);
    LuaObject* getVariable(string varname);
 
};

#endif	/* SCOPE_H */

