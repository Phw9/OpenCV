#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void Sum_Mean_Func() {
	Mat img = imread("phw.jpg", IMREAD_GRAYSCALE);

	cout << "Sum: " << (int)sum(img)[0] << endl;		// 자료형이 Scalar면 [0]은 첫번째 원소값
	cout << "Mean: " << (int)mean(img)[0] << endl;		// 자료형이 Scalar면 [0]은 첫번째 원소값
}
void minMaxLoc_Func() {
	Mat img = imread("phw.jpg", IMREAD_GRAYSCALE);		// GRAYSCALE 선언
	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);	// 해당 변수의 주소값을 전달해줘야함

	cout << "minVal: " << minVal << " at " << minPos << endl;	//minVal은 GRAYSSCALE phw.jpg에서 가장 작은 픽셀값, 해당 위치는 minPos
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;	//maxVal은 GRAYSSCALE phw.jpg에서 가장 큰 픽셀값, 해당 위치는 maxPos
}

void NORMALIZE_FUNC() {

	/*norm_type은  NORM_INF, NORM_L1, NORM_L2, NORM_MINMAX가 있는데 
	  NORM_MINMAX인 경우 src 행렬의 최솟값이 alpha, 최댓값이 beta가
	  되도록 모든 원소 값 크기를 조절함.
	  많은 openCV 예제 코드에서 NORM_MINMAX 타입으로 normalize()함수를
	  사용하고 있으며, 특히 실수로 구성된 행렬을 그레이스케일 영상 형태로
	  변환하고자 할 때 normalize()함수를 사용하면 유용*/

	Mat src = Mat_<float>({ 1,5 }, { -1.f,-0.5f,0.f,0.5f,1.f });

	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	// 최솟값이 0, 최댓값이 255가 되도록 크기 조정

	cout << "src: " << src << endl;	// src가 -1~1의 범위인데 이게
	cout << "dst: " << dst << endl;	// dst에서 0~255의 범위로 크기가 조정됨
}

void cvRound_Func() {
	// round 함수와 비슷하게 반올림 시켜주는 함수
	// 소수점 아래가 정확하게 0.5인 경우에는 가장 가까운 짝수로 반올림 수행
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;		// 2
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;		// 3
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;	// 3
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;		// 4
}


int main(void) {



	return 0;
}