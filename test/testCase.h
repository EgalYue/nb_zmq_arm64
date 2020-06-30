#include <iostream>
#include <memory>
#include <algorithm>
#include <random>
#include <functional>
#include <climits>
#include <vector>
#include <zmq.h>
// #include <opencv2/opencv.hpp>
#include <unistd.h> //sleep
#include <chrono>
#include "ninebot_zmq/ninebot_zmq.h"

using namespace ninebot_algo;
// using namespace nb_zmq;

namespace pubCase
{
    void generate_vec(std::vector<uint8_t> &data)
    {
        using random_bytes_engine = std::independent_bits_engine<std::default_random_engine, CHAR_BIT, uint8_t>;
        random_bytes_engine rbe;
        std::generate(begin(data), end(data), std::ref(rbe));
    }
    
    /*
    void readImg(const std::string &dirpath, int imgNr, cv::Mat &cur_img)
    {
        std::string posfix = ".pgm";
        std::string file = dirpath + "/" + std::to_string(imgNr) + posfix;
        std::cout << file << std::endl;
        cur_img = cv::imread(file, CV_LOAD_IMAGE_GRAYSCALE);
        //    cv::imshow("test", cur_img);
        //    cv::waitKey(1);
    }

    void toFrameImg(const cv::Mat &src, std::shared_ptr<FrameImage> dst, const std::string &frame_id, int64_t time_stamp)
    {
        // img descriptor
        Segway_proto::StampedImage imgProto;
        auto header = imgProto.mutable_header();
        header->set_seq(1);             //TODO
        header->set_frame_id(frame_id); // TODO

        auto stamp = header->mutable_stamp(); //TODO
        stamp->set_time_stamp(time_stamp);

        auto image = imgProto.mutable_image();
        image->set_height(src.rows);
        image->set_width(src.cols);
        image->set_encoding("mono8"); //TODO
        image->set_is_bigendian(1);   //TODO
        image->set_step(src.cols * src.elemSize());

        dst->msg_desc = imgProto;
        // img raw data
        size_t size = imgProto.image().step() * src.rows;
        dst->raw_data = std::make_shared<std::vector<uint8_t>>();
        dst->raw_data->resize(size);

        if (src.isContinuous())
        {
            memcpy(dst->raw_data->data(), src.data, size);
        }
        else
        {
            // Copy by row by row
            uint8_t *ros_data_ptr = dst->raw_data->data();
            uint8_t *cv_data_ptr = src.data;
            for (int i = 0; i < src.rows; ++i)
            {
                memcpy(ros_data_ptr, cv_data_ptr, imgProto.image().step());
                ros_data_ptr += imgProto.image().step();
                cv_data_ptr += src.step;
            }
        }
    }

    void toFrameImg(const cv::Mat &src, std::shared_ptr<FrameStampedImageWithPose> dst, const std::string &frame_id, int64_t time_stamp)
    {
        // img descriptor
        Segway_proto::StampedImageWithPose imgProto;
        // header
        auto header = imgProto.mutable_header();
        header->set_seq(1);             //TODO
        header->set_frame_id(frame_id); // TODO

        auto stamp = header->mutable_stamp(); //TODO
        stamp->set_time_stamp(time_stamp);
        // pose
        auto pose = imgProto.mutable_pose();
        auto point = pose->mutable_p_xyz();
        point->set_x(1.1);
        point->set_y(2.2);
        point->set_z(3.3);
        auto quat = pose->mutable_q_xyzw();
        quat->set_x(0);
        quat->set_y(0);
        quat->set_z(0);
        quat->set_w(1);

        // image
        auto image = imgProto.mutable_image();
        image->set_height(src.rows);
        image->set_width(src.cols);
        image->set_encoding("mono8"); //TODO
        image->set_is_bigendian(1);   //TODO
        image->set_step(src.cols * src.elemSize());

        dst->msg_desc = imgProto;
        // img raw data
        size_t size = imgProto.image().step() * src.rows;
        dst->raw_data = std::make_shared<std::vector<uint8_t>>();
        dst->raw_data->resize(size);

        if (src.isContinuous())
        {
            memcpy(dst->raw_data->data(), src.data, size);
        }
        else
        {
            // Copy by row by row
            uint8_t *ros_data_ptr = dst->raw_data->data();
            uint8_t *cv_data_ptr = src.data;
            for (int i = 0; i < src.rows; ++i)
            {
                memcpy(ros_data_ptr, cv_data_ptr, imgProto.image().step());
                ros_data_ptr += imgProto.image().step();
                cv_data_ptr += src.step;
            }
        }
    }

    void Image_case(nb_zmq::ZmqPublisher &mq_pub, std::string &filepath, std::string &topic)
    {
        cv::Mat cur_img;
        nb_zmq::Rate loop_rate(1);
        for (int i = 0; i < 1000; i++)
        {
            readImg(filepath, i, cur_img);
            // convert cv::Mat to FrameImage
            //std::shared_ptr<FrameImage> frame_pub = std::make_shared<FrameImage>(); // TODO
            std::shared_ptr<FrameStampedImageWithPose> frame_pub = std::make_shared<FrameStampedImageWithPose>(); // TODO

            int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            std::cout << curr_ts << std::endl;

            toFrameImg(cur_img, frame_pub, std::to_string(i), curr_ts);

            // publish
            //mq_pub.pubFrame(frame_pub.get(), "image"); //TODO topic
            mq_pub.publish(frame_pub.get(), topic); //TODO topic
            loop_rate.sleep();
        }
    }
*/

    void Image_case(nb_zmq::ZmqPublisher& mq_pub, std::string& topic, int frame_id){
        std::shared_ptr<FrameStampedImageWithPose> frame_pub = std::make_shared<FrameStampedImageWithPose>();

        // img raw data
        Segway_proto::StampedImageWithPose imgProto;
        size_t size = 480 * 640; // default TODO...
        frame_pub->raw_data = std::make_shared<std::vector<uint8_t>>();
        frame_pub->raw_data->resize(size);

        uint8_t data[size];
        for(int i =0;i< size;i++){
            data[i] = 8;
        };
        memcpy(frame_pub->raw_data->data(), data, size * sizeof(uint8_t));

        // img descriptor
        // header
        auto header = imgProto.mutable_header();
        header->set_seq(1); //TODO
        header->set_frame_id(std::to_string(frame_id)); // TODO

        auto stamp = header->mutable_stamp(); //TODO
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count();
        std::cout << "[ZMQ Publisher]: curr_ts: "<< curr_ts << std::endl;
        stamp->set_time_stamp(curr_ts);
        // pose
        auto pose = imgProto.mutable_pose();
        auto point = pose->mutable_p_xyz();
        point->set_x(1.1);
        point->set_y(2.2);
        point->set_z(3.3);
        auto quat = pose->mutable_q_xyzw();
        quat->set_x(0);
        quat->set_y(0);
        quat->set_z(0);
        quat->set_w(1);

        // image
        auto image = imgProto.mutable_image();
        image->set_height(640);
        image->set_width(480);
        image->set_encoding("mono8"); //TODO
        image->set_is_bigendian(1); //TODO
        image->set_step(480 * 1);

        frame_pub->msg_desc = imgProto;
        std::cout << ">>> frame_pub->raw_data->data().size() : "<< frame_pub->raw_data->size() << std::endl;

        mq_pub.publish(frame_pub.get(), topic);
    }

    void StampedLidarScan_case(nb_zmq::ZmqPublisher &mq_pub, std::string &topic, int frame_id)
    {
        std::shared_ptr<FrameStampedLidarScan> frame_pub = std::make_shared<FrameStampedLidarScan>();
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << curr_ts << std::endl;

        Segway_proto::StampedLidarScan lidar_proto;
        auto header = lidar_proto.mutable_header();
        header->set_seq(1);
        header->set_frame_id(std::to_string(frame_id));

        auto stamp = header->mutable_stamp();
        stamp->set_time_stamp(curr_ts);

        auto scan = lidar_proto.mutable_scan();
        scan->set_size(1440);
        scan->set_angle_min(55.5);
        scan->set_range_max(120.0);
        scan->set_angle_increment(2.0);
        scan->set_time_increment(5.0);
        scan->set_range_min(1.1);
        scan->set_range_max(10.0);

        frame_pub->msg_desc = lidar_proto;
        //TODO ....range data
        size_t size = lidar_proto.scan().size();
        std::cout << "lidar_proto.scan().size() " << size << std::endl;
        frame_pub->ranges = std::make_shared<std::vector<float>>();
        frame_pub->ranges->resize(size);
        float data[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = (float)i;
        }
        memcpy(frame_pub->ranges->data(), data, size * sizeof(float));
        std::cout << ">>> frame_pub->ranges->data().size() " << frame_pub->ranges->size() << std::endl;
        std::cout << ">>> frame_pub->ranges->at(last) " << frame_pub->ranges->at(size - 1) << std::endl;

        //TODO ....intensities data
        frame_pub->intensities = std::make_shared<std::vector<float>>();
        frame_pub->intensities->resize(size);
        memcpy(frame_pub->intensities->data(), data, size * sizeof(float));
        std::cout << ">>> frame_pub->ranges->data().size() " << frame_pub->intensities->size() << std::endl;
        std::cout << ">>> frame_pub->ranges->at(last) " << frame_pub->intensities->at(size - 1) << std::endl;

        mq_pub.publish(frame_pub.get(), topic); //TODO topic
    }

    void StampedIMU_case(nb_zmq::ZmqPublisher &mq_pub, std::string &topic, int frame_id)
    {
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << curr_ts << std::endl;

        Segway_proto::StampedIMU imu_proto; 
        auto header = imu_proto.mutable_header();
        header->set_seq(1);
        header->set_frame_id(std::to_string(frame_id));

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
        mq_pub.publish(protoMsgPtr.get(), topic); //TODO topic
    }

    void StampedEncoderData_case(nb_zmq::ZmqPublisher &mq_pub, std::string &topic, int frame_id)
    {
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << curr_ts << std::endl;

        Segway_proto::StampedEncoderData encoderProto;
        auto header = encoderProto.mutable_header();
        header->set_seq(1);
        header->set_frame_id(std::to_string(frame_id));

        auto stamp = header->mutable_stamp();
        stamp->set_time_stamp(curr_ts);

        auto data = encoderProto.mutable_data();
        auto pose = data->mutable_pose();
        auto p_xy = pose->mutable_p_xy();
        p_xy->set_x(1.1);
        p_xy->set_y(2.2);

        data->set_linear_velocity(3.3);
        data->set_angular_velocity(4.4);
        data->set_left_ticks(5);
        data->set_right_ticks(6);

        std::shared_ptr<Segway_proto::StampedEncoderData> protoMsgPtr = std::make_shared<Segway_proto::StampedEncoderData>(encoderProto);
        mq_pub.publish(protoMsgPtr.get(), topic);
    }

    void StampedPose3Dd_case(nb_zmq::ZmqPublisher &mq_pub, std::string &topic, int frame_id)
    {
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << curr_ts << std::endl;

        Segway_proto::StampedPose3Dd point3DProto;
        auto header = point3DProto.mutable_header();
        header->set_seq(1);
        header->set_frame_id(std::to_string(frame_id));

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

        std::shared_ptr<Segway_proto::StampedPose3Dd> protoMsgPtr = std::make_shared<Segway_proto::StampedPose3Dd>(point3DProto);
        mq_pub.publish(protoMsgPtr.get(), topic);
    }
} // namespace pubCase

//===================================================================================

namespace subCase
{   
    /*
    template <typename T>
    cv::Mat matFromFrameImg(T src)
    { // std::shared_ptr<FrameImage>
        uint32_t src_height = src->msg_desc.image().height();
        uint32_t src_width = src->msg_desc.image().width();
        int source_type = CV_8UC1; //TODO
        uint32_t src_step = src->msg_desc.image().step();
        cv::Mat dst(src_height, src_width, CV_8UC1, src->raw_data->data(), src_step);
        return dst;
    }
    */

    void callbackFuncImage_case(FrameStampedImageWithPose *framePtr){
        std::cout<< "====== This is FrameStampedImageWithPose callback func ======" <<std::endl;

        //cv::Mat res = matFromFrameImg(framePtr);
        std::cout << ">>> FrameImg ts: " << framePtr->msg_desc.header().stamp().time_stamp() << std::endl;
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << ">>> Curr ts:" << curr_ts << std::endl;
        printf(">>> Diff time: %10.9f\n", (double)(curr_ts - framePtr->msg_desc.header().stamp().time_stamp()) / 1000000000);

        std::cout << ">>> FrameStampedImageWithPose pose x: " << framePtr->msg_desc.pose().p_xyz().x() << std::endl;
        std::cout << ">>> FrameStampedImageWithPose pose y: " << framePtr->msg_desc.pose().p_xyz().y() << std::endl;
        std::cout << ">>> FrameStampedImageWithPose pose z: " << framePtr->msg_desc.pose().p_xyz().z() << std::endl;
        std::cout << ">>> FrameStampedImageWithPose raw data [last] z: " << (unsigned)framePtr->raw_data->at(framePtr->raw_data->size() - 1) << std::endl;
    }

    int Image_case(nb_zmq::ZmqSubscriber &mq_recv, std::string &topic, bool hasCallback)
    {
        if (hasCallback){
            mq_recv.subscribe(topic, callbackFuncImage_case);
            return 1;
        }

        std::shared_ptr<FrameStampedImageWithPose> frame_recv = std::make_shared<FrameStampedImageWithPose>();
        int res = mq_recv.subscribe(frame_recv.get(), topic);
        if(res > 0){
            callbackFuncImage_case(frame_recv.get());
        }
        return res;

        // cv::imshow("zmq_recv", res);
        // cv::waitKey(1);
    }

    void callbackFuncLidar(FrameStampedLidarScan* framePtr){
        std::cout<< "====== This is FrameStampedLidarScan callback func ======" <<std::endl;

        std::cout << ">>> FrameImg ts: " << framePtr->msg_desc.header().stamp().time_stamp() << std::endl;
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << ">>> Curr ts:" << curr_ts << std::endl;
        printf(">>> Diff time: %10.9f\n", (double)(curr_ts - framePtr->msg_desc.header().stamp().time_stamp()) / 1000000000);

        std::cout << ">>> FrameStampedLidarScan lidar size : " << framePtr->msg_desc.scan().size() << std::endl;
        std::cout << ">>> FrameStampedLidarScan ranges size : " << framePtr->ranges->size() << std::endl;
        std::cout << ">>> FrameStampedLidarScan ranges[last] : " << framePtr->ranges->at(framePtr->ranges->size() - 1) << std::endl;

        std::cout << ">>> FrameStampedLidarScan intensities size : " << framePtr->intensities->size() << std::endl;
        std::cout << ">>> FrameStampedLidarScan intensities[last] : " << framePtr->intensities->at(framePtr->intensities->size() - 1) << std::endl;

    }

    int StampedLidarScan_case(nb_zmq::ZmqSubscriber &mq_recv, std::string &topic, bool hasCallback)
    {
        if (hasCallback){
            mq_recv.subscribe(topic, callbackFuncLidar);
            return 1;
        }

        std::shared_ptr<FrameStampedLidarScan> frame_recv = std::make_shared<FrameStampedLidarScan>();
        int res = mq_recv.subscribe(frame_recv.get(), topic);
        if ( res > 0){
            callbackFuncLidar(frame_recv.get());
        }
        return res;
    }


    void callbackFuncIMU(Segway_proto::StampedIMU *protoMsgPtr){
        std::cout<< "====== This is StampedIMU callback func ======" <<std::endl;
        
        std::cout << ">>> StampedIMU ts: " << protoMsgPtr->header().stamp().time_stamp() << std::endl;
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << ">>> Curr ts:" << curr_ts << std::endl;
        printf(">>> Diff time: %10.9f\n", (double)(curr_ts - protoMsgPtr->header().stamp().time_stamp()) / 1000000000);

        std::cout << ">>> StampedIMU pose x: " << protoMsgPtr->data().acc_xyz().x() << std::endl;
        std::cout << ">>> StampedIMU pose y: " << protoMsgPtr->data().acc_xyz().y() << std::endl;
        std::cout << ">>> StampedIMU pose z: " << protoMsgPtr->data().acc_xyz().z() << std::endl;

        std::cout << ">>> StampedIMU pose x: " << protoMsgPtr->data().gyro_xyz().x() << std::endl;
        std::cout << ">>> StampedIMU pose y: " << protoMsgPtr->data().gyro_xyz().y() << std::endl;
        std::cout << ">>> StampedIMU pose z: " << protoMsgPtr->data().gyro_xyz().z() << std::endl;
    }

    int StampedIMU_case(nb_zmq::ZmqSubscriber &mq_recv, std::string &topic, bool hasCallback)
    {
        if (hasCallback){
            mq_recv.subscribe(topic, callbackFuncIMU);
            return 1;
        }

        std::shared_ptr<Segway_proto::StampedIMU> protoMsgPtr = std::make_shared<Segway_proto::StampedIMU>();
        int res = mq_recv.subscribe(protoMsgPtr.get(), topic);
        if (res > 0){
            callbackFuncIMU(protoMsgPtr.get());
        }
        return res;
    }


    void callbackEncoderData(Segway_proto::StampedEncoderData* protoMsgPtr){
        std::cout<< "====== This is StampedEncoderData callback func ======" <<std::endl;

        std::cout << ">>> FrameImg ts: " << protoMsgPtr->header().stamp().time_stamp() << std::endl;
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << ">>> Curr ts:" << curr_ts << std::endl;
        printf(">>> Diff time: %10.9f\n", (double)(curr_ts - protoMsgPtr->header().stamp().time_stamp()) / 1000000000);

        std::cout << ">>> StampedEncoderData angular_velocity: " << protoMsgPtr->data().angular_velocity() << std::endl;
        std::cout << ">>> StampedEncoderData_case linear_velocity: " << protoMsgPtr->data().linear_velocity() << std::endl;
    }

    int StampedEncoderData_case(nb_zmq::ZmqSubscriber &mq_recv, std::string &topic, bool hasCallback)
    {
        if (hasCallback){
            mq_recv.subscribe(topic, callbackEncoderData);
            return 1;
        }

        std::shared_ptr<Segway_proto::StampedEncoderData> protoMsgPtr = std::make_shared<Segway_proto::StampedEncoderData>();
        int res = mq_recv.subscribe(protoMsgPtr.get(), topic);
        if (res > 0){
            callbackEncoderData(protoMsgPtr.get());
        }
        return res;
    }

    void callbackPose3Dd(Segway_proto::StampedPose3Dd* protoMsgPtr){
        std::cout<< "====== This is callbackPose3Dd callback func ======" <<std::endl;
        
        std::cout << ">>> FrameImg ts: " << protoMsgPtr->header().stamp().time_stamp() << std::endl;
        int64_t curr_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        std::cout << ">>> Curr ts:" << curr_ts << std::endl;
        printf(">>> Diff time: %10.9f\n", (double)(curr_ts - protoMsgPtr->header().stamp().time_stamp()) / 1000000000);

        std::cout << ">>> StampedPose3Dd pose x: " << protoMsgPtr->pose().p_xyz().x() << std::endl;
        std::cout << ">>> StampedPose3Dd pose y: " << protoMsgPtr->pose().p_xyz().y() << std::endl;
        std::cout << ">>> StampedPose3Dd pose z: " << protoMsgPtr->pose().p_xyz().z() << std::endl;

        std::cout << ">>> StampedPose3Dd quen x: " << protoMsgPtr->pose().q_xyzw().x() << std::endl;
        std::cout << ">>> StampedPose3Dd pose y: " << protoMsgPtr->pose().q_xyzw().y() << std::endl;
        std::cout << ">>> StampedPose3Dd pose z: " << protoMsgPtr->pose().q_xyzw().z() << std::endl;
        std::cout << ">>> StampedPose3Dd pose w: " << protoMsgPtr->pose().q_xyzw().w() << std::endl;
    }

    int StampedPose3Dd_case(nb_zmq::ZmqSubscriber &mq_recv, std::string &topic, bool hasCallback)
    {
        if (hasCallback){
            mq_recv.subscribe(topic, callbackPose3Dd);
            return 1;
        }

        std::shared_ptr<Segway_proto::StampedPose3Dd> protoMsgPtr = std::make_shared<Segway_proto::StampedPose3Dd>();
        int res = mq_recv.subscribe(protoMsgPtr.get(), topic);
        if (res > 0){
            callbackPose3Dd(protoMsgPtr.get());
        }
        return res;
    }

} // namespace subCase

//=====================================================================================================================
namespace subPubCase
{   
    /*
    template <typename T>
    cv::Mat matFromFrameImg(T src)
    { // std::shared_ptr<FrameImage>
        uint32_t src_height = src->msg_desc.image().height();
        uint32_t src_width = src->msg_desc.image().width();
        int source_type = CV_8UC1; //TODO
        uint32_t src_step = src->msg_desc.image().step();
        cv::Mat dst(src_height, src_width, CV_8UC1, src->raw_data->data(), src_step);
        return dst;
    }
    */

    void Image_case(nb_zmq::ZmqSubscriber &mq_recv, nb_zmq::ZmqPublisher &mq_pub, const std::string &topic)
    {
        std::shared_ptr<FrameStampedImageWithPose> frame_recv = std::make_shared<FrameStampedImageWithPose>();
        // 1. subscribe
        mq_recv.subscribe(frame_recv.get(), topic);

        // 2. publish
        mq_pub.publish(frame_recv.get(), topic); //TODO topic

        std::cout << ">>> FrameStampedImageWithPose pose x: " << frame_recv->msg_desc.pose().p_xyz().x() << std::endl;
        std::cout << ">>> FrameStampedImageWithPose pose y: " << frame_recv->msg_desc.pose().p_xyz().y() << std::endl;
        std::cout << ">>> FrameStampedImageWithPose pose z: " << frame_recv->msg_desc.pose().p_xyz().z() << std::endl;
        std::cout << ">>> FrameStampedImageWithPose raw data [last] z: " << (unsigned)frame_recv->raw_data->at(frame_recv->raw_data->size() - 1) << std::endl;

        // cv::Mat res = matFromFrameImg(frame_recv);
        // cv::imshow("zmq_recv", res);
        // cv::waitKey(1);
    }

    void StampedIMU_case(nb_zmq::ZmqSubscriber &mq_recv, nb_zmq::ZmqPublisher &mq_pub, const std::string &topic)
    {

        std::shared_ptr<Segway_proto::StampedIMU> protoMsgPtr = std::make_shared<Segway_proto::StampedIMU>();
        // 1. subscribe
        mq_recv.subscribe(protoMsgPtr.get(), topic);

        // 2. publish
        mq_pub.publish(protoMsgPtr.get(), topic);

        std::cout << ">>> StampedIMU pose x: " << protoMsgPtr->data().acc_xyz().x() << std::endl;
        std::cout << ">>> StampedIMU pose y: " << protoMsgPtr->data().acc_xyz().y() << std::endl;
        std::cout << ">>> StampedIMU pose z: " << protoMsgPtr->data().acc_xyz().z() << std::endl;

        std::cout << ">>> StampedIMU pose x: " << protoMsgPtr->data().gyro_xyz().x() << std::endl;
        std::cout << ">>> StampedIMU pose y: " << protoMsgPtr->data().gyro_xyz().y() << std::endl;
        std::cout << ">>> StampedIMU pose z: " << protoMsgPtr->data().gyro_xyz().z() << std::endl;
    }

    void StampedLidarScan_case(nb_zmq::ZmqSubscriber &mq_recv, nb_zmq::ZmqPublisher &mq_pub, const std::string &topic)
    {
        std::shared_ptr<FrameStampedLidarScan> frame_recv = std::make_shared<FrameStampedLidarScan>();
        // 1. subscribe
        mq_recv.subscribe(frame_recv.get(), topic);

        // 2. publish
        mq_pub.publish(frame_recv.get(), topic);

        std::cout << ">>> FrameStampedLidarScan lidar size : " << frame_recv->msg_desc.scan().size() << std::endl;
        std::cout << ">>> FrameStampedLidarScan ranges size : " << frame_recv->ranges->size() << std::endl;
        std::cout << ">>> FrameStampedLidarScan ranges[last] : " << frame_recv->ranges->at(frame_recv->ranges->size() - 1) << std::endl;

        std::cout << ">>> FrameStampedLidarScan intensities size : " << frame_recv->intensities->size() << std::endl;
        std::cout << ">>> FrameStampedLidarScan intensities[last] : " << frame_recv->intensities->at(frame_recv->intensities->size() - 1) << std::endl;
    }

    void StampedEncoderData_case(nb_zmq::ZmqSubscriber &mq_recv, nb_zmq::ZmqPublisher &mq_pub, const std::string &topic)
    {
        std::shared_ptr<Segway_proto::StampedEncoderData> protoMsgPtr = std::make_shared<Segway_proto::StampedEncoderData>();
        // 1. subscribe
        mq_recv.subscribe(protoMsgPtr.get(), topic);

        // 2. publish
        mq_pub.publish(protoMsgPtr.get(), topic);

        std::cout << ">>> StampedEncoderData angular_velocity: " << protoMsgPtr->data().angular_velocity() << std::endl;
        std::cout << ">>> StampedEncoderData_case linear_velocity: " << protoMsgPtr->data().linear_velocity() << std::endl;
    }

    void StampedPose3Dd_case(nb_zmq::ZmqSubscriber &mq_recv, nb_zmq::ZmqPublisher &mq_pub, const std::string &topic)
    {
        std::shared_ptr<Segway_proto::StampedPose3Dd> protoMsgPtr = std::make_shared<Segway_proto::StampedPose3Dd>();
        // 1. subscribe
        mq_recv.subscribe(protoMsgPtr.get(), topic);

        // 2. publish
        mq_pub.publish(protoMsgPtr.get(), topic);

        std::cout << ">>> StampedPose3Dd pose x: " << protoMsgPtr->pose().p_xyz().x() << std::endl;
        std::cout << ">>> StampedPose3Dd pose y: " << protoMsgPtr->pose().p_xyz().y() << std::endl;
        std::cout << ">>> StampedPose3Dd pose z: " << protoMsgPtr->pose().p_xyz().z() << std::endl;

        std::cout << ">>> StampedPose3Dd quen x: " << protoMsgPtr->pose().q_xyzw().x() << std::endl;
        std::cout << ">>> StampedPose3Dd pose y: " << protoMsgPtr->pose().q_xyzw().y() << std::endl;
        std::cout << ">>> StampedPose3Dd pose z: " << protoMsgPtr->pose().q_xyzw().z() << std::endl;
        std::cout << ">>> StampedPose3Dd pose w: " << protoMsgPtr->pose().q_xyzw().w() << std::endl;
    }

} // namespace subPubCase

namespace serverCase
{
    int SlamStartup_case(nb_zmq::ZmqRepServer &zmqRepServer)
    {
        std::shared_ptr<Segway_proto::SlamStartup> protoMsgPtr = std::make_shared<Segway_proto::SlamStartup>();

        int flag = zmqRepServer.reply(protoMsgPtr.get());
        std::cout << ">>> Client recv protoMsgPtr->use_fake_pose: " << protoMsgPtr->use_fake_pose() << std::endl;
        std::cout << ">>> Client recv protoMsgPtr->camera model: " << protoMsgPtr->fisheye().model() << std::endl;
        if (1 == flag)
        {
            std::cout << ">>> Navi-port send SlamStartup proto to Cal-port successfully!" << std::endl;
        }
        else
        {
            std::cout << ">>> Error occurs when Navi-port send SlamStartup proto to Cal-port!" << std::endl;
        }
        return flag;
    }

    int Response_case(nb_zmq::ZmqRepServer &zmqRepServer)
    {
        std::shared_ptr<Segway_proto::Response> protoMsgPtr = std::make_shared<Segway_proto::Response>();
        int flag = zmqRepServer.reply(protoMsgPtr.get()); // SlamStartup

        std::cout << ">>> Client recv Response->type: " << protoMsgPtr->type() << std::endl;
        std::cout << ">>> Client recv Response->code: " << protoMsgPtr->code() << std::endl;
        std::cout << ">>> Client recv Response->info: " << protoMsgPtr->info() << std::endl;

        if (1 == flag)
        {
            std::cout << ">>> Navi-port receive SlamStartup proto from Cal-port successfully!" << std::endl;
        }
        else
        {
            std::cout << ">>> Error occurs when Navi-port receive SlamStartup proto from Cal-port!" << std::endl;
        }
        return flag;
    }

    int IP_case(nb_zmq::ZmqRepServer &zmqRepServer)
    {
        std::string serverIP;
        if (GetIP(serverIP))
        {
            int flag = zmqRepServer.reply(serverIP);
            if (1 == flag)
            {
                //J4A_ALOGD("[ZMQ Server]: Navi-port send '%s' to Cal-port successfully!", serverIP.c_str());
                std::cout << ">>> Navi-port send " << serverIP << " to Cal-port successfully!" << std::endl;
            }
            else
            {
                //J4A_ALOGD("[ZMQ Server]: Error occurs when Navi-port send 'ip' to Cal-port!");
                std::cout << ">>> Error occurs when Navi-port send 'ip' to Cal-port!" << std::endl;
            }
            return flag;
        }
        else
        {
            std::cout << ">>> Error Could not get current device IP! " << std::endl;
            return -1;
        }
    }


    int androidCtrl_case(nb_zmq::AndroidControl &androidCtrl, long timeout)
    {
        Segway_proto::HeartbeatCmd hbc;
        hbc.set_hb(8);
        hbc.set_cmd(5);
        std::shared_ptr<Segway_proto::HeartbeatCmd> protoMsgPtr = std::make_shared<Segway_proto::HeartbeatCmd>(hbc);

        int flag = androidCtrl.replyHeartBeat(protoMsgPtr.get(), timeout);
        if (1 == flag)
        {
            //J4A_ALOGD("[ZMQ AndroidCtrl]: Navi-port send '%s' to Cal-port successfully!", serverIP.c_str());
            std::cout << ">>> Navi-port send cmd: " <<  protoMsgPtr->hb() << " to Cal-port successfully!" << std::endl;
        }
        else
        {
            //J4A_ALOGD("[ZMQ AndroidCtrl]: Error occurs when Navi-port send 'ip' to Cal-port!");
            std::cout << ">>> Error occurs when Navi-port send heartbeat to Cal-port!" << std::endl;
        }
        return flag;
    }

} // namespace serverCase

namespace clientCase
{
    int SlamStartup_case(nb_zmq::ZmqReqClient &zmqReqClient)
    {
        Segway_proto::SlamStartup slamStartup;
        auto fisheye = slamStartup.mutable_fisheye();
        fisheye->set_model("Mono_model");
        slamStartup.set_use_fake_pose(true);
        std::shared_ptr<Segway_proto::SlamStartup> protoMsgPtr = std::make_shared<Segway_proto::SlamStartup>(slamStartup);

        int flag = zmqReqClient.request(protoMsgPtr.get());
        if (1 == flag)
        {
            std::cout << ">>> Cal-port receive SlamStartup proto from Navi-port successfully!" << std::endl;
        }
        else
        {
            std::cout << ">>> Error occurs when Cal-port receive SlamStartup proto from Navi-port!" << std::endl;
        }
        return flag;
    }

    int Response_case(nb_zmq::ZmqReqClient &zmqReqClient)
    {
        Segway_proto::Response resp;
        resp.set_type("type_ex");
        resp.set_code(123);
        resp.set_info("This is response ex");
        std::shared_ptr<Segway_proto::Response> protoMsgPtr = std::make_shared<Segway_proto::Response>(resp);

        int flag = zmqReqClient.request(protoMsgPtr.get());
        if (1 == flag)
        {
            std::cout << ">>> Cal-port send Response proto to Navi-port successfully!" << std::endl;
        }
        else
        {
            std::cout << ">>> Error occurs when Cal-port send Response proto to Navi-port!" << std::endl;
        }
        return flag;
    }

    int IP_case(nb_zmq::ZmqReqClient &zmqReqClient)
    {
        std::string serverIP;
        int flag = zmqReqClient.request(serverIP);
        if (1 == flag)
        {
            //J4A_ALOGD("[ZMQ Client]: Cal-port send Response proto to Navi-port successfully!");
            std::cout << ">>> Cal-port send Response proto to Navi-port successfully!" << std::endl;
        }
        else
        {
            //J4A_ALOGD("[ZMQ Client]: Error occurs when Cal-port send Response proto to Navi-port!");
            std::cout << ">>> Error occurs when Cal-port send Response proto to Navi-port!" << std::endl;
        }
        return flag;
    }

    int linuxCtrl_case(nb_zmq::LinuxControl &linuxCtrl, long timeout)
    {
        Segway_proto::HeartbeatCmd hbc;
        hbc.set_hb(8);
        hbc.set_cmd(5);
        std::shared_ptr<Segway_proto::HeartbeatCmd> protoMsgPtr = std::make_shared<Segway_proto::HeartbeatCmd>(hbc);

        int flag = linuxCtrl.requestHeartBeat(protoMsgPtr.get(), timeout); //ms
        if (1 == flag)
        {
            //J4A_ALOGD("[ZMQ Client]: Cal-port send heartbeat to Navi-port successfully!");
            std::cout << ">>> Cal-port send heartbeat to Navi-port successfully!" << std::endl;
        }
        else
        {
            //J4A_ALOGD("[ZMQ Client]: Error occurs when Cal-port send heartbeat to Navi-port!");
            std::cout << ">>> Error occurs when Cal-port send heartbeat to Navi-port!" << std::endl;
        }
        return flag;
    }

} // namespace clientCase