#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void blurring_gaussian() {

	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	/*
	sigma(ǥ������)�� Ŭ���� blurring�� �� ���̵�
	sigmaX, sigmaY�� �� ���������� ����þ� Ŀ�� ǥ�� �����ε�
	sigmaY = 0 �̸� sigmaX�� ���� ���� ���
	��� 0�̸� ksize�� width�� height �����κ��� ǥ�� ������ ����� ���
	
	*/

	for (int sigma = 1; sigma <= 5; sigma++) {
		GaussianBlur(src, dst, Size(), (double)sigma);
		String text = format("sigma=%d", sigma);
		putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}
int main(void) {

	blurring_gaussian();

	return 0;
}

/*

getGaussianKernel() �Լ��� ǥ�� ������ sigma�� 1���� ����þ� ����
�Լ��κ��� (ksize x 1) ũ���� ���� ����ũ ����� ������ ��ȯ
ksize�� ((8 x sigma) + 1)���� ���ų� ũ�� �����ϴ� ���� ����

getGaussianKernel() �Լ��� ksize ���� 7���� ���ų� �۰� sigma ����
0 �Ǵ� ������ ��쿡�� ������ ���� �̸� ���� ���� �迭 ���� �̿��� Ŀ�� ����� ����

static const float small_gaussian_tab[][7] =
{
	{ 1.f },
	{ 0.25f, 0.5f, 0.25f },
	{ 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f },
	{ 0.03125f, 0.109375f, 0.21875f, 0.28125f, 0.21875f, 0.109375f, 0.03125f }
};

*/