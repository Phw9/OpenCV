#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*	
	��ȭ ������ �����ϴ� saturate_cast()��� �̸��� ĳ���� �Լ��� ������.
	���ø� �Լ��� ���ǵǾ� ������ �׷��� ������ ���� ���� ���� ���Ǵ� ������
	
	template<> inline uchar saturate_cast<uchar>(int v);
	
	v�� int �ڷ����� ǥ���� �� �ִ� ������ ����
	��ȯ���� 0~255������ ����
*/

/*	
	���� ����ó�� �� ���� �ϳ��� �����ϴ� �ͺ��� openCV���� �����ϴ� ���� ������
	�����Ǹ� ����Ͽ� �ڵ带 �ۼ��ϴ� ���� ���� ������ ����.
	OpenCV���� �����ϴ� �Լ��� ����ϸ� CPU ����ȭ �� ���� ó���� �����ϱ� ������
	������ �����ϰ�, �ҽ� �ڵ� �������� ���� ��, �ٸ� ��ǻ�� ���� ������Ʈ�� �����ϴ�
	���� OpenCV���� �������� �ʴ� ���ο� ����� ���� �����ؾ� �ϴ� ��찡 �߻��ϱ�
	������ ������ �ȼ� ���� ���� �����ϰ� �����ϴ� ����� �ݵ�� ����ϰ� �־����.
	���Ҿ� ��ȭ ������ ���� saturate_cast()�Լ� ������ ����.
*/

// ��ȭ ������ ����� �������
void brightness3() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	// ��ȭ ������ ����� �ݺ����� ����ٸ� ���� ���� �����ڸ� �̿�
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			int v = src.at<uchar>(j, i) + 100;
			dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}


int main(void) {

	brightness3();
	
	return 0;
}