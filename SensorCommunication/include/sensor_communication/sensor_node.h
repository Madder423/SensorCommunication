#pragma once
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include "BaseSensor.h"
#include "bupt_interfaces/srv/control_state.hpp"
#include <vector>
#include <algorithm>

class sensor_node : public rclcpp::Node {
public:
    sensor_node(std::string name) : Node(name) {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
        // 创建服务
        control_srv =
        this->create_service<bupt_interfaces::srv::ControlState>(
        "ControlState",
        std::bind(&sensor_node::handle_ControlState, this,
                  std::placeholders::_1, std::placeholders::_2));
  }
    void add_publisher(std::shared_ptr<BaseSensor> _senser){this->sensors.push_back(_senser);}//增加传感器
private:
    rclcpp::Service<bupt_interfaces::srv::ControlState>::SharedPtr control_srv;   //声明服务
    // ros2 service call /ControlState bupt_interfaces/srv/ControlState "{sensor_name: DT_35, open: 1}"
    std::vector<std::shared_ptr<BaseSensor>> sensors;
    void handle_ControlState(
        const std::shared_ptr<bupt_interfaces::srv::ControlState::Request> request,
        std::shared_ptr<bupt_interfaces::srv::ControlState::Response> respense){
        RCLCPP_INFO(this->get_logger(),"收到请求");
        auto sensor = find_if(this->sensors.begin(),this->sensors.end(),[&request](std::shared_ptr<BaseSensor> &sensor)
        {
            return sensor->get_name()==request->sensor_name;
        });
        if(sensor==sensors.end()){
            std::cout<<"没有这个传感器"<<std::endl;
            respense->message = "没有这个传感器";
        }
        else
        {
            if(request->open){
                (*sensor)->open();
            }
            else{
                (*sensor)->close();
            }
        }
    }
};
