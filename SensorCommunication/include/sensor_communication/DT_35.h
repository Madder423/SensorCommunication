#pragma once

#include "bupt_interfaces/msg/double_array.hpp"
#include "BaseSensor.h"

class DT_35 : public BaseSensor{
private:
    std::shared_ptr<Can> _can; //can智能指针
    std::string can_name;      //can端口名
    bupt_interfaces::msg::DoubleArray msg_;   //消息内容
    rclcpp::TimerBase::SharedPtr timer_;    //定时器指针
    rclcpp::Publisher<bupt_interfaces::msg::DoubleArray>::SharedPtr publisher_;  //话题发布者
public:
    DT_35(const std::shared_ptr<rclcpp::Node> _node, std::string _can_name):BaseSensor("DT_35", _node),can_name(_can_name)
    {
        for(size_t i;i<3;++i){msg_.data.push_back(0.0);}
        std::cout<<"canID:0x023->[0],0x024->[1],0x025->[2]"<<std::endl;
        publisher_ = this->node->create_publisher<bupt_interfaces::msg::DoubleArray>(topic_name, 10);
    }
    void DT1_process(const std::shared_ptr<can_frame> &frame);
    void DT2_process(const std::shared_ptr<can_frame> &frame);
    void DT3_process(const std::shared_ptr<can_frame> &frame);
    void msg_pub();
    virtual void open() override;
    virtual void close() override;
};