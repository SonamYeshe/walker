#ifndef ROOMBA_H_
#define ROOMBA_H_

#include<ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class Roomba {
 public:
  float distanceToObstacle;
  bool ifObstacle(const sensor_msgs::LaserScan::ConstPtr& scan);
};

#endif  //  INCLUDE_ROOMBA_H_"
