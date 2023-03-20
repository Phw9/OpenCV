#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*

QRCodeDetector���� ����Լ� decode, detect �� ���������� �̸� detectAndDecode ����Լ��� �Ѳ����� �� �� ����.

QRCodeDetector Ŭ������ ����� ���� QR �ڵ� ���̺귯���� QUirc�� ������� ���������.
QUirc ���̺귯���� ���� �ڼ��� ������ http://github.com/dlbeer/quirc �� ����Ʈ�� ����.

*/


int main() {

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Video open failed" << endl;
		return -1;
	}
	
	QRCodeDetector detector;

	Mat frame;
	while (true) {
		cap >> frame;
		
		if (frame.empty()) {
			cerr << "Frame load failed" << endl;
			break;
		}

		//	�� �����Ӹ��� QR �ڵ� ���� �� �ؼ� ����
		vector<Point> points;
		String info = detector.detectAndDecode(frame, points);

		if (!info.empty()) {
			polylines(frame, points, true, Scalar(0, 0, 255), 2);
			putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
		}

		imshow("frame", frame);
		if (waitKey(10) == 27)
			break;
	}

	destroyAllWindows();



	return 0;
}