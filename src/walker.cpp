#include<ros/ros.h>
#include<sensor_mags/LaserScan.h>
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

  ros::Publisher walker_pub = n.advertise < geometry_msgs / Twist
      > ("/mobile_base/commands/velocity", 1000);
  ros::Subscriber walker_sub = n.subscribe("/scan", 1000, Roomba::ifObstacle,
                                           &walker);
  ros::Rate loop_rate(pub_frequency);

  while (ros::ok) {
    geometry_msgs::Twist input;
    if (walker.ifObstacle(const sensor_msgs::LaserScan)) {
      input.linear.x = 0;
      input.linear.y = 0;
      input.linear.z = 0;
      input.angular.x = 0;
      input.angular.y = 0;
      input.angular.z = .1;
      if (walker.distanceToObstacle > .00001) {
        ROS_INFO_STREAM("Dist: " << walker.distanceToObstacle << ", Turn");
      }
    } else {
      if (walker.distanceToObstacle > 0) {
        input.linear.x = .15;
        input.linear.y = 0;
        input.linear.z = 0;
        input.angular.x = 0;
        input.angular.y = 0;
        input.angular.z = 0;
        if (walker.distanceToObstacle < 100) {
          ROS_INFO_STREAM("Dist: " << walker.distanceToObstacle << ", Forward");
        }
      }
    }
    if (walker.distanceToObstacle < .00001 || walker.distanceToObstacle > 99) {
      input.angular.z = 0;
      input.linear.x = 0;
      ROS_INFO_STREAM("Idle");
    }
    walker_pub.publish(input);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

