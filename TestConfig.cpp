
#include "TestConfig.h"

TestConfig::TestConfig()
{
	bLex = false;
	bAst = false;
	bFixPoint = false;
	bOptAst = false;
}

TestConfig::~TestConfig()
{

}

TestConfig*  TestConfig::getInstance()
{
	static TestConfig config;
	return &config;
}
