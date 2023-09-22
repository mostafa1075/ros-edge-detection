#include "ros/ros.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "edge_detection/DetectEdges.h"
#include "edge_detection/PointCloudCreator.hpp"

using namespace sensor_msgs;

void callback(const ImageConstPtr &img, const ImageConstPtr &depth, const CameraInfoConstPtr &info, ros::ServiceClient &edge_client, ros::Publisher &pointcloud_pub)
{
    edge_detection::DetectEdges srv;
    srv.request.img = *img;
    if (edge_client.call(srv))
    {
        edge_detection::PointCloudCreator pcCreator;
        auto cloud = pcCreator.create(srv.response.edges, *depth, *info);

        pointcloud_pub.publish(cloud);
    }
    else
    {
        ROS_ERROR("Failed to call service detect_edges");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "edge_detection_3D_points");

    ros::NodeHandle n;
    ros::ServiceClient edge_client = n.serviceClient<edge_detection::DetectEdges>("detect_edges");
    ros::Publisher pointcloud_pub = n.advertise<PointCloud>("/camera/edges/points", 1000);

    message_filters::Subscriber<Image> image_sub(n, "/camera/color/image_raw", 1);
    message_filters::Subscriber<Image> depth_sub(n, "/camera/depth/image_rect_raw", 1);
    message_filters::Subscriber<CameraInfo> info_sub(n, "/camera/depth/camera_info", 1);

    message_filters::TimeSynchronizer<Image, Image, CameraInfo> sync(image_sub, depth_sub, info_sub, 10);

    sync.registerCallback(boost::bind(&callback, _1, _2, _3, edge_client, pointcloud_pub));

    ros::spin();

    return 0;
}