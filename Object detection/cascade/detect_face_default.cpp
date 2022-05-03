#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
OpenCV 얼굴 검출 기능은 2001년에 비올라와 존스가 발표한 부스팅 기반의 캐스케이드 분류기(cascade classifier) 알고리즘을 기반으로 만들어짐
이 객체 검출 알고리즘은 기본적으로 다양한 객체를 검출하지만 특히 얼굴 검출에 적용되어 속도와 정확도를 인정받음

영상을 24x24 크기로 정규화한 후, 유사-하르 필터(Haar-like filter) 집합으로부터 특징 정보를 추출해 얼굴 여부를 판별
유사-하르 필터란 흑백 사각형이 서로 붙어있는 형태로 구성된 필터이며 흰색 영역 픽셀 값은 모두 더하고, 검은색 영역 픽셀
값은 모두 빼서 하나의 특징 값을 얻을 수 있음. 사람의 정면 얼굴 형태가 전형적으로 밝은 영역(이마, 미간, 볼 등)과
어두운 영역(눈썹, 입술 등)이 정해져 있기 땜누에 유사-하르 필터로 구한 특징 값은 얼굴을 판별하는 용도로 사용

24x24 크기에서 다양한 크기의 유사-하르 필터를 대략 18만개 생성할 수 있음. 픽셀 값의 합과 차를 계산하는 것이 복잡하진 않지만 시간이 오래걸림
이를 에이다부스트(adaboost) 알고리즘과 적분 영상(integral image)을 이용해 문제 해결

에이다부스트 알고리즘에 의해 24x24 부분 영상에서 검사할 특징 개수가 약 6000개로 감소했찌만, 입력 영상 전체에서 부분영상을 추출해
검사해야 하기 때문에 여전히 연산량은 부담이됨. 더군다나 나타날 수 있는 얼굴 크기가 다양하기 때문에 보통 입력 영상의 크기를
줄여 가면서 전체 영역에 대한 검사를 다시 수행해야함.
이를 캐스케이드(cascade) 구조라는 새로운 방식을 도입해 얼굴이 아닌 영역을 빠르게 걸러 내는 방식을 사용

캐스케이드 구조 1단계에서는 얼굴 검출에 가장 유용한 유사-하르 필터 하나를 사용해 얼굴이 아니라고 판단되면 이후의 유사-하르 필터 계산은 수행하지 않음.
1단계를 통과하면 2단계에서 유사-하르 필터 다섯 개를 사용해 얼굴이 아닌지를 검사하고, 얼굴이 아니라고 판단되면 이후 단계 검사는 수행하지 않음.
이러한 방식으로 얼굴이 아닌 영역을 빠르게 제거함으로써 빠르게 동작하는 성능을 보임.

OpenCV에서 제공하는 하르 기반 분류기 XML 파일
haarcascade_frontal_face_~~~.xml		: 정면 얼굴 검출
haarcascade_profileface.xml				: 측면 얼굴 검출
haarcascade_smile.xml					: 웃음 검출
haarcascade_eye~~~~.xml					: 눈 검출
haarcascade_frontalcatface~~~.xml		: 고양이 얼굴 검출
haarcascade_fullbody.xml				: 사람의 전신 검출
haarcascade_upperbody.xml				: 사람의 상반신 검출
haarcascade_lowerbody.xml				: 사람의 하반신 검출
┌haarcascade_russian_plate_number.xml		: 러시아 자동차
└haarcascade_licence_plate_rus_16stages.xml	: 번호판 검출

*/


void detect_face() {
	Mat src = imread("phw.jpg");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	CascadeClassifier classifier("haarcascade_frontalface_default.xml");	// 절대 및 상대경로 지정

	if (classifier.empty()) {
		cerr << "XML load failed" << endl;
		return;
	}
	//	검출된 객체의 사각형 좌표 정보 벡터
	vector<Rect> faces;
	/*
	XML 파일을 정상적으로 불러왔으면 객체 검출을 실행함.
	
	다양한 크기의 얼굴을 검출하기 위해 처음엔 작은 크기의 검색 윈도우(scaleFactor)를 이용하여 객체를 검출하고,
	이후 scaleFactor 값의 비율로 검색 윈도우 크기를 확대 시키면서 여러 번 객체를 검출
	
	minNeighbors 인자에는 검출할 객체 영역에서 얼마나 많은 사각형이 중복되어 검출되어야 최종적으로 객체 영역으로 설정할지를 지정
	*/
	classifier.detectMultiScale(src, faces);

	//	검출된 얼굴 영역 사각형을 src영상에 보라색으로 그림
	for (Rect rc : faces) {
		rectangle(src, rc, Scalar(255, 0, 255), 2);
	}

	imshow("src", src);

	waitKey();
	destroyAllWindows();
}

int main() {

	detect_face();

	return 0;
}