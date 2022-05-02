#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//	img 영상에서 pts 외곽선 주변에 바운딩 박스를 그린다. label 문자열을 출력 한다.
void setLabel(Mat& img, const vector<Point>& pts, const String& label) {
	Rect rc = boundingRect(pts);											//	pts 외곽선을 감싸는 바운딩 박스를 구함
	rectangle(img, rc, Scalar(0, 0, 255), 1);								//	바운딩 박스를 주황색으로 표시
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));	//	바운딩 박스 좌상단에 label 문자열을 출력
}

int main() {
	Mat img = imread("polygon.bmp", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	//	영상 이진화를 위해 GRAY로 변환
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//	오츠 알고리즘으로 자동 이진화하여 bin에 저장
	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	//	bin 영상에서 모든 객체의 바깥쪽 외곽선을 검출
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);


	
	//	검출된 각 객체의 외곽선 좌표를 pts 변수로 참조하며 for문 수행
	for (vector<Point>& pts : contours) {
		if (contourArea(pts) < 400)	//	외곽선이 감싸는 면적이 400보다 작으면 무시
			continue;
		/*
		pts 외곽선을 근사화해 approx에 저장
		더글라스-포이커(DP: Douglas-Peucker) 알고리즘을 사용해 곡선 또는 다각형을 단순화
		1. 입력 외곽선에서 가장 멀리 떨어져 있는 두 점을 찾아 직선으로 연결
		2. 해당 직선에서 가장 멀리 떨어져 있는 외곽선 상의 점을 찾아 근사화 점으로 추가
		3. 1,2 를 반복하다 2의 거리가 epsilon 인자보다 작으면 근사화를 멈춤
		4. epsilon 인자는 보통 입력 외곽선 또는 곡선 길이의 일정 비율(arcLength(curve, true) * 0.02)로 지정
		*/
		vector<Point> approx;	
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

		//	approx에 저장된 외곽선 점의 개수를 vtc에 저장
		int vtc = (int)approx.size();

		/*
		근사화된 외곽선의 꼭지점 개수가 3이면 외곽선 주변에 바운딩 박스를 그리고 "TRI" 문자열을 출력 (삼각형)
		근사화된 외곽선의 꼭지점 개수가 4이면 외곽선 주변에 바운딩 박스를 그리고 "RECT" 문자열을 출력 (사각형)
		
		객체의 면적대 길이 비율을 조사해 원에 가까우면 외곽선 주변에 바운딩 박스를 그리고 "CIR" 문자열을 출력 (원)
		도형의 면적 비율(R): R = (4 * PI * Area) / Len^2
		이 수식으로 구한 비율 R은 0에서 1 사이의 실수로 계산되며, 입력 도형이 원 모양에 가까울수록 1에 가까운 값을 가짐
		*/
		if (vtc == 3) {
			setLabel(img, pts, "TRI");
		}
		else if (vtc == 4){
			setLabel(img, pts, "RECT");
		}
		else if (vtc > 4) {
			double len = arcLength(pts, true);	//	총 길이를 구함 (폐곡선임)
			//	oriented의 default는 false 이고 면적의 절댓값을 반환, true면 곡선의 진행 방향에 따라 면적의 부호가 달라짐.
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);

			if (ratio > 0.8) {
				setLabel(img, pts, "CIRCLE");
			}
		}
	}

	imshow("img", img);
	waitKey();
	destroyAllWindows();

	return 0;
}