# ninebot ros zmq

### Zmq communication  
zmq_pub -> zmq_recv  

### Ros communication  
ros_pub -> ros_recv  

### zmq + ros communication
1. zmq_pub -> zmq_ros_forwarder -> ros_sub  

2. ros_pub -> ros_zmq_forwarder -> zmq_recv




-----------------------------------------------------------  


## Publish-Subscrib Mode

zmqPub tcp://127.0.0.1:8888 /home/yuehu/Desktop/zmq_test_data/fisheye  

zmqSub tcp://127.0.0.1:8888  


## Request-Reply Mode

zmqReqServer tcp://127.0.0.1:5555

zmqReqClient tcp://127.0.0.1:5555  


## 开发笔记:
### 注意事项:
1. common.h 里面需要添加端口, 新的数据类型需要新的端口.   

### TODO list:  
1. 测试不同topic的频率.  
2. 模板
3. req/rep 模型的返回值, rc等问题优化
4. req/rep 重链



## Cross-Compile Google Protobuf And ZMQ For Android JNI
### 1. Cross-Compile Google Protobuf For Android JNI  
Environment:  
NDK: smb://algo@10.10.81.27/share/unix_dev_tools/  
SDK: smb://algo@10.10.81.27/share/unix_dev_tools/
Protobuf: v3.2.0  

参考: https://tech.pic-collage.com/how-to-cross-compile-google-protobuf-lite-for-android-977df3b7f20c  

直接编译 protobuf 即可, protoc可以注释调, protobuf-lite不适合vision_algo. 
 

complie_protobuf_andriod.sh 内参数需要调整.  


### 2. Cross-Compile ZMQ For Android JNI
参考官方: https://github.com/zeromq/libzmq/tree/master/builds/android  

NDK-16r 编译不通过, 直接使用 NDK-21 编译后, 也可以在vision_algo使用.