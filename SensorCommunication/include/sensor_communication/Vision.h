#pragma once

#include "bupt_interfaces/msg/vision_data_array.hpp"
#include "BaseSensor.h"

class vision : public BaseSensor{
private:
    bupt_interfaces::msg::VisionDataArray msg_;   //消息内容
    rclcpp::TimerBase::SharedPtr timer_;    //定时器指针
    rclcpp::Publisher<bupt_interfaces::msg::VisionDataArray>::SharedPtr publisher_;  //话题发布者
public:
    vision(const std::shared_ptr<rclcpp::Node> _node):BaseSensor("Vision", _node)
    {
        publisher_ = this->node->create_publisher<bupt_interfaces::msg::VisionDataArray>(topic_name, 10);
    }
    void msg_pub();
    virtual void open() override;
    virtual void close() override;
};