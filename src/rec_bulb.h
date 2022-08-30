#if !defined(REC_BULB_H)
#define REC_BULB_H

#include <QObject>
#include <atomic>
#include <thread>
#include <chrono>
#include "ros/ros.h"
#include "std_msgs/String.h"

class Rec_bulb: public QObject 
{
    Q_OBJECT;
private:
    int argc;
    int is_type;
    char**  argv;
    std_msgs::String msga;
    int get_data(std_msgs::String msga);
    ros::Subscriber sub;
public:
    Rec_bulb(QObject *parent = nullptr);
    Q_INVOKABLE void subscriber();
    void getRosInit(int _argc,char* _argv[]);
    bool init();
signals:
    void turnOff();
    void turnOn();
};






#endif // REC_BULB_H
