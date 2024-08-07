#include <haptic_feedback_generation/hapticFeedbackGenerator.h>

HapticFeedbackGenerator::HapticFeedbackGenerator(std::string name) : Node(name) {

    /************
     Subscribers
    ************/

    hammer_distance_sub_ = this->create_subscription<std_msgs::msg::Int32MultiArray>("hammer_distance_topic", 10,
                          std::bind(&HapticFeedbackGenerator::distance_callback, this, std::placeholders::_1), sub_options_);

    /************
     Publishers
    ************/

    force_profile_pub_ = this->create_publisher<haptic_station_msgs::msg::ForceProfile>("force_profile_topic", 1);

}

HapticFeedbackGenerator::~HapticFeedbackGenerator(void) {
    return;
}

void HapticFeedbackGenerator::distance_callback(const std_msgs::msg::Int32MultiArray msg) {
    
}