#include "opencv2/opencv.hpp"

#include <iostream>


using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);

	//	calcHist()�Լ� parameter ����
	Mat hist;								//	����� ������׷� ��ü ����

	int channels[] = { 0 };					//	������׷��� ���� ä���� ��Ÿ���� ������ �迭
											//	ä�� ��ȣ�� 0���� �����ϹǷ� channels �迭�� 0 �ϳ��� ���ҷ� ����

	int dims = 1;							//	����� ������׷� ���� ���� 1���� ���

	const int histSize[] = { 256 };			//	�� ������ ������׷� �迭 ũ�⸦ ��Ÿ���� �迭
											//	= �� ������ ������׷� �� ������ ��Ÿ���� �迭
											//	�Է� ������ ù ��° ä�� ���� ������ 256�� ������ ������ ������׷��� ���ϰڴٴ� �ǹ�


	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };	//	��� ������׷�(uniform = true(default��))�̸� ranges[i] �� ������
											//	�ּڰ��� �ִ����� ������ �迭��
											//	���� ������׷�(uniform = false)�̸� ranges[i]�� �� ������ ��Ÿ����
											//	histSize[i]+1���� ���ҷ� ������ �迭

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));		//	hist�� 256���� ������ ������ ������׷� ������� �˻�

	double histMax;
	minMaxLoc(hist, 0, &histMax);				//	hist ��� ������ �ִ��� ����

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));//	������� �ʱ�ȭ�� 256x100 ũ���� �� ���� imgHist ����

	/*
	������׷� ����׷����� �ִ� ���̴� 100�ȼ��� ����.
	�ִ� ��ġ����100�ȼ��� �ش��ϴ� ������ ������ �׸���,
	������ ������׷� ����׷����� 100�ȼ����� ª�� ������ �������� ǥ����
	*/
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;

}


/*

dst(x,y) = (src(x,y) - Gmin) / (Gmax - Gmin) * 255
Gmin�� �Է� ������ �ȼ��� �� ���� ���� grayscale ��

*/
void histogram_stretching() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	//	������׷� ��Ʈ��Ī ���� ������ ������� dst ����
	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

int main(void) {
	
	histogram_stretching();

	return 0;
}