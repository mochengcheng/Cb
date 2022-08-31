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

	map<string, string> mapDef;   //左边
	map<string, string> mapUse;   //右边

	map<string, string> mapIn;
	map<string, string> mapOut;

	map<string, string> mapIn_;
	map<string, string> mapOut_;

	map<string, string> mapSucc;   //出边
	map<string, string> mapPred;   //入边

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

	//保存变量名
	map<string, string> varMap;

	map<string, string> fixVar;

};


