#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void color_split() {
	Mat src = imread("phw.jpg");	//	jpg�� BGR �÷� ���� �������� �ҷ���

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	/*
	src ������ ä���� �����Ͽ� bgr_planes ���Ϳ� ����
	bgr_planes[0]�� �Ķ���
	bgr_planes[1]�� ���
	bgr_planes[2]�� ������
	*/
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	imshow("src", src);
	imshow("B_planes[0]", bgr_planes[0]);
	imshow("G_planes[1]", bgr_planes[1]);
	imshow("R_planes[2]", bgr_planes[2]);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	color_split();

	return 0;
}