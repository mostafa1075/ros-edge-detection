#include "opencv2/imgproc.hpp"

void superimpose(cv::Mat& img, cv::Mat& overlay, cv::Mat& superimposed){
    cv::Mat green;

    green.create(img.size(), img.type());
    green = cv::Scalar(0, 255, 0);

    img.copyTo(superimposed);
    green.copyTo(superimposed, overlay);
}