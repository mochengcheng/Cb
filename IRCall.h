#pragma once

#include "base.h"
#include "IRDump.h"

class IRBlock;

class IRCall :public IRDump
{
public:
	IRCall();
	~IRCall();

	IRCall(string ret0, string lhs1,string funcName2, vector<string> &args3);


	virtual string EqualString();

	virtual string printIR();

	friend class IRBlock;

private:

	string ret;

	//×óÖµ
	string lhs;

	string funcName;

	vector<string> args;
};