#pragma once

#include <string>
#include <sstream>
#include <exception>
using namespace std;

class LuaObject
{
	private:

		string m_id;

	public:

		const static int STRING = 1;
		const static int DOUBLE = 2;
		const static int FUNCTION = 3;
                const static int BOOLEAN = 4;
                const static int TABLE = 5;
		const static int NIL = 0;

		LuaObject();
		LuaObject(string id);
		~LuaObject();
		virtual LuaObject& operator=( LuaObject& rhs);
		string getID();
		void setID(string id);		
		virtual LuaObject& operator||(LuaObject & rhs);
                virtual LuaObject& operator&&(LuaObject & rhs);
                virtual LuaObject& operator+(LuaObject & rhs);
                virtual LuaObject& operator-(LuaObject & rhs);
                virtual LuaObject& operator/(LuaObject & rhs);
                virtual LuaObject& operator*(LuaObject & rhs);
                virtual LuaObject& operator%(LuaObject & rhs);
                virtual LuaObject& operator^(LuaObject & rhs);
                virtual LuaObject& operator>(LuaObject & rhs);
                virtual LuaObject& operator<(LuaObject & rhs);
                virtual LuaObject& operator<=(LuaObject & rhs);
                virtual LuaObject& operator>=(LuaObject & rhs);
                virtual LuaObject& operator==(LuaObject & rhs);
                virtual LuaObject& operator!=(LuaObject & rhs);
                virtual LuaObject& operator+=(LuaObject & rhs);
		virtual int getType();
                virtual string toString();
};

