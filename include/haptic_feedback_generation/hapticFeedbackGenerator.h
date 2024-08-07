#ifndef FEEDBACKGENERATOR_H
#define FEEDBACKGENERATOR_H

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <std_msgs/msg/multi_array_dimension.hpp>
#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/u_int16.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/bool.hpp>

#include <kacanopen/ros_bridge/bridge.h>
#include <kacanopen/core/logger.h>
#include <kacanopen/ros_bridge/entry_publisher.h>
#include <kacanopen/ros_bridge/entry_subscriber.h>

#include <thread>
#include <chrono>
#include <memory>
#include <string>

#include <iostream>
#include <vector>
#include <algorithm>

#include <brunner_can_interface/brunner_interpreter.h>
#include <haptic_station_msgs/msg/force_profile.hpp>
#include <haptic_station_msgs/msg/haptic_joy.hpp>
#include <haptic_station_msgs/msg/data_joy.hpp>
#include <haptic_station_msgs/msg/settings_joy.hpp>
#include <haptic_station_msgs/msg/settings_joysticks.hpp>
#include <haptic_station_msgs/msg/haptic_joysticks.hpp>

class HapticFeedbackGenerator : public rclcpp::Node
{
public:
  HapticFeedbackGenerator(std::string name);

  ~HapticFeedbackGenerator(void);

private:

  /** Callbacks */
  void distance_callback(const std_msgs::msg::Int32MultiArray msg);

  /** Callback groups */
  rclcpp::CallbackGroup::SharedPtr sub_cbg_;
  rclcpp::CallbackGroup::SharedPtr pub_cbg_;

  /** Timer **/
  // rclcpp::TimerBase::SharedPtr publish_timer_;

  /** Subscribers */
  rclcpp::SubscriptionOptions sub_options_;
  rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr hammer_distance_sub_;

  /** Publishers */
  rclcpp::Publisher<haptic_station_msgs::msg::ForceProfile>::SharedPtr force_profile_pub_;
  

protected:

  double publish_period_;

};

#endif
