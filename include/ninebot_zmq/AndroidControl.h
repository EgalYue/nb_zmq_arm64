#ifndef NINEBOT_ZMQ_ANDROIDCONTROL_H
#define NINEBOT_ZMQ_ANDROIDCONTROL_H

#include <stdint.h>
#include "ninebot_zmq/common.h"
#include "ninebot_zmq/util.h"


namespace ninebot_algo{
    namespace nb_zmq{

        class AndroidControl{
        public:            
            AndroidControl(void* context, const std::string& ip, const std::string& msgType);
            
            ~AndroidControl();

            CtrlStatus getLinuxCtrlStatus();
            
            /**
             * Send Heartbeat to LinuxCtrl and get Heartbeat from LinuxCtrl 
             */
            int replyHeartBeat(Segway_proto::HeartbeatCmd* protoMsgPtr, long timeout);

            // ------------ following are used for Android node -------------
            int startAndroidNode();

            int closeAndroidNode();
            
            int reconnectAndroidNode();
            
        private:
            AndroidControl(const AndroidControl &) = delete;
            void operator=(const AndroidControl &) = delete;

            // void* m_context;
            void* m_reply;
            // char m_endpoint[100];
            // std::string m_ip;
            // std::string m_msgType; // in order to determine port
            
            CtrlStatus m_linuxCtrlstatus;

            bool closeLinuxCtrl;
            bool reconnectLinuxCtrl;
        };
    
    } // namespace: nb_zmq
} // namespace: ninebot_algo


#endif //NINEBOT_ZMQ_ANDROIDCONTROL_H