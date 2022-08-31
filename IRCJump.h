#pragma once

#include "base.h"
#include "IRDump.h"

class IREdge;

class IRCJump :public IRDump
{
public:
	IRCJump();
	~IRCJump();


	IRCJump(string cond_,string label1_,string label0_);

	virtual string EqualString();

	virtual string printIR();

	virtual int replaceVar(map<string, string>& old, string dst);

	string getLabel1();

	string getLabel0();

	friend class IREdge;
private:

	string cond;
	string label1;
	string label0;

};