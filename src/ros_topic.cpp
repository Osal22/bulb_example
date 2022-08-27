#include "ros_topic.h"
#include <QDebug>


 Ros_topic:: Ros_topic(QObject *parent) : QObject(parent)
 {

 }

 void Ros_topic::get_count(int _count)
 {

        count_var=_count;
        qDebug()<<count_var;
        ros::NodeHandle n;
        ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
        std_msgs::String msg;

    std::stringstream ss;
    ss<< count_var;
    msg.data = ss.str();
    chatter_pub.publish(msg);
     ros::spinOnce();
        
         

 }

 void Ros_topic::getRosInit(int _argc,char* _argv[])
 {
        argc=_argc;
        argv=_argv;
        ros::init(argc, argv, "talker");
        
 
 }