#ifndef LUATABLE_H
#define	LUATABLE_H

#include "LuaObject.h"
#include <map>
#include <exception>
using namespace std;

class LuaTable : public LuaObject 
{
    private:
        map<string,LuaObject*> table;
        int indice;
    public:
        LuaTable();
        LuaTable(string id, map<string, LuaObject*> ntable);
        LuaTable(const LuaTable& orig);
        virtual ~LuaTable();
        
        virtual LuaObject& operator=(LuaObject & rhs);
        map<string,LuaObject*> getValue();
	LuaObject* getValue(string key);
	void setValue(string key, LuaObject* value);
        virtual LuaObject& operator||(LuaObject & rhs);
        virtual LuaObject& operator&&(LuaObject & rhs);
        virtual LuaObject& operator+(LuaObject & rhs);
        virtual LuaObject& operator-(LuaObject & rhs);
        virtual LuaObject& operator/(LuaObject & rhs);
        virtual LuaObject& operator*(LuaObject & rhs);
        virtual LuaObject& operator%(LuaObject & rhs);
        virtual LuaObject& operator^(LuaObject & rhs);
        virtual LuaObject& operator>(LuaObject & rhs);
        virtual LuaObject& operator<(LuaObject & rhs);
        virtual LuaObject& operator<=(LuaObject & rhs);
        virtual LuaObject& operator>=(LuaObject & rhs);
        virtual LuaObject& operator==(LuaObject & rhs);
        virtual LuaObject& operator!=(LuaObject & rhs);
        virtual LuaObject& operator+=(LuaObject & rhs);
	virtual int getType();
        virtual string toString();


};

#endif	/* LUATABLE_H */

