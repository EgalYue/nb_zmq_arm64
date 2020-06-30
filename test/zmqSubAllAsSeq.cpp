#include "testCase.h"
#include "ninebot_zmq/Control.h"
#include <thread>

using namespace ninebot_algo;


static bool g_bCloseSubscribe = false;

void threadSub(std::string ip){
    nb_zmq::ZmqSubscriber mq_recv;
    if(mq_recv.init(ip, AllType) < 0){
        std::cout << "[ZMQ Subscriber]: Error can not connect to endpoint!" << std::endl;
        return;
    }
    while(!g_bCloseSubscribe){
        std::string topic = StampedImageWithPose;
        subCase::Image_case(mq_recv, topic, true);
        topic = StampedIMU;
        subCase::StampedIMU_case(mq_recv, topic, true);
        topic = StampedLidarScan;
        subCase::StampedLidarScan_case(mq_recv, topic, true);
        topic = StampedEncoderData;
        subCase::StampedEncoderData_case(mq_recv, topic, true);
        topic = StampedPose3Dd;
        subCase::StampedPose3Dd_case(mq_recv, topic, true);
    }
    mq_recv.close();
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
        std::cout<< "Usage: zmqSubAllAsSeq [ip]" << std::endl;
        std::cout<< "Ex: zmqSubAllAsSeq tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Recv... ===" << std::endl;

    std::string ip = argv[1]; // "tcp://127.0.0.1";

    g_bCloseSubscribe = false;

    std::thread th_subRun(threadSub, ip);
    std::thread th_close(threadClose);

    if (th_close.joinable()){
        th_close.join();
    }
    if (th_subRun.joinable()){
        th_subRun.join();
    }

    std::cout<< " --- end ---" << std::endl;
    return 0;
}