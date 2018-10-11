#include<ros/ros.h>
#include<actionlib/client/simple_action_client.h>
#include<auv/customAction.h>
#include <actionlib/client/terminal_state.h>

int main(int argc , char** argv){
    ros::init(argc,argv,"test_increment");

    actionlib::SimpleActionClient<auv::customAction> ac("increment",true);

    ROS_INFO("Waiting for server to start");

    ac.waitForServer();

    ROS_INFO("Server Started");

    auv::customGoal goal;
    goal.order = 50;

    ac.sendGoal(goal);

    bool finished_before_timeout = ac.waitForResult(ros::Duration(120.0));

    if(finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s",state.toString().c_str());
    }  
    else{
        ROS_INFO("Action did not finished in given duration");
    } 

    return 0;

 
}