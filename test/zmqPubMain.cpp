#include <thread>
#include "testCase.h"


using namespace ninebot_algo;


static bool g_bClosePublish = false;

void threadPub(std::shared_ptr<nb_zmq::ZmqPublisher> mq_pub, std::string& topic){
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
    }
}

void threadClose(){
    while (true) {
        usleep(20000000); // 10s
        break;
    }

    g_bClosePublish = false;
}

int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqPub [ip] [msgType] [topic]" << std::endl;
        std::cout<< "Ex: zmqPub tcp://127.0.0.1 StampedImageWithPose StampedImageWithPose" << std::endl;
        return -1;
    }
    std::cout << "=== This is pub ... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2]; // "StampedImageWithPose"
    std::string topic = argv[3];
    
    nb_zmq::NodeHandle nh;
    auto zmqPubPtr = nh.createPublisher(ip, msgType);
    

    g_bClosePublish = false;
    std::thread th_pub(threadPub, zmqPubPtr, std::ref(topic));
    std::thread th_close(threadClose);

    if (th_close.joinable()){
        th_close.join();
    }
    if (th_pub.joinable()) {
      th_pub.join();
    }

    std::cout<< ">>> Closing socket..." << std::endl;
    zmqPubPtr->closeSocket();
    
    std::cout<< " --- end ---" << std::endl;
    return 0;
}