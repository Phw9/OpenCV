#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

Mat src;

Point2f srcQuad[4], dstQuad[4];

void on_mouse(int event, int x, int y, int flags, void* userdata);


int main(void) {

	src = imread("phw.jpg");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	namedWindow("src");
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*) {
	// ���콺 ���� Ƚ���� ������ ����
	static int cnt = 0;

	if (event == EVENT_LBUTTONDOWN) {
		if (cnt < 4) {
			// ��ư�� ������ srcQuad �迭�� ��ǥ ����
			/*
					2	1
					3	4 ������ ���� ���ϴ� ����� ��/����Ѵ�.
			*/
			srcQuad[cnt++] = Point2f(x, y);

			circle(src, Point(x, y), 2, Scalar(0, 0, 255), -1);

			imshow("src", src);

			// ���콺 ��ư�� 4�� �������� if�� ����
			if (cnt == 4) {
				// ���ú�ȯ�ؼ� ���� ��� ���� ũ��
				int w = 200, h = 300;

				dstQuad[0] = Point2f(0, 0);
				dstQuad[1] = Point2f(w - 1, 0);
				dstQuad[2] = Point2f(w - 1, h - 1);
				dstQuad[3] = Point2f(0, h - 1);

				// (3x3)���ú�ȯ����� ����
				Mat M = getPerspectiveTransform(srcQuad, dstQuad);

				Mat dst;
				// ���ú�ȯ ���� (wxh)ũ���� ������� dst ����
				warpPerspective(src, dst, M, Size(w, h));

				imshow("dst", dst);
			}
		}
	}
}

/*
���ú�ȯ ����� ������ ���� �� �Ϻ� ������ ���ú�ȯ��
���� ��� ��ġ�� �̵��Ұ����� �˰� ������ �� �Լ��� �̿�

void perspectiveTransform(InputArray src, OutputArray dst, InputArray m);
*/