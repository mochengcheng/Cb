
#include "IRJump.h"

IRJump::IRJump()
{
}

IRJump::~IRJump()
{
}

IRJump::IRJump(string label_)
{
	jumpLabel = label_;
	setLabel(label_);
}

string IRJump::EqualString()
{
	return printIR();
}

string IRJump::printIR()
{
	assert(!jumpLabel.empty() && "jump label is null");

	ostringstream out;
	out << TAB << "jump "<< jumpLabel<<ENDL;
	return out.str();
}
