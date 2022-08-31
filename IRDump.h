#pragma once

#include "base.h"


class IRBlock;

//�м����Ի���
class IRDump
{
public:
	IRDump();
	virtual ~IRDump();

	virtual void IR();

	virtual string EqualString();

	virtual string printIR();

	//�滻����
	virtual int replaceVar(map<string, string>&old, string dst);

	void setLabel(string s);
	string getLabel();


	void setDel(bool del_);
	bool getDel();

	friend class IRBlock;

private:
	string label;

	//�Ƿ����ɾ��
	bool del;
};