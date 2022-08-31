

#include "IRStore.h"

IRStore::IRStore()
{
}

IRStore::~IRStore()
{
}

IRStore::IRStore(string s1, string s2)
{
	lhs = s1;
	rhs = s2;
}

void IRStore::IR()
{

}

string IRStore::EqualString()
{
	return printIR();
}

string IRStore::printIR()
{
	ostringstream out;

	if (!getLabel().empty())
		out << getLabel() << ENDL;

	out << TAB << "store " << rhs << ", " << lhs << ENDL;

	return out.str();
}

int IRStore::replaceVar(map<string, string>& old, string dst)
{
	int count = 0;

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

	if (lhs == rhs)
		setDel(true);

	return count;
}

string IRStore::getRhs()
{
	return rhs;
}

string IRStore::getLhs()
{
	return lhs;
}
