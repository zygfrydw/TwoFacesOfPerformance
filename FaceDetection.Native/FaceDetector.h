#pragma once
#include <string>
#include "FaceDetection.Native.h"
#include "Detection.h"
#include <vector>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include "Image.h"
#include "IFaceDetector.h"

using namespace cv;
using namespace dnn;



class FaceDetector : public IFaceDetector
{
	Net net;
	cv::Size targetSize;
	double scale;
	bool swapRB;
	Scalar blobMean;
	float confThreshold;
	float nmsThreshold;
public:
	FaceDetector(std::string configuration, std::string model);
	std::vector<Detection> detect(Image image);

	~FaceDetector();

private:
	std::vector<Detection> postprocess(Mat& frame, const std::vector<Mat>& outs, Net& net);

	std::vector<String> getOutputsNames(const Net& net);
};

