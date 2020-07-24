#include "testCase.h"
#include <thread>
using namespace ninebot_algo;
static bool g_closeSignal = false;

void threadRun(std::shared_ptr<nb_zmq::ZmqRepServer> ZmqRepServerPtr, std::string ip, std::string msgType){
    if (SlamConfig == msgType){
        while(1){
            serverCase::SlamConfig_case(ZmqRepServerPtr);
            if (g_closeSignal){
                break;
            }
        }    
    } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
        while(1){
            serverCase::Response_case(ZmqRepServerPtr);
            if (g_closeSignal){
                break;
            }
        }    
    } else if (IP == msgType){
        while(1){
            if (serverCase::IP_case(ZmqRepServerPtr) < 0){
                break;
            }
        }
    }

    std::cout<< ">>> Closing socket..." << std::endl;
    // ZmqRepServerPtr->closeSocket(); 
}

void threadClose(std::shared_ptr<nb_zmq::ZmqRepServer> ZmqRepServerPtr){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    ZmqRepServerPtr->terminateBlocking();
    g_closeSignal = true;
}

int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqRepServer [ip] [msgTpye]" << std::endl;
        std::cout<< "Ex: zmqRepServer tcp://127.0.0.1 SlamConfig" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmqReqServer... ===" << std::endl;
    std::string ip = argv[1]; // "tcp://127.0.0.1";
    std::string msgType = argv[2];

    nb_zmq::NodeHandle nh;
    auto zmqRepServerPtr = nh.createRepServer(ip, msgType);

    std::thread th_run(threadRun, zmqRepServerPtr, ip, msgType);
    std::thread th_close(threadClose, zmqRepServerPtr);


    if (th_close.joinable()){
        th_close.join();
    }
    if (th_run.joinable()){
        th_run.join();
    }


    return 0;
}