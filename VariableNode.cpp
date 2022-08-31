
#include "VariableNode.h"
#include "IRAlloca.h"
#include "IntegerType.h"
#include "DoubleType.h"

VariableNode::VariableNode()
{
	nodeType = nullptr;
	name = "";
}

VariableNode::~VariableNode()
{
}

string VariableNode::IR(IRBlock * ir)
{
	if (nullptr != nodeType)
	{
		if (nodeType->isInt())
		{
			IntegerType* pType = dynamic_cast<IntegerType*>(nodeType.get());
			unique_ptr<IRAlloca> p = make_unique<IRAlloca>(name, "int", pType->getSize());
			p->setLabel(getNodeLabel());
			ir->AddIRDump(move(p));
		}
		else if (nodeType->isDouble())
		{
			DoubleType* pType = dynamic_cast<DoubleType*>(nodeType.get());
			unique_ptr<IRAlloca> p = make_unique<IRAlloca>(name, "double", pType->getSize());
			p->setLabel(getNodeLabel());
			ir->AddIRDump(move(p));
		}
		else
		{
			assert(0 && "VariableNode IR Error");
		}
	}
	else
		return name;

	return "";
}

Type* VariableNode::getNodeType()
{
	return nodeType.get();
}

string VariableNode::dump(ostringstream& out)
{
	Node::dump(out);

	
	if (nullptr != nodeType)
	{
		if (nodeType->isInt())
			out << "int"<< SPACE << name << ENDL;
		else if (nodeType->isDouble())
			out << "double"<< SPACE << name << ENDL;

		return "";
	}
	
	
	return name;

}

void VariableNode::setNodeType(unique_ptr<Type> nodeType)
{
	this->nodeType = move(nodeType);
}

string VariableNode::getName()
{
	return name;
}

void VariableNode::setName(string name)
{
	this->name = "%" + name;
}
