#include <memory>
#include <iostream>
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include "sensor_msgs/Image.h"
#include "ninebot_zmq/ZmqPublisher.h"
#include "ninebot_zmq/image.pb.h"


void rosMsgToFrameImg(const sensor_msgs::ImageConstPtr& src, std::shared_ptr<FrameImage> dst){
    // img descriptor
    Segway_proto::StampedImage imgProto;
    auto header = imgProto.mutable_header();
    header->set_seq(src->header.seq);
    header->set_frame_id(src->header.frame_id);

    auto stamp = header->mutable_stamp();
    std::string sec_str = std::to_string(src->header.stamp.sec);
    std::string nsec_str = std::to_string(src->header.stamp.nsec);
    int64_t ts = std::stoll(sec_str + nsec_str);
    stamp->set_time_stamp(ts);

    auto image = imgProto.mutable_image();
    image->set_height(src->height);
    image->set_width(src->width);
    image->set_encoding(src->encoding);
    image->set_is_bigendian(src->is_bigendian);
    image->set_step(src->step);

    dst->msg_desc = imgProto;

    // img raw data
    size_t size = src->step * src->height;
    dst->img_data = std::make_shared<std::vector<uint8_t >>();
    dst->img_data->resize(size);
    memcpy(dst->img_data->data(), &src->data, size);
}


void imageCallback(const sensor_msgs::ImageConstPtr& msg, ZmqPublisher& mq_pub)
{
    // cv::imshow("view", cv_bridge::toCvShare(msg, "mono8")->image);
    // cv::waitKey(30);

    //time info
    std_msgs::Header h = msg->header;
    std::cout<< "pub ts: " <<h.stamp<<std::endl;
    ros::Time this_t = ros::Time::now();
    std::cout<< "sub ts: "<<this_t <<" time Diff: " << this_t - h.stamp << " frame_id: " << h.frame_id <<std::endl;

    // zmq publish
    std::shared_ptr<FrameImage> frame_pub = std::make_shared<FrameImage>();
    rosMsgToFrameImg(msg, frame_pub);
    mq_pub.pubFrame(frame_pub.get(), "image"); //TODO topic    
}

int main(int argc, char **argv)
{
    if (argc < 2){
        std::cout<< "Usage: rosrun ninebot_zmq rosZmqForwarder [ip:port]" << std::endl;
        std::cout<< "Ex: rosrun ninebot_zmq rosZmqForwarder tcp://127.0.0.1:8888" << std::endl;
        return -1;
    }

    std::cout << "=== This is ros zmq forwarder(subscribe msg from ros and publish msg through zmq)... ===" << std::endl;
    // start zmq
    std::string end_point = argv[1]; // "tcp://127.0.0.1:8888";
    ZmqPublisher mq_pub;
    mq_pub.init(end_point.c_str());
    
    // start ros
    ros::init(argc, argv, "ros_zmq_forwarder");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<sensor_msgs::Image>("image_topic", 1, std::bind(&imageCallback, std::placeholders::_1, std::ref(mq_pub)));
    ros::spin();
}


