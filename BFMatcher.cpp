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

    Ptr<Feature2D> feature = ORB::create(); //ORB 객체 생성

    vector<KeyPoint> keypoints1, keypoints2;

    /*  img1, img2 영상에서 각각 특징점을 검출하고 기술자를 계산
        각 영상의 기술자는 desc1, desc2에 저장                 */
    Mat desc1, desc2;

    feature->detectAndCompute(img1, Mat(), keypoints1, desc1);
    feature->detectAndCompute(img2, Mat(), keypoints2, desc2);

    // img1,2 의 검출된 feature 수
    cout << "img1 - " << keypoints1.size() << " features, "
        << "img2 - " << keypoints2.size() << " features" << endl;

    // BFMatcher 객체 생성, desc 거리 계산 방식은 해밍거리를 이용
    Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

    vector<DMatch> matches; // 매칭결과 저장을 위해 DMatch 객체 생성
    matcher->match(desc1, desc2, matches, noArray());

    // 매칭 결과를 정렬시킨 후 distance가 작은 상위 50개 매칭 결과를 저장
    std::sort(matches.begin(), matches.end());
    vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

    // DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS 상수를 지정 해 매칭되지 않은
    // 특징점은 화면에 표시하지 않음
    Mat dst;
    drawMatches(img1, keypoints1, img2, keypoints2, good_matches, dst,
        Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    //good_matches 매칭 결과에 저장된 query,train IDX를 pts1,pts2에 저장
    vector<Point2f> pts1, pts2;
    for (size_t i = 0; i < good_matches.size(); i++) {
        pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
        pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
    }
    // pts1이 pts2로 이동하는 호모그래피 행렬을 구해 H에 저장
    // RANdom SAmple Consunsus 알고리즘을 이용
    Mat H = findHomography(pts1, pts2, RANSAC);


    // img1 영상의 네 모서리 점을 corners1에 저장 후 호모그래피 행렬을 이용해
    // 이동한 위치를 계산 후 corners2에 저장
    vector<Point2f> corners1, corners2;
    corners1.push_back(Point2f(0, 0));
    corners1.push_back(Point2f(img1.cols - 1.f, 0));
    corners1.push_back(Point2f(img1.cols - 1.f, img1.rows - 1.f));
    corners1.push_back(Point2f(0, img1.rows - 1.f));
    perspectiveTransform(corners1, corners2, H);


    // 영상 dst에 corner2 의 위치좌표를 corners_dst에 저장
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
