#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

	Mat img;
	Point pt0ld;	//	���� ���콺�̺�Ʈ �߻� ��ġ�� �����ϱ� ���� �뵵�� �������� ���·� ����

	void on_mouse(int event, int x, int y, int flags, void*);



int main(void) {
	
	img = imread("phw.jpg");

	if (img.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}
	/*setMouseCallback() �Լ���
	  ����ϱ����� ���콺 �̺�Ʈ�� ���� â��
	  �̸� �����Ǿ� �־����				*/
	namedWindow("img");
	setMouseCallback("img", on_mouse);	
	
	
	imshow("img", img);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*) {
	switch (event) {
	case  EVENT_LBUTTONDOWN:
		pt0ld = Point(x, y);	/*���콺 ���� ��ư�� ���� ��ǥ�� ���������� ����
								  ���콺�� ������ ������ �׸� �� ���*/
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