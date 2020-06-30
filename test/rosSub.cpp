#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "sensor_msgs/Image.h"


void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  // cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
  // cv::waitKey(30);

  //time info
  std_msgs::Header h = msg->header;
  std::cout<< "pub ts: " <<h.stamp<<std::endl;
  ros::Time this_t = ros::Time::now();
  std::cout<< "sub ts: "<< this_t <<" time Diff: " << this_t - h.stamp << " frame_id: " << h.frame_id <<std::endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_sub");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe<sensor_msgs::Image> ("image_topic", 1, imageCallback);
  ros::spin();
}