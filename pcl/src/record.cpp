
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& kinect){
int gyro=0; int encoder=0;
ofstream out;
out.open("gyro.txt",ios_base::app);
out <<"gyro "<< gyro <<endl;
out <<"encoder "<< encoder<<endl;
out.close();



time_t t = time(0);

time(&t);

ROS_INFO_STREAM("SUCCESS");
pcl::PCLPointCloud2 pcl_pc;
pcl::PointCloud<pcl::PointXYZ>cloud;
pcl_conversions::toPCL(*kinect,pcl_pc);
pcl::fromPCLPointCloud2(pcl_pc,cloud);
string date = ctime(&t);
date += ".pcd";
pcl::io::savePCDFile(date,cloud);
sleep(2);
}

int main (int argc, char** argv){
ros::init(argc,argv,"record");
ros::NodeHandle use;
ros::Subscriber sub=use.subscribe<sensor_msgs::PointCloud2>("/camera/depth/points",1,cloud_cb);
ros::spin();
return 0;
}


