#ifndef NINEBOT_ZMQ_ZMQSUBSCRIBER_H
#define NINEBOT_ZMQ_ZMQSUBSCRIBER_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>

#include "ninebot_zmq/util.h"




namespace ninebot_algo{
    namespace nb_zmq{

        struct nbZmqSockets;

        class ZmqSubscriber {
        public:
            ZmqSubscriber(void* context, const std::string& ip, const std::string& msgType);

            ~ZmqSubscriber();

            int init();

            int reconnect();

            void closeSocket();


            /**
             * Blocking mode, blocked until receive one msg.
             * If the duration of disconnect larger than 1min, this node will reconnect. 
             * Return 1: receive msg Successfully.
             * Return -1: Error occurs when call 'zmq_msg_recv'; OR receive 'Terminate socket' signal. 
             */
            int subscribe(FrameStampedImageWithPose* framePtr, const std::string& topicStr, long timeout=-1);

            int subscribe(FrameStampedLidarScan* framePtr, const std::string& topicStr, long timeout=-1);

            int subscribe(Segway_proto::StampedIMU* protoMsgPtr, const std::string& topicStr, long timeout=-1);

            int subscribe(Segway_proto::StampedEncoderData* protoMsgPtr, const std::string& topicStr, long timeout=-1);

            int subscribe(Segway_proto::StampedLocalization* protoMsgPtr, const std::string& topicStr, long timeout=-1);
            
            // Test Used to measure system time difference between 2 systems.
            int subscribe(Segway_proto::TsWithID *protoMsgPtr, const std::string& topicStr, long timeout=-1);
            int subscribe(Segway_proto::Ts2WithID *protoMsgPtr, const std::string& topicStr, long timeout=-1);
            /**
             * Send Terminate signal
             */  
            int terminateBlocking();

        private:
            ZmqSubscriber(const ZmqSubscriber &) = delete;
            void operator=(const ZmqSubscriber &) = delete;
            /**
             * Receive Terminate signal
             */
            int executeTerminateCmd();

            void* m_context;
            std::string m_ip;
            std::string m_msgType;
            std::shared_ptr<nbZmqSockets> m_Sockets;
        };

    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQSUBSCRIBER_H