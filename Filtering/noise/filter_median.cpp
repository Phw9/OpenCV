#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void filter_median() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	Mat salt_pep = src.clone();

	if (src.empty() || salt_pep.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	int num = (int)(salt_pep.total() * 0.1);	// �Է� ���� ��ü ũ���� 10%
	for (int i = 0; i < num; i++) {
		int x = rand() % salt_pep.cols;
		int y = rand() % salt_pep.rows;
		salt_pep.at<uchar>(y, x) = (i % 2) * 255; // �Է� ���� �ȼ��� �ұ�&���� ���� �߰�
	}

	Mat dst1;
	GaussianBlur(salt_pep, dst1, Size(), 1);	// S&P noise�� gaussian ���͸�

	Mat dst2;
	medianBlur(salt_pep, dst2, 3);				// S&P noise�� median ���͸�

	Mat dst3;
	medianBlur(src, dst3, 3);					// ������ median ���͸� 

	imshow("src", src);
	imshow("S&P", salt_pep);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);

	waitKey();

	destroyAllWindows();
}

int main(void) {

	filter_median();

	return 0;
}