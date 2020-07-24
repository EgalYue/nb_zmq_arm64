#ifndef NINEBOT_ZMQ_ZMQPUBLISHER_H
#define NINEBOT_ZMQ_ZMQPUBLISHER_H

#include <iostream>
#include <vector>
#include <string>

#include "ninebot_zmq/util.h"
#include <type_traits>



namespace ninebot_algo{
    namespace nb_zmq{
        class ZmqPublisher {
        public:
            ZmqPublisher(void* context, const std::string& ip, const std::string& msgType);

            ~ZmqPublisher();
            
            void closeSocket();

            // Each kind of msg type, need one unique socket
            // void* initSocket(const std::string& ip, const std::string& msgType);

            int publish(FrameStampedImageWithPose *framePtr, const std::string& topicStr);

            int publish(FrameStampedLidarScan *framePtr, const std::string& topicStr);

            int publish(Segway_proto::StampedIMU *protoMsgPtr, const std::string& topicStr);

            int publish(Segway_proto::StampedEncoderData *protoMsgPtr, const std::string& topicStr);

            int publish(Segway_proto::StampedLocalization *protoMsgPtr, const std::string& topicStr);

            // Test Used to measure system time difference between 2 systems.
            int publish(Segway_proto::TsWithID *protoMsgPtr, const std::string& topicStr);
            int publish(Segway_proto::Ts2WithID *protoMsgPtr, const std::string& topicStr);
        private:
            ZmqPublisher(const ZmqPublisher &) = delete;
            void operator=(const ZmqPublisher &) = delete;
            // void* m_context;
            //std::string m_ip;
            void* m_publisher;
        };

    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQPUBLISHER_H