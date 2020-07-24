cmake_minimum_required(VERSION 3.6)
project(ninebot_zmq)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

# ninebot_zmq
include_directories(/home/linaro/nb_zmq_arm64/include) #TODO...
link_libraries(/home/linaro/nb_zmq_arm64/lib/arm64_v8a/libninebot_log.so) # TODO...
link_libraries(/home/linaro/nb_zmq_arm64/lib/arm64_v8a/libninebot_zmq.so)
link_libraries(/home/linaro/nb_zmq_arm64/lib/arm64_v8a/libprotobuf.a)
link_libraries(/home/linaro/nb_zmq_arm64/lib/arm64_v8a/libzmq.a)



add_executable(zmqPub test/zmqPubMain.cpp )
add_executable(zmqSub test/zmqSubMain.cpp )
add_executable(zmqRepServer test/zmqRepServerMain.cpp )
add_executable(zmqReqClient test/zmqReqClientMain.cpp )
add_executable(zmqSubAllThreadMain test/zmqSubAllThreadMain.cpp)
add_executable(stress_testing test/stress_testing.cpp)

add_executable(zmqSubPub test/zmqSubPubMain.cpp)
add_executable(zmqPubSub test/zmqPubSubMain.cpp)

# add_executable(zmqSub test/zmqSubMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqSub ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqPub test/zmqPubMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqPub ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqSub test/zmqSubMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqSub ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqRepServer test/zmqRepServerMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqRepServer ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqReqClient test/zmqReqClientMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqReqClient ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqSubPub test/zmqSubPubMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqSubPub ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqPubSub test/zmqPubSubMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqPubSub ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqSubAll test/zmqSubAllMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqSubAll ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqPubAll test/zmqPubAllMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqPubAll ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqPubSubAll test/zmqPubSubAllMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqPubSubAll ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqSubPubAll test/zmqSubPubAllMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqSubPubAll ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqRepServerAll test/zmqRepServerAllMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqRepServerAll ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqReqClientAll test/zmqReqClientAllMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqReqClientAll ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqPubAllAsSeq test/zmqPubAllAsSeq.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqPubAllAsSeq ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqSubAllAsSeq test/zmqSubAllAsSeq.cpp  ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqSubAllAsSeq ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqSubAllThreadMain test/zmqSubAllThreadMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqSubAllThreadMain ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqAndroidCtrl test/zmqAndroidCtrlMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqAndroidCtrl ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})

# add_executable(zmqLinuxCtrl test/zmqLinuxCtrlMain.cpp ${SRC_CPP} ${PROTO_SRCS})
# target_link_libraries(zmqLinuxCtrl ${ZMQ_LIBRARIES} ${PROTOBUF_LIBRARIES} ${OpenCV_LIBS})