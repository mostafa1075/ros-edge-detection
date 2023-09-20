#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "edge_detection/DetectEdges.h"
#include <edge_detection/EdgeDetector.hpp>

using namespace edge_detection;

bool detect(DetectEdges::Request &req, DetectEdges::Response &res) {
    EdgeDetector detector;
    auto cv_ptr = cv_bridge::toCvCopy(req.img);
    detector.detect(cv_ptr->image, cv_ptr->image);
    res.edges = *(cv_ptr->toImageMsg());

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "edge_detection_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("detect_edges", detect);
    ROS_INFO("Ready to detect edges");
    ros::spin();

    return 0;
}