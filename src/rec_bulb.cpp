#include "rec_bulb.h"

using namespace  std;
       
//  int argc;
//  char**  argv;
// std_msgs::String& msga;
int is_type;

Rec_bulb::Rec_bulb(QObject *parent) : QObject(parent)
 {

 }
int get_data(std_msgs::String::ConstPtr& msga)
{
    
    return stoi(msga->data);
}

void subscribe()
{
while(true){
    if(is_type % 2 == 0)//is even emit on else emit off
   {
        // emit turnOn();
        cout<<"even "<< is_type<<endl;
        break;
   }
   else
   {
        // emit turnOff();
        cout<<"odd "<<is_type<<endl;
        break;

   }
}
}

void Rec_bulb::subscriber()
 {

    std::thread update_threada(subscribe);
	update_threada.join();
   
	
}

void Rec_bulb::getRosInit(int _argc,char* _argv[])
{
     argc=_argc;
     argv=_argv;
     Rec_bulb::init();
}

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());
    // get_data(msg);
    // msga=msg;
    int counnt=stoi(msg->data.c_str());
    cout<<"counting recieved:= " <<counnt<<endl;
    is_type=counnt;
    subscribe();
    
}

bool Rec_bulb::init()
  {
    ros::init(argc,argv,"Bulb_node_sub");
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
		// chatter_publisher = n.advertise<std_msgs::String>("status_count", 1000);
		sub = n.subscribe("status_count", 1000, chatterCallback);
        std_msgs::String msg;
		// std::stringstream ss;
		// ss  << count_var;
		// msg.data = ss.str();
		// chatter_publisher.publish(msg);
		ros::spinOnce();

		return true;
  }









 




 