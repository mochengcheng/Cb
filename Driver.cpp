

#include "Driver.h"
#include "Expression.h"
#include "VariableNode.h"
#include "Module.h"
#include "BinaryOpNode.h"
#include "BreakNode.h"
#include "ContinueNode.h"
#include "NullNode.h"
#include "TestConfig.h"
#include "JumpNode.h"



DriverAction::DriverAction()
{
	curFun = nullptr;
}

DriverAction::~DriverAction()
{

}

DriverAction* DriverAction::getInstance()
{
	static DriverAction action;
	return &action;
}

void DriverAction::Lexer(const char* pFile)
{
	unique_ptr<MyParser> parser = make_unique<MyParser>();
	parser->parserFile(pFile);
	if (TestConfig::getInstance()->bLex)
	{
		parser->dump();
		return;
	}

	CreateAST(move(parser));

	Module::getInstance()->dump();
}

void DriverAction::CreateAST(unique_ptr<MyParser> parser)
{
	TokenQueue tokens;
	parser->getTokens(tokens);

	Token t1;
	Token t2;
	Token t3;

	while (1)
	{
		t1 = tokens.next();
		//参数类型
		if (isParameterType(t1.getType()))
		{
			t2 = tokens.next();
			if (t2.getType() == tok_string)
			{
				t3 = tokens.next();

				//是函数定义
				if (t3.getType() == tok_l_parent)
				{
					unique_ptr<FunctionNode> pFunc = make_unique<FunctionNode>();
					pFunc->setRetType(move(CreateType(t1)));
					pFunc->setName(t2.getContext());
					pFunc = CreateFunctionNode(move(pFunc), tokens);
					pFunc->CreateNodeLink();

					Module::getInstance()->addFunctionNode(t2.getContext(), move(pFunc));
				}
			}
		}
		else if (t1.getType() == tok_kw_import)
		{
			t1 = tokens.next();
			assert(t1.getType() == tok_double_quotes && "import error");

			t1 = tokens.next();
			string file;
			while (t1.getType() != tok_double_quotes)
			{
				file += t1.getContext();
				t1 = tokens.next();
			}
				
			Lexer(file.data());
		}

		if (t1.getType() == tok_eof)
			return;
	}
}

//解析函数
unique_ptr<FunctionNode> DriverAction::CreateFunctionNode(unique_ptr<FunctionNode> node, TokenQueue &tokens)
{
	curFun = node.get();

	Token t1;
	Token t2;
	Token t3;

	//先解析函数参数
	while (1)
	{
		t1 = tokens.next();
		if (t1.getType() == tok_r_parent)
			break;

		//第一个是类型
		assert(isParameterType(t1.getType()) && "must be parameter type");

		t2 = tokens.next();
		assert((t2.getType() == tok_string) && "must be string type");

		unique_ptr<ParamArg> arg = make_unique<ParamArg>();
		arg->name = "%" + t2.getContext();
		arg->type = move(CreateType(t1));
		node->addArg(move(arg));

		t3 = tokens.next();
		if (t3.getType() == tok_sem)
			continue;
		else if (t3.getType() == tok_r_parent)
			break;
		else
			assert(0 && "function define error");
	}

	//解析body
	vector<unique_ptr<Node>> &body = node->getBody();
	CreateBlock(body, tokens);

//	for (auto& it : body)
	{
//		node->addBlockNode(move(it));
	}

	return move(node);
}

void DriverAction::CreateBlock(vector<unique_ptr<Node>>& body, TokenQueue& tokens)
{
	Token t1 = tokens.next();

	if (tok_l_brace == t1.getType())
	{
		CreateMultiBlock(body, tokens);
	}
	else
	{
		tokens.addTokenHead(t1);
		CreateSingleBlock(body, tokens);
	}

}

void DriverAction::CreateMultiBlock(vector<unique_ptr<Node>>& body, TokenQueue& tokens)
{
	Token t1 = tokens.next();
	if (t1.getType() == tok_r_brace)
		return;

	while (1)
	{
		if (t1.getType() == tok_r_brace)
			return;

		tokens.addTokenHead(t1);

		CreateGrammar(body, tokens);

		t1 = tokens.next();
	}
}

void DriverAction::CreateSingleBlock(vector<unique_ptr<Node>>& body, TokenQueue& tokens)
{
	CreateGrammar(body, tokens);
}

void DriverAction::CreateMultipleVarDefine(vector<unique_ptr<Node>>& body, TokenQueue& tokens)
{
	Token t1 = tokens.next();
	Token t2 = tokens.next();
	Token t3 = tokens.next();

	assert(t2.getType() == tok_string && "CreateMultipleVarDefine Error");

	while (1)
	{
		//分号
		if (t3.getType() == tok_comma)
		{
			unique_ptr<VariableNode> node = make_unique<VariableNode>();
			node->setName(t2.getContext());
			node->setNodeType(move(CreateType(t1)));
			body.push_back(move(node));
			return;
		}

		//逗号
		if (t3.getType() == tok_sem)
		{
			unique_ptr<VariableNode> node = make_unique<VariableNode>();
			node->setName(t2.getContext());
			node->setNodeType(move(CreateType(t1)));
			body.push_back(move(node));

			t2 = tokens.next();
			t3 = tokens.next();
			continue;
		}

		//赋值
		if (t3.getType() == tok_op_assign)
		{
			unique_ptr<VariableNode> lhs = make_unique<VariableNode>();
			lhs->setName(t2.getContext());
			lhs->setNodeType(move(CreateType(t1)));
			body.push_back(move(lhs));

			lhs = make_unique<VariableNode>();
			lhs->setName(t2.getContext());

			tokens.addTokenHead(t3);
			unique_ptr<Expression> exp = make_unique<Expression>(&tokens);
			unique_ptr<Node> node = move(exp->CreateExpression(move(lhs)));
			body.push_back(move(node));

			t2 = tokens.next();
			if (t2.getType() == tok_comma)
				return;

			t3 = tokens.next();
			continue;
		}
	}
}

void DriverAction::CreateGrammar(vector<unique_ptr<Node>>& body, TokenQueue& tokens)
{
	Token t1 = tokens.next();

	if (t1.getType() == tok_kw_return)
	{
		unique_ptr<Expression> exp = make_unique<Expression>(&tokens);

		auto expr = move(exp->CreateExpression());
		auto ret = make_unique<ReturnNode>(move(expr));
		body.push_back(move(ret));
	}
	else if (isParameterType(t1.getType()))   //判断变量声明
	{
		tokens.addTokenHead(t1);
		CreateMultipleVarDefine(body, tokens);
	}
	else if (t1.getType() == tok_string)
	{
		tokens.addTokenHead(t1);
		unique_ptr<Expression> exp = make_unique<Expression>(&tokens);
		auto expr = move(exp->CreateExpression());
		body.push_back(move(expr));
	}
	else if (t1.getType() == tok_kw_if)
	{
		unique_ptr<IFNode> node = move(CreateIF(tokens));
		body.push_back(move(node));
	}
	else if (t1.getType() == tok_kw_while)
	{
		unique_ptr<WhileNode> node = move(CreateWhile(tokens));
		body.push_back(move(node));
	}
	else if (t1.getType() == tok_kw_break)
	{
		unique_ptr<BreakNode> node = make_unique<BreakNode>();
		t1 = tokens.next();
		assert(t1.getType() == tok_comma && "break keyword next token must be ;");
		body.push_back(move(node));
	}
	else if (t1.getType() == tok_kw_continue)
	{
		unique_ptr<ContinueNode> node = make_unique<ContinueNode>();
		t1 = tokens.next();
		assert(t1.getType() == tok_comma && "continue keyword next token must be ;");
		body.push_back(move(node));
	}
	else if (t1.getType() == tok_l_brace)
	{
		CreateMultiBlock(body, tokens);
	}
}

unique_ptr<IFNode> DriverAction::CreateIF(TokenQueue& tokens)
{
	unique_ptr<IFNode> node = make_unique<IFNode>();

	Token t1 = tokens.next();
	//解析if
	{
		unique_ptr<ConditionBrace> ifstmt = make_unique<ConditionBrace>();

		assert(t1.getType() == tok_l_parent && "CreateIF if not match (");
		unique_ptr<Expression> exp = make_unique<Expression>(&tokens);

		unique_ptr<Node> ifcon = move(exp->CreateExpression());
		ifstmt->addIF(move(ifcon));
		t1 = tokens.next();
		assert(t1.getType() == tok_r_parent && "CreateIF if not match )");

		vector<unique_ptr<Node>> ifbody;
		CreateBlock(ifbody, tokens);
		if (ifbody.empty())
		{
			unique_ptr<NullNode> p = make_unique<NullNode>();
			ifbody.push_back(move(p));
		}
		ifstmt->addIFBody(ifbody);

		node->addIFStmt(move(ifstmt));
	}

	t1 = tokens.next();
	while (t1.getType() == tok_comma)
		t1 = tokens.next();

	Token t2 = tokens.next();

	//解析elseif和else
	{
		while (1)
		{
			if (t1.getType() == tok_kw_else && t2.getType() == tok_kw_if)
			{
				t1 = tokens.next();
				assert(t1.getType() == tok_l_parent && "CreateIF else if not match (");

				unique_ptr<ConditionBrace> elseifstmt = make_unique<ConditionBrace>();
				unique_ptr<Expression> exp = make_unique<Expression>(&tokens);

				unique_ptr<Node> ifcon = move(exp->CreateExpression());
				elseifstmt->addIF(move(ifcon));

				t1 = tokens.next();
				assert(t1.getType() == tok_r_parent && "CreateIF else if not match )");

				vector<unique_ptr<Node>> ifbody;
				CreateBlock(ifbody, tokens);
				if (ifbody.empty())
				{
					unique_ptr<NullNode> p = make_unique<NullNode>();
					ifbody.push_back(move(p));
				}
				elseifstmt->addIFBody(ifbody);

				node->addElseIFStmt(move(elseifstmt));
				t1 = tokens.next();
				t2 = tokens.next();
			}
			else if (t1.getType() == tok_kw_else)
			{
				tokens.addTokenHead(t2);
				unique_ptr<ConditionBrace> elsestmt = make_unique<ConditionBrace>();
				vector<unique_ptr<Node>> elsebody;
				CreateBlock(elsebody, tokens);
				if (elsebody.empty())
				{
					unique_ptr<NullNode> p = make_unique<NullNode>();
					elsebody.push_back(move(p));
				}
				elsestmt->addIFBody(elsebody);
				node->addElseStmt(move(elsestmt));
				break;
			}
			else
			{
				tokens.addTokenHead(t2);
				tokens.addTokenHead(t1);
				break;
			}
		}
	
	}

	return move(node);
}

unique_ptr<WhileNode> DriverAction::CreateWhile(TokenQueue& tokens)
{
	unique_ptr<WhileNode> node = make_unique<WhileNode>();

	Token t1 = tokens.next();

	assert(t1.getType() == tok_l_parent && "While not match (");
	{
		unique_ptr<Expression> exp = make_unique<Expression>(&tokens);
		unique_ptr<Node> ifcon = move(exp->CreateExpression());
		node->addCond(move(ifcon));
	}
	t1 = tokens.next();
	assert(t1.getType() == tok_r_parent && "While not match )");
	{
		vector<unique_ptr<Node>> body;
		CreateBlock(body, tokens);

		unique_ptr<JumpNode> pJ = make_unique<JumpNode>();
		pJ->setNodeTag("while_jump");
		body.push_back(move(pJ));
		node->addBody(body);

	}

	return move(node);
}

FunctionNode* DriverAction::getCurFunPoint()
{
	assert(curFun && "current function point is null");

	return curFun;
}
