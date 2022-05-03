#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
���ø� ��Ī�� �˰��� Ư���� �Է� ������ ȸ���ǰų� ũ�Ⱑ ����Ǹ� ����� �������� ����.
ã���� �ϴ� ���ø� ������ �ٸ� ��ü�� ���� �ܷ����� ���� ���� ����� ����ϱ� �����
*/

/*
���ø� ������ �Է� ���� ��ü ������ ���� �̵��ϸ� ���ø� ����� �Է� ���� �κ� ������� ���絵 �Ǵ� �����絵(dissimilarity)�� ���
���絵�� ����� ��� ���ø� ����� ����� �κ� ���� ��ġ���� ���� ũ�� ��Ÿ����,
�����絵�� ����� ��쿡 ���ø� ����� ����� �κп��� ���� �۰� ��Ÿ��.
���絵�� ������� ��� ���� ���� �ȼ� ��ġ�� ���ø� ����� ���� ������ �κ�
�����絵�� ������� ��� ���� ��ο� �ȼ� ��ġ�� ���ø� ����� ���� ������ �κ�

���絵 ��, �����絵 ���� result(res) ���ڷ� ��ȯ.
Image ���� ũ�Ⱑ WxH, templ ���� ũ�Ⱑ wxh�� ���
result ����� ũ��� (W-w+1)x(H-h+1)�� ����

method ���ڿ��� TemplateMatchModes ������ ��� �� �ϳ��� ����
TM_SQDIFF	: ������(squared difference)��Ī ���. ���� �� ������ �Ϻ��ϰ� ��ġ�ϸ� 0, ���� �������� ������ 0���� ū ���
TM_CCORR	: �������(correlation)��Ī ���. ���� �� ������ �����ϸ� ū ����� ������ �������� ������ ���� ��.
TM_CCOEFF	: ������(correlation coefficient) ��Ī ���. ���� �� ������ �̸� ��� ���� ������ �� ������� ��Ī�� ����. ������ �����ϸ� ū ���, �ƴϸ� 0�� ����� ��� �Ǵ� ����.

���� ����� ���� ���� ������ ��� ���� ������ �ٿ��ִ� ����ȭ ������ �߰���
TM_SQDIFF_NORMED, TM_CCORR_NORMED, TM_CCOEFF_NORMED ����� ����.
TM_CCORR_NORMED	: ��Ī �ᱣ���� 0���� 1 ������ �Ǽ�
TM_CCOEFF_NORMED: ��Ī �ᱣ���� -1���� 1 ������ �Ǽ�
�� ��� ��� �ᱣ���� 1�� �������� ��Ī�� �� �Ǿ����� �ǹ�

TM_CCOEFF_NORMED ����� ���� ����� ���������� ��� ������ ���� �����ϱ� ������ ���� ���� �� ���귮�� ����

TM_SQDIFF�� result ��� ��Ŀ��� �ּڰ� ��ġ�� ���� ��Ī�� �ߵ� ��ġ
TM_CCORR, TM_CCOEFF�� result ��� ��Ŀ��� �ִ� ��ġ�� ���� ��Ī�� �ߵ� ��ġ
�ִ�/�ּҰ� ��ġ�� OpenCV�� minMaxLoc() �Լ��� �̿��ؼ� �˾Ƴ���.
*/

void template_matching() {
	Mat img = imread("circuit.bmp", IMREAD_COLOR);	//	�Է� ���� (8��Ʈ �Ǵ� 32��Ʈ �Ǽ���)
	Mat templ = imread("crystal.bmp", IMREAD_COLOR);	//	���ø� ���� (�Է� ���󺸴� ���ų� �۾ƾ� �ϰ� Ÿ���� ���ƾ���)

	if (img.empty() || templ.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	���� ���� ȹ�� �������� �߻��� �� �ִ� ������ ������ �ùķ��̼� �ϱ� ���� �Է� ���� ��⸦ 50��ŭ ����
	img = img + Scalar(50, 50, 50);

	//	���� ���� ȹ�� �������� �߻��� �� �ִ� ������ ������ �ùķ��̼� �ϱ� ���� �Է� ���� ǥ�� ������ 10�� ����þ� ���� �߰�
	Mat noise(img.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);

	/*
	res�� -1���� 1 ������ �Ǽ�
	res_norm�� 0���� 255 ������ ���� ������ ����ȭ�� ���
	*/
	Mat res, res_norm;
	//	����ȭ�� ������ ��Ī����� ����� ���ø� ��Ī, res���� result����� �����
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
	//	���ø� ��Ī ��� ��� res�� ��� ���� ���� 0~255 ���̷� ����ȭ�ϰ�, Ÿ���� CV_8UC1�� ��ȯ�� res_norm�� ����
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

	//	res ��Ŀ��� �ִ� ��ġ�� ã�� maxloc�� ����. �� ��ġ������ �ִ� maxv�� ���ø� ��Ī�� �� �Ǿ������� �����ϴ� ô���� ���
	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv: " << maxv << endl;

	//	���ø� ��Ī���� ã�� ��ġ�� ������ �簢������ ǥ��
	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);

	waitKey();
	destroyAllWindows();
}

int main() {

	template_matching();

	return 0;
}