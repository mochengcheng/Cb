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


//ÿ���ڵ������ǰ���ڵ㣬�����ڵ㣬�͸��ڵ�(Ƕ�׽ṹ)
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

	//��һ���ڵ�
	Node* nextNode;
	Node* predNode;

	string nodeLabel;

	//���if,while�������㼶Ƕ�ױ��游�ڵ�
	Node* parentNode;

	//�ڵ��ǩ
	string nodeTag;
};