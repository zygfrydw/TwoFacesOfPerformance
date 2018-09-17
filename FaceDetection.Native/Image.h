#pragma once
#include <cstdint>
#include "FaceDetection.Native.h"

class FACEDETECTIONNATIVE_API Image
{
public:
	Image();
	Image(uint8_t* ptr, int width, int height, int step);
	~Image();
	uint8_t* ptr;
	int width;
	int height;
	int step;
};

