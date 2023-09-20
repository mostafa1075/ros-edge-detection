#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

namespace edge_detection
{
	class EdgeDetector
	{
		int threshold;
	public:
		EdgeDetector(int threshold);
		void detect(Mat &img, Mat &detected_edges);
	};

}