#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*	openCV 함수 중에는 그레이스케일 영상만을 or 컬려 영상만을 입력으로 받는
		함수가 있음. 그래서 채널이 맞는 영상을 입력해줘야하는데 이를 확인 하기 위해
		Mat::type() 멤버함수를 이용
*/
void func(Mat& img) {
	/*	OpenCV에서 제공하는 매크로 함수
		CV_Assert(expr)		디버그, 릴리스 모두 동작
		CV_DbgAssert(expr)	이건 디버그에서만 동작
		expr은 조건식

	*/
	//	그레이스케일이 아니면 에러가 발생하면서 프로그램 종료
	CV_Assert(img.type() == CV_8UC1);

	//	그레이스케일 영상 처리 수행
}


int main(void) {

	/*	두 번째 인자에 IMREAD_GRAYSCALE을 지정해 그레이스케일 형식으로 변환된
		영상이 img1 변수에 저장
	*/
	Mat img1 = imread("phw.jpg", IMREAD_GRAYSCALE);

	/*	프로그램 동작 중 그레이스케일 영상을 저장할 새로운 Mat 객체를 생성하려면
		CV_8UC1 타입의 객체를 생성해야함
	*/
	Mat img2(480, 640, CV_8UC1, Scalar(0));

	/*	만약 이미 3채널 컬러영상을 가지고 그레이스케일로 변환하려면 cvtColor()함수
		를 사용*/
	Mat img3 = imread("phw.jpg", IMREAD_COLOR);
	Mat img4;
	cvtColor(img3, img4, COLOR_BGR2GRAY);

	return 0;
}