#include "LuaString.h"
#include "LuaBoolean.h"
#include "LuaFloat.h"
#include <cstdio>

LuaString::LuaString(): LuaObject()
{	}
LuaString::LuaString(string id, string value): LuaObject(id), m_value(value)
{	}

LuaString::LuaString(string value): LuaObject(), m_value(value)
{	}

LuaString::~LuaString()
{

}

LuaObject& LuaString::operator=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
	{
		this->setValue(dynamic_cast<LuaString*>(&rhs)->getValue());
	}else
	{
		//ERRORS
	}
	return *this;
}
void LuaString::setValue(string value)
{
	m_value = value;
}
string LuaString::getValue() const
{
	return m_value;
}

//Circuito corto, parte izq
LuaObject& LuaString::operator||(LuaObject & rhs)
{
    return *this;
}

//Circuito largo, parte derecha
LuaObject& LuaString::operator&&(LuaObject & rhs)
{
    return rhs;
}

LuaObject& LuaString::operator+(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica en string";
}
LuaObject& LuaString::operator-(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica en string";
}
LuaObject& LuaString::operator/(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en string";
}
LuaObject& LuaString::operator*(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en string";
}

LuaObject& LuaString::operator%(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en string";
}

LuaObject& LuaString::operator^(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica en string";
}

LuaObject& LuaString::operator==(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::STRING)
	{	
		string temp1 = this->getValue();
                string temp2 = dynamic_cast<LuaString*>(&rhs)->getValue(); 

		tBool->setValue(temp1.compare(temp2) == 0);
	}
        //else siempre false
	
	return *tBool;
}

LuaObject& LuaString::operator!=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::STRING)
	{	
		string temp1 = this->getValue();
                string temp2 = dynamic_cast<LuaString*>(&rhs)->getValue(); 

		tBool->setValue(temp1.compare(temp2) != 0);
	}
        //else siempre false
	
	return *tBool;
}

LuaObject& LuaString::operator>(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::STRING)
	{	
		string temp1 = this->getValue();
                string temp2 = dynamic_cast<LuaString*>(&rhs)->getValue(); 

		tBool->setValue(temp1.compare(temp2) > 0);
	}else
	{
            if(rhs.getType() == LuaObject::DOUBLE)
                throw "Error: Intentando comparar string con number";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar string con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar string con boolean";
	}
	return *tBool;
}

LuaObject& LuaString::operator<(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::STRING)
	{	
		string temp1 = this->getValue();
                string temp2 = dynamic_cast<LuaString*>(&rhs)->getValue(); 

		tBool->setValue(temp1.compare(temp2) < 0);
	}else
	{
            if(rhs.getType() == LuaObject::DOUBLE)
                throw "Error: Intentando comparar string con number";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar string con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar string con boolean";
	}
	return *tBool;
}

LuaObject& LuaString::operator>=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::STRING)
	{	
		string temp1 = this->getValue();
                string temp2 = dynamic_cast<LuaString*>(&rhs)->getValue(); 

		tBool->setValue(temp1.compare(temp2) >= 0);
	}else
	{
            if(rhs.getType() == LuaObject::DOUBLE)
                throw "Error: Intentando comparar string con number";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar string con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar string con boolean";
	}
	return *tBool;
}

LuaObject& LuaString::operator<=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::STRING)
	{	
		string temp1 = this->getValue();
                string temp2 = dynamic_cast<LuaString*>(&rhs)->getValue(); 

		tBool->setValue(temp1.compare(temp2) <= 0);
	}else
	{
            if(rhs.getType() == LuaObject::DOUBLE)
                throw "Error: Intentando comparar string con number";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar string con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar string con boolean";
	}
	return *tBool;
}

LuaObject& LuaString::operator+=(LuaObject & rhs)
{
    LuaString* ls = new LuaString("","");

	if(rhs.getType() == LuaObject::STRING)
	{	
		string temp = this->getValue();
		temp = temp.append(dynamic_cast<LuaString*>(&rhs)->getValue()); 

		ls->setValue(temp);
	}else
	{
            if(rhs.getType() == LuaObject::DOUBLE)
            {
                string temp = this->getValue();
                double doub = dynamic_cast<LuaFloat*>(&rhs)->getValue();
                char* buffer = new char(32);
                snprintf(buffer, 32, "%g", doub);
                temp = temp.append(buffer);
                
                ls->setValue(temp);
            }
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando concatenar un valor nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando concatenar un valor booleano";		
	}
	return *ls; 
}




int LuaString::getType()
{
	return LuaObject::STRING;
}

string LuaString::toString()
{
	return m_value;
}


