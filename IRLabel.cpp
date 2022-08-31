
#include "IRLabel.h"

IRLabel::IRLabel()
{
}

IRLabel::~IRLabel()
{
}

IRLabel::IRLabel(string label_)
{
	setLabel(label_);
	label_temp = label_;
}

string IRLabel::EqualString()
{
	return printIR();
}

string IRLabel::printIR()
{
	string l = getLabel();
	assert(!l.empty() && "IRLabel label is null");

	l += "\r\n";

	return l;
}
