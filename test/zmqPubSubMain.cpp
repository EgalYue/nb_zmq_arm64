#include "testCase.h"
#include <thread>

using namespace ninebot_algo;


static bool g_closeSignal = false;
static bool g_bClosePublish = false;


void threadPub(std::shared_ptr<nb_zmq::ZmqPublisher> mq_pub, std::string topic){
    if (StampedImageWithPose == topic) {
        //pubCase::Image_case(mq_pub, filepath, topic);
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(1000000); // 1Hz
            pubCase::Image_case(mq_pub, topic, frame_id);
            frame_id++;
        }
    } else if (StampedIMU == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(5000); // 200Hz
            pubCase::StampedIMU_case(mq_pub, topic, frame_id);
            frame_id++;
        }
    } else if (StampedLidarScan == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(100000); // 10Hz
            pubCase::StampedLidarScan_case(mq_pub, topic, frame_id);
            frame_id++;
        }
    } else if (StampedEncoderData == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(50000); // 20Hz
            pubCase::StampedEncoderData_case(mq_pub, topic, frame_id);
            frame_id++;
        }
    } else if (StampedLocalization == topic) {
        int frame_id = 0;
        while(!g_bClosePublish){
            usleep(50000); // 20Hz   
            pubCase::StampedLocalization_case(mq_pub, topic, frame_id);
            frame_id++;
        }
    } else if (TsWithID == topic) {
        int64_t frame_id = 0;
        while(!g_bClosePublish){
            usleep(50000); // 20Hz   
            pubCase::TsWithID_case(mq_pub, topic, frame_id);
            frame_id++;
        }
    } else if (Ts2WithID == topic) {
        int64_t frame_id = 0;
        while(!g_bClosePublish){
            usleep(60000000); // 20Hz   
            pubCase::Ts2WithID_case(mq_pub, topic, frame_id);
            frame_id++;
        }
    }
}


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
    } else if (Ts2WithID == topic) {
        while(1){
            subCase::Ts2WithID_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    }
    
    std::cout<< ">>> Closing socket..." << std::endl;
    mq_recv->closeSocket(); //TODO... !!!!
}


void threadCloseSub(){
    while (true) {
        usleep(15000000); // 10s
        break;
    }

  //TODO
}


/*
 * Pub msg first and then sub msg.
 * [pub-ip] is "tcp://*" as default
 * [sub-ip] is the ip of subscriber
 */
int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqPubSub [sub-ip] [msgType] [topic]" << std::endl;
        std::cout<< "Ex: zmqPubSub tcp://127.0.0.1 StampedImageWithPose StampedImageWithPose" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Pub Sub... ===" << std::endl;
    //std::string filepath = argv[2];
    std::string ipSub = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    std::string topic = argv[3];

    std::string ipPub = "tcp://*"; // localhost as default
    nb_zmq::NodeHandle nh;
    auto zmqPubPtr = nh.createPublisher(ipPub, msgType);
    auto zmqSubPtr = nh.createSubscriber(ipSub, msgType);

    std::thread th_pub(threadPub, zmqPubPtr, topic);
    std::thread th_sub(threadSub, zmqSubPtr, topic);

    if (th_pub.joinable()){
        th_pub.join();
    }
    if (th_sub.joinable()){
        th_sub.join();
    }


    std::cout<< " --- end ---" << std::endl;
    return 0;
}