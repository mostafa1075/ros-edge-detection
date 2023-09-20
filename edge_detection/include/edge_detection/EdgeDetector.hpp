#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

namespace edge_detection
{
	class EdgeDetector
	{
	public:
		void detect(Mat &img, Mat &detected_edges, int threshold);
	};

}