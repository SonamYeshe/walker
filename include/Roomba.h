#ifndef ROOMBA_H_ // NOLINT
#define ROOMBA_H_

#include<ros/ros.h>
#include<sensor_msgs/LaserScan.h>

class Roomba {
 public:
  float distanceToObstacle;
  void sortScanData(const sensor_msgs::LaserScan::ConstPtr& scan);
  bool ifObstacle(float distance);
};

#endif  //  INCLUDE_ROOMBA_H_"
