#pragma once

#include "IRDump.h"

//��������ת
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

