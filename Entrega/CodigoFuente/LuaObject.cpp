#include "LuaObject.h"
#include "LuaBoolean.h"
#include <cstdio>

LuaObject::LuaObject(): m_id("")
{	}
LuaObject::LuaObject(string id): m_id(id)
{	}
LuaObject::~LuaObject()
{	}
LuaObject& LuaObject::operator=( LuaObject& rhs)
{
	//error

	return *this;
}
void LuaObject::setID(string id)
{
	m_id = id;
}
string LuaObject::getID()
{
	return m_id;
}

int LuaObject::getType()
{
	return NIL;
}

//Siempre devuelve el segundo exp
LuaObject& LuaObject::operator||(LuaObject & rhs)
{
    return rhs;
}

//Siempre nil
LuaObject& LuaObject::operator&&(LuaObject & rhs)
{
    return *this;
}

LuaObject& LuaObject::operator+(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica en nil";
}
LuaObject& LuaObject::operator-(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica en nil";
}
LuaObject& LuaObject::operator/(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en nil";
}
LuaObject& LuaObject::operator*(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en nil";
}

LuaObject& LuaObject::operator%(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en nil";
}

LuaObject& LuaObject::operator^(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en nil";
}

LuaObject& LuaObject::operator==(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::NIL)
	{	
		tBool->setValue(true);
	}
        //else siempre false
	
	return *tBool;
}

LuaObject& LuaObject::operator!=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::NIL)
	{	
		tBool->setValue(false);
	}
        //else siempre devuelve true
	return *tBool;
}

LuaObject& LuaObject::operator>(LuaObject & rhs)
{
        if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar nil con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar nil con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar nil con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar nil con number";
}

LuaObject& LuaObject::operator<(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar nil con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar nil con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar nil con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar nil con number";
}

LuaObject& LuaObject::operator>=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar nil con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar nil con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar nil con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar nil con number";
}

LuaObject& LuaObject::operator<=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar nil con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar nil con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar nil con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar nil con number";
}


LuaObject& LuaObject::operator+=(LuaObject & rhs)
{
    throw "Error: Intentando concatenar un nil";
}

string LuaObject::toString()
{
    return "";
}

