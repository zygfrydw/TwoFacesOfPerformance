#pragma once
#include "Detection.h"
#include <vector>
#include "Image.h"

class FACEDETECTIONNATIVE_API IFaceDetector
{
public:
	virtual ~IFaceDetector();
	virtual std::vector<Detection> detect(Image image) = 0;
};
