
#include "BreakNode.h"
#include "WhileNode.h"
#include "IRJump.h"

BreakNode::BreakNode()
{

}

BreakNode::~BreakNode()
{

}

string BreakNode::IR(IRBlock* ir)
{
	Node* parent = getParentNode();
	assert(parent && "parent node must be exist");

	while (parent)
	{
		if (nullptr != dynamic_cast<WhileNode*>(parent))
			break;

		parent = parent->getParentNode();
		assert(parent && "parent node must be exist");
	}

	Node* parentNext = parent->getNextNode();
	assert(parent && "parent next node must be exist");

	string label = parentNext->getNodeLabel();
	if (label.empty())
	{
		label = Node::getLabel();
		parentNext->setNodeLabel(label);
	}

	{
		unique_ptr<IRJump> p = make_unique<IRJump>(label);
		ir->AddIRDump(move(p));
	}
	
	return "";
}
