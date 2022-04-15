#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// Ʈ���ٸ� �̿��� �������

void on_brightness(int pos, void* userdata);

void brightness4() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src);
	/*
		��� Ʈ���� �ݹ� �Լ��� ����ڰ� ���� ȣ���ϴ�
		�뵵�� �ƴ϶� �ý��ۿ� ���� �ڵ����� ȣ��ǵ���
		����� �Լ������� ���α׷� ������ �Ų�����
		����� ���� ������� on_brightness() �Լ���
		������ ȣ���� ��.

		�� ���� ������ {on_brightness() �Լ� ȣ���� �����ϸ�}
		���α׷��� ���۵� ���� ������ ��Ÿ���� �ʰ�, 
		Ʈ���ٸ� �����̱� ������ �� ���� ������ ��Ÿ����.
	*/
	

	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;
	imshow("dst", dst);
}
int main(void) {

	brightness4();

	return 0;
}