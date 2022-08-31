#pragma once

#include "base.h"
#include "IRDump.h"


class IRLabel :public IRDump
{
public:
	IRLabel();
	~IRLabel();

	IRLabel(string label_);

	virtual string EqualString();
	virtual string printIR();

private:
	string label_temp;

};