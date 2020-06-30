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

void* threadClose(){
    while (true) {
        usleep(10000000); // 10s
        break;
    }

    nb_zmq::Control ctl;
    g_bClosePublish = ctl.close();
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

    g_bClosePublish = false;
    std::thread th_pub(threadPub, std::ref(ip), std::ref(msgType), std::ref(topic));
    std::thread th_close(threadClose);

    if (th_close.joinable()){
        th_close.join();
    }
    if (th_pub.joinable()) {
      th_pub.join();
    }
    
    std::cout<< " --- end ---" << std::endl;
    return 0;
}