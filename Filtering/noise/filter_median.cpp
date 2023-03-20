#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void filter_median() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	Mat salt_pep = src.clone();

	if (src.empty() || salt_pep.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	int num = (int)(salt_pep.total() * 0.1);	// 입력 영상 전체 크기의 10%
	for (int i = 0; i < num; i++) {
		int x = rand() % salt_pep.cols;
		int y = rand() % salt_pep.rows;
		salt_pep.at<uchar>(y, x) = (i % 2) * 255; // 입력 영상 픽셀에 소금&후추 잡음 추가
	}

	Mat dst1;
	GaussianBlur(salt_pep, dst1, Size(), 1);	// S&P noise를 gaussian 필터링

	Mat dst2;
	medianBlur(salt_pep, dst2, 3);				// S&P noise를 median 필터링

	Mat dst3;
	medianBlur(src, dst3, 3);					// 원본을 median 필터링 

	imshow("src", src);
	imshow("S&P", salt_pep);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);

	waitKey();

	destroyAllWindows();
}

int main(void) {

	filter_median();

	return 0;
}