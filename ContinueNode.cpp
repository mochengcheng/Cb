
#include "ContinueNode.h"
#include "IRJump.h"
#include "WhileNode.h"

ContinueNode::ContinueNode()
{

}

ContinueNode::~ContinueNode()
{

}

string ContinueNode::IR(IRBlock* ir)
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

	string label = parent->getNodeLabel();
	if (label.empty())
	{
		label = Node::getLabel();
		parent->setNodeLabel(label);
	}

	{
		unique_ptr<IRJump> p = make_unique<IRJump>(label);
		ir->AddIRDump(move(p));
	}


	return "";
}
