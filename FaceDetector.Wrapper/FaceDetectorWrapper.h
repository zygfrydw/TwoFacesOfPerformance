#pragma once
#include "DetectionManaged.h"
#include "IFaceDetector.h"
#include "ManagedImage.h"

public ref class FaceDetectorWrapper
{
	IFaceDetector* faceDetector;
public:
	FaceDetectorWrapper(System::String^ configuration, System::String^ model);

	cli::array<DetectionManaged^>^ detect(ManagedImage^ image);

	!FaceDetectorWrapper();

	~FaceDetectorWrapper();
};
