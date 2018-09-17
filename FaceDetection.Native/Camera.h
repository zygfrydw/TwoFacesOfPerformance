#pragma once

#include "FaceDetection.Native.h"
#include "ICamera.h"
#include <opencv2/videoio/videoio.hpp>

class Camera : public ICamera
{
	cv::VideoCapture video_capture;
public:
	Camera();
	::Size getFrameSize() override;
	void capture(Image output) override;
	~Camera();
};

