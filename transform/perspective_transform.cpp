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
	// 마우스 눌린 횟수를 저장할 변수
	static int cnt = 0;

	if (event == EVENT_LBUTTONDOWN) {
		if (cnt < 4) {
			// 버튼을 누르면 srcQuad 배열에 좌표 저장
			/*
					2	1
					3	4 순으로 찍어야 원하는 모양을 입/출력한다.
			*/
			srcQuad[cnt++] = Point2f(x, y);

			circle(src, Point(x, y), 2, Scalar(0, 0, 255), -1);

			imshow("src", src);

			// 마우스 버튼이 4번 눌러지면 if문 실행
			if (cnt == 4) {
				// 투시변환해서 만들 결과 영상 크기
				int w = 200, h = 300;

				dstQuad[0] = Point2f(0, 0);
				dstQuad[1] = Point2f(w - 1, 0);
				dstQuad[2] = Point2f(w - 1, h - 1);
				dstQuad[3] = Point2f(0, h - 1);

				// (3x3)투시변환행렬을 얻음
				Mat M = getPerspectiveTransform(srcQuad, dstQuad);

				Mat dst;
				// 투시변환 수행 (wxh)크기의 결과영상 dst 생성
				warpPerspective(src, dst, M, Size(w, h));

				imshow("dst", dst);
			}
		}
	}
}

/*
투시변환 행렬을 가지고 있을 때 일부 점들이 투시변환에
의해 어느 위치로 이동할것인지 알고 싶으면 이 함수를 이용

void perspectiveTransform(InputArray src, OutputArray dst, InputArray m);
*/