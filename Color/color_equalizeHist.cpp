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

	//	BGR 색공간의 src 영상을 YCrCb 색 공간으로 변경해 src_ycrcb 객체에 저장
	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	//	src_ycrcb 영상의 채널을 분리해서 ycrcb_planes에 저장
	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);

	//	Y 성분에 해당하는 ycrcb_planes[0] 영상에 대해서만 히스토그램 평활화를 수행
	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);	// Y channel

	//	ycrcb_planes 벡터에 들어 있는 세 영상을 합쳐서 dst_ycrcb 영상을 생성
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);

	//	dst_ycrcb 영상의 색 공간을 BGR 색 공간으로 변환해 dst에 저장
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}