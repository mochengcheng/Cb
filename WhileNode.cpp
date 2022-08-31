
#include "WhileNode.h"
#include "IRCJump.h"
#include "IRLabel.h"
#include "IRJump.h"
#include "JumpNode.h"

WhileNode::WhileNode()
{

}

WhileNode::~WhileNode()
{

}

string WhileNode::IR(IRBlock* ir)
{
	string condLabel = getNodeLabel();
	if (condLabel.empty())
	{
		condLabel = getLabel();
		setNodeLabel(condLabel);

		if (body.size() > 0)
		{
			JumpNode* pJ = dynamic_cast<JumpNode*>(body[body.size() - 1].get());
			if (nullptr != pJ)
			{
				if (pJ->getNodeTag() == "while_jump")
				{
					pJ->setNodeLabel(condLabel);
				}
			}
		}
		
	}
	{
		unique_ptr<IRLabel> pL = make_unique<IRLabel>(condLabel);
		ir->AddIRDump(move(pL));
	}

	string s1 = cond->IR(ir);


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

	setBodyLable(l1);

	for (auto& it : body)
	{
		it->IR(ir);
	}

	{
		unique_ptr<IRJump> pL = make_unique<IRJump>(condLabel);
		ir->AddIRDump(move(pL));
	}


	return "";
}

void WhileNode::setNextNode(Node* p)
{
	Node::setNextNode(p);

	if (body.empty())
		return;

	if (body.size() == 1)
	{
		body[0]->setNextNode(p);
		return;
	}

	size_t len = body.size() - (size_t)1;
	for (size_t i = 0; i < len; i++)
	{
		body[i]->setNextNode(body[i + 1].get());
	}
	body[len]->setNextNode(p);
}

Node* WhileNode::getNextNode()
{
	return Node::getNextNode();
}

void WhileNode::setPredNode(Node* p)
{
	Node::setPredNode(p);

	size_t len = body.size() - (size_t)1;
	for (size_t i = len; i > 0; i--)
	{
		body[i]->setPredNode(body[i - 1].get());
	}

	body[0]->setPredNode(p);

}

Node* WhileNode::getPredNode()
{
	return Node::getPredNode();
}

void WhileNode::setParentNode(Node* p)
{
	Node::setParentNode(p);

	if (cond)
		cond->setParentNode(this);

	for (auto& it : body)
	{
		it->setParentNode(this);
	}
}

Node* WhileNode::getParentNode()
{
	return Node::getParentNode();
}

void WhileNode::addCond(unique_ptr<Node> cond_)
{
	cond = move(cond_);
}

void WhileNode::addBody(unique_ptr<Node> item_)
{
	body.push_back(move(item_));
}

void WhileNode::addBody(vector<unique_ptr<Node>>& body_)
{
	body.clear();
	for (auto& it : body_)
		body.push_back(move(it));
}

void WhileNode::setBodyLable(string l)
{
	if (body.empty())
		return;

	body[0]->setNodeLabel(l);
}

string WhileNode::getBodyLable()
{
	if (body.empty())
		return "";

	return body[0]->getNodeLabel();
}
