#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
허프 변환 원 검출
(x-a)^2 + (y-b)^2 = r^2
원래는 a,b,r 세 개의 파라미터를 가지고 있으므로, 허프 변환을 그대로 적용하려면
3차원 파라미터 공간에서 축적 배열을 정의하고 가장 누적이 많은 위치를 찾아야 하지만
너무 많은 메모리와 연산 시간을 필요로 하게 되므로 허프 그래디언트 방법을 사용해 원을 검출
*/
void hough_circles() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	잡음을 제거하기 위함
	Mat blurred;
	blur(src, blurred, Size(3, 3));

	/*
	circles 인자에는 보통 vector<Vec3f> or vector<Vec4f> 자료형 변수 지정
	Vec3f면 중심좌표(a,b), 반지름 r 이 차례대로 저장
	Vec4f면 추가적으로 축적 배열 누적 값이 저장
	
	dp 인자는 사용할 축적 배열의 크기를 결정
	dp 인자를 1로 지정하면 입력 영상과 같은 크기의 축적 배열을 사용
	2를 지정하면 입력 영상의 가로와 세로 크기를 2로 나눈 크기의 축적 배열을 사용
	
	minDist 인자에는 인접한 원의 최소 거리를 지정 즉, 두 원의 중심점 사이
	거리가 mindDist보다 작으면 두 원중 하나는 검출X
	
	param1 인자는 HoughCircles() 함수 내부에서 캐니 에지 검출기를 이용할 때 높은
	임계값으로, 낮은 임계값은 param1의 절반으로 설정.
	
	param2는 축적 배열에서 원의 중심을 찾을 때 사용하는 임계값
	
	minRadius와 maxRadius 인자에 검출할 원의 최소 반지름과 최대반지름을 지정하는데
	만약 영상에서 검출할 원의 대략적인 크기를 알고있다면 적절히 지정해 연산 속도를 향상시킴
	*/
	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	hough_circles();

	return 0;
}