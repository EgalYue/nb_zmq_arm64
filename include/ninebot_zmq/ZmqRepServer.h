#ifndef NINEBOT_ZMQ_ZMQREPSERVER_H
#define NINEBOT_ZMQ_ZMQREPSERVER_H

#include "ninebot_zmq/util.h"
#include <zmq.h>




namespace ninebot_algo{
    namespace nb_zmq{
        class ZmqRepServer {
        public:
            ZmqRepServer();
            ~ZmqRepServer();

            int init(const std::string& ip, const std::string& msgType);

            /**
             * IPC 
             */  
            int init();

            void close();

            void setStopSignal(bool stopSignal);

            bool getStopSignal();
            
            void reconnect();
            
            /**
             * Receive "SlamStartup" string from client.
             * Reply SlamStartup proto as response
             */
            int reply(Segway_proto::SlamStartup* protoMsgPtr);

            /**
             * Receive Response proto from client. Saved in protoMsgPtr
             * Reply "OK" string as response
             */
            int reply(Segway_proto::Response* protoMsgPtr);

            /**
             * Receive IP request "ip" from client
             * Reply server's ip (string) as response
             */
            int reply(std::string& serverIP);

            /**
             * Receive cmd from linux control 
             */ 
            int reply(int& cmd);

        private:
            void *m_context;
            void *m_reply;
            char m_endpoint[100];
            std::string m_ip;
            std::string m_msgType; // in order to determine port
            //zmq_msg_t m_recvMsg;
            //long recv_fail_count;
        };
        
    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQREPSERVER_H