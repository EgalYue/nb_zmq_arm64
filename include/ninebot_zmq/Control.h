#ifndef NINEBOT_ZMQ_CONTROL_H
#define NINEBOT_ZMQ_CONTROL_H
namespace ninebot_algo{
    namespace nb_zmq{

        class Control{
        public:
            Control();
            
            ~Control();

            int close();

            int reconnect();

        };
    
    } // namespace: nb_zmq
} // namespace: ninebot_algo


#endif //NINEBOT_ZMQ_CONTROL_H