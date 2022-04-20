#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void blurring_mean() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	Mat dst;
	/*
	3x3, 5x5, 7x7 filter를 이용해 blur를 해봄
	filter 크기가 클수록 영상이 더욱 부드럽게 변경됨
	filter 행렬은 (1 / (ksize x ksize)) * (1로 이루어진 (ksize x ksize) 행렬)

	filter mask 행렬은 원소합이 1 또는 0이 되도록 설계하는 이유는
	결과 영상의 평균 밝기가 입력 영상 평균 밝기와 같게 유지되기 때문
	원소합이 1보다 작으면 어두운 영상을, 크면 밝은 형태의 영상이 생성

	*/
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));

		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

int main(void) {

	blurring_mean();

	return 0;
}