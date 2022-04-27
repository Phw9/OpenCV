#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
HSV 색 공간에서 inRange() 함수를 이용해 사용자가 지정한 색상 영역 검출 방법
이러한 방식은 빨, 노, 녹, 파 원샋에 가까운 색상을 찾기에 효과적
사람의 피부색처럼 미세한 변화가 있거나 색상 값을 수치적으로 지정하기 어려운 경우는 비적합
*/

//	두 개의 트랙바 위치를 저장할 lower_hue, upper_hue를 전역 변수로 선언
int lower_hue = 40, upper_hue = 80;

//	main함수와 트랙바 콜백 함수 on_hue_changed() 함수에서 함께 사용할 Mat객체 선언
Mat src, src_hsv, mask;

void on_hue_changed(int, void*);

int main(int argc, char* argv[]) {
	src = imread("candies.png", IMREAD_COLOR);
	
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	//	src 영상을 HSV 색 공간으로 변환해 src_hsv에 저장
	cvtColor(src, src_hsv, COLOR_BGR2HSV);

	imshow("src", src);

	namedWindow("mask");
	/*
	색상의 하한 값과 상한 값을 조절할 수 있는 두 개의 트랙바 생성
	색상의 최댓값을 179로 설정하고, 두 트랙바의 콜백 함수를 모두
	on_hue_changed() 함수로 설정
	*/
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	
	//	프로그램이 처음 실행될 떄 영상이 정상적으로 출력되도록 트랙바 콜백함수를 강제호출
	on_hue_changed(0, 0);

	waitKey();
	return 0;
}

void on_hue_changed(int, void*) {
	Scalar lowerb(lower_hue, 100, 0);	//	최소 색상(Hue), 채도(Saturation) = 100, 명도(Value) = 0
	Scalar upperb(upper_hue, 255, 255);	//	최대 H, S = 255, V = 255

	//	사용자가 설정한 색상 값 범위에 해당하는 영역은 흰색 그 외는 검은색으로 표현된 마스크 영상
	inRange(src_hsv, lowerb, upperb, mask);

	imshow("mask", mask);
}