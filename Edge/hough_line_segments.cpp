#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

/*
Ȯ���� ���� ��ȯ ���� ����
HoughLinesP() �Լ����� ����� ���� ������ ����Ǵ� lines ���ڿ���
���� vector<Vec4i> �ڷ��� ������ ����
������ ���� ������ Vec4i �ڷ������� ����ǰ�, �ϳ��� Vec4i ��ü����
���� �������� x,y ��ǥ,  ���� ������ x,y ��ǥ�� ����
maxLineGap ���ڴ� ���������� ������ ���� �� �������� ������ ���� ��,
�� ������ �ϳ��� �������� �����ϰ��� �� �� ���
*/

void hough_line_segments() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat edge;
	Canny(src, edge, 50, 150);	// ĳ���Լ��� ��������

	//	HoughLinesP()�� �̿��� ��� ���� ������ �������� ���� ��ǥ�� ���Ѵ�
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

	//	������ ��Ÿ���� ���� ���������� 3ä�� �÷��������� ����
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	/*
	HoughLinesP()�� ���� ������ ��� ���� ������ dst ���� ���� �׸�
	l[0], l[1]�� ���� ������ x, y
	l[2], l[3]�� ���� ���� x, y
	
	C + 11�� ���� ��� for �ݺ���(range - based for loop) ������ ���
	vetor �Ǵ� �迭 � ����Ǿ� �ִ� ��� ���Ҹ� �ϳ��� ������
	����� �� ���� ����
	*/
	
	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	hough_line_segments();

	return 0;
}