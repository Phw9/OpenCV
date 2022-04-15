#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;


//	�⺻���� ��Ϻ� ���� ����
/*
	��ǻ� �ȼ����� ���� ����� �ܼ��� ���Ͽ� ��Ϻ� �����ϴ� �����
	���������� �� ��� x
	ȿ������ ��Ϻ� ���̱� ���ؼ� ���� �ȼ��� �� ���, ��ο� �ȼ��� �� ��Ӱ�
	�����ؾ���.
*/
void contrast1() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {
	
	contrast1();

	return 0;
}