/**
 * @file turtle_sim_commander.cpp
 * @author Ryan DelGizzi (ryan.delgizzi@stratom.com)
 * @date December 18, 2018
 * @brief TODO
 * @copyright Stratom, Inc.
 */

#include <ros_sml_examples/turtle_sim_commander.h>

namespace turtle_sim_commander
{
auto action1 = []() { ROS_INFO("In action1"); };

struct turtle_commander
{
  auto operator()() const
  {
    using namespace sml;
 
    // clang-format off
    return make_transition_table(
      *state<TurtleSimCommander::idle> + event<TurtleSimCommander::draw> / ([]{std::cout << "action to draw" << std::endl;},action1) = state<TurtleSimCommander::drawing>,
       state<TurtleSimCommander::idle> + sml::on_entry<_> / [] { std::cout << "Entering Idle State" << std::endl;} 
    );
    // clang-format on
  }
};

TurtleSimCommander::TurtleSimCommander(ros::NodeHandle nh) : nh_(nh), test{std::make_unique<sml::sm<turtle_commander>>()}
{
  pub = nh.advertise<std_msgs::Bool>("/bool", 1);
  sub = nh.subscribe("/bool", 10, &TurtleSimCommander::callback, this);
}

TurtleSimCommander::~TurtleSimCommander()
{
}

void TurtleSimCommander::start()
{
  std_msgs::Bool msg;
  pub.publish(msg);
}

void TurtleSimCommander::dummyPub()
{
  std_msgs::Bool msg;
  msg.data = true;
  pub.publish(msg);
}

void TurtleSimCommander::callback(const std_msgs::Bool::ConstPtr& msg)
{
  ROS_INFO("In Callback");
  test->process_event(draw{});
}

}  // namespace turtle_sim_commander
