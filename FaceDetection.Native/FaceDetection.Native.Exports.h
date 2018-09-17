#pragma once
#include "FaceDetection.Native.h"
#include <memory>
#include "IFaceDetector.h"
#include "ICamera.h"

std::unique_ptr<IFaceDetector> FACEDETECTIONNATIVE_API CreateFaceDetector(std::string configuration, std::string model);
std::unique_ptr<ICamera> FACEDETECTIONNATIVE_API CreateCamera();
