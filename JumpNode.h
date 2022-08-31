#pragma once

#include "base.h"
#include "Node.h"


class JumpNode :public Node
{
public:
	JumpNode();
	~JumpNode();


	virtual string IR(IRBlock* ir);

	virtual string dump(ostringstream& out);


};