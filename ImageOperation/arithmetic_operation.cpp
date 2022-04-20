#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*

영상에서 행렬의 곱셈을 수행하는 경우는 거의 없지만 두 영상에서
같은 위치에 있는 픽셀 값끼리 서로 곱하거나 나누는 연산을 수행할
수 있으며, 이를 위해 openCV에서 multiply(), divide() 함수를 제공함.

일반적인 행렬의 곱셈 연산은 gemm() 함수를 사용함.

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

	add(src1, src2, dst1);
	addWeighted(src1, 0.1, src2, 0.9, 0, dst2);	//	가중치와 gamma를 더해준 add연산
	subtract(src1, src2, dst3);
	absdiff(src1, src2, dst4);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	
	waitKey();
	destroyAllWindows();

	return 0;
}