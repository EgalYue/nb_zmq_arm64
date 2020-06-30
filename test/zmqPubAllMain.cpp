#include <thread>
#include "testCase.h"
#include "ninebot_zmq/Control.h"


using namespace ninebot_algo;


static bool g_bClosePublish = false;

void threadPub(std::string& ip, std::string& msgType, std::string& topic){
    nb_zmq::ZmqPublisher mq_pub;
    if (mq_pub.init(ip, msgType) < 0){
        std::cout << "[ZMQ Pulisher]: Error can not bind endpoint !" << std::endl;
        return;
    }

    if (StampedImageWithPose == topic) {
        //pubCase::Image_case(mq_pub, filepath, topic);
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(1000000); // 1Hz
            pubCase::Image_case(mq_pub, topic, frame_id);
            frame_id++;
        }
        mq_pub.close();
    } else if (StampedIMU == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(5000); // 200Hz
            pubCase::StampedIMU_case(mq_pub, topic, frame_id);
            frame_id++;
        }
        mq_pub.close();
    } else if (StampedLidarScan == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(100000); // 10Hz
            pubCase::StampedLidarScan_case(mq_pub, topic, frame_id);
            frame_id++;
        }
        mq_pub.close();
    } else if (StampedEncoderData == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(50000); // 20Hz
            pubCase::StampedEncoderData_case(mq_pub, topic, frame_id);
            frame_id++;
        }
        mq_pub.close();
    } else if (StampedPose3Dd == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(50000); // 20Hz
            pubCase::StampedPose3Dd_case(mq_pub, topic, frame_id);
            frame_id++;
        }
        mq_pub.close();
    }
}

void threadClose(){
    while (true) {
        usleep(5000000); // 10s
        break;
    }

    nb_zmq::Control ctl;
    g_bClosePublish = ctl.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqPubAll [ip] " << std::endl;
        std::cout<< "Ex: zmqPubAll tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is pubAll ... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    
    {
        std::cout << "========= Pub StampedImageWithPose =========="<<std::endl; 
        g_bClosePublish = false;
        std::string temp = StampedImageWithPose;
        std::thread th_pub(threadPub, std::ref(ip), std::ref(temp), std::ref(temp));
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_pub.joinable()) {
        th_pub.join();
        }
        usleep(1000000);
    }

    {
        std::cout << "========= Pub StampedIMU =========="<<std::endl; 
        g_bClosePublish = false;
        std::string temp = StampedIMU;
        std::thread th_pub(threadPub, std::ref(ip), std::ref(temp), std::ref(temp));
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_pub.joinable()) {
        th_pub.join();
        }
        usleep(1000000);
    }

    {
        std::cout << "========= Pub StampedLidarScan =========="<<std::endl; 
        g_bClosePublish = false;
        std::string temp = StampedLidarScan;
        std::thread th_pub(threadPub, std::ref(ip), std::ref(temp), std::ref(temp));
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_pub.joinable()) {
        th_pub.join();
        }
        usleep(1000000);
    }

    {
        std::cout << "========= Pub StampedEncoderData =========="<<std::endl; 
        g_bClosePublish = false;
        std::string temp = StampedEncoderData;
        std::thread th_pub(threadPub, std::ref(ip), std::ref(temp), std::ref(temp));
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_pub.joinable()) {
        th_pub.join();
        }
        usleep(1000000);
    }

    {
        std::cout << "========= Pub StampedPose3Dd =========="<<std::endl; 
        g_bClosePublish = false;
        std::string temp = StampedPose3Dd;
        std::thread th_pub(threadPub, std::ref(ip), std::ref(temp), std::ref(temp));
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if (th_pub.joinable()) {
        th_pub.join();
        }
        usleep(1000000);
    }   

    
    std::cout<< " --- end ---" << std::endl;
    return 0;
}