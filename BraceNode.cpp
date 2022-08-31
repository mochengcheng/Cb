
#include "BraceNode.h"

BraceNode::BraceNode()
{
}

BraceNode::~BraceNode()
{

}

void BraceNode::addNode(unique_ptr<Node> node_)
{
	body.push_back(move(node_));
}

void BraceNode::addNode(vector<unique_ptr<Node>>& body_)
{
	for (auto& it : body_)
		body.push_back(move(it));
}

string BraceNode::IR(IRBlock* ir)
{
	return "";
}

void BraceNode::setNextNode(Node* p)
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

Node* BraceNode::getNextNode()
{
	return Node::getNextNode();
}

void BraceNode::setPredNode(Node* p)
{
	Node::setPredNode(p);

	if (body.empty())
		return;

	size_t len = body.size() - (size_t)1;
	for (size_t i = len; i > 0; i--)
	{
		body[i]->setPredNode(body[i - 1].get());
	}

	body[0]->setPredNode(p);
}

Node* BraceNode::getPredNode()
{
	return Node::getPredNode();
}

void BraceNode::setParentNode(Node* p)
{
	Node::setParentNode(p);

	for (auto& it : body)
		it->setParentNode(this);
}

Node* BraceNode::getParentNode()
{
	return Node::getParentNode();
}
