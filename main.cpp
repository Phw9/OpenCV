#include <opencv4/opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Dense"


double lidar2imu_data[] = {0.006609639848469365, -0.9999773650294649, 0.0012578115132016717, -0.006730146149038548,
                          -0.9999762249571927, -0.006612093869054189, -0.0019569708811106104, -0.006897049862999071,
                           0.001965243352927244, -0.0012448467359610184, -0.9999972940839232, 0.049898628062256645,
                           0.0, 0.0, 0.0, 1.0};
double cam2imu_data[] = {0.004849772428227678, 0.9999414346087855, -0.009675074155577834, -0.04687164440963156,
                         0.0015617672176878594, 0.009667602187984597, 0.9999520480258492, 0.014013727849697887,
                         0.9999870202110375, -0.004864650085710409, -0.001514790081641404, -0.047456938997062464,
                         0.0, 0.0, 0.0, 1.0};


cv::Mat cam2imu(cv::Size(4, 4), CV_64FC1, cam2imu_data);
cv::Mat lidar2imu(cv::Size(4, 4), CV_64FC1, lidar2imu_data);

void InverseSE3(cv::Mat& input, cv::Mat& output)
{
    double data[] = {0,0,0,1};
    cv::Mat homogen(cv::Size(4,1), CV_64FC1, data);
    cv::Mat rot = input(cv::Rect(0, 0, 3, 3)).clone();
    std::cout << "rot: " << rot << std::endl;

    cv::Mat trans = input(cv::Rect(3, 0, 1, 3)).clone();
    cv::Mat rot_inv = rot.inv();
    std::cout << "rot_inv: " << rot_inv << std::endl;
    rot_inv = rot_inv.t();
    cv::Mat rt = -rot_inv*trans;
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
    cv::Mat imu2cam;
    InverseSE3(cam2imu, imu2cam);
    lidar2cam = lidar2imu*imu2cam;
    lidar2cam = lidar2cam.inv();
    std::cout << lidar2cam << std::endl;
    return 0;
}