#ifndef NINEBOT_ZMQ_ZMQSUBSCRIBER_H
#define NINEBOT_ZMQ_ZMQSUBSCRIBER_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include "ninebot_zmq/util.h"
#include <zmq.h>




namespace ninebot_algo{
    namespace nb_zmq{

        typedef struct nbZmqSockets{
            zmq_pollitem_t items [2];
        } nbZmqSockets;

        class ZmqSubscriber {
        public:
            ZmqSubscriber(void* context, const std::string& ip, const std::string& msgType);

            ~ZmqSubscriber();

            void closeSocket();


            /**
             * Blocking mode, blocked until receive one msg.
             * Return 1: receive msg Successfully.
             * Return -1: Error occurs when call 'zmq_msg_recv'; OR receive 'Terminate socket' signal. 
             */
            int subscribe(FrameStampedImageWithPose* framePtr, const std::string& topicStr);

            int subscribe(FrameStampedLidarScan* framePtr, const std::string& topicStr);

            int subscribe(Segway_proto::StampedIMU* protoMsgPtr, const std::string& topicStr);

            int subscribe(Segway_proto::StampedEncoderData* protoMsgPtr, const std::string& topicStr);

            int subscribe(Segway_proto::StampedPose3Dd* protoMsgPtr, const std::string& topicStr);
            
            /**
             * Send Terminate signal
             */  
            int terminateBlocking();

        private:
            /**
             * Receive Terminate signal
             */
            int executeTerminateCmd();

            void* m_context;
            // std::string m_ip;
            std::string m_msgType;
            nbZmqSockets m_Sockets;
        };

    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQSUBSCRIBER_H