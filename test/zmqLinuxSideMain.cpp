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
    // if (argc < 2){
    //     std::cout<< "Usage: zmqLinuxSide" << std::endl;
    //     std::cout<< "Ex: zmqLinuxSide" << std::endl;
    //     return -1;
    // }
    // std::cout << "=== This is zmqLinuxCtrl... ===" << std::endl;
    // nb_zmq::LinuxControl linuxCtrl;
    // std::string ip = argv[1]; // "tcp://127.0.0.1";
    // std::string msgType = argv[2];
    // if(linuxCtrl.init(ip, msgType) < 0){
    //     std::cout<< "[ZMQ Client]: Error can not connect to endpoint! " << std::endl;
    //     return -1;
    // }

    

    // std::thread th_run(threadRun, std::ref(linuxCtrl), ip, msgType);
    // std::thread th_close(threadClose, std::ref(linuxCtrl));


    // if (th_close.joinable()){
    //     th_close.join();
    // }
    // if (th_run.joinable()){
    //     th_run.join();
    // }


    nb_zmq::ZmqRepServer zmqRepServer;
    if(zmqRepServer.init() < 0){
        std::cout<< "[ZMQ Server]: Error can not bind endpoint!"<< std::endl;
        return -1;
    }

    int major, minor, patch;
    zmq_version (&major, &minor, &patch); 
    printf ("Current ØMQ version is %d.%d.%d\n", major, minor, patch);


    return 0;
}
