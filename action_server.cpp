#include<ros/ros.h>
#include<actionlib/server/simple_action_server.h>
#include<auv/customAction.h>

class Actionserver{
    protected:
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<auv::customAction> as;

    std::string action_name;
    auv::customFeedback feedback;
    auv::customResult result;

    public:
      Actionserver(std::string name):
      as(nh,name,boost::bind(&Actionserver::executeCB,this,_1),false),action_name(name){
          as.start();
      }

    ~Actionserver(void){
    }

    void executeCB(const auv::customGoalConstPtr &goal){
        ros::Rate r(1);
        bool success = true;
        
        int x = goal->order;
         
        feedback.sequence.clear();
        feedback.sequence.push_back(x);

        ROS_INFO("%s: Executing, creating increment sequence of order %i with seeds %i",action_name.c_str(), goal->order, feedback.sequence[0]);
  
        for(int i=1;i<=100;i++){
        
            if(as.isPreemptRequested() || !ros::ok()){
                 ROS_INFO("%s: Preempted", action_name.c_str());
                 as.setPreempted();
                 success = false;
                 break;
            }
        
            feedback.sequence.push_back(i+x);
            as.publishFeedback(feedback);
    
            r.sleep();

        }
        if(success){
            result.sequence = feedback.sequence;
            ROS_INFO("%s: Succeeded", action_name.c_str());
            as.setSucceeded(result);
        }

    }
};    
int main(int argc,char** argv){
    ros::init(argc,argv,"increment");
    Actionserver action("increment");
    ros::spin();

    return 0;
}

