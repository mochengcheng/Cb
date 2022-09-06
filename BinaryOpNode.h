#pragma once

#include "base.h"
#include "Node.h"

class BinaryOpNode :public Node
{
public:
	BinaryOpNode();
	~BinaryOpNode();

	BinaryOpNode(string op, unique_ptr<Node> lhs, unique_ptr<Node> rhs);

	virtual string IR(IRBlock* ir);

	virtual string dump(ostringstream& out);

	virtual void setNodeLabel(string label);

	virtual string getNodeLabel();

	virtual NodeType GetType();

	virtual void setParentNode(Node* p);

private:
	string op;

	unique_ptr<Node> lhs;
	unique_ptr<Node> rhs;

};