
#include "IRAlloca.h"

IRAlloca::IRAlloca()
{
}

IRAlloca::~IRAlloca()
{
}

IRAlloca::IRAlloca(string lhs_, string type_, long align_)
{
	lhs = lhs_;
	type = type_;
	align = align_;
}

string IRAlloca::EqualString()
{
	return printIR();
}

string IRAlloca::printIR()
{
	ostringstream out;

	if (!getLabel().empty())
		out << getLabel() << ENDL;

	//% retval = alloca i32, align 4
	char szMsg[128] = {0};
	sprintf(szMsg, "%s = alloca %s, align %ld", lhs.data(), type.data(), align);

	out << TAB << szMsg<< ENDL;

	return out.str();
}

int IRAlloca::replaceVar(map<string, string>& old, string dst)
{
	int count = 0;
	if (old.find(lhs) != old.end())
	{
		lhs = dst;
		count++;
	}

	return count;
}

string IRAlloca::getLhs()
{
	return lhs;
}

void IRAlloca::setLhs(string lhs_)
{
	lhs = lhs_;
}
