/**
 * @file turtle_sim_commander.cpp
 * @author Ryan DelGizzi (ryan.delgizzi@stratom.com)
 * @date December 18, 2018
 * @brief TODO
 * @copyright Stratom, Inc.
 */

#include <ros_sml_examples/turtle_sim_commander.h>
#include <ros_sml_examples/turtle_sim_sm.h>
#include <turtle_actionlib/ShapeAction.h>
#include <ros_sml_examples/sml.hpp>

namespace ros_sml_examples
{
struct TurtleSimCommander::turtle_sim : public boost::sml::sm<turtle_sim_impl>
{
  explicit turtle_sim(TurtleSimCommander* tsm) : boost::sml::sm<turtle_sim_impl>(static_cast<TurtleSimCommander*>(tsm))
  {
  }
};

auto action5 = [](double i) { ROS_INFO("In action5: [%g]", i); };

TurtleSimCommander::TurtleSimCommander(ros::NodeHandle nh)
  : test_(std::make_shared<turtle_sim>(this)), nh_(nh), ac_("shape_server", true)
{
  sub = nh.subscribe("/cmd", 10, &TurtleSimCommander::cmdCallback, this);
  ROS_INFO("Waiting For Turtle Server...");

  ac_.waitForServer();
  ROS_INFO("Turtle Server Found!");
}

TurtleSimCommander::~TurtleSimCommander()
{
}

void TurtleSimCommander::start()
{
  ROS_INFO("Trying to pub bool faslse");
}

void TurtleSimCommander::startDraw(int edges, double radius)
{
  turtle_actionlib::ShapeGoal goal;
  goal.edges = edges;
  goal.radius = radius;
  ac_.sendGoal(goal, boost::bind(&TurtleSimCommander::doneCallback, this, _1, _2),
      actionlib::SimpleActionClient<turtle_actionlib::ShapeAction>::SimpleActiveCallback(),
      actionlib::SimpleActionClient<turtle_actionlib::ShapeAction>::SimpleFeedbackCallback());
}

void TurtleSimCommander::cmdCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("In Callback");
  test_->process_event(draw{ 4, 2.2 });
}

void TurtleSimCommander::doneCallback(const actionlib::SimpleClientGoalState& state,
                                      const turtle_actionlib::ShapeResultConstPtr& result)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
  ROS_INFO("interior angle: %g   apothem: %g", result->interior_angle, result->apothem);
  test_->process_event(drawComplete{});
}

void TurtleSimCommander::here()
{
  ROS_INFO("HERE HERE HERE!");
}

}  // namespace ros_sml_examples
