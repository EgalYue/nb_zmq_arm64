#include <thread>
#include <queue>          // std::queue
#include <vector>
#include <algorithm> 
#include <numeric>
#include <utility>      // std::pair
#include "ninebot_zmq/ninebot_zmq.h"
#include "ninebot_log/ninebot_log.h"
using namespace ninebot_algo;

static int VEC_SIZE = 1000; // sampling //TODO。。。
static int VECIMG_SIZE = 30; // sampling //TODO。。。

// typedef enum LEVEL_TYPE
// {
//     ANDROID_LOG_UNKNOWN = 0,
//     ANDROID_LOG_DEFAULT,    /* only for SetMinPriority() */
//     ANDROID_LOG_VERBOSE,
//     ANDROID_LOG_DEBUG,
//     ANDROID_LOG_INFO,
//     ANDROID_LOG_WARN,
//     ANDROID_LOG_ERROR,
//     ANDROID_LOG_FATAL,
//     ANDROID_LOG_SILENT, /* only for SetMinPriority(); must be last */
// }LEVEL_TYPE;

int64_t getCurrTs(){
    return std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
}

int handleCase(std::queue< std::pair <int64_t,int32_t> > &subQ, double max_duration, std::string logStr){
    if (subQ.size() == 2){
        std::pair <int64_t,int32_t> lastMsg = subQ.front();
        std::pair <int64_t,int32_t> currMsg = subQ.back();
        subQ.pop();

        int64_t last_ts = lastMsg.first;
        int64_t curr_ts = currMsg.first;
        long last_seq = lastMsg.second;
        long curr_seq = currMsg.second;

        double msg_duration = (double)((curr_ts - last_ts) / 1000000000); // ns -> s
        if (msg_duration >= max_duration){ // disconnect internet case
            ALOGW("[%s Case] Disconnect duration: [%10.9f s] . disconnect time: [%ld] , reconnect time [%ld]", logStr.c_str(), msg_duration, last_ts, curr_ts);
        }
        if (curr_seq - last_seq > 1){ // lost msg case
            ALOGW("[%s Case] LOST MSG, last_seq: [%ld], curr_seq: [%ld], lost [%ld]", logStr.c_str(), last_seq, curr_seq, curr_seq - last_seq - 1);
        }
        return 1;
    } else{
        return -1;
    }
}

void subImgThread(std::shared_ptr<nb_zmq::ZmqSubscriber> suber, std::string topic, double max_duration){
    ALOGW("[Image Case]: --- Begin sub ---");
    std::pair <int64_t,int32_t> eachMsg;
    std::queue< std::pair <int64_t,int32_t> > subQ;  // this queue can have max. 2 elements 
    std::vector<double> delayV;

    std::shared_ptr<nb_zmq::FrameStampedImageWithPose> frame_recv = std::make_shared<nb_zmq::FrameStampedImageWithPose>();
    while(1){
        if (suber->subscribe(frame_recv.get(), topic) > 0){
            int32_t curr_seq = frame_recv->msg_desc.header().seq();
            int64_t curr_ts = getCurrTs();
            eachMsg = std::make_pair(curr_ts, curr_seq);
            subQ.push(eachMsg);

            // delay 
            double delay = (double)(curr_ts - frame_recv->msg_desc.header().stamp().time_stamp()) / 1000000000; // us -> s
            delayV.push_back(delay);
            if(VECIMG_SIZE == delayV.size()){
                std::vector<double>::iterator maxDelayIter = std::max_element(delayV.begin(), delayV.end());
                std::vector<double>::iterator minDelayIter = std::min_element(delayV.begin(), delayV.end());
                double avgDelay = std::accumulate( delayV.begin(), delayV.end(), 0.0) / (delayV.size());
                delayV.clear(); // Removes all elements from the vector 
                
                ALOGW("[Image Case]: [delay s] maxDelay: [%f], minDelay: [%f], avgDelay: [%f], Seq: [%ld]", *maxDelayIter, *minDelayIter, avgDelay, curr_seq);
            }
        } else {
            ALOGD("[Image Case]: no msg");
        }
        
        // Following is used to determine Disconnect and LOST msg case.
        if (handleCase(subQ, max_duration, "Image") < 0){
            continue;
        }
    }
    ALOGD("[Image Case] === subImgThread End ===");
}

void subIMUThread(std::shared_ptr<nb_zmq::ZmqSubscriber> suber, std::string topic, double max_duration){
    ALOGW("[IMU Case]: --- Begin sub ---");
    std::pair <int64_t, int32_t> eachMsg;
    std::queue< std::pair <int64_t,int32_t> > subQ;  // this queue can have max. 2 elements 
    std::vector<double> delayV;

    std::shared_ptr<Segway_proto::StampedIMU> frame_recv = std::make_shared<Segway_proto::StampedIMU>();
    while(1){
        if (suber->subscribe(frame_recv.get(), topic) > 0){            
            int64_t curr_ts = getCurrTs();
            int32_t curr_seq = frame_recv->header().seq();
            eachMsg = std::make_pair(curr_ts, curr_seq);
            subQ.push(eachMsg);
            
            // delay 
            double delay = (double)(curr_ts - frame_recv->header().stamp().time_stamp()) / 1000000000; // us -> s
            delayV.push_back(delay);
            if(VEC_SIZE == delayV.size()){
                std::vector<double>::iterator maxDelayIter = std::max_element(delayV.begin(), delayV.end());
                std::vector<double>::iterator minDelayIter = std::min_element(delayV.begin(), delayV.end());
                double avgDelay = std::accumulate( delayV.begin(), delayV.end(), 0.0) / (delayV.size());
                delayV.clear(); // Removes all elements from the vector 
                
                ALOGW("[IMU Case]: [delay s] maxDelay: [%f], minDelay: [%f], avgDelay: [%f], Seq: [%ld]", *maxDelayIter, *minDelayIter, avgDelay, curr_seq);
            }
        } else {
            ALOGD("[IMU Case]: no msg");
        }

        // Following is used to determine Disconnect and LOST msg case.
        if (handleCase(subQ, max_duration, "IMU") < 0){
            continue;
        }
    }
    ALOGD("[IMU Case] === subIMUThread End ===");
}

void subLidarThread(std::shared_ptr<nb_zmq::ZmqSubscriber> suber, std::string topic, double max_duration){
    ALOGW("[Lidar Case]: --- Begin sub ---");
    std::pair <int64_t,int32_t> eachMsg;
    std::queue< std::pair <int64_t,int32_t> > subQ;  // this queue can have max. 2 elements 
    std::vector<double> delayV;

    std::shared_ptr<nb_zmq::FrameStampedLidarScan> frame_recv = std::make_shared<nb_zmq::FrameStampedLidarScan>();
    while(1){
        if (suber->subscribe(frame_recv.get(), topic) > 0){
            int64_t curr_ts = getCurrTs();
            int32_t curr_seq = frame_recv->msg_desc.header().seq();
            eachMsg = std::make_pair(curr_ts, curr_seq);
            subQ.push(eachMsg);
            
            // delay 
            double delay = (double)(curr_ts - frame_recv->msg_desc.header().stamp().time_stamp()) / 1000000000; // us -> s
            delayV.push_back(delay);
            if(VEC_SIZE == delayV.size()){
                std::vector<double>::iterator maxDelayIter = std::max_element(delayV.begin(), delayV.end());
                std::vector<double>::iterator minDelayIter = std::min_element(delayV.begin(), delayV.end());
                double avgDelay = std::accumulate( delayV.begin(), delayV.end(), 0.0) / (delayV.size());
                delayV.clear(); // Removes all elements from the vector 
                
                ALOGW("[Lidar Case]: [delay s] maxDelay: [%f], minDelay: [%f], avgDelay: [%f], Seq: [%ld]", *maxDelayIter, *minDelayIter, avgDelay, curr_seq);
            }
        } else {
            ALOGD("[Lidar Case]: no msg");
        }

        // Following is used to determine Disconnect and LOST msg case.
        if (handleCase(subQ, max_duration, "Lidar") < 0){
            continue;
        }        
    }
    ALOGD("[Lidar Case] === subLidarThread End ===");
}

void subEncoderThread(std::shared_ptr<nb_zmq::ZmqSubscriber> suber, std::string topic, double max_duration){
    ALOGW("[Encoder Case]: --- Begin sub ---");
    std::pair <int64_t,int32_t> eachMsg;
    std::queue< std::pair <int64_t,int32_t> > subQ;  // this queue can have max. 2 elements 
    std::vector<double> delayV;
    
    std::shared_ptr<Segway_proto::StampedEncoderData> frame_recv = std::make_shared<Segway_proto::StampedEncoderData>();
    while(1){
        if (suber->subscribe(frame_recv.get(), topic) > 0){
            int64_t curr_ts = getCurrTs();
            int32_t curr_seq = frame_recv->header().seq();
            eachMsg = std::make_pair(curr_ts, curr_seq);
            subQ.push(eachMsg);
            
            // delay 
            double delay = (double)(curr_ts - frame_recv->header().stamp().time_stamp()) / 1000000000; // us -> s
            delayV.push_back(delay);
            if(VEC_SIZE == delayV.size()){
                std::vector<double>::iterator maxDelayIter = std::max_element(delayV.begin(), delayV.end());
                std::vector<double>::iterator minDelayIter = std::min_element(delayV.begin(), delayV.end());
                double avgDelay = std::accumulate( delayV.begin(), delayV.end(), 0.0) / (delayV.size());
                delayV.clear(); // Removes all elements from the vector 
                
                ALOGW("[Encoder Case]: [delay s] maxDelay: [%f], minDelay: [%f], avgDelay: [%f], Seq: [%ld]", *maxDelayIter, *minDelayIter, avgDelay, curr_seq);
            }
        } else {
            ALOGD("[Encoder Case]: no msg");
        }

        // Following is used to determine Disconnect and LOST msg case.
        if (handleCase(subQ, max_duration, "Encoder") < 0){
            continue;
        } 
    }
    ALOGD("[Encoder Case] === subEncoderThread End ===");
}

void subLocalizationThread(std::shared_ptr<nb_zmq::ZmqSubscriber> suber, std::string topic, double max_duration){
    ALOGW("[Localization Case]: --- Begin sub ---");
    std::pair <int64_t,int32_t> eachMsg;
    std::queue< std::pair <int64_t,int32_t> > subQ;  // this queue can have max. 2 elements 
    std::vector<double> delayV;
    
    std::shared_ptr<Segway_proto::StampedLocalization> frame_recv = std::make_shared<Segway_proto::StampedLocalization>();
    while(1){
        if (suber->subscribe(frame_recv.get(), topic) > 0){
            int64_t curr_ts = getCurrTs();
            int32_t curr_seq = frame_recv->header().seq();
            eachMsg = std::make_pair(curr_ts, curr_seq);
            subQ.push(eachMsg);
            
            // delay 
            double delay = (double)(curr_ts - frame_recv->header().stamp().time_stamp()) / 1000000000; // us -> s
            delayV.push_back(delay);
            if(VEC_SIZE == delayV.size()){
                std::vector<double>::iterator maxDelayIter = std::max_element(delayV.begin(), delayV.end());
                std::vector<double>::iterator minDelayIter = std::min_element(delayV.begin(), delayV.end());
                double avgDelay = std::accumulate( delayV.begin(), delayV.end(), 0.0) / (delayV.size());
                delayV.clear(); // Removes all elements from the vector 
                
                ALOGW("[Localization Case]: [delay s] maxDelay: [%f], minDelay: [%f], avgDelay: [%f], Seq: [%ld]", *maxDelayIter, *minDelayIter, avgDelay, curr_seq);
            }
        } else {
            ALOGD("[Localization Case]: no msg");
        }

        // Following is used to determine Disconnect and LOST msg case.
        if (handleCase(subQ, max_duration, "Localization") < 0){
            continue;
        } 
    }
    ALOGD("[Localization Case] === subLocalizationThread End ===");
}

void replySlamConfigThread(std::shared_ptr<nb_zmq::ZmqRepServer> replier){
    ALOGW("[replySlamConfigThread Case]: --- Begin replySlamConfigThread ---");
    while(1){
        std::shared_ptr<Segway_proto::SlamConfig> protoMsgPtr = std::make_shared<Segway_proto::SlamConfig>();

        int flag = replier->reply(protoMsgPtr.get());
        int64_t curr_ts = getCurrTs();
        ALOGD("[replySlamConfig Case]: Client recv protoMsgPtr->camera model: %s",protoMsgPtr->fisheye().model().c_str());
        ALOGW("[replySlamConfig Case]: Delay: %10.9f", (double)(curr_ts - protoMsgPtr->header().stamp().time_stamp()) / 1000000000);

        if (1 == flag)
        {
            ALOGD("[replySlamConfig Case]: Navi-port send SlamConfig proto to Cal-port successfully!");
        }
        else
        {
            ALOGE("[replySlamConfig Case]: Error occurs when Navi-port send SlamConfig proto to Cal-port!");
        }
    }
}

void requestResponseThread(std::shared_ptr<nb_zmq::ZmqReqClient> requester){                                            
    ALOGW("[requestResponse Case]: --- Begin requestResponseThread ---");
    while(1){
        int64_t curr_ts = getCurrTs();

        Segway_proto::Response resp;
        auto header = resp.mutable_header();
        header->set_seq(1);
        header->set_frame_id("empty");
        auto stamp = header->mutable_stamp();
        stamp->set_time_stamp(curr_ts);

        resp.set_type("type_ex");
        resp.set_code(123);
        resp.set_info("This is response ex");
        std::shared_ptr<Segway_proto::Response> protoMsgPtr = std::make_shared<Segway_proto::Response>(resp);

        int flag = requester->request(protoMsgPtr.get());
        if (1 == flag)
        {
            ALOGD("[replySlamConfig Case]: Cal-port send Response proto to Navi-port successfully!");
        }
        else
        {
            ALOGE("[replySlamConfig Case]: Error occurs when Cal-port send Response proto to Navi-port!");
        }
    }
}

void pubPoseThread(std::shared_ptr<nb_zmq::ZmqPublisher> puber, std::string topic){
    ALOGW("[Localization Case]: --- Begin Publish ---");
    int32_t seq = 0;
    while(1){
        usleep(30000); // 33Hz   
        {
            int64_t curr_ts = getCurrTs();

            Segway_proto::StampedLocalization point3DProto;
            auto header = point3DProto.mutable_header();
            header->set_seq(seq);
            header->set_frame_id("empty");

            auto stamp = header->mutable_stamp();
            stamp->set_time_stamp(curr_ts);

            auto pose = point3DProto.mutable_pose();
            auto p3d = pose->mutable_p_xyz();
            p3d->set_x(1.1);
            p3d->set_y(2.2);
            p3d->set_z(3.3);
            auto quat = pose->mutable_q_xyzw();
            quat->set_x(0);
            quat->set_y(0);
            quat->set_z(0);
            quat->set_w(1);

            std::shared_ptr<Segway_proto::StampedLocalization> protoMsgPtr = std::make_shared<Segway_proto::StampedLocalization>(point3DProto);
            puber->publish(protoMsgPtr.get(), topic);
        }
    }
    ALOGD("[Localization Case] === PubLocalizationThread End ===");
}


void tsPubThread(std::shared_ptr<nb_zmq::ZmqPublisher> puber, std::string topic){
    ALOGW("[Ts2WithID Pub Case]: --- Begin TsWWithID ---");
    int64_t frame_id = 0;
    while(1){
        // pub
        usleep(1000000); // 1min //TODO。。。
        int64_t curr_ts = getCurrTs();

        Segway_proto::Ts2WithID tsProto;
        tsProto.set_time_stamp_pub(curr_ts);
        tsProto.set_frame_id(frame_id);
        std::shared_ptr<Segway_proto::Ts2WithID> tsProtoPtr = std::make_shared<Segway_proto::Ts2WithID>(tsProto);
        puber->publish(tsProtoPtr.get(), topic);
        frame_id++;
    }
}

void tsSubThread(std::shared_ptr<nb_zmq::ZmqSubscriber> suber, std::string topic){
    ALOGW("[Ts2WithID Sub Case]: --- Begin TsWWithID ---");
    while(1){        
        // sub
        std::shared_ptr<Segway_proto::Ts2WithID> protoMsgPtr = std::make_shared<Segway_proto::Ts2WithID>();
        int res = suber->subscribe(protoMsgPtr.get(), topic);
        int64_t t1 = protoMsgPtr->time_stamp_pub();
        int64_t t2 = protoMsgPtr->time_stamp_forward();
        int64_t t3 = getCurrTs();
        if (res > 0){
                ALOGW("[Ts2WithID Case]: FrameID: %ld, System time diff: %10.9f", protoMsgPtr->frame_id(), (double)((2*t2 - t1 - t3)/2) / 1000000000);
                // ALOGW("[Ts2WithID Case]: Ts2WithID Msg delay: %10.9f", (double)((t3 -t1)/2) / 1000000000);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc < 4){
        std::cout<< "Usage: stress_testing [ipLocal] [ipTarget] [max_duration]" << std::endl;
        std::cout<< "Ex: stress_testing tcp://192.168.0.103 tcp://192.168.0.1 5" << std::endl;
        return -1;
    }
    std::cout << "=== This is stress_testing ... ===" << std::endl;
    std::string ipLocal = argv[1]; // "tcp://127.0.0.1";
    std::string ip = argv[2]; // "tcp://127.0.0.1";
    double max_duration = std::atof(argv[3]); // max disconnect duration [s]
    std::cout << ">>> max_duration: " << max_duration << std::endl;
    

    nb_zmq::NodeHandle nh;
    auto imageSuber = nh.createSubscriber(ip, nb_zmq::StampedImageWithPose);
    auto imuSuber = nh.createSubscriber(ip, nb_zmq::StampedIMU);
    auto lidarSuber = nh.createSubscriber(ip, nb_zmq::StampedLidarScan);
    auto encoderSuber = nh.createSubscriber(ip, nb_zmq::StampedEncoderData); 
    auto localizationSuber = nh.createSubscriber(ip, nb_zmq::StampedLocalization);
    auto tsSuber = nh.createSubscriber(ip, nb_zmq::Ts2WithID);

    auto slamConfigReplier = nh.createRepServer(ipLocal, nb_zmq::SlamConfig);
    auto responseRequester = nh.createReqClient(ip, nb_zmq::ResponseError); 
    
    auto posePuber = nh.createPublisher(ipLocal, nb_zmq::StampedLocalization);
    auto tsPuber = nh.createPublisher(ipLocal, nb_zmq::Ts2WithID); 

    std::thread image_th(subImgThread, imageSuber, nb_zmq::StampedImageWithPose, max_duration);
    std::thread imu_th(subIMUThread, imuSuber, nb_zmq::StampedIMU, max_duration);
    std::thread lidar_th(subLidarThread, lidarSuber, nb_zmq::StampedLidarScan, max_duration);
    std::thread encoder_th(subEncoderThread, encoderSuber, nb_zmq::StampedEncoderData, max_duration);
    std::thread localization_th(subLocalizationThread, localizationSuber, nb_zmq::StampedLocalization, max_duration);

    std::thread slamConfig_th(replySlamConfigThread, slamConfigReplier);
    std::thread response_th(requestResponseThread, responseRequester);

    std::thread ts_pubth(tsPubThread, tsPuber, nb_zmq::Ts2WithID);
    std::thread ts_subth(tsSubThread, tsSuber, nb_zmq::Ts2WithID);

    std::thread pose_th(pubPoseThread, posePuber, nb_zmq::StampedLocalization);

    if (image_th.joinable()){
        image_th.join();
    }
    if (imu_th.joinable()){
        imu_th.join();
    }
    if (lidar_th.joinable()){
        lidar_th.join();
    }
    if (encoder_th.joinable()){
        encoder_th.join();
    }
    if (localization_th.joinable()){
        localization_th.join();
    }

    if (pose_th.joinable()){
        pose_th.join();
    }

    if (slamConfig_th.joinable()){
        slamConfig_th.join();
    }

    if (response_th.joinable()){
        response_th.join();
    }

    if (ts_pubth.joinable()){
        ts_pubth.join();
    }

    if (ts_subth.joinable()){
        ts_subth.join();
    }

    ALOGW("[WARN] TEST");
    return 0;
}