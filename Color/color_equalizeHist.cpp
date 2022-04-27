#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(void) {
	Mat src = imread("phw.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	//	BGR �������� src ������ YCrCb �� �������� ������ src_ycrcb ��ü�� ����
	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	//	src_ycrcb ������ ä���� �и��ؼ� ycrcb_planes�� ����
	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);

	//	Y ���п� �ش��ϴ� ycrcb_planes[0] ���� ���ؼ��� ������׷� ��Ȱȭ�� ����
	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);	// Y channel

	//	ycrcb_planes ���Ϳ� ��� �ִ� �� ������ ���ļ� dst_ycrcb ������ ����
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);

	//	dst_ycrcb ������ �� ������ BGR �� �������� ��ȯ�� dst�� ����
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}