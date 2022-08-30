import  QtQuick 2.12
import  QtQuick.Controls 1.0
import  Ros_topic 1.0
import  Rec_bulb 1.0
import  QtQuick.Window 2.12



ApplicationWindow{
    id:root 
    width:200
    height:250
    visible:true
    minimumHeight: height
    minimumWidth: width
    maximumHeight:height
    maximumWidth:width

    

    Ros_topic{
        id:ros_topic
        onAfter_count_sig:{
            console.log(_count)
        }
    }
    Rec_bulb{
        id:rec_bulb
        
        onTurnOff:{
            toggle_off()
        }
        onTurnOn:{
            toggle_on()
        
        }
        // delay(1,subscriber())

    }
    property int count:0
    property string status_toggle:""
    function track_count(){
        if(count>=50)
        {
            count=0
        }
        
    }
    function toggle_on(){
        if(!off_image.visible)
        {
            off_image.visible=true
            
        }
        else
        {
            off_image.visible=false
        }
    }

    function toggle_off(){

        if(!on_image.visible)
        {
            on_image.visible=true
            count++;
            status_toggle="on"
            ros_topic.get_count(count);
            ros_topic.update_thread();
            // rec_bulb.subscriber();
            ros_topic.turn_on_tread()
        }
        else
        {
            on_image.visible=false
            status_toggle="off"
            ros_topic.turn_off_tread()
        }
    }
     Timer {
        id: timer
    }

    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = true;
        timer.triggered.connect(cb);
        timer.start();
    }


    Image{
        
        source:"/images/off.jpeg"
        id:off_image 
        width:200
        height:200
        visible:true
    }
    Image{
        source:"/images/on.jpeg"
        id:on_image 
        width:200
        height:200
        visible:false
    }
    MouseArea{
        id:main_btn
        anchors.top:parent.top
        anchors.left:parent.left
        width:200
        height:200
        
        onClicked:{
            track_count();
            toggle_on();
            toggle_off();
            
        }
        onEntered:{
        // off_image.visible=false
        // on_image.visible=true
        }
        onExited:{
        // off_image.visible=true
        // on_image.visible=false
        }


    }
    Text{
        id:count_text
        anchors.top:main_btn.bottom
        anchors.left:parent.left
        anchors.leftMargin:10
        text:count
    }
    Text{
        id:status_txt
        anchors.top:main_btn.bottom
        anchors.left:count_text.right
        anchors.leftMargin:10
        text:status_toggle
    }

}