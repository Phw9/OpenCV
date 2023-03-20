#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void MatOp1() {
	Mat img1; // empty matrix

	Mat img2(480, 640, CV_8UC1);	//	unsinged char, 1-channel
	Mat img3(480, 640, CV_8UC3);	//	unsinged char, 3-channel
	Mat img4(Size(640, 480), CV_8UC3);	//	Size(width, height)

	Mat img5(480, 640, CV_8UC1, Scalar(128));	// initial values, 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));	// initial values, red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);	//	0's matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);	//	1's matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);	//	identity matrix

	float data[] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);
	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<uchar>({ 2, 3 }, { 1,2,3,4,5,6 });

	mat4.create(256, 256, CV_8UC3);	//	uchar, 3-channels
	mat5.create(4, 4, CV_32FC1);	//	float, 1-channels

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);

	/*3차원 이상의 다차원 행렬
	
		Mat::Mat(int ndims, const int* sizes, int type);
		
		Mat::Mat(const std::vector<int>& sizes, int type);	// type은 바이트와 채널(깊이)
	*/



}


int main(void) {

	MatOp1();

	return 0;
}