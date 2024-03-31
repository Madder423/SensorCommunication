#include "DT_35.h"


void DT_35::DT1_process(const std::shared_ptr<can_frame> &frame)
{
    msg_.data[0] = (*(float *)frame->data);
}
void DT_35::DT2_process(const std::shared_ptr<can_frame> &frame)
{
    msg_.data[1] = *(float *)frame->data;
}
void DT_35::DT3_process(const std::shared_ptr<can_frame> &frame)
{
    msg_.data[2] = *(float *)frame->data;
}
void DT_35::msg_pub()
{
    // 发布消息
    RCLCPP_INFO(this->node->get_logger(),"DT35:%f,%f,%f",msg_.data[0],msg_.data[1],msg_.data[2]);
    //std::cout<<msg_.data[0]<<std::endl;
    publisher_->publish(msg_);
}

void DT_35::open()
{
    //std::cout<<"canID:0x023->[0],0x024->[1],0x025->[2]"<<std::endl;
    //publisher_ = this->node->create_publisher<std_msgs::msg::Float64MultiArray>(topic_name, 10);
    timer_ = this->node->create_wall_timer(std::chrono::milliseconds(100), std::bind(&DT_35::msg_pub, this));
    _can = std::make_shared<Can>(can_name);
    _can->register_msg(0x023, Can::CAN_ID_STD, std::bind(&DT_35::DT1_process, this,std::placeholders::_1));
    _can->register_msg(0x024, Can::CAN_ID_STD, std::bind(&DT_35::DT2_process, this,std::placeholders::_1));
    _can->register_msg(0x025, Can::CAN_ID_STD, std::bind(&DT_35::DT3_process, this,std::placeholders::_1));
    _can->can_start();
}
void DT_35::close()
{
    timer_.reset();
    _can.reset();
}