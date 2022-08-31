#pragma once

#include "base.h"
#include "IRDump.h"

class IRReturn :public IRDump
{
public:
	IRReturn();
	~IRReturn();

	IRReturn(string ret_);

	virtual string EqualString();

	virtual string printIR();

	virtual int replaceVar(map<string, string>& old, string dst);

private:
	string ret;
};
