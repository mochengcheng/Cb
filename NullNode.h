#pragma once

#include "base.h"
#include "Node.h"

//空节点，针对是{}中没有语句类型
class NullNode :public Node
{
public:
	NullNode();
	~NullNode();

	virtual string IR(IRBlock* ir);
};
