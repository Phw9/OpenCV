#include "opencv2/opencv.hpp"
#include <iostream>


void good_matching()
{
	cv::Mat src1 = imread("book.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src2 = imread("book-in-scene.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		std::cerr << "Image load failed" << std::endl;
		return;
	}

	cv::Ptr<cv::Feature2D> feature = cv::ORB::create();

	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Mat desc1, desc2;

	feature->detectAndCompute(src1, cv::Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, cv::Mat(), keypoints2, desc2);

	cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING);


	std::vector<cv::DMatch> matches;
	matcher->match(desc1, desc2, matches);

	//	두 영상의 특징점 매칭 결과를 정렬한다.
	std::sort(matches.begin(), matches.end());

	//	정렬된 매칭 결과에서 상위 50개 매칭 결과를 good_matches에 저장
	std::vector<cv::DMatch> good_matches(matches.begin(), matches.begin() + 50);

	cv::Mat dst;

	//	good_matches를 이용해 매칭 결과 영상을 생성. 10번째 인자에 DrawDrawMatchesFlags::NOT_DRAW_SINGLE_POINTS 상수를 지정해 매칭되지 않은 특징점은 화면에 표시하지 않는다.
	cv::drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst, cv::Scalar::all(-1),
		cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	cv::imshow("dst", dst);

	cv::waitKey();
	cv::destroyAllWindows();
}


int main() {

	good_matching();

	return 0;
}