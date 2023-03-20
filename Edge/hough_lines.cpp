#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void hough_lines() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat edge;
	//	���������� ����
	Canny(src, edge, 50, 150);
	
	/*
		x * cos(theta) + y * sin(theta) = ��
	*/

	//	�����迭���� ��� 1�ȼ� ������, �ȴ� 1�� ������ ó��
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);	// threshold�� 250���� ����

	//	grayscale ������ edge�� BGR 3ä�� �÷� �������� ��ȯ�� dst ����
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	
	/*
	HoughLines() �Լ��� ���� ������ ������ ������ŭ for �ݺ��� ����
	������ ������ �Ķ���� �� �� ���� r��, �ȸ� ���� t�� ����
	x0�� y0�� �������� ������ ������ ������ �� ������ ���� ��ǥ
	pt1�� pt2���� (x0, y0)���� ����� �ָ� ������ �ִ� �������� �� �� ��ǥ�� ����
	line()�Լ��� ����� ������ �β��� 2�� ������ �Ǽ����� �׸�
	alpha�� ������ ����� �ָ� �������ְ� �ϱ����� weighted
	*/
	
	for (size_t i = 0; i < lines.size(); i++) {
		float r = lines[i][0], t = lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255),2,LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	hough_lines();
	return 0;
}