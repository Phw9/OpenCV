#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void sobel_edge() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
	}

	/*
	x��, y�� �������� 1�� ��̺��� ���� ���Ͽ� dx�� dy ��Ŀ� ����
	dx, dy ����� float �ڷ����� ����ϵ��� ����
	*/
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat fmag, mag;
	
	/*
	dx, dy ��ķκ��� �׷����Ʈ ũ�⸦ ����� fmag�� ����
	���̴� dx,dy�� ���� �Ǽ� �ڷ������� ����
	*/
	magnitude(dx, dy, fmag);
	//	�Ǽ��� ��� fmag�� �׷��̽����� �������� ��ȯ�� ����
	fmag.convertTo(mag, CV_8UC1);
	
	/*
	���� �Ǻ��� ���� �׷����Ʈ ũ�� �Ӱ谪�� 150���� ����
	��� edge�� ���� ���� mag ��� ���� ���� 150���� ũ�� 255
	������ 0���� ������
	*/
	Mat edge = mag > 150;

	imshow("src", src);
	/*
	mage ������ �׷����Ʈ ũ�⸦ �׷��̽����� ���� �������� ��Ÿ�� ��
	���� �׷����Ʈ ũ�Ⱑ 255���� ū ��� ��ȭ���꿡 ���ؼ� ������� ǥ��
	*/
	imshow("mag", mag);

	/*
	edge ������ �׷����Ʈ ũ�Ⱑ 150���� ū �ȼ��� �������
	�׷��� ���� �ȼ��� ���������� ǥ���� ���� ����
	threshold�� 150���� ���� �����ϸ� �� ���� ���� �ȼ��� ��Ÿ������
	�ʹ� ���߸� ������ ���⵵ ������ ����� �� ����
	*/
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}


int main(void) {

	sobel_edge();

	return 0;
}