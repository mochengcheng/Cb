#pragma once

#include "base.h"
#include "Node.h"
#include "FunctionPass.h"


class Module
{
public:
	Module();
	~Module();

	static Module* getInstance();

	void addFunctionNode(string name, unique_ptr<Node> sec);
	bool isExistFunction(string name);

	bool isStruct(string name);

	void dump();

	string getFunctionReturn(string name);

	void addFunctionPass(unique_ptr<FunctionPass> lhs);

private:

	map<string, unique_ptr<Node>> func;

	vector<unique_ptr<FunctionPass>> pass;

};
