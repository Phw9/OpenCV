#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void canny_edge() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);

	Mat dx, dy;
	//	입력 영상의 x방향, y방향의 미분방향을 만들어 캐니에지 검출에 이용
	//	깊이는 CV_16SC1 or CV_16SC3
	Sobel(src, dx, CV_16SC1, 1, 0);
	Sobel(src, dy, CV_16SC1, 0, 1);

	Canny(dx, dy, dst3, 50, 100);	//	임계점은 낮은것, 높은것 순으로 지정
	Canny(dx, dy, dst4, 50, 150);

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);

	waitKey();
	destroyAllWindows();
}


int main(void) {

	canny_edge();

	return 0;
}