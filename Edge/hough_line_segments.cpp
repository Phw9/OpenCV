#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

/*
확률적 허프 변환 선분 검출
HoughLinesP() 함수에서 검출된 선분 정보가 저장되는 lines 인자에는
보통 vector<Vec4i> 자료형 변수를 지정
각각의 선분 정보는 Vec4i 자료형으로 저장되고, 하나의 Vec4i 객체에는
선분 시작점의 x,y 좌표,  선분 끝점의 x,y 좌표가 저장
maxLineGap 인자는 일직선상의 직선이 잡음 등 영향으로 끊어져 있을 때,
두 직선을 하나의 직선으로 간주하고자 할 때 사용
*/

void hough_line_segments() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);	// 캐니함수로 에지검출

	//	HoughLinesP()를 이용해 모든 직선 성분의 시작점과 끝점 좌표를 구한다
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	//	직선을 나타내기 위해 에지영상을 3채널 컬러영상으로 변경
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	/*
	HoughLinesP()에 의해 구해진 모든 직선 성분을 dst 영상 위에 그림
	l[0], l[1]이 선분 시작점 x, y
	l[2], l[3]이 선분 끝점 x, y
	
	C + 11의 범위 기반 for 반복문(range - based for loop) 문법을 사용
	vetor 또는 배열 등에 저장되어 있는 모든 원소를 하나씩 꺼내어
	사용할 때 편리한 문법
	*/
	
	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	hough_line_segments();

	return 0;
}