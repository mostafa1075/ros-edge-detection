#include "ros/ros.h"
#include "cv_bridge/cv_bridge.h"
#include "edge_detection/PointCloudCreator.hpp"

using namespace edge_detection;
using namespace sensor_msgs;
using namespace cv;

PointCloud PointCloudCreator::create(const Image &edges, const Image &depth, const CameraInfo &camera)
{
    auto cv_depth_ptr = cv_bridge::toCvCopy(depth);
    auto cv_edges_ptr = cv_bridge::toCvCopy(edges);

    Mat maskedDepth;
    cv_depth_ptr->image.copyTo(maskedDepth, cv_edges_ptr->image);

    std::vector<Point2i> points;
    findNonZero(maskedDepth, points);

    double fx = camera.K[0];
    double fy = camera.K[4];
    double cx = camera.K[2];
    double cy = camera.K[5];
    float scale = 0.001f;

    sensor_msgs::PointCloud pc;
    pc.header = edges.header;

    for (auto &point : points)
    {
        geometry_msgs::Point32 point3d;

        uint16_t z = maskedDepth.at<uint16_t>(point.y, point.x);

        point3d.x = (point.x - cx) * z * scale / fx;
        point3d.y = (point.y - cy) * z * scale / fy;
        point3d.z = z * scale;

        pc.points.push_back(point3d);
    }

    return pc;
}
