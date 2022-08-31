#pragma once

#include "base.h"
#include "Node.h"


class ContinueNode :public Node
{
public:
	ContinueNode();
	~ContinueNode();


	virtual string IR(IRBlock* ir);

private:
};