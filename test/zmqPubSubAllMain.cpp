#include "testCase.h"
#include "ninebot_zmq/Control.h"
#include <thread>

using namespace ninebot_algo;


static bool g_bClosePublish = false;
static bool g_bCloseSubscribe = false;

void threadPub(std::string msgType, std::string topic){
    nb_zmq::ZmqPublisher mq_pub;
    std::string ipPub = "tcp://*"; // localhost as default
    if(mq_pub.init(ipPub, msgType) < 0){
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


void threadSub(std::string ipSub, std::string msgType, std::string topic){
    nb_zmq::ZmqSubscriber mq_recv;
    if(mq_recv.init(ipSub, msgType) < 0){
        std::cout << "[ZMQ Subscriber]: Error can not connect to endpoint!" << std::endl;
        return;
    }

    if (StampedImageWithPose == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubscribe){
            subCase::Image_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedIMU == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubscribe){
            subCase::StampedIMU_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedLidarScan == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubscribe){
            subCase::StampedLidarScan_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedEncoderData == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubscribe){
            subCase::StampedEncoderData_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } else if (StampedPose3Dd == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubscribe){
            subCase::StampedPose3Dd_case(mq_recv, topic, true);
        }
        mq_recv.close();
    } 
}


void* threadClosePub(){
    while (true) {
        usleep(5000000); // 5s
        break;
    }

    nb_zmq::Control ctl;
    g_bClosePublish = ctl.close();
}


void* threadCloseSub(){
    while (true) {
        usleep(5000000); // 5s
        break;
    }

    nb_zmq::Control ctl;
    g_bCloseSubscribe = ctl.close();
}


/*
 * Pub msg first and then sub msg.
 * [pub-ip] is "tcp://*" as default
 * [sub-ip] is the ip of subscriber
 */
int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqPubSubAll [sub-ip]" << std::endl;
        std::cout<< "Ex: zmqPubSubAll tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Pub Sub... ===" << std::endl;
    //std::string filepath = argv[2];
    std::string ipSub = argv[1]; // "tcp://127.0.0.1";
    
    {
        std::cout<< "======== PubSub StampedImageWithPose ========"<<std::endl;
        g_bClosePublish = false;
        g_bCloseSubscribe = false;
        std::string temp = StampedImageWithPose;
        std::thread th_pub(threadPub, temp, temp);
        std::thread th_sub(threadSub, ipSub, temp, temp);
        std::thread th_close_pub(threadClosePub);
        std::thread th_close_sub(threadCloseSub);

        if (th_close_pub.joinable()){
            th_close_pub.join();
        }
        if (th_close_sub.joinable()){
            th_close_sub.join();
        }
        if (th_pub.joinable()){
            th_pub.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedIMU ========"<<std::endl;
        g_bClosePublish = false;
        g_bCloseSubscribe = false;
        std::string temp = StampedIMU;
        std::thread th_pub(threadPub, temp, temp);
        std::thread th_sub(threadSub, ipSub, temp, temp);
        std::thread th_close_pub(threadClosePub);
        std::thread th_close_sub(threadCloseSub);

        if (th_close_pub.joinable()){
            th_close_pub.join();
        }
        if (th_close_sub.joinable()){
            th_close_sub.join();
        }
        if (th_pub.joinable()){
            th_pub.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedLidarScan ========"<<std::endl;
        g_bClosePublish = false;
        g_bCloseSubscribe = false;
        std::string temp = StampedLidarScan;
        std::thread th_pub(threadPub, temp, temp);
        std::thread th_sub(threadSub, ipSub, temp, temp);
        std::thread th_close_pub(threadClosePub);
        std::thread th_close_sub(threadCloseSub);

        if (th_close_pub.joinable()){
            th_close_pub.join();
        }
        if (th_close_sub.joinable()){
            th_close_sub.join();
        }
        if (th_pub.joinable()){
            th_pub.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedEncoderData ========"<<std::endl;
        g_bClosePublish = false;
        g_bCloseSubscribe = false;
        std::string temp = StampedEncoderData;
        std::thread th_pub(threadPub, temp, temp);
        std::thread th_sub(threadSub, ipSub, temp, temp);
        std::thread th_close_pub(threadClosePub);
        std::thread th_close_sub(threadCloseSub);

        if (th_close_pub.joinable()){
            th_close_pub.join();
        }
        if (th_close_sub.joinable()){
            th_close_sub.join();
        }
        if (th_pub.joinable()){
            th_pub.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedPose3Dd ========"<<std::endl;
        g_bClosePublish = false;
        g_bCloseSubscribe = false;
        std::string temp = StampedPose3Dd;
        std::thread th_pub(threadPub, temp, temp);
        std::thread th_sub(threadSub, ipSub, temp, temp);
        std::thread th_close_pub(threadClosePub);
        std::thread th_close_sub(threadCloseSub);

        if (th_close_pub.joinable()){
            th_close_pub.join();
        }
        if (th_close_sub.joinable()){
            th_close_sub.join();
        }
        if (th_pub.joinable()){
            th_pub.join();
        }
        if (th_sub.joinable()){
            th_sub.join();
        }
        usleep(1000000);
    }      

    std::cout<< " --- end ---" << std::endl;
    return 0;
}