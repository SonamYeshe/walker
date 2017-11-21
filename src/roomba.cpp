/**
 *  @file     roomba.cpp
 *  @brief    define two functions in roomba class
 *  @details  sort the smallest float number from array "ranges". give the definition of whether there's a obstacle
 *  @author     Jiawei Ge(SonamYeshe)
 *  @copyright  BSD, GNU Public License 2017 Jiawei Ge
 *  @disclaimer Jiawei Ge(SonamYeshe), hereby disclaims all copyright interest in the program `beginner_tutorials' (which makes passes at compilers) written by Jiawei Ge(SonamYeshe).
 <signature of Jiawei Ge>, 21 November 2017
 Jiawei Ge
 */

#include<ros/console.h>
#include<iterator>
#include<vector>
#include<algorithm>
#include<sstream>
#include"std_msgs/String.h"
#include"Roomba.h"

/**
 *  @brief  acquire data from /scan topic and sort the smallest float number in the array "ranges"  
 *  @param  const pointer to msg type sensor_msgs::LaserScan
 *  @return void
 */

void Roomba::sortScanData(const sensor_msgs::LaserScan::ConstPtr& scan) {
  std::vector<float> v(scan->ranges.begin(),
                       scan->ranges.begin() + scan->ranges.size());
  std::sort(v.begin(), v.end());
  Roomba::distanceToObstacle = v[0];
}

/**
 *  @brief  give the definition of the existence of obstacles 
 *  @param  a float number. typically the smallest distance from turtlebot to the obstacle.
 *  @return bool value. obstacle or not
 */

bool Roomba::ifObstacle(float distance) {
  if (distance < 0.5) {
    return true;
  } else {
    return false;
  }
}

