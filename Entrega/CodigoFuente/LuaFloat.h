#pragma once

#include "LuaObject.h"

class LuaFloat: public LuaObject
{
private:
	double m_value;

public:
	LuaFloat();
        LuaFloat(double value);
	LuaFloat(string id, double value);
	~LuaFloat();
	virtual LuaObject& operator=(LuaObject & rhs);
	double getValue() const;
	void setValue(double value);
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
