#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
HSV �� �������� inRange() �Լ��� �̿��� ����ڰ� ������ ���� ���� ���� ���
�̷��� ����� ��, ��, ��, �� ������ ����� ������ ã�⿡ ȿ����
����� �Ǻλ�ó�� �̼��� ��ȭ�� �ְų� ���� ���� ��ġ������ �����ϱ� ����� ���� ������
*/

//	�� ���� Ʈ���� ��ġ�� ������ lower_hue, upper_hue�� ���� ������ ����
int lower_hue = 40, upper_hue = 80;

//	main�Լ��� Ʈ���� �ݹ� �Լ� on_hue_changed() �Լ����� �Բ� ����� Mat��ü ����
Mat src, src_hsv, mask;

void on_hue_changed(int, void*);

int main(int argc, char* argv[]) {
	src = imread("candies.png", IMREAD_COLOR);
	
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	//	src ������ HSV �� �������� ��ȯ�� src_hsv�� ����
	cvtColor(src, src_hsv, COLOR_BGR2HSV);

	imshow("src", src);

	namedWindow("mask");
	/*
	������ ���� ���� ���� ���� ������ �� �ִ� �� ���� Ʈ���� ����
	������ �ִ��� 179�� �����ϰ�, �� Ʈ������ �ݹ� �Լ��� ���
	on_hue_changed() �Լ��� ����
	*/
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	
	//	���α׷��� ó�� ����� �� ������ ���������� ��µǵ��� Ʈ���� �ݹ��Լ��� ����ȣ��
	on_hue_changed(0, 0);

	waitKey();
	return 0;
}

void on_hue_changed(int, void*) {
	Scalar lowerb(lower_hue, 100, 0);	//	�ּ� ����(Hue), ä��(Saturation) = 100, ��(Value) = 0
	Scalar upperb(upper_hue, 255, 255);	//	�ִ� H, S = 255, V = 255

	//	����ڰ� ������ ���� �� ������ �ش��ϴ� ������ ��� �� �ܴ� ���������� ǥ���� ����ũ ����
	inRange(src_hsv, lowerb, upperb, mask);

	imshow("mask", mask);
}