#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
	��ȭ������ ������ ȿ������ ��Ϻ� ���� ����
	dst(x,y) = saturate(src(x,y) + (src(x,y)-128)*��)
	�� ���Ŀ��� ��� -1���� ���ų� ū �Ǽ�.
	-1<=��<=0�̸� ���Ⱑ 0���� 1 ������ ������ �Ǹ� ��Ϻ� ���ҽ�Ŵ
	��>0�̸� ���Ⱑ 1���� ū ������ �������̸� ��Ϻ� ������Ű�� ��ȯ �Լ�
*/
void contrast2() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	contrast2();

	return 0;
}