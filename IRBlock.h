#pragma once

#include "base.h"
#include "common.h"
#include "IRDump.h"
#include "IRLabel.h"

class IREdge
{
public:
	IREdge();

	void addPreEdge(IREdge *p);
	void addNextEdge(IREdge* p);

	void initUseAndDef();

	void initSuccAndPred();

	bool CalcFixPoint();

	void printUseAndDef();

	vector<string> getFixPoint();

	vector<IREdge*> preEdge;
	vector<IREdge*> nextEdge;

	IRLabel* pLabel;
	IRDump* pData;

	int sn;

	map<string, string> mapDef;   //���
	map<string, string> mapUse;   //�ұ�

	map<string, string> mapIn;
	map<string, string> mapOut;

	map<string, string> mapIn_;
	map<string, string> mapOut_;

	map<string, string> mapSucc;   //����
	map<string, string> mapPred;   //���

	map<string, string> varMap;
};

class IRBlock
{
public:
	IRBlock();
	~IRBlock();


	void AddIRDump(unique_ptr<IRDump> ir);

	void dump(ostringstream& out);

	void addVar(string var);

	void CountVar();

	void CalcFixedPoint();

	vector<unique_ptr<IRDump>>& getIRCode();

	map<string, string>& getFixVar();

	map<string, string>& getVar();

private:
	vector<unique_ptr<IRDump>> irCode;

	//���������
	map<string, string> varMap;

	map<string, string> fixVar;

};


