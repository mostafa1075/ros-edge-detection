#include <edge_detection/EdgeDetector.hpp>

/**
 * For testing the edge detection with sample images. Needs image file path as argument.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		return 1;
	}

	edge_detection::EdgeDetector detector;
	Mat img = imread(argv[1]), detected_edges;

	detector.detect(img, detected_edges);

	imshow("Test Display", detected_edges);
	waitKey(0);

	return 0;
}
