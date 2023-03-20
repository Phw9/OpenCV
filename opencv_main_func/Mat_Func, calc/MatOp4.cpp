#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void MatOp4() {
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);	// �����


	/*
	Mat::at() �Լ��� ���� �������� ��� ���� ���� ���
	��� ���� ��Ÿ���� �� ���� ������ ���ڷ� �޾� �ش� ��ġ�� ��� ���Ұ���
	���� �������� ��ȯ
	
	template<typename _Tp> _Tp& Mat::at(int y, int x)
	y�� ������ �� ��ȣ, x�� ������ �� ��ȣ
	��ȯ�� (_Tp& Ÿ������ �� ��ȯ��) y��° ��, x��° ���� ���� ��(����)

	*/
	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++;
		}
	}
	cout << "Mat1:\n " << mat1 << endl;

	/*
	Mat::ptr() �Լ��� Mat ��Ŀ��� Ư�� ���� ù ��° ���� �ּҸ� ��ȯ

	template<typename _Tp> _Tp* Mat::ptr(int y)
	y�� ������ �� ��ȣ
	��ȯ�� (_Tp* Ÿ������ �� ��ȯ��) y��° ���� ���� �ּ�
	*/

	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	}

	cout << "Mat1:\n " << mat1 << endl;

	/*
	MatIterator_ �ݺ��ڴ� �Լ� ���� ���޷� �� ���� ����� ũ�⸦ ����� �ʾ� �����߻��� ����
	Mat ��� ���� ������ ���� �ݺ��� ������ ����� ��� ũ�⿡ ������� ��� ��ü���Ҹ� ���ʴ�� ����
	Mat::begin() �Լ��� �̿��� ����� ù ��° ���� ��ġ�� ���, Mat::end() �Լ��� �̿��� ������ ����
	�ٷ� ���� ��ġ�� ���� �� ����
	MatIterator_<uchar> Ÿ���� ���� it�� �����ϰ�, mat1.begin<uchar>() �Լ��� ��ȯ������ �ʱ�ȭ
	it ���� mat1.end<uchar>()�� ������ ������ ��ġ�� ������Ű�鼭, �ش� ��ġ ���� ���� 1�� ����
	�̶� �ݺ��� ���� it�� ����Ű�� ���� ���� �����ϱ����� (*it) ���·� �ڵ��ۼ�

	����: ��ü�� ���� ������ ���� �ӵ� �鿡�� ������, ������ ��ġ�� �����Ӱ� ������ �Ұ���

	*/

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}

	waitKey();
	destroyAllWindows();
}

int main() {

	MatOp4();

	return 0;
}