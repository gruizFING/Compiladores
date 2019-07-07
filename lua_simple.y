%{
//Declaraciones en C




%}

%union {
	double tipoDouble
	char* tipoString
}

%token AND BREAK DO ELSE ELSEIF END TRUE FALSE FOR FUNCTION IF IN LOCAL NIL NOT OR
%token REPEAT RETURN THEN UNTIL WHILE

%token <tipoString> IDENTIFICADOR
%token <tipoDouble> NUMERO
%token <tipoString> STRING

%left OR
%left AND
%left '<' '>' MENORIGUAL MAYORIGUAL DISTINTO IGUALIGUAL
%left PUNTOPUNTO
%left '+' '-'
%left '*' '/' '%'
%left NOT '#' '-'
%right '^'

%%

chunk		: block
			;

block	 	: stmt_list stmt_end
			;

/* Lista de sentencias, ';' opcional */

stmt_list	: /* empty */
			| stmt_list stmt opt_semicolon										
			;

/* Las ordenes return y break pueden aparecer solo como ultima sentencia dentro de un bloque. Cambia en Version 5.2 */

stmt_end	: /* empty */
			| RETURN opt_exp_list opt_semicolon
			| BREAK opt_semicolon
			;

opt_semicolon	: /* empty */
				| ';'
				;

stmt 	: var_list '=' exp_list
		| functioncall
		| DO block END
		| WHILE exp DO block END
		| REPEAT block UNTIL exp
		| IF exp THEN block opt_elseif_list opt_else END
		| FOR for_stmt
		| FUNCTION function_name funcbody								
		| LOCAL FUNCTION IDENTIFICADOR funcbody
		| LOCAL name_list initializer
		;

name_list	: IDENTIFICADOR
			| name_list ',' IDENTIFICADOR
			;

initializer	: /* empty */
			| '=' exp_list
			;

var_list	: var
			| var_list ',' var 
			;

exp_list	: exp
			| exp_list ',' exp
			;

opt_exp_list	: /* empty */
				| exp_list
				;
				
opt_elseif_list	: /* empty */
				| opt_elseif_list ELSEIF exp THEN block
				;

opt_else	: /* empty */
			| ELSE block
			;
			
for_stmt	: IDENTIFICADOR '=' exp ',' exp opt_comma_expr DO block END				/* OTROS CASOS */
			| name_list IN exp_list DO block END
			;
			
opt_comma_expr	: /* empty */
				| ',' exp
				;
			
var 	: IDENTIFICADOR 
		| prefixexp index
		;

index	: '[' exp ']'
		| '.' IDENTIFICADOR
		;

exp 	: NIL 
		| FALSE 
		| TRUE 
		| NUMERO 
		| STRING
		| PUNTOPUNTOPUNTO /* '...' */
		| FUNCTION funcbody 
		| prefixexp 
		| table_constructor 
		| exp binop exp 
		| unop exp
		;
		
prefixexp 	: var 
			| functioncall 
			| '(' exp ')'
			;

function_name	: dotted_name_list opt_colon_name
				;

dotted_name_list	: IDENTIFICADOR
					| dotted_name_list '.' IDENTIFICADOR
					;

opt_colon_name	: /* empty */
				| ':' IDENTIFICADOR
				;

funcbody 		: '(' param_list ')' block END
				;

functioncall	: prefixexp args 
				| prefixexp ':' IDENTIFICADOR args
				;

args	: '(' opt_exp_list ')'
		| table_constructor 
		| STRING
		;

param_list 	: /* empty */
			| PUNTOPUNTOPUNTO
			| name_list
			| name_list ',' PUNTOPUNTOPUNTO
			;

table_constructor	: '{' table_contents '}'
;

table_contents	: /* empty */
				| field_list opt_field_sep
				;

field_list 	: field
			| field_list fieldsep field 									/* OTROS CASOS (fieldsep al final ) */
			;

field 	: '[' exp ']' '=' exp 
		| IDENTIFICADOR '=' exp 
		| exp															/* ANALIZAR CASO */
		;

opt_field_sep	: /* empty */
				| fieldsep
				;

fieldsep 	: ',' 
			| ';'
			;

binop 	: OR
		| AND
		| '<'
		| '>'
		| MENORIGUAL
		| MAYORIGUAL
		| DISTINTO
		| IGUALIGUAL
		| PUNTOPUNTO
		| '+'
		| '-'
		| '*'
		| '/'
		| '%'
		| '^'
		;

unop 	: NOT
		| '#'
		| '-'
		;

%%








