#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void Sum_Mean_Func() {
	Mat img = imread("phw.jpg", IMREAD_GRAYSCALE);

	cout << "Sum: " << (int)sum(img)[0] << endl;		// �ڷ����� Scalar�� [0]�� ù��° ���Ұ�
	cout << "Mean: " << (int)mean(img)[0] << endl;		// �ڷ����� Scalar�� [0]�� ù��° ���Ұ�
}
void minMaxLoc_Func() {
	Mat img = imread("phw.jpg", IMREAD_GRAYSCALE);		// GRAYSCALE ����
	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);	// �ش� ������ �ּҰ��� �����������

	cout << "minVal: " << minVal << " at " << minPos << endl;	//minVal�� GRAYSSCALE phw.jpg���� ���� ���� �ȼ���, �ش� ��ġ�� minPos
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;	//maxVal�� GRAYSSCALE phw.jpg���� ���� ū �ȼ���, �ش� ��ġ�� maxPos
}

void NORMALIZE_FUNC() {

	/*norm_type��  NORM_INF, NORM_L1, NORM_L2, NORM_MINMAX�� �ִµ� 
	  NORM_MINMAX�� ��� src ����� �ּڰ��� alpha, �ִ��� beta��
	  �ǵ��� ��� ���� �� ũ�⸦ ������.
	  ���� openCV ���� �ڵ忡�� NORM_MINMAX Ÿ������ normalize()�Լ���
	  ����ϰ� ������, Ư�� �Ǽ��� ������ ����� �׷��̽����� ���� ���·�
	  ��ȯ�ϰ��� �� �� normalize()�Լ��� ����ϸ� ����*/

	Mat src = Mat_<float>({ 1,5 }, { -1.f,-0.5f,0.f,0.5f,1.f });

	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	// �ּڰ��� 0, �ִ��� 255�� �ǵ��� ũ�� ����

	cout << "src: " << src << endl;	// src�� -1~1�� �����ε� �̰�
	cout << "dst: " << dst << endl;	// dst���� 0~255�� ������ ũ�Ⱑ ������
}

void cvRound_Func() {
	// round �Լ��� ����ϰ� �ݿø� �����ִ� �Լ�
	// �Ҽ��� �Ʒ��� ��Ȯ�ϰ� 0.5�� ��쿡�� ���� ����� ¦���� �ݿø� ����
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;		// 2
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;		// 3
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;	// 3
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;		// 4
}


int main(void) {



	return 0;
}