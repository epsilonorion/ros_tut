#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <action_tut/ExampleAction.h>

//using namespace actionlib_tutorials;
typedef actionlib::SimpleActionClient<action_tut::ExampleAction> Client;

// Called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state,
            const action_tut::ExampleResultConstPtr& result)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
  ROS_INFO("Answer: %i", result->sequence.back());
  ros::shutdown();
}

// Called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goal
void feedbackCb(const action_tut::ExampleFeedbackConstPtr& feedback)
{
  ROS_INFO("Got Feedback of length %lu", feedback->sequence.size());

  ROS_INFO("Values are:");

  for (int i = 0; i < feedback->sequence.size(); i++) {
    ROS_INFO("%i", feedback->sequence[i]); 
  }
}

int main (int argc, char **argv)
{
  ros::init(argc, argv, "example_client");

  // Create the action client
  Client ac("example_server", true);

  ROS_INFO("Waiting for action server to start.");
  ac.waitForServer();
  ROS_INFO("Action server started, sending goal.");

  // Send Goal
  action_tut::ExampleGoal goal;
  goal.order = 20;
  ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

  ros::spin();
  return 0;
}
