#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void contours_basic() {
	Mat src = imread("mask.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src ������ ���̳ʸ� ��Ŵ
	threshold(src, src, 0, 255, THRESH_BINARY | THRESH_BINARY);

	/*
	contours ������ vector<vector<Point>> Ÿ���̰� �̴� vector<Point> Ÿ���� ������ ������ �� �ִ� Ÿ��
	�ܰ��� ��ü���� ���� contours[0], controus[1] ~~~ ���·� ���� ���� �� ��ü���� ��� vector<Point> Ÿ���̰�,
	���� �ε����� �ش��ϴ� �ܰ��� ������ ��ǥ�� �����ϰ� ����
	��ü ��ü ������ �˰�ʹٸ� contours.size() ��ȯ���� Ȯ��
	0�� �ܰ����� �� ������ �˰� �ʹٸ� contours[0].size() ��ȯ���� Ȯ��

	findContours() �Լ��� �Է� �������δ� ���� threshold() �� �Լ��� ���� ������� ���� ������ ���
	�Է� ���󿡼� �ȼ� ���� 0�� �ƴϸ� ��ü�� ������ �ܰ����� ����
	findContours() �Լ��� �ܰ������� ���� ������ �޾� ���� hierarchy ���ڰ� �ִ� ���¿� ���� ���� �� ������ ����
	
	hierarchy ���ڿ��� ����� �ܰ����� ���� ������ ����. ���� vector<Vec4i> Ÿ���� ������ ����
	Vec4i Ŭ������ int �ڷ��� �� ���� ������ �� �ִ� OpenCV ���� Ŭ����. i��° �ܰ����� ����
	hierarchy[i][0] : ���� �ܰ��� ��ȣ
	hierarchy[i][1] : ���� �ܰ��� ��ȣ
	hierarchy[i][2] : �ڽ� �ܰ��� ��ȣ
	hierarchy[i][3] : �θ� �ܰ��� ��ȣ
	���� ���� �������� �ش� �ܰ����� �������� ������ -1�� ����

	modes ���ڿ��� RetrievalModes ������ ��� �� �ϳ��� ����, �ֿ� RetrievalModes ������ ����� �ǹ̴� ������ ����.
	RETR_EXTERNAL	: ��ü �ٱ��� �ܰ����� �˻�. ���� ������ ������ �ʴ´�.
	RETR_LIST		: ��ü �ٱ��ʰ� ���� �ܰ����� ��� �˻�. ���� ������ ������ �ʴ´�.
	RETR_CCOMP		: ��� �ܰ����� �˻��ϰ� 2�ܰ� ���� ������ ���� (��� ��� ��ü�� �ٱ��� �ܰ����� ���� �����ϰ�, �� ��ü ���� Ȧ �ܰ����� �ڽ� �ܰ������� ����)
					  �׷��� RETR_CCOMP ��忡���� ���� ������ �ִ� �� �� �����θ� ����, ���� ��� ��ü�� ���� ���� Ȧ�� ������ ���, ���� ���� ����� �ܰ��� �ϳ��� �ڽ� �ܰ������� ����
					  �׸��� ������ Ȧ �ܰ����� ��ü �ٱ��� �ܰ����� ��� �θ� �ܰ������� ����
	RETR_TREE		: �ܰ��� ��ü�� ���� ������ ����, ���� ��ü ���ο� Ȧ�� �ְ�, �� Ȧ �ȿ� �� �ٸ� ���� ��ü�� �ִٸ�
					  ���� ��ü�� �ܰ����� Ȧ �ܰ����� �ڽ����� ����

	method ���ڿ��� ����� �ܰ��� ������ ��ǥ�� �ٻ�ȭ�ϴ� ����� ����
	ContourApproximationModes ������ ���
	CHAIN_APPROX_NONE		: ��� �ܰ��� ������ ��ǥ�� ����
	CHAIN_APPROX_SIMPLE		: �ܰ��� �߿��� ����, ������, �밢�� ������ ������ ����
	CHAIN_APPROX_TC89_L1	: Teh & Chin L1 �ٻ�ȭ�� ����
	CHAIN_APPROX_TC89_KCOS	: Teh & Chin k cos �ٻ�ȭ�� ����

	drawContours() �Լ��� findContours() �Լ��� ���� �ܰ��� ������ �̿��� ���� �ܰ����� �׸�
	��ü �ܰ����� �Ѳ����� �׸� ���� �ְ�, Ư�� ��ȣ�� �ܰ����� �����Ͽ� �׸� �� �� ����.
	�ܰ��� ���� ������ �Բ� ������ ���, �ڽ� �ܰ����� �Բ� �׸� �� ����.
	*/

	//	src �������� ���� ��� �ܰ����� �����ϰ� ���������� ����X
	vector<vector<Point>> contours;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//	����� ��ü �ܰ��� ������ contours.size()�� �� �� ������ 0���� �ݺ��ϸ� �ܰ����� �׸�
	for (int i = 0; i < contours.size(); i++) {
		// �ܰ��� ������ c�� �������� ����
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, i, c, 2);
	}

	//	��ü �ٱ��� �ܰ����� ���� Ȧ �ܰ����� ��� ������ �������� �׷���.
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();



}

int main() {

	contours_basic();

	return 0;
}