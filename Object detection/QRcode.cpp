#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*

QRCodeDetector에는 멤버함수 decode, detect 가 존재하지만 이를 detectAndDecode 멤버함수로 한꺼번에 할 수 있음.

QRCodeDetector 클래스의 기능은 무료 QR 코드 라이브러리인 QUirc를 기반으로 만들어졌다.
QUirc 라이브러리에 대한 자세한 사항은 http://github.com/dlbeer/quirc 웹 사이트를 참고.

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

		//	매 프레임마다 QR 코드 검출 및 해석 수행
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