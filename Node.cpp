
#include "Node.h"

int Node::sn = 0;
int Node::label_sn = 0;


Node::Node()
{
	nextNode = nullptr;
	predNode = nullptr;
	nodeLabel = "";
	parentNode = nullptr;
	tempName = "";
}

Node::~Node()
{
	nextNode = nullptr;
	predNode = nullptr;
}

void Node::IR()
{
}

string Node::IR(IRBlock * ir)
{
	return "";
}

NodeType Node::GetType()
{
	return UNKNOWN_NODE;
}

Type* Node::getNodeType()
{
	return nullptr;
}

string Node::dump(ostringstream& out)
{
	if (!nodeLabel.empty())
		out << nodeLabel <<":" << ENDL;

	return "";
}

string Node::getName()
{
	return "";
}

void Node::clearSN()
{
	sn = 0;
}

string Node::getSN()
{
	ostringstream out;
	out << "%" << sn++;
	return out.str();
}

void Node::clearLabel()
{
	label_sn = 0;
}

string Node::getLabel()
{
	ostringstream out;
	out << "label" << label_sn++;
	return out.str();
}

void Node::setNextNode(Node* p)
{
	nextNode = p;
}

Node* Node::getNextNode()
{
	return nextNode;
}

void Node::setPredNode(Node* p)
{
	predNode = p;
}

Node* Node::getPredNode()
{
	return predNode;
}

void Node::setParentNode(Node* p)
{
	parentNode = p;
}

Node* Node::getParentNode()
{
	return parentNode;
}

string Node::getNodeLabel()
{
	return nodeLabel;
}

IRBlock* Node::getIR()
{
	return nullptr;
}

void Node::setTempName(string name)
{
	tempName = name;
}

string Node::getTempName()
{
	return tempName;
}

void Node::setNodeLabel(string label)
{
	nodeLabel = label;
}

