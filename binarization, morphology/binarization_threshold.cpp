#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void on_threshold(int pos, void* userdata);

int main(int argc, char* argv[]) {
	Mat src;

	if (argc < 2)
		src = imread("phw.jpg", IMREAD_GRAYSCALE);
	else
		src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	/*
	dst 창에 Threshold 이름의 트랙바를 생성
	트랙바의 최댓값은 255이고, 트랙바 콜백 함수 이름은 on_threshold
	입력 영상 src의 주소를 사용자 데이터로 전달
	*/
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src);

	/*
	프로그램이 처음 실행될 때 트랙바 위치가 128이 되도록 설정
	on_threshold()함수가 처음에 한 번 실행되도록함
	*/
	setTrackbarPos("Threshold", "dst", 128);

	waitKey();
	destroyAllWindows();

	return 0;
}

void on_threshold(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY);

	imshow("dst", dst);
}