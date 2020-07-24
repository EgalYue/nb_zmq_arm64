#include "testCase.h"
#include <thread>

using namespace ninebot_algo;
static bool g_closeSignal = false;



void threadRun(std::shared_ptr<nb_zmq::ZmqReqClient> zmqReqClientPtr, std::string ip, std::string msgType){
    if (SlamConfig == msgType){
        while(1){
            clientCase::SlamConfig_case(zmqReqClientPtr);
            if (g_closeSignal) break;
        }
    } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
        while(1){
            clientCase::Response_case(zmqReqClientPtr);
            if (g_closeSignal) break;
        }
    } else if (IP == msgType){
        while(1){
            clientCase::IP_case(zmqReqClientPtr);
            if (g_closeSignal) break;
        }
    }

    std::cout<< ">>> Closing socket..." << std::endl;
    // zmqReqClientPtr->closeSocket(); 
}

void threadClose(std::shared_ptr<nb_zmq::ZmqReqClient> zmqReqClientPtr){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    zmqReqClientPtr->terminateBlocking();
    g_closeSignal = true;
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        std::cout<< "Usage: zmqReqClient [ip] [msgType]" << std::endl;
        std::cout<< "Ex: zmqReqClient tcp://127.0.0.1 SlamConfig" << std::endl;
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
