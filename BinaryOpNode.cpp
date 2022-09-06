

#include "BinaryOpNode.h"
#include "IRStore.h"
#include "IRBinary.h"
#include "IRLabel.h"

BinaryOpNode::BinaryOpNode()
{
}

BinaryOpNode::~BinaryOpNode()
{
}

BinaryOpNode::BinaryOpNode(string op, unique_ptr<Node> lhs, unique_ptr<Node> rhs)
{
	this->op = op;
	this->lhs = move(lhs);
	this->rhs = move(rhs);
}

string BinaryOpNode::IR(IRBlock* ir)
{
	{
		string l = getNodeLabel();
		if (!l.empty())
		{
			unique_ptr<IRLabel> pL = make_unique<IRLabel>(l);
			ir->AddIRDump(move(pL));
		}
	}
	{
		Node* parent = getParentNode();
		string l = parent->getNodeLabel();
		if (!l.empty())
		{
			unique_ptr<IRLabel> pL = make_unique<IRLabel>(l);
			ir->AddIRDump(move(pL));
		}
	}
	string s1 = lhs->IR(ir);
	string s2 = rhs->IR(ir);

	if (s1.empty())
		s1 = lhs->getName();

	if (op == "=")
	{
		unique_ptr<IRStore> p = make_unique<IRStore>(s1, s2);
		ir->AddIRDump(move(p));
	}
	else
	{
		string tmp = Node::getSN();
		unique_ptr<IRBinary> p = make_unique<IRBinary>(op, tmp, s1, s2);
		ir->AddIRDump(move(p));
		return tmp;
	}

	return "";
}

string BinaryOpNode::dump(ostringstream& out)
{
	Node::dump(out);

	string s1 = lhs->dump(out);
	string s2 = rhs->dump(out);

	if (s1.empty())
		s1 = lhs->getName();

	string s3 = s1 + SPACE + op + SPACE + s2;

	s1 = "";
	if (op != "=")
	{
		s1 = Node::getSN();
		s3 = s1 + SPACE + "=" + SPACE + s3;
	}
	out << s3 << ENDL;

	return s1;
}

void BinaryOpNode::setNodeLabel(string label)
{
	//lhs->setNodeLabel(label);
	rhs->setNodeLabel(label);
}

string BinaryOpNode::getNodeLabel()
{
	return rhs->getNodeLabel();
}

NodeType BinaryOpNode::GetType()
{
	return BINARYOP_NODE;
}

void BinaryOpNode::setParentNode(Node* p)
{
	Node::setParentNode(p);
	lhs->setParentNode(p);
	rhs->setParentNode(p);
}
