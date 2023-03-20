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

	Mat dst = src + 100;	// ��⸦ 100��ŭ ����
	//Mat dst = src -100;	// ��⸦ 100��ŭ ����

	Mat img = imread("phw.jpg", IMREAD_GRAYSCALE);
	img += 100;	// ��������� �ڱ��ڽ����� ������ ���� ����

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

int main(void) {

	brightness1();

	return 0;
}