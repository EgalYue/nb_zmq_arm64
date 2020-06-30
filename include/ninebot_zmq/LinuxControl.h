#ifndef NINEBOT_ZMQ_LINUXCONTROL_H
#define NINEBOT_ZMQ_LINUXCONTROL_H

#include <stdint.h>
#include <zmq.h>
#include "ninebot_zmq/common.h"
#include "ninebot_zmq/util.h"


namespace ninebot_algo{
    namespace nb_zmq{

        class LinuxControl{
        public:
            LinuxControl();
            
            ~LinuxControl();

            int init(const std::string& ip, const std::string& msgType);

            /**
             * IPC
             */   
            int init();

            void close();

            int reconnect();

            CtrlStatus getAndroidCtrlStatus();

            /**
             * Get Heartbeat from AndroidCtrl and reply Heartbeat to AndroidCtrl 
             */
            int requestHeartBeat(Segway_proto::HeartbeatCmd* protoMsgPtr, long timeout);

            /**
             * Send cmd to linux comm part
             */
            int sendCmd(int cmd); 

        private:
            void *m_context;
            void *m_request;
            std::string m_ip;
            std::string m_msgType; // in order to determine port

            CtrlStatus m_androidCtrlstatus;
        };
    
    } // namespace: nb_zmq
} // namespace: ninebot_algo


#endif //NINEBOT_ZMQ_LINUXCONTROL_H