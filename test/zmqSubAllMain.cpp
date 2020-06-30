#include "testCase.h"
#include "ninebot_zmq/Control.h"
#include <thread>

using namespace ninebot_algo;


static bool g_bCloseSubscribe = false;

void threadSub(std::string ip, std::string msgType, std::string topic){
    nb_zmq::ZmqSubscriber mq_recv;
    if(mq_recv.init(ip, msgType) < 0){
        std::cout << "[ZMQ Subscriber]: Error can not connect to endpoint!" << std::endl;
        return;
    }

    if (StampedImageWithPose == topic) {
        while(!g_bCloseSubscribe){
            subCase::Image_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedIMU == topic) {
        while(!g_bCloseSubscribe){
            subCase::StampedIMU_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedLidarScan == topic) {
        while(!g_bCloseSubscribe){
            subCase::StampedLidarScan_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedEncoderData == topic) {
        while(!g_bCloseSubscribe){
            subCase::StampedEncoderData_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedPose3Dd == topic) {
        while(!g_bCloseSubscribe){
            subCase::StampedPose3Dd_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } 
}

void threadClose(){
    while (true) {
        usleep(5000000); // 5s
        break;
    }

    nb_zmq::Control ctl;
    g_bCloseSubscribe = ctl.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqSubAll [ip]" << std::endl;
        std::cout<< "Ex: zmqSubAll tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Recv... ===" << std::endl;

    std::string ip = argv[1]; // "tcp://127.0.0.1";

    {   
        std::cout << "========= Sub StampedImageWithPose =========="<<std::endl; 
        g_bCloseSubscribe = false;
        std::thread th_sub(threadSub, ip, StampedImageWithPose, StampedImageWithPose);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    { 
        std::cout << "========= Sub StampedIMU =========="<<std::endl; 
        g_bCloseSubscribe = false;
        std::thread th_sub(threadSub, ip, StampedIMU, StampedIMU);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    { 
        std::cout << "========= Sub StampedLidarScan =========="<<std::endl; 
        g_bCloseSubscribe = false;
        std::thread th_sub(threadSub, ip, StampedLidarScan, StampedLidarScan);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    { 
        std::cout << "========= Sub StampedEncoderData =========="<<std::endl; 
        g_bCloseSubscribe = false;
        std::thread th_sub(threadSub, ip, StampedEncoderData, StampedEncoderData);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    { 
        std::cout << "========= Sub StampedPose3Dd =========="<<std::endl; 
        g_bCloseSubscribe = false;
        std::thread th_sub(threadSub, ip, StampedPose3Dd, StampedPose3Dd);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    std::cout<< " --- end ---" << std::endl;
    return 0;
}