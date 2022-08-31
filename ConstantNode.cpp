
#include "ConstantNode.h"

ConstantNode::ConstantNode()
{
	value = "";
	nodeType = nullptr;
}

ConstantNode::~ConstantNode()
{
}

ConstantNode::ConstantNode(unique_ptr<Type> nodeType, string value)
{
	this->nodeType = move(nodeType);
	this->value = value;
}

string ConstantNode::IR(IRBlock* ir)
{
	return value;
}

string ConstantNode::dump(ostringstream& out)
{
	Node::dump(out);

	return value;
}

Type* ConstantNode::getNodeType()
{
	return nodeType.get();
}

string ConstantNode::getName()
{
	return value;
}

void ConstantNode::setNodeType(unique_ptr<Type> nodeType)
{
	this->nodeType = move(nodeType);
}

void ConstantNode::setValue(string value)
{
	this->value = value;
}
