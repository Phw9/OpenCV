#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mask_copyTo() {
	Mat src = imread("airplane.jpg", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);

	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	/* mask영상에서 흰색 영역 위치에서만 src 영상 픽셀값을 dst로 복사 */
	src.copyTo(dst, mask);	

	imshow("dst", dst);


	waitKey();
	destroyAllWindows();

}

int main(void) {

	mask_copyTo();
	return 0;

}
