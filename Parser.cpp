

#include "Parser.h"

#define FULLAPTH(NAME) string(string("C:\\Users\\morven.mo\\Desktop\\cb\\cbc-1.0\\test\\") + string(NAME)).data()

void TokenQueue::addToken(Token t)
{
	tokens.push_back(t);
}

void TokenQueue::addTokenHead(Token t)
{
	tokens.insert(tokens.begin(), t);
}

Token TokenQueue::next()
{
	assert(!tokens.empty() && "tokens is empty");

	Token tt = tokens[0];
	tokens.erase(tokens.begin());
	return tt;
}

Token TokenQueue::get(int i)
{
	assert(!tokens.empty() && "tokens is empty");

	assert((i < tokens.size()) && "tokens is length not enough");

	return tokens[i];
}

void TokenQueue::dump()
{


	ostringstream out;
	for (auto it : tokens)
	{
		if (tok_unkonw == it.getType())
			out << it.getContext() << "   " <<"tok_unkonw" << endl;
		else
			out << it.getContext() << "   " << it.getType() << endl;
	}

	{
		fstream file;
		file.open("ir.txt", ios::out | ios::trunc);
		file << out.str();
		file.close();
		system("ir.txt");
	}
}

void TokenQueue::clear()
{
	tokens.clear();
}

MyParser::MyParser()
{
}

MyParser::~MyParser()
{
}

void MyParser::parserFile(const char* pFullPath)
{
	pFile = fopen(FULLAPTH(pFullPath), "r");
	assert(pFile && "file open fail!");

	lastChar = fgetc(pFile);

	Token tt = getToken();

	while (tt.getType() != tok_eof)
	{
		if (tt.getType() != tok_comment)
				tokens.addToken(tt);

		tt = getToken();
	}

	tokens.addToken(tt);
	fclose(pFile);
	pFile = nullptr;
}

void MyParser::dump()
{
	tokens.dump();
}

void MyParser::getTokens(TokenQueue& rhs)
{
	rhs = tokens;
	tokens.clear();
}


Token MyParser::getToken()
{
	//È¥µô¿Õ¸ñ
	while (isspace(lastChar))
		lastChar = fgetc(pFile);

	// identifier: [a-zA-Z][a-zA-Z0-9]*
	if (isalpha(lastChar))
	{
		strCurToken = lastChar;
		while (isalnum((lastChar = fgetc(pFile))))
			strCurToken += lastChar;

		if ("return" == strCurToken)
			return Token("", tok_kw_return);

		if (strCurToken == "void")
			return Token("void", tok_kw_void);

		if (strCurToken == "char")
			return Token("char", tok_kw_char);

		if (strCurToken == "short")
			return Token("short", tok_kw_short);

		if (strCurToken == "int")
			return Token("int", tok_kw_int);
		if (strCurToken == "long")
			return Token("long", tok_kw_long);
		if (strCurToken == "struct")
			return Token("struct", tok_kw_struct);
		if (strCurToken == "union")
			return Token("union", tok_kw_union);
		if (strCurToken == "enum")
			return Token("enum", tok_kw_enum);
		if (strCurToken == "static")
			return Token("static", tok_kw_static);
		if (strCurToken == "extern")
			return Token("extern", tok_kw_extern);
		if (strCurToken == "const")
			return Token("const", tok_kw_const);
		if (strCurToken == "signed")
			return Token("signed", tok_kw_signed);
		if (strCurToken == "unsigned")
			return Token("unsigned", tok_kw_unsigned);
		
		if (strCurToken == "if")
			return Token("if", tok_kw_if);
		if (strCurToken == "else")
			return Token("else", tok_kw_else);
		if (strCurToken == "switch")
			return Token("switch", tok_kw_switch);
		if (strCurToken == "case")
			return Token("case", tok_kw_case);
		if (strCurToken == "default")
			return Token("default", tok_kw_default);
		if (strCurToken == "while")
			return Token("while", tok_kw_while);
		if (strCurToken == "do")
			return Token("do", tok_kw_do);
		if (strCurToken == "for")
			return Token("for", tok_kw_for);
		if (strCurToken == "return")
			return Token("return", tok_kw_return);
		if (strCurToken == "break")
			return Token("break", tok_kw_break);
		if (strCurToken == "continue")
			return Token("continue", tok_kw_continue);
		if (strCurToken == "goto")
			return Token("goto", tok_kw_goto);
		if (strCurToken == "typedef")
			return Token("typedef", tok_kw_typedef);
		if (strCurToken == "import")
			return Token("import", tok_kw_import);
		if (strCurToken == "sizeof")
			return Token("sizeof", tok_kw_sizeof);

		return Token(strCurToken, tok_string);
	}

	// Number: [0-9.]+
	if (isdigit(lastChar) || lastChar == '.')
	{
		strCurToken = "";
		do {
			strCurToken += lastChar;
			lastChar = fgetc(pFile);
		} while (isdigit(lastChar) || lastChar == '.');

		if (strCurToken == ".")
			return Token(".", tok_period);

		return Token(strCurToken, tok_number);
	}

	if (lastChar == EOF)
		return Token("", tok_eof);

	strCurToken = lastChar;
	lastChar = fgetc(pFile);

	if (strCurToken == "/" && lastChar == '/')
	{
		lastChar = fgetc(pFile);
		while (lastChar != '\n')
			lastChar = fgetc(pFile);

		lastChar = fgetc(pFile);
		return Token("", tok_comment);
	}

	if (strCurToken == "/" && lastChar == '*')
	{
		char perLastChar;
		while (1)
		{
			lastChar = fgetc(pFile);
			if (lastChar == '*')
			{
				perLastChar = lastChar;
				lastChar = fgetc(pFile);
				if (lastChar == '/')
				{
					lastChar = fgetc(pFile);
					return Token("", tok_comment);
				}
			}

			if (lastChar == EOF)
				return Token("", tok_eof);
		}
	}

	if ("+" == strCurToken)
		return Token("+", tok_op_plus);
	if ("-" == strCurToken)
		return Token("-", tok_op_minus);
	if ("*" == strCurToken)
		return Token("*", tok_op_mul);
	if ("/" == strCurToken)
		return Token("/", tok_op_div);
	if ("=" == strCurToken)
		return Token("=", tok_op_assign);
	if ("<" == strCurToken)
		return Token("<", tok_op_less);
	if (">" == strCurToken)
		return Token(">", tok_op_greater);

	if ("(" == strCurToken)
		return Token(strCurToken, tok_l_parent);
	if (")" == strCurToken)
		return Token(strCurToken, tok_r_parent);
	if ("{" == strCurToken)
		return Token(strCurToken, tok_l_brace);
	if ("}" == strCurToken)
		return Token(strCurToken, tok_r_brace);
	if ("," == strCurToken)
		return Token(strCurToken, tok_sem);
	if (";" == strCurToken)
		return Token(strCurToken, tok_comma);
	if ("[" == strCurToken)
		return Token(strCurToken, tok_l_square);
	if ("]" == strCurToken)
		return Token(strCurToken, tok_r_square);
	if ("." == strCurToken)
		return Token(strCurToken, tok_period);
	if ("\"" == strCurToken)
		return Token(strCurToken, tok_double_quotes);
	if ("%" == strCurToken)
		return Token(strCurToken, tok_percent_sign);
	


	return Token(strCurToken, tok_unkonw);
}
