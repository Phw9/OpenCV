#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void blurring_mean() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	/*
	3x3, 5x5, 7x7 filter�� �̿��� blur�� �غ�
	filter ũ�Ⱑ Ŭ���� ������ ���� �ε巴�� �����
	filter ����� (1 / (ksize x ksize)) * (1�� �̷���� (ksize x ksize) ���)

	filter mask ����� �������� 1 �Ǵ� 0�� �ǵ��� �����ϴ� ������
	��� ������ ��� ��Ⱑ �Է� ���� ��� ���� ���� �����Ǳ� ����
	�������� 1���� ������ ��ο� ������, ũ�� ���� ������ ������ ����

	*/
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));

		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

int main(void) {

	blurring_mean();

	return 0;
}