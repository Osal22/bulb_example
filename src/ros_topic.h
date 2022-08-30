#ifndef ROS_TOPIC_H
#define ROS_TOPIC_H
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <QObject>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <sstream>
#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"


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
    // void hello(int &count);
    Q_INVOKABLE int get_count_after(int _count);
    Q_INVOKABLE bool turn_on_tread();
    Q_INVOKABLE bool turn_off_tread();
    
private:

    int argc;
    char**  argv;
    int count_var;
    int changingcount;
    ros::Publisher my_publisher,chatter_publisher;
    std::thread update_threada;
    bool first_time=true;
    std::atomic<bool> program_is_running{ true } ;
    int after_count;
    std::mutex m;
    bool turn_flag=false;
signals:
    void toggle();
    void after_count_sig(std::string _count);

};

#endif // _ROS_TOPIC_H