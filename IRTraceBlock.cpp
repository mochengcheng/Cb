
#include "IRTraceBlock.h"

IRTraceBlock::IRTraceBlock()
{
	blockType = BlockType::NormalBlockType;
}

IRTraceBlock::~IRTraceBlock()
{

}

void IRTraceBlock::setBlockType(BlockType blockType_)
{
	blockType = blockType_;
}

BlockType IRTraceBlock::getBlockType()
{
	return blockType;
}

void IRTraceBlock::setPrecBlock(IRTraceBlock* p)
{
	precBlock.insert(p);
}

set<IRTraceBlock*>& IRTraceBlock::getPrecBlock()
{
	return precBlock;
}

void IRTraceBlock::setNextBlock(IRTraceBlock* p)
{
	nextBlock.insert(p);
}

set<IRTraceBlock*>& IRTraceBlock::getNextBlock()
{
	return nextBlock;
}
