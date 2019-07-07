#include "Scope.h"
#include "LuaTable.h"

Scope::Scope() {
}

Scope::~Scope() {
}

Scope* Scope::instance = NULL;
Scope* Scope::getInstance()
{
    if (instance == NULL)
        instance = new Scope();
    return instance;
}

void Scope::push()
{
    LookupTable* lut = new LookupTable();
    stack.push_back(lut);
}

void Scope::pop()
{
    delete stack.back();
    stack.pop_back();
}

int Scope::getLevelScope(string varname)
{
    //Busco desde el scope mayor posible..
    int lvl = stack.size()-1;
    while (lvl >= 0)
    {
        if (stack[lvl]->existeVar(varname))
            break;
        lvl--;
    }
    return lvl;
}

bool Scope::existeEnScopeActual(string varname)
{
    int lvl = stack.size()-1;
    if (stack[lvl]->existeVar(varname))
        return true;
    return false;
}


//Agrega una var global al scope, si ya existe actualiza su valor
//Si ya existe pero no es global, entonces cambia su valor tmb
void Scope::addGlobal(string varname, LuaObject* value)
{
    int lvl = getLevelScope(varname);
    if (lvl == -1)
    {
        value->setID(varname);
        stack.front()->Add(value);
    }
    else
    {
        stack[lvl]->update(varname,value);
    }
}

//Agrega una val local al scope, solo ve en el scope actual, el mayor
void Scope::addLocal(string varname, LuaObject* value)
{
    if (!existeEnScopeActual(varname))
    {
        //Puede existir en un scope inferior pero al ser local esta tiene prioridad..
        value->setID(varname);
        stack.back()->Add(value);
    }
    else
    {
        //Ya existe esta var local, actualiza
        stack.back()->update(varname,value);
    }
}

//Retorna LuaObject tipo NIL si no existe la variable con nombre varname
LuaObject* Scope::getVariable(string varname)
{
    //Busco desde el scope mayor posible..
    int lvl = stack.size()-1;
    LuaObject* loRes = NULL;
    while (lvl >= 0 && loRes == NULL)
    {
        loRes = stack[lvl]->getVar(varname);
        lvl--;
    }
    if (loRes == NULL)
        loRes = new LuaObject(varname);
    return loRes;
}

//Si retorna NULL entonces error
vector<LuaObject*> Scope::atom_exp(ast* exp)
{
    vector<LuaObject*> lo;
    //Tabla vacia constructor
    if (exp == NULL)
    {
        lo.push_back(new LuaTable());
    }
    else
    {
        switch (exp->tn)
        {
            case _null:
            {
                lo.push_back(new LuaObject());
                break;
            }
            case _false:
            {
                lo.push_back(new LuaBoolean(false));
                break;
            }
            case _true:
            {
                lo.push_back(new LuaBoolean(true));
                break;
            }
            case _number:
            {
                lo.push_back(new LuaFloat(exp->vn.valor_double));
                break;
            }
            case _string:
            {
                string valor = exp->vn.valor_string;
                lo.push_back(new LuaString(valor));
                break;
            }
            case _id:
            {
                string id = exp->vn.valor_string;
                LuaObject* lov = Scope::getInstance()->getVariable(id); //Puede devolver nil
                lo.push_back(lov);
                break;
            }
            case _function_call:
            {
                return ejecutar_function_call(exp)->lo;
            }
            case _ppp:
            {
                //??????
                break;
            }
            case _function_body:
            {
                //??????
                break;
            }
            case _field_list:
            {
                LuaTable* loTable = new LuaTable();
                ast* field = exp->hijos[0];
                ast* field_list = exp->hijos[1];

                while (field != NULL)
                {
                    switch (field->tn)
                    {
                        case _field_1:
                        {
                            vector<LuaObject*> loKey   = atom_exp(field->hijos[0]);
                            vector<LuaObject*> loValue = atom_exp(field->hijos[1]);                           
                            if (loKey.size() == 1 && loValue.size() == 1 && loKey.front()->getType() != LuaObject::NIL)
                            {
                                LuaObject* loK = loKey.front();
                                LuaObject* loV = loValue.front();
                                loTable->setValue(loK->toString(),loV);
                            }
                            else
                            {
                                if (loKey.size() != 1 )
                                    throw "Error: La clave en las tablas deben ser una sola expresion";
                                else if (loValue.size() != 1)
                                    throw "Error: El valor en los campos de las tablas debe ser una sola expresion";
                            }
                            break;
                        }
                        case _field_2:
                        {
                            string id = field->hijos[0]->vn.valor_string;
                            vector<LuaObject*> loValue = atom_exp(field->hijos[1]);
                            if (loValue.size() == 1)
                            {
                                LuaObject* loV = loValue.front();
                                loTable->setValue(id,loV);
                            }
                            else
                            {
                                if (loValue.size() != 1)
                                    throw "Error: El valor en los campos de las tablas debe ser una sola expresion";
                            }
                            break;
                        }
                        default: //field es una exp
                        {
                            vector<LuaObject*> loResult = atom_exp(field);
                            for (vector<LuaObject*>::iterator it = loResult.begin(); it != loResult.end(); ++it)
                                loTable->setValue("",*it);
                        }
                     }
                     field = field_list != NULL ? field_list->hijos[0] : NULL;
                     field_list = field_list != NULL ? field_list->hijos[1] : NULL;
                }
                lo.push_back(loTable);
                break;
            }
            case _var_2:
            {
                LuaObject* loTValue;
                ast* prefiexp = exp->hijos[0];
                ast* index = exp->hijos[1];
                //traigo la tabla
                vector<LuaObject*> loResult = atom_exp(prefiexp);
                if (prefiexp->tn = _id)
                    loResult = atom_exp(prefiexp);
                else
                    loResult = atom_exp(prefiexp->hijos[0]);
                if (loResult.size() == 1 && loResult.front()->getType() == LuaObject::TABLE) 
                {
                    LuaTable* lotable = dynamic_cast<LuaTable*>(loResult.front());
                    //Caso .IDENTIFICADOR
                    if (index->tn == _id) {
                        loTValue = lotable->getValue(index->vn.valor_string);
                    } else //Caso expresion [ exp ]
                    {
                        vector<LuaObject*> exp = atom_exp(index);
                        string str = exp.front()->toString();
                        loTValue = lotable->getValue(str);
                    }
                } 
                else 
                {
                    if (loResult.size() == 0)
                    {
                        string error = "Error: No existe la tabla ";
                        error += prefiexp->vn.valor_string;
                        throw error;
                    }
                }                           
                lo.push_back(loTValue);
                break;
            }
            case _unop:
            {
                vector<LuaObject*> loResult = atom_exp(exp->hijos[0]);
                switch (exp->vn.tipo_op)
                {
                    //Si es LuaBoolean hace el not booleano, sino retorna false excepto en nil
                    case _not:
                    {
                        if (loResult.front()->getType() == LuaObject::NIL)
                            lo.push_back(new LuaBoolean(true));
                        else if (loResult.front()->getType() == LuaObject::BOOLEAN)
                            lo.push_back(new LuaBoolean(!(dynamic_cast<LuaBoolean*>(loResult.front())->getValue())));
                        else
                            lo.push_back(new LuaBoolean(false));
                        break;
                    }
                    //Lenght de un string
                    case _numeral:
                    {
                        if (loResult.front()->getType() == LuaObject::STRING)
                            lo.push_back(new LuaFloat((dynamic_cast<LuaString*>(loResult.front())->getValue()).length()));
                        else
                        {
                            string error;
                            if(loResult.front()->getType() == LuaObject::DOUBLE)
                                    throw "Error: Intentando obtener largo de un number";
                            else if (loResult.front()->getType() == LuaObject::NIL)
                                    throw "Error: Intentando obtener largo de nil";
                            else if (loResult.front()->getType() == LuaObject::BOOLEAN)
                                    throw "Error: Intentando obtener largo de un boolean";
                        }
                        break;
                    }
                    case _menos:
                    {
                        if (loResult.front()->getType() == LuaObject::DOUBLE)
                            lo.push_back(new  LuaFloat(-(dynamic_cast<LuaFloat*>(loResult.front())->getValue())));
                        else
                        {
                            string error;
                            if(loResult.front()->getType() == LuaObject::BOOLEAN)
                                    throw "Error: Intentando aritemtica en un boolean";
                            else if (loResult.front()->getType() == LuaObject::NIL)
                                    throw "Error: Intentando aritemtica en un nil";
                            else if (loResult.front()->getType() == LuaObject::STRING)
                                    throw "Error: Intentando aritemtica en un string";
                        }
                        break;
                    }
                    default:break;
                }
                for (int i = 0; i < loResult.size(); i++)
                {
                    delete loResult[i];
                }
                break;
            }
            case _binop:
            {
                vector<LuaObject*> loResultIzq = atom_exp(exp->hijos[0]);
                vector<LuaObject*> loResultDer = atom_exp(exp->hijos[1]);              
                switch (exp->vn.tipo_op) 
                {
                    case _or:
                    {
                        lo.push_back(&(*loResultIzq.front() || *loResultDer.front()));
                        break;
                    }
                    case _and:
                    {
                        lo.push_back(&(*loResultIzq.front() && *loResultDer.front()));
                        break;
                    }
                    case _menor:
                    {
                        lo.push_back(&(*loResultIzq.front() < *loResultDer.front()));
                        break;
                    }
                    case _mayor:
                    {
                        lo.push_back(&(*loResultIzq.front() > *loResultDer.front()));
                        break;
                    }
                    case _menorigual:
                    {
                        lo.push_back(&(*loResultIzq.front() <= *loResultDer.front()));
                        break;
                    }
                    case _mayorigual:
                    {
                        lo.push_back(&(*loResultIzq.front() >= *loResultDer.front()));
                        break;
                    }
                    case _distinto:
                    {
                        lo.push_back(&(*loResultIzq.front() != *loResultDer.front()));
                        break;
                    }
                    case _igualigual:
                    {
                        lo.push_back(&(*loResultIzq.front() == *loResultDer.front()));
                        break;
                    }
                    case _puntopunto:
                    {
                        lo.push_back(&(*loResultIzq.front() += *loResultDer.front()));
                        break;
                    }
                    case _mas:
                    {
                        lo.push_back(&(*loResultIzq.front() + *loResultDer.front()));
                        break;
                    }
                    case _menos:
                    {
                        lo.push_back(&(*loResultIzq.front() - *loResultDer.front()));
                        break;
                    }
                    case _mul:
                    {
                        lo.push_back(&(*loResultIzq.front() * *loResultDer.front()));
                        break;
                    }
                    case _div:
                    {
                        lo.push_back(&(*loResultIzq.front() / *loResultDer.front()));
                        break;
                    }
                    case _mod:
                    {
                        lo.push_back(&(*loResultIzq.front() % *loResultDer.front()));
                        break;
                    }
                    case _exp:
                    {
                        lo.push_back(&(*loResultIzq.front() ^ *loResultDer.front()));
                        break;
                    }
                    default:break;
                }                   
                for (int i = 0; i < loResultIzq.size(); i++)
                {
                    delete loResultIzq[i];
                }
                for (int i = 0; i < loResultDer.size(); i++)
                {
                    delete loResultDer[i];
                }
                break;
            }
            default:break;
        }
    }
    return lo;
}







