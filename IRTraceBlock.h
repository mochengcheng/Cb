#pragma once


#include "base.h"

//轨迹块描述
/*
当IRBlock数据生成时候，通过label标签扫描（lable1标签后面到label2之间的就是轨迹块1的内容），来一个一个创建TraceBlock
每个函数必须有一个入口和一个出口：
1 入口就是第一个块，entry标签修饰
2 增加一个结束块节点，用来标记所有的结束	，这样的话整个控制流图转化为一个输入，一个输出
3 入口轨迹块只有出没有入，出口轨迹块只有入没有出，正常的有入和出（1-N个）
*/

enum class BlockType
{
	BeginBlockType,
	EndBlockType,
	NormalBlockType
};

class IRTraceBlock
{
public:
	IRTraceBlock();
	~IRTraceBlock();

	void setBlockType(BlockType blockType_);
	BlockType getBlockType();

	void setPrecBlock(IRTraceBlock*p);
	set<IRTraceBlock*>& getPrecBlock();

	void setNextBlock(IRTraceBlock* p);
	set<IRTraceBlock*>& getNextBlock();

private:
	BlockType blockType;

	set<IRTraceBlock*> precBlock;  //前驱块
	set<IRTraceBlock*> nextBlock; //后驱块

};