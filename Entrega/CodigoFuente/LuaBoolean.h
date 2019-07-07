#ifndef LUABOOLEAN_H
#define	LUABOOLEAN_H

#include "LuaObject.h"
#include <exception>
using namespace std;

class LuaBoolean : public LuaObject
{
    private:
        bool m_value;
    public:
        LuaBoolean();
        LuaBoolean(string id, bool value);
        LuaBoolean(bool value);
        LuaBoolean(const LuaBoolean& orig);
        virtual ~LuaBoolean();
        virtual LuaObject& operator=(LuaObject & rhs);
	bool getValue() const;
	void setValue(bool value);
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

#endif	/* LUABOOLEAN_H */

