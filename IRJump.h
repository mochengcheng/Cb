#pragma once

#include "IRDump.h"

//无条件跳转
class IRJump :public IRDump
{
public:
	IRJump();
	~IRJump();

	IRJump(string label_);

	virtual string EqualString();

	virtual string printIR();

private:

	string jumpLabel;

};

