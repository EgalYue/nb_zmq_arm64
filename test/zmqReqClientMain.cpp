#include "testCase.h"
#include <thread>

using namespace ninebot_algo;



void threadRun(std::shared_ptr<nb_zmq::ZmqReqClient> zmqReqClientPtr, std::string ip, std::string msgType){
    while(1){
        if (SlamStartup == msgType){
            if (clientCase::SlamStartup_case(zmqReqClientPtr) < 0) break;
        } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
            if (clientCase::Response_case(zmqReqClientPtr) < 0) break;
        } else if (IP == msgType){
            if (clientCase::IP_case(zmqReqClientPtr) < 0) break;
        }
    }

    std::cout<< ">>> Closing socket..." << std::endl;
    zmqReqClientPtr->closeSocket(); 
}

void threadClose(std::shared_ptr<nb_zmq::ZmqReqClient> zmqReqClientPtr){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    //TODO CLOSE signal?
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqReqClient [ip] [msgType]" << std::endl;
        std::cout<< "Ex: zmqReqClient tcp://127.0.0.1 SlamStartup" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqReqClient... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];

    nb_zmq::NodeHandle nh;
    auto zmqReqClientPtr = nh.createReqClient(ip, msgType);

    std::thread th_run(threadRun, zmqReqClientPtr, ip, msgType);
    std::thread th_close(threadClose, zmqReqClientPtr);


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}
