#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void hough_lines() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat edge;
	//	에지영상을 추출
	Canny(src, edge, 50, 150);
	
	/*
		x * cos(theta) + y * sin(theta) = ρ
	*/

	//	축적배열에서 ρ는 1픽셀 단위로, Θ는 1˚ 단위로 처리
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);	// threshold를 250으로 설정

	//	grayscale 영상인 edge를 BGR 3채널 컬러 영상으로 변환해 dst 저장
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	
	/*
	HoughLines() 함수에 의해 구해진 직선의 개수만큼 for 반복문 수행
	직선의 방정식 파라미터 중 ρ를 변수 r에, Θ를 변수 t에 저장
	x0와 y0는 원점에서 직선에 수선을 내렸을 때 만나는 점의 좌표
	pt1과 pt2에는 (x0, y0)에서 충분히 멀리 떨어져 있는 직선상의 두 점 좌표가 저장
	line()함수로 검출된 직선을 두께가 2인 빨간색 실선으로 그림
	alpha는 직선을 충분히 멀리 떨어져있게 하기위한 weighted
	*/
	
	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0], t = lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255),2,LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	hough_lines();
	return 0;
}