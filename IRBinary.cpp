
#include "IRBinary.h"
#include "IROp.h"

IRBinary::IRBinary()
{
}

IRBinary::~IRBinary()
{
}

IRBinary::IRBinary(string op_, string ret_, string lhs_, string rhs_)
{
	op = op_;
	ret = ret_;
	lhs = lhs_;
	rhs = rhs_;
}

string IRBinary::EqualString()
{
	return printIR();
}

string IRBinary::printIR()
{
	ostringstream out;
	if (!getLabel().empty())
		out << getLabel() << ENDL;

	char szMsg[128] = { 0 };

	sprintf(szMsg, "%s = %s %s, %s", ret.data(), FormatOp(op).data(), lhs.data(), rhs.data());
	out << TAB << szMsg<< ENDL;
	return out.str();
}

int IRBinary::replaceVar(map<string, string>& old, string dst)
{
	int count = 0;

	if (old.find(ret) != old.end())
	{
		ret = dst;
		count++;
	}


	if (old.find(lhs) != old.end())
	{
		lhs = dst;
		count++;
	}

	if (old.find(rhs) != old.end())
	{
		rhs = dst;
		count++;
	}

	return count;
}

void IRBinary::setRet(string ret_)
{
	ret = ret_;
}

string IRBinary::getRet()
{
	return ret;
}
