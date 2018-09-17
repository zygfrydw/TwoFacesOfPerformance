#include "stdafx.h"
#include "FaceDetectorWrapper.h"
#include "FaceDetection.Native.Exports.h"
#include <msclr\marshal_cppstd.h>

FaceDetectorWrapper::FaceDetectorWrapper(System::String^ configuration, System::String^ model)
{
	std::string nativeConfig = msclr::interop::marshal_as<std::string>(configuration);
	std::string nativeModel = msclr::interop::marshal_as<std::string>(model);;
	faceDetector = CreateFaceDetector(nativeConfig, nativeModel).release();
}

cli::array<DetectionManaged^>^ FaceDetectorWrapper::detect(ManagedImage^ image)
{
	try
	{
		pin_ptr<unsigned char> pin = &image->data[0];
		const ::Image nativeImage(
			pin,
			image->width,
			image->height,
			image->step);

		auto detections = faceDetector->detect(nativeImage);

		cli::array <DetectionManaged^>^ managedDetections = gcnew cli::array <DetectionManaged^>(detections.size());
		for (size_t i = 0; i < detections.size(); i++)
		{
			managedDetections[i] = gcnew DetectionManaged();
			managedDetections[i]->classId = detections[i].classId;
			managedDetections[i]->confidence = detections[i].confidence;
			managedDetections[i]->height = detections[i].height;
			managedDetections[i]->width = detections[i].width;
			managedDetections[i]->x = detections[i].x;
			managedDetections[i]->y = detections[i].y;
		}

		return managedDetections;
	}
	catch (const std::exception& ex) {
		throw gcnew System::Exception(gcnew System::String(ex.what()));
	}
}

FaceDetectorWrapper::!FaceDetectorWrapper()
{
	this->~FaceDetectorWrapper();
}

FaceDetectorWrapper::~FaceDetectorWrapper()
{
	delete faceDetector;
}
