#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void video_in() {
	cv::VideoCapture cap("123.mp4");

	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	
	int delay = cvRound(1000 / fps);

	Mat frame, inversed;
	while (1) {
		cap >> frame;
		if (frame.empty()) {
			cerr << "frame is empty" << endl;
			break;
		}
		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)	// ESC key
			break;
	}
	destroyAllWindows();
}

int main(void) {

	video_in();

}