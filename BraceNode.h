#pragma once


#include "base.h"
#include "Node.h"


//���{}�����Ŀ�ڵ�
class BraceNode :public Node
{
public:
	BraceNode();
	~BraceNode();

	void addNode(unique_ptr<Node> node_);

	void addNode(vector<unique_ptr<Node>> &body_);

	virtual string IR(IRBlock* ir);

	//�����ڵ�
	virtual void setNextNode(Node* p);
	virtual Node* getNextNode();

	//ǰ���ڵ�
	virtual void setPredNode(Node* p);
	virtual Node* getPredNode();

	//���ڵ�
	virtual void setParentNode(Node* p);
	virtual Node* getParentNode();

private:
	vector<unique_ptr<Node>> body;
};
