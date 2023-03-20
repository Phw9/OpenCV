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

	//	good_matches 매칭 결과에 저장된 query 영상과 train 영상의 특징점 좌표를 추출하여 vector<Point2f> 타입의 변수 pts1, pts2에 저장한다.
	std::vector<cv::Point2f> pts1, pts2;
	for (size_t i = 0; i < good_matches.size(); i++) {
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}
	//	pts1 점들이 pts2 점들로 이동하는 호모그래피 행렬을 구하여 H에 저장한다. 호모그래피 계산 방법은 RANSAC 알고리즘을 사용한다.
	cv::Mat H = cv::findHomography(pts1, pts2, cv::RANSAC);

	/*
	src1 영상(우리가 원하는 객체)의 네 모서리 점을 corners1에 저장한 후, 호모그래피 행렬 H를 이용하여 이 점들이 이동하는 위치를 계산하여 corners2에 저장한다.
	*/

	std::vector<cv::Point2f> corners1, corners2;
	corners1.push_back(cv::Point2f(0, 0));
	corners1.push_back(cv::Point2f(src1.cols - 1.f, 0));
	corners1.push_back(cv::Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(cv::Point2f(0, src1.rows - 1.f));
	cv::perspectiveTransform(corners1, corners2, H);

	// 매칭 결과 영상 dst에서 corner2 점들이 위치하는 좌표를 corner_dst에 저장한다.
	
	std::vector<cv::Point> corners_dst;
	for (cv::Point2f pt : corners2) {
		corners_dst.push_back(cv::Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
	}

	// 매칭 결과 영상 dst에서 src1가 있는 위치를 녹색 사각형으로 그린다.
	cv::polylines(dst, corners_dst, true, cv::Scalar(0, 255, 0), 2, cv::LineTypes::LINE_AA);

	imshow("dst", dst);

	cv::waitKey();
	cv::destroyAllWindows();
}


int main() {

	find_homography();

	return 0;
}