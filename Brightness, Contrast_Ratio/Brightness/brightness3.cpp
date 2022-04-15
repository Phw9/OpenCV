#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*	
	포화 연산을 수행하는 saturate_cast()라는 이름의 캐스팅 함수를 지원함.
	템플릿 함수로 정의되어 있으며 그레이 스케일 영상에 대해 자주 사용되는 형식은
	
	template<> inline uchar saturate_cast<uchar>(int v);
	
	v는 int 자료형이 표현할 수 있는 범위의 정수
	반환값이 0~255사이의 정수
*/

/*	
	지금 예제처럼 셀 값을 하나씩 변경하는 것보다 openCV에서 제공하는 덧셈 연산자
	재정의를 사용하여 코드를 작성하는 것이 더욱 빠르고 간편.
	OpenCV에서 제공하는 함수를 사용하면 CPU 최적화 및 병렬 처리를 수행하기 때문에
	빠르게 동작하고, 소스 코드 가독성도 높은 편, 다만 컴퓨터 비전 프로젝트를 수행하다
	보면 OpenCV에서 지원하지 않는 새로운 기능을 직접 구현해야 하는 경우가 발생하기
	때문에 영상의 픽셀 값을 직접 참조하고 변경하는 방법은 반드시 기억하고 있어야함.
	더불어 포화 연산을 위한 saturate_cast()함수 사용법도 숙지.
*/

// 포화 연산을 고려한 밝기증가
void brightness3() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	// 포화 연산을 고려해 반복문을 만든다면 삼항 조건 연산자를 이용
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			int v = src.at<uchar>(j, i) + 100;
			dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}


int main(void) {

	brightness3();
	
	return 0;
}