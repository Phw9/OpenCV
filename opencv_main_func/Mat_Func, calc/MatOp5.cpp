#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void MatOp5() {
	Mat img1 = imread("phw.jpg");

	cout << "Width: " << img1.cols << endl;
	cout << "Height: " << img1.rows << endl;
	cout << "Channels: " << img1.channels() << endl;

	if (img1.type() == CV_8UC1)
		cout << "img5 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img5 is a truecolor image." << endl;
	float data[] = { 2.f,1.414f,3.f,1.732f };
	
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;
}

int main(void) {

	MatOp5();

	return 0;
}