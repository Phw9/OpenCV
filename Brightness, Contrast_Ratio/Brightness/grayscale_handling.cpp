#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*	openCV �Լ� �߿��� �׷��̽����� ������ or �÷� ������ �Է����� �޴�
		�Լ��� ����. �׷��� ä���� �´� ������ �Է�������ϴµ� �̸� Ȯ�� �ϱ� ����
		Mat::type() ����Լ��� �̿�
*/
void func(Mat& img) {
	/*	OpenCV���� �����ϴ� ��ũ�� �Լ�
		CV_Assert(expr)		�����, ������ ��� ����
		CV_DbgAssert(expr)	�̰� ����׿����� ����
		expr�� ���ǽ�

	*/
	//	�׷��̽������� �ƴϸ� ������ �߻��ϸ鼭 ���α׷� ����
	CV_Assert(img.type() == CV_8UC1);

	//	�׷��̽����� ���� ó�� ����
}


int main(void) {

	/*	�� ��° ���ڿ� IMREAD_GRAYSCALE�� ������ �׷��̽����� �������� ��ȯ��
		������ img1 ������ ����
	*/
	Mat img1 = imread("phw.jpg", IMREAD_GRAYSCALE);

	/*	���α׷� ���� �� �׷��̽����� ������ ������ ���ο� Mat ��ü�� �����Ϸ���
		CV_8UC1 Ÿ���� ��ü�� �����ؾ���
	*/
	Mat img2(480, 640, CV_8UC1, Scalar(0));

	/*	���� �̹� 3ä�� �÷������� ������ �׷��̽����Ϸ� ��ȯ�Ϸ��� cvtColor()�Լ�
		�� ���*/
	Mat img3 = imread("phw.jpg", IMREAD_COLOR);
	Mat img4;
	cvtColor(img3, img4, COLOR_BGR2GRAY);

	return 0;
}