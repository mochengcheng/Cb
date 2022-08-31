#pragma once

#include "base.h"
#include "Type.h"
#include "IRBlock.h"

enum NodeType
{
	IF_NODE,
	BINARYOP_NODE,
	UNKNOWN_NODE
};


//每个节点必须有前驱节点，后驱节点，和父节点(嵌套结构)
class Node
{
public:
	Node();
	virtual ~Node();

	virtual void IR();

	virtual string IR(IRBlock *ir);

	virtual NodeType GetType();

	virtual Type* getNodeType();

	virtual string dump(ostringstream & out);

	virtual string getName();

	static void clearSN();

	static string getSN();

	static void clearLabel();

	static string getLabel();

	virtual void setNextNode(Node *p);
	virtual Node* getNextNode();

	virtual void setPredNode(Node* p);
	virtual Node* getPredNode();

	virtual void setParentNode(Node* p);
	virtual Node* getParentNode();

	virtual void setNodeLabel(string label);
	virtual string getNodeLabel();

	virtual IRBlock* getIR();


	string getNodeTag() {
		return nodeTag;
	}
	void setNodeTag(string rhs) { 
		nodeTag = rhs; 
	}

private:
	static int sn;

	static int label_sn;

	//下一个节点
	Node* nextNode;
	Node* predNode;

	string nodeLabel;

	//针对if,while控制语句层级嵌套保存父节点
	Node* parentNode;

	//节点标签
	string nodeTag;
};