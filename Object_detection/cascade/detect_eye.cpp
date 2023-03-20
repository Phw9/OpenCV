#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
눈을 검출하는 기능을 만들기 위해서는 먼저 얼굴을 검출하고,
얼굴 영역 안에서만 눈을 검출하는 것이 효율적임.

만약 캐스케이스 분류기를 이용해 나만의 객체 검출 기능을 만들고 싶다면 OpenCV 3.4.x 버전에 들어 있는
opencv_createsamples.exe, opencv_traincascade.exe 프로그램을 이용해 XML 파일을 생성해 사용할 수 있음.
다만 딥러닝에 의한 객체 검출을 선호하는 편이긴함.
*/

void detect_eye() {
	Mat src = imread("phw.jpg");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	
	//	얼굴과 눈 검출을 위해 각각 분류기 정보를 가져옴
	CascadeClassifier face_classifier("haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier("haarcascade_eye.xml");

	if (face_classifier.empty() || eye_classifier.empty()) {
		cerr << "XML load failed" << endl;
		return;
	}

	vector<Rect> faces;
	face_classifier.detectMultiScale(src, faces);
	for (Rect face : faces) {
		rectangle(src, face, Scalar(255, 0, 255), 2);
		

		//	입력 영상에서 검출한 사각형 얼굴 영역의 부분 영상을 추출해 faceROI에 저장
		Mat faceROI = src(face);

		//	faceROI 영상에서 눈을 검출
		vector<Rect> eyes;
		eye_classifier.detectMultiScale(faceROI, eyes);
		
		//	검출한 눈의 중앙에 파란색 원을 그림. faceROI 영상은 src영상의 부분 영상을 참조(얕은복사)하므로 faceROI에 원을 그리면 src 영상에도 그려짐.
		for (Rect eye : eyes) {
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
		}

	}

	imshow("src", src);

	waitKey();
	destroyAllWindows();
}

int main() {

	detect_eye();

	return 0;
}