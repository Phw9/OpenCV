#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;



int main(void) {

	//ref.png로 부터 CrCb histogram을 계산한다.

	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);			//	피부색 히스토그램 정보를 추출할 기준 영상
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);	//	기준 영상에서 피부색이 있는 위치를 흰색으로 표시한 마스크 영상
													//	이 때 마스크 영상은 포토샵 같은 영상 편집툴을 이용해 미리 생성했음
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);		//	YCrCb 색 공간으로 변환

	//	기준 영상에서 피부색 영역의 CrCbv 2차원 히스토그램을 계산해 hist에 저장
	Mat hist;
	int channels[] = { 1,2 };						
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins,cb_bins };
	float cr_range[] = { 0,256 };
	float cb_range[] = { 0,256 };
	const float* ranges[] = { cr_range,cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

	//	input 영상에 히스토그램 역투영(histogram backprojection) 적용

	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	//	앞에서 구한 히스토그램 hist를 이용해 입력 영상에서 히스토그램 역투영 수행
	Mat backproj;
	//	calcBackProject() 함수가 반환하는 backproj 영상은 CV_8UC1 타입 이므로 imshow() 함수로 쉽게 출력
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

	imshow("src", src);
	imshow("backproj", backproj);
	waitKey();

	return 0;
}