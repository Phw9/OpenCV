#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;



int main(void) {

	//ref.png�� ���� CrCb histogram�� ����Ѵ�.

	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);			//	�Ǻλ� ������׷� ������ ������ ���� ����
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);	//	���� ���󿡼� �Ǻλ��� �ִ� ��ġ�� ������� ǥ���� ����ũ ����
													//	�� �� ����ũ ������ ���伥 ���� ���� �������� �̿��� �̸� ��������
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);		//	YCrCb �� �������� ��ȯ

	//	���� ���󿡼� �Ǻλ� ������ CrCbv 2���� ������׷��� ����� hist�� ����
	Mat hist;
	int channels[] = { 1,2 };						
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins,cb_bins };
	float cr_range[] = { 0,256 };
	float cb_range[] = { 0,256 };
	const float* ranges[] = { cr_range,cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	//	input ���� ������׷� ������(histogram backprojection) ����

	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	//	�տ��� ���� ������׷� hist�� �̿��� �Է� ���󿡼� ������׷� ������ ����
	Mat backproj;
	//	calcBackProject() �Լ��� ��ȯ�ϴ� backproj ������ CV_8UC1 Ÿ�� �̹Ƿ� imshow() �Լ��� ���� ���
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("src", src);
	imshow("backproj", backproj);
	waitKey();

	return 0;
}