#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
logical operation�� �ȼ� ���� �������� ǥ���Ͽ�
�� bit ���� �� ������ �����ϴ� ���� �ǹ�

	����(AND)		: �� ���� �Է� ��Ʈ�� ��� 1�� ���, ����� 1
	����(OR)		: �� ���� �Է� ��Ʈ �� �ϳ��� 1�� ���, ����� 1
��Ÿ�� ����(XOR)	: 1. �� ���� �Է� ��Ʈ �� ���� �ϳ��� 1�� ���, ����� 1
					  2. �Է� ��Ʈ�� ��� 0 �Ǵ� 1 �ΰ��, ����� 0
	����(NOT)		: 1. �ϳ��� �Է� ���� ���� �����ϸ� �Է� ��Ʈ�� 0�̸� ����� 1
					  2. 1�̸� ����� 0
*/

int main(void) {

	Mat src1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	/*
	bitwise �Լ���뵵 ������ OpenCV�� ������ �����ǵ� ������
	*/
	bitwise_and(src1, src2, dst1);	//	dst1 = src1 & src2;
	bitwise_or(src1, src2, dst2);	//	dst2 = src1 | src2;
	bitwise_xor(src1, src2, dst3);	//	dst1 = src1 ^ src2;
	bitwise_not(src1, dst4);	//	dst1 = ~src1;

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();

	destroyAllWindows();

	return 0;
}