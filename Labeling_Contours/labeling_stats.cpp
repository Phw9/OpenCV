#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void labeling_stats() {
	Mat src = imread("mask.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	//	src ������ ���� �˰������� ����ȭ���� bin�� ����
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	/*
	bin ���� ���� ���̺��� �����ϰ� �� ��ü ������ ��� ������ ����
	
	labels�� ���̺��
	
	stats�� CV_32SC1 Ÿ���� ���. �� ������ ���̺� ������ ����, �� ������ �׻� 5
	ù ��° ���� ��� ���� ����, �� ��° ����ʹ� 1������ �����ϴ� ��ü ���� ����
	�� ���� ���ʴ�� Ư�� ������ ���δ� �ٿ�� �ڽ���
	x ��ǥ, y ��ǥ, ����ũ��(width), ����ũ��(height), ����(�ش� ������ �ȼ� ����)�� ��� ����.
	RectŬ����ó�� �»��(LU) ��ǥ�� �ڽ� ũ�� + ������ ��Ҵٰ� �����ϸ� ��.

	centroids�� �� ������ ���̺� ������ ���� �� ������ �׻� 2
	�� ���� ���ʴ�� �� ������ ���� �߽� x��ǥ, y��ǥ�� �������.
	�̴� ������ ��ü�� x��ǥ�� y��ǥ�� ��� ���� �� �ȼ� ������ ���� ��

	��ȯ��(N)�� ���̺� ���� ���� ��ü ������ N-1
	*/
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	//	���̺��� ���� src ������ 3ä�� �÷� ���� �������� ��ȯ
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//	��� ������ �����ϰ� ��� ��ü ������ ���ؼ��� for���� ����
	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);

		//	��ü�� �ȼ� ������ 20���� ������ �����̶�� �����ϰ� ����
		if (p[4] < 20) continue;

		//	����� ��ü�� ���δ� �ٿ�� �ڽ��� ��������� �׸�
		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {

	labeling_stats();

	return 0;
}