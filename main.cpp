


#include "base.h"
#include "Driver.h"
#include "TestConfig.h"
#include "DelRepeatLabelPass.h"
#include "FixPointPass.h"
#include "Module.h"

int main(int argc, char** argv)
{
	string cmd;
	if (argc > 1)
		cmd = argv[2];

	for (int i = 2; i < argc; i++)
	{
		cmd = argv[i];

		if ("lexer" == cmd)
			TestConfig::getInstance()->bLex = true;
		if ("ast" == cmd)
			TestConfig::getInstance()->bAst = true;
		if ("fix_point" == cmd)
		{
			TestConfig::getInstance()->bFixPoint = true;
			unique_ptr<FixPointPass> p = make_unique<FixPointPass>();
			Module::getInstance()->addFunctionPass(move(p));
		}
			
		if ("opt_ast" == cmd)
		{
			TestConfig::getInstance()->bOptAst = true;
			unique_ptr<DelRepeatLabelPass> p = make_unique<DelRepeatLabelPass>();
			Module::getInstance()->addFunctionPass(move(p));
		}
	}

	DriverAction::getInstance()->Lexer(argv[1]);

	return 0;

}



