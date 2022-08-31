

#include "Token.h"

Token::Token()
{
	context = "";
	type = tok_unkonw;
}

Token::Token(string str, TokenType tt)
{
	context = str;
	type = tt;
}

string Token::getContext()
{
	return context;
}

TokenType Token::getType()
{
	return type;
}

bool isParameterType(TokenType type)
{
	if (tok_kw_int == type)
		return true;
	if (tok_kw_void == type)
		return true;

	return false;
}

int getOpLevel(TokenType t)
{
	if (tok_op_assign == t)
		return 2;

	if (tok_op_less == t || tok_op_greater == t)
		return 10;

	if (tok_op_plus == t || tok_op_minus == t)
		return 20;

	if (tok_op_mul == t || tok_op_div == t)
		return 40;

	return -1;
}
