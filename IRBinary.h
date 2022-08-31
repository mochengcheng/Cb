#pragma once

#include "base.h"
#include "IRDump.h"

class IRBlock;

class IREdge;

class IRBinary:public IRDump
{
public:
	IRBinary();
	~IRBinary();

	IRBinary(string op_, string ret_,string lhs_,string rhs_);

	virtual string EqualString();

	virtual string printIR();

	virtual int replaceVar(map<string, string>& old, string dst);

	friend class IRBlock;

	friend class IREdge;

	void setRet(string ret_);
	string getRet();

private:

	string op;
	string ret;
	string lhs;
	string rhs;
};