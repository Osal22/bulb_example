#include "ros_topic.h"
#include <iostream>
#include <QDebug>

using namespace  std;

Ros_topic obj_rostopic;
       
 int argc;
 char**  argv;
 std::mutex m;
 bool turnflag=false;

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
	ros::Rate loop_rate(100);
	while ( ros::ok() ) {

		std_msgs::String msg;
		std::stringstream ss;
		ss  << count_var;
		msg.data = ss.str();
		// ros::init(argc,argv,"Bulb_node");
		// ros::start(); // explicitly needed since our nodehandle is going out of scope.
		// ros::NodeHandle n;
		// ros::Publisher chatter_publisher;
		// chatter_publisher = n.advertise<std_msgs::String>("status_count", 1000);
		// chatter_publisher.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
		
}
void f()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int hello(int &count,int *res)
{
		std_msgs::String msg;
		std::stringstream ss;
		ss  << count;
		msg.data = ss.str();
	    ros::init(argc,argv,"Bulb_node");
		ros::start(); // explicitly needed since our nodehandle is going out of scope.
		ros::NodeHandle n;
		ros::Publisher chatter_publisher;
		chatter_publisher = n.advertise<std_msgs::String>("status_count", 1000);
		
	count=10;
	while(true && turnflag)
	{
	f();
	count++;
	string m="";
	std::stringstream().swap(ss);
	msg.data.clear();
	ss  << count;
	msg.data = ss.str();
	
	ros::spinOnce();
	// std::cout<<"count:= "<<count<<" ss:= "<<ss.str()<<" msg.data:=  "<<msg.data <<std::endl;
	if(count>=50){
		count=0;
		std::stringstream().swap(ss);
		ss<<"value is fity now do somthing else";
		msg.data = ss.str();
	}
	chatter_publisher.publish(msg);
	// update(count);
	// std::terminate();
	res=&count;
	obj_rostopic.get_count_after(count);
	msg.data.clear();
	ss.clear();
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
	int *_res;
	std::thread update_threada(hello,std::ref(changingcount),std::ref(_res));
	first_time=true;
	update_threada.detach();
	}
	changingcount++;
	
}

int Ros_topic::get_count_after(int _count){
	std::cout<<"i am function calling:= "<<_count<<endl;
	string count_str=std::to_string(_count);
	emit after_count_sig(count_str);
	return _count;

}

bool Ros_topic::turn_on_tread(){
	turnflag=true;
	return true;
}

bool Ros_topic::turn_off_tread(){
	turnflag=false;
	return true;
}