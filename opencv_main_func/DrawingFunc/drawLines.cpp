#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void drawLines() {
	// 400x400크기의 3채널 컬러영상을 생성하고 모든픽셀을 흰색으로 초기화
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	// 수평방향의 직선 세 개를 서로 다른 색상과 두께로 그린 것
	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	// 대각선 방향의 직선 세 개를 서로 다른 색상과 직선 타입으로 그린 것
	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	// 수평 방향의 화살표 세 개를 서로 다른 색상, 길이, 화살표 길이로 그린 것

	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0.05);

	// 다양한 모양의 마커를 그린 것

	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), 4);
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), 5);
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), 6);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}


int main(void) {
	
	drawLines();

	return 0;
	
}