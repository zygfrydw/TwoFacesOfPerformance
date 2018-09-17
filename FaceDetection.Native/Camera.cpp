#include "stdafx.h"
#include "Camera.h"


Camera::Camera() : video_capture(0)
{
	
}

Size Camera::getFrameSize()
{
	cv::Mat image;
	video_capture.read(image);
	return { image.cols, image.rows };
}

void Camera::capture(Image output)
{
	cv::Mat cvOutput(output.height, output.width, CV_8UC3, output.ptr, output.step);
	cv::Mat frameBuffer;
	video_capture.read(frameBuffer);

	frameBuffer.copyTo(cvOutput);
	if(cvOutput.ptr() != output.ptr)
	{
		// Throw the exception in case openCV reallocate the array.
		throw std::exception("The array has been reallocated");
	}
}


Camera::~Camera()
{
}
