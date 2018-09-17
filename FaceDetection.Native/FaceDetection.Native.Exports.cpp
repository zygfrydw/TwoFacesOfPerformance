#include "stdafx.h"
#include "FaceDetection.Native.Exports.h"
#include "FaceDetector.h"
#include "Camera.h"

std::unique_ptr<IFaceDetector> CreateFaceDetector(std::string configuration, std::string model)
{
	return std::make_unique<FaceDetector>(configuration, model);
}

std::unique_ptr<ICamera> CreateCamera()
{
	return std::make_unique<Camera>();
}
