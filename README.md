# ROS Edge Detection
 
## Introduction
Edge detection is a preliminary but important step in computer vision. The goal of this challenge is to detect the edges of a checkboard image and visualize them in 3D.

## Preliminary Requirements
1. Install ROS Noetic and OpenCV
2. Create a catkin workspace
3. Clone this repository into the src/ directory of your workspace
4. Set `OpenCV_DIR` in edge_detection/CMakeLists.txt:
```
set(OpenCV_DIR "<path>") 
```

5. Build project:
```
cd <path to catkin workspace>
catkin_make
```


## Results
### 1. Basic 
In order to detect edges in an image launch the `basic.launch` file:

```
roslaunch edge_detection basic.launch path:=<path to image> threshold:=<optional edge detection threshold> blur_kernel:=<optional blur kernel size>
```
The optional blur kernel size and the edge detection threshold are passed as arguments as needed. However, the default values work well for this step and for the next ones.

The implementation steps are:
1. The image is blurred in order to remove any noise that would be detected as false edges. A median blurring filter is applied which works well with salt and pepper noise. It also doesn't impact the detection of true edges as its smoothing effect on edges is small. 
2. The Canny edge detector is applied which relies on the image intensity gradients. 

A possible improvement would be a noise reduction method that balances between removing noise and maintaining the fine details needed for edge detection.
### 2. Vision_ROS: 

<p align="center">
  <img src="media/vision_ros.gif" alt="animated" />
</p>

An ROS service was created for edge detection. A client was created to test and visualize the output of this service:
```
#Terminal 1
roscore

#Terminal 2
roslaunch edge_detection vision_ros.launch threshold:=<optional edge detection threshold> blur_kernel:=<optional blur kernel size>

#Terminal 3
rosbag play --clock -l <path to bagfile>
```

### 3. Robot_ROS: 

<p align="center">
  <img src="media/robot_ros.gif" alt="animated" />
</p>

In this step, we attempt to visualize the detected edges in 3D. Given a depth image:
1. Mask it using the detected edges.
2. Unproject the pixel points using the camera intrinsics and the pixel's depth.
3. Display the points in the optical camera frame.

To detect and visualize the 3D edge points, run:
```
#Terminal 1
roscore

#Terminal 2
roslaunch edge_detection robot_ros.launch threshold:=<optional edge detection threshold> blur_kernel:=<optional blur kernel size>

#Terminal 3
rosbag play --clock -l <path to bagfile>
```
