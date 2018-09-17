#include "stdafx.h"
#include "FaceDetector.h"


FaceDetector::FaceDetector(std::string configuration, std::string model)
{
	net = readNet(model, configuration, "");
	net.setPreferableBackend(0);
	net.setPreferableTarget(1);

	targetSize = { 300, 300 };
	scale = 1.0;
	swapRB = true;
	blobMean = { 104, 117, 123 };
	confThreshold = 0.5;
	nmsThreshold = 0.4;
}

std::vector<Detection> FaceDetector::detect(Image image)
{
	// Create a 4D blob from a frame.
	cv::Mat frame(image.height, image.width, CV_8UC3, image.ptr, image.step);
	
	cv::Mat blob;

	cv::Mat resized;
	cv::resize(frame, resized, targetSize);

	blobFromImage(resized, blob, scale, targetSize, blobMean, swapRB, false);

	// Run a model.
	net.setInput(blob);
	std::vector<Mat> outs;
	net.forward(outs, getOutputsNames(net));

	return postprocess(frame, outs, net);
}

std::vector<Detection> FaceDetector::postprocess(Mat& frame, const std::vector<Mat>& outs, Net& net)
{
	static std::vector<int> outLayers = net.getUnconnectedOutLayers();
	static std::string outLayerType = net.getLayer(outLayers[0])->type;

	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<Rect> boxes;
	
	if (outLayerType == "DetectionOutput")
	{
		// Network produces output blob with a shape 1x1xNx7 where N is a number of
		// detections and an every detection is a vector of values
		// [batchId, classId, confidence, left, top, right, bottom]
		CV_Assert(outs.size() == 1);
		float* data = (float*)outs[0].data;
		for (size_t i = 0; i < outs[0].total(); i += 7)
		{
			float confidence = data[i + 2];
			if (confidence > confThreshold)
			{
				int left = (int)(data[i + 3] * frame.cols);
				int top = (int)(data[i + 4] * frame.rows);
				int right = (int)(data[i + 5] * frame.cols);
				int bottom = (int)(data[i + 6] * frame.rows);
				int width = right - left + 1;
				int height = bottom - top + 1;
				classIds.push_back((int)(data[i + 1]) - 1); // Skip 0th background class id.
				boxes.push_back(Rect(left, top, width, height));
				confidences.push_back(confidence);
			}
		}
	}
	else
		CV_Error(Error::StsNotImplemented, "Unknown output layer type: " + outLayerType);

	std::vector<Detection> detections;
	std::vector<int> indices;
	NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];

		detections.emplace_back(classIds[idx],confidences[idx], box.x, box.y, box.width, box.height);
	}
	return detections; 
}

std::vector<String> FaceDetector::getOutputsNames(const Net& net)
{
	static std::vector<String> names;
	if (names.empty())
	{
		std::vector<int> outLayers = net.getUnconnectedOutLayers();
		std::vector<String> layersNames = net.getLayerNames();
		names.resize(outLayers.size());
		for (size_t i = 0; i < outLayers.size(); ++i)
			names[i] = layersNames[outLayers[i] - 1];
	}
	return names;
}


FaceDetector::~FaceDetector()
{
}
