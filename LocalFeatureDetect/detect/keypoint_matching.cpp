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

	//	ORB Ŭ���� ��ü ����
	cv::Ptr<cv::Feature2D> feature = cv::ORB::create();


	//	src1�� src2 ���󿡼� ���� Ư¡���� �����ϰ� ����ڸ� ����Ѵ�. �� ������ ����ڴ� desc1, desc2��Ŀ� �����.
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Mat desc1, desc2;
	feature->detectAndCompute(src1, cv::Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, cv::Mat(), keypoints2, desc2);

	//	BFMatcher Ŭ���� ��ü�� �����Ѵ�. ����� �Ÿ� ��� ����� �عְŸ��� ���(ORB�� ����ϱ� ����)
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING);

	//	desc1, desc2 ����ڸ� ���� ��Ī�Ͽ� �� ����� matches�� ����.
	std::vector<cv::DMatch> matches;
	matcher->match(desc1, desc2, matches);


	//	matches ������ �̿��� ��Ī ��� ���� dst�� ����.
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