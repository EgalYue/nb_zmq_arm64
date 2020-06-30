#include "testCase.h"
#include <thread>
using namespace ninebot_algo;


void threadRun(nb_zmq::ZmqRepServer& ZmqRepServer, std::string ip, std::string msgType){
    while(1){
        if (SlamStartup == msgType){
            if (serverCase::SlamStartup_case(ZmqRepServer) < 0){
                break;
            }
        } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
            if (serverCase::Response_case(ZmqRepServer) < 0){
                break;
            }
        } else if (IP == msgType){
            if (serverCase::IP_case(ZmqRepServer) < 0){
                break;
            }
        }
    }
}

void threadClose(nb_zmq::ZmqRepServer& ZmqRepServer){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    // ZmqRepServer.setStopSignal(true);
    ZmqRepServer.close();
}

int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqRepServer [ip] [msgTpye]" << std::endl;
        std::cout<< "Ex: zmqRepServer tcp://127.0.0.1 SlamStartup" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqReqServer... ===" << std::endl;
    nb_zmq::ZmqRepServer zmqRepServer;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    if(zmqRepServer.init(ip, msgType) < 0){
        std::cout<< "[ZMQ Server]: Error can not bind endpoint!"<< std::endl;
        return -1;
    }

    std::thread th_run(threadRun, std::ref(zmqRepServer), ip, msgType);
    std::thread th_close(threadClose, std::ref(zmqRepServer));


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}