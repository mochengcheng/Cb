
#include "NullNode.h"
#include "IRJump.h"

NullNode::NullNode()
{

}

NullNode::~NullNode()
{
}

string NullNode::IR(IRBlock* ir)
{
	Node* parent = getParentNode();
	Node* nextNode = parent->getNextNode();

	string l = nextNode->getNodeLabel();
	if (l.empty())
	{
		l = getLabel();
		nextNode->setNodeLabel(l);
	}

	{
		unique_ptr<IRJump> pL = make_unique<IRJump>(l);
		ir->AddIRDump(move(pL));
	}

	return "";
}
