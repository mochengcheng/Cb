#pragma once


#include "base.h"


//测试参数

class TestConfig
{
public:
	TestConfig();
	~TestConfig();

	static TestConfig* getInstance();


public:
	//启动词法
	bool bLex;

	//语法
	bool bAst;

	//不动点优化
	bool bFixPoint;

	//优化ast树
	bool bOptAst;
};