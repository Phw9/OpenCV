#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void on_trackbar(int pos, void* userdata);	// pos는 트랙바 위치 및 값

int main(void) {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	//	적응형 이진화의 블록 크기 지정을 위한 트랙바 생성
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void*)&src);
	setTrackbarPos("Block Size", "dst", 11);	//	트랙바 초기위치 11

	waitKey();
	destroyAllWindows();

	return 0;
}

void on_trackbar(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;

	int bsize = pos;
	if (bsize % 2 == 0) bsize--;	// bsize값이 짝수면 홀수로 만듬
	if (bsize < 3) bsize = 3;		// bsize는 최소 3이여야함

	Mat dst;

	/*
	트랙바에서 설정한 블록 크기를 이용해 적응형 이진화를 수행
	가우시안 가중 평균을 사용하고, 블록 평균에서 5를 뺀 값을 임계값으로 사용
	*/
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

	imshow("dst", dst);

}

