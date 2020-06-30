#include <iostream>
#include <string>
#include <stdlib.h>

#include <sys/socket.h>
#include <string.h>
#include <string>
#include <assert.h>
#include <cstring>
using namespace std;


#include "points.pb.h"

#include <dirent.h>
#include <vector>
#include <algorithm>
#include <time.h>

int main()
{
//    vector<uint8_t> vec;
//    vec.push_back(0);
//    vec.push_back(1);
//    vec.push_back(2);
//    vec.push_back(3);
//    vec.push_back(4);
////    printf("", vec[2]);
//    cout<< unsigned(vec[2]) << endl;
//    uint8_t * ptr = (uint8_t *)(&vec.data()[0]);
//
//    std ::vector<uint8_t > vec2(ptr,  ptr + sizeof(ptr) / sizeof(ptr[0]));
//
//    cout << sizeof(ptr) << endl;
//    cout <<sizeof(ptr[0]) << endl;
//
//    cout<< unsigned(vec2[2])<< endl;
//    cout<< vec2.size()<< endl;


//    u_char array[307200] = {'a'};
//    u_char *ptr = array;
//    cout<< unsigned(ptr[0]) << endl;
//    cout<< unsigned(ptr[1]) << endl;
//    cout<< unsigned(ptr[2]) << endl;
//
//
//    std ::vector<uint8_t > vec2(ptr,  ptr+ 307200);
//
//    cout <<"new vec size: "<< vec2.size()<< endl;
//
//    cout <<unsigned(vec2[0]) << endl;
//    cout <<unsigned(vec2[1]) << endl;
//    cout <<unsigned(vec2[2]) << endl;
//
//    int64_t ts = 1589515347473093508;
//    string sec = to_string(ts).substr(0,10);
//    string nsec = to_string(ts).substr(10,to_string(ts).length()-1);
//    std::string::size_type sz;
//    int32_t sec_int = std::stoi (sec,&sz);
//    cout<< to_string(ts) << endl;
//    cout<< sec_int << endl;
//    cout<< nsec << endl;
//
//
//    string ts_str = "1589515347473093508";
//    int64_t ts_64 = std::stoll(ts_str);
//    cout<< ts_64 << endl;


//    vector<float> vec_f;
//    vec_f.push_back(1.1f);
//    vec_f.push_back(1.2f);
//
//    const uint8_t * bytes = reinterpret_cast<const uint8_t*>(&vec_f[0]);
//    vector<uint8_t> byteVec(bytes, bytes + sizeof(float) * vec_f.size());
//
//    cout << byteVec.size() << endl;
//
//
//    float* floatArray = reinterpret_cast<float*>(&byteVec[0]);
//    vector<float> vec_back(floatArray, floatArray + byteVec.size()/4);
//    cout << vec_back.size() << endl;
//    cout << vec_back[0] << endl;
//    cout << vec_back[1] << endl;


    // define
    Segway_proto::Points points;
    for(int i = 0;i< 1024*100;i++){
        points.add_x((float)i);
    }
    cout <<"Segway_proto::Points points size: byte " <<points.x_size() * 4<< endl;

    // serilize
    size_t imgProtoSize = points.ByteSizeLong();
    std::cout<< "points_size: "<< imgProtoSize << std::endl;
    std::shared_ptr<std::vector<uint8_t >> buffer = std::make_shared<std::vector<uint8_t>>();
    buffer->resize(imgProtoSize);

    clock_t start = clock();
    points.SerializeToArray(buffer->data(), imgProtoSize);

    // deserilize
    Segway_proto::Points points_back;
    points_back.ParseFromArray(buffer->data(), imgProtoSize);

    clock_t ends = clock();
    cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
    std::cout<< "back points_size: "<< points_back.x_size() << std::endl;




    vector<float> vec_f;
    for(int i = 0;i< 1024*100;i++){
        vec_f.push_back((float)i);
    }

    clock_t start2 = clock();
    const uint8_t * bytes = reinterpret_cast<const uint8_t*>(&vec_f[0]);
    vector<uint8_t> byteVec(bytes, bytes + sizeof(float) * vec_f.size());
    //cout << byteVec.size() << endl;
    float* floatArray = reinterpret_cast<float*>(&byteVec[0]);
    vector<float> vec_back(floatArray, floatArray + byteVec.size()/4);
    clock_t ends2 = clock();
    cout <<"Running Time : "<<(double)(ends2 - start2)/ CLOCKS_PER_SEC << endl;

    cout << vec_back.size() << endl;
    cout << vec_back[0] << endl;
    cout << vec_back[1] << endl;
}