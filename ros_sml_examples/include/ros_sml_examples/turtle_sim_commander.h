/**
 * @file turtle_sim_commander.h
 * @author Ryan DelGizzi (ryan.delgizzi@stratom.com)
 * @date December 18, 2018
 * @brief TODO
 * @copyright Stratom, Inc.
 */

#ifndef ROS_SML_EXAMPLES_TURTLE_SIM_COMMANDER_H
#define ROS_SML_EXAMPLES_TURTLE_SIM_COMMANDER_H

#include <functional>
#include <memory>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <turtle_actionlib/ShapeAction.h>
#include <actionlib/client/simple_action_client.h>

namespace ros_sml_examples
{

class TurtleSimCommander
{
public:
  TurtleSimCommander(ros::NodeHandle nh);
  ~TurtleSimCommander();

  void start();
  void here();
  void startDraw(int edges, double radius);

private:
  ros::Publisher pub;
  ros::Subscriber sub;
  ros::NodeHandle nh_;

  actionlib::SimpleActionClient<turtle_actionlib::ShapeAction> ac_;

public:
  struct turtle_sim;
  std::shared_ptr<turtle_sim> test_;




  void cmdCallback(const std_msgs::String::ConstPtr& msg);
  void doneCallback(const actionlib::SimpleClientGoalState& state,
                    const turtle_actionlib::ShapeResultConstPtr& result);
};
}  // namespace ros_sml_examples

#endif  // ROS_SML_EXAMPLES_TURTLE_SIM_COMMANDER_H