#include "testCase.h"
#include <thread>
using namespace ninebot_algo;


void threadRun(nb_zmq::AndroidControl& androidCtrl, std::string ip, std::string msgType){
    if (CTRL == msgType){
        serverCase::androidCtrl_case(androidCtrl, 1000);
    }
}

void threadClose(nb_zmq::AndroidControl& androidCtrl){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    androidCtrl.close();
}

int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqAndroidCtrl [ip] [msgTpye]" << std::endl;
        std::cout<< "Ex: zmqAndroidCtrl tcp://127.0.0.1 CTRL" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqAndroidCtrl... ===" << std::endl;
    nb_zmq::AndroidControl androidCtrl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    if(androidCtrl.init(ip, msgType) < 0){
        std::cout<< "[ZMQ AndroidCtrl]: Error can not bind endpoint!"<< std::endl;
        return -1;
    }

    std::thread th_run(threadRun, std::ref(androidCtrl), ip, msgType);
    std::thread th_close(threadClose, std::ref(androidCtrl));


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}