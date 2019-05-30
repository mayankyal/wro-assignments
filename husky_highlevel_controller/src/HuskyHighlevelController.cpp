#include "husky_highlevel_controller/HuskyHighlevelController.hpp"

#include<string>
#include <iostream>
#include <array>
#include <algorithm> 
using namespace std; 


namespace husky_highlevel_controller {

int queueSize_;  

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle)
{
  
  if(!readParameters()){
    ROS_ERROR("could not read parameters.");
    ros::requestShutdown();
  }
  
  scanSubscriber_ = nodeHandle_.subscribe(scanTopic_,1,
                                          &HuskyHighlevelController::topicCallback,this);
    ROS_INFO("SUUCCESFULLY LAUNCHED NODE");
}

HuskyHighlevelController::~HuskyHighlevelController()
{
}

bool HuskyHighlevelController::readParameters()
{
  if(!nodeHandle_.getParam("topic_name", scanTopic_))return false;
  if(!nodeHandle_.getParam("queue_size",queueSize_))return false;
  return true;
}

void HuskyHighlevelController::topicCallback(const sensor_msgs::LaserScan::ConstPtr& message)
{
  int a=message->ranges.size();
   
  float minValue;
  for(int i=0;i<a;i++)
  {
    if(i==0)
    minValue=message->ranges[i];
    if((message->ranges)[i]<minValue)
    {
      minValue=(message->ranges)[i];
    }
  }
  ROS_INFO("smallest distance(m)=%f", minValue); 
}

} /* namespace */

