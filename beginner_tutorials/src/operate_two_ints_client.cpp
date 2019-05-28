#include "ros/ros.h"
#include "beginner_tutorials/OperationOnTwoInts.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "operate_two_ints_client");
  if (argc != 4)
  {
    ROS_INFO("usage: operates_two_ints_client X Y OPERATION");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<beginner_tutorials::OperationOnTwoInts>("operate_two_ints");
  beginner_tutorials::OperationOnTwoInts srv;
  srv.request.a = atoll(argv[1]);
  srv.request.b = atoll(argv[2]);
  srv.request.operation = argv[3];
  if (client.call(srv))
  {
    ROS_INFO("Value: %f", srv.response.value);
  }
  else
  {
    ROS_ERROR("Failed to call service operate_two_ints");
    return 1;
  }

  return 0;
}
