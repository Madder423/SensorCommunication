#pragma once
#include<iostream>
#include "bupt_can/bupt_can.h"
#include "rclcpp/rclcpp.hpp"

class BaseSensor{
protected:
    std::string topic_name;  //话题名称类型
    std::shared_ptr<rclcpp::Node> node; //调用者指针
    BaseSensor(std::string _topic_name,std::shared_ptr<rclcpp::Node> _node):topic_name(_topic_name),node(_node){};
    ~BaseSensor(){};
public:
    virtual void open() = 0;        //打开
    virtual void close() = 0;       //关闭
    std::string get_name(){return this->topic_name;}
};
