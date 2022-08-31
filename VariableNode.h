#pragma once

#include "base.h"
#include "Node.h"

class VariableNode :public Node
{
public:

	VariableNode();
	~VariableNode();

	virtual string IR(IRBlock * ir);
	virtual Type* getNodeType();

	virtual string dump(ostringstream& out);

	virtual string getName();

	void setNodeType(unique_ptr<Type> nodeType);

	void setName(string name);

private:
	unique_ptr<Type> nodeType;
	string name;
};
