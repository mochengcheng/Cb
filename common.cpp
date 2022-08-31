

#include "common.h"

string ReplceLable(string  s1)
{
	regex pattern1("\r\n");
	s1 = regex_replace(s1, pattern1, "");
	regex pattern2(":");
	s1 = regex_replace(s1, pattern2, "");
	return s1;
}


bool equalCustom(map<string, string> lhs, map<string, string> rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	if (lhs.empty() && rhs.empty())
		return true;

	map<string, string> lhs_ = lhs;
	map<string, string> rhs_ = rhs;

	for (auto& it : rhs)
	{
		lhs_.erase(it.first);
	}
	for (auto& it : lhs)
	{
		rhs_.erase(it.first);
	}

	if (lhs_.empty() && rhs_.empty())
		return true;

	return false;
}

