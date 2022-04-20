#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
logical operation은 픽셀 값을 이진수로 표현하여
각 bit 단위 논리 연산을 수행하는 것을 의미

	논리곱(AND)		: 두 개의 입력 비트가 모두 1인 경우, 결과가 1
	논리합(OR)		: 두 개의 입력 비트 중 하나라도 1인 경우, 결과가 1
배타적 논리합(XOR)	: 1. 두 개의 입력 비트 중 오직 하나만 1인 경우, 결과가 1
					  2. 입력 비트가 모두 0 또는 1 인경우, 결과가 0
	부정(NOT)		: 1. 하나의 입력 영상에 대해 동작하며 입력 비트가 0이면 결과가 1
					  2. 1이면 결과가 0
*/

int main(void) {

	Mat src1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	/*
	bitwise 함수사용도 되지만 OpenCV는 연산자 재정의도 지원함
	*/
	bitwise_and(src1, src2, dst1);	//	dst1 = src1 & src2;
	bitwise_or(src1, src2, dst2);	//	dst2 = src1 | src2;
	bitwise_xor(src1, src2, dst3);	//	dst1 = src1 ^ src2;
	bitwise_not(src1, dst4);	//	dst1 = ~src1;

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	destroyAllWindows();

	return 0;
}