#pragma once
#include "FaceDetection.Native.h"
#include "Image.h"

class FACEDETECTIONNATIVE_API Size
{
public:
	int width;
	int height;
};

class FACEDETECTIONNATIVE_API ICamera
{
public:
	virtual void capture(Image output) =0;
	virtual ::Size getFrameSize() =0;
	virtual ~ICamera();
};
