#ifndef NINEBOT_ZMQ_UTIL_H
#define NINEBOT_ZMQ_UTIL_H

#include "ninebot_zmq/image.pb.h"
#include "ninebot_zmq/slam_config.pb.h"
#include "ninebot_zmq/encoder.pb.h"
#include "ninebot_zmq/response.pb.h"
#include "ninebot_zmq/imu.pb.h"
#include "ninebot_zmq/lidar.pb.h"
#include "ninebot_zmq/encoder.pb.h"
#include "ninebot_zmq/pose.pb.h"
#include "ninebot_zmq/localization.pb.h"
#include "ninebot_zmq/heartbeat.pb.h"
#include "ninebot_zmq/tsWithID.pb.h"
#include "ninebot_zmq/ts2WithID.pb.h"

namespace ninebot_algo{
    namespace nb_zmq{

        class FrameImage{
        public:
            Segway_proto::StampedImage msg_desc; // image descriptor
            std::shared_ptr<std::vector<uint8_t>> raw_data; // image raw data
        };

        class FrameStampedImageWithPose{
        public:
            Segway_proto::StampedImageWithPose msg_desc; // image descriptor, fisheye pose
            std::shared_ptr<std::vector<uint8_t>> raw_data; // image raw data
        };


        class FrameStampedLidarScan{
        public:
            Segway_proto::StampedLidarScan msg_desc; // imu 
            std::shared_ptr<std::vector<float>> ranges; // range data.
            std::shared_ptr<std::vector<float>> intensities; // intensity data. size_of(intensities) = size_of(ranges)
        };

    }// namespace nb_zmq

} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_UTIL_H