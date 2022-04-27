#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
ħ��(erosion) ������ ��ü ������ �ܰ��� ���� ��� ���� �������� ��ü������
��ü ������ ��ҵǰ� ����� Ȯ����. ������Ҹ� ���� ��ü�� ���� ��ĵ�ϸ鼭, ���� ��Ұ�
��ü ���� ���ο� ������ ���Ե� ��� ������(anchor point) ��ġ �ȼ��� 255�� ����

��â(dilation) ������ ��ü �ܰ��� Ȯ���ϴ� ����. ��â ������ �����ϸ� ��ü ������
Ȯ��ǰ�, ��濵���� �پ��. ������Ҹ� ���� ��ü�� ���� �̵���Ű�鼭, ���� ��ҿ�
��ü ������ �� �ȼ��̶� ���� ��� ������ ��ġ �ȼ��� 255�� ����
*/

void erode_dilate() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src ���� ���� ���� �˰������� �ڵ� ����ȭ�� ����
	Mat binary;
	threshold(src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat dst1, dst2;
	/*
	����° ���ڷ� Mat()���� �� 3x3 ������ ������Ҹ� ��� �� ���� ������Ҵ�
	getStructuringElement()�Լ��� �̿��� ���� �� ����.
	*/
	erode(binary, dst1, Mat());	//	ħ�� ������ ����
	dilate(binary, dst2, Mat());//	��â ������ ����

	imshow("src", src);
	imshow("binary", binary);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	erode_dilate();

	return 0;
}