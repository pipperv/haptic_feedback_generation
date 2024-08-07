#include <haptic_feedback_generation/hapticFeedbackGenerator.h>

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(),2);
  auto node = std::make_shared<HapticFeedbackGenerator>("haptic_feedback_generator");
  executor.add_node(node);
  PRINT("Node Added");
  executor.spin();
  PRINT("Afterspin");
  return 0;
}
