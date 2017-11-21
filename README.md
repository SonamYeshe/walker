# walker

## Overview
Modify the TurtleBot simulation from the lecture and implement a simple walker algorithm much like a Roomba robot vacuum cleaner. The robot should move forward until it reaches an obstacle (but not colliding), then rotate in place until the way ahead is clear, then move forward again and repeat.

## License
GNU General Public License v3.0

Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.

## Disclaimer 
Jiawei Ge(SonamYeshe), hereby disclaims all copyright interest in the program `walker' (which makes passes at compilers) written by Jiawei Ge(SonamYeshe).

 (signature of Jiawei Ge), 14 November 2017

 Jiawei Ge

## Build
```
$ cd <path to catkin_ws/src>
$ git clone --recursive https://github.com/SonamYeshe/walker.git
$ cd ../..
$ catkin_make
```

## Run
Run the ros service first.
```
$ roscore
```
Open a new terminal, and 
```
$ roslaunch walker walker.launch
```
Now place the obstacles or turtlebot in the gazebo as you want, to see the roomba function that the robot will avoid all the obstacles.

## Bagfiles
The bagfile is recorded by the command in the walker.launchfile, the default setting is false. If you want to record again, append "record_except_camera:=true" after roslaunch command line.

To see the bag file info,
```
$ roscd walker/
$ rosbag info results/record_except_camera_topics_2017-11-21-12-22-50.bag
```

To play the bag file, close all the terminal except the roscore, first open turtlebot_world.launch to build the world,
```
$ roslaunch turtlebot_gazebo turtlebot_world.launch
```
Then in another terminal,
```
$ rosbag play results/record_except_camera_topics_2017-11-21-12-22-50.bag
```

Note that the default position of turtlebot is meaningless for roomba-like walker function because it'll go straight and pass all the obstacles. I record this bag file while I gather 5 obstacles together as a circle. if you would like to make a bag file by yourself, place the 5 obstacles and turtlebot in the gazebo as you wish, and open a new terminal,
```
$ roslaunch walker walker.launch record_except_camera:=true
```
Type in ctrl+c while you are satisfied. The bag file will be in the /results/ directory with a time postfix.

## Cpplint
```
$ cd <path to catkin_ws/src>
$ wget https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py
$ chmod +x cpplint.py
$ roscd walker/
$ ../cpplint.py $( find . -name \*.hpp -or -name \*.cpp | grep -vE -e "^./build/" -e "^./vendor/" -e "^./docs/" -e "^./results" )
```

## Cppcheck
```
$ roscd walker/
$ cppcheck --enable=all --std=c++11 --includes-file=cppcheck.txt --check-config --suppress=missingIncludeSystem $( find . -name *.cpp | grep -vE -e "^./build/" -e "^./vendor/" )
```

## Dependency

1. ROS kinetic
2. Gazebo8
