#ifndef ROS_TOPIC_H
#define ROS_TOPIC_H
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <QObject>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

class Ros_topic : public QObject 
{
    Q_OBJECT;

public:
    explicit Ros_topic(QObject *parent = nullptr);
    Q_INVOKABLE void get_count(int _count);
    void getRosInit(int _argc,char* _argv[]);
    bool init();
     void run( );
    Q_INVOKABLE void update_thread() ;
    
private:

    int argc;
    char**  argv;
    int count_var;
    int changingcount;
    ros::Publisher my_publisher,chatter_publisher;
    std::thread update_threada;
    bool first_time=true;
    std::atomic<bool> program_is_running{ true } ;

};

#endif // _ROS_TOPIC_H