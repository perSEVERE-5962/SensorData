#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <ros/ros.h>
#include <string>
#include <sensor_msgs/PointCloud2.h>

using namespace std;
//Do not use this as an example for format, this is bad practice in c++, should be obj oriented.

ros::Publisher pointcloud2_pub;
string filename;

void timerCallback(const ros::TimerEvent& e){
sensor_msgs::PointCloud2 ros_cloud;

pcl::PCLPointCloud2::Ptr cloud2(new pcl::PCLPointCloud2());
pcl::PointCloud<pcl::PointXYZ>::Ptr cloudxyz(new pcl::PointCloud<pcl::PointXYZ>());
pcl::io::loadPCDFile<pcl::PointXYZ>(filename, *cloudxyz);
pcl::toPCLPointCloud2(*cloudxyz, *cloud2);
pcl_conversions::moveFromPCL(*cloud2, ros_cloud);

if(ros_cloud.row_step <= 0)
  ROS_ERROR("Empty Cloud!");

if(ros_cloud.header.frame_id.size() == 0)
  ros_cloud.header.frame_id = "map";

pointcloud2_pub.publish(ros_cloud);
}

int main(int argc, char** argv){
if(argc <= 1){
  ROS_ERROR("Need to give an argument when running this script. EXITING!");
  return 0;
}

filename = argv[1];

ros::init(argc, argv, "display_cloud");
ros::NodeHandle nh;

ros::Timer timer = nh. createTimer(ros::Duration(0.1), timerCallback);
pointcloud2_pub = nh.advertise<sensor_msgs::PointCloud2>("FRC/Kickoff_Cloud", 1);

ros::spin();
return 0;
}
