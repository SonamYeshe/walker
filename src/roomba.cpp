#include<iterator>
#include<vector>
#include<algorithm>
#include<ros/console.h>
#include<sstream>
#include<cstdlib>
#include<string>
#include"std_msgs/String.h"
#include"Roomba.h" 

void Roomba::sortScanData(const sensor_msgs::LaserScan::ConstPtr& scan) {
//  std::vector<float> v( std::begin(scan->ranges), std::end(scan->ranges) );
  std::vector<float> v( scan->ranges.begin(), scan->ranges.begin() + scan->ranges.size() );
  std::sort( v.begin(), v.end() );
  Roomba::distanceToObstacle = v[0];
}

bool Roomba::ifObstacle(float distance) {
  if (distance<0.5) {
    return true;
  }
  else {
    return false;
  };
}
