#include "testCase.h"
#include <thread>

using namespace ninebot_algo;



void threadSub(nb_zmq::ZmqSubscriber& mq_recv, std::string ip, std::string msgType, std::string topic){
    if (StampedImageWithPose == topic) {
        while(1){
            if (subCase::Image_case(mq_recv, topic, false) < 0){
                break;
            }
        }
    } else if (StampedLidarScan == topic) {
        while(1){
            if (subCase::StampedLidarScan_case(mq_recv, topic, false) < 0){
                break;
            }
        }
    } else if (StampedIMU == topic) {
        while(1){
            if(subCase::StampedIMU_case(mq_recv, topic, false) < 0){
                break;
            }
        }  
    } else if (StampedEncoderData == topic) {
        while(1){
            if(subCase::StampedEncoderData_case(mq_recv, topic, false) < 0){
                break;
            }
        }
    } else if (StampedPose3Dd == topic) {
        while(1){
            if(subCase::StampedPose3Dd_case(mq_recv, topic, false) < 0){
                break;
            }
        }
    } 
}

void* threadClose(nb_zmq::ZmqSubscriber& mq_recv){
    while (true) {
        usleep(5000000); // 10s
        break;
    }
    mq_recv.close();
}

int main(int argc, char *argv[]) {
    if (argc < 4){
        std::cout<< "Usage: zmqSub [ip] msgType topic" << std::endl;
        std::cout<< "Ex: zmqSub tcp://127.0.0.1 StampedImageWithPose StampedImageWithPose" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Recv... ===" << std::endl;

    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2]; // "StampedImageWithPose"
    std::string topic = argv[3];

    nb_zmq::ZmqSubscriber mq_recv;
    if(mq_recv.init(ip, msgType) < 0){
        std::cout << "[ZMQ Subscriber]: Error can not connect to endpoint!" << std::endl;
        return -1;
    }

    std::thread th_sub(threadSub, std::ref(mq_recv), ip, msgType, topic);
    std::thread th_close(threadClose, std::ref(mq_recv));

    if (th_close.joinable()){
        th_close.join();
    }
    if (th_sub.joinable()){
        th_sub.join();
    }

    std::cout<< " --- end ---" << std::endl;
    return 0;
}