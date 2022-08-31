#pragma once

#include "base.h"
#include "IRDump.h"

class IREdge;

class IRStore :public IRDump
{
public:
	IRStore();
	~IRStore();
	IRStore(string lhs_, string rhs_);

	virtual void IR();

	virtual string EqualString();

	virtual string printIR();

	virtual int replaceVar(map<string, string>& old, string dst);

	friend class IREdge;

	string getRhs();

	string getLhs();

private:
	//×óÖµ
	string lhs;
	//ÓÒÖµ
	string rhs;

};