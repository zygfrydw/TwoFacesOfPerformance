#pragma once
#include "FaceDetection.Native.h"

class FACEDETECTIONNATIVE_API Detection
{
public:

	int classId;
	float confidence;

	int x;
	int y; 
	int width; 
	int height;

	Detection(int class_id, float confidence, int x, int y, int width, int height);

	~Detection();
};

