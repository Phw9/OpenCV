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

	//	�� ������ Ư¡�� ��Ī ����� �����Ѵ�.
	std::sort(matches.begin(), matches.end());

	//	���ĵ� ��Ī ������� ���� 50�� ��Ī ����� good_matches�� ����
	std::vector<cv::DMatch> good_matches(matches.begin(), matches.begin() + 50);

	cv::Mat dst;

	//	good_matches�� �̿��� ��Ī ��� ������ ����. 10��° ���ڿ� DrawDrawMatchesFlags::NOT_DRAW_SINGLE_POINTS ����� ������ ��Ī���� ���� Ư¡���� ȭ�鿡 ǥ������ �ʴ´�.
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