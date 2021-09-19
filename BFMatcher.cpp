#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;


int main() {

    Mat img1 = imread("book.jpg", IMREAD_GRAYSCALE);
    Mat img2 = imread("book_in_scene.jpg", IMREAD_GRAYSCALE);
    if (img1.empty() || img2.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

    Ptr<Feature2D> feature = ORB::create(); //ORB ��ü ����

    vector<KeyPoint> keypoints1, keypoints2;

    /*  img1, img2 ���󿡼� ���� Ư¡���� �����ϰ� ����ڸ� ���
        �� ������ ����ڴ� desc1, desc2�� ����                 */
    Mat desc1, desc2;

    feature->detectAndCompute(img1, Mat(), keypoints1, desc1);
    feature->detectAndCompute(img2, Mat(), keypoints2, desc2);

    // img1,2 �� ����� feature ��
    cout << "img1 - " << keypoints1.size() << " features, "
        << "img2 - " << keypoints2.size() << " features" << endl;

    // BFMatcher ��ü ����, desc �Ÿ� ��� ����� �عְŸ��� �̿�
    Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

    vector<DMatch> matches; // ��Ī��� ������ ���� DMatch ��ü ����
    matcher->match(desc1, desc2, matches, noArray());

    // ��Ī ����� ���Ľ�Ų �� distance�� ���� ���� 50�� ��Ī ����� ����
    std::sort(matches.begin(), matches.end());
    vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

    // DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS ����� ���� �� ��Ī���� ����
    // Ư¡���� ȭ�鿡 ǥ������ ����
    Mat dst;
    drawMatches(img1, keypoints1, img2, keypoints2, good_matches, dst,
        Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    //good_matches ��Ī ����� ����� query,train IDX�� pts1,pts2�� ����
    vector<Point2f> pts1, pts2;
    for (size_t i = 0; i < good_matches.size(); i++) {
        pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
        pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
    }
    // pts1�� pts2�� �̵��ϴ� ȣ��׷��� ����� ���� H�� ����
    // RANdom SAmple Consunsus �˰����� �̿�
    Mat H = findHomography(pts1, pts2, RANSAC);


    // img1 ������ �� �𼭸� ���� corners1�� ���� �� ȣ��׷��� ����� �̿���
    // �̵��� ��ġ�� ��� �� corners2�� ����
    vector<Point2f> corners1, corners2;
    corners1.push_back(Point2f(0, 0));
    corners1.push_back(Point2f(img1.cols - 1.f, 0));
    corners1.push_back(Point2f(img1.cols - 1.f, img1.rows - 1.f));
    corners1.push_back(Point2f(0, img1.rows - 1.f));
    perspectiveTransform(corners1, corners2, H);


    // ���� dst�� corner2 �� ��ġ��ǥ�� corners_dst�� ����
    vector<Point> corners_dst;
    for (Point2f pt : corners2) {
        corners_dst.push_back(Point(cvRound(pt.x + img1.cols), cvRound(pt.y)));
    }

    polylines(dst, corners_dst, true, Scalar(255, 0, 0), 1, LINE_AA);

    namedWindow("dst", WINDOW_NORMAL);
    imshow("dst", dst);
    waitKey();
    destroyAllWindows();


    return 0;
}
