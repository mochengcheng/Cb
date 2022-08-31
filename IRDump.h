#pragma once

#include "base.h"


class IRBlock;

//中间语言基类
class IRDump
{
public:
	IRDump();
	virtual ~IRDump();

	virtual void IR();

	virtual string EqualString();

	virtual string printIR();

	//替换变量
	virtual int replaceVar(map<string, string>&old, string dst);

	void setLabel(string s);
	string getLabel();


	void setDel(bool del_);
	bool getDel();

	friend class IRBlock;

private:
	string label;

	//是否可以删除
	bool del;
};