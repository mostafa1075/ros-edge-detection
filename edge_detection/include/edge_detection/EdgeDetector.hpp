#pragma once
#include "opencv2/imgproc.hpp"


namespace edge_detection
{
	class EdgeDetector
	{
		int threshold;
	public:
		EdgeDetector(int threshold);
		void detect(cv::Mat &img, cv::Mat &detected_edges);
	};

}