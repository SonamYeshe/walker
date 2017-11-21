/**
 *  @file   	Roomba.h
 *  @brief  	header of the roomba.cpp
 *  @details	define one class member, two class member functions 
 *  @author     Jiawei Ge(SonamYeshe)
 *  @copyright  BSD, GNU Public License 2017 Jiawei Ge
 *  @disclaimer Jiawei Ge(SonamYeshe), hereby disclaims all copyright interest in the program `beginner_tutorials' (which makes passes at compilers) written by Jiawei Ge(SonamYeshe).
 <signature of Jiawei Ge>, 21 November 2017
 Jiawei Ge
 */

#ifndef ROOMBA_H_
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
