#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
보행자 검출을 위한 HOG는 기본적으로 64x128 크기의 영상에서 계산한다.
HOG 알고리즘은 먼저 입력 영상으로부터 그래디언트(크기와 방향 성분으로) 계산한다.
방향은 0˚~180˚까지로 설정한다. 그 다음은 입력 영상을 8x8 크기 단위로 분할하는데,
각각의 8x8 부분 영상을 셀(cell)이라고 부른다.
각각의 셀로부터 그래디언트 방향 성분에 대한 히스토그램을 구하며, 이때 방향 성분을 20˚단위로
구분하면 총 아홉 개의 bin으로 구성된 방향 히스토그램이 만들어진다. 그리고 인접한 네 개의 셀을 합쳐 블록 이라고 정의.

하나의 블록에는 네 개의 셀이 있고, 각 셀에는 아홉 개의 빈으로 구성된 히스토그램 정보가 있으니
블록 하나에서는 총 36개의 실수 값으로 이루어진 방향 히스토그램 정보가 추출됨.
블록은 가로와 세로방향으로 각각 한 개의 셀만큼 이동하며 정의하므로 64x128 영상에서 블록은 가로 방향으로 일곱개,
세로 방향으로 15개 정의할 수 있다. 결국 64x128 영상에서 105개의 블록이 추출되고 전체 블록에서
추출되는 방향 히스토그램 실수 값 개수는 105x36=3780개 된다. 이 3780개의 실수 값이 64x128 영상을 표현하는 HOG 특징 벡터 역할을 한다.

보행자 영상과 보행자 영상이 아닌 영상에서 각각 HOG 특징 벡터를 추출해 SVM을 이용해
두 개의 클래스를 효과적으로 분리했다. 특징벡터를 이용해 SVM을 훈련시키고 효과적인 보행자 검출 방법을 완성시킨게 HOGDescriptor클래스다.

HOG와 SVM을 이용한 객체 검출 기술은 보행자 검출뿐만 아니라 다양한 형태의 객체 검출에서도 응용됨.

*/

int main() {

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Video open failed" << endl;
		return -1;
	}
	//	보행자 검출을 위한 용도로 훈련된 SVM 분류기 계수를 등록
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	Mat frame;
	while (true) {
		cap >> frame;
		if (frame.empty()) {
			break;
		}

		vector<Rect> detected;
		
		//	세번째 매개변수로 std::vector<double>& foundWeights 변수를 가진 함수도 오버로딩되어있음.
		hog.detectMultiScale(frame, detected);

		//	detected area를 box
		for (Rect r : detected) {
			Scalar c = Scalar(rand() % 256, rand() % 256, rand() % 256);
			rectangle(frame, r, c, 3);
		}

		imshow("frame", frame);
		if (waitKey(10) == 27)
			break;
	}

	destroyAllWindows();



	return 0;
}