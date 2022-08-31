
#include "DelRepeatLabelPass.h"

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
}
