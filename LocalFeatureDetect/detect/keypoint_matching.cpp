#include "opencv2/opencv.hpp"
#include <iostream>



void keypoint_matching()
{
	cv::Mat src1 = cv::imread("book.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src2 = cv::imread("book-in-scene.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		std::cerr << "Image load failed" << std::endl;
		return;
	}

	//	ORB 클래스 객체 생성
	cv::Ptr<cv::Feature2D> feature = cv::ORB::create();


	//	src1과 src2 영상에서 각각 특징점을 검출하고 기술자를 계산한다. 각 영상의 기술자는 desc1, desc2행렬에 저장됨.
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Mat desc1, desc2;
	feature->detectAndCompute(src1, cv::Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, cv::Mat(), keypoints2, desc2);

	//	BFMatcher 클래스 객체를 생성한다. 기술자 거리 계산 방식은 해밍거리를 사용(ORB를 사용하기 때문)
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING);

	//	desc1, desc2 기술자를 서로 매칭하여 그 결과를 matches에 저장.
	std::vector<cv::DMatch> matches;
	matcher->match(desc1, desc2, matches);


	//	matches 정보를 이용해 매칭 결과 영상 dst를 생성.
	cv::Mat dst;
	cv::drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);

	cv::imshow("dst", dst);

	cv::waitKey();
	cv::destroyAllWindows();
}


int main() {

	keypoint_matching();

	return 0;
}