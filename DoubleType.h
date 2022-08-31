#pragma once


#include "Type.h"

class DoubleType :public Type
{
public:
	DoubleType(long size, string name);
	~DoubleType();

	virtual bool isDouble();

	long getSize();

	virtual string getName();
	virtual void setName(string name);

	virtual string getTypeName();

private:
	long size; //�ֽڳ���
	string name;
};