#include "testCase.h"
#include <thread>

using namespace ninebot_algo;
static bool g_closeSignal = false;



void threadSub(std::shared_ptr<nb_zmq::ZmqSubscriber> mq_recv, std::string topic){

    if (StampedImageWithPose == topic) {
        while(1){
            subCase::Image_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }    
        }
    } else if (StampedLidarScan == topic) {
        while(1){
            subCase::StampedLidarScan_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    } else if (StampedIMU == topic) {
        while(1){
            subCase::StampedIMU_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }
        }  
    } else if (StampedEncoderData == topic) {
        while(1){
            subCase::StampedEncoderData_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    } else if (StampedLocalization == topic) {
        while(1){
            subCase::StampedLocalization_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    } else if (TsWithID == topic) {
        while(1){
            subCase::TsWithID_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    }
    
    std::cout<< ">>> Closing socket..." << std::endl;
    mq_recv->closeSocket(); //TODO... !!!!
}

void threadClose(std::shared_ptr<nb_zmq::ZmqSubscriber>  mq_recv){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    // mq_recv->terminateBlocking();   
    // g_closeSignal = true;
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

    nb_zmq::NodeHandle nh;
    auto mq_recvPtr = nh.createSubscriber(ip, msgType);

    std::thread th_sub(threadSub, mq_recvPtr, topic);
    std::thread th_close(threadClose, mq_recvPtr);


    if (th_sub.joinable()){
        th_sub.join();
    }
    if (th_close.joinable()){
        th_close.join();
    }

    std::cout<< " --- end ---" << std::endl;
    return 0;
}