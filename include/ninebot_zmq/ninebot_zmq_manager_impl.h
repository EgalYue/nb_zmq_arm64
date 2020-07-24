#ifndef NINEBOT_ZMQ_MANAGER_IMPL_H_
#define NINEBOT_ZMQ_MANAGER_IMPL_H_

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <functional>
#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "ninebot_zmq/ninebot_zmq.h"
#ifndef __ANDROID__
  #include "ninebot_log/ninebot_log.h"
#else
  #include "ninebot_log.h"
  #undef DEFAULT_LOG_TAG
  #define DEFAULT_LOG_TAG "ZMQTEST"
#endif

namespace ninebot_algo {

class ZmqManagerImpl {

public:
  template <class MsgCls>
  void startReqClient(const std::string& ip, const std::string& msg_type,
                      std::function<void(const MsgCls&)> req_sent_cb,
                      const std::string& thread_name="ZMQ_REQ") {
    if (getReqClient(msg_type) != nullptr) {
      ALOGW("ZmqManager:startReqClient: attempting to repeatedly start ReqClient for requests of type \"%s\"!", msg_type.c_str());
      return;
    }

    ReqClientPtr client(new ReqClient());
    client->end_request = false;
    client->msg_type = msg_type;
    client->ip = ip;
    client->thread_name = thread_name;
    client->req_sent_cb = [req_sent_cb, msg_type] (ZmqMsgWrapperInterface* msg_wrapper_ptr) {
      ZmqMsgWrapper<MsgCls>* cast_msg_wrapper_ptr = dynamic_cast<ZmqMsgWrapper<MsgCls>*>(msg_wrapper_ptr);
      if (nullptr ==  cast_msg_wrapper_ptr) {
        ALOGW("ZmqManager:ReqClient.req_sent_cb: dynamic_cast failed for msg of type \"%s\"", msg_type.c_str());
      } else if (nullptr == cast_msg_wrapper_ptr->msg) {
        ALOGW("ZmqManager:ReqClient.req_sent_cb: null msg of type \"%s\"!", msg_type.c_str());
      } else {
        req_sent_cb(*(cast_msg_wrapper_ptr->msg));
      }
    };

    addReqClient<MsgCls>(client);
  }

  template <class MsgCls>
  void pushReq(const std::string& msg_type, std::shared_ptr<MsgCls> msg) {

    ReqClientPtr client = getReqClient(msg_type);
    if (client == nullptr) {
      ALOGW("ZmqManager:pushReq: unknown msg type \"%s\"", msg_type.c_str());
      return;
    }
    
    {
      std::lock_guard<std::mutex> lock(client->req_queue_mutex);
      std::shared_ptr<ZmqMsgWrapperInterface> msg_wrapper (new ZmqMsgWrapper<MsgCls>(msg));
      client->req_queue.push_back(msg_wrapper);
    }
    client->cond.notify_one();
    //ALOGD("ZmqManager:pushReq: msg type \"%s\", remaining %d", msg_type.c_str(), client->req_queue.size());
  }

  void stopReqClient(const std::string& msg_type) {

    ReqClientPtr client = getReqClient(msg_type);
    removeReqClient(msg_type);

    if (client == nullptr) {
      ALOGW("ZmqManager:stopReqClient: unknown msg type \"%s\"", msg_type.c_str());
      return;
    }

    client->end_request = true;
    client->cond.notify_one();
    client->client->terminateBlocking();

    if (client->thread->joinable()) {
      client->thread->join();
    }
  }

  template <class MsgCls>
  void startRepServer(const std::string& ip, const std::string& msg_type,
                      std::function<void(const MsgCls&)> rep_recv_cb,
                      const std::string& thread_name="ZMQ_REP") {
    if (getRepServer(msg_type) != nullptr) {
      ALOGW("ZmqManager:startRepServer: attempting to repeatedly start RepServer for requests of type \"%s\"!", msg_type.c_str());
      return;
    }

    RepServerPtr server(new RepServer());
    server->end_request = false;
    server->msg_type = msg_type;
    server->ip = ip;
    server->thread_name = thread_name;
    server->rep_recv_cb = [rep_recv_cb, msg_type] (ZmqMsgWrapperInterface* msg_wrapper_ptr) {
      ZmqMsgWrapper<MsgCls>* cast_msg_wrapper_ptr = dynamic_cast<ZmqMsgWrapper<MsgCls>*>(msg_wrapper_ptr);
      if (nullptr ==  cast_msg_wrapper_ptr) {
        ALOGW("ZmqManager:RepServer.rep_recv_cb: dynamic_cast failed for msg of type \"%s\"", msg_type.c_str());
      } else if (nullptr == cast_msg_wrapper_ptr->msg) {
        ALOGW("ZmqManager:RepServer.rep_recv_cb: null msg of type \"%s\"!", msg_type.c_str());
      } else {
        rep_recv_cb(*(cast_msg_wrapper_ptr->msg));
      }
    };

    addRepServer<MsgCls>(server);
  }

  void stopRepServer(const std::string& msg_type) {
    RepServerPtr server = getRepServer(msg_type);
    removeRepServer(msg_type);

    if (server == nullptr) {
      ALOGW("ZmqManager:stopRepServer: unknown msg type \"%s\"", msg_type.c_str());
      return;
    }

    server->end_request = true;
    server->server->terminateBlocking();

    if (server->thread->joinable()) {
      server->thread->join();
    }
  }

  template <class MsgCls>
  void startSubscriber(const std::string& ip, const std::string& msg_type,
                      std::function<void(const MsgCls&)> msg_recv_cb,
                      const std::string& thread_name="ZMQ_SUB") {
    if (getSubscriber(msg_type) != nullptr) {
      ALOGW("ZmqManager:startSubscriber: attempting to repeatedly start Subscriber for msg of type \"%s\"!", msg_type.c_str());
      return;
    }

    SubscriberPtr subscriber(new Subscriber());
    subscriber->end_request = false;
    subscriber->msg_type = msg_type;
    subscriber->ip = ip;
    subscriber->thread_name = thread_name;
    subscriber->msg_recv_cb = [msg_recv_cb, msg_type] (ZmqMsgWrapperInterface* msg_wrapper_ptr) {
      ZmqMsgWrapper<MsgCls>* cast_msg_wrapper_ptr = dynamic_cast<ZmqMsgWrapper<MsgCls>*>(msg_wrapper_ptr);
      if (nullptr ==  cast_msg_wrapper_ptr) {
        ALOGW("ZmqManager:Subscriber.msg_recv_cb: dynamic_cast failed for msg of type \"%s\"", msg_type.c_str());
      } else if (nullptr == cast_msg_wrapper_ptr->msg) {
        ALOGW("ZmqManager:Subscriber.msg_recv_cb: null msg of type \"%s\"!", msg_type.c_str());
      } else {
        msg_recv_cb(*(cast_msg_wrapper_ptr->msg));
      }
    };

    addSubscriber<MsgCls>(subscriber);
  }


  void stopSubscriber(const std::string& msg_type) {
    SubscriberPtr subscriber = getSubscriber(msg_type);
    removeSubscriber(msg_type);

    if (subscriber == nullptr) {
      ALOGW("ZmqManager:stopSubscriber: unknown msg type \"%s\"", msg_type.c_str());
      return;
    }

    subscriber->end_request = true;
    subscriber->subscriber->terminateBlocking();

    if (subscriber->thread->joinable()) {
      subscriber->thread->join();
    }
  }


  // template <class MsgCls>
  void startPublisher(const std::string& ip, const std::string& msg_type) {
    if (getPublisher(msg_type) != nullptr) {
      ALOGW("ZmqManager:startPublisher: attempting to repeatedly start Publisher for msg of type \"%s\"!", msg_type.c_str());
      return;
    }

    PublisherPtr publisher(new Publisher());
    //publisher->end_request = false;
    publisher->msg_type = msg_type;
    publisher->ip = ip;
    //publisher->thread_name = thread_name;
    //publisher->thread = std::shared_ptr<std::thread>(
    //        new std::thread(&ZmqManagerImpl::PublisherThread<MsgCls>, this, publisher));

    addPublisher(publisher);
  }

  template <class MsgCls>
  void publish(const std::string& msg_type, std::shared_ptr<MsgCls> msg) {
    PublisherPtr publisher = getPublisher(msg_type);
    if (publisher == nullptr) {
      ALOGW("ZmqManager:publish: unknown msg type \"%s\"", msg_type.c_str());
      return;
    }

    publisher->publisher->publish(msg.get(), publisher->msg_type);
  }


  void stopPublisher(const std::string& msg_type) {
    PublisherPtr publisher = getPublisher(msg_type);
    removePublisher(msg_type);

    if (publisher == nullptr) {
      ALOGW("ZmqManager:stopPublisher: unknown msg type \"%s\"", msg_type.c_str());
      return;
    }

    //publisher->end_request = true;
    //publisher->publisher->wakeup() ?

    //if (publisher->thread->joinable()) {
    //  publisher->thread->join();
    //}
  }


protected:

  //// typedefs

  struct ZmqMsgWrapperInterface {  
    virtual ~ZmqMsgWrapperInterface() {}
  };

  template <class MsgCls>
  struct ZmqMsgWrapper : public ZmqMsgWrapperInterface {
    typedef std::shared_ptr<MsgCls> MsgPtr;
    ZmqMsgWrapper(MsgPtr input_msg) : msg(input_msg) {}
    virtual ~ZmqMsgWrapper() {}
    MsgPtr msg;
  };

  typedef std::deque<std::shared_ptr<ZmqMsgWrapperInterface>> ZmqMsgQueue;
  typedef std::function<void(ZmqMsgWrapperInterface*)> MsgCallback;

  struct Publisher {
    std::shared_ptr<nb_zmq::ZmqPublisher> publisher;
    //std::shared_ptr<std::thread> thread;
    //std::string thread_name;
    //std::atomic<bool> end_request;
    std::string msg_type;
    std::string ip;

    //ZmqMsgQueue msg_queue;
    //std::mutex msg_queue_mutex;
    //std::condition_variable cond;
  };

  struct Subscriber {
    std::shared_ptr<nb_zmq::ZmqSubscriber> subscriber;
    std::shared_ptr<std::thread> thread;
    std::string thread_name;
    std::atomic<bool> end_request;
    std::string msg_type;
    std::string ip;
    
    MsgCallback msg_recv_cb;
  };

  struct ReqClient {
    std::shared_ptr<nb_zmq::ZmqReqClient> client;
    std::shared_ptr<std::thread> thread;
    std::string thread_name;
    std::atomic<bool> end_request;
    std::string msg_type;
    std::string ip;
    
    ZmqMsgQueue req_queue;
    std::mutex req_queue_mutex;
    std::condition_variable cond;
    MsgCallback req_sent_cb;
  };

  struct RepServer {
    std::shared_ptr<nb_zmq::ZmqRepServer> server;
    std::shared_ptr<std::thread> thread;
    std::string thread_name;
    std::atomic<bool> end_request;
    std::string msg_type;
    std::string ip;
    
    MsgCallback rep_recv_cb;
  };

  typedef std::shared_ptr<Publisher> PublisherPtr;
  typedef std::shared_ptr<Subscriber> SubscriberPtr;
  typedef std::shared_ptr<ReqClient> ReqClientPtr;
  typedef std::shared_ptr<RepServer> RepServerPtr;



protected:  
  //// zmq-thread templates

  template <class MsgCls>
  void ReqClientThread(ReqClientPtr client) {
    pthread_setname_np(pthread_self(), client->thread_name.c_str());
    while(! client->end_request) {
      ZmqMsgQueue temp_req_queue;
      std::unique_lock<std::mutex> lk(client->req_queue_mutex);
      client->cond.wait(lk, [&] {
        std::swap(temp_req_queue, client->req_queue);
        return client->end_request || !(temp_req_queue.empty());
      });
      lk.unlock();

      if (client->end_request) {
        return;
      }

      while(! client->end_request && ! temp_req_queue.empty()) {
        std::shared_ptr<ZmqMsgWrapperInterface> temp_msg_wrapper_ptr = temp_req_queue.front();
        temp_req_queue.pop_front();

        ZmqMsgWrapper<MsgCls>* msg_wrapper_ptr = dynamic_cast<ZmqMsgWrapper<MsgCls>*>(temp_msg_wrapper_ptr.get());
        if (!msg_wrapper_ptr) {
          ALOGW("ZmqManager:ReqClientThread: dynamic_cast failed for ZmqMsgWrapper of msg type \"%s\"", client->msg_type.c_str());
          continue;
        }

        int flag = client->client->request(msg_wrapper_ptr->msg.get());  // this might block the current thread.
        if (1 == flag) {
          //ALOGD("ZmqManager:ReqClientThread: send request of type \"%s\" successfully!", client->msg_type.c_str());
          client->req_sent_cb(msg_wrapper_ptr);
        } else {
          ALOGW("ZmqManager:ReqClientThread: Error occurs when sending request of type \"%s\"!", client->msg_type.c_str());
        }
      }

      if (client->end_request && temp_req_queue.size() > 0) {
        ALOGW("ZmqManager:ReqClientThread: abandon %d requests of type \"%s\"!", temp_req_queue.size(), client->msg_type.c_str());
      }
    }
  }


  template <class MsgCls>
  void RepServerThread(RepServerPtr server) {
    pthread_setname_np(pthread_self(), server->thread_name.c_str());
    while(! server->end_request) {
      std::shared_ptr<MsgCls> msg_ptr(new MsgCls());
      int flag = server->server->reply(msg_ptr.get());
      if (1 == flag) {
        //ALOGD("ZmqManager:RepServerThread: reply request of type \"%s\" successfully!", server->msg_type.c_str());
        ZmqMsgWrapper<MsgCls> msg_wrapper (msg_ptr);
        server->rep_recv_cb(&msg_wrapper);
      } else {
        ALOGW("ZmqManager:RepServerThread: Error occurs when replying request of type \"%s\"!", server->msg_type.c_str());
      }
    }
  }


  template <class MsgCls>
  void SubscriberThread(SubscriberPtr subscriber) {
    pthread_setname_np(pthread_self(), subscriber->thread_name.c_str());
    while(! subscriber->end_request) {
      std::shared_ptr<MsgCls> msg_ptr(new MsgCls());
      int flag = subscriber->subscriber->subscribe(msg_ptr.get(), subscriber->msg_type);
      if (flag > 0) {
        //ALOGD("ZmqManager:SubscriberThread: subscribe msg of type \"%s\" successfully!", subscriber->msg_type.c_str());
        ZmqMsgWrapper<MsgCls> msg_wrapper (msg_ptr);
        subscriber->msg_recv_cb(&msg_wrapper);
      } else {
        ALOGW("ZmqManager:SubscriberThread: Error occurs when subscribing msg of type \"%s\"!", subscriber->msg_type.c_str());
      }
    }
  }


protected:

  ReqClientPtr getReqClient(const std::string& msg_type) {
    ReqClientPtr client(nullptr);
    std::lock_guard<std::mutex> lock(m_map_mutex);

    if (m_req_clients.find(msg_type) != m_req_clients.end()) {
      client = m_req_clients[msg_type];
    }
    return client;
  }

  template <class MsgCls>
  bool addReqClient(ReqClientPtr client) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_req_clients.find(client->msg_type) != m_req_clients.end()) {
      ALOGW("ZmqManager:addReqClient: conflict for msg_type \"%s\"!", client->msg_type.c_str());
      return false;
    }
    client->client = nh.createReqClient(client->ip, client->msg_type);
    client->thread = std::shared_ptr<std::thread>(
            new std::thread(&ZmqManagerImpl::ReqClientThread<MsgCls>, this, client));
    m_req_clients[client->msg_type] = client;
    return true;
  }

  bool removeReqClient(const std::string& msg_type) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_req_clients.find(msg_type) != m_req_clients.end()) {
      ALOGW("ZmqManager:removeReqClient: unknown msg_type \"%s\"!", msg_type.c_str());
      return false;
    }
    m_req_clients.erase(msg_type);
    return true;
  }

  RepServerPtr getRepServer(const std::string& msg_type) {
    RepServerPtr server(nullptr);
    std::lock_guard<std::mutex> lock(m_map_mutex);

    if (m_rep_servers.find(msg_type) != m_rep_servers.end()) {
      server = m_rep_servers[msg_type];
    }
    return server;
  }

  template <class MsgCls>
  bool addRepServer(RepServerPtr server) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_rep_servers.find(server->msg_type) != m_rep_servers.end()) {
      ALOGW("ZmqManager:addRepServer: conflict for msg_type \"%s\"!", server->msg_type.c_str());
      return false;
    }
    server->server = nh.createRepServer(server->ip, server->msg_type);
    server->thread = std::shared_ptr<std::thread>(
            new std::thread(&ZmqManagerImpl::RepServerThread<MsgCls>, this, server));
    m_rep_servers[server->msg_type] = server;
    return true;
  }

  bool removeRepServer(const std::string& msg_type) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_rep_servers.find(msg_type) != m_rep_servers.end()) {
      ALOGW("ZmqManager:removeRepServer: unknown msg_type \"%s\"!", msg_type.c_str());
      return false;
    }
    m_rep_servers.erase(msg_type);
    return true;
  }

  SubscriberPtr getSubscriber(const std::string& msg_type) {
    SubscriberPtr subscriber(nullptr);
    std::lock_guard<std::mutex> lock(m_map_mutex);

    if (m_subscribers.find(msg_type) != m_subscribers.end()) {
      subscriber = m_subscribers[msg_type];
    }
    return subscriber;
  }

  template <class MsgCls>
  bool addSubscriber(SubscriberPtr subscriber) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_subscribers.find(subscriber->msg_type) != m_subscribers.end()) {
      ALOGW("ZmqManager:addSubscriber: conflict for msg_type \"%s\"!", subscriber->msg_type.c_str());
      return false;
    }

    subscriber->subscriber = nh.createSubscriber(subscriber->ip, subscriber->msg_type);
    subscriber->thread = std::shared_ptr<std::thread>(
            new std::thread(&ZmqManagerImpl::SubscriberThread<MsgCls>, this, subscriber));
    m_subscribers[subscriber->msg_type] = subscriber;
    return true;
  }

  bool removeSubscriber(const std::string& msg_type) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_subscribers.find(msg_type) != m_subscribers.end()) {
      ALOGW("ZmqManager:removeSubscriber: unknown msg_type \"%s\"!", msg_type.c_str());
      return false;
    }
    m_subscribers.erase(msg_type);
    return true;
  }

  PublisherPtr getPublisher(const std::string& msg_type) {
    PublisherPtr publisher(nullptr);
    std::lock_guard<std::mutex> lock(m_map_mutex);

    if (m_publishers.find(msg_type) != m_publishers.end()) {
      publisher = m_publishers[msg_type];
    }
    return publisher;
  }

  bool addPublisher(PublisherPtr publisher) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_publishers.find(publisher->msg_type) != m_publishers.end()) {
      ALOGW("ZmqManager:addPublisher: conflict for msg_type \"%s\"!", publisher->msg_type.c_str());
      return false;
    }

    publisher->publisher = nh.createPublisher(publisher->ip, publisher->msg_type);
    m_publishers[publisher->msg_type] = publisher;
    return true;
  }

  bool removePublisher(const std::string& msg_type) {
    std::lock_guard<std::mutex> lock(m_map_mutex);
    if (m_publishers.find(msg_type) != m_publishers.end()) {
      ALOGW("ZmqManager:removePublisher: unknown msg_type \"%s\"!", msg_type.c_str());
      return false;
    }
    m_publishers.erase(msg_type);
    return true;
  }

protected:
  nb_zmq::NodeHandle nh;

private:
  std::map<std::string, PublisherPtr> m_publishers;
  std::map<std::string, SubscriberPtr> m_subscribers;
  std::map<std::string, ReqClientPtr> m_req_clients;
  std::map<std::string, RepServerPtr> m_rep_servers;
  std::mutex m_map_mutex;
};

} // namespace ninebot_algo

#endif
