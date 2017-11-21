#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>
#include<ros/console.h>
#include<sstream>
#include<cstdlib>
#include<string>
#include"std_msgs/String.h"
#include"Roomba.h"

int pub_frequency = 10;

int main(int argc, char **argv) {
  ros::init(argc, argv, "walker");
  ros::NodeHandle n;
  Roomba walker;

  ros::Rate loop_rate(pub_frequency);
  ros::Publisher walker_pub = n.advertise < geometry_msgs::Twist
      > ("/mobile_base/commands/velocity", 1000);
//  ros::Publisher walker_pub = n.advertise<geometry_msgs/Twist> ("/mobile_base/commands/velocity", 1000);
  ros::Subscriber walker_sub = n.subscribe("/scan", 1000, &Roomba::sortScanData, &walker);

  while (ros::ok() && n.ok()) {
    geometry_msgs::Twist input;
    if (walker.ifObstacle(walker.distanceToObstacle)) {
      input.linear.x = 0;
      input.linear.y = 0;
      input.linear.z = 0;
      input.angular.x = 0;
      input.angular.y = 0;
      input.angular.z = 1.57;
      ROS_INFO_STREAM("Dist: " << walker.distanceToObstacle << ", Turn");
    } else {
      input.linear.x = .05;
      input.linear.y = 0;
      input.linear.z = 0;
      input.angular.x = 0;
      input.angular.y = 0;
      input.angular.z = 0;
      ROS_INFO_STREAM("Dist: " << walker.distanceToObstacle << ", Forward");
    }
    walker_pub.publish(input);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

