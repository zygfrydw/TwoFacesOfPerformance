#pragma once
#include "ICamera.h"
#include "ManagedImage.h"

public ref class CameraWrapper
{
	ICamera* camera;
public:
	CameraWrapper();

	System::Drawing::Size getFrameSize();
	void readFrame(ManagedImage^ bitmap);


	~CameraWrapper();

	!CameraWrapper();
};
