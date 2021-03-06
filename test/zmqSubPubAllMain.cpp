#include "testCase.h"
#include "ninebot_zmq/Control.h"
#include <thread>

using namespace ninebot_algo;



static bool g_bCloseSubPub = false;

void threadSubPub(std::string ipSub, std::string msgType, std::string topic){
    nb_zmq::ZmqSubscriber mq_recv;
    if(mq_recv.init(ipSub, msgType) < 0){
        std::cout << "[ZMQ Subscriber]: Error can not connect to endpoint!" << std::endl;
        return;
    }

    nb_zmq::ZmqPublisher mq_pub;
    std::string ipPub = "tcp://*"; // localhost as default
    if(mq_pub.init(ipPub, msgType) < 0){
        std::cout << "[ZMQ Pulisher]: Error can not bind endpoint !" << std::endl; 
        return;
    }

    if (StampedImageWithPose == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubPub){
            subPubCase::Image_case(mq_recv, mq_pub, topic);
        }
        mq_recv.close();
        mq_pub.close();
    } else if (StampedIMU == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubPub){
            subPubCase::StampedIMU_case(mq_recv, mq_pub, topic);
        }
        mq_recv.close();
        mq_pub.close();
    } else if (StampedLidarScan == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubPub){
            subPubCase::StampedLidarScan_case(mq_recv, mq_pub, topic);
        }
        mq_recv.close();
        mq_pub.close();
    } else if (StampedEncoderData == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubPub){
            subPubCase::StampedEncoderData_case(mq_recv, mq_pub, topic);
        }
        mq_recv.close();
        mq_pub.close();
    } else if (StampedPose3Dd == topic) {
        int nRecvFailCount = 0;
        while(!g_bCloseSubPub){
            subPubCase::StampedPose3Dd_case(mq_recv, mq_pub, topic);
        }
        mq_recv.close();
        mq_pub.close();
    } 
}


void* threadClose(){
    while (true) {
        usleep(5000000); // 10s
        break;
    }

    nb_zmq::Control ctl;
    g_bCloseSubPub = ctl.close();
}


/*
 * Sub msg first and then pub msg.
 * [pub-ip] is "tcp://*" as default
 * [sub-ip] is the ip of subscriber
 */
int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqSubPubAll [sub-ip]" << std::endl;
        std::cout<< "Ex: zmqSubPubAll tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Sub pub all... ===" << std::endl;

    std::string ipSub = argv[1]; // "tcp://127.0.0.1";

    {
        std::cout<< "======== PubSub StampedImageWithPose ========"<<std::endl;
        g_bCloseSubPub = false;
        std::thread th_subpub(threadSubPub, ipSub, StampedImageWithPose, StampedImageWithPose);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if(th_subpub.joinable()){
            th_subpub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedIMU ========"<<std::endl;
        g_bCloseSubPub = false;
        std::thread th_subpub(threadSubPub, ipSub, StampedIMU, StampedIMU);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if(th_subpub.joinable()){
            th_subpub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedLidarScan ========"<<std::endl;
        g_bCloseSubPub = false;
        std::thread th_subpub(threadSubPub, ipSub, StampedLidarScan, StampedLidarScan);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if(th_subpub.joinable()){
            th_subpub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedEncoderData ========"<<std::endl;
        g_bCloseSubPub = false;
        std::thread th_subpub(threadSubPub, ipSub, StampedEncoderData, StampedEncoderData);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if(th_subpub.joinable()){
            th_subpub.join();
        }
        usleep(1000000);
    }

    {
        std::cout<< "======== PubSub StampedPose3Dd ========"<<std::endl;
        g_bCloseSubPub = false;
        std::thread th_subpub(threadSubPub, ipSub, StampedPose3Dd, StampedPose3Dd);
        std::thread th_close(threadClose);

        if (th_close.joinable()){
            th_close.join();
        }
        if(th_subpub.joinable()){
            th_subpub.join();
        }
        usleep(1000000);
    }


    std::cout<< " --- end ---" << std::endl;
    return 0;
}
