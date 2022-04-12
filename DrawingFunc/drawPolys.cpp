#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void drawLines() {
	//	400x400크기의 3채널 컬러영상을 생성하고 모든픽셀을 흰색으로 초기화
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	//	사각형을 두께 2인 선으로 그림(Red)
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	//	사각형 내부를 채워서 그림(Brown)
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);
	//	반지름이 30인 원 내부를 채워서 그림(Sky)
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	//	반지름이 60인 원을 두께 3인 선으로 그림(Blue)
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);
	//	타원을 0˚부터 270˚까지 내부를 채워 그림(Sky)
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), -1, LINE_AA);
	//	타원을 두께 2인 선으로 그림(Green)
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	//	계단 모양의 다각형을 두께 2인 선으로 그림(Purple)

	vector<Point> pts;
	pts.push_back(Point(250, 250)); pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300)); pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350)); pts.push_back(Point(250, 350));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);


	imshow("img", img);
	waitKey();

	destroyAllWindows();
}


int main(void) {
	
	drawLines();

	return 0;
	
}