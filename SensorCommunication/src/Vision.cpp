#include "Vision.h"

void vision::msg_pub()
{
    // 发布消息
    //TODO:以任意方式在msg_中放入内容
    publisher_->publish(msg_);
}

void vision::open()
{
    //std::cout<<"canID:0x023->[0],0x024->[1],0x025->[2]"<<std::endl;
    //publisher_ = this->node->create_publisher<std_msgs::msg::Float64MultiArray>(topic_name, 10);
    //TODO:设置发布周期
    timer_ = this->node->create_wall_timer(std::chrono::milliseconds(100), std::bind(&vision::msg_pub, this));
    //TODO:可能的打开操作，如果做不到就拉到
}
void vision::close()
{
    timer_.reset();
    //TODO:可能的关闭操作，如果做不到就拉到
}