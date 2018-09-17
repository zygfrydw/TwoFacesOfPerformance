#include "stdafx.h"
#include "NativeCalculator.h"
#include <limits>
#undef max

void NativeCalculator::Add(unsigned char* arg1, unsigned char* arg2, unsigned char* dst, int length)
{
	const auto charMax = std::numeric_limits<uint8_t>::max();
	;
	for (int i = 0; i < length; i++)
	{
		int value = arg1[i] + arg2[i];
		dst[i] = value < charMax ? value : charMax;
	}
}

void NativeCalculator::Sum(const std::vector<unsigned char*>& arguments, unsigned char* dst, int length)
{
	std::fill_n(dst, length, 0);
	const auto charMax = std::numeric_limits<uint8_t>::max();

	for (auto array : arguments)
	{
		for (int i = 0; i < length; i++)
		{
			int value = dst[i] + array[i];
			dst[i] = value < charMax ? value : charMax;
		}
	}
}

