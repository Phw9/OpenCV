#include "opencv2/opencv.hpp"
#include <iostream>

void find_homography()
{
	cv::Mat src1 = imread("book.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src2 = imread("book-in-scene.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		std::cerr << "Image load failed" << std::endl;
		return;
	}

	cv::Ptr<cv::Feature2D> orb = cv::ORB::create();

	std::vector<cv::KeyPoint> keypoints1, keypoints2;

	cv::Mat desc1, desc2;
	orb->detectAndCompute(src1, cv::Mat(), keypoints1, desc1);
	orb->detectAndCompute(src2, cv::Mat(), keypoints2, desc2);

	cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING);

	std::vector<cv::DMatch> matches;
	matcher->match(desc1, desc2, matches);

	std::sort(matches.begin(), matches.end());
	std::vector<cv::DMatch> good_matches(matches.begin(), matches.begin() + 50);

	cv::Mat dst;
	cv::drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst,
		cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(),
		cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//	good_matches ��Ī ����� ����� query ����� train ������ Ư¡�� ��ǥ�� �����Ͽ� vector<Point2f> Ÿ���� ���� pts1, pts2�� �����Ѵ�.
	std::vector<cv::Point2f> pts1, pts2;
	for (size_t i = 0; i < good_matches.size(); i++) {
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}
	//	pts1 ������ pts2 ����� �̵��ϴ� ȣ��׷��� ����� ���Ͽ� H�� �����Ѵ�. ȣ��׷��� ��� ����� RANSAC �˰����� ����Ѵ�.
	cv::Mat H = cv::findHomography(pts1, pts2, cv::RANSAC);

	/*
	src1 ����(�츮�� ���ϴ� ��ü)�� �� �𼭸� ���� corners1�� ������ ��, ȣ��׷��� ��� H�� �̿��Ͽ� �� ������ �̵��ϴ� ��ġ�� ����Ͽ� corners2�� �����Ѵ�.
	*/

	std::vector<cv::Point2f> corners1, corners2;
	corners1.push_back(cv::Point2f(0, 0));
	corners1.push_back(cv::Point2f(src1.cols - 1.f, 0));
	corners1.push_back(cv::Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(cv::Point2f(0, src1.rows - 1.f));
	cv::perspectiveTransform(corners1, corners2, H);

	// ��Ī ��� ���� dst���� corner2 ������ ��ġ�ϴ� ��ǥ�� corner_dst�� �����Ѵ�.
	
	std::vector<cv::Point> corners_dst;
	for (cv::Point2f pt : corners2) {
		corners_dst.push_back(cv::Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
	}

	// ��Ī ��� ���� dst���� src1�� �ִ� ��ġ�� ��� �簢������ �׸���.
	cv::polylines(dst, corners_dst, true, cv::Scalar(0, 255, 0), 2, cv::LineTypes::LINE_AA);

	imshow("dst", dst);

	cv::waitKey();
	cv::destroyAllWindows();
}


int main() {

	find_homography();

	return 0;
}