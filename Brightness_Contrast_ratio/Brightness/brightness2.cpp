#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//	포화 연산을 고려하지 않은 영상의 밝기 증가
void brightness2() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	/*	unsigned char a =256; cout << "a = " << a << endl; 을 출력하면 a=0이
		출력된다. 그 이유는 C/C++의 unsigned char 자료형은 1바이트 메모리 공간을
		사용하고 0~255까지의 정수 값을 저장할 수 있음. 그래서 변수 a에 256을 대입
		하려고 하면 자동으로 0으로 변환돼 저장됨.
		좀 더 자세히 설명하면 정수 256을 16진수로 표현하면 0x00000100이고, 이 값을
		unsigned char 자료형에 대입하려고 하면 하위 1바이트만 대입되기 때문에 변수
		a에는 0x00이 저장됨.
		257은 0x00000101이므로 0x01이여서 1이 저장됨
	*/
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();

	

	

}


int main(void) {

	brightness2();

	return 0;
}