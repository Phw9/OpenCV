#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
침식(erosion) 연산은 객체 영역의 외곽을 골고루 깎아 내는 연산으로 전체적으로
객체 영역은 축소되고 배경은 확대함. 구조요소를 영상 전체에 대해 스캔하면서, 구조 요소가
객체 영역 내부에 완전히 포함될 경우 고정점(anchor point) 위치 픽셀을 255로 설정

팽창(dilation) 연산은 객체 외곽을 확대하는 연산. 팽창 연산을 수행하면 객체 영역은
확대되고, 배경영역은 줄어듬. 구조요소를 영상 전체에 대해 이동시키면서, 구조 요소와
객체 영역이 한 픽셀이라도 만날 경우 고정점 위치 픽셀을 255로 설정
*/

void erode_dilate() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src 영상에 대해 오츠 알고리즘으로 자동 이진화를 수행
	Mat binary;
	threshold(src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	/*
	세번째 인자로 Mat()선언 시 3x3 정방형 구조요소를 사용 그 외의 구조요소는
	getStructuringElement()함수를 이용해 만들 수 있음.
	*/
	erode(binary, dst1, Mat());	//	침식 연산을 수행
	dilate(binary, dst2, Mat());//	팽창 연산을 수행

	imshow("src", src);
	imshow("binary", binary);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	erode_dilate();

	return 0;
}