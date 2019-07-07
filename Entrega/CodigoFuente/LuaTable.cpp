#include "LuaTable.h"
#include "LuaBoolean.h"
#include "LuaFloat.h"
#include "LuaString.h"
#include "LuaFunction.h"
#include "LuaFloat.h"
#include <iostream>

LuaTable::LuaTable() : LuaObject(), indice(1) {
}

LuaTable::LuaTable(string id, map<string,LuaObject*> ntable) : LuaObject(id), table(ntable), indice(1) 
{
   
}

LuaTable::LuaTable(const LuaTable& orig) {
}

LuaTable::~LuaTable() {
    for (map<string,LuaObject*>::iterator it=table.begin(); it!=table.end(); ++it)
        delete it->second;   
}


LuaObject& LuaTable::operator=(LuaObject & rhs)
{
//    if(rhs.getType() == LuaObject::TABLE) {
//        this->setValue(dynamic_cast<LuaTable*> (&rhs)->getValue());
//    } else {
//        //ERRORS
//    }
    return *this;
}

map<string,LuaObject*> LuaTable::getValue()
{
    return table;
}


LuaObject* LuaTable::getValue(string key)
{

	LuaObject* value = table[key];
        if (value == NULL)
        {
            value = new LuaObject();
        }
        LuaObject* newLo;
        switch (value->getType()) 
        {
            case LuaObject::NIL:
            {
                newLo = value;
                break;
            }
            case LuaObject::DOUBLE:
            {
                newLo = new LuaFloat("", dynamic_cast<LuaFloat*> (value)->getValue());
                break;
            }
            case LuaObject::STRING:
            {
                newLo = new LuaString("", dynamic_cast<LuaString*> (value)->getValue());
                break;
            }
            case LuaObject::BOOLEAN:
            {
                newLo = new LuaBoolean("", dynamic_cast<LuaBoolean*> (value)->getValue());
                break;
            }
            case LuaObject::FUNCTION:
            {
                newLo = new LuaFunction("", dynamic_cast<LuaFunction*> (value)->getValue());
                break;
            }
            case LuaObject::TABLE:
            {
                newLo = new LuaTable("", dynamic_cast<LuaTable*> (value)->getValue());
                break;
            }
            default:break;
        }
        return newLo;
}

string NumberToString(int pNumber)
{
        ostringstream oOStrStream;
        oOStrStream << pNumber;
        return oOStrStream.str();
}


//Actualiza el valor si ya existe, sino crea un nuevo par y lo inserta
void LuaTable::setValue(string key, LuaObject* value)
{
    if (key == "")
    {
        string ind = NumberToString(indice); 
        table.insert(pair<string,LuaObject*>(ind,value));
        indice++;
    }
    else
    {
        LuaObject* aux = table[key];
        table[key] = value;
        if (aux != NULL)
                delete aux;
    }
}

int LuaTable::getType()
{
    return LuaObject::TABLE;
}

//Circuito corto, parte izq
LuaObject& LuaTable::operator||(LuaObject & rhs)
{
    return *this;
}

//Circuito largo, parte derecha
LuaObject& LuaTable::operator&&(LuaObject & rhs)
{
    return rhs;
}

LuaObject& LuaTable::operator+(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica con una tabla";
}
LuaObject& LuaTable::operator-(LuaObject& rhs)
{
	throw "Error: Intentando aritemtica con una tabla";
}
LuaObject& LuaTable::operator/(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica con una tabla";
}
LuaObject& LuaTable::operator*(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica con una tabla";
}

LuaObject& LuaTable::operator%(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica con una tabla";
}

LuaObject& LuaTable::operator^(LuaObject & rhs)
{
	throw "Error: Intentando aritemtica con una tabla";
}

LuaObject& LuaTable::operator==(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::TABLE)
	{	
		tBool->setValue(this->getID() == rhs.getID());
	}
        //else siempre false
	
	return *tBool;
}

LuaObject& LuaTable::operator!=(LuaObject & rhs)
{
	LuaBoolean* tBool = new LuaBoolean("",false);

	if(rhs.getType() == LuaObject::TABLE)
	{	
		tBool->setValue(this->getID() != rhs.getID());
	}
        //else siempre devuelve true
	return *tBool;
}


LuaObject& LuaTable::operator>(LuaObject & rhs)
{
        if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar tabla con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar tabla con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar tabla con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar tabla con number";
}

LuaObject& LuaTable::operator<(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar tabla con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar tabla con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar tabla con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar tabla con number";
}

LuaObject& LuaTable::operator>=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar tabla con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar tabla con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar tabla con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar tabla con number";
}

LuaObject& LuaTable::operator<=(LuaObject & rhs)
{
	if(rhs.getType() == LuaObject::STRING)
            throw "Error: Intentando comparar tabla con string";
        else if (rhs.getType() == LuaObject::NIL)
            throw "Error: Intentando comparar tabla con nil";
        else if (rhs.getType() == LuaObject::BOOLEAN)
            throw "Error: Intentando comparar tabla con boolean";
        else if (rhs.getType() == LuaObject::DOUBLE)
            throw "Error: Intentando comparar tabla con number";
}

LuaObject& LuaTable::operator+=(LuaObject & rhs)
{
    throw "Error: Intentando concatenar una tabla";
}


string LuaTable::toString()
{
	return "";
}


