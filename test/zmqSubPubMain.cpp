#include "testCase.h"
#include <thread>

using namespace ninebot_algo;



static bool g_closeSignal = false;

void threadSubPub(std::shared_ptr<nb_zmq::ZmqSubscriber> suberPtr, std::shared_ptr<nb_zmq::ZmqPublisher> pubPtr, std::string topic){
    if (StampedImageWithPose == topic) {
        while(1){
            subPubCase::Image_case(suberPtr, pubPtr, topic);
            if (g_closeSignal){
                break;
            }    
        }
    } else if (StampedIMU == topic) {
        while(1){
            subPubCase::StampedIMU_case(suberPtr, pubPtr, topic);
            if (g_closeSignal){
                break;
            }    
        }
    } else if (StampedLidarScan == topic) {
        while(1){
            subPubCase::StampedLidarScan_case(suberPtr, pubPtr, topic);
            if (g_closeSignal){
                break;
            }    
        }
    } else if (StampedEncoderData == topic) {
        while(1){
            subPubCase::StampedEncoderData_case(suberPtr, pubPtr, topic);
            if (g_closeSignal){
                break;
            }    
        }
    } else if (StampedLocalization == topic) {
        while(1){
            subPubCase::StampedLocalization_case(suberPtr, pubPtr, topic);
            if (g_closeSignal){
                break;
            }    
        }
    }  else if (TsWithID == topic) {
        while(1){
            subPubCase::TsWithID_case(suberPtr, pubPtr, topic);
            if (g_closeSignal){
                break;
            }    
        }
    }




}


void* threadClose(){
    while (true) {
        usleep(10000000); // 10s
        break;
    }
    //todo
}


/*
 * Sub msg first and then pub msg.
 * [pub-ip] is "tcp://*" as default
 * [sub-ip] is the ip of subscriber
 */
int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqSubPub [sub-ip] [msgType] [topic]" << std::endl;
        std::cout<< "Ex: zmqSubPub tcp://127.0.0.1 StampedImageWithPose StampedImageWithPose" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Sub pub... ===" << std::endl;

    std::string ipSub = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    std::string topic = argv[3];

    std::string ipPub = "tcp://*"; // localhost as default

    nb_zmq::NodeHandle nh;
    auto subPtr = nh.createSubscriber(ipSub, msgType);
    auto pubPtr = nh.createPublisher(ipPub, msgType);

    g_closeSignal = false;
    std::thread th_subpub(threadSubPub, subPtr, pubPtr, msgType);
    std::thread th_close(threadClose);

    if (th_close.joinable()){
        th_close.join();
    }
    if(th_subpub.joinable()){
        th_subpub.join();
    }


    std::cout<< " --- end ---" << std::endl;
    return 0;
}
