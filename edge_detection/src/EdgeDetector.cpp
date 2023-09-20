#include <edge_detection/EdgeDetector.hpp>
#include "ros/ros.h"

using namespace edge_detection;


void EdgeDetector::detect(Mat &img, Mat &detected_edges, int threshold)
{
	Mat img_gray, green;

	cvtColor(img, img_gray, COLOR_RGB2GRAY);
	medianBlur(img_gray, img_gray, 9);
	Canny(img_gray, img_gray, threshold, 3 * threshold, 3);

	img.copyTo(detected_edges);

	green.create(img.size(), img.type());
	green = Scalar(0, 255, 0);
	green.copyTo(detected_edges, img_gray);
}

