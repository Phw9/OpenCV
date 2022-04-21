#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void noise_gaussian() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	// standard deviation 값은 커질수록 잡음이 더 심해짐
	for (int stddev = 10; stddev <= 30; stddev += 10) {
		
		// noise는 부호 있는 정수형(CV_32SC1)을 사용
		Mat noise(src.size(), CV_32SC1);
		randn(noise, 0, stddev);

		Mat dst;
		add(src, noise, dst, Mat(), CV_8U);

		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(100), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}
	
	destroyAllWindows();

}




int main(void) {

	noise_gaussian();

	return 0;
}