#pragma once

#include "base.h"
#include "FunctionPass.h"

//�Ż�������
class FixPointPass :public FunctionPass
{
public:
	FixPointPass();
	~FixPointPass();

	virtual void runOnFunction(IRBlock* ir);
};