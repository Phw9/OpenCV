#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void labeling_basic() {
	uchar data[] = {
		// 0�� ����� ������, 1�� ��ü�� ���
		0,0,1,1,0,0,0,0,
		1,1,1,1,0,0,1,0,
		1,1,1,1,0,0,0,0,
		0,0,0,0,0,1,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,
	};
	//	255�� ���� ����ȭ�� ��Ŵ
	Mat src = Mat(8, 8, CV_8UC1, data) * 255;

	/*
	���̺� ���� labels ��Ŀ� �����ϰ� ���̺� ������ ��ȯ
	��ȯ���� N�̸� 0���� N-1������ ���̺� ��ȣ�� ����, �� �� 0�� ���̺��� ���
	���� ��ü���� N-1��
	*/
	Mat labels;
	int cnt = connectedComponents(src, labels);

	cout << "src:\n" << src << endl;
	cout << "labels:\n" << labels << endl;
	cout << "nuber of labels: " << cnt << endl;
}

int main() {

	labeling_basic();

	return 0;
}