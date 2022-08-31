#pragma once

#include "base.h"
#include "IRDump.h"

class IRBlock;

class IRAlloca :public IRDump
{
public:
	IRAlloca();
	~IRAlloca();

	IRAlloca(string lhs_, string type_, long align_);

	virtual string EqualString();

	virtual string printIR();

	virtual int replaceVar(map<string, string>& old, string dst);

	friend class IRBlock;

	string getLhs();
	void setLhs(string lhs_);

private:
	//×óÖµ
	string lhs;

	string type;

	long align;
};
