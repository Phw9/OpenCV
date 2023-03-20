#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;


void camera_in_video_out() {
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));

	double fps = cvRound(cap.get(CAP_PROP_FPS));

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}
	Mat frame, inversed;
	while (1) {
		cap >> frame;
		if (frame.empty()) {
			cerr << "Frame is empty" << endl;
			break;
		}
		inversed = ~frame;
		outputVideo << inversed;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();
}

int main(void) {

	camera_in_video_out();
}