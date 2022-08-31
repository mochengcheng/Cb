
#include "IRCall.h"

IRCall::IRCall()
{
}

IRCall::~IRCall()
{
}

IRCall::IRCall(string ret0, string lhs1, string funcName2, vector<string>& args3)
{
	ret = ret0;
	lhs = lhs1;
	funcName = funcName2;
	args = args3;
}

string IRCall::EqualString()
{
	return printIR();
}

string IRCall::printIR()
{
	ostringstream out;

	if (!getLabel().empty())
		out << getLabel() << ENDL;

	if (lhs.empty())
	{
		out << TAB << "call " << ret << " @" << funcName << "(";
	}
	else
	{
		out << TAB << lhs<<" = "<<"call " << ret << " @" << funcName << "(";
	}

	if (args.size() > 0)
	{
		size_t len = args.size() - 1;
		for (int i = 0; i < len; i++)
		{
			out << args[i] << ", ";
		}
		out << args[len];
	}
	out << ")" << ENDL;

	return out.str();
}
