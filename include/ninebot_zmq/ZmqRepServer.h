#ifndef NINEBOT_ZMQ_ZMQREPSERVER_H
#define NINEBOT_ZMQ_ZMQREPSERVER_H

#include "ninebot_zmq/util.h"




namespace ninebot_algo{
    namespace nb_zmq{

        
        class ZmqRepServer {
        public:
            ZmqRepServer(void* context, const std::string& ip, const std::string& msgType);

            ~ZmqRepServer();

            int init();

            int reconnect();

            void closeSocket();

            /**
             * IPC 
             */  
            // int init();

            void setStopSignal(bool stopSignal);

            bool getStopSignal();
            
            /**
             * Receive "SlamConfig" string from client.
             * Reply SlamConfig proto as response
             */
            int reply(Segway_proto::SlamConfig* protoMsgPtr, long timeout=-1);

            /**
             * Receive Response proto from client. Saved in protoMsgPtr
             * Reply "OK" string as response
             */
            int reply(Segway_proto::Response* protoMsgPtr, long timeout=-1);

            /**
             * Receive IP request "ip" from client
             * Reply server's ip (string) as response
             */
            int reply(std::string& serverIP, long timeout=-1);

            /**
             * Receive cmd from linux control 
             */ 
            // int reply(int& cmd);

            /**
             * Send Terminate signal
             */  
            int terminateBlocking();

        private:
            ZmqRepServer(const ZmqRepServer &) = delete;
            void operator=(const ZmqRepServer &) = delete;
            /**
             * Receive Terminate signal
             */
            int executeTerminateCmd();

            void *m_context;
            void* m_replier;
            void* m_ctrlPuller;
            // char m_endpoint[100];
            std::string m_ip;
            std::string m_msgType; // in order to determine port
            //zmq_msg_t m_recvMsg;
            //long recv_fail_count;

        };
        
    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQREPSERVER_H