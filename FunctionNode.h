#pragma once

#include "base.h"
#include "Node.h"
#include "IRBlock.h"

struct ParamArg
{
	string name;
	unique_ptr<Type> type;
};

class FunctionNode :public Node
{

public:
	FunctionNode();
	~FunctionNode();

	FunctionNode(unique_ptr<Type> rhs_ret, string rhs_name, vector<unique_ptr<ParamArg>> rhs_args);

	virtual void IR();

	virtual string dump(ostringstream& out);

	virtual void setName(string name);

	virtual Type* getNodeType();

	void setRetType(unique_ptr<Type> ret);
	
	void addArg(unique_ptr<ParamArg> arg);

	void addBlockNode(unique_ptr<Node> node);

	void CreateNodeLink();

	virtual IRBlock* getIR();

	Type* getVarType(string s);

	vector<unique_ptr<Node>>& getBody() { return body; }
private:

	//返回类型
	unique_ptr<Type> retType;
	string name;
	//参数名
	vector<unique_ptr<ParamArg>> args;

	vector<unique_ptr<Node>> body;

	unique_ptr<IRBlock> ir;
};