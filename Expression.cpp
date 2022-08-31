

#include "Expression.h"
#include "Module.h"
#include "CallFuncNode.h"
#include "ConstantNode.h"
#include "ReturnNode.h"
#include "VariableNode.h"
#include "BinaryOpNode.h"
#include "Driver.h"

Expression::Expression()
{
}

Expression::~Expression()
{
	pToken = nullptr;
}

Expression::Expression(TokenQueue* p)
{
	pToken = p;
}

void Expression::setTokenQueue(TokenQueue* p)
{
	pToken = p;
}

unique_ptr<Node> Expression::CreateExpression()
{
	auto lhs = CreateUnary();
	if (!lhs)
		return nullptr;

	unique_ptr<Node> node = move(CreateBinaryOp(0, move(lhs)));

	Token t1 = pToken->get();
	if (t1.getType() == tok_sem)
		pToken->next();

	return move(node);
}

unique_ptr<Node> Expression::CreateExpression(unique_ptr<Node> lhs)
{
	unique_ptr<Node> node = move(CreateBinaryOp(0, move(lhs)));

	Token t1 = pToken->get();
	if (t1.getType() == tok_sem)
		pToken->next();

	return move(node);
}

unique_ptr<Node> Expression::CreateUnary()
{
	Token t1 = pToken->get();

	if (t1.getType() == tok_string || t1.getType() == tok_number || t1.getType() == tok_l_parent
		|| t1.getType() == tok_comma || t1.getType() == tok_kw_return)
		return CreatePrimary();

	assert(0 && "CreateUnary Type Error");

	return nullptr;
}

unique_ptr<Node> Expression::CreateBinaryOp(int ExprPrec, unique_ptr<Node> lhs)
{
	Token t1;
	int TokPrec = 0;
	int NextPrec = 0;
	string op;

	while (1)
	{
		t1 = pToken->get();
		TokPrec = getOpLevel(t1.getType());
		if (TokPrec < ExprPrec)
			return move(lhs);

		op = t1.getContext();
		pToken->next();

		auto rhs = CreateUnary();
		assert(rhs && "CreateBinaryOp CreateUnary Error");

		t1 = pToken->get();
		NextPrec = getOpLevel(t1.getType());

		if (TokPrec < NextPrec) {
			rhs = CreateBinaryOp(TokPrec + 1, move(rhs));
			assert(rhs && "CreateBinaryOp Next Error");
		}

		lhs = make_unique<BinaryOpNode>(op, move(lhs), move(rhs));
	}
}

unique_ptr<Node> Expression::CreatePrimary()
{
	Token t1 = pToken->get();
	Token t2 = pToken->get(1);

	//函数
	if (t1.getType() == tok_string && t2.getType() == tok_l_parent)
	{
		assert((Module::getInstance()->isExistFunction(t1.getContext())) && "CreatePrimary Function no exist");
		return CreateCallFunc();
	}

	//结构体
	if (Module::getInstance()->isStruct(t1.getContext()))
	{
		return CreateStruct();
	}

	if (t1.getType() == tok_string)
		return CreateIdentifier();
	if (t1.getType() == tok_number)
		return CreateConstant();
	if (t1.getType() == tok_l_parent)
		return CreateParent();
	if (t1.getType() == tok_kw_return)
		return CreateReturn();

	assert(0 && "CreatePrimary Type Error");

	return nullptr;
}

unique_ptr<Node> Expression::CreateCallFunc()
{
	Token t1 = pToken->next();
	unique_ptr<CallFuncNode> callFunc= make_unique<CallFuncNode>(t1.getContext(), Module::getInstance()->getFunctionReturn(t1.getContext()));
	

	t1 = pToken->next();

	assert(t1.getType() == tok_l_parent && "CreateCallFunc args error");
	t1 = pToken->next();
	if (t1.getType() == tok_r_parent)
		return move(callFunc);

	while (1)
	{
		if (auto Arg = CreateExpression())
			callFunc->addArgs(move(Arg));
		else
			assert(0 && "CreateCallFunc Error");

		t1 = pToken->next();
		if (t1.getType() == tok_r_parent)
			return move(callFunc);

		if (t1.getType() == tok_sem)
			continue;

		pToken->addTokenHead(t1);
	}
}

unique_ptr<Node> Expression::CreateStruct()
{
	return nullptr;
}

unique_ptr<Node> Expression::CreateIdentifier()
{
	//处理自加减法
	{
		Token t1 = pToken->get();
		Token t2 = pToken->get(1);
		Token t3 = pToken->get(2);
		if ((t1.getType() == tok_string && t2.getType() == tok_op_plus && t2.getType() == t3.getType()) ||
			(t1.getType() == tok_string && t2.getType() == tok_op_minus && t2.getType() == t3.getType()))
		{
			//++,--
			string op = "-";
			if (t2.getType() == tok_op_plus)
				op = "+";

			unique_ptr<VariableNode> node1 = make_unique< VariableNode>();
			node1->setName(t1.getContext());

			Type* pType = DriverAction::getInstance()->getCurFunPoint()->getVarType(t1.getContext());

			TokenType tt;
			if (pType->isInt())
				tt = tok_kw_int;
	
			unique_ptr<ConstantNode> node2 = make_unique< ConstantNode>(move(CreateType(Token("", tt))), "1");

			unique_ptr<BinaryOpNode> bin1 = make_unique<BinaryOpNode>(op, move(node1), move(node2));

			node1 = make_unique< VariableNode>();
			node1->setName(t1.getContext());

			unique_ptr<BinaryOpNode> lhs = make_unique<BinaryOpNode>("=", move(node1), move(bin1));
			pToken->next();
			pToken->next();
			pToken->next();
			return move(lhs);
		}

	}
	Token t1 = pToken->next();

	unique_ptr<VariableNode> node = make_unique< VariableNode>();
	node->setName(t1.getContext());

	return move(node);
}

unique_ptr<Node> Expression::CreateConstant()
{
	Token t1 = pToken->next();

	unique_ptr<ConstantNode> node = make_unique< ConstantNode>(move(CreateType(t1)), t1.getContext());

	return move(node);
}

unique_ptr<Node> Expression::CreateParent()
{
	//eat(
	Token t1 = pToken->next();

	auto expr = CreateExpression();
	assert(expr && "CreateParent Error");

	t1 = pToken->next();
	assert((t1.getType() == tok_r_parent) && "CreateParent Type Error");

	return move(expr);
}

unique_ptr<Node> Expression::CreateReturn()
{
	Token t1 = pToken->next();
	auto expr = CreateExpression();

	unique_ptr<ReturnNode> node = make_unique<ReturnNode>(move(expr));
	return move(node);
}
