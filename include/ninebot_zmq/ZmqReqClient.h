#ifndef NINEBOT_ZMQ_ZMQREQCLIENT_H
#define NINEBOT_ZMQ_ZMQREQCLIENT_H

#include "ninebot_zmq/util.h"




namespace ninebot_algo{
    namespace nb_zmq{
        class ZmqReqClient {
        public:
            ZmqReqClient(void* context, const std::string& ip, const std::string& msgType);

            ~ZmqReqClient();

            int init();

            int reconnect();

            void closeSocket();

            void setStopSignal(bool stopSignal);

            bool getStopSignal();

            /*
            * Used to receive SlamConfig msg
            * Reply msg would be saved in protoMsgPtr 
            * timeout=-1, zmq_poll() shall block indefinitely until a requested event has occurred
            */
            int request(Segway_proto::SlamConfig* protoMsgPtr, long timeout=-1);

            /**
             * Send Response msg to Server
             * The sent msg is packsged in protoMsgPtr
             */
            int request(Segway_proto::Response* protoMsgPtr, long timeout=-1);

            /**
            * Used to receive server's ip
            * The received ip would be saved in serverIP
            */
            int request(std::string& serverIP, long timeout=-1);

            /**
             * Send Terminate signal
             */  
            int terminateBlocking();

        private:
            ZmqReqClient(const ZmqReqClient &) = delete;
            void operator=(const ZmqReqClient &) = delete;
            /**
             * Receive Terminate signal
             */
            int executeTerminateCmd();

            void *m_context;
            void* m_requester;
            void* m_ctrlPuller;
            std::string m_ip;
            std::string m_msgType; // in order to determine port
        };
    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQREQCLIENT_H