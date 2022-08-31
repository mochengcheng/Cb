
#include "IRReturn.h"

IRReturn::IRReturn()
{
}

IRReturn::~IRReturn()
{
}

IRReturn::IRReturn(string ret_)
{
	ret = ret_;
}

string IRReturn::EqualString()
{
	return printIR();
}

string IRReturn::printIR()
{
	ostringstream out;
	if (!getLabel().empty())
		out << getLabel() << ENDL;

	char szMsg[128] = { 0 };
	sprintf(szMsg, "ret %s", ret.data());

	out << TAB << szMsg<< ENDL;
	return out.str();
}

int IRReturn::replaceVar(map<string, string>& old, string dst)
{
	int ref = 0;

	if (old.find(ret) != old.end())
	{
		ret = dst;
		ref++;
	}

	return ref;
}
