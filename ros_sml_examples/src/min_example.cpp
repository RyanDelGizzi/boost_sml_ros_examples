/**
 * @file min_example.cpp
 * @author Ryan DelGizzi (ryan.delgizzi@stratom.com)
 * @date December 18, 2018
 * @brief TODO
 * @copyright Stratom, Inc.
 */

#include <ros_sml_examples/turtle_sim_commander.h>

#include <ros/ros.h>
#include <ros_sml_examples/sml.hpp>
#include <std_msgs/Bool.h>


namespace sml = boost::sml;


// events
struct release
{
};
struct ack
{
};
struct fin
{
};
struct timeout
{
};

// guards
const auto is_ack_valid = [](const ack&) { return true; };
const auto is_fin_valid = [](const fin&) { return true; };

// actions
const auto send_fin = [] { ROS_INFO("send_fin"); };
const auto send_ack = [] {};

class established;
class fin_wait_1;
class fin_wait_2;
class timed_wait;

//------------------


// events



int main(int argc, char** argv)
{
  using namespace sml;
  using namespace turtle_sim_commander;

  ros::init(argc, argv, "agvr_core_node");
  ros::NodeHandle nh;

  TurtleSimCommander turtle_sim_commander(nh);

  turtle_sim_commander.start();

  ros::Duration(2).sleep();

  ros::Duration(2).sleep();
  

  ros::spin();
  /*
    sm<hello_world> sm;
    assert(sm.is(state<established>));

    sm.process_event(release{});
    assert(sm.is(state<fin_wait_1>));

    sm.process_event(ack{});
    assert(sm.is(state<fin_wait_2>));

    sm.process_event(fin{});
    assert(sm.is(state<timed_wait>));

    sm.process_event(timeout{});
    assert(sm.is(X));  // released
    */
}
