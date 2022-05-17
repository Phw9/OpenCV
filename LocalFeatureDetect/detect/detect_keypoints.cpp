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
	Ptr Ŭ������ OpenCV���� ����ϴ� ����Ʈ ������ (smart pointer) Ŭ������.
	ORB Ŭ���� ��ü�� ������ feature ����Ʈ �����Ϳ� �����Ѵ�.
	*/
	Ptr<Feature2D> feature = ORB::create();

	//	ORB Ű����Ʈ�� ������ keypoints ���Ϳ� ����
	vector<KeyPoint> keypoints;
	feature->detect(src, keypoints);

	//	ORB Ű����Ʈ ����ڸ� ����� desc��Ŀ� ����
	Mat desc;
	feature->compute(src, keypoints, desc);

	cout << "keypoints.size(): " << keypoints.size() << endl;	// ����� keypoints ����
	cout << "desc.size(): " << desc.size() << endl;				// desc ��� ũ�⸦ �ܼ�â�� ���

	/*
	�Է� ���� src�� keypoint�� �׸� ����� dst�� ����. keypoint �׸��� �����
	DrawMatchesFlags::DRAW_RICH_KEYPOINTS�� ������ keypoint�� ��ġ, ũ��, ���� ������ �Բ� ��Ÿ������ ����
	DrawMatchesFlags ������ ���
	DEFAULT					: ����� ��� Ư¡���� ���� ũ���� ���� �׸���, ���� ��Ī�� Ư¡������ ������ �׸���.
	DRAW_OVER_OUTIMG		: ��� ������ ���� �������� �ʰ� ���޵� ���� ���� �׸���.
	NOT_DRAW_SINGLE_POINTS	: drawMatches() �Լ��� �Բ� ���Ǹ�, ��Ī���� ���� Ư¡���� �׸��� �ʴ´�.
	DRAW_RICH_KEYPOINTS		: Ű����Ʈ�� ũ��� ���� ������ �Բ� ��Ÿ���ϴ�.
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