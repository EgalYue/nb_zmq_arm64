#include "testCase.h"
#include <thread>

using namespace ninebot_algo;


static bool g_bCloseImg = false;
static bool g_bCloseLidar = false;
static bool g_bCloseIMU = false;
static bool g_bCloseEncoder = false;
static bool g_bClosePose = false;



void threadSub(std::shared_ptr<nb_zmq::ZmqSubscriber> mq_recv, std::string topic){

    if (StampedImageWithPose == topic) {
        while(1){
            subCase::Image_case(mq_recv, topic);
            if (g_bCloseImg){
                break;
            }    
        }
    } else if (StampedLidarScan == topic) {
        while(1){
            subCase::StampedLidarScan_case(mq_recv, topic);
            if (g_bCloseLidar){
                break;
            }   
        }
    } else if (StampedIMU == topic) {
        while(1){
            subCase::StampedIMU_case(mq_recv, topic);
            if (g_bCloseIMU){
                break;
            }
        }  
    } else if (StampedEncoderData == topic) {
        while(1){
            subCase::StampedEncoderData_case(mq_recv, topic);
            if (g_bCloseEncoder){
                break;
            }   
        }
    } else if (StampedLocalization == topic) {
        while(1){
            subCase::StampedLocalization_case(mq_recv, topic);
            if (g_bClosePose){
                break;
            }   
        }
    }
    
    std::cout<< ">>> Closing socket..." << std::endl;
    mq_recv->closeSocket(); //TODO... !!!!
}



void threadClose(std::shared_ptr<nb_zmq::ZmqSubscriber> mq_recv){
    while (true) {
        usleep(5000000); // 5s
        break;
    }

    std::cout << ">>> Calling terminateBlocking func ..." << std::endl;
    mq_recv->terminateBlocking();   // Important before following close signal !  

    g_bCloseImg = true;
    g_bCloseLidar = true;
    g_bCloseIMU = true;
    g_bCloseEncoder = true;
    g_bClosePose = true;
}



int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqSubAllThreadMain [ip]" << std::endl;
        std::cout<< "Ex: zmqSubAllThreadMain tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Recv... ===" << std::endl;

    std::string ip = argv[1]; // "tcp://127.0.0.1";



    nb_zmq::NodeHandle nh;
    auto mq_recv_image = nh.createSubscriber(ip, StampedImageWithPose);
    auto mq_recv_imu = nh.createSubscriber(ip, StampedIMU);
    auto mq_recv_lidar = nh.createSubscriber(ip, StampedLidarScan);
    auto mq_recv_encoder = nh.createSubscriber(ip, StampedEncoderData);
    auto mq_recv_pose = nh.createSubscriber(ip, StampedLocalization);

    std::thread th_subImage(threadSub, mq_recv_image, StampedImageWithPose);
    std::thread th_subIMU(threadSub, mq_recv_imu, StampedIMU);
    std::thread th_subLidar(threadSub, mq_recv_lidar, StampedLidarScan);
    // std::thread th_subEncoder(threadSub, mq_recv_encoder, StampedEncoderData);
    // std::thread th_subPose(threadSub, mq_recv_pose, StampedLocalization);

    std::thread th_close_image(threadClose, mq_recv_image);
    std::thread th_close_imu(threadClose, mq_recv_imu);
    std::thread th_close_lidar(threadClose, mq_recv_lidar);

    if (th_close_image.joinable()){
        th_close_image.join();
    }

    if (th_close_imu.joinable()){
        th_close_imu.join();
    }

    if (th_close_lidar.joinable()){
        th_close_lidar.join();
    }


    if (th_subImage.joinable()){
        th_subImage.join();
    }

    if (th_subIMU.joinable()){
        th_subIMU.join();
    }

    if (th_subLidar.joinable()){
        th_subLidar.join();
    }

    // if (th_subEncoder.joinable()){
    //     th_subEncoder.join();
    // }

    // if (th_subPose.joinable()){
    //     th_subPose.join();
    // }



    std::cout<< " --- end ---" << std::endl;
    return 0;
}