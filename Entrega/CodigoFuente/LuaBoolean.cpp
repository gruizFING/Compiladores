#include "LuaBoolean.h"

LuaBoolean::LuaBoolean() : LuaObject(), m_value(false) {
}

LuaBoolean::LuaBoolean(string id, bool value) : LuaObject(id), m_value(value){
}

LuaBoolean::LuaBoolean(bool value) : LuaObject(), m_value(value){
}

LuaBoolean::LuaBoolean(const LuaBoolean& orig) {
}

LuaBoolean::~LuaBoolean() {
}

bool LuaBoolean::getValue() const
{
	return m_value;
}

void LuaBoolean::setValue(bool value)
{
	m_value = value;
}

LuaObject& LuaBoolean::operator=(LuaObject & rhs)
{
    this->setValue((dynamic_cast<LuaBoolean*>(&rhs))->getValue());
    return *this;
}


LuaObject& LuaBoolean::operator||(LuaObject & rhs)
{
    LuaBoolean* tBool = new LuaBoolean("",false);
    
    if(rhs.getType() == LuaObject::BOOLEAN)
    {	
	bool temp = m_value || (dynamic_cast<LuaBoolean*>(&rhs))->getValue();
        tBool->setValue(temp);
    }
    else
    {
	bool temp = this->getValue();
        if (temp == true)
            tBool->setValue(temp);
        else
            return rhs; //retorno la exp derecha
    }
    return *tBool;    
}

LuaObject& LuaBoolean::operator&&(LuaObject & rhs)
{
    LuaBoolean* tBool = new LuaBoolean("",false);
    
    if(rhs.getType() == LuaObject::BOOLEAN)
    {	
        bool temp = this->getValue();
	temp = temp && (dynamic_cast<LuaBoolean*>(&rhs))->getValue();
        tBool->setValue(temp);
    }
    else
    {
	bool temp = this->getValue();
        if (temp == false)
            tBool->setValue(temp);
        else
            return rhs; //retorno la exp derecha
    }
    return *tBool;    
}

LuaObject& LuaBoolean::operator+(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica en boolean";
}
LuaObject& LuaBoolean::operator-(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica en boolean";
}
LuaObject& LuaBoolean::operator/(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en boolean";
}
LuaObject& LuaBoolean::operator*(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en boolean";
}

LuaObject& LuaBoolean::operator%(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en boolean";
}

LuaObject& LuaBoolean::operator^(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en boolean";
}

LuaObject& LuaBoolean::operator==(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::BOOLEAN)
	{	
		bool temp1 = this->getValue();
                bool temp2 = dynamic_cast<LuaBoolean*>(&rhs)->getValue(); 

		tBool->setValue(temp1 == temp2);
	}
        //else siempre false
	
	return *tBool;
}

LuaObject& LuaBoolean::operator!=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",true);

	if(rhs.getType() == LuaObject::BOOLEAN)
	{	
		bool temp1 = this->getValue();
                bool temp2 = dynamic_cast<LuaBoolean*>(&rhs)->getValue(); 

		tBool->setValue(temp1 != temp2);
	}
        //else siempre devuelve true
	return *tBool;
}

LuaObject& LuaBoolean::operator>(LuaObject & rhs)
{
        if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar boolean con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar boolean con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar boolean con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar boolean con number";
}

LuaObject& LuaBoolean::operator<(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar boolean con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar boolean con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar boolean con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar boolean con number";
}

LuaObject& LuaBoolean::operator>=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar boolean con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar boolean con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar boolean con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar boolean con number";
}

LuaObject& LuaBoolean::operator<=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar boolean con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar boolean con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar boolean con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar boolean con number";
}

LuaObject& LuaBoolean::operator+=(LuaObject & rhs)
{
    throw "Error: Intentando concatenar un valor booleano";
}


int LuaBoolean::getType()
{
	return LuaObject::BOOLEAN;
}

string LuaBoolean::toString()
{
    if (m_value == true)
        return "true";
    else
        return "false";
}

