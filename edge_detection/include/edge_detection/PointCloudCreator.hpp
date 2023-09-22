#pragma once
#include "sensor_msgs/Image.h"
#include "sensor_msgs/CameraInfo.h"
#include "sensor_msgs/PointCloud.h"


namespace edge_detection
{
    class PointCloudCreator
    {
        public:
        sensor_msgs::PointCloud create(const sensor_msgs::Image& image, const sensor_msgs::Image& depth, const sensor_msgs::CameraInfo& camera);
    };
}