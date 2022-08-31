#pragma once

#include "Type.h"

class IntegerType :public Type
{
public:
	IntegerType(long size, bool isSigned, string name);
	~IntegerType();

	virtual bool isInt();

	long getSize();

	bool getSigned();

	virtual string getName();
	virtual void setName(string name);

	virtual string getTypeName();

private:
	long size; //×Ö½Ú³¤¶È
	bool isSigned;
	string name;
};