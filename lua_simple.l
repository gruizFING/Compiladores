%{

	//Declaraciones en C

	#include <string.h> 

	#include <stdlib.h> 

	#include "y.tab.h" /* The tokens */

	
	// numero de linea y numero de columna para el manejo de errores

	unsigned int line = 1;

	unsigned int colnum = 1;

	#define YY_USER_ACTION 

	{	

		yylloc.first_line = line;

        yylloc.first_column = colnum;                 

        colnum = colnum + yyleng;                         

        yylloc.last_column = colnum;                    

        yylloc.last_line = line;

	}



	

%}



DIGITO [0-9]

LETRA  [a-zA-Z]

ID 	   [LETRA_][LETRA_DIGITO]*


ESPACIO     [ \t\v\a]*

NATURAL     {DIGITO}+

FLOTANTE    {DIGITO}*"."{NATURAL}

EXPONENTE   ({FLOTANTE}|{NATURAL})[eE][+-]?{NATURAL}

HEXADECIMAL 0x[DIGITOa-fA-F]+







%x COMENTARIO_LINEA

%x COMENTARIO_MULTIPLES

%x XSTRINGD
%x XSTRINGS
%x XSTRINGL





%%

^#!.*     fprintf(yyout,"skipping: %s\n", yytext);

and 	  { return (AND); }

break     { return (BREAK); }

do        { return (DO); }

else      { return (ELSE); }

elseif	  { return (ELSEIF); }

end       { return (END); }

false     { return (FALSE); }

for       { return (FOR); }

function  { return (FUNCTION); }

if	      { return (IF); }

in        { return (IN); }

local     { return (LOCAL); }

nil       { return (NIL); }

not       { return (NOT); }

or        { return (OR); }

repeat    { return (REPEAT); }

return    { return (RETURN); }

then      { return (THEN); }

true      { return (TRUE); }

until     { return (UNTIL); }

while     { return (WHILE); }



"+"       { return (yytext[0]); }

"-"       { return (yytext[0]); }

"*"       { return (yytext[0]); }

"/"       { return (yytext[0]); }

"%"       { return (yytext[0]); } 

"^"       { return (yytext[0]); }

"#"       { return (yytext[0]); }

"=="      { return (IGUALIGUAL); }

"~="      { return (DISTINTO); }

"<="      { return (MENORIGUAL); }

">="      { return (MAYORIGUAL); }

"<"       { return (yytext[0]); }

">"       { return (yytext[0]); }

"="       { return (yytext[0]); }

"("       { return (yytext[0]); }

")"       { return (yytext[0]); }

"{"       { return (yytext[0]); }

"}"       { return (yytext[0]); }

"["       { return (yytext[0]); }

"]"       { return (yytext[0]); }

";"       { return (yytext[0]); }

":"       { return (yytext[0]); }

","       { return (yytext[0]); }

"."       { return (yytext[0]); }

".."      { return (PUNTOPUNTO); }

"..."     { return (PUNTOS); }



{ID}	  { setTipoString(); return (IDENTIFICADOR); }

{NATURAL}|{FLOTANTE}|{EXPONENTE}|{HEXADECIMAL} { setTipoDouble(); return (NUMERO); }

"[["({ESPACIO}\n)?   { yymore(); BEGIN(XLONGSTRING); }
\"             { yymore(); BEGIN(XSTRINGD); }
'              { yymore(); BEGIN(XSTRINGS); }




"--"	  BEGIN(COMENTARIO_LINEA);

"--[["	  BEGIN(COMENTARIO_MULTIPLES);



[ \t]	  {  }

[\n\r]	  { line++; colnum = 1; }





.	      { yyerror("Unrecognized Character"); }


<XSTRINGD>
{
  \"\"        yymore();
  \"          setTipoString(); BEGIN(0); return (STRING);
  \\[abfnrtv] yymore();
  \\\n        yymore();
  \\\"        yymore();
  \\'         yymore();
  \\"["       yymore();
  \\"]"       yymore();
  [\n|\r]     {    fprintf(yyout,"unterminated string.\n");
                      line++; colnum = 1;
                      setTipoString(); 
                      BEGIN(0);
                      return (STRING);
                  }
  .           yymore();
}

<XSTRINGS>
{
  ''          yymore();
  '           setTipoString(); BEGIN(0); return (STRING);
  \\[abfnrtv] yymore();
  \\\n        yymore();
  \\\"        yymore();
  \\'         yymore();
  \\"["       yymore();
  \\"]"       yymore();
  [\n|\r]     {    fprintf(yyout,"unterminated string.\n");
                      line++; colnum = 1;
                      setTipoString();
                      BEGIN(0);
                      return (STRING);
                  }
  .           yymore();
}

<XSTRINGL>
{
  "]]"        setTipoString(); BEGIN(0); return (STRING);
  \n          line++; colnum = 1; yymore();
  \r          line++; colnum = 1; yymore();
  .           yymore();
}





<COMENTARIO_LINEA>

{

	[\n\r]	{ colnum = 1; BEGIN(0); }

	.

}



<COMENTARIO_MULTIPLES>

{

	"]]--"	{ BEGIN(0); }

	[\n\r]	{ colnum = 1; }

	.	

}





%%



%{

	void setTipoString()

	{

		char* aux = (char*) malloc(sizeof(char) * (strlen(yytext)+1));
		strcpy(aux, yytext);
		yylval.tipoString = aux;

	}



	void setTipoDouble()

	{

		yylval.tipoDouble = strtod(yytext, NULL);

	}

	



	void yyerror (const char *s)

	{

        fprintf(stderr, "Error: %s: %s line: %d", s, yytext, yylloc.first_line);

	}	

		

%}