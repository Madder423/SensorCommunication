#include "sensor_node.h"
#include "DT_35.h"
#include "Vision.h"

int main(int argc,char **argv)
{
    rclcpp::init(argc, argv);
    std::cout<<"test"<<std::endl;
    auto node = std::make_shared<sensor_node>("OtherSensors");
    node->add_publisher(std::make_shared<DT_35>(node,"can0"));
    node->add_publisher(std::make_shared<vision>(node));
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}