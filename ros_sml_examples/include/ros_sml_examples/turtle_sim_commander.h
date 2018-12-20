/**
 * @file turtle_sim_commander.h
 * @author Ryan DelGizzi (ryan.delgizzi@stratom.com)
 * @date December 18, 2018
 * @brief TODO
 * @copyright Stratom, Inc.
 */

#ifndef ROS_SML_EXAMPLES_TURTLE_SIM_COMMANDER_H
#define ROS_SML_EXAMPLES_TURTLE_SIM_COMMANDER_H

#include <ros_sml_examples/sml.hpp>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <memory.h>
#include <functional>


namespace turtle_sim_commander
{
namespace sml = boost::sml;



class TurtleSimCommander
{
public:
  TurtleSimCommander(ros::NodeHandle nh);
  ~TurtleSimCommander();

  void start();
  void dummyPub();

  struct turtle_commander;

  // events

  struct stop
  {
  };

  struct draw
  {
    int edges;
    double radius;
  };

  struct done
  {
  };

  // states

  class idle;
  class drawing;

  //std::function<void()> action1;
  //constexpr auto action1 = []() { ROS_INFO("In action1"); };

private:

ros::Publisher pub;
ros::Subscriber sub;
ros::NodeHandle nh_;


public:

std::unique_ptr<sml::sm<turtle_commander>> test;

void callback(const std_msgs::Bool::ConstPtr& msg);

};
}  // namespace turtle_sim_commander

#endif  // ROS_SML_EXAMPLES_TURTLE_SIM_COMMANDER_H