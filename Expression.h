#pragma once


#include "base.h"
#include "Parser.h"
#include "Node.h"
#include "ReturnNode.h"

//解析表达式
class Expression
{
public:
	Expression();
	~Expression();

	Expression(TokenQueue* p);

	void setTokenQueue(TokenQueue* p);

	unique_ptr<Node> CreateExpression();

	unique_ptr<Node> CreateExpression(unique_ptr<Node> lhs);

private:
	//一元
	unique_ptr<Node> CreateUnary();
	//二元
	unique_ptr<Node> CreateBinaryOp(int ExprPrec, unique_ptr<Node> lhs);

	unique_ptr<Node> CreatePrimary();

	unique_ptr<Node> CreateCallFunc();

	unique_ptr<Node> CreateStruct();

	unique_ptr<Node> CreateIdentifier();

	unique_ptr<Node> CreateConstant();

	unique_ptr<Node> CreateParent();

	unique_ptr<Node> CreateReturn();


private:
	TokenQueue* pToken;
};