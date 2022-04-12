#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void drawText1() {
	
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));

	putText(img, "FONT_HERSHEY_SIMPEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	
	//	FONT_HERSHEY_COMPLEX 폰트와 FONT_ITALIC 상수를 함께 사용해 이탤릭체로 문자열 출력
	putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));


	imshow("img", img);
	waitKey();

	destroyAllWindows();
}


int main(void) {
	
	drawText1();

	return 0;
	
}