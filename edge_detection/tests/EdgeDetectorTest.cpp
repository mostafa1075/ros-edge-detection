#include "ros/ros.h"
#include "opencv2/highgui.hpp"
#include "edge_detection/EdgeDetector.hpp"
#include "edge_detection/utils.hpp"

using namespace cv;

/**
 * For testing the edge detection with sample images. 
 * Needs image file path and edge detection threshold as arguments.
 */
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		return 1;
	}

	edge_detection::EdgeDetector detector(atoi(argv[2]), atoi(argv[3]));
	Mat img = imread(argv[1]), detected_edges;

	Mat superimposed;
	detector.detect(img, detected_edges);
	superimpose(img, detected_edges, superimposed);

	imshow("Test Display", superimposed);
	waitKey(0);

	return 0;
}
