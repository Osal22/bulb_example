#include "ros_topic.h"
#include <iostream>
#include <QDebug>

using namespace  std;
       
 int argc;
 char**  argv;

 Ros_topic:: Ros_topic(QObject *parent) : QObject(parent)
 {

 }

 void Ros_topic::get_count(int _count)
 {
       ros::start(); 
       count_var=_count;
       std_msgs::String msg;
       std::stringstream ss;
       ss<< count_var;
       msg.data = ss.str();
 }

 void Ros_topic::getRosInit(int _argc,char* _argv[])
 {
        argc=_argc;
        argv=_argv;
		Ros_topic::init();
      
 }

  bool Ros_topic::init()
  {
    ros::init(argc,argv,"Bulb_node");
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
		chatter_publisher = n.advertise<std_msgs::String>("status_count", 1000);
		std_msgs::String msg;
		std::stringstream ss;
		ss  << count_var;
		msg.data = ss.str();
		chatter_publisher.publish(msg);
		ros::spinOnce();

		return true;
  }

 void Ros_topic::run()
{
  ros::Rate loop_rate(1);
	while ( ros::ok() ) {

		std_msgs::String msg;
		std::stringstream ss;
		ss  << "count_var";
		msg.data = ss.str();
		chatter_publisher.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	}
	
}


void update(int count_var)
{
	std::cout<<count_var<<std::endl;
	ros::Rate loop_rate(0.001);
	while ( ros::ok() ) {

		std_msgs::String msg;
		std::stringstream ss;
		ss  << count_var;
		msg.data = ss.str();
		ros::init(argc,argv,"Bulb_node");
		ros::start(); // explicitly needed since our nodehandle is going out of scope.
		ros::NodeHandle n;
		ros::Publisher chatter_publisher;
		chatter_publisher = n.advertise<std_msgs::String>("status_count", 1000);
		chatter_publisher.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
		
}
void hello(int &count)
{
	
	while(true)
	{
	std::cout<<"count:= "<<count<<std::endl;
	update(count);
	// std::terminate();
	}
	std::cout<<"stopped"<<count<<std::endl;
}

void Ros_topic::update_thread()
{
	
	if(count_var>=50){
		program_is_running=false;
	}
	first_time=false;
	if(!first_time)
	{
	std::thread update_threada(hello,std::ref(changingcount));
	first_time=true;
	update_threada.detach();
	}
	changingcount++;
	

	
	
	
	
	
	
}
