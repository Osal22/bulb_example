import  QtQuick 2.12
import  QtQuick.Controls 1.0
import  Ros_topic 1.0


ApplicationWindow{
    id:root 
    width:200
    height:200
    visible:true
    minimumHeight: height
    minimumWidth: width
    // maximunHeight:height
    // maximunWidth:width
    Ros_topic{
        id:ros_topic
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
        }
        else
        {
            on_image.visible=false
            status_toggle="off"
        }
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
        anchors.fill:parent
        width:parent.width
        height:parent.height
        
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
        anchors.top:parent.top
        anchors.left:parent.left
        anchors.leftMargin:10
        text:count
    }
    Text{
        id:status_txt
        anchors.top:parent.top
        anchors.left:count_text.right
        anchors.leftMargin:10
        text:status_toggle

    }

}