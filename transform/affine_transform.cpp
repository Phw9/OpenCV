#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

/*
입력 영상의 좌표 (x,y)가 결과 영상의 좌표 (x',y')로 이동하는 수식은
x' = f1(x,y) = ax + by + c
y' = f2(x,y) = dx + ey + f

이를 행렬로 표현하면

{ {x'}, {y'} } = { { a,b,c }, { d,e,f } } * { {x}, {y}, {1} } 

M = { { a,b,c }, { d,e,f } }를 어파인 변환 행렬(affine tranformation matrix)
이라고 한다.

*/

/*
이동 변환(translation transformation)
: 가로 또는 세로 방향으로 일정 크기만큼 이동
x' = x + a
y' = y + b
M = { { 1,0,a }, { 0,1,b } }
*/
void affine_translation() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// 3-Channel image를 가로로 150, 세로로 100 픽셀 이동
	Mat M = Mat_<double>({ 2,3 }, { 1,0,150,0,1,100 });

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/*
전단 변환(shear transformation)
: 직사각형 형태의 영상을 한쪽 방향으로 밀어서 평행사변형 모양으로 변형
x' = x + (mx)*y
y' = y
M = { { 1,mx,0 }, { 0,1,0 } }
or
x' = x
y' = (my)*x + y
M = { { 1,0,0 }, { my,1,0 } }
*/
void affine_shear() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	double mx = 0.3;
	Mat M = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 });

	Mat dst;
	// M으로 어파인 변환을 수행하고 전단 변화에 ㅡ이해 입력 영상의 일부가 잘리지 않게
	// 가로 크기를 늘렸음
	warpAffine(src, dst, M, Size(cvRound(src.cols+src.rows*mx),src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
/*
크기 변환(scale transformation)
: 영상의 전체적인 크기를 확대 또는 축소하는 변환
x' = (sx)*x
y' = (sy)*y
M = { { sx,0,0 }, { 0,sy,0 } }
resize() 함수 이용
*/
void affine_scale() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	Mat dst1, dst2, dst3, dst4;
	// src 영상을 x,y 방향으로 각각 4배 확대해 dst1 생성, 최근방 이웃 보간법 사용
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	// src 영상을 1920x1280 크기로 확대해 dst2 생성, 양선형 보간법(default값)
	resize(src, dst2, Size(1920, 1280));
	// src 영상을 1920x1280 크기로 확대해 dst3 생성, 3차 회선 보간법
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	// src 영상을 1920x1280 크기로 확대해 dst4 생성, 란초스 보간법
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	
	imshow("src", src);
	// 확대변환 결과 영상은 (40,50) 좌표부터 400x400 크기의 부분 영상을 화면에 출력
	/*imshow("dst1", dst1(Rect(400, 500, 400, 400)));*/
	imshow("dst1", dst1(Rect(40, 50, 400, 400)));
	imshow("dst2", dst2(Rect(40, 50, 400, 400)));
	imshow("dst3", dst3(Rect(40, 50, 400, 400)));
	imshow("dst4", dst4(Rect(40, 50, 400, 400)));
	imshow("dst11", dst1);

	waitKey();
	destroyAllWindows();
}

/*
회전 변환(rotation transformation)
: 영상 처리 시스템을 개발하다보면 입력 영상을 회전해야 하는 경우가 종종 있음
 (ex. OCR 시스템에서 글씨 영상의 수평이 맞아야 인식률이 증가하므로 문서의 회전 각도를 측정)
x' = (cos(theta))*x + (sin(theta))*y
y' = -(sin(theta))*x + (cos(theta))*y
M = { { cos(theta),sin(theta),0 }, { -sin(theta),cos(theta),0 } }
resize() 함수 이용
*/
void affine_rotation() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	
	// 영상의 중심 좌표를 가리키는 변수 cp 선언
	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	// cp 좌표를 기준으로 반시계 방향 20˚ 회전하는 변환 행렬 M 생성
	Mat M = getRotationMatrix2D(cp, 20, 1);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
/*
대칭 변환(flip transformation)
: 영상의 좌우를 서로 바꾸거나 상하를 뒤집는 형태의 변환
x' = w-1-x
y' = y
M = { { -1,0,w-1 }, { 0,1,0 } }
or
x' = x
y' = h-1-y
M = { { 1,0,0 }, { 0,-1,h-1 } }
resize() 함수 이용
*/
void affine_flip() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1,0,-1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipCode[i]);
		
		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);


		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

void affine_transform() {
	Mat src = imread("phw.jpg");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat M = getAffineTransform(srcPts, dstPts);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {
	affine_translation();
	affine_shear();
	affine_scale();
	affine_rotation();
	affine_flip();
	affine_transform();
	return 0;
}