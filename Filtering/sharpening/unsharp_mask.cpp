#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

void unsharp_mask() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	imshow("src", src);

	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

		float alpha = 1.f;
		/*
		가우시안 필터를 이용한 블러링 영상으로 언샤프 마스크 필터링을 수행
		h(x,y) = f(x,y) + α * g(x,y)
			   = f(x,y) + α(f(x,y) - blur(x,y))
			   = (1+α)*f(x,y) - α * blur(x,y)
		*/
		Mat dst = (1 + alpha) * src - alpha * blurred;

		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();

}


int main(void) {

	unsharp_mask();

	return 0;
}