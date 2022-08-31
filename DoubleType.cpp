

#include "DoubleType.h"

DoubleType::DoubleType(long size, string name)
{
	this->size = size;
	this->name = name;
}

DoubleType::~DoubleType()
{
}

bool DoubleType::isDouble()
{
	return true;
}

long DoubleType::getSize()
{
	return size;
}

string DoubleType::getName()
{
	return name;
}

void DoubleType::setName(string name)
{
	this->name = name;
}

string DoubleType::getTypeName()
{
	return "double";
}
