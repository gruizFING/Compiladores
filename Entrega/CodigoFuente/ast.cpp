#include "ast.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;

void error_semantico(int numero_linea, const char* token, const char* mensaje)
{
    cout << "Error semantico cerca de linea " << numero_linea << " y token " << token << ".";
    cout << mensaje;
    exit(0);
}

void ejecutar(ast* ast_start) 
{
    // ast_start tiene tipo _chunk
    // el primer hijo de ast_start tiene tipo _block
    vector<LuaObject*> lo;
    stmt_end* se = ejecutar_block(ast_start->hijos[0],lo);
    if(se != NULL) // break fuera de ciclo o return fuera de funcion
    {
        if (se->tn == _break) // ejecuto el break
        {
            error_semantico(se->line,"break","No hay ciclo para break.");
        }
        else // (stmt_res->tn == _return)
        {
            print(se->lo);
        }
    }
}

stmt_end* ejecutar_block(ast* ast_start, vector<LuaObject*> lo) 
{
    // **** SE CREA EL SCOPE DEL BLOQUE Y SE AGREGAN LOS LUA OBJECTS **** //
    Scope::getInstance()->push();
    for (vector<LuaObject*>::iterator it = lo.begin(); it != lo.end(); ++it)
        Scope::getInstance()->addLocal((*it)->getID(),(*it));
    // *********** //
    
    ast* stmt_list      = ast_start->hijos[0];
    ast* stmtend        = ast_start->hijos[1];
    stmt_end* result    = NULL;

    while (stmt_list != NULL) 
    {
        result = ejecutar_sentencia(stmt_list->hijos[0]);

        // si se ejecuta una sentencia do block end esta puede terminar en break o return 
        // terminando con la ejecucion del bloque
        if (result != NULL)
            break;

        stmt_list = stmt_list->hijos[1];
    }
    
    if(result == NULL && stmtend != NULL)
        result = ejecutar_sentencia(stmtend);
    
    // ******* SE ELIMINA EL SCOPE ********** //
    Scope::getInstance()->pop();
    
    return result;
}

stmt_end* ejecutar_sentencia(ast* stmt) 
{
    try
    {
        switch (stmt->tn) {
            case _asign:
            {
                ejecutar_asign(stmt);
                break;
            }
            case _function_call:
            {
                ejecutar_function_call(stmt);
                break;
            }
            case _block:
            {
                vector<LuaObject*> lo;
                return ejecutar_block(stmt,lo);
            }
            case _while:
                return ejecutar_while(stmt);
            case _repeat:
            {
                ejecutar_repeat(stmt);
                break;
            }
            case _if:
                return ejecutar_if(stmt);
            case _for_1:
            {
                ejecutar_for(stmt);
                break;
            }
            case _for_2:
            {
                ejecutar_for(stmt);
                break;
            }
            case _function:
            {
                ejecutar_function(stmt);
                break;
            }
            case _local_function:
            {
                ejecutar_local_function(stmt);
                break;
            }
            case _local_init:
            {
                ejecutar_local_init(stmt);
                break;
            }
            case _return:
                return ejecutar_return(stmt);
            case _break:
                return ejecutar_break(stmt);
            default:
                break;
        }
    }
    catch (const char* excep) 
    {
        cout << excep << " cerca de la linea: " << stmt->line << endl;
        exit(-1);
    }
    return NULL;
}

void ejecutar_asign(ast* asign_stmt)
{
    ast* var_list = asign_stmt->hijos[0];
    ast* exp_list = asign_stmt->hijos[1];
    string nameVar;
    
    vector<LuaObject*> exp_lov;
    
    // para la lista de expresiones atomizo las expresiones y agrego
    // el resultado en el vector exp_lov
    // recordar que una expresion puede atomizarse en varios LuaObjects
    while(exp_list != NULL)
    {
        vector<LuaObject*> aux_lov = Scope::getInstance()->atom_exp(exp_list->hijos[0]);
        // recorro el vector lo y agrego sus elementos a exp_lov
        for (vector<LuaObject*>::iterator it = aux_lov.begin(); it != aux_lov.end(); ++it)
            exp_lov.push_back(*it);
        
        exp_list = exp_list->hijos[1];
    }
    
    int i = 0; // numero de LuaObject a asignar
    while (var_list != NULL && (i+1) <= exp_lov.size())
    {
        ast* var = var_list->hijos[0];
         
        if (var->tn == _id)
        {
            nameVar = var->vn.valor_string;
            Scope::getInstance()->addGlobal(nameVar, exp_lov[i]);
        }
        else // (var->tn == _var_2)
        {
            error_semantico(asign_stmt->line,"=","Caso de gramatica no previsto por el interprete.");
        }          
        
        i++;
        var_list = var_list->hijos[1];
     }         
}

stmt_end* ejecutar_function_call(ast* function_call_stmt) 
{
    string name = function_call_stmt->hijos[0]->vn.valor_string;
    
    // EJECUCION DE PRINT //
    if(name == "print")
    {
        print(function_call_stmt->hijos[1]);
        stmt_end* stmt_res = new stmt_end();
        stmt_res->tn = _return;
        stmt_res->lo.push_back(new LuaObject());
        return stmt_res;
    }
    // ***************** //
    
    LuaObject* lof = Scope::getInstance()->getVariable(name);
    if (lof->getType() == LuaObject::FUNCTION)
    {       
        ast* function_body = dynamic_cast<LuaFunction*>(lof)->getValue();
        //***//    agregar los parametros como LuaObjects al vector local_lov
        vector<LuaObject*> local_lov; // local LuaObject vector
        ast* param_list = function_body->hijos[0];
        ast* args = function_call_stmt->hijos[1];

        vector<LuaObject*> exp_lov;

        // para la lista de expresiones atomizo las expresiones y agrego
        // el resultado en el vector exp_lov
        // recordar que una expresion puede atomizarse en varios LuaObjects
        while(args != NULL)
        {
            vector<LuaObject*> aux_lov = Scope::getInstance()->atom_exp(args->hijos[0]);

            // recorro el vector lo y agrego sus elementos a exp_lov
            for (vector<LuaObject*>::iterator it = aux_lov.begin(); it != aux_lov.end(); ++it)
                exp_lov.push_back(*it);

            args = args->hijos[1];
        }
        
        int i = 0; // numero de LuaObject a asignar
        string nameVar;
        while (param_list != NULL && (i+1) <= exp_lov.size())
        {
            ast* param = param_list->hijos[0];
            if (param->tn == _id)
            {
                nameVar = param->vn.valor_string;
                exp_lov[i]->setID(nameVar);
                local_lov.push_back(exp_lov[i]);
            }
            else // (var->tn == _var_2)
            {
                error_semantico(function_call_stmt->line,"=","Caso de gramatica no previsto por el interprete.");
            }          

            i++;
            param_list = param_list->hijos[1];
        }
        
        stmt_end* stmt_res = ejecutar_block(function_body->hijos[1], local_lov);
        if (stmt_res == NULL) // no se ejecuto ninguna sentencia return
        {
            stmt_res = new stmt_end();
            stmt_res->tn = _return;
            stmt_res->lo.push_back(new LuaObject());
        }
        return stmt_res; 
    }
    else //Error
    {
        
        
        
    }
}

stmt_end* ejecutar_while(ast* while_stmt)
{
    ast* exp    = while_stmt->hijos[0];
    ast* block  = while_stmt->hijos[1];
    vector<LuaObject*> lo;
    
    while (evaluar_exp(exp)) 
    {
        stmt_end* stmt_res = ejecutar_block(block,lo);
        if (stmt_res != NULL) // termino ejecucion del while por break o return
        {
            if (stmt_res->tn == _break) // ejecuto el break
                return NULL; // break
            else // (stmt_res->tn == _return)
                return stmt_res;
        }
    }
    
    return NULL;
}

stmt_end* ejecutar_repeat(ast* repeat_stmt) 
{
    ast* block  = repeat_stmt->hijos[0];
    ast* exp    = repeat_stmt->hijos[1];
    vector<LuaObject*> lo;
    do
    {
        stmt_end* stmt_res = ejecutar_block(block,lo);
        if (stmt_res != NULL) // termino ejecucion del repeat por break o return
        {
            if (stmt_res->tn == _break) // ejecuto el break
                return NULL; // break
            else // (stmt_res->tn == _return)
                return stmt_res;
        }
    } while(!evaluar_exp(exp));
    
    return NULL;
}

stmt_end* ejecutar_if(ast* if_stmt)
{
    ast* exp             = if_stmt->hijos[0];
    ast* block           = if_stmt->hijos[1];
    ast* opt_elseif_list = if_stmt->hijos[2];
    ast* opt_else        = if_stmt->hijos[3];

    // me muevo por las condiciones hasta encontrar una verdadera
    while (exp != NULL && !evaluar_exp(exp)) 
    {
        if (opt_elseif_list != NULL) 
        {
            exp    = opt_elseif_list->hijos[0];
            block  = opt_elseif_list->hijos[1];
            opt_elseif_list = opt_elseif_list->hijos[2];
        } 
        else
            exp = NULL;
    }

    // no encontre una condicion verdadera y tengo condicion else
    if (exp == NULL && opt_else != NULL) 
    {
        block = opt_else;
    }
    
    // si tengo una condicion verdadera o condicion else
    // ejecuto el bloque correspondiente
    if (exp != NULL || opt_else != NULL)
    {
        vector<LuaObject*> lo;
        return ejecutar_block(block, lo);
    }
    else
        return NULL;
}

void ejecutar_function(ast* function_stmt) 
{
    // agregarla al scope - nombre y ast*
    // no se 'ejecuta'
    ast* function_name = function_stmt->hijos[0]->hijos[0];
    ast* function_body = function_stmt->hijos[1];
    
    //Tipo id simple
    string name = function_name->hijos[0]->vn.valor_string;
    LuaObject* lof = new LuaFunction("",function_body);
    Scope::getInstance()->addGlobal(name, lof);
}

void ejecutar_local_function(ast* local_function_stmt) 
{
    // agregarla al scope local - nombre y ast*
    // no se 'ejecuta'
    ast* function_body = local_function_stmt->hijos[1];
    
    //Tipo id simple
    string name = local_function_stmt->hijos[0]->vn.valor_string;
    LuaObject* lof = new LuaFunction("",function_body);
    Scope::getInstance()->addLocal(name, lof);  
}

void ejecutar_local_init(ast* local_init_stmt) 
{
    ast* name_list      = local_init_stmt->hijos[0];
    ast* exp_list       = local_init_stmt->hijos[1];
    
     vector<LuaObject*> exp_lov;
    // para la lista de expresiones atomizo las expresiones y agrego
    // el resultado en el vector exp_lov
    // recordar que una expresion puede atomizarse en varios LuaObjects
    while(exp_list != NULL)
    {
        vector<LuaObject*> aux_lov = Scope::getInstance()->atom_exp(exp_list->hijos[0]);
        
        // recorro el vector lo y agrego sus elementos a exp_lov
        for (vector<LuaObject*>::iterator it = aux_lov.begin(); it != aux_lov.end(); ++it)
            exp_lov.push_back(*it);
        
        exp_list = exp_list->hijos[1];
    }
    
    int i = 0; // numero de LuaObject a asignar
    while (name_list != NULL && (i+1) <= exp_lov.size())
    {
        ast* name = name_list->hijos[0];
         
        Scope::getInstance()->addLocal(name->vn.valor_string, exp_lov[i]);      
        
        i++;
        name_list = name_list->hijos[1];
    }   
}

stmt_end* ejecutar_for(ast* for_stmt) 
{
    if(for_stmt->tn == _for_1)
    {
        ast* id         = for_stmt->hijos[0];
        ast* exp1       = for_stmt->hijos[1];
        ast* exp2       = for_stmt->hijos[2];
        ast* exp3       = for_stmt->hijos[3];
        ast* block      = for_stmt->hijos[4];
        
        vector<LuaObject*> atom_exp1 = Scope::getInstance()->atom_exp(exp1);
        vector<LuaObject*> atom_exp2 = Scope::getInstance()->atom_exp(exp2);
        vector<LuaObject*> atom_exp3;
        if(exp3 != NULL)
            atom_exp3 = Scope::getInstance()->atom_exp(exp3);
        
        if(atom_exp1.front()->getType() != LuaObject::DOUBLE)
        {
            // 'for' initial value must be a number
            error_semantico(for_stmt->line,"for","Valor inicial debe ser un numero");
        }
        else if(atom_exp2.front()->getType() != LuaObject::DOUBLE)
        {
            // 'for' limit must be a number
            error_semantico(for_stmt->line,"for","Limite debe ser un numero.");
        }
        else if((exp3 != NULL) && 
                (atom_exp3.front()->getType() != LuaObject::DOUBLE))
        {
            // 'for' step must be a number
            error_semantico(for_stmt->line,"for","Incremento debe ser un numero");
        }
        else
        {
             double var         = (dynamic_cast<LuaFloat*>(atom_exp1.front()))->getValue();
             double limit       = (dynamic_cast<LuaFloat*>(atom_exp2.front()))->getValue();
             double step = 1;
             if(exp3 != NULL)
                 step = (dynamic_cast<LuaFloat*>(atom_exp3.front()))->getValue();
        
             vector<LuaObject*> local_lov; // local LuaObject vector
             
             while ((step > 0 && var <= limit) || (step <= 0 && var >= limit))
             {
                 // una vez que se ejecuta el bloque todos los lua objects
                 // que se encuentran como variables locales son eliminados
                 // por eso se debe vaciar el vector y agregar un LuaFloat nuevo
                 local_lov.clear();
                 local_lov.push_back(new LuaFloat(id->vn.valor_string,var));
                 stmt_end* stmt_res = ejecutar_block(block, local_lov);
                 
                 if (stmt_res != NULL) // termino ejecucion for por break o return
                 {
                    if (stmt_res->tn == _break) // ejecuto el break
                        return NULL; // break
                    else // (stmt_res->tn == _return)
                        return stmt_res;
                 }
                 
                 var += step;
             }
        }
    }
    else // (for_stmt->tn == _for_2)
    {
        error_semantico(for_stmt->line,"for","Caso de gramatica no previsto por el interprete.");
    }
    return NULL;
}

stmt_end* ejecutar_return(ast* return_stmt)
{
    ast* opt_exp_list = return_stmt->hijos[0];
    stmt_end* se = new stmt_end();
    se->tn = _return;
    se->line = return_stmt->line;
    
    if(opt_exp_list == NULL)
        return se;
    
    // atomizo cada una de las expresiones de la lista de expresiones
    while(opt_exp_list != NULL)
    {
        vector<LuaObject*> lo = Scope::getInstance()->atom_exp(opt_exp_list->hijos[0]);
        
        // recorro el vector lo y agrego sus elementos a se->lo
        for (vector<LuaObject*>::iterator it = lo.begin(); it != lo.end(); ++it)
            se->lo.push_back(*it);
        
        opt_exp_list = opt_exp_list->hijos[1];
    }
    return se;
}

stmt_end* ejecutar_break(ast* break_stmt)
{
    stmt_end* se = new stmt_end();
    se->tn = _break;
    se->line = break_stmt->line;
    return se;
}

bool evaluar_exp(ast* exp)
{
    vector<LuaObject*> atom_exp1 = Scope::getInstance()->atom_exp(exp);
    
    if(atom_exp1.size() == 0)
        return false;
       
    switch (atom_exp1.front()->getType()) 
    {
        case LuaObject::BOOLEAN:
            return dynamic_cast<LuaBoolean*>(atom_exp1.front())->getValue();
        case LuaObject::DOUBLE:
            return true;
        case LuaObject::STRING:
            return true;
        case LuaObject::TABLE:
            return true;
        case LuaObject::FUNCTION:
            return true;
        default:
            return false;
    }
}

void print(ast* args)
{
    if(args == NULL)
    {
        cout << endl;
    }
    else
    {
        switch(args->tn)
        {
            case _exp_list:
            {
                vector<LuaObject*> exp_lov;
                while(args != NULL)
                {
                    vector<LuaObject*> aux_lov = Scope::getInstance()->atom_exp(args->hijos[0]);
                    for (vector<LuaObject*>::iterator it = aux_lov.begin(); it != aux_lov.end(); ++it)
                        exp_lov.push_back(*it);
                    args = args->hijos[1];
                }
                print(exp_lov);
                cout << endl;
                break;
            }
            case _string:
            {
                cout << args->vn.valor_string << endl;
                break;
            }
            case _field_list:
            {
                error_semantico(args->line,"print","Caso de gramatica no previsto por el interprete.");
            }
        }
    }
}

void print(vector<LuaObject*> exp_lov) 
{
    bool primero = true;
    for (vector<LuaObject*>::iterator it = exp_lov.begin(); it != exp_lov.end(); ++it) 
    {
        if (primero)
            primero = false;
        else {
            cout << "\t";
        }
        switch ((*it)->getType()) {
            case LuaObject::NIL:
                cout << "nil";
                break;
            case LuaObject::BOOLEAN:
            {
                if (dynamic_cast<LuaBoolean*> (*it)->getValue())
                    cout << "true";
                else
                    cout << "false";
                break;
            }
            case LuaObject::DOUBLE:
            {
                cout.precision(14);
                cout << (dynamic_cast<LuaFloat*> (*it)->getValue());
                break;
            }
            case LuaObject::STRING:
                cout << (dynamic_cast<LuaString*> (*it)->getValue());
                break;
            case LuaObject::TABLE:
                cout << endl;
                break;
            case LuaObject::FUNCTION:
                cout << (dynamic_cast<LuaFunction*> (*it)->getValue()) << endl;
                break;
            default:
                break;
        }
        delete (*it); // Libero memoria
    }
}

