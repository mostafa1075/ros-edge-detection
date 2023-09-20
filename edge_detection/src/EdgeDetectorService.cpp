#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "edge_detection/DetectEdges.h"
#include <edge_detection/EdgeDetector.hpp>

using namespace edge_detection;


int main(int argc, char **argv)
{
    ros::init(argc, argv, "edge_detection_service");
    ros::NodeHandle n;

    EdgeDetector detector(atoi(argv[1]));

    ros::ServiceServer service = n.advertiseService<DetectEdges::Request, DetectEdges::Response>(
        "detect_edges",
        [&](DetectEdges::Request &req, DetectEdges::Response &res) {
            auto cv_ptr = cv_bridge::toCvCopy(req.img);
            detector.detect(cv_ptr->image, cv_ptr->image);
            res.edges = *(cv_ptr->toImageMsg());

            return true;
        }
    );
    
    ROS_INFO("Ready to detect edges");
    ros::spin();

    return 0;
}