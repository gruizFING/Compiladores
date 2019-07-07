#pragma once

#include "LuaObject.h"
#include "ast.hpp"


class LuaFunction: public LuaObject
{
	private:
		struct ast* func_body;
	public:
		LuaFunction();
		LuaFunction(string id, struct ast* funcBody);
		~LuaFunction();
		virtual LuaObject& operator=(LuaObject& rhs);
		ast* getValue();
		virtual int getType();
};
