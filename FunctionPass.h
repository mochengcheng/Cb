#pragma once

#include "base.h"
#include "IRBlock.h"
#include "IRReturn.h"
#include "IRJump.h"

//优化基类
class FunctionPass
{
public:
	FunctionPass();
	~FunctionPass();

	virtual void runOnFunction(IRBlock * ir);

};