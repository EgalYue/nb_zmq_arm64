#ifndef NINEBOT_ZMQ_COMMON_H
#define NINEBOT_ZMQ_COMMON_H
#include <map>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

namespace ninebot_algo{
    namespace nb_zmq{

        // Unique Port for pub all kinds of msg as sequence
        extern const std::string AllType;

        // Following are used for zmq Pub/Sub mode
        extern const std::string StampedImageWithPose;
        extern const std::string StampedIMU;
        extern const std::string StampedLidarScan;
        extern const std::string StampedEncoderData;
        extern const std::string StampedPose3Dd;

        // Following are used for zmq Req/Rep mode
        extern const std::string SlamStartup;
        extern const std::string ResponseMap;
        extern const std::string ResponsePose;
        extern const std::string ResponseError;
        extern const std::string IP;
        extern const std::string CTRL;

        extern std::map<std::string, std::string> PORTS;
        extern std::vector<std::string> NetType;


        // ControlLinux and ControlAndroid status
        enum CtrlStatus {starting, working, stop};
        extern const int HEARTBEAT_LIVENESS;
        extern const long HEARTBEAT_INTERVAL; // us


        // Others
        extern const std::string IPC_linux_addr;
        extern const std::string IPC_CTRL_CHANNEL;

        /**
         * Get ip of current device
         */
        bool GetIP(std::string& strip);

    } //namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_COMMON_H