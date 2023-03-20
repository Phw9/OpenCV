#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void contours_basic() {
	Mat src = imread("mask.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src 영상을 바이너리 시킴
	threshold(src, src, 0, 255, THRESH_BINARY | THRESH_BINARY);

	/*
	contours 변수는 vector<vector<Point>> 타입이고 이는 vector<Point> 타입을 여러개 포함할 수 있는 타입
	외곽선 객체들은 각각 contours[0], controus[1] ~~~ 형태로 접근 가능 이 객체들은 모두 vector<Point> 타입이고,
	각각 인덱스는 해당하는 외곽선 점들의 좌표를 저장하고 있음
	전체 객체 개수를 알고싶다면 contours.size() 반환값을 확인
	0번 외곽선의 점 개수를 알고 싶다면 contours[0].size() 반환값을 확인

	findContours() 함수의 입력 영상으로는 보통 threshold() 등 함수에 의해 만들어진 이진 영상을 사용
	입력 영상에서 픽셀 값이 0이 아니면 객체로 간주해 외곽선을 검출
	findContours() 함수는 외곽선들의 계층 정보를 받아 오는 hierarchy 인자가 있는 형태와 없는 형태 두 가지로 정의
	
	hierarchy 인자에는 검출된 외곽선의 계층 정보가 저장. 보통 vector<Vec4i> 타입의 변수를 지정
	Vec4i 클래스는 int 자료형 네 개를 저장할 수 있는 OpenCV 벡터 클래스. i번째 외곽선에 대해
	hierarchy[i][0] : 다음 외곽선 번호
	hierarchy[i][1] : 이전 외곽선 번호
	hierarchy[i][2] : 자식 외곽선 번호
	hierarchy[i][3] : 부모 외곽선 번호
	만약 계층 구조에서 해당 외곽선이 존재하지 않으면 -1이 저장

	modes 인자에는 RetrievalModes 열거형 상수 중 하나를 지정, 주요 RetrievalModes 열거형 상수와 의미는 다음과 같다.
	RETR_EXTERNAL	: 객체 바깥쪽 외곽선만 검색. 계층 구조는 만들지 않는다.
	RETR_LIST		: 객체 바깥쪽과 안쪽 외곽선을 모두 검색. 계층 구조는 만들지 않는다.
	RETR_CCOMP		: 모든 외곽선을 검색하고 2단계 계층 구조를 구성 (모든 흰색 객체의 바깥쪽 외곽선을 먼저 검출하고, 각 객체 안의 홀 외곽선을 자식 외곽선으로 설정)
					  그래서 RETR_CCOMP 모드에서는 상하 계층이 최대 두 개 층으로만 구성, 만약 흰색 객체에 여러 개의 홀이 존재할 경우, 그중 제일 가까운 외곽선 하나만 자식 외곽선으로 설정
					  그리고 각각의 홀 외곽선은 객체 바깥쪽 외곽선을 모두 부모 외곽선으로 설정
	RETR_TREE		: 외곽선 전체의 계층 구조를 생성, 만약 객체 내부에 홀이 있고, 그 홀 안에 또 다른 작은 객체가 있다면
					  작은 객체의 외곽선은 홀 외곽선의 자식으로 설정

	method 인자에는 검출된 외곽선 점들의 좌표를 근사화하는 방법을 지정
	ContourApproximationModes 열거형 상수
	CHAIN_APPROX_NONE		: 모든 외곽선 점들의 좌표를 저장
	CHAIN_APPROX_SIMPLE		: 외곽선 중에서 수평선, 수직선, 대각선 성분은 끝점만 저장
	CHAIN_APPROX_TC89_L1	: Teh & Chin L1 근사화를 적용
	CHAIN_APPROX_TC89_KCOS	: Teh & Chin k cos 근사화를 적용

	drawContours() 함수는 findContours() 함수로 얻은 외곽선 정보를 이용해 영상에 외곽선을 그림
	전체 외곽선을 한꺼번에 그릴 수도 있고, 특정 번호의 외곽선을 선택하여 그릴 수 도 있음.
	외곽선 계층 정보를 함께 지정할 경우, 자식 외곽선도 함께 그릴 수 있음.
	*/

	//	src 영상으로 부터 모든 외곽선을 검출하고 계층정보는 추출X
	vector<vector<Point>> contours;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//	검출된 전체 외곽선 개수는 contours.size()로 알 수 있으며 0부터 반복하며 외곽선을 그림
	for (int i = 0; i < contours.size(); i++) {
		// 외곽선 색상을 c에 랜덤으로 저장
		Scalar c(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, i, c, 2);
	}

	//	객체 바깥쪽 외곽선과 안쪽 홀 외곽선이 모두 임의의 색상으로 그려짐.
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();



}

int main() {

	contours_basic();

	return 0;
}