

#include "IntegerType.h"

IntegerType::IntegerType(long size, bool isSigned, string name)
{
	this->size = size;
	this->isSigned = isSigned;
	this->name = name;
}

IntegerType::~IntegerType()
{
}

bool IntegerType::isInt()
{
	return true;
}

long IntegerType::getSize()
{
	return size;
}

bool IntegerType::getSigned()
{
	return isSigned;
}

string IntegerType::getName()
{
	return name;
}

void IntegerType::setName(string name)
{
	this->name = name;
}

string IntegerType::getTypeName()
{
	return "int";
}
