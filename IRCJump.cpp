
#include "IRCJump.h"

IRCJump::IRCJump()
{
}

IRCJump::~IRCJump()
{
}

IRCJump::IRCJump(string cond_, string label1_, string label0_)
{
	cond = cond_;
	label1 = label1_;
	label0 = label0_;
}

string IRCJump::EqualString()
{
	return printIR();
}

string IRCJump::printIR()
{
	ostringstream out;
	if (!getLabel().empty())
		out << getLabel() << ENDL;

	// br i1 %cmp, label %if.then, label %if.end
	char szMsg[128] = { 0 };

	sprintf(szMsg, "br %s, %s, %s", cond.data(), label1.data(), label0.data());

	out << TAB << szMsg<< ENDL;
	return out.str();
}

int IRCJump::replaceVar(map<string, string>& old, string dst)
{
	int ref = 0;
	if (old.find(cond) != old.end())
	{
		cond = dst;
		ref++;
	}

	return ref;
}

string IRCJump::getLabel1()
{
	return label1;
}

string IRCJump::getLabel0()
{
	return label0;
}
