#include "ros/ros.h"
#include "std_msgs/String.h"
#include "pcanrecv.h"
#include "pcan_h19_e.h"
#include "std_msgs/Int32.h"
#include "adcuautodriver.h"
#include "Sys_DataUploadProto_system.pb.h"

class talker_listener
{
private:

    int num;

    ros::NodeHandle nh;

    ros::Subscriber sub;

    ros::Publisher pub;
    
public:
    talker_listener()
    {
         sub = nh.subscribe("/adecu/system", 1000, &talker_listener::listenMsg, this);
        pub = nh.advertise<beginner_tutorials::adcuautodriver>("autodriver_msg", 1000);
    }

   void listenMsg(const std_msgs::ByteMultiArray::ConstPtr& msg);
};


#if  0
void talker_listener::listenMsg(const beginner_tutorials::pcanrecv::ConstPtr& msg)
{
 pcan_h19_e_auto_drive_adcu_t auto_driver_msg_st;
 beginner_tutorials::adcuautodriver auto_driver_msg_send_st;
//  phoenix::ad_data_upload::System_Display_Data_message sys_display_msg;
//  sys_display_msg.ParseFromArray()

switch (msg->id)
{
case PCAN_H19_E_AUTO_DRIVE_ADCU_FRAME_ID:
    pcan_h19_e_auto_drive_adcu_unpack(&auto_driver_msg_st,(uint8_t*)msg->data.data.data(),msg->data.data.size());
    // ROS_INFO("cnt = %d ",auto_driver_msg_st.counter);
    // ROS_INFO("crc = %d ",auto_driver_msg_st.crc8);
    // ROS_INFO("enable = %d ",auto_driver_msg_st.ad_mode_enable);
    // ROS_INFO("engage = %d ",auto_driver_msg_st.ad_mode_engage);   

    auto_driver_msg_send_st.id = PCAN_H19_E_AUTO_DRIVE_ADCU_FRAME_ID;
    auto_driver_msg_send_st.cnt = auto_driver_msg_st.counter;
    auto_driver_msg_send_st.crc8 = auto_driver_msg_st.crc8;
    auto_driver_msg_send_st.enable = auto_driver_msg_st.ad_mode_engage;
    auto_driver_msg_send_st.engage = auto_driver_msg_st.ad_mode_engage;
    pub.publish(auto_driver_msg_send_st);
    break;

default:
    break;
}
}
#endif

void talker_listener::listenMsg(const std_msgs::ByteMultiArray::ConstPtr& msg)
{

phoenix::ad_data_upload::System_Display_Data_message sys_display_msg;
// sys_display_msg.ParseFromArray(msg->data().c_str(), msg->length());
// sys_display_msg.ParseFromString(msg->data());
// std_msgs::String msg;

// std_msgs::ByteMultiArray MulByte;

// ROS_INFO("string msg: %s", msg->data.at(0));

sys_display_msg.ParseFromArray(msg->data.data(), msg->data.size());
// sys_display_msg.sys_control_info().admode()
ROS_INFO("admode:  %d", sys_display_msg.sys_control_info().admode());

// pub.publish(auto_driver_msg_send_st);
   
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker_listener");

    talker_listener tl;

    ros::spin();

    return 0;
}
