#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

	Mat img;
	Point pt0ld;	//	이전 마우스이벤트 발생 위치를 저장하기 위한 용도로 전역병수 형태로 선언

	void on_mouse(int event, int x, int y, int flags, void*);



int main(void) {
	
	img = imread("phw.jpg");

	if (img.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}
	/*setMouseCallback() 함수를
	  사용하기전에 마우스 이벤트를 받을 창이
	  미리 생성되어 있어야함				*/
	namedWindow("img");
	setMouseCallback("img", on_mouse);	
	
	
	imshow("img", img);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*) {
	switch (event) {
	case  EVENT_LBUTTONDOWN:
		pt0ld = Point(x, y);	/*마우스 왼쪽 버튼이 눌린 좌표를 전역변수에 저장
								  마우스가 움직인 궤적을 그릴 때 사용*/
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl;
		break;
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON) {
			line(img, pt0ld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			pt0ld = Point(x, y);
		}
		break;
	default:
		break;
	}//