#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
���� �����ϴ� ����� ����� ���ؼ��� ���� ���� �����ϰ�,
�� ���� �ȿ����� ���� �����ϴ� ���� ȿ������.

���� ĳ�����̽� �з��⸦ �̿��� ������ ��ü ���� ����� ����� �ʹٸ� OpenCV 3.4.x ������ ��� �ִ�
opencv_createsamples.exe, opencv_traincascade.exe ���α׷��� �̿��� XML ������ ������ ����� �� ����.
�ٸ� �����׿� ���� ��ü ������ ��ȣ�ϴ� ���̱���.
*/

void detect_eye() {
	Mat src = imread("phw.jpg");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	
	//	�󱼰� �� ������ ���� ���� �з��� ������ ������
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
		

		//	�Է� ���󿡼� ������ �簢�� �� ������ �κ� ������ ������ faceROI�� ����
		Mat faceROI = src(face);

		//	faceROI ���󿡼� ���� ����
		vector<Rect> eyes;
		eye_classifier.detectMultiScale(faceROI, eyes);
		
		//	������ ���� �߾ӿ� �Ķ��� ���� �׸�. faceROI ������ src������ �κ� ������ ����(��������)�ϹǷ� faceROI�� ���� �׸��� src ���󿡵� �׷���.
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