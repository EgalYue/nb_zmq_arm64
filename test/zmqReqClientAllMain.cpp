#include "testCase.h"

using namespace ninebot_algo;


void run(std::string ip, std::string msgType){
    nb_zmq::ZmqReqClient zmqReqClient;
    if(zmqReqClient.init(ip, msgType) < 0){
        std::cout<< "[ZMQ Client]: Error can not connect to endpoint! " << std::endl;
        return;
    }
    
    if (SlamStartup == msgType){
        clientCase::SlamStartup_case(zmqReqClient);
    } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
        clientCase::Response_case(zmqReqClient);
    } else if (IP == msgType){
        clientCase::IP_case(zmqReqClient);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqReqClientAll [ip]" << std::endl;
        std::cout<< "Ex: zmqReqClientAll tcp://127.0.0.1" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqReqClient all... ===" << std::endl;

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
