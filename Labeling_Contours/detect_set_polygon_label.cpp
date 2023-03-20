#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//	img ���󿡼� pts �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸���. label ���ڿ��� ��� �Ѵ�.
void setLabel(Mat& img, const vector<Point>& pts, const String& label) {
	Rect rc = boundingRect(pts);											//	pts �ܰ����� ���δ� �ٿ�� �ڽ��� ����
	rectangle(img, rc, Scalar(0, 0, 255), 1);								//	�ٿ�� �ڽ��� ��Ȳ������ ǥ��
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));	//	�ٿ�� �ڽ� �»�ܿ� label ���ڿ��� ���
}

int main() {
	Mat img = imread("polygon.bmp", IMREAD_COLOR);

	if (img.empty()) {
		cerr << "Image load failed" << endl;
		return -1;
	}

	//	���� ����ȭ�� ���� GRAY�� ��ȯ
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//	���� �˰������� �ڵ� ����ȭ�Ͽ� bin�� ����
	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	//	bin ���󿡼� ��� ��ü�� �ٱ��� �ܰ����� ����
	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);


	
	//	����� �� ��ü�� �ܰ��� ��ǥ�� pts ������ �����ϸ� for�� ����
	for (vector<Point>& pts : contours) {
		if (contourArea(pts) < 400)	//	�ܰ����� ���δ� ������ 400���� ������ ����
			continue;
		/*
		pts �ܰ����� �ٻ�ȭ�� approx�� ����
		���۶�-����Ŀ(DP: Douglas-Peucker) �˰����� ����� � �Ǵ� �ٰ����� �ܼ�ȭ
		1. �Է� �ܰ������� ���� �ָ� ������ �ִ� �� ���� ã�� �������� ����
		2. �ش� �������� ���� �ָ� ������ �ִ� �ܰ��� ���� ���� ã�� �ٻ�ȭ ������ �߰�
		3. 1,2 �� �ݺ��ϴ� 2�� �Ÿ��� epsilon ���ں��� ������ �ٻ�ȭ�� ����
		4. epsilon ���ڴ� ���� �Է� �ܰ��� �Ǵ� � ������ ���� ����(arcLength(curve, true) * 0.02)�� ����
		*/
		vector<Point> approx;	
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

		//	approx�� ����� �ܰ��� ���� ������ vtc�� ����
		int vtc = (int)approx.size();

		/*
		�ٻ�ȭ�� �ܰ����� ������ ������ 3�̸� �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸��� "TRI" ���ڿ��� ��� (�ﰢ��)
		�ٻ�ȭ�� �ܰ����� ������ ������ 4�̸� �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸��� "RECT" ���ڿ��� ��� (�簢��)
		
		��ü�� ������ ���� ������ ������ ���� ������ �ܰ��� �ֺ��� �ٿ�� �ڽ��� �׸��� "CIR" ���ڿ��� ��� (��)
		������ ���� ����(R): R = (4 * PI * Area) / Len^2
		�� �������� ���� ���� R�� 0���� 1 ������ �Ǽ��� ���Ǹ�, �Է� ������ �� ��翡 �������� 1�� ����� ���� ����
		*/
		if (vtc == 3) {
			setLabel(img, pts, "TRI");
		}
		else if (vtc == 4){
			setLabel(img, pts, "RECT");
		}
		else if (vtc > 4) {
			double len = arcLength(pts, true);	//	�� ���̸� ���� (����)
			//	oriented�� default�� false �̰� ������ ������ ��ȯ, true�� ��� ���� ���⿡ ���� ������ ��ȣ�� �޶���.
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);

			if (ratio > 0.8) {
				setLabel(img, pts, "CIRCLE");
			}
		}
	}

	imshow("img", img);
	waitKey();
	destroyAllWindows();

	return 0;
}