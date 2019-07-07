#pragma once

#include "LuaObject.h"
//#include <string>
//using std::string;

class LuaString: public LuaObject
{

	private:
		string m_value;
	public:
		LuaString();
                LuaString(string value);
		LuaString(string id, string value);
		~LuaString();
		virtual LuaObject& operator=(LuaObject & rhs);
		void setValue(string value);
		string getValue() const;
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
