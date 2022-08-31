
#include "IRBlock.h"
#include "IRAlloca.h"
#include "IRBinary.h"
#include "IRCall.h"
#include "IRLabel.h"
#include "IRJump.h"
#include "IRCJump.h"
#include "IRStore.h"
#include "TestConfig.h"
#include "IRReturn.h"


IRBlock::IRBlock()
{
}

IRBlock::~IRBlock()
{
	irCode.clear();
}

void IRBlock::AddIRDump(unique_ptr<IRDump> ir)
{
	size_t len = irCode.size();
	if (len == 0)
	{
		irCode.push_back(move(ir));
		return;
	}

	if (irCode[len - 1]->EqualString() == ir->EqualString())
		return;

	{
		//jump指令后面的jump指令无法执行，直接剔除
		if (nullptr != dynamic_cast<IRJump*>(ir.get()) && nullptr != dynamic_cast<IRJump*>(irCode[len - 1].get()))
		{
			return;
		}
	}

	for (auto& it : irCode)
	{
		if (nullptr != dynamic_cast<IRLabel*>(it.get()))
		{
			if (it->EqualString() == ir->EqualString())
				return;
		}
	}

	irCode.push_back(move(ir));
}

void IRBlock::dump(ostringstream& out)
{

	for (auto& it : irCode)
	{
		out << it->printIR();
	}

	out << endl;
}

void IRBlock::addVar(string var)
{
	if (var.empty())
		return;

	if (var[0] == '%')
	{
		varMap[var] = var;
		return;
	}

	assert(varMap.find(var) == varMap.end() && "redefine var");
	varMap[var] = var;
}

void IRBlock::CountVar()
{
	varMap.clear();

	for (auto& it : irCode)
	{
		IRDump* pBase = it.get();

		if (nullptr != dynamic_cast<IRAlloca*>(pBase))
		{
			IRAlloca* pDev = dynamic_cast<IRAlloca*>(pBase);
			addVar(pDev->lhs);
			continue;
		}

		if (nullptr != dynamic_cast<IRBinary*>(pBase))
		{
			IRBinary* pDev = dynamic_cast<IRBinary*>(pBase);
			addVar(pDev->ret);
			continue;
		}

		if (nullptr != dynamic_cast<IRCall*>(pBase))
		{
			IRCall* pDev = dynamic_cast<IRCall*>(pBase);
			addVar(pDev->lhs);
			continue;
		}

	}
}

void IRBlock::CalcFixedPoint()
{
	vector<unique_ptr<IREdge>> vcEdge;
	map<string, IREdge*> mapIndex;

	map<string, IRDump*> mapLabel;

	//计算label

	for (size_t i = 0; i < irCode.size(); i++)
	{
		IRDump* it = (irCode[i]).get();
		if (nullptr != dynamic_cast<IRLabel*>(it))
		{
			IRLabel* pl = dynamic_cast<IRLabel*>(it);

			string label = ReplceLable(pl->getLabel());
			if ((i + 1) < irCode.size())
			{
				mapLabel[label] = (irCode[i+1]).get();
			}
			else
				mapLabel[label] = nullptr;
		}
		else 	if (nullptr != dynamic_cast<IRJump*>(it))
		{
		}
		else
		{
			if (!it->getLabel().empty())
			{
				string label = ReplceLable(it->getLabel());

				mapLabel[label] = it;
			}
		}
	}

	vector<IRDump*> vcIR;

	for (size_t i = 0; i < irCode.size(); i++)
	{
		IRDump* it = (irCode[i]).get();
		if (nullptr == dynamic_cast<IRLabel*>(it))
			vcIR.push_back(it);
	}

	for (auto& it : vcIR)
	{
		unique_ptr<IREdge> p = make_unique<IREdge>();
		p->pData = it;

		uintptr_t index = reinterpret_cast<std::uintptr_t>(it);
		mapIndex[to_string(index)] = p.get();

		vcEdge.push_back(move(p));
	}

	for (size_t i = 0; i < vcIR.size(); i++)
	{
		if ((i+1) >= vcIR.size())
			continue;

		IRDump* p = vcIR[i];
		if (nullptr != dynamic_cast<IRCJump*>(p))
		{
			IRCJump* pBin = dynamic_cast<IRCJump*>(p);
			string l1 = ReplceLable(pBin->getLabel1());
			string l0 = ReplceLable(pBin->getLabel0());

			uintptr_t curIndex = reinterpret_cast<std::uintptr_t>(p);
			uintptr_t nextIndex = reinterpret_cast<std::uintptr_t>(mapLabel[l1]);
			mapIndex[to_string(curIndex)]->addNextEdge(mapIndex[to_string(nextIndex)]);
			mapIndex[to_string(nextIndex)]->addPreEdge(mapIndex[to_string(curIndex)]);

			nextIndex = reinterpret_cast<std::uintptr_t>(mapLabel[l0]);
			mapIndex[to_string(curIndex)]->addNextEdge(mapIndex[to_string(nextIndex)]);
			mapIndex[to_string(nextIndex)]->addPreEdge(mapIndex[to_string(curIndex)]);

		}
		else if (nullptr != dynamic_cast<IRJump*>(p))
		{
			IRJump* pJ = dynamic_cast<IRJump*>(p);
			string la = ReplceLable(pJ->getLabel());
			uintptr_t nextIndex = reinterpret_cast<std::uintptr_t>(mapLabel[la]);
			uintptr_t curIndex = reinterpret_cast<std::uintptr_t>(p);
			mapIndex[to_string(curIndex)]->addNextEdge(mapIndex[to_string(nextIndex)]);
			mapIndex[to_string(nextIndex)]->addPreEdge(mapIndex[to_string(curIndex)]);
		}
		else
		{
			IRDump* pNext = vcIR[i+1];
			uintptr_t curIndex = reinterpret_cast<std::uintptr_t>(p);
			uintptr_t nextIndex = reinterpret_cast<std::uintptr_t>(pNext);
			mapIndex[to_string(curIndex)]->addNextEdge(mapIndex[to_string(nextIndex)]);
		}
	}

	for (size_t i = vcIR.size() - 1; i >= 1; i--)
	{
		IRDump* pPre = vcIR[i - 1];
		if (nullptr != dynamic_cast<IRJump*>(pPre))
			continue;

		if (nullptr != dynamic_cast<IRCJump*>(pPre))
			continue;

		IRDump* p = vcIR[i];

		uintptr_t curIndex = reinterpret_cast<std::uintptr_t>(p);
		uintptr_t preIndex = reinterpret_cast<std::uintptr_t>(pPre);
		mapIndex[to_string(curIndex)]->addPreEdge(mapIndex[to_string(preIndex)]);
	}

	//打印
	/*
	for (auto& it : vcEdge)
	{
		cout << "********************begin" << endl;
		cout << "cur context:"  << it->pData->printIR() << endl;

		for (auto& it1 : it->nextEdge)
		{
			cout << "next context:" << endl << it1->pData->printIR();
		}
	//	cout << "next context over " << endl << endl;

		for (auto& it1 : it->preEdge)
		{
			cout << "pre context:" << endl << it1->pData->printIR();
		}
	//	cout << "pre context over " << endl << endl;

		cout << "********************end" << endl;

		//system("cls");
	}
	*/

	{
		int index = 1;
		for (auto& it : vcEdge)
		{
			it->sn = index++;
			it->varMap = varMap;

			it->initUseAndDef();
			it->mapIn.clear();
			it->mapOut.clear();
		}

		for (auto& it : vcEdge)
		{
			it->initSuccAndPred();
		}

		bool bRet = true;

		while (1)
		{
			bRet = true;
			for (auto& it : vcEdge)
			{
				if (!it->CalcFixPoint())
					bRet = false;

				it->printUseAndDef();
			}
			cout << endl;

			if (bRet)
			{
				break;
			}
		}
		
	}

	//获取变量名
	fixVar.clear();
	{
		int iCount = 0;
		map<string, int> countVar;
		for (auto& it : vcEdge)
		{
			vector<string> s1 = it->getFixPoint();
			if (s1.empty())
				continue;
			
			iCount++;

			for (auto& it1 : s1)
			{
				if (countVar.find(it1) == countVar.end())
					countVar[it1] = 1;
				else
					countVar[it1] = countVar[it1] + 1;
			}
		}

		iCount = iCount / 2;
		for (auto& it : countVar)
		{
			if (it.second >= iCount)
				fixVar[it.first] = it.first;
		}
	}
}

vector<unique_ptr<IRDump>>& IRBlock::getIRCode()
{
	return irCode;
}

map<string, string>& IRBlock::getFixVar()
{
	return fixVar;
}

map<string, string>& IRBlock::getVar()
{
	return varMap;
}

IREdge::IREdge()
{
	pLabel = nullptr;
	pData = nullptr;
	sn = 0;
}

void IREdge::addPreEdge(IREdge* p)
{
	for (auto& it : preEdge)
	{
		if (reinterpret_cast<std::uintptr_t>(it) == reinterpret_cast<std::uintptr_t>(p))
			return;
	}
	preEdge.push_back(p);
}

void IREdge::addNextEdge(IREdge* p)
{
	for (auto& it : nextEdge)
	{
		if (reinterpret_cast<std::uintptr_t>(it) == reinterpret_cast<std::uintptr_t>(p))
			return;
	}
	nextEdge.push_back(p);
}

void IREdge::initUseAndDef()
{
	IRStore* pS= dynamic_cast<IRStore*>(pData);
	if (nullptr != pS)
	{
		if (varMap.find(pS->lhs) != varMap.end())
			mapDef[pS->lhs] = pS->lhs;

		if (varMap.find(pS->rhs) != varMap.end())
			mapUse[pS->rhs] = pS->rhs;

		return;
	}

	IRCJump* pC = dynamic_cast<IRCJump*>(pData);
	if (nullptr != pC)
	{
		if (varMap.find(pC->cond) != varMap.end())
			mapUse[pC->cond] = pC->cond;
		return;
	}

	IRBinary* pB = dynamic_cast<IRBinary*>(pData);
	if (nullptr != pB)
	{
	//	if ("=" == pB->op)
		{
			if (varMap.find(pB->ret) != varMap.end())
				mapDef[pB->ret] = pB->ret;

			if (varMap.find(pB->lhs) != varMap.end())
				mapUse[pB->lhs] = pB->lhs;

			if (varMap.find(pB->rhs) != varMap.end())
				mapUse[pB->rhs] = pB->rhs;

			return;
		}
	}


}

void IREdge::initSuccAndPred()
{
	mapSucc.clear();
	mapPred.clear();

	for (auto& it : nextEdge)
	{
		mapSucc[to_string(sn)] = mapSucc[to_string(it->sn)];
	}

	for (auto& it : preEdge)
	{
		mapPred[to_string(sn)] = mapPred[to_string(it->sn)];
	}

}

bool IREdge::CalcFixPoint()
{
	mapIn_ = mapIn;
	mapOut_ = mapOut;

	mapIn = mapUse;

	for (auto& it : mapDef)
	{
		mapOut.erase(it.first);
	}
	mapIn.clear();

	for (auto& it : mapOut)
	{
		mapIn[it.first] = it.second;
	}

	for (auto& it : mapUse)
	{
		mapIn[it.first] = it.second;
	}

	mapOut.clear();

	for (auto& it : nextEdge)
	{
		for (auto& it1 : it->mapIn)
		{
			mapOut[it1.first] = it1.second;
		}
	}

	if (equalCustom(mapIn, mapIn_) && equalCustom(mapOut, mapOut_))
		return true;

	return false;
}

void IREdge::printUseAndDef()
{
	cout << sn << " in:";
	for (auto& it : mapIn)
		cout << it.first << " ";

	cout << " out:";
	for (auto& it : mapOut)
		cout << it.first << " ";
	cout << endl;

}

vector<std::string> IREdge::getFixPoint()
{
	vector<string> a;
	for (auto& it : mapIn)
	{
		if (mapOut.find(it.first) != mapOut.end())
			a.push_back(it.first);
	}
	
	return a;
}
