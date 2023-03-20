#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
	포화연산을 포함한 효과적인 명암비 조절 수식
	dst(x,y) = saturate(src(x,y) + (src(x,y)-128)*α)
	이 수식에서 α는 -1보다 같거나 큰 실수.
	-1<=α<=0이면 기울기가 0부터 1 사이의 직선이 되며 명암비를 감소시킴
	α>0이면 기울기가 1보다 큰 직선의 방정식이며 명암비를 증가시키는 변환 함수
*/
void contrast2() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {

	contrast2();

	return 0;
}