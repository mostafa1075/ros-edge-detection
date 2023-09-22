#include <edge_detection/EdgeDetector.hpp>
#include "ros/ros.h"

using namespace edge_detection;
using namespace cv;

EdgeDetector::EdgeDetector(int threshold): threshold(threshold) {}

void EdgeDetector::detect(Mat &img, Mat &detected_edges)
{
	Mat img_gray;

	cvtColor(img, img_gray, COLOR_RGB2GRAY);
	medianBlur(img_gray, img_gray, 9);
	Canny(img_gray, detected_edges, threshold, 3 * threshold, 3);
}