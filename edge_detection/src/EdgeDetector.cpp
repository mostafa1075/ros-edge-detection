#include <edge_detection/EdgeDetector.hpp>
#include "ros/ros.h"

using namespace edge_detection;
using namespace cv;

EdgeDetector::EdgeDetector(int threshold, int blur_kernel): 
threshold(threshold), blur_kernel(blur_kernel)  {}

void EdgeDetector::detect(Mat &img, Mat &detected_edges)
{
	Mat img_gray;

	cvtColor(img, img_gray, COLOR_RGB2GRAY);
	medianBlur(img_gray, img_gray, blur_kernel);
	Canny(img_gray, detected_edges, threshold, 3 * threshold);
}