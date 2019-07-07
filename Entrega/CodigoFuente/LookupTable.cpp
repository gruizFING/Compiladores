#include "LookupTable.h"
#include <iostream>
using namespace std;

LookupTable::~LookupTable() 
{
    for (int i = 0; i < table.size(); i++)
        delete table[i];
}

void LookupTable::Add(LuaObject* var)
{
    table.push_back(var);
}

void LookupTable::update(string varname, LuaObject* value)
{
    int pos = table.size()-1;
    while (pos >= 0)
    {
        LuaObject* lo = table[pos];
        if (lo->getID().compare(varname) == 0)
        {
            if (lo->getType() == value->getType())
            {
                value->setID(varname);
                table[pos] = value;
                value = lo;
            }
            else
            {
                LuaObject* newLo;
                switch (value->getType())
                {
                    case LuaObject::NIL:
                    {
                        newLo = new LuaObject(varname);
                        break;
                    }
                    case LuaObject::DOUBLE:
                    {
                        newLo = new LuaFloat(varname, dynamic_cast<LuaFloat*>(value)->getValue());
                        break;
                    }
                    case LuaObject::STRING:
                    {
                        newLo = new LuaString(varname, dynamic_cast<LuaString*>(value)->getValue());
                        break;
                    }
                    case LuaObject::BOOLEAN:
                    {
                        newLo = new LuaBoolean(varname, dynamic_cast<LuaBoolean*>(value)->getValue());
                        break;
                    }
                    case LuaObject::FUNCTION:
                    {
                        newLo = new LuaFunction(varname, dynamic_cast<LuaFunction*>(value)->getValue());
                        break;
                    }
                    case LuaObject::TABLE:
                    {
                        newLo = new LuaTable(varname, dynamic_cast<LuaTable*>(value)->getValue());
                        break;
                    }
                    default:break;
                }
                table[pos] = newLo;
                delete lo;
            }
            break;
        }
        pos--;
    }
    delete value;
}

void LookupTable::addVar(string id, double value)
{
	table.push_back(new LuaFloat(id, value));
}
void LookupTable::addVar(string id, string value)
{
	table.push_back(new LuaString(id, value));
}
void LookupTable::addFunc(string id, ast* funcBody)
{
	table.push_back(new LuaFunction(id, funcBody));
}
vector<LuaObject *> & LookupTable::SymbolTable()
{
	return table;
}




bool LookupTable::existeVar(string varname)
{
    int pos = table.size()-1;
    while (pos >= 0)
    {
        if (table[pos]->getID().compare(varname) == 0)
            return true;
        pos--;
    }
    return false;
}

LuaObject* LookupTable::getVar(string varname)
{
    int pos = table.size()-1;
    LuaObject* newLo = NULL;
    while (pos >= 0 && newLo == NULL)
    {
        LuaObject* value = table[pos];
        if (value->getID().compare(varname) == 0)
        {
            switch (value->getType())
            {
                case LuaObject::NIL:
                {
                    newLo = new LuaObject(varname);
                    break;
                }
                case LuaObject::DOUBLE:
                {
                    newLo = new LuaFloat(varname, dynamic_cast<LuaFloat*>(value)->getValue());
                    break;
                }
                case LuaObject::STRING:
                {
                    newLo = new LuaString(varname, dynamic_cast<LuaString*>(value)->getValue());
                    break;
                }
                case LuaObject::BOOLEAN:
                {
                    newLo = new LuaBoolean(varname, dynamic_cast<LuaBoolean*>(value)->getValue());
                    break;
                }
                case LuaObject::FUNCTION:
                {
                    newLo = new LuaFunction(varname, dynamic_cast<LuaFunction*>(value)->getValue());
                    break;
                }
                case LuaObject::TABLE:
                {
                    newLo = new LuaTable(varname, dynamic_cast<LuaTable*>(value)->getValue());
                    break;
                }
                default:break;
            }
        }
        pos--;
    }
    return newLo;
}



