#include <opencv4/opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Dense"


double imu2lidar_data[] = {0.006609639848469365, -0.9999773650294649, 0.0012578115132016717, -0.006730146149038548,
                          -0.9999762249571927, -0.006612093869054189, -0.0019569708811106104, -0.006897049862999071,
                           0.001965243352927244, -0.0012448467359610184, -0.9999972940839232, 0.049898628062256645,
                           0.0, 0.0, 0.0, 1.0};
double cam2imu_data[] = {0.00484977,  0.00156177,  0.99998702,  0.04766175,
                         0.99994143,  0.0096676,  -0.00486465,  0.04650256,
                         -0.00967507,  0.99995205, -0.00151479, -0.01453843,
                         0.0, 0.0, 0.0, 1.0};
double imu2cam_data[] = {0.00484977,  0.99994143, -0.00967507, -0.04687164,
                         0.00156177,  0.0096676,   0.99995205,  0.01401373,
                         0.99998702, -0.00486465, -0.00151479, -0.04745694,
                         0.0, 0.0, 0.0, 1.0};

cv::Mat imu2lidar(cv::Size(4, 4), CV_64FC1, imu2lidar_data);
cv::Mat cam2imu(cv::Size(4, 4), CV_64FC1, cam2imu_data);
cv::Mat imu2cam(cv::Size(4, 4), CV_64FC1, imu2cam_data);

void InverseSE3(cv::Mat& input, cv::Mat& output)
{
    double data[] = {0,0,0,1};
    cv::Mat homogen(cv::Size(4,1), CV_64FC1, data);
    cv::Mat rot = input(cv::Rect(0, 0, 3, 3)).clone();
    std::cout << "rot: " << rot << std::endl;

    cv::Mat trans = input(cv::Rect(3, 0, 1, 3)).clone();
    cv::Mat rot_inv = rot.inv();
    std::cout << "rot_inv: " << rot_inv << std::endl;
    cv::Mat rt = -rot_inv*trans;
    rot_inv = rot_inv.t();
    cv::Mat temp;
    rt = rt.t();
    temp.push_back(rot);
    temp.push_back(rt);
    temp = temp.t();
    temp.push_back(homogen);
    temp.copyTo(output);
    std::cout << "temp: " << temp << std::endl;
    std::cout << "rt: " << rt << std::endl;
    std::cout << "output: " << output << std::endl;

    return;
}


int main()
{
    cv::Mat lidar2cam;
    cv::Mat cam2lidar;
    cv::Mat imu2cam_m;
    cv::Mat lidar2imu_m;
    InverseSE3(imu2lidar, lidar2imu_m);
    std::cout << imu2cam << std::endl;
    lidar2cam = lidar2imu_m*imu2cam;
    cam2lidar = lidar2cam.inv();
    std::cout << "lidar2cam: " << lidar2cam << std::endl;
    std::cout << "cam2lidar: " << cam2lidar << std::endl;
    return 0;
}