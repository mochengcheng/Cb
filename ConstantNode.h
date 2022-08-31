#pragma once

#include "base.h"
#include "Node.h"
#include "IntegerType.h"


class ConstantNode :public Node
{
public:
	ConstantNode();
	~ConstantNode();

	ConstantNode(unique_ptr<Type> nodeType, string value);

	virtual string IR(IRBlock* ir);
	virtual Type* getNodeType();

	virtual string getName();

	virtual string dump(ostringstream& out);

	void setNodeType(unique_ptr<Type> nodeType);
	void setValue(string value);

private:
	unique_ptr<Type> nodeType;
	string value;
};