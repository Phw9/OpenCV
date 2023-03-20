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
	//	음수 값은 모두 포화 연산에 의해 0이 되고 입체감이 크게 줄어들어 엠보싱
	//	필터를 구현할때에는 결과 영상에 128을 더하는것이 보이 좋음
	//	Point(-1, -1)을 그대로 지정해 필터 마스크 중앙을 고정점으로 사용
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