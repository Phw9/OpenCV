#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*Ư�� �Լ��� ����Ǵ� �ð��� �и��� ������ �����Ϸ��� ������ ���� �ڵ��ۼ�*/

/*

int64 t1 = getTickCount();

my_func(); // do something

int64 t2 = getTickCount();

double ms = (t2 - t1) * 1000 / getTickFrequency();

*/

void time_inverse() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;
	tm.start();

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}

	tm.stop();
	cout << "Image inverse took: " << tm.getTimeMilli() << "ms." << endl;
}

int main(void) {

	time_inverse();

	return 0;
}