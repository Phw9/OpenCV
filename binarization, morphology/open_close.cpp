#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
���� ������ �Է� ���� ���� ħ�� ������ ������ �� �ٽ� ��â ������ ����
�ݱ� ������ �Է� ���� ���� ��â ������ ������ �� �ٽ� ħ�� ������ ����

���� ������ ħ�� ������ ���� �����ϱ� ������ �ѵ� �ȼ�¥�� ������ ���ŵ� ��, ��â ������ ����
�� ��� �Է� ���� ���� �����ϴ� ���� ũ���� ��ü�� ȿ�������� ���ŵ�.

�ݱ� ������ ��â ������ ���� �����ϱ� ������ ��ü ������ ���� ������ �޿��� ��, ħ�� ������ ����
��������� �ݱ� ������ ��ü ������ ���� ������ ���ŵ�.

OpenCV���� �������� ����� �ݱ� ������ morphologyEx() �Լ��� �̿���.
����� �ݱ�Ӹ� �ƴ϶� ħ�İ� ��â ���� �Ϲ����� �������� ���굵 ������ �� �ִ�
�������� �������� ���� �Լ�
morphologyEx()�� �� ��° ���� op�� �������� ���� ����� ������. ������ ��� ��
MORPH_GRADIENT ����� ��â ��� ���󿡼� ħ�� ��� ������ ���� ������ �����ϸ�,
��ü�� �ܰ����� ����Ǵ� ȿ���� ����.{ dst = dilate(src, element) - erode(src, element) }
*/

void open_close() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src ���� ���� ���� �˰������� �ڵ� ����ȭ�� ����
	Mat binary;
	threshold(src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	/*
	���� ������ ���� ������ erode() dilate() �Լ��� ����Ͽ� ���� ���� ����
	Mat dst;
	erode(src, dst, Mat());
	dilate(dst, dst, Mat());

	���� ������ �ݱ� ������
	Mat dst;
	dilate(src, dst, Mat());
	erode(dst, dst, Mat());

	������ morphologyEx() �Լ� ���ο����� �̿� ���� ������ �����.
	*/
	Mat dst1, dst2;
	morphologyEx(src, dst1, MORPH_OPEN, Mat());	//	MORPH_OPEN�� ���� ����
	morphologyEx(src, dst2, MORPH_CLOSE, Mat());//	MORPH_CLOSE�� �ݱ� ����

	imshow("src", src);
	imshow("binary", binary);
	imshow("open", dst1);
	imshow("close", dst2);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	open_close();

	return 0;
}