#pragma once

#include "base.h"
#include "FunctionPass.h"

//优化不动点
class FixPointPass :public FunctionPass
{
public:
	FixPointPass();
	~FixPointPass();

	virtual void runOnFunction(IRBlock* ir);
};