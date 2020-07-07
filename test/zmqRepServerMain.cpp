#include "testCase.h"
#include <thread>
using namespace ninebot_algo;


void threadRun(std::shared_ptr<nb_zmq::ZmqRepServer> ZmqRepServerPtr, std::string ip, std::string msgType){
    while(1){
        if (SlamStartup == msgType){
            if (serverCase::SlamStartup_case(ZmqRepServerPtr) < 0){
                break;
            }
        } else if (ResponseError == msgType || ResponseMap == msgType || ResponsePose == msgType){
            if (serverCase::Response_case(ZmqRepServerPtr) < 0){
                break;
            }
        } else if (IP == msgType){
            if (serverCase::IP_case(ZmqRepServerPtr) < 0){
                break;
            }
        }
    }

    std::cout<< ">>> Closing socket..." << std::endl;
    ZmqRepServerPtr->closeSocket(); 
}

void threadClose(std::shared_ptr<nb_zmq::ZmqRepServer> ZmqRepServerPtr){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    // TODO close ? 
}

int main(int argc, char *argv[]) {
    if (argc < 3){
        std::cout<< "Usage: zmqRepServer [ip] [msgTpye]" << std::endl;
        std::cout<< "Ex: zmqRepServer tcp://127.0.0.1 SlamStartup" << std::endl;
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