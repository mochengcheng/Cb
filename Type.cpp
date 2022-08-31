

#include "Type.h"
#include "IntegerType.h"
#include "DoubleType.h"
#include "VoidType.h"

bool Type::isVoid()
{
	return false;
}

bool Type::isInt()
{
	return false;
}

bool Type::isDouble()
{
	return false;
}

bool Type::isStruct()
{
	return false;
}

bool Type::isArray()
{
	return false;
}

bool Type::isPointer()
{
	return false;
}

string Type::getName()
{
	return "basetype";
}

string Type::getTypeName()
{
	return string();
}

unique_ptr<Type> CreateType(Token rhs)
{
	if (rhs.getType() == tok_kw_int)
	{
		unique_ptr<Type> pType = make_unique<IntegerType>(4, false, "");
		return move(pType);
	}
	if (rhs.getType() == tok_number)
	{
		if (-1 != rhs.getContext().find("."))
		{
			unique_ptr<Type> pType = make_unique<DoubleType>(8, "");
			return move(pType);
		}

		unique_ptr<Type> pType = make_unique<IntegerType>(4, false, "");
		return move(pType);
	}

	if (rhs.getType() == tok_kw_void)
	{
		unique_ptr<Type> pType = make_unique<VoidType>("");
		return move(pType);
	}

	return nullptr;
}
