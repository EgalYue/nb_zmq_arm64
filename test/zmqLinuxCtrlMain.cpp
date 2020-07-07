#include "testCase.h"
#include <thread>

using namespace ninebot_algo;



void threadRun(std::shared_ptr<nb_zmq::LinuxControl> linuxCtrl, std::string ip, std::string msgType){
    if (CTRL == msgType){
        clientCase::linuxCtrl_case(linuxCtrl, 1000);
    }
}

void threadClose(std::shared_ptr<nb_zmq::LinuxControl> linuxCtrl){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    //TODO...
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqLinuxCtrl [ip] [msgType]" << std::endl;
        std::cout<< "Ex: zmqLinuxCtrl tcp://127.0.0.1 CTRL" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqLinuxCtrl... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    nb_zmq::NodeHandle nh;
    auto linuxCtrlPtr = nh.createLinuxCtrl(ip, msgType);

    std::thread th_run(threadRun, linuxCtrlPtr, ip, msgType);
    std::thread th_close(threadClose, linuxCtrlPtr);


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}
