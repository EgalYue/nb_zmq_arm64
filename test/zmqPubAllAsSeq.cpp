#include <thread>
#include "testCase.h"


using namespace ninebot_algo;

/*
static bool g_bClosePublish = false;

void threadPub(std::string& ip, std::string& msgType){
    nb_zmq::ZmqPublisher mq_pub;
    if (mq_pub.init(ip, msgType) < 0){
        std::cout << "[ZMQ Pulisher]: Error can not bind endpoint !" << std::endl;
        return;
    }

    int frame_id = 0;
    while (!g_bClosePublish){
        usleep(1000000); // 1Hz
        std::cout << "[Pub]: ====== StampedImageWithPose ======" << std::endl;
        std::string topic = StampedImageWithPose;
        pubCase::Image_case(mq_pub, topic, frame_id);

        std::cout << "[Pub]: ====== StampedIMU ======" << std::endl;
        topic = StampedIMU;
        pubCase::StampedIMU_case(mq_pub, topic, frame_id);

        std::cout << "[Pub]: ====== StampedLidarScan ======" << std::endl;
        topic = StampedLidarScan;
        pubCase::StampedLidarScan_case(mq_pub, topic, frame_id);

        std::cout << "[Pub]: ====== StampedEncoderData ======" << std::endl;
        topic = StampedEncoderData;
        pubCase::StampedEncoderData_case(mq_pub, topic, frame_id);

        std::cout << "[Pub]: ====== StampedPose3Dd ======" << std::endl;
        topic = StampedPose3Dd;
        pubCase::StampedPose3Dd_case(mq_pub, topic, frame_id);

        frame_id++;
    }
    mq_pub.close();
}

void threadClose(){
    while (true) {
        usleep(5000000); // 10s
        break;
    }

    nb_zmq::Control ctl;
    g_bClosePublish = ctl.close();
}
*/

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqPubAllAsSeq [ip] " << std::endl;
        std::cout<< "Ex: zmqPubAllAsSeq tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqPubAllAsSeq, using one port ... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";

    nb_zmq::NodeHandle nh;
    auto imagePuber = nh.createPublisher(ip, nb_zmq::StampedImageWithPose);
    auto imuPuber = nh.createPublisher(ip, nb_zmq::StampedIMU);
    auto lidarPuber = nh.createPublisher(ip, nb_zmq::StampedLidarScan);
    auto encoderPuber = nh.createPublisher(ip, nb_zmq::StampedEncoderData);


    
    // {
    //     g_bClosePublish = false;
    //     std::string temp = AllType;
    //     std::thread th_pub(threadPub, std::ref(ip), std::ref(temp));
    //     std::thread th_close(threadClose);

    //     if (th_close.joinable()){
    //         th_close.join();
    //     }
    //     if (th_pub.joinable()) {
    //     th_pub.join();
    //     }
    //     usleep(1000000);
    // }
    int frame_id = 0;
    while(1){
        usleep(100000); // 10Hz
        std::string topic = StampedImageWithPose;
        pubCase::Image_case(imagePuber, topic, frame_id);
        topic = nb_zmq::StampedIMU;
        pubCase::StampedIMU_case(imuPuber, topic, frame_id);
        topic = nb_zmq::StampedLidarScan;
        pubCase::StampedLidarScan_case(lidarPuber, topic, frame_id);
        topic = nb_zmq::StampedEncoderData;
        pubCase::StampedEncoderData_case(encoderPuber, topic, frame_id);
        frame_id++;
    }

    
    std::cout<< " --- end ---" << std::endl;
    return 0;
}