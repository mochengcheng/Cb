#pragma once


#include "base.h"
#include "Token.h"



class TokenQueue
{
public:
	TokenQueue() {}
	~TokenQueue() { tokens.clear(); }

	void addToken(Token t);

	void addTokenHead(Token t);

	//ȡ����ɾ��
	Token next();
	//��ȡ��
	Token get(int i = 0);

	void dump();

	void clear();

private:
	vector<Token> tokens;
};


class MyParser
{
public:
	MyParser();
	~MyParser();

	void parserFile(const char *pFullPath);

	void dump();

	void getTokens(TokenQueue &rhs);


private:
	Token getToken();

private:
	TokenQueue tokens;

	FILE* pFile;
	char lastChar;
	string strCurToken;
};

