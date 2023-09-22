#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "cv_bridge/cv_bridge.h"
#include "edge_detection/DetectEdges.h"
#include "edge_detection/utils.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "edge_detection_test_client");

    ros::NodeHandle n;
    ros::ServiceClient edge_client = n.serviceClient<edge_detection::DetectEdges>("detect_edges");
    ros::Publisher edge_pub = n.advertise<sensor_msgs::Image>("/camera/color/detect_edges", 1000);

    ros::Subscriber sub = n.subscribe<sensor_msgs::Image>(
        "/camera/color/image_raw",
        1000,
        [&](const sensor_msgs::ImageConstPtr &img)
        {
            edge_detection::DetectEdges srv;

            srv.request.img = *img;
            if (edge_client.call(srv))
            {
                cv::Mat superimposed;
                cv_bridge::CvImagePtr cv_edges_ptr = cv_bridge::toCvCopy(srv.response.edges);
                cv_bridge::CvImagePtr cv_img_ptr = cv_bridge::toCvCopy(*img);

                superimpose(cv_img_ptr->image, cv_edges_ptr->image, superimposed);
                cv_img_ptr->image = superimposed;
                
                edge_pub.publish(cv_img_ptr->toImageMsg());
            }
            else
            {
                ROS_ERROR("Failed to call service detect_edges");
            }
        });

    ros::spin();

    return 0;
}