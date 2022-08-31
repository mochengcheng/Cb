#pragma once

#include "base.h"
#include "Node.h"

class ReturnNode :public Node
{
public:
	ReturnNode();
	~ReturnNode();


	ReturnNode(unique_ptr<Node> ret);

	virtual string IR(IRBlock* ir);

	virtual string dump(ostringstream& out);

	virtual void setParentNode(Node* p);

private:
	unique_ptr<Node> ret;
};