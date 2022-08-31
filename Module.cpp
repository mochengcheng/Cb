
#include "Module.h"


Module::Module()
{
}

Module::~Module()
{
}

Module* Module::getInstance()
{
	static Module module;
	return &module;
}

void Module::addFunctionNode(string name, unique_ptr<Node> sec)
{
	if (func.find(name) == func.end())
	{
		func[name] = move(sec);
	}
}

bool Module::isStruct(string name)
{
	return false;
}


bool Module::isExistFunction(string name)
{
	return (func.find(name) != func.end());
}

void Module::dump()
{
	ostringstream out;
	
	IRBlock* pB = nullptr;

	for (auto& it : func)
	{
		it.second->IR();

		pB = it.second->getIR();
		if (nullptr != pB)
		{
			for (auto& it_pass : pass)
			{
				it_pass->runOnFunction(pB);
			}
		}
	}

	for (auto& it : func)
	{
		it.second->dump(out);
	}

	{
		fstream file;
		file.open("ir.txt", ios::out | ios::trunc);
		file << out.str();
		file.close();
		system("ir.txt");
	}
}

string Module::getFunctionReturn(string name)
{
	if (!isExistFunction(name))
		return "";

	Type* p = func[name]->getNodeType();

	return p->getTypeName();
}

void Module::addFunctionPass(unique_ptr<FunctionPass> lhs)
{
	pass.push_back(move(lhs));
}

