

#include "IFNode.h"
#include "JumpNode.h"
#include "IRCJump.h"
#include "IRLabel.h"
#include "IRJump.h"

ConditionBrace::ConditionBrace()
{
	cb_if = nullptr;
}

ConditionBrace::~ConditionBrace()
{
}

void ConditionBrace::addIF(unique_ptr<Node> node)
{
	cb_if = move(node);
}

void ConditionBrace::addIFBody(unique_ptr<Node> node)
{
	cb_if_body.push_back(move(node));
}

void ConditionBrace::addIFBody(vector<unique_ptr<Node>>& body)
{
	for (auto &it: body)
		cb_if_body.push_back(move(it));
}

string ConditionBrace::IRCond(IRBlock* ir)
{
	string s1 = cb_if->IR(ir);
	return s1;
}

string ConditionBrace::IRBody(IRBlock* ir)
{
	for (auto& it : cb_if_body)
	{
		it->IR(ir);
	}
	return "";
}

void ConditionBrace::setBodyLable(string l)
{
	assert(!cb_if_body.empty() && "ElseIFStmt body is null");

	cb_if_body[0]->setNodeLabel(l);
}

string ConditionBrace::getBodyLable()
{
	assert(!cb_if_body.empty() && "ElseIFStmt body is null");

	return cb_if_body[0]->getNodeLabel();
}

void ConditionBrace::setNextNode(Node* p)
{
	if (cb_if_body.empty())
		return;

	if (cb_if_body.size() == 1)
	{
		cb_if_body[0]->setNextNode(p);
		return;
	}
		
	size_t len = cb_if_body.size() - (size_t)1;
	for (size_t i = 0; i < len; i++)
	{
		cb_if_body[i]->setNextNode(cb_if_body[i + 1].get());
	}
	cb_if_body[len]->setNextNode(p);
}

void ConditionBrace::setParentNode(Node* p)
{
	if (cb_if)
		cb_if->setParentNode(p);

	for (auto& it : cb_if_body)
	{
		it->setParentNode(p);
	}
}


void ConditionBrace::setPredNode(Node* p)
{
	size_t len = cb_if_body.size() - (size_t)1;
	for (size_t i = len; i > 0; i--)
	{
		cb_if_body[i]->setPredNode(cb_if_body[i - 1].get());
	}

	cb_if_body[0]->setPredNode(p);
}

IFNode::IFNode()
{
	cb_if_stmt = nullptr;
	cb_else_stmt = nullptr;
}

IFNode::~IFNode()
{
}

NodeType IFNode::GetType()
{
	return IF_NODE;
}

string IFNode::IR(IRBlock* ir)
{
	if (cb_if_stmt && cb_elseif_stmt.empty() && !cb_else_stmt)
		return onlyIF(ir);

	if (cb_if_stmt && cb_elseif_stmt.empty() && cb_else_stmt)
		return onlyIFAndElse(ir);

	if (cb_if_stmt && !cb_elseif_stmt.empty() && cb_else_stmt)
		return All(ir);

	return "";
}

void IFNode::addIFStmt(unique_ptr<ConditionBrace> stmt)
{
	cb_if_stmt = move(stmt);
}

void IFNode::addElseIFStmt(unique_ptr<ConditionBrace> stmt)
{
	cb_elseif_stmt.push_back(move(stmt));
}

void IFNode::addElseStmt(unique_ptr<ConditionBrace> stmt)
{
	cb_else_stmt = move(stmt);
}

void IFNode::setNextNode(Node* p)
{
	Node::setNextNode(p);

	if (cb_if_stmt)
		cb_if_stmt->setNextNode(p);

	for (auto& it : cb_elseif_stmt)
		it->setNextNode(p);

	if (cb_else_stmt)
		cb_else_stmt->setNextNode(p);
}

Node* IFNode::getNextNode()
{
	return Node::getNextNode();
}

void IFNode::setPredNode(Node* p)
{
	Node::setPredNode(p);

	if (cb_if_stmt)
		cb_if_stmt->setPredNode(p);

	for (auto& it : cb_elseif_stmt)
		it->setPredNode(p);

	if (cb_else_stmt)
		cb_else_stmt->setPredNode(p);
}

Node* IFNode::getPredNode()
{
	return Node::getPredNode();
}

void IFNode::setParentNode(Node* p)
{
	Node::setParentNode(p);

	if (cb_if_stmt)
		cb_if_stmt->setParentNode(this);

	for (auto& it : cb_elseif_stmt)
	{
		it->setParentNode(this);
	}

	if (cb_else_stmt)
		cb_else_stmt->setParentNode(this);
}

Node* IFNode::getParentNode()
{
	return Node::getParentNode();
}

string IFNode::onlyIF(IRBlock* ir)
{
	string s1 = cb_if_stmt->IRCond(ir);
	string l1 = getLabel();
	string l2;

	Node* nextNode = getNextNode();
	if (nullptr != nextNode)
	{
		l2 = nextNode->getNodeLabel();
		if (l2.empty())
		{
			l2 = getLabel();
			nextNode->setNodeLabel(l2);
		}
	}

	unique_ptr<IRCJump> p = make_unique<IRCJump>(s1, l1, l2);
	ir->AddIRDump(move(p));

	{
		unique_ptr<IRLabel> pL = make_unique<IRLabel>(l1);
		ir->AddIRDump(move(pL));
	}
	cb_if_stmt->setBodyLable(l1);

	s1 = cb_if_stmt->IRBody(ir);

	return "";
}


string IFNode::onlyIFAndElse(IRBlock* ir)
{
	string s1 = cb_if_stmt->IRCond(ir);

	string l1 = getLabel();
	string l2 = getLabel();
	string l3;
	{
		Node* nextNode = getNextNode();
		if (nullptr != nextNode)
		{
			l3 = nextNode->getNodeLabel();
			if (l3.empty())
			{
				l3 = getLabel();
				nextNode->setNodeLabel(l3);
			}
		}
	}

	{
		unique_ptr<IRCJump> p = make_unique<IRCJump>(s1, l1, l2);
		ir->AddIRDump(move(p));
		unique_ptr<IRLabel> pL = make_unique<IRLabel>(l1);
		ir->AddIRDump(move(pL));
	}

	cb_if_stmt->setBodyLable(l1);
	s1 = cb_if_stmt->IRBody(ir);
	{
		unique_ptr<IRJump> pJ = make_unique<IRJump>(l3);
		ir->AddIRDump(move(pJ));
	}

	{
		unique_ptr<IRLabel> pL = make_unique<IRLabel>(l2);
		ir->AddIRDump(move(pL));
	}
	cb_else_stmt->setBodyLable(l2);

	s1 = cb_else_stmt->IRBody(ir);
	{
		unique_ptr<IRJump> pJ = make_unique<IRJump>(l3);
		ir->AddIRDump(move(pJ));
	}

	return "";
}

string IFNode::All(IRBlock* ir)
{
	vector<ConditionBrace*> vcLink;

	vcLink.push_back(cb_if_stmt.get());

	for (auto& it : cb_elseif_stmt)
	{
		vcLink.push_back(it.get());
	}

	vcLink.push_back(cb_else_stmt.get());

	size_t len = vcLink.size() - 1;

	string l3;

	//获取下个节点
	{
		Node* nextNode = getNextNode();
		if (nullptr != nextNode)
		{
			l3 = nextNode->getNodeLabel();
			if (l3.empty())
			{
				l3 = getLabel();
				nextNode->setNodeLabel(l3);
			}
		}
	}

	for (size_t i = 0; i < len; i++)
	{
		string s1 = vcLink[i]->IRCond(ir);

		string l1 = vcLink[i]->getBodyLable().empty() ? getLabel() : vcLink[i]->getBodyLable();
		string l2 = vcLink[i+1]->getBodyLable().empty() ? getLabel() : vcLink[i+1]->getBodyLable();
	
		{
			unique_ptr<IRCJump> p = make_unique<IRCJump>(s1, l1, l2);
			ir->AddIRDump(move(p));
			unique_ptr<IRLabel> pL = make_unique<IRLabel>(l1);
			ir->AddIRDump(move(pL));
		}

		vcLink[i]->setBodyLable(l1);
		s1 = vcLink[i]->IRBody(ir);
		{
			unique_ptr<IRJump> pJ = make_unique<IRJump>(l3);
			ir->AddIRDump(move(pJ));
		}

		{
			unique_ptr<IRLabel> pL = make_unique<IRLabel>(l2);
			ir->AddIRDump(move(pL));
		}
		vcLink[i+1]->setBodyLable(l2);
	}

	//处理最后一个
	string s1 = cb_else_stmt->IRBody(ir);
	{
		unique_ptr<IRJump> pJ = make_unique<IRJump>(l3);
		ir->AddIRDump(move(pJ));
	}

	return "";
}

