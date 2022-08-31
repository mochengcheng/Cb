#pragma once

#include "base.h"
#include "Node.h"


class BreakNode:public Node
{
public:
	BreakNode();
	~BreakNode();

	virtual string IR(IRBlock* ir);

};