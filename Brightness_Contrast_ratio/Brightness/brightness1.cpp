#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void brightness1() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst = src + 100;	// 밝기를 100만큼 증가
	//Mat dst = src -100;	// 밝기를 100만큼 감소

	Mat img = imread("phw.jpg", IMREAD_GRAYSCALE);
	img += 100;	// 밝기조정을 자기자신한테 저장할 수도 있음

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

int main(void) {

	brightness1();

	return 0;
}