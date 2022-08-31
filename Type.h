#pragma once

#include "base.h"
#include "Token.h"

class Type
{
public:
	Type() {}
	~Type() {}

	virtual bool isVoid();

	virtual bool isInt();

	virtual bool isDouble();

	virtual bool isStruct();

	virtual bool isArray();

	virtual bool isPointer();

	virtual void setName(string name) {};

	virtual string getName();

	virtual string getTypeName();

};

unique_ptr<Type> CreateType(Token rhs);