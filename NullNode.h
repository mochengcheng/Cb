#pragma once

#include "base.h"
#include "Node.h"

//�սڵ㣬�����{}��û���������
class NullNode :public Node
{
public:
	NullNode();
	~NullNode();

	virtual string IR(IRBlock* ir);
};
