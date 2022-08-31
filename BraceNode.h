#pragma once


#include "base.h"
#include "Node.h"


//针对{}包括的块节点
class BraceNode :public Node
{
public:
	BraceNode();
	~BraceNode();

	void addNode(unique_ptr<Node> node_);

	void addNode(vector<unique_ptr<Node>> &body_);

	virtual string IR(IRBlock* ir);

	//后驱节点
	virtual void setNextNode(Node* p);
	virtual Node* getNextNode();

	//前驱节点
	virtual void setPredNode(Node* p);
	virtual Node* getPredNode();

	//父节点
	virtual void setParentNode(Node* p);
	virtual Node* getParentNode();

private:
	vector<unique_ptr<Node>> body;
};
