#include "LuaFloat.h"
#include "LuaBoolean.h"
#include "LuaString.h"
#include <math.h>
#include <cstdio>

LuaFloat::LuaFloat(): LuaObject(), m_value(0)
{	}
LuaFloat::LuaFloat(string id, double value):LuaObject(id), m_value(value)
{	}

LuaFloat::LuaFloat(double value):LuaObject(), m_value(value)
{	}

LuaFloat::~LuaFloat()
{	}
LuaObject& LuaFloat::operator=(LuaObject& rhs)
{//Assuming the scope is correct
	if(rhs.getType() == LuaObject::DOUBLE)
	{
		this->setValue(dynamic_cast<LuaFloat*>(&rhs)->getValue());
	}else
	{
		//nope
			//error out?
	}

	return *this;
}
double LuaFloat::getValue() const
{
	return m_value;
}

void LuaFloat::setValue(double value)
{
	m_value = value;
}

//Circuito corto, parte izq
LuaObject& LuaFloat::operator||(LuaObject & rhs)
{
    return *this;
}

//Circuito largo, parte derecha
LuaObject& LuaFloat::operator&&(LuaObject & rhs)
{
    return rhs;
}

LuaObject& LuaFloat::operator+(LuaObject& rhs)
{
	LuaFloat* tFloat = new LuaFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp += dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat->setValue(temp);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando aritemtica en un string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando aritemtica en nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando aritemtica en boolean";		
	}
	return *tFloat;
}
LuaObject& LuaFloat::operator-(LuaObject & rhs)
{
	LuaFloat* tFloat = new LuaFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp -= dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat->setValue(temp);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando aritemtica en un string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando aritemtica en nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando aritemtica en boolean";		
	}
	return *tFloat;
}
LuaObject& LuaFloat::operator/(LuaObject & rhs)
{
	LuaFloat* tFloat = new LuaFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp /= dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat->setValue(temp);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando aritemtica en un string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando aritemtica en nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando aritemtica en boolean";		
	}
	return *tFloat;
}
LuaObject& LuaFloat::operator*(LuaObject & rhs)
{
	LuaFloat* tFloat = new LuaFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		temp *= dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat->setValue(temp);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando aritemtica en un string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando aritemtica en nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando aritemtica en boolean";		
	}
	return *tFloat;
}

double moduloDouble(double a, double b)
{
        int result = static_cast<int>( a / b );
        return a - static_cast<double>( result ) * b;
}

LuaObject& LuaFloat::operator%(LuaObject & rhs)
{
	LuaFloat* tFloat = new LuaFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat->setValue(moduloDouble(temp,temp2));
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando aritemtica en un string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando aritemtica en nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando aritemtica en boolean";
	}
	return *tFloat;
}



LuaObject& LuaFloat::operator^(LuaObject & rhs)
{
	LuaFloat* tFloat = new LuaFloat("",0);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp = this->getValue();
		double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue();

		tFloat->setValue(pow(temp,temp2));
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando aritemtica en un string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando aritemtica en nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando aritemtica en boolean";
	}
	return *tFloat;
}

LuaObject& LuaFloat::operator==(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp1 = this->getValue();
                double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue(); 

		tBool->setValue(temp1 == temp2);
	}
        //else siempre false
	
	return *tBool;
}

LuaObject& LuaFloat::operator!=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp1 = this->getValue();
                double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue(); 

		tBool->setValue(temp1 != temp2);
	}
        //else siempre devuelve true
	return *tBool;
}

LuaObject& LuaFloat::operator>(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp1 = this->getValue();
                double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue(); 

		tBool->setValue(temp1 > temp2);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando comparar number con string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar number con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar number con boolean";
	}
	return *tBool;
}

LuaObject& LuaFloat::operator<(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp1 = this->getValue();
                double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue(); 

		tBool->setValue(temp1 < temp2);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando comparar number con string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar number con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar number con boolean";
	}
	return *tBool;
}

LuaObject& LuaFloat::operator>=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp1 = this->getValue();
                double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue(); 

		tBool->setValue(temp1 >= temp2);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando comparar number con string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar number con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar number con boolean";
	}
	return *tBool;
}

LuaObject& LuaFloat::operator<=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::DOUBLE)
	{	
		double temp1 = this->getValue();
                double temp2 = dynamic_cast<LuaFloat *>(&rhs)->getValue(); 

		tBool->setValue(temp1 <= temp2);
	}else
	{
            if(rhs.getType() == LuaObject::STRING)
                throw "Error: Intentando comparar number con string";
            else if (rhs.getType() == LuaObject::NIL)
                throw "Error: Intentando comparar number con nil";
            else if (rhs.getType() == LuaObject::BOOLEAN)
                throw "Error: Intentando comparar number con boolean";
	}
	return *tBool;
}

LuaObject& LuaFloat::operator+=(LuaObject & rhs)
{
    
    LuaString* ls = new LuaString("","");

	if(rhs.getType() == LuaObject::STRING)
	{	
                double doub = this->getValue();
                char* buffer = new char(32);
                snprintf(buffer, 32, "%g", doub);
                string temp = buffer;
		temp = temp.append(dynamic_cast<LuaString*>(&rhs)->getValue()); 

		ls->setValue(temp);
	}else
	{
            if(rhs.getType() == LuaObject::DOUBLE)
            {
                double doub = this->getValue();
                char* buffer = new char(32);
                snprintf(buffer, 32, "%g", doub);
                string temp = buffer;
                
                doub = dynamic_cast<LuaFloat*>(&rhs)->getValue();
                buffer = new char(32);
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



int LuaFloat::getType()
{
	return LuaObject::DOUBLE;
}

string LuaFloat::toString()
{
    double doub = this->getValue();
    char* buffer = new char(32);
    snprintf(buffer, 32, "%g", doub);
    string temp = buffer;
    return temp;
}

