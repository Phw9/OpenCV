#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
열기 연산은 입력 영상에 대해 침식 연산을 수행한 후 다시 팽창 연산을 수행
닫기 연산은 입력 영상에 대해 팽창 연산을 수행한 후 다시 침식 연산을 수행

열기 연산은 침식 연산을 먼저 수행하기 때문에 한두 픽셀짜리 영역이 제거된 후, 팽창 연산이 수행
그 결과 입력 이진 영상에 존재하는 작은 크기의 객체가 효과적으로 제거됨.

닫기 연산은 팽창 연산을 먼저 수행하기 때문에 객체 내부의 작은 구멍이 메워진 후, 침식 연산이 수행
결과적으로 닫기 연산은 객체 내부의 작은 구멍을 제거됨.

OpenCV에서 모폴로지 열기와 닫기 연산은 morphologyEx() 함수를 이용함.
열기와 닫기뿐만 아니라 침식과 팽창 같은 일반적인 모폴로지 연산도 수행할 수 있는
범용적인 모폴로지 연산 함수
morphologyEx()의 세 번째 인자 op는 모폴로지 연산 방법을 지정함. 열거형 상수 중
MORPH_GRADIENT 상수는 팽창 결과 영상에서 침식 결과 영상을 빼는 연산을 수행하며,
객체의 외곽선이 추출되는 효과가 있음.{ dst = dilate(src, element) - erode(src, element) }
*/

void open_close() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src 영상에 대해 오츠 알고리즘으로 자동 이진화를 수행
	Mat binary;
	threshold(src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	/*
	이진 영상의 열기 연산은 erode() dilate() 함수를 사용하여 쉽게 구현 가능
	Mat dst;
	erode(src, dst, Mat());
	dilate(dst, dst, Mat());

	이진 영상의 닫기 연산은
	Mat dst;
	dilate(src, dst, Mat());
	erode(dst, dst, Mat());

	실제로 morphologyEx() 함수 내부에서도 이와 같이 연산이 수행됨.
	*/
	Mat dst1, dst2;
	morphologyEx(src, dst1, MORPH_OPEN, Mat());	//	MORPH_OPEN은 열기 연산
	morphologyEx(src, dst2, MORPH_CLOSE, Mat());//	MORPH_CLOSE은 닫기 연산

	imshow("src", src);
	imshow("binary", binary);
	imshow("open", dst1);
	imshow("close", dst2);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	open_close();

	return 0;
}