
#include "base.h"
#include "FunctionNode.h"
#include "ReturnNode.h"
#include "VariableNode.h"


FunctionNode::FunctionNode()
{
	ir = make_unique<IRBlock>();
}

FunctionNode::~FunctionNode()
{
}

FunctionNode::FunctionNode(unique_ptr<Type> rhs_ret, string rhs_name, vector<unique_ptr<ParamArg>> rhs_args)
{
	this->retType = move(rhs_ret);
	this->name = rhs_name;

	args.clear();
	for (auto &it : rhs_args)
	{
		args.push_back(move(it));
	}

	ir = make_unique<IRBlock>();
}

void FunctionNode::IR()
{
	Node::clearSN();
	Node::clearLabel();

	for (auto& it : body)
	{
		it->IR(ir.get());
	}
}

string FunctionNode::dump(ostringstream& out)
{
	{
		map<string, string>& fix_point = ir->getFixVar();
		if (!fix_point.empty())
		{
			out << "function:" << name << " fix_point:" << endl;
			for (auto& it : fix_point)
			{
				out << it.first << endl;
			}
			out << endl;
		}
		else
		{
			out << endl << endl;
		}
	}
	out << "define" << SPACE;

	out<< retType->getTypeName()<< SPACE;

	out << "@"<<name << "(";

	if (args.size() > 0)
	{
		for (size_t i = 0; i < args.size() - 1; i++)
		{
			if (args[i]->type->isInt())
				out << "int" << SPACE << args[i]->name << ", ";
			else if (args[i]->type->isDouble())
				out << "double" << SPACE << args[i]->name << ", ";
		}

		size_t i = args.size() - 1;

		if (args[i]->type->isInt())
			out << "int" << SPACE << args[i]->name;
		else if (args[i]->type->isDouble())
			out << "double" << SPACE << args[i]->name;
	}

	out << ")" << endl;

	ir->dump(out);

	return "";
}

void FunctionNode::setRetType(unique_ptr<Type> ret)
{
	this->retType = move(ret);
}

void FunctionNode::setName(string name)
{
	this->name = name;
}

Type* FunctionNode::getNodeType()
{
	return retType.get();
}

void FunctionNode::addArg(unique_ptr<ParamArg> arg)
{
	args.push_back(move(arg));
}

void FunctionNode::addBlockNode(unique_ptr<Node> node)
{
	body.push_back(move(node));
}

void FunctionNode::CreateNodeLink()
{
	//如果是void,增加ret指令
	if ("void" == retType->getTypeName())
	{
		unique_ptr<ReturnNode> p = make_unique<ReturnNode>();
		body.push_back(move(p));
	}

	if (body.size() > 0)
	{
		body[0]->setNodeLabel("entry");
	}

	if (body.empty() || body.size() == 1)
		return;

	size_t len = body.size() - 1;
	for (size_t i = 0; i < len; i++)
	{
		body[i]->setNextNode(body[i + 1].get());
	}
	for (size_t i = len; i > 0; i--)
	{
		body[i]->setPredNode(body[i - 1].get());
	}

	for (auto& it : body)
		it->setParentNode(this);
}

IRBlock* FunctionNode::getIR()
{
	return ir.get();
}

Type* FunctionNode::getVarType(string s)
{
	Type* pType = nullptr;

	s = "%" + s;

	for (auto& it : body)
	{
		VariableNode* p = dynamic_cast<VariableNode*>(it.get());
		if (nullptr != p && p->getName() == s)
		{
			pType = p->getNodeType();

			if (nullptr != pType)
				return pType;
		}
	}

	for (auto& it : args)
	{
		if (it->name == s)
			return it->type.get();
	}

	return pType;
}
