#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include "ninebot_zmq/ZmqSubscriber.h" 
#include "ninebot_zmq/image.pb.h"


void FrameImgToRosImg(const std::shared_ptr<FrameImage>& src, sensor_msgs::ImagePtr dst){
    dst->header.seq = src->msg_desc.header().seq();
    dst->header.frame_id = src->msg_desc.header().frame_id();
    //TODO header time, maybe need to modify
    std::string ts = std::to_string(src->msg_desc.header().stamp().time_stamp());
    std::string::size_type sz;
    dst->header.stamp.sec = std::stoi (ts.substr(0, 10),&sz);
    dst->header.stamp.nsec = std::stoi (ts.substr(10, ts.length()-1),&sz);

    dst->height = src->msg_desc.image().height();
    dst->width = src->msg_desc.image().width();
    dst->encoding = src->msg_desc.image().encoding();
    dst->is_bigendian = src->msg_desc.image().is_bigendian();
    dst->step = src->msg_desc.image().step();
    size_t size = dst->step * dst->height;
    dst->data.resize(size);
    memcpy((char*)(&dst->data[0]), src->img_data->data(), size);
}

int main(int argc, char** argv)
{   
    if (argc < 2){
        std::cout<< "Usage: rosrun ninebot_zmq zmqRosForwarder [ip:port]" << std::endl;
        std::cout<< "Ex: rosrun ninebot_zmq zmqRosForwarder tcp://127.0.0.1:8888" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq_ros_forwarder, (receive zmq msg and publish ros msg) ... ===" << std::endl;

    // start ros
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<sensor_msgs::Image> ("image_topic", 1);
    ros::Rate loop_rate(10);
    
    // start zmq
    ZmqSubscriber mq_recv;
    std::string end_point = argv[1]; // "tcp://127.0.0.1:8888";
    mq_recv.init(end_point.c_str());

    std::shared_ptr<FrameImage> frame_recv = std::make_shared<FrameImage>();
    int nRecvFailCount = 0;
    while(nh.ok()){
        if (!mq_recv.recvFrame(frame_recv.get(), "image")) { //TODO topic
            std::cout << "Recv Frame Timeout" << std::endl;
            {
                nRecvFailCount++;
                if (nRecvFailCount > 100) {
                    mq_recv.reconnect();
                    nRecvFailCount = 0;
                }
            }
            continue;
        }

        std::cout<< ">>>frameImg ts: "<< frame_recv->msg_desc.header().stamp().time_stamp()<<std::endl;
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>
                          (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout<< ">>> Curr ts:" << curr_ts << std::endl;
        printf("Diff time: %10.9f\n",(double)(curr_ts - frame_recv->msg_desc.header().stamp().time_stamp()) / 1000000000);

        sensor_msgs::ImagePtr msg = boost::make_shared<sensor_msgs::Image>();
        FrameImgToRosImg(frame_recv, msg);
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}