#pragma once
#include "opencv2/imgproc.hpp"


namespace edge_detection
{
	class EdgeDetector
	{
		int threshold;
		int blur_kernel;
	public:
		EdgeDetector(int threshold = 100, int blur_kernel = 3);
		void detect(cv::Mat &img, cv::Mat &detected_edges);
	};

}