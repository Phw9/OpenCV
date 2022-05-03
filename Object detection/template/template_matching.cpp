#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
템플릿 매칭은 알고리즘 특성상 입력 영상이 회전되거나 크기가 변경되면 제대로 동작하지 않음.
찾고자 하는 템플릿 영상이 다른 객체에 의해 겨려져도 좋은 맻이 결과를 기대하기 어려움
*/

/*
템플릿 영상을 입력 영상 전체 영역에 대해 이동하며 템플릿 영상과 입력 영상 부분 영상과의 유사도 또는 비유사도(dissimilarity)를 계산
유사도를 계산할 경우 템플릿 영상과 비슷한 부분 영상 위치에서 값이 크게 나타나고,
비유사도를 계산할 경우에 템플릿 영상과 비슷한 부분에서 값이 작게 나타남.
유사도로 계산했을 경우 가장 밝은 픽셀 위치가 템플릿 영상과 가장 유사한 부분
비유사도로 계산했을 경우 가장 어두운 픽셀 위치가 템플릿 영상과 가장 유사한 부분

유사도 맵, 비유사도 맵은 result(res) 인자로 반환.
Image 영상 크기가 WxH, templ 영상 크기가 wxh인 경우
result 행렬의 크기는 (W-w+1)x(H-h+1)로 결정

method 인자에는 TemplateMatchModes 열거형 상수 중 하나를 지정
TM_SQDIFF	: 제곱차(squared difference)매칭 방법. 비교할 두 영상이 완벽하게 일치하면 0, 서로 유사하지 않으면 0보다 큰 양수
TM_CCORR	: 상관관계(correlation)매칭 방법. 비교할 두 영상이 유사하면 큰 양수가 나오고 유사하지 않으면 작은 값.
TM_CCOEFF	: 상관계수(correlation coefficient) 매칭 방법. 비교할 두 영상을 미리 평균 밝기로 보정한 후 상관관계 매칭을 수행. 영상이 유사하면 큰 양수, 아니면 0에 가까운 양수 또는 음수.

위의 방법에 대해 각각 영상의 밝기 차이 영향을 줄여주는 정규화 수식이 추가된
TM_SQDIFF_NORMED, TM_CCORR_NORMED, TM_CCOEFF_NORMED 방법도 있음.
TM_CCORR_NORMED	: 매칭 결괏값이 0에서 1 사이의 실수
TM_CCOEFF_NORMED: 매칭 결괏값이 -1에서 1 사이의 실수
두 방법 모두 결괏값이 1에 가까울수록 매칭이 잘 되었음을 의미

TM_CCOEFF_NORMED 방법이 좋은 결과를 제공하지만 계산 수식이 가장 복잡하기 때문에 실제 동작 시 연산량이 많음

TM_SQDIFF는 result 결과 행렬에서 최솟값 위치가 가장 매칭이 잘된 위치
TM_CCORR, TM_CCOEFF는 result 결과 행렬에서 최댓값 위치가 가장 매칭이 잘된 위치
최대/최소값 위치는 OpenCV의 minMaxLoc() 함수를 이용해서 알아낸다.
*/

void template_matching() {
	Mat img = imread("circuit.bmp", IMREAD_COLOR);	//	입력 영상 (8비트 또는 32비트 실수형)
	Mat templ = imread("crystal.bmp", IMREAD_COLOR);	//	템플릿 영상 (입력 영상보다 같거나 작아야 하고 타입은 같아야함)

	if (img.empty() || templ.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	실제 영상 획득 과정에서 발생할 수 있는 조명의 영향을 시뮬레이션 하기 위해 입력 영상 밝기를 50만큼 증가
	img = img + Scalar(50, 50, 50);

	//	실제 영상 획득 과정에서 발생할 수 있는 잡음의 영향을 시뮬레이션 하기 위해 입력 영상에 표준 편차가 10인 가우시안 잡음 추가
	Mat noise(img.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);

	/*
	res는 -1부터 1 사이의 실수
	res_norm은 0부터 255 사이의 정수 범위로 정규화한 결과
	*/
	Mat res, res_norm;
	//	정규화된 상관계수 매칭방법을 사용해 템플릿 매칭, res에는 result행렬이 저장됨
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
	//	템플릿 매칭 결과 행렬 res의 모든 원소 값을 0~255 사이로 정규화하고, 타입을 CV_8UC1로 변환해 res_norm에 저장
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

	//	res 행렬에서 최댓값 위치를 찾아 maxloc에 저장. 이 위치에서의 최댓값 maxv는 템플릿 매칭이 잘 되었는지를 가늠하는 척도로 사용
	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv: " << maxv << endl;

	//	템플릿 매칭으로 찾은 위치를 빨간색 사각형으로 표시
	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);

	waitKey();
	destroyAllWindows();
}

int main() {

	template_matching();

	return 0;
}