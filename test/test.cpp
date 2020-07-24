#include "testCase.h"
#include <thread>
#include <ninebot_zmq/ninebot_zmq_manager_impl.h>

using namespace ninebot_algo;
static bool g_closeSignal = false;



void threadSub(std::shared_ptr<nb_zmq::ZmqSubscriber> mq_recv, std::string topic){

    if (StampedImageWithPose == topic) {
        while(1){
            subCase::Image_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }    
        }
    } else if (StampedLidarScan == topic) {
        while(1){
            subCase::StampedLidarScan_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    } else if (StampedIMU == topic) {
        while(1){
            subCase::StampedIMU_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }
        }  
    } else if (StampedEncoderData == topic) {
        while(1){
            subCase::StampedEncoderData_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    } else if (StampedPose3Dd == topic) {
        while(1){
            subCase::StampedPose3Dd_case(mq_recv, topic);
            if (g_closeSignal){
                break;
            }   
        }
    }
    
    std::cout<< ">>> Closing socket..." << std::endl;
    mq_recv->closeSocket(); //TODO... !!!!
}

void threadClose(std::shared_ptr<nb_zmq::ZmqSubscriber>  mq_recv){
    while (true) {
        usleep(5000000); // 5s
        break;
    }
    mq_recv->terminateBlocking();   
    g_closeSignal = true;
}


int main(int argc, char *argv[]) {
    if (argc < 4){
        std::cout<< "Usage: test [ip] msgType topic" << std::endl;
        std::cout<< "Ex: test tcp://127.0.0.1 StampedIMU StampedIMU" << std::endl;
        return -1;
    }
    std::cout << "=== This is zmq Recv... ===" << std::endl;

    const std::string ip = argv[1]; // "tcp://127.0.0.1";
    const std::string msgType = argv[2]; // "StampedImageWithPose"
    const std::string topic = argv[3];

    ZmqManagerImpl zmImpl;

        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << curr_ts << std::endl;

        Segway_proto::StampedIMU imu_proto; 
        auto header = imu_proto.mutable_header();
        header->set_seq(1);
        header->set_frame_id(std::to_string(1));

        auto stamp = header->mutable_stamp();
        stamp->set_time_stamp(curr_ts);

        auto data = imu_proto.mutable_data();
        auto acc_xyz = data->mutable_acc_xyz();
        acc_xyz->set_x(1.1);
        acc_xyz->set_y(2.2);
        acc_xyz->set_z(3.3);

        auto gyro_xyz = data->mutable_gyro_xyz();
        gyro_xyz->set_x(4.4);
        gyro_xyz->set_y(5.5);
        gyro_xyz->set_z(6.6);

        std::shared_ptr<Segway_proto::StampedIMU> protoMsgPtr = std::make_shared<Segway_proto::StampedIMU>(imu_proto);

    zmImpl.startPublisher(ip, msgType);
    while(1){
    zmImpl.publish(StampedIMU, protoMsgPtr);
    }

    std::cout<< " --- end ---" << std::endl;
    return 0;
}