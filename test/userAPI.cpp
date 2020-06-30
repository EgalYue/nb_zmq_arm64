#include "ninebot_zmq/ninebot_zmq.h"

using namespace ninebot_algo;


int main(){
    std::string ip = "tcp://127.0.0.1";
    std::string msgType = AllType;
    std::string topic = "TopicName";

    nb_zmq::ZmqPublisher mq_pub;
    mq_pub.init(ip, msgType); // sending all msg as seqence, using one port!

    while(1){
        usleep(100000); // 10Hz
        
        std::shared_ptr<FrameStampedImageWithPose> frame_pub = std::make_shared<FrameStampedImageWithPose>(); // TODO
        topic = "FrameStampedImageWithPose";
        mq_pub.publish(frame_pub.get(), topic);

        std::shared_ptr<FrameStampedLidarScan> frame_pub2 = std::make_shared<FrameStampedLidarScan>(); // TODO
        topic = "FrameStampedLidarScan";
        mq_pub.publish(frame_pub2.get(), topic);

        std::shared_ptr<Segway_proto::StampedIMU> frame_pub3 = std::make_shared<Segway_proto::StampedIMU>(); // TODO
        topic = "StampedIMU";
        mq_pub.publish(frame_pub3.get(), topic);

        // ......
    }

    return 0;
}




int main(){
    std::string ip = "tcp://127.0.0.1";
    std::string msgType = ResponseError;

    nb_zmq::ZmqRepServer zmqRepServer;
    zmqRepServer.init(ip, msgType);
    while (1){
        std::shared_ptr<Segway_proto::Response> protoMsgPtr = std::make_shared<Segway_proto::Response>();//TODO
        zmqRepServer.reply(protoMsgPtr.get());
    }

    return 0;
}

/*
int main(){
    std::string ip = "tcp://127.0.0.1";
    std::string msgType = ResponseError;

    nb_zmq::ZmqReqClient zmqReqClient;
    zmqReqClient.init(ip, msgType);
    while (1){
        std::shared_ptr<Segway_proto::Response> protoMsgPtr = std::make_shared<Segway_proto::Response>();//TODO
        zmqReqClient.request(protoMsgPtr.get());
    }

    return 0;
}
*/



/*
int main(){
    std::string ip = "tcp://127.0.0.1";
    std::string msgType = SlamStartup;

    nb_zmq::ZmqReqClient zmqReqClient;
    zmqReqClient.init(ip, msgType);
    while (1){
        std::shared_ptr<Segway_proto::SlamStartup> protoMsgPtr = std::make_shared<Segway_proto::SlamStartup>();//TODO
        zmqReqClient.request(protoMsgPtr.get());
    }

    return 0;
}
*/

/*
int main(){
    std::string ip = "tcp://127.0.0.1";
    std::string msgType = SlamStartup;

    nb_zmq::ZmqRepServer zmqRepServer;
    zmqRepServer.init(ip, msgType);
    while (1){
        std::shared_ptr<Segway_proto::SlamStartup> protoMsgPtr = std::make_shared<Segway_proto::SlamStartup>();//TODO
        zmqRepServer.reply(protoMsgPtr.get());
    }

    return 0;
}
*/
/*
int main(){
    std::string ip = "tcp://127.0.0.1";
    std::string msgType = StampedImageWithPose;
    std::string topic = "TopicName";

    nb_zmq::ZmqSubscriber mq_sub;
    mq_sub.init(ip, msgType);
    while (1){
        std::shared_ptr<FrameStampedImageWithPose> frame_pub = std::make_shared<FrameStampedImageWithPose>(); // TODO
        mq_sub.subscribe(frame_pub.get(), topic);
    }

    return 0;

}
*/


/*
int main(){
    std::string ip = "tcp://127.0.0.1";
    std::string msgType = StampedImageWithPose;
    std::string topic = "TopicName";

    nb_zmq::ZmqPublisher mq_pub;
    mq_pub.init(ip, msgType);
    nb_zmq::Rate loop_rate(10);
    while (1){
        std::shared_ptr<FrameStampedImageWithPose> frame_pub = std::make_shared<FrameStampedImageWithPose>(); // TODO
        mq_pub.publish(frame_pub.get(), topic);
        loop_rate.sleep();
    }

    return 0;
}*/