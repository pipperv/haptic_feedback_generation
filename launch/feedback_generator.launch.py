from ament_index_python import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

  node = Node(package='haptic_feedback_generation',
              executable='FeedbackGenerator',
              name='feedback_generator',
              output='screen',
              namespace='/JOYSTICK',
              )

  ld = LaunchDescription()
  ld.add_action(node)

  return ld