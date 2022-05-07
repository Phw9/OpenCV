#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;


/*
FAST(Features from Accelerated Segment Test) 코너 검출 방법은 단순한 픽셀 값 비교 방법을 통해 코너를 검출

점 p에서의 밝기를 Ip라고 표현하고 t는 충분히 밝거나 어두운 정도를 조절하기 위한 임계값으로 정의하면
만약 주변 16개 픽셀 중에서 그 값이 Ip+t보다 큰 픽셀이 아홉 개 이상 연속으로 나타나면 점 p는 어두운 영역이
뾰족하게 돌출되어 있는 코너다. 반면에 주변 16개 픽셀 중에서 그 값이 Ip-t보다 작은 픽셀이 아홉개 이상 연속으로 나타나면
점 p는 밝은 영역이 돌출되어 있는 코너다.

FAST 방법은 특징 코너 점 주변 픽셀들도 함께 코너로 검출하는 경우가 많기 때문에 주변 코너 픽셀 중에서
가장 코너에 적합한 픽셀을 선택하는 비최대 억제 작업을 추가적으로 수행하는 것이 좋다.

FAST 방법에서는 코너 점과 주변 16개 점과의 픽셀 값 차이 합을 코너 점수로 정의하고, 인접한 코너 중에서 코너 점수가 가장 큰 코너만 최종 코너로 선택(비최대 억제)

FAST() 함수 input은 CV_8UC1 타입만 사용, keypoints 인자는 KeyPoint 클래스 객체의 벡터로 지정한다.
KeyPoint 클래스는 Point 타입의 멤버 변수 pt를 가지고 있어서 , 여기에 코너 점 좌표가 저장됨. 즉, FAST()함수에 의해 결정된 코너 점 중에서
i번째 코너의 x,y좌표는 keypoints[i].pt.x와 같이 코드로 접근이 가능함

*/

void corner_fast() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	vector<KeyPoint> keypoints;
	//	src 영상에서 FAST 방법으로 코너 점 검출. 밝기차이임계값은 60으로 지정, 마지막에 true인자로 비최대 억제 수행
	//	검출된 모든 코너 점 좌표는 keypoints 변수에 저장됨.
	FAST(src, keypoints, 60, true);	

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (KeyPoint kp : keypoints) {
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {

	corner_fast();

	return 0;
}