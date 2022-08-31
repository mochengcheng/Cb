
#include "ReturnNode.h"
#include "IRReturn.h"

ReturnNode::ReturnNode()
{
	ret = nullptr;
}

ReturnNode::~ReturnNode()
{
}

ReturnNode::ReturnNode(unique_ptr<Node> ret)
{
	this->ret = move(ret);
}

string ReturnNode::IR(IRBlock* ir)
{
	if (nullptr == ret)
	{
		unique_ptr<IRReturn> p = make_unique<IRReturn>();
		p->setLabel(this->getNodeLabel());
		ir->AddIRDump(move(p));
	}
	else
	{
		string var = ret->IR(ir);
		unique_ptr<IRReturn> p = make_unique<IRReturn>(var);
		p->setLabel(this->getNodeLabel());
		ir->AddIRDump(move(p));
	}

	return "";
}

string ReturnNode::dump(ostringstream& out)
{
	Node::dump(out);

	if (nullptr == ret)
	{
		out << "return";
		return "";
	}
	else
	{
		string var = ret->dump(out);
		out << "return" << SPACE << var << ENDL;
		return "";
	}
}

void ReturnNode::setParentNode(Node* p)
{
	Node::setParentNode(p);
	ret->setParentNode(p);
}
