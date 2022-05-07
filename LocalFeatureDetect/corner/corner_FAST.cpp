#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;


/*
FAST(Features from Accelerated Segment Test) �ڳ� ���� ����� �ܼ��� �ȼ� �� �� ����� ���� �ڳʸ� ����

�� p������ ��⸦ Ip��� ǥ���ϰ� t�� ����� ��ų� ��ο� ������ �����ϱ� ���� �Ӱ谪���� �����ϸ�
���� �ֺ� 16�� �ȼ� �߿��� �� ���� Ip+t���� ū �ȼ��� ��ȩ �� �̻� �������� ��Ÿ���� �� p�� ��ο� ������
�����ϰ� ����Ǿ� �ִ� �ڳʴ�. �ݸ鿡 �ֺ� 16�� �ȼ� �߿��� �� ���� Ip-t���� ���� �ȼ��� ��ȩ�� �̻� �������� ��Ÿ����
�� p�� ���� ������ ����Ǿ� �ִ� �ڳʴ�.

FAST ����� Ư¡ �ڳ� �� �ֺ� �ȼ��鵵 �Բ� �ڳʷ� �����ϴ� ��찡 ���� ������ �ֺ� �ڳ� �ȼ� �߿���
���� �ڳʿ� ������ �ȼ��� �����ϴ� ���ִ� ���� �۾��� �߰������� �����ϴ� ���� ����.

FAST ��������� �ڳ� ���� �ֺ� 16�� ������ �ȼ� �� ���� ���� �ڳ� ������ �����ϰ�, ������ �ڳ� �߿��� �ڳ� ������ ���� ū �ڳʸ� ���� �ڳʷ� ����(���ִ� ����)

FAST() �Լ� input�� CV_8UC1 Ÿ�Ը� ���, keypoints ���ڴ� KeyPoint Ŭ���� ��ü�� ���ͷ� �����Ѵ�.
KeyPoint Ŭ������ Point Ÿ���� ��� ���� pt�� ������ �־ , ���⿡ �ڳ� �� ��ǥ�� �����. ��, FAST()�Լ��� ���� ������ �ڳ� �� �߿���
i��° �ڳ��� x,y��ǥ�� keypoints[i].pt.x�� ���� �ڵ�� ������ ������

*/

void corner_fast() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	vector<KeyPoint> keypoints;
	//	src ���󿡼� FAST ������� �ڳ� �� ����. ��������Ӱ谪�� 60���� ����, �������� true���ڷ� ���ִ� ���� ����
	//	����� ��� �ڳ� �� ��ǥ�� keypoints ������ �����.
	FAST(src, keypoints, 60, true);	

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (KeyPoint kp : keypoints) {
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {

	corner_fast();

	return 0;
}