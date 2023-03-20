#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void contours_hier() {
	Mat src = imread("mask.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	findContours() �Լ� ȣ�� �� hierarchy ���ڸ� �����Ͽ� ���� ������ �޾ƿ�.
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/*
	0�� �ܰ������� ������ ���� ������ ���� �ܰ������� �̵��ϸ鼭 for���� ����
	drawContours() �Լ��� hierarchy ������ �����Ͽ� �ܰ����� �׸�. ���� �β��� -1�� ������ �ܰ��� ���θ� ������ ����� ä��.
	
	idx �ʱⰪ�� 0�̰� idx = hierarchy[idx][0] �ڵ带 �̿��� idx ���� ����.
	���⼭ hierarchy[idx][0]�� idx���� �ش��ϴ� �ܰ����� ���� �ܰ��� ��ȣ�� ����Ű�µ�
	���� �ܰ��� ��ȣ�� -1�� �Ǿ� idx >= 0 ������ �������� ������ for ���� ��������.
	*/
	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();



}

int main() {

	contours_hier();

	return 0;
}