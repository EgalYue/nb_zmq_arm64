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
        class ZmqSubscriber {
        public:
            ZmqSubscriber();
            ~ZmqSubscriber();

            void close();

            int init(const std::string& ip, const std::string& msgType);

            void reconnect();

            int subscribe(FrameStampedImageWithPose *framePtr, const std::string& topicStr);

            int subscribe(FrameStampedLidarScan *framePtr, const std::string& topicStr);

            int subscribe(Segway_proto::StampedIMU *protoMsgPtr, const std::string& topicStr);

            int subscribe(Segway_proto::StampedEncoderData *protoMsgPtr, const std::string& topicStr);

            int subscribe(Segway_proto::StampedPose3Dd *protoMsgPtr, const std::string& topicStr);

            // FrameStampedImageWithPose subscribe with Callback
            template <typename ...Args>
            void subscribe(const std::string& topicStr, void callBack(FrameStampedImageWithPose*, Args...), Args... args){
                subscribe(topicStr, std::function<void(FrameStampedImageWithPose*, Args...)>(callBack), args...);
            }

            template <typename ...Args>
            void subscribe(const std::string& topicStr, std::function<void(FrameStampedImageWithPose*, Args...)>&&(callBack), Args... args){
                std::shared_ptr<FrameStampedImageWithPose> framePtr = std::make_shared<FrameStampedImageWithPose>();
                if(subscribe(framePtr.get(), topicStr) < 0){
                    return;
                } else{
                    callBack(framePtr.get());
                }
            }
  

            // FrameStampedLidarScan subscribe with Callback
            template <typename ...Args>
            void subscribe(const std::string& topicStr, void callBack(FrameStampedLidarScan*, Args...), Args... args){
                subscribe(topicStr, std::function<void(FrameStampedLidarScan*, Args...)>(callBack), args...);
            }

            template <typename ...Args>
            void subscribe(const std::string& topicStr, std::function<void(FrameStampedLidarScan*, Args...)>&&(callBack), Args... args){
                std::shared_ptr<FrameStampedLidarScan> framePtr = std::make_shared<FrameStampedLidarScan>();
                if(subscribe(framePtr.get(), topicStr) < 0){
                    return;
                } else{
                    callBack(framePtr.get());
                }
            }

            // Segway_proto::StampedEncoderData subscribe with Callback
            template <typename ...Args>
            void subscribe(const std::string& topicStr, void callBack(Segway_proto::StampedEncoderData*, Args...), Args... args){
                subscribe(topicStr, std::function<void(Segway_proto::StampedEncoderData*, Args...)>(callBack), args...);
            }

            template <typename ...Args>
            void subscribe(const std::string& topicStr, std::function<void(Segway_proto::StampedEncoderData*, Args...)>&&(callBack), Args... args){
                std::shared_ptr<Segway_proto::StampedEncoderData> framePtr = std::make_shared<Segway_proto::StampedEncoderData>();
                if(subscribe(framePtr.get(), topicStr) < 0){
                    return;
                } else{
                    callBack(framePtr.get());
                }
            }


            // Segway_proto::StampedIMU subscribe with Callback
            template <typename ...Args>
            void subscribe(const std::string& topicStr, void callBack(Segway_proto::StampedIMU*, Args...), Args... args){
                subscribe(topicStr, std::function<void(Segway_proto::StampedIMU*, Args...)>(callBack), args...);
            }

            template <typename ...Args>
            void subscribe(const std::string& topicStr, std::function<void(Segway_proto::StampedIMU*, Args...)>&&(callBack), Args... args){
                std::shared_ptr<Segway_proto::StampedIMU> framePtr = std::make_shared<Segway_proto::StampedIMU>();
                if(subscribe(framePtr.get(), topicStr) < 0){
                    return;
                } else{
                    callBack(framePtr.get());
                }
            }


            // Segway_proto::StampedPose3Dd subscribe with Callback
            template <typename ...Args>
            void subscribe(const std::string& topicStr, void callBack(Segway_proto::StampedPose3Dd*, Args...), Args... args){
                subscribe(topicStr, std::function<void(Segway_proto::StampedPose3Dd*, Args...)>(callBack), args...);
            }

            template <typename ...Args>
            void subscribe(const std::string& topicStr, std::function<void(Segway_proto::StampedPose3Dd*, Args...)>&&(callBack), Args... args){
                std::shared_ptr<Segway_proto::StampedPose3Dd> framePtr = std::make_shared<Segway_proto::StampedPose3Dd>();
                if(subscribe(framePtr.get(), topicStr) < 0){
                    return;
                } else{
                    callBack(framePtr.get());
                }
            }

        private:
            void *m_context;
            void *m_requester;
            std::string m_ip;
            std::string m_msgType; // in order to determine port
            bool m_closeSig;
        };

    } // namespace nb_zmq
} // namespace ninebot_algo


#endif //NINEBOT_ZMQ_ZMQSUBSCRIBER_H