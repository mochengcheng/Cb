#pragma once

#include "base.h"
#include "Node.h"


class CallFuncNode :public Node
{
public:
	CallFuncNode();
	~CallFuncNode();

	CallFuncNode(string name,string retType_ = "void");

	virtual string IR(IRBlock* ir);

	virtual string dump(ostringstream& out);

	void setCallName(string name);
	string getCallName();

	void addArgs(unique_ptr<Node> arg);

private:

	string callName;

	vector<unique_ptr<Node>> Args;

	//∑µªÿ¿‡–Õ
	string retType;
		
};