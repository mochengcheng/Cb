#pragma once


#include "base.h"
#include "Node.h"

class ConditionBrace
{
public:
	ConditionBrace();
	~ConditionBrace();

	void addIF(unique_ptr<Node> node);

	void addIFBody(unique_ptr<Node> node);

	void addIFBody(vector<unique_ptr<Node>>& body);

	string IRCond(IRBlock* ir);

	string IRBody(IRBlock* ir);

	void setBodyLable(string l);

	string getBodyLable();

	void setNextNode(Node* p);

	void setParentNode(Node* p);

	void setPredNode(Node* p);

private:
	unique_ptr<Node> cb_if;
	vector<unique_ptr<Node>> cb_if_body;
};

class IFNode:public Node
{
public:
	IFNode();
	~IFNode();

	virtual NodeType GetType();
	virtual string IR(IRBlock* ir);

	virtual void setNextNode(Node* p);
	virtual Node* getNextNode();

	virtual void setPredNode(Node* p);
	virtual Node* getPredNode();

	virtual void setParentNode(Node* p);
	virtual Node* getParentNode();


	void addIFStmt(unique_ptr<ConditionBrace> stmt);

	void addElseIFStmt(unique_ptr<ConditionBrace> stmt);

	void addElseStmt(unique_ptr<ConditionBrace> stmt);

private:

	string  onlyIF(IRBlock* ir);

	string  onlyIFAndElse(IRBlock* ir);

	string  All(IRBlock* ir);


private:
	unique_ptr<ConditionBrace> cb_if_stmt;

	vector<unique_ptr<ConditionBrace>> cb_elseif_stmt;

	unique_ptr<ConditionBrace> cb_else_stmt;
};