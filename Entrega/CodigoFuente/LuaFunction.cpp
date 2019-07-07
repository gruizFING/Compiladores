#include "LuaFunction.h"
#include <cstdio>

LuaFunction::LuaFunction(): LuaObject()
{	}
LuaFunction::LuaFunction(string id, struct ast* funcBody): LuaObject(id), func_body(funcBody)
{
	
}

LuaFunction::~LuaFunction()
{	}

LuaObject& LuaFunction::operator=(LuaObject& rhs)
{
    
    return *this;
}

ast* LuaFunction::getValue()
{
    return func_body;
}
int LuaFunction::getType()
{
	return LuaObject::FUNCTION;
}

