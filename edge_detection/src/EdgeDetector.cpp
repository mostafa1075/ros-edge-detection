#include <edge_detection/EdgeDetector.hpp>
#include "ros/ros.h"

using namespace edge_detection;


void EdgeDetector::detect(Mat &img, Mat &detected_edges, int threshold = 50)
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

/**
 * For testing the edge detection with sample images. Needs image file path as argument.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ROS_INFO("Missing file argument");
		return 1;
	}

	edge_detection::EdgeDetector detector;
	Mat img = imread(argv[1]), detected_edges;

	detector.detect(img, detected_edges);

	imshow("Test Display", detected_edges);
	waitKey(0);

	return 0;
}
