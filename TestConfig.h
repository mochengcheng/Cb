#pragma once


#include "base.h"


//���Բ���

class TestConfig
{
public:
	TestConfig();
	~TestConfig();

	static TestConfig* getInstance();


public:
	//�����ʷ�
	bool bLex;

	//�﷨
	bool bAst;

	//�������Ż�
	bool bFixPoint;

	//�Ż�ast��
	bool bOptAst;
};