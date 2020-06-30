#include "testCase.h"
#include <thread>

using namespace ninebot_algo;



void threadRun(nb_zmq::LinuxControl& linuxCtrl, std::string ip, std::string msgType){
    if (CTRL == msgType){
        clientCase::linuxCtrl_case(linuxCtrl, 1000);
    }
}

void threadClose(nb_zmq::LinuxControl& linuxCtrl){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    linuxCtrl.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqLinuxCtrl [ip] [msgType]" << std::endl;
        std::cout<< "Ex: zmqLinuxCtrl tcp://127.0.0.1 CTRL" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqLinuxCtrl... ===" << std::endl;
    nb_zmq::LinuxControl linuxCtrl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    if(linuxCtrl.init(ip, msgType) < 0){
        std::cout<< "[ZMQ Client]: Error can not connect to endpoint! " << std::endl;
        return -1;
    }

    std::thread th_run(threadRun, std::ref(linuxCtrl), ip, msgType);
    std::thread th_close(threadClose, std::ref(linuxCtrl));


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}
