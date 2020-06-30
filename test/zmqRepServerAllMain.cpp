#include "testCase.h"

using namespace ninebot_algo;

void run(std::string ip, std::string msgType){
    nb_zmq::ZmqRepServer zmqRepServer;
    if(zmqRepServer.init(ip, msgType) < 0){
        std::cout<< "[ZMQ Server]: Error can not bind endpoint!"<< std::endl;
        return;
    }

    if (SlamStartup == msgType){
        serverCase::SlamStartup_case(zmqRepServer);
    } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
        serverCase::Response_case(zmqRepServer);
    } else if (IP == msgType){
        serverCase::IP_case(zmqRepServer);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqRepServerAll [ip]" << std::endl;
        std::cout<< "Ex: zmqRepServerAll tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqReqServer all ... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    
    {   
        std::cout<< "======== Server SlamStartup ========"<<std::endl;
        run(ip, SlamStartup);
        usleep(1000000);
    }

    {
        std::cout<< "======== Server ResponseMap ========"<<std::endl;
        run(ip, ResponseMap);
        usleep(1000000);
    }

    {
        std::cout<< "======== Server ResponsePose ========"<<std::endl;
        run(ip, ResponsePose);
        usleep(1000000);
    }

    {
        std::cout<< "======== Server ResponseError ========"<<std::endl;
        run(ip, ResponseError);
        usleep(1000000);
    }

    {
        std::cout<< "======== Server IP ========"<<std::endl;
        run(ip, IP);
        usleep(1000000);
    }

    std::cout<< " --- end ---" << std::endl;
    return 0;
}