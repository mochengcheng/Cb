
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
