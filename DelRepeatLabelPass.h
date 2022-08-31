#pragma once


#include "base.h"
#include "FunctionPass.h"

class DelRepeatLabelPass :public FunctionPass
{
public:
	DelRepeatLabelPass();
	~DelRepeatLabelPass();

	virtual void runOnFunction(IRBlock* ir);

};