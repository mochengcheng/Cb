#pragma once

#include "base.h"
#include "Node.h"

class WhileNode:public Node
{
public:
	WhileNode();
	~WhileNode();

	virtual string IR(IRBlock* ir);

	virtual void setNextNode(Node* p);
	virtual Node* getNextNode();

	virtual void setPredNode(Node* p);
	virtual Node* getPredNode();

	virtual void setParentNode(Node* p);
	virtual Node* getParentNode();

	void addCond(unique_ptr<Node> cond_);

	void addBody(unique_ptr<Node> item_);

	void addBody(vector<unique_ptr<Node>> &body_);

	void setBodyLable(string l);

	string getBodyLable();



private:
	unique_ptr<Node> cond;
	vector<unique_ptr<Node>> body;
};