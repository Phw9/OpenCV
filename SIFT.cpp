#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;


static double timer()
{
    return getTickCount() / getTickFrequency();
}

int main(int argc, char** argv)
{
    
    Mat img1 = imread("book.jpg", IMREAD_GRAYSCALE);
    Mat img2 = imread("book_in_scene.jpg", IMREAD_GRAYSCALE);
    if (img1.empty() || img2.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

     /*
    img1, img2 영상에서 각각 특징점을 검출하고 기술자를 계산
    각 영상의 기술자는 desc1, desc2에 저장
    */
    vector<KeyPoint> keypoints1, keypoints2;
    Ptr<DescriptorMatcher> matcher; 
    
    matcher = DescriptorMatcher::create("FlannBased");  // BFMatching에 비해 상대적으로 빠른 동작
    int maxlines = 50; //매칭된 키포인트를 그려줄 최대 직선 개수 
    cout << "extracting with " << "SIFT" << "..." << endl;
    Ptr<SIFT> ext = SIFT::create(); // SIFT 객체 생성, Norm_L2

    Mat desc1, desc2;   // 영상에서 추출한 특징점 기술자 행렬

    ext->detectAndCompute(img1, Mat(), keypoints1, desc1);
    ext->detectAndCompute(img2, Mat(), keypoints2, desc2);
    
    // img1,2 의 검출된 feature 수
    cout << "img1 - " << keypoints1.size() << " features, "
        << "img2 - " << keypoints2.size() << " features" << endl;

    cout << "matching with " << "Flann" << "..." << endl;
    
    double start = timer();

    // match and draw
    vector< vector<DMatch> > rawMatches; // 매칭결과벡터
    vector<Point2f> p1, p2; // p1 = img1의 질의 기술자 index, p2 = img2의 훈련 기술자 index
    vector<float> distances;
    matcher->knnMatch(desc1, desc2, rawMatches, 2); // Flannbased라서 knn 매칭을 적용해봄

    // filter_matches
    for (size_t i = 0; i < rawMatches.size(); i++)
    {
        const vector<DMatch>& m = rawMatches[i];
        if (m.size() == 2 && m[0].distance < m[1].distance * 0.75)
        {
            p1.push_back(keypoints1[m[0].queryIdx].pt);
            p2.push_back(keypoints2[m[0].trainIdx].pt);
            distances.push_back(m[0].distance);
        }
    }
    return 0;
}