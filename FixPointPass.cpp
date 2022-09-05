
#include "FixPointPass.h"
#include "IRAlloca.h"
#include "IRBinary.h"
#include "IRStore.h"

FixPointPass::FixPointPass()
{

}

FixPointPass::~FixPointPass()
{

}

void FixPointPass::runOnFunction(IRBlock* ir)
{
	ir->CountVar();
	ir->CalcFixedPoint();

	map<string, string>& fixVar = ir->getFixVar();
	map<string, string>& varMap = ir->getVar();

	if (fixVar.empty())
		return;

	for (auto& it : fixVar)
	{
		varMap.erase(it.first);
		cout << "fix point:" << it.first << endl;
	}

	vector<unique_ptr<IRDump>>& irCode = ir->getIRCode();

	int tmp_use_line = -1;
	for (int pos = 0; pos < irCode.size(); pos++)
	{
		//if (fixVar.size() == 1)
		{
			int ref = irCode[pos]->replaceVar(varMap, "%tmp");
			if (-1 == tmp_use_line && ref > 0)
				tmp_use_line = pos;
		}
	}

	{
		int pos;
		for (pos = 0; pos < irCode.size(); pos++)
		{
			IRDump* it = (irCode[pos]).get();
			if (nullptr != dynamic_cast<IRAlloca*>(it))
			{
				IRAlloca* pA = dynamic_cast<IRAlloca*>(it);
				if (pA->getLhs() == "%tmp")
					break;
			}
		}

		//假如优化后，声明落后于使用，进行替换
		if (pos > tmp_use_line && pos < irCode.size())
		{
			unique_ptr<IRDump> p = move(irCode[pos]);
			irCode[pos] = nullptr;
			irCode.erase(irCode.begin() + pos);
			irCode.insert(irCode.begin() + tmp_use_line, move(p));
		}

		for (pos = pos + 1; pos < irCode.size(); pos++)
		{
			IRDump* it = (irCode[pos]).get();
			if (nullptr != dynamic_cast<IRAlloca*>(it))
			{
				IRAlloca* pA = dynamic_cast<IRAlloca*>(it);
				if (pA->getLhs() == "%tmp")
					pA->setDel(true);
			}
		}

		for (pos = 0; pos < irCode.size(); pos++)
		{
			IRDump* it = (irCode[pos]).get();

			if (it->getDel())
			{
				irCode[pos] = nullptr;
				irCode.erase(irCode.begin() + pos);
				pos = -1;
				continue;
			}
		}
	}

	{
		int pos;
		for (pos = 0; pos < irCode.size(); pos++)
		{
			IRDump* it = (irCode[pos]).get();
			if (nullptr != dynamic_cast<IRAlloca*>(it))
			{
				IRAlloca* pA = dynamic_cast<IRAlloca*>(it);
				if (pA->getLhs() == "%tmp")
					break;
			}
		}

		int def_pos = pos;


	}

	/*删除无效赋值
	tmp = a + b
	a = tmp
	直接合并为
	a = a + b;
	*/
	{
		int pos;
		for (pos = 0; pos < irCode.size(); pos++)
		{
			IRDump* it = (irCode[pos]).get();
			if (nullptr != dynamic_cast<IRBinary*>(it))
			{
				IRBinary* pB = dynamic_cast<IRBinary*>(it);
				if (pos == (irCode.size() - 1))
					continue;

				IRStore *pS = dynamic_cast<IRStore*>((irCode[pos + 1]).get());
				if (nullptr == pS)
					continue;

				if (pB->getRet() == pS->getRhs())
				{
					pB->setRet(pS->getLhs());

					irCode[pos + 1] = nullptr;
					irCode.erase(irCode.begin() + pos + 1);
					pos = pos - 1;
					continue;
				}
			}
		}
	}
}

