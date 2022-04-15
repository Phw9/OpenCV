#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// 트랙바를 이용한 밝기조절

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
		사실 트랙바 콜백 함수는 사용자가 직접 호출하는
		용도가 아니라 시스템에 의해 자동으로 호출되도록
		만드는 함수이지만 프로그램 동작을 매끄럽게
		만들기 위한 편법으로 on_brightness() 함수를
		강제로 호출한 것.

		이 행이 없으면 {on_brightness() 함수 호출을 생략하면}
		프로그램이 시작될 때는 영상이 나타나지 않고, 
		트랙바를 움직이기 시작한 후 부터 영상이 나타난다.
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