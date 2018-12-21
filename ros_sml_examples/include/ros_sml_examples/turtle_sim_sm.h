/**
 * @file turtle_sim_sm.h
 * @author Ryan DelGizzi (ryan.delgizzi@stratom.com)
 * @date December 20, 2018
 * @brief TODO
 * @copyright Stratom, Inc.
 */

#ifndef ROS_SML_EXAMPLES_TURTLE_SIM_SM_H
#define ROS_SML_EXAMPLES_TURTLE_SIM_SM_H

#include <ros/ros.h>

#include <ros_sml_examples/turtle_sim_commander.h>
#include <ros_sml_examples/sml.hpp>

namespace ros_sml_examples
{
namespace sml = boost::sml;

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

struct drawComplete
{
};

class idle;
class drawing;

auto action1 = [](TurtleSimCommander* tsm) { tsm->here(); };

auto enterIdleState = []() { ROS_INFO("Entering Idle State"); };

auto doDraw = [](TurtleSimCommander* tsm, draw event) {
  ROS_INFO("Sending Command to ActionServer to Do Draw [%d] [%g]", event.edges, event.radius);
  tsm->startDraw(event.edges, event.radius);
};
struct turtle_sim_impl
{
  auto operator()() const
  {
    using namespace sml;

    // clang-format off
    return make_transition_table(
      *state<idle>    + sml::on_entry<_>    /   enterIdleState, 
      state<idle>     + event<draw>         /   doDraw              =   state<drawing>,
      state<drawing>  + event<drawComplete> /   enterIdleState      =   state<idle>
    );
    // clang-format on
  }
};

}  // namespace ros_sml_examples

#endif  // ROS_SML_EXAMPLES_TURTLE_SIM_SM_H