#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
���� Ư¡ �߿��� ����, ���� ����, �ڳ�ó�� ���� ��ü�� �ƴ� �Ϻ� �������� ������ �� �ִ� Ư¡�� ���� Ư¡(local feature)��� ��.
�ڳ�(corner)�� ������ ������ �ް��ϰ� ���ϴ� �κ����μ� �ﰢ���� �������̳� ���� ��ó�� �����ϰ� Ƣ��� �ִ� �κ��� �ڳʴ�.
�ڳʴ� ������ ���� ���� ���� �ٸ� ���� Ư¡�� ���� �к����� ���� ��ġ�ľ��ϱ� ���� ��ü�� ���� �� ������ ���� �����ϱ� ������ ������ �м��ϴ� �� ������ ����Ư¡���� ���ȴ�.
�ڳ�ó�� �� ���� ���·� ǥ���� �� �ִ� Ư¡�� Ư¡��(feature point)��� �ϸ�, Ư¡���� Ű����Ʈ(keypoint), ������(interest point)��� �θ���.

�ڳ� ���� ����� �ڳ� �� ������ ���� �⺻���� ���̵� ���������� �� �����Ͽ��ٴ� ������ ū �ǹ̰� ����.

E(��x,��y) = �� w(x,y) * [I(x+��x,y+��y)-I(x,y)]^2

w(x,y)�� ������ ���� ���� �簢�� ������ �Ǵ� ����þ� ������ ����ġ�� ���� ������.
���� E(��x,��y) �Լ��� ��� �������� ���� ũ�� ��Ÿ���ٸ� ��(x,y)�� �ڳʶ�� ������ �� ����.
E(��x,��y)�� ��� �������� �� ���� ũ�� ��Ÿ�������� �˻��ϱ� ���� ���Ϸ� �޼�, ������ �м�(eigenvalue analysis)���� ������ ����� ������ �ڳ� ���� �Լ� R�� ����

R = Det(M) - k*Tr(M)^2

Det()�� ��Ľ�(Determinant), Tr()�� �밢��(trace)�� �ǹ��ϰ� ��� M�� ������ ���� ���� �ȴ�.

M = �� w(x,y) * { (Ix*Ix,Ix*Iy),(Ix*Iy,Iy*Iy) }

Ix�� Iy�� �Է� ���� I�� ���� x�� ����� y�� �������� ��̺��� ���. �ڳ� ���� �Լ� ���ǿ��� ��� k�� ���� 0.04~0.06 ������ ���� ���
�ڳ� ���� �Լ�(R)�� �Է� ���� ������ �ȼ����� ���ǵǴ� �Ǽ� ���̸�, �� ���� �м��� �ڳ�, ����, ��ź�� ������ �Ǻ���.

R>0 : R�� 0���� ����� ū ����̸� �ڳ� ����
R=0 : R�� 0�� ����� �Ǽ��� ��ź�� ����
R<0 : R�� 0���� ���� ������ ���� ����

cornerHarris()�Լ����� ����ڰ� ���� �Ӱ谪���� ũ�� �ڳ������� �Ǵ��� �� �ִµ�
�ϳ��� �ڳ� ��ġ�� ����� ���� �Ӱ谪���� ū �ȼ��� ���� �� �߻��� �� �����Ƿ�, ������ ���ִ� ����(non-maximum suppression)�� ������
���� �ִ� ��ġ�� �ڳʷ� �Ǻ��ϴ� ���� ����.
�̴� �ش� �ȼ��� �����¿�� ���� �����ϰ� ���ִ� ������ ������ �� ����.
*/

void corner_harris() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src �������κ��� �ظ��� �ڳ� ����(R) �Լ� ���harris�� ���Ѵ�.
	Mat harris;
	cornerHarris(src, harris, 3, 3, 0.04);

	/*
	harris ��� ���� �� ������ 0~225�� ����ȭ�ϰ�, Ÿ���� CV_8UC1�� ��ȯ�� ����
	�ظ��� �ڳ� ���� �Լ� ������ ���� ���·� ȭ�鿡 ǥ���ϱ� ���� ��������.
	*/
	Mat harris_norm;
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//	������ ���ִ� ������ ����. (i,j) ��ġ���� �ֺ� �� ���� �ȼ��� ���� ���� �ִ��� ��쿡�� dst ���� ������ ������ �ڳʸ� ǥ��
	for (int j = 1; j < harris.rows - 1; j++) {
		for (int i = 1; i < harris.cols - 1; i++) {
			//	harris_norm �ȼ����� 200���� ū ���� �ڳʷ� �����Ѵ�. �Ӱ谪�� ���߸� �� ���� �𼭸��� �ڳʷ� ����
			if (harris_norm.at<uchar>(j, i) > 200) {
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j + 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j, i - 1) &&
					harris.at<float>(j, i) > harris.at<float>(j, i + 1)) {
					circle(dst, Point(i, j), 4, Scalar(0, 0, 255), 2);
				}

			}
		}
	}

	imshow("src", src);
	imshow("harris_norm", harris_norm);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main() {

	corner_harris();

	return 0;
}