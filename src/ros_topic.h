#ifndef ROS_TOPIC_H
#define ROS_TOPIC_H
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
    
private:

    int argc;
    char**  argv;
    int count_var;




};








#endif // _ROS_TOPIC_H