#include "testCase.h"
#include "ninebot_zmq/Control.h"
#include <thread>

using namespace ninebot_algo;


static bool g_bCloseSubscribe = false;


static bool g_bCloseImg = false;
static bool g_bCloseLidar = false;
static bool g_bCloseIMU = false;
static bool g_bCloseEncoder = false;
static bool g_bClosePose = false;



// void threadSub(nb_zmq::ZmqSubscriber& mq_recv, std::string topic){

//     if (StampedImageWithPose == topic) {
//         int nRecvFailCount = 0;
//         while(!g_bCloseSubscribe){
//             subCase::Image_case(mq_recv, topic, nRecvFailCount, true);
//         }
//         g_bCloseImg = true;
//     } else if (StampedIMU == topic) {
//         int nRecvFailCount = 0;
//         while(!g_bCloseSubscribe){
//             subCase::StampedIMU_case(mq_recv, topic, nRecvFailCount, true);
//         }
//         g_bCloseLidar = true;
//     } else if (StampedLidarScan == topic) {
//         int nRecvFailCount = 0;
//         while(!g_bCloseSubscribe){
//             subCase::StampedLidarScan_case(mq_recv, topic, nRecvFailCount, true);
//         }
//         g_bCloseIMU = true;
//     } else if (StampedEncoderData == topic) {
//         int nRecvFailCount = 0;
//         while(!g_bCloseSubscribe){
//             subCase::StampedEncoderData_case(mq_recv, topic, nRecvFailCount, true);
//         }
//         g_bCloseEncoder = true;
//     } else if (StampedPose3Dd == topic) {
//         int nRecvFailCount = 0;
//         while(!g_bCloseSubscribe){
//             subCase::StampedPose3Dd_case(mq_recv, topic, nRecvFailCount, true);
//         }
//         g_bClosePose = true;
//     } 
// }


// void threadCloseAll(nb_zmq::ZmqSubscriber& mq_recv){
//     std::cout<< ">>>>>>>>threadCloseAll>>>>>>>>>>>"<<std::endl;
//     while(1){
//         if (g_bCloseImg && g_bCloseLidar && g_bCloseIMU && g_bCloseEncoder && g_bClosePose){
//             std::cout<< "=== GET all stop signal of all msg types ==="<<std::endl;
//             mq_recv.close();
//             break;
//         }
//     }

// }


void threadSub(std::string ip, std::string topic){
    nb_zmq::ZmqSubscriber mq_recv;
    if(mq_recv.init(ip, AllType) < 0){
        std::cout << "[ZMQ Subscriber]: Error can not connect to endpoint!" << std::endl;
        return;
    }

    if (StampedImageWithPose == topic) {
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
        std::cout<< "Usage: zmqSubAllThreadMain [ip]" << std::endl;
        std::cout<< "Ex: zmqSubAllThreadMain tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Recv... ===" << std::endl;

    std::string ip = argv[1]; // "tcp://127.0.0.1";

    // nb_zmq::ZmqSubscriber mq_recv;
    // if(mq_recv.init(ip, AllType) < 0){
    //     std::cout << "[ZMQ Subscriber]: Error can not connect to endpoint!" << std::endl;
    //     return -1;
    // }


    g_bCloseSubscribe = false;
    // std::thread th_subImage(threadSub, std::ref(mq_recv), StampedImageWithPose);
    // std::thread th_subIMU(threadSub, std::ref(mq_recv), StampedIMU);
    // std::thread th_subLidar(threadSub, std::ref(mq_recv), StampedLidarScan);
    // std::thread th_subEncoder(threadSub, std::ref(mq_recv), StampedEncoderData);
    // std::thread th_subPose(threadSub, std::ref(mq_recv), StampedPose3Dd);
    // std::thread th_getCloseSignal(threadClose);
    // std::thread th_closeAll(threadCloseAll, std::ref(mq_recv));

    std::thread th_subImage(threadSub, ip, StampedImageWithPose);
    std::thread th_subIMU(threadSub, ip, StampedIMU);
    std::thread th_subLidar(threadSub, ip, StampedLidarScan);
    std::thread th_subEncoder(threadSub, ip, StampedEncoderData);
    std::thread th_subPose(threadSub, ip, StampedPose3Dd);
    std::thread th_getCloseSignal(threadClose);

    // if (th_closeAll.joinable()){
    //     th_closeAll.join();
    // }

    if (th_getCloseSignal.joinable()){
        th_getCloseSignal.join();
    }
    if (th_subImage.joinable()){
        th_subImage.join();
    }

    if (th_subLidar.joinable()){
        th_subLidar.join();
    }

    if (th_subIMU.joinable()){
        th_subIMU.join();
    }

    if (th_subEncoder.joinable()){
        th_subEncoder.join();
    }

    if (th_subPose.joinable()){
        th_subPose.join();
    }



    std::cout<< " --- end ---" << std::endl;
    return 0;
}