#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void labeling_basic() {
	uchar data[] = {
		// 0은 배경인 검정색, 1은 객체인 흰색
		0,0,1,1,0,0,0,0,
		1,1,1,1,0,0,1,0,
		1,1,1,1,0,0,0,0,
		0,0,0,0,0,1,1,0,
		0,0,0,1,1,1,1,0,
		0,0,0,1,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,
	};
	//	255를 곱해 이진화를 시킴
	Mat src = Mat(8, 8, CV_8UC1, data) * 255;

	/*
	레이블 맵을 labels 행렬에 저장하고 레이블 개수를 반환
	반환값이 N이면 0부터 N-1까지의 레이블 번호가 존재, 이 때 0번 레이블은 배경
	실제 객체수는 N-1개
	*/
	Mat labels;
	int cnt = connectedComponents(src, labels);

	cout << "src:\n" << src << endl;
	cout << "labels:\n" << labels << endl;
	cout << "nuber of labels: " << cnt << endl;
}

int main() {

	labeling_basic();

	return 0;
}