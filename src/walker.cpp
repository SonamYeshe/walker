/**
 *  @file     walker.cpp
 *  @brief    a publisher to /mobile_base/commands/velocity topic. a Subscriber to /scan topic.
 *  @details  publishing geometry_msgs::Twist type msg. subscribing sensor_msgs/LaserScan type msg. mainly want to use the smallest float number from array ranges
 *  @author     Jiawei Ge(SonamYeshe)
 *  @copyright  BSD, GNU Public License 2017 Jiawei Ge
 *  @disclaimer Jiawei Ge(SonamYeshe), hereby disclaims all copyright interest in the program `beginner_tutorials' (which makes passes at compilers) written by Jiawei Ge(SonamYeshe).
 <signature of Jiawei Ge>, 21 November 2017
 Jiawei Ge
 */

#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>
#include<geometry_msgs/Twist.h>
#include<ros/console.h>
#include<sstream>
#include<string>
#include"std_msgs/String.h"
#include"Roomba.h"

int pub_frequency = 10;

/**
 *  @brief  acquire depth info from scaner and publish velocity to control turtlebot to move without hitting obstacles  
 *  @param  integer of argument count
 *  @param  char pointer of argument value
 *  @return a bool value
 */

int main(int argc, char **argv) {
  ros::init(argc, argv, "walker");
  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  Roomba walker;

  ros::Rate loop_rate(pub_frequency);
  /**
   * invoke a call to the ros master node. register publishing to "/mobile_base
   * /commands/velocity" and subscribing to "/scan".
   * size of the message queue are both 1000 for subscriber and publisher.
   */
  ros::Publisher walker_pub = n.advertise < geometry_msgs::Twist
      > ("/mobile_base/commands/velocity", 1000);
  ros::Subscriber walker_sub = n.subscribe("/scan", 1000, &Roomba::sortScanData,
                                           &walker);

  while (ros::ok() && n.ok()) {
    geometry_msgs::Twist input;
    /**
     *  if find a obstacle ahead, rotate 90 degree to avoid hitting.
     *  send output to the screen to show the distance toobstacle,
     *  and the turtlebot is moving forward or turning around.
     */
    if (walker.ifObstacle(walker.distanceToObstacle)) {
      input.linear.x = 0;
      input.linear.y = 0;
      input.linear.z = 0;
      input.angular.x = 0;
      input.angular.y = 0;
      input.angular.z = 1.57;
      ROS_INFO_STREAM(
          "Distance to obstacle: " << walker.distanceToObstacle
              << ", Turning...");
    } else {
      /**
       *  if don't find a obstacle ahead, movee forward.
       *  send output to the screen to show the distance to obstacle,
       *  and the turtlebot is moving forward or turning around.
       */
      input.linear.x = .05;
      input.linear.y = 0;
      input.linear.z = 0;
      input.angular.x = 0;
      input.angular.y = 0;
      input.angular.z = 0;
      ROS_INFO_STREAM(
          "Distance to obstacle: " << walker.distanceToObstacle
              << ", Forwarding...");
    }
    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    walker_pub.publish(input);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

