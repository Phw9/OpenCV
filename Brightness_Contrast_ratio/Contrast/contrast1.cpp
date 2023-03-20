#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;


//	기본적인 명암비 증가 예제
/*
	사실상 픽셀값에 일정 상수를 단순히 곱하여 명암비를 조절하는 방식은
	실전에서는 잘 사용 x
	효과적인 명암비를 높이기 위해선 밝은 픽셀은 더 밝게, 어두운 픽셀은 더 어둡게
	변경해야함.
*/
void contrast1() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {
	
	contrast1();

	return 0;
}