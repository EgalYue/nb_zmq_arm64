#ifndef NINEBOT_ZMQ_MANAGER_H_
#define NINEBOT_ZMQ_MANAGER_H_

#include "ninebot_zmq/ninebot_zmq_manager_impl.h"

namespace ninebot_algo {

class ZmqManager {
public:
  template <class MsgCls>
  void startReqClient(const std::string& ip, const std::string& msg_type,
                      std::function<void(const MsgCls&)> req_sent_cb,
                      const std::string& thread_name="ZMQ_REQ") {
    return impl.startReqClient<MsgCls>(ip, msg_type, req_sent_cb, thread_name);
  }

  template <class MsgCls>
  void pushReq(const std::string& msg_type, std::shared_ptr<MsgCls> msg) {
    return impl.pushReq<MsgCls>(msg_type, msg);
  }

  void stopReqClient(const std::string& msg_type) {
    return impl.stopReqClient(msg_type);
  }




  template <class MsgCls>
  void startRepServer(const std::string& ip, const std::string& msg_type,
                      std::function<void(const MsgCls&)> rep_recv_cb,
                      const std::string& thread_name="ZMQ_REP") {
    return impl.startRepServer<MsgCls>(ip, msg_type, rep_recv_cb, thread_name);
  }

  void stopRepServer(const std::string& msg_type) {
    return impl.stopRepServer(msg_type);
  }



  template <class MsgCls>
  void startSubscriber(const std::string& ip, const std::string& msg_type,
                      std::function<void(const MsgCls&)> msg_recv_cb,
                      const std::string& thread_name="ZMQ_SUB") {
    return impl.startSubscriber<MsgCls>(ip, msg_type, msg_recv_cb, thread_name);
  }

  void stopSubscriber(const std::string& msg_type) {
    return impl.stopSubscriber(msg_type);
  }




  void startPublisher(const std::string& ip, const std::string& msg_type) {
    return impl.startPublisher(ip, msg_type);
  }

  template <class MsgCls>
  void publish(const std::string& msg_type, std::shared_ptr<MsgCls> msg) {
    return impl.publish<MsgCls>(msg_type, msg);
  }

  void stopPublisher(const std::string& msg_type) {
    return impl.stopPublisher(msg_type);
  }

private:
  ZmqManagerImpl impl;
};

} // namespace ninebot_algo

#endif
