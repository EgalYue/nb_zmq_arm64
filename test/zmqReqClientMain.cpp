#include "testCase.h"
#include <thread>

using namespace ninebot_algo;



void threadRun(nb_zmq::ZmqReqClient& zmqReqClient, std::string ip, std::string msgType){
    while(1){
        if (SlamStartup == msgType){
            if (clientCase::SlamStartup_case(zmqReqClient) < 0) break;
        } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
            if (clientCase::Response_case(zmqReqClient) < 0) break;
        } else if (IP == msgType){
            if (clientCase::IP_case(zmqReqClient) < 0) break;
        }
    }
}

void threadClose(nb_zmq::ZmqReqClient& zmqReqClient){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    zmqReqClient.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqReqClient [ip] [msgType]" << std::endl;
        std::cout<< "Ex: zmqReqClient tcp://127.0.0.1 SlamStartup" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqReqClient... ===" << std::endl;
    nb_zmq::ZmqReqClient zmqReqClient;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];
    if(zmqReqClient.init(ip, msgType) < 0){
        std::cout<< "[ZMQ Client]: Error can not connect to endpoint! " << std::endl;
        return -1;
    }

    std::thread th_run(threadRun, std::ref(zmqReqClient), ip, msgType);
    std::thread th_close(threadClose, std::ref(zmqReqClient));


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}
