#pragma once
#include "NativeLib.h"
#include <vector>

class NATIVELIB_API NativeCalculator
{
public:
	void Add(unsigned char* arg1, unsigned char* arg2, unsigned char* dst, int length);
	void Sum(const std::vector<unsigned char*>& arguments, unsigned char* dst, int length);
};
