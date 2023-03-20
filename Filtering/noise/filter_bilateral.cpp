#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void filter_bilateral() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	
	Mat noise(src.size(), CV_32SC1);
	randn(noise, 0, 5);
	
	Mat addN;
	add(src, noise, addN, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(addN, dst1, Size(), 5);	// noise�� ���� ��Ŀ� stddev�� 5�� blurring

	Mat dst2;
	bilateralFilter(addN, dst2, -1, 10, 5);	// noise�� ���� ��Ŀ� ���������� stddev�� 10�� ����� ���͸���,
											// ��ǥ�������� stddev�� 5�� ����� ���͸��� ����

	Mat dst3;
	bilateralFilter(src, dst3, -1, 10, 5);	// ������ ����� ���͸� ����

	imshow("src", src);
	imshow("addN", addN);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	filter_bilateral();

	return 0;
}