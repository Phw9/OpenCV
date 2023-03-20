#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void sobel_edge() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
	}

	/*
	x축, y축 방향으로 1차 편미분을 각각 구하여 dx와 dy 행렬에 저장
	dx, dy 행렬은 float 자료형을 사용하도록 설정
	*/
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	
	/*
	dx, dy 행렬로부터 그래디언트 크기를 계산해 fmag에 저장
	깊이는 dx,dy와 같게 실수 자료형으로 저장
	*/
	magnitude(dx, dy, fmag);
	//	실수형 행렬 fmag를 그레이스케일 형식으로 변환해 저장
	fmag.convertTo(mag, CV_8UC1);
	
	/*
	에지 판별을 위해 그래디언트 크기 임계값을 150으로 설정
	행렬 edge의 원소 값은 mag 행렬 원소 값이 150보다 크면 255
	작으면 0으로 설정됨
	*/
	Mat edge = mag > 150;

	imshow("src", src);
	/*
	mage 영상은 그래디언트 크기를 그레이스케일 영상 형식으로 나타낸 것
	만약 그래디언트 크기가 255보다 큰 경우 포화연산에 의해서 흰색으로 표현
	*/
	imshow("mag", mag);

	/*
	edge 영상은 그래디언트 크기가 150보다 큰 픽셀은 흰색으로
	그렇지 않은 픽셀은 검은색으로 표현된 이진 영상
	threshold를 150보다 낮게 설정하면 더 많은 에지 픽셀이 나타나지만
	너무 낮추면 잡음의 영향도 에지로 검출될 수 있음
	*/
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}


int main(void) {

	sobel_edge();

	return 0;
}