#ifndef NINEBOT_ZMQ_NODEHANDLE_H
#define NINEBOT_ZMQ_NODEHANDLE_H

#include "ninebot_zmq/ZmqPublisher.h"
#include "ninebot_zmq/ZmqSubscriber.h"
#include "ninebot_zmq/ZmqRepServer.h"
#include "ninebot_zmq/ZmqReqClient.h"
#include "ninebot_zmq/AndroidControl.h"
#include "ninebot_zmq/LinuxControl.h"
#include <memory>

namespace ninebot_algo{
    namespace nb_zmq{

        class NodeHandle{
            public:
                NodeHandle();
                ~NodeHandle();

                std::shared_ptr<ZmqPublisher> createPublisher(const std::string& ip, const std::string& msgType);

                std::shared_ptr<ZmqSubscriber> createSubscriber(const std::string& ip, const std::string& msgType);

                std::shared_ptr<ZmqRepServer> createRepServer(const std::string& ip, const std::string& msgType);

                std::shared_ptr<ZmqReqClient> createReqClient(const std::string& ip, const std::string& msgType);

                std::shared_ptr<AndroidControl> createAndroidCtrl(const std::string& ip, const std::string& msgType);

                std::shared_ptr<LinuxControl> createLinuxCtrl(const std::string& ip, const std::string& msgType);

            private:    
                void* m_context;
        };
    
    } // namespace: nb_zmq
} // namespace: ninebot_algo

#endif //NINEBOT_ZMQ_NODEHANDLE_H