#pragma once

#include "Type.h"


class VoidType :public Type
{
public:
	VoidType();
	~VoidType();

	VoidType(string name_);

	long getSize();

	virtual string getTypeName();

	virtual bool isVoid();

private:
	long size; //�ֽڳ���
	string name;
};