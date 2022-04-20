#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void filter_embossing() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Imaga load failed" << endl;
		return;
	}

	float data[] = { -1,-1,0,-1,0,1,0,1,1 };

	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst1, dst2;
	//	���� ���� ��� ��ȭ ���꿡 ���� 0�� �ǰ� ��ü���� ũ�� �پ��� ������
	//	���͸� �����Ҷ����� ��� ���� 128�� ���ϴ°��� ���� ����
	//	Point(-1, -1)�� �״�� ������ ���� ����ũ �߾��� ���������� ���
	filter2D(src, dst1, -1, emboss, Point(-1, -1), 128);
	filter2D(src, dst2, -1, emboss, Point(-1, -1), 0);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}


int main(void) {

	filter_embossing();

	return 0;
}