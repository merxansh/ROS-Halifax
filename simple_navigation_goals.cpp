#include <ros/ros.h>
//move_base action accepts goals from clients and attempts to move the robot to the specified position/orientation in the world
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//Allow us to communicate with actions that adhere to the MoveBaseAction action interface.
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
MoveBaseClient;

int main(int argc, char** argv)
{

	ros::init(argc, argv, "simple_navigation_goals");

	//INitializa array for x and y coordinates
	double a[4]={1.4,1.4,0.3,0.3};
	double b[4]={0.3,1.4,1.4,0.3};

	//INitializa for loop  with a counter i
	for(int i=0; i<4;i++)
	{
		//tell the action client that we want to spin a thread by default
		MoveBaseClient ac("move_base", true);

		//wait for the action server to come up to begin processing goals
		while(!ac.waitForServer(ros::Duration(5.0))){
			ROS_INFO("Waiting for the move_base action server to come up");
		}
		move_base_msgs::MoveBaseGoal goal;

		//we'll send a goal to the robot to move 1.1 meter forward
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();

		// Counterclockwise through space
		//Calling a and b arrays to correspond with x and y coordinates with respect to counter i
		goal.target_pose.pose.position.x = a[i];
		goal.target_pose.pose.position.y = b[i];
		goal.target_pose.pose.orientation.w = 1;


		ROS_INFO("Sending goal");
		ac.sendGoal(goal);

		ac.waitForResult();

		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
			ROS_INFO("Hooray, the base moved 1.1 meter forward");
		} else {
			ROS_INFO("The base failed to move forward 1.1 meter for some reason");
		}

	return 0;
}
