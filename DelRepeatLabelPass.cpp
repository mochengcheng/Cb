
#include "DelRepeatLabelPass.h"
#include "IRBinary.h"
#include "IRStore.h"

DelRepeatLabelPass::DelRepeatLabelPass()
{

}

DelRepeatLabelPass::~DelRepeatLabelPass()
{

}

void DelRepeatLabelPass::runOnFunction(IRBlock* ir)
{
	vector<std::unique_ptr<IRDump>>& irCode = ir->getIRCode();

	int i = 0;

	for (i = 0; i < irCode.size(); i++)
	{
		IRLabel* pL = dynamic_cast<IRLabel*>(irCode[i].get());
		//当前标签和下个节点的标签是一样的，就剔除当前的标签数据
		if (nullptr != pL)
		{
			if ((i + 1) >= irCode.size())
				continue;

			IRDump* pNext = irCode[i + 1].get();

			if (pL->getLabel() == pNext->getLabel())
			{
				irCode[i] = nullptr;
				irCode.erase(irCode.begin() + i);
				i = -1;
				continue;
			}
			if (pNext->getLabel().empty())
			{
				string s1 = pL->getLabel();
				s1 = ReplceLable(s1);
				pNext->setLabel(s1);
				irCode[i] = nullptr;
				irCode.erase(irCode.begin() + i);
				i = -1;
				continue;
			}
			else
			{
				assert(pL->getLabel() == pNext->getLabel() && "IRBlock::delRepeatLabel label must same.");
			}
		}
	}

	//return语句后面有jump直接剔除
	for (i = 0; i < irCode.size(); i++)
	{
		IRReturn* pR = dynamic_cast<IRReturn*>(irCode[i].get());
		if (nullptr == pR)
			continue;

		if (i == (irCode.size() - 1))
			continue;

		IRJump* pJ = dynamic_cast<IRJump*>(irCode[i + 1].get());
		if (nullptr != pJ)
		{
			irCode[i + 1] = nullptr;
			irCode.erase(irCode.begin() + i + 1);
			i = -1;
			continue;
		}
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

				IRStore* pS = dynamic_cast<IRStore*>((irCode[pos + 1]).get());
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
