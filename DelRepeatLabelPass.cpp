
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
		//��ǰ��ǩ���¸��ڵ�ı�ǩ��һ���ģ����޳���ǰ�ı�ǩ����
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

	//return��������jumpֱ���޳�
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
