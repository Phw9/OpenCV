#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
���� ��ȯ �� ����
(x-a)^2 + (y-b)^2 = r^2
������ a,b,r �� ���� �Ķ���͸� ������ �����Ƿ�, ���� ��ȯ�� �״�� �����Ϸ���
3���� �Ķ���� �������� ���� �迭�� �����ϰ� ���� ������ ���� ��ġ�� ã�ƾ� ������
�ʹ� ���� �޸𸮿� ���� �ð��� �ʿ�� �ϰ� �ǹǷ� ���� �׷����Ʈ ����� ����� ���� ����
*/
void hough_circles() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	������ �����ϱ� ����
	Mat blurred;
	blur(src, blurred, Size(3, 3));

	/*
	circles ���ڿ��� ���� vector<Vec3f> or vector<Vec4f> �ڷ��� ���� ����
	Vec3f�� �߽���ǥ(a,b), ������ r �� ���ʴ�� ����
	Vec4f�� �߰������� ���� �迭 ���� ���� ����
	
	dp ���ڴ� ����� ���� �迭�� ũ�⸦ ����
	dp ���ڸ� 1�� �����ϸ� �Է� ����� ���� ũ���� ���� �迭�� ���
	2�� �����ϸ� �Է� ������ ���ο� ���� ũ�⸦ 2�� ���� ũ���� ���� �迭�� ���
	
	minDist ���ڿ��� ������ ���� �ּ� �Ÿ��� ���� ��, �� ���� �߽��� ����
	�Ÿ��� mindDist���� ������ �� ���� �ϳ��� ����X
	
	param1 ���ڴ� HoughCircles() �Լ� ���ο��� ĳ�� ���� ����⸦ �̿��� �� ����
	�Ӱ谪����, ���� �Ӱ谪�� param1�� �������� ����.
	
	param2�� ���� �迭���� ���� �߽��� ã�� �� ����ϴ� �Ӱ谪
	
	minRadius�� maxRadius ���ڿ� ������ ���� �ּ� �������� �ִ�������� �����ϴµ�
	���� ���󿡼� ������ ���� �뷫���� ũ�⸦ �˰��ִٸ� ������ ������ ���� �ӵ��� ����Ŵ
	*/
	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	hough_circles();

	return 0;
}