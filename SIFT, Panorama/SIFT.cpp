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
    img1, img2 ���󿡼� ���� Ư¡���� �����ϰ� ����ڸ� ���
    �� ������ ����ڴ� desc1, desc2�� ����
    */
    vector<KeyPoint> keypoints1, keypoints2;
    Ptr<DescriptorMatcher> matcher; 
    
    matcher = DescriptorMatcher::create("FlannBased");  // BFMatching�� ���� ��������� ���� ����
    int maxlines = 50; //��Ī�� Ű����Ʈ�� �׷��� �ִ� ���� ���� 
    cout << "extracting with " << "SIFT" << "..." << endl;
    Ptr<SIFT> ext = SIFT::create(); // SIFT ��ü ����, Norm_L2

    Mat desc1, desc2;   // ���󿡼� ������ Ư¡�� ����� ���

    ext->detectAndCompute(img1, Mat(), keypoints1, desc1);
    ext->detectAndCompute(img2, Mat(), keypoints2, desc2);
    
    // img1,2 �� ����� feature ��
    cout << "img1 - " << keypoints1.size() << " features, "
        << "img2 - " << keypoints2.size() << " features" << endl;

    cout << "matching with " << "Flann" << "..." << endl;
    
    double start = timer();

    // match and draw
    vector< vector<DMatch> > rawMatches; // ��Ī�������
    vector<Point2f> p1, p2; // p1 = img1�� ���� ����� index, p2 = img2�� �Ʒ� ����� index
    vector<float> distances;
    matcher->knnMatch(desc1, desc2, rawMatches, 2); // Flannbased�� knn ��Ī�� �����غ�

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