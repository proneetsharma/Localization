# Localization:
Determining the position of robot in a mapped environment.
Because it is a probabilistic model so robot do this by making some guesses and then over the time it narrow down to one position.

**3 types** -  
		* Local (Initial position is known but the challenge is in estimating its position 
	 		   		   while movement.)
		* Global (Initial position is not known)
		* Kidnapped (The position of robot can be changed any time)

### Kalman Filter: 
It is used to remove the noise/uncertainty form the data. 
* It is a continuous iteration of two step process-
#### 1. Update measurement- In this we us the recorded measurement to update the state.
#### 2. State prediction- We use the information of current state to predict what will 
be the future state. In start we make a guess.

**3 types** 
		* KF (for linear system)
		* Extended KF (for non linear system)
		* Unscented KF (for extreme non linear system)


# Implementation of EKF Package on ROS

### Here we are using 5 different Packages-
1. TurtleBot Gazebo Package
2. Robot Pose EKF Package
3. Odometetry to Trajectory Package
4. TurtleBot Teleop Package
5. Rviz Package

### 1.TurtleBot Gazebo Package
Launches a mobile robot inside the gazebo environment

#### Clone package
```sh
$ cd /home/catkin_ws/src
$ git clone https://github.com/turtlebot/turtlebot_simulator
```
#### Install Dependencies
```sh
$ cd /home/catkin_ws/src
$ source devel/setup.zsh
$ rosdep -i install turtlebot_gazebo
```
#### Build Package
```sh
$ catkin_make
$ source devel/setup.zsh
```
#### Launch Node
```sh 
$ roslaunch turtlebot_gazebo turtlebot_world.launch
```
### 2. Robot Pose EKF Package
Estimate the position and orientation of the robot


              SENSORS --------> robot_pose_ekf ---------> FILTER

The EKF node is subscribes the data from different different topics(like odom topic,IMU data topic etc)and publishes the filtered results.


#### Clone package
```sh
$ cd /home/catkin_ws/src
$ git clone https://github.com/udacity/robot_pose_ekf
```
Edit the robot_pose_ekf.launch file

		<launch>

		<node pkg="robot_pose_ekf" type="robot_pose_ekf" name="robot_pose_ekf">
		  <param name="output_frame" value="odom_combined"/>
		  <param name="base_footprint_frame" value="base_footprint"/>
		  <param name="freq" value="30.0"/>
		  <param name="sensor_timeout" value="1.0"/>  
		  <param name="odom_used" value="true"/>
		  <param name="imu_used" value="true"/>
		  <param name="vo_used" value="false"/>

		  <remap from="imu_data" to="/mobile_base/sensors/imu_data" />    

		</node>

		</launch>

#### Build Package
```sh
$ catkin_make
$ source devel/setup.zsh
```
#### Launch Node 
```sh
$ roslaunch robot_pose_ekf robot_pose_ekf.launch 
```
### 3. Odometetry to Trajectory Package
Append the odometry value generated over time into a trajectory path

#### Install the package
```sh
$ cd /home/workspace/catkin_ws/src
$ git clone https://github.com/udacity/odom_to_trajectory
```
#### Build the package
```sh
$ cd /home/workspace/catkin_ws
$ catkin_make
$ source devel/setup.bash
```
#### Launch the nodes
```sh
$ roslaunch odom_to_trajectory create_trajectory.launch
```

### TurtleBot Teleop Package
It will let you drive the turtleBot with keyboard command
The turtleBot node has no subscriber, it only publishes control commands

#### Clone package
```sh
$ cd /home/catkin_ws/src
$ git clone https://github.com/turtlebot/turtlebot
```
#### Install Dependencies
```sh
$ cd /home/catkin_ws/src
$ source devel/setup.zsh
$ rosdep -i install turtlebot_teleop
```
#### Build Package
```sh
$ catkin_make
$ source devel/setup.zsh
```
#### Launch Node 
```sh
$ roslaunch turtlebot_teleop turtlebot_teleop.launch
```

### Rviz Package
Gives a visualisation of estimated robot position and its orientation 

#### Launch Package
```sh
$ rviv
```
## Creating a launch file so that it can launch the above packages simlultaneously
	
#### Create a main package(the launch file should always be in a package)
```sh
$ cd /home/catkin_ws/src
$ catkin_cretae_pkg main
```	
#### Build Package
```sh
$ catkin_make
$ source devel/setup.zsh
``` 	
#### Create and edit the main.launch file
```sh
$ cd /home/catkin_ws/src/main
$ mkdir launch
$ cd launch
$ subl main.launch
```
(copy the content of each file to the main.launch)

#### Launch the main.launch file
```sh
$ cd /home/workspace/catkin_ws
$ source devel/setup.bash
$ roslaunch main main.launch
```


