
#include "VoidType.h"

VoidType::VoidType()
{
}

VoidType::~VoidType()
{
}

VoidType::VoidType(string name_)
{
	name = name_;
	size = 1;
}

long VoidType::getSize()
{
	return size;
}

string VoidType::getTypeName()
{
	return "void";
}

bool VoidType::isVoid()
{
	return true;
}
