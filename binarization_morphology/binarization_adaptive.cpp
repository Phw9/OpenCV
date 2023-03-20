#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void on_trackbar(int pos, void* userdata);	// pos�� Ʈ���� ��ġ �� ��

int main(void) {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	//	������ ����ȭ�� ��� ũ�� ������ ���� Ʈ���� ����
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void*)&src);
	setTrackbarPos("Block Size", "dst", 11);	//	Ʈ���� �ʱ���ġ 11

	waitKey();
	destroyAllWindows();

	return 0;
}

void on_trackbar(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;

	int bsize = pos;
	if (bsize % 2 == 0) bsize--;	// bsize���� ¦���� Ȧ���� ����
	if (bsize < 3) bsize = 3;		// bsize�� �ּ� 3�̿�����

	Mat dst;

	/*
	Ʈ���ٿ��� ������ ��� ũ�⸦ �̿��� ������ ����ȭ�� ����
	����þ� ���� ����� ����ϰ�, ��� ��տ��� 5�� �� ���� �Ӱ谪���� ���
	*/
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

	imshow("dst", dst);

}

