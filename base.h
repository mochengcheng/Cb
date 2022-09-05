#pragma once


#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <regex>

using namespace std;


#define SPACE " "

#define TAB "  "

#define ENDL endl

#define ERRORINFO(a, b) (string(string(a)+string(b)).data())


template<class T>
uintptr_t PointConvertUnit(T* p)
{
	uintptr_t num = reinterpret_cast<uintptr_t>(p);
	return num;
}