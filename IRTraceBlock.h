#pragma once


#include "base.h"

//�켣������
/*
��IRBlock��������ʱ��ͨ��label��ǩɨ�裨lable1��ǩ���浽label2֮��ľ��ǹ켣��1�����ݣ�����һ��һ������TraceBlock
ÿ������������һ����ں�һ�����ڣ�
1 ��ھ��ǵ�һ���飬entry��ǩ����
2 ����һ��������ڵ㣬����������еĽ���	�������Ļ�����������ͼת��Ϊһ�����룬һ�����
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

private:
	BlockType blockType;

};