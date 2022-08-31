#pragma once

#include "base.h"
#include "Node.h"
#include "FunctionNode.h"
#include "Parser.h"
#include "IFNode.h"
#include "WhileNode.h"


class DriverAction
{
public:
	~DriverAction();

	static DriverAction* getInstance();


	void Lexer(const char* pFile);

	FunctionNode* getCurFunPoint();

private:
	DriverAction();

	void CreateAST(unique_ptr<MyParser> parser);

private:
	unique_ptr<FunctionNode> CreateFunctionNode(unique_ptr<FunctionNode> node, TokenQueue & tokens);

	void CreateBlock(vector<unique_ptr<Node>> &body, TokenQueue& tokens);

	void CreateMultiBlock(vector<unique_ptr<Node>>& body, TokenQueue& tokens);

	void CreateSingleBlock(vector<unique_ptr<Node>>& body, TokenQueue& tokens);

	//针对变量多定义
	void CreateMultipleVarDefine(vector< unique_ptr<Node> >& body, TokenQueue& tokens);

	void CreateGrammar(vector<unique_ptr<Node>>& body, TokenQueue& tokens);


	unique_ptr<IFNode> CreateIF(TokenQueue& tokens);

	unique_ptr<WhileNode> CreateWhile(TokenQueue& tokens);

private:
	FunctionNode* curFun;
};
