#ifndef NINEBOT_ZMQ_ZMQPUBLISHER_H
#define NINEBOT_ZMQ_ZMQPUBLISHER_H

#include <iostream>
#include <vector>
#include <string>

#include "ninebot_zmq/util.h"
#include <zmq.h>
#include <type_traits>



namespace ninebot_algo{
    namespace nb_zmq{
        class ZmqPublisher {
        public:
            ZmqPublisher();
            ~ZmqPublisher();
            
            void close();

            int init(const std::string& ip, const std::string& msgType);
            
            int publish(FrameStampedImageWithPose *framePtr, const std::string& topicStr);

            int publish(FrameStampedLidarScan *framePtr, const std::string& topicStr);

            int publish(Segway_proto::StampedIMU *protoMsgPtr, const std::string& topicStr);

            int publish(Segway_proto::StampedEncoderData *protoMsgPtr, const std::string& topicStr);

            int publish(Segway_proto::StampedPose3Dd *protoMsgPtr, const std::string& topicStr);

        private:
            void *m_context;
            void *m_publisher;
            std::string m_ip;
            std::string m_msgType; // in order to determine port
        };

    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQPUBLISHER_H