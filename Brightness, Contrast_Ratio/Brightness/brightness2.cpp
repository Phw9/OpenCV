#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//	��ȭ ������ ������� ���� ������ ��� ����
void brightness2() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	/*	unsigned char a =256; cout << "a = " << a << endl; �� ����ϸ� a=0��
		��µȴ�. �� ������ C/C++�� unsigned char �ڷ����� 1����Ʈ �޸� ������
		����ϰ� 0~255������ ���� ���� ������ �� ����. �׷��� ���� a�� 256�� ����
		�Ϸ��� �ϸ� �ڵ����� 0���� ��ȯ�� �����.
		�� �� �ڼ��� �����ϸ� ���� 256�� 16������ ǥ���ϸ� 0x00000100�̰�, �� ����
		unsigned char �ڷ����� �����Ϸ��� �ϸ� ���� 1����Ʈ�� ���ԵǱ� ������ ����
		a���� 0x00�� �����.
		257�� 0x00000101�̹Ƿ� 0x01�̿��� 1�� �����
	*/
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();

	

	

}


int main(void) {

	brightness2();

	return 0;
}