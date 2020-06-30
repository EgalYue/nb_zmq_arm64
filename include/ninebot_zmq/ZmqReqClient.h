#ifndef NINEBOT_ZMQ_ZMQREQCLIENT_H
#define NINEBOT_ZMQ_ZMQREQCLIENT_H

#include "ninebot_zmq/util.h"
#include <zmq.h>




namespace ninebot_algo{
    namespace nb_zmq{
        class ZmqReqClient {
        public:
            ZmqReqClient();
            ~ZmqReqClient();

            int init(const std::string& ip, const std::string& msgType);

            void close();

            void setStopSignal(bool stopSignal);

            bool getStopSignal();

            void reconnect();

            /*
            * Used to receive SlamStartup msg
            * Reply msg would be saved in protoMsgPtr 
            */
            int request(Segway_proto::SlamStartup* protoMsgPtr);

            /**
             * Send Response msg to Server
             * The sent msg is packsged in protoMsgPtr
             */
            int request(Segway_proto::Response* protoMsgPtr);

            /**
            * Used to receive server's ip
            * The received ip would be saved in serverIP
            */
            int request(std::string& serverIP);

        private:
            void *m_context;
            void *m_request;
            std::string m_ip;
            std::string m_msgType; // in order to determine port
            //zmq_msg_t m_recvMsg;
            //long recv_fail_count;
        };
    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQREQCLIENT_H