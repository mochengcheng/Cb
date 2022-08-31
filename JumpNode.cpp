

#include "JumpNode.h"

JumpNode::JumpNode()
{
}

JumpNode::~JumpNode()
{
}

string JumpNode::IR(IRBlock* ir)
{
	return "";
}

string JumpNode::dump(ostringstream& out)
{
	out <<"jump" << SPACE << getNodeLabel() << endl;
	return "";
}
