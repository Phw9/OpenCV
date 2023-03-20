#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);

	//	calcHist()함수 parameter 생성
	Mat hist;								//	출력할 히스토그램 객체 생성

	int channels[] = { 0 };					//	히스토그램을 구할 채널을 나타내는 정수형 배열
											//	채널 번호는 0부터 시작하므로 channels 배열은 0 하나만 원소로 가짐

	int dims = 1;							//	출력할 히스토그램 차원 수가 1차원 행렬

	const int histSize[] = { 256 };			//	각 차원의 히스토그램 배열 크기를 나타내는 배열
											//	= 각 차원의 히스토그램 빈 개수를 나타내는 배열
											//	입력 영상의 첫 번째 채널 값의 범위를 256개 빈으로 나누어 히스토그램을 구하겠다는 의미


	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };	//	등간격 히스토그램(uniform = true(default값))이면 ranges[i] 각 차원의
											//	최솟값과 최댓값으로 구성된 배열임
											//	비등간격 히스토그램(uniform = false)이면 ranges[i]는 각 구역을 나타내는
											//	histSize[i]+1개의 원소로 구성된 배열

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);
	
	return hist;
}

Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));		//	hist가 256개의 빈으로 구성된 히스토그램 행렬인지 검사

	double histMax;
	minMaxLoc(hist, 0, &histMax);				//	hist 행렬 원소의 최댓값을 저장

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));//	흰색으로 초기화된 256x100 크기의 새 영상 imgHist 생성

	/*	
	히스토그램 막대그래프의 최대 길이는 100픽셀로 설정.
	최댓값 위치에서100픽셀에 해당하는 검은색 직선을 그리고,
	나머지 히스토그램 막대그래프는 100픽셀보다 짧은 길이의 직선으로 표현됨
	*/
	for (int i = 0; i < 256; i++) {
	line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
}

	return imgHist;

}

int main(void) {

	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);
	Mat hist = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);
	
	//	만약 단순 히스토그램 그래프 영상을 화면에 출력하는 것이 목적이면 변수 선언 불필요

	// imshow("hist", getGrayHistImage(calcGrayHist(src)));

	imshow("phw", src);
	imshow("hist", hist_img);
	
	waitKey();
	destroyAllWindows();

	return 0;
}

// C/C++ 문법을 이용한 그레이스케일 영상의 히스토그램 구하기
void getCppHist(const Mat& src) {

	int hist[256] = { 0, };
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			hist[src.at<uchar>(j, i)]++;
		}
	}
}