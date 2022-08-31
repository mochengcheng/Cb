

#include "CallFuncNode.h"
#include "IRCall.h"

CallFuncNode::CallFuncNode()
{
	retType = "void";
}

CallFuncNode::~CallFuncNode()
{
}

CallFuncNode::CallFuncNode(string name, string retType_)
{
	callName = name;
	retType = retType_;
}

string CallFuncNode::IR(IRBlock* ir)
{
	vector<string> arg;

	for (auto& it : Args)
	{
		string s1 = it->IR(ir);
		arg.push_back(s1);
	}

	string tmp;
	if ("void" != retType)
		tmp = Node::getSN();

	unique_ptr<IRCall> p = make_unique<IRCall>(retType, tmp, callName, arg);
	ir->AddIRDump(move(p));

	return tmp;
}

string CallFuncNode::dump(ostringstream& out)
{
	Node::dump(out);

	string s1=  "call" + string(SPACE) + "@" + callName + "(";

	for (size_t i = 0; i < Args.size() - 1; i++)
	{
		s1 += Args[i]->getName() + "," + string(SPACE);
	}
	if (Args.size() > 0)
	{
		size_t i = Args.size() - 1;
		s1 += Args[i]->getName() + ")";
	}

	return s1;
}

void CallFuncNode::setCallName(string name)
{
	callName = name;
}

string CallFuncNode::getCallName()
{
	return callName;
}

void CallFuncNode::addArgs(unique_ptr<Node> arg)
{
	Args.push_back(move(arg));
}
