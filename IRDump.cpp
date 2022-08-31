
#include "IRDump.h"

IRDump::IRDump()
{
    del = false;
}

IRDump::~IRDump()
{
}

void IRDump::IR()
{
}

string IRDump::EqualString()
{
    return "";
}

string IRDump::printIR()
{
    return string();
}

int IRDump::replaceVar(map<string, string>& old, string dst)
{
    return 0;
}

void IRDump::setLabel(string s)
{
    label = s;
}

string IRDump::getLabel()
{
    if (label.empty())
        return "";

    if ("entry" == label)
        return label + ":";

    return "\r\n"+label + ":";
}

void IRDump::setDel(bool del_)
{
    del = del_;
}

bool IRDump::getDel()
{
    return del;
}
