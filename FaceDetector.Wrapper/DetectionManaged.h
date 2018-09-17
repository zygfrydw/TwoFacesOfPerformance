#pragma once

public ref class DetectionManaged
{
public:
	int classId;
	float confidence;

	int x;
	int y;
	int width;
	int height;
};