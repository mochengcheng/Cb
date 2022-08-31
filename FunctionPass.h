#pragma once

#include "base.h"
#include "IRBlock.h"
#include "IRReturn.h"
#include "IRJump.h"

//�Ż�����
class FunctionPass
{
public:
	FunctionPass();
	~FunctionPass();

	virtual void runOnFunction(IRBlock * ir);

};