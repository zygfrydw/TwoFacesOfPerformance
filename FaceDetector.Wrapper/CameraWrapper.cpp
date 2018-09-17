#include "stdafx.h"
#include "CameraWrapper.h"

#include "stdafx.h"
#include "CameraWrapper.h"
#include "FaceDetection.Native.Exports.h"

using namespace System::Drawing;

CameraWrapper::CameraWrapper() : camera(nullptr)
{
	camera = CreateCamera().release();
}

System::Drawing::Size CameraWrapper::getFrameSize()
{
	auto size = camera->getFrameSize();
	return System::Drawing::Size(size.width, size.height);
}

void CameraWrapper::readFrame(ManagedImage^ image)
{
	pin_ptr<unsigned char> pin = &image->data[0];

	const ::Image nativeImage(
		pin,
		image->width,
		image->height,
		image->step);

	camera->capture(nativeImage);
}


CameraWrapper::~CameraWrapper()
{
	this->!CameraWrapper();
}

CameraWrapper::!CameraWrapper()
{
	delete camera;
}
