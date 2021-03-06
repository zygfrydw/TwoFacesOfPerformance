// NativeLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NativeLib.h"
#include <ipp.h>
#include <emmintrin.h>
#include <limits>
#include <cstdint>
#undef max

void NativeAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length)
{
	const auto charMax = std::numeric_limits<uint8_t>::max();
	for (int i = 0; i < length; i++)
	{
		int value = arg1[i] + arg2[i];
		dst[i] = value < charMax ? value : charMax;
	}
}


void NativeParallelAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length)
{
	const auto charMax = std::numeric_limits<uint8_t>::max();

	#pragma omp parallel for
	for (int i = 0; i < length; i++)
	{
		int value = arg1[i] + arg2[i];
		dst[i] = value < charMax ? value : charMax;
	}
}

void SimdAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length)
{
	__m128i* arg1Ptr = reinterpret_cast<__m128i*>(arg1);
	__m128i* arg2Ptr = reinterpret_cast<__m128i*>(arg2);
	__m128i* dstPtr = reinterpret_cast<__m128i*>(dst);

	int i = 0;
	for (; i < length; i += 128 / 8)
	{
		__m128i a = _mm_loadu_si128(arg1Ptr);
		__m128i b = _mm_loadu_si128(arg2Ptr);
		__m128i c = _mm_adds_epu8(a, b);
		_mm_storeu_si128(dstPtr, c);
		arg1Ptr++;
		arg2Ptr++;
		dstPtr++;
	}

	// Add the remaining part of array indivisible by SIMD size 
	auto charMax = std::numeric_limits<uint8_t>::max();
	for (; i < length; i++)
	{
		int value = arg1[i] + arg2[i];
		dst[i] = value < charMax ? value : charMax;
	}
}

void IntelIppAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length)
{
	ippsAdd_8u_Sfs(arg1, arg2, dst, length, 0);
}

void IntelIppParallelAdd(uint8_t * arg1, uint8_t * arg2, uint8_t * dst, int length)
{
	int blockSize = 4096;
	int blockCount = length / blockSize;

#pragma omp parallel for
	for (int n = 0; n < blockCount; ++n)
		ippsAdd_8u_Sfs(arg1 + n * blockSize, arg2 + n * blockSize, dst + n * blockSize, blockSize, 0);

	// Add the remaining part of array indivisible by block size
	auto remainOffset = blockCount * blockSize;
	int remainLength = length - remainOffset;
	ippsAdd_8u_Sfs(arg1 + remainOffset, arg2 + remainOffset, dst + remainOffset, remainLength, 0);
}