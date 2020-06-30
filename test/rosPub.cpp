#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>


void readImg(const std::string& dirpath, int imgNr, cv::Mat& cur_img){
    std::string posfix = ".pgm";
    std::string file = dirpath + "/" + std::to_string(imgNr) + posfix;
    std::cout<< "Img path: " << file << std::endl;
    cur_img = cv::imread(file,CV_LOAD_IMAGE_GRAYSCALE);
//    cv::imshow("test", cur_img);
//    cv::waitKey(1);
}

int main(int argc, char** argv)
{
  if (argc < 2){
    std::cout<< "Usage: rosrun ninebot_zmq rosPub [img_folder]" << std::endl;
    std::cout<< "Ex: rosrun ninebot_zmq rosPub /home/nb/Desktop/zmq_test_data/fisheye" << std::endl;
    return -1;
  }
  std::string filepath = argv[1];// "/home/yuehu/Desktop/zmq_test_data/fisheye";

  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("image_topic", 1);
  ros::Rate loop_rate(10);

  cv::Mat cur_img;
  int frame_id = 0;
  while (nh.ok() && frame_id < 1000) {
    readImg(filepath, frame_id,cur_img); // read img from local

    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", cur_img).toImageMsg();
    msg->header.frame_id = std::to_string(frame_id);
    msg->header.stamp = ros::Time::now();
    frame_id++;    
    std::cout<<"Send time: " <<msg->header.stamp<<" frame_id: " << msg->header.frame_id<<std::endl;

    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}