#include <iterator>
#include <vector>
#include <algorithm>
#include<ros/console.h>
#include<sstream>
#include<cstdlib>
#include<string>
#include"std_msgs/String.h"
#include"Roomba.h" 

bool Roomba::ifObstacle(const sensor_msgs::LaserScan::ConstPtr& scan) {
//  std::vector<float> v( std::begin(scan.ranges), std::end(scan.ranges) );
  std::vector<float> v( scan.ranges, scan.ranges + scan.ranges.size() );
  std::sort( v.begin(), v.end() );
  Roomba::distanceToObstacle = v[0];
  if (v[0]<0.3) {
    return true;
  };
  else {
    return false;
  };
}
