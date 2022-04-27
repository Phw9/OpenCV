#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void color_split() {
	Mat src = imread("phw.jpg");	//	jpg를 BGR 컬러 영상 형식으로 불러옴

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	/*
	src 영상의 채널을 분할하여 bgr_planes 벡터에 저장
	bgr_planes[0]은 파란색
	bgr_planes[1]은 녹색
	bgr_planes[2]은 빨간색
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