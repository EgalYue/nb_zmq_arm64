#include "testCase.h"
#include <thread>
using namespace ninebot_algo;


void threadRun(std::shared_ptr<nb_zmq::AndroidControl> androidCtrlPtr, std::string ip, std::string msgType){
    if (CTRL == msgType){
        serverCase::androidCtrl_case(androidCtrlPtr, 1000);
    }
}

void threadClose(std::shared_ptr<nb_zmq::AndroidControl> androidCtrl){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    //TODO...
}

int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqAndroidCtrl [ip] [msgTpye]" << std::endl;
        std::cout<< "Ex: zmqAndroidCtrl tcp://127.0.0.1 CTRL" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqAndroidCtrl... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    nb_zmq::NodeHandle nh;
    auto androidCtrlPtr = nh.createAndroidCtrl(ip, msgType);

    std::thread th_run(threadRun, androidCtrlPtr, ip, msgType);
    std::thread th_close(threadClose, androidCtrlPtr);


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}