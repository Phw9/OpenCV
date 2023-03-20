#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void detect_keypoints()
{
	Mat src = imread("book_in_scene.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	/*
	Ptr 클래스는 OpenCV에서 사용하는 스마트 포인터 (smart pointer) 클래스다.
	ORB 클래스 객체를 생성해 feature 스마트 포인터에 저장한다.
	*/
	Ptr<Feature2D> feature = ORB::create();

	//	ORB 키포인트를 검출해 keypoints 벡터에 저장
	vector<KeyPoint> keypoints;
	feature->detect(src, keypoints);

	//	ORB 키포인트 기술자를 계산해 desc행렬에 저장
	Mat desc;
	feature->compute(src, keypoints, desc);

	cout << "keypoints.size(): " << keypoints.size() << endl;	// 저장된 keypoints 개수
	cout << "desc.size(): " << desc.size() << endl;				// desc 행렬 크기를 콘솔창에 출력

	/*
	입력 영상 src에 keypoint를 그린 결과를 dst에 저장. keypoint 그리는 방식은
	DrawMatchesFlags::DRAW_RICH_KEYPOINTS로 지정해 keypoint의 위치, 크기, 방향 정보를 함께 나타내도록 설정
	DrawMatchesFlags 열거형 상수
	DEFAULT					: 검출된 모든 특징점에 작은 크기의 원을 그리고, 서로 매칭된 특징점끼리 직선을 그린다.
	DRAW_OVER_OUTIMG		: 출력 영상을 새로 생성하지 않고 전달된 영상 위에 그린다.
	NOT_DRAW_SINGLE_POINTS	: drawMatches() 함수와 함께 사용되며, 매칭되지 않은 특징점은 그리지 않는다.
	DRAW_RICH_KEYPOINTS		: 키포인트의 크기와 방향 정보를 함께 나타냅니다.
	*/

	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

}

int main() {

	detect_keypoints();

	return 0;
}