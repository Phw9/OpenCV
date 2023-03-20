#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void contours_hier() {
	Mat src = imread("mask.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	findContours() 함수 호출 시 hierarchy 인자를 전달하여 계층 정보를 받아옴.
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	/*
	0번 외곽선부터 시작해 계층 정보의 다음 외곽선으로 이동하면서 for문을 수행
	drawContours() 함수에 hierarchy 정보를 전달하여 외곽선을 그림. 선의 두께를 -1로 지정해 외곽선 내부를 지정한 색깔로 채움.
	
	idx 초기값은 0이고 idx = hierarchy[idx][0] 코드를 이용해 idx 값이 갱신.
	여기서 hierarchy[idx][0]은 idx번에 해당하는 외곽선의 다음 외곽선 번호를 가리키는데
	다음 외곽선 번호가 -1이 되어 idx >= 0 조건을 만족하지 않으면 for 문을 빠져나옴.
	*/
	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();



}

int main() {

	contours_hier();

	return 0;
}