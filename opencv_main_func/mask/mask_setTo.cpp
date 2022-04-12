#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mask_setTo() {
	Mat src = imread("phw.jpg", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);
	waitKey();

	destroyAllWindows();

}

int main(void) {
	
	mask_setTo();
	return 0;

}
