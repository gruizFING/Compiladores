#ifndef AST_HPP
#define AST_HPP

#include <cstddef> /* NULL */
#include <new>
#include <iostream>
#include "Scope.h"
using namespace std;

enum tipo_nodo 	
{
	_chunk, _block, _stmt_list, _return, _break, _asign, _while, _repeat, 
        _if, _for_1, _for_2, _function, _id, _local_function, _local_init,
	_name_list, _var_list, _exp_list, _elseif_list, _var_2, _null, _false, 
        _true, _number, _string, _ppp, _function_name, _function_body,
	_function_call, _param_list_4, _field_list, _field_1, _field_2, _binop, 
        _unop
};

enum tipo_operador 	
{
	_or = 0, _and, _menor, _mayor, _menorigual, _mayorigual, _distinto, 
        _igualigual, _puntopunto, _mas, _menos, _mul, _div, _mod, _exp, 
	_not, _numeral
};

union valor_nodo{
	double valor_double;
	char* valor_string;
        bool valor_bool;
	tipo_operador tipo_op;
};

struct stmt_end
{
	tipo_nodo tn;
        vector<LuaObject*> lo;
        int line;
};

struct ast
{
	tipo_nodo tn;
	valor_nodo vn;
	struct ast* hijos[5];
	
	int line;
        
	ast(tipo_nodo t_n, int nl, ast* h1 = NULL, ast* h2 = NULL, ast* h3 = NULL, ast* h4 = NULL, ast* h5 = NULL)
	{
		tn = t_n;
		
		hijos[0] = h1;
		hijos[1] = h2;
		hijos[2] = h3;
		hijos[3] = h4;
		hijos[4] = h5;
                
                line = nl;
	}
	
	ast(tipo_nodo t_n, int nl, valor_nodo v_n)
	{
		tn = t_n;
		vn = v_n;
		
		for(int i = 0; i < 5; i ++)
			hijos[i] = NULL;
                
                line = nl;
	}
	
	ast(tipo_nodo t_n, tipo_operador t_o, int nl, struct ast* h1 = NULL, struct ast* h2 = NULL)
	{
		tn = t_n;
		vn.tipo_op = t_o;
		
		hijos[0] = h1;
		hijos[1] = h2;
		hijos[2] = NULL;
		hijos[3] = NULL;
		hijos[4] = NULL;
                
                line = nl;
	}
	
	void visit()
	{
		if(tn != _id && tn != _true && tn != _false && tn != _null && tn != _number && tn != _string &&  tn != _ppp){
		cout << "-----PADRE: "; this->DisplayType(); cout << endl;
		cout << "HIJOS: " << endl;
			for(int i = 0; i < 5; i ++)
			{
				if(hijos[i] != NULL){
					cout << i+1 << ": "; hijos[i]->DisplayType(); 
					cout << " - ";
				}
				else
				{
					cout << " NULL - ";
				}
			}
			cout << endl;
			cout << endl;
			for(int i = 0; i < 5; i ++)
			{
				if(hijos[i] != NULL){
					hijos[i]->visit(); 
				}
			}
			
		}
	}
	
	void DisplayType()
	{
		switch(tn)
		{
			case _chunk:
				cout << "chunk";
				break;
			case _block:
				cout << "block";
				break;
			case _stmt_list:
				cout << "stmt_list";
				break;
			case _asign:
				cout << "asign";
				break;
			case _function_call:
				cout << "function_call";
				break;	
			case _while:
				cout << "while";
				break;
			case _repeat:
				cout << "repeat";
				break;
			case _if:
				cout << "if";
				break;
			case _elseif_list:
				cout << "elseif_list";
				break;	
			case _for_1:
				cout << "for_1";
				break;
			case _for_2:
				cout << "for_2";
				break;
			case _function:
				cout << "function";
				break;
			case _function_name:
				cout << "function_name";
				break;
			case _function_body:
				cout << "function_body";
				break;
			case _id:
				cout << "id";
				break;
			case _number:
				cout << "number";
				break;	
			case _var_list:
				cout << "var_list";
				break;
			case _exp_list:
				cout << "exp_list";
				break;
			case _local_function:
				cout << "local_function";
				break;
			case _local_init:
				cout << "local_init";
				break;
			default:
				cout<< tn;
				break;
		}
	}
	
	static void liberar_memoria(ast* current)
	{
		if(current != NULL)
		{
			for(int i = 0; i < 5; i ++)
				liberar_memoria(current->hijos[i]);
			delete current;
		}
	}
	
	void free()
	{
		liberar_memoria(this);
	}
};
	

void error_semantico(int numero_linea, char* token, char* mensaje);

void ejecutar(ast* ast_start);

stmt_end* ejecutar_block(ast* ast_start, vector<LuaObject*> lo);

stmt_end* ejecutar_function_call(ast* function_call_stmt);

stmt_end* ejecutar_sentencia(ast* stmt);

void ejecutar_asign(ast* asign_stmt);

stmt_end* ejecutar_while(ast* while_stmt);

stmt_end* ejecutar_repeat(ast* repeat_stmt);

stmt_end* ejecutar_if(ast* if_stmt);

void ejecutar_function(ast* function_stmt);

void ejecutar_local_function(ast* local_function_stmt);

void ejecutar_local_init(ast* local_init_stmt);

stmt_end* ejecutar_for(ast* for_stmt);

stmt_end* ejecutar_return(ast* return_stmt);

stmt_end* ejecutar_break(ast* break_stmt);

bool evaluar_exp(ast* exp);

void print(ast* args);

void print(vector<LuaObject*> exp_lov);

#endif
