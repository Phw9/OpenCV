#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void color_inverse() {
	Mat src = imread("phw.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);
			Vec3b& p2 = dst.at<Vec3b>(j, i);

			p2[0] = 255 - p1[0];	//	B
			p2[0] = 255 - p1[1];	//	G
			p2[0] = 255 - p1[2];	//	B
		}
	}
	/*
	i) 반전을 각각 따로 처리하지 않고, Vec3b 클래스에서 지원하는 -연산자 재정의를 이용해 한꺼번에 반전을 수행
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<Vec3b>(j, i) = Vec3b(255, 255, 255) - src.at<Vec3b>(j, i);
		}
	}

	ii) - 연산자 재정의 함수를 사용할 수도 있음.
	Mat dst = Scalar(255, 255, 255) - src;
	*/

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	color_inverse();

	return 0;
}