#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void blurring_gaussian() {

	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	/*
	sigma(표준편차)가 클수록 blurring이 더 많이됨
	sigmaX, sigmaY는 각 방향으로의 가우시안 커널 표준 편차인데
	sigmaY = 0 이면 sigmaX와 같은 값을 사용
	모두 0이면 ksize의 width와 height 값으로부터 표준 편차를 계산해 사용
	
	*/

	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(), (double)sigma);
		String text = format("sigma=%d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}
int main(void) {

	blurring_gaussian();

	return 0;
}

/*

getGaussianKernel() 함수는 표준 편차가 sigma인 1차원 가우시안 분포
함수로부터 (ksize x 1) 크기의 필터 마스크 행렬을 생성해 반환
ksize는 ((8 x sigma) + 1)보다 같거나 크게 지정하는 것이 좋음

getGaussianKernel() 함수는 ksize 값이 7보다 같거나 작고 sigma 값이
0 또는 음수인 경우에는 다음과 같이 미리 정해 놓은 배열 값을 이용해 커널 행렬을 생성

static const float small_gaussian_tab[][7] =
{
	{ 1.f },
	{ 0.25f, 0.5f, 0.25f },
	{ 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f },
	{ 0.03125f, 0.109375f, 0.21875f, 0.28125f, 0.21875f, 0.109375f, 0.03125f }
};

*/