PATH=%PATH%;C:\Program Files (x86)\GnuWin32\bin
FUENTES= lex.yy.c lua.tab.cpp LookupTable.h LookupTable.cpp LuaBoolean.h LuaBoolean.cpp LuaFloat.h LuaFloat.cpp LuaFunction.h LuaFunction.cpp LuaObject.h LuaObject.cpp LuaString.h LuaString.cpp LuaTable.h LuaTable.cpp Scope.h Scope.cpp ast.hpp ast.cpp lua.l lua.ypp
obj= LookupTable.o LuaObject.o LuaFloat.o LuaBoolean.o LuaFunction.o  LuaString.o LuaTable.o Scope.o ast.o
CC= gcc
FLAGS= -lstdc++
lua_interprete: $(obj) lex.yy.c lua.tab.cpp
	$(CC) -o lua_interprete $(obj) lex.yy.c lua.tab.cpp $(FLAGS)
LuaObject.o: LuaObject.cpp
	$(CC) -c LuaObject.cpp
LuaBoolean.o: LuaBoolean.cpp
	$(CC) -c LuaBoolean.cpp
LuaFloat.o: LuaFloat.cpp
	$(CC) -c LuaFloat.cpp
LuaFunction.o: LuaFunction.cpp
	$(CC) -c LuaFunction.cpp
LuaString.o: LuaString.cpp
	$(CC) -c LuaString.cpp
LuaTable.o: LuaTable.cpp
	$(CC) -c LuaTable.cpp
LookupTable.o: LuaBoolean.o LuaFloat.o LuaFunction.o LuaObject.o LuaString.o LookupTable.cpp
	$(CC) -c LookupTable.cpp
Scope.o: lookupTable.o Scope.cpp
	$(CC) -c Scope.cpp
ast.o: Scope.o ast.cpp
	$(CC) -c ast.cpp 	
	
lex.yy.c: lua.l
	flex lua.l
lua.tab.cpp: lua.ypp
	bison -d lua.ypp

clean:
	rm $(obj)
	rm lex.yy.c
	rm lua.tab.cpp
	rm lua.tab.hpp
	rm lua_interprete.exe
rebuild:
	make clean
	make