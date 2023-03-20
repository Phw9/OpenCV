#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void MatOp4() {
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);	// 영행렬


	/*
	Mat::at() 함수는 가장 직관적인 행렬 원소 접근 방법
	행과 열을 나타내는 두 개의 정수를 인자로 받아 해당 위치의 행렬 원소값을
	참조 형식으로 반환
	
	template<typename _Tp> _Tp& Mat::at(int y, int x)
	y는 참조할 행 번호, x는 참조할 열 번호
	반환값 (_Tp& 타입으로 형 변환된) y번째 행, x번째 열의 원소 값(참조)

	*/
	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++;
		}
	}
	cout << "Mat1:\n " << mat1 << endl;

	/*
	Mat::ptr() 함수는 Mat 행렬에서 특정 행의 첫 번째 원소 주소를 반환

	template<typename _Tp> _Tp* Mat::ptr(int y)
	y는 참조할 행 번호
	반환값 (_Tp* 타입으로 형 변환된) y번째 행의 시작 주소
	*/

	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	}

	cout << "Mat1:\n " << mat1 << endl;

	/*
	MatIterator_ 반복자는 함수 인자 전달로 된 값이 행렬의 크기를 벗어나지 않아 에러발생이 적음
	Mat 행렬 원소 참조를 위한 반복자 변수를 만들어 행렬 크기에 상관없이 행렬 전체원소를 차례대로 참조
	Mat::begin() 함수를 이용해 행렬의 첫 번째 원소 위치를 얻고, Mat::end() 함수를 이용해 마지막 원소
	바로 다음 위치를 얻을 수 있음
	MatIterator_<uchar> 타입의 변수 it를 선언하고, mat1.begin<uchar>() 함수의 반환값으로 초기화
	it 값이 mat1.end<uchar>()와 같아질 때까지 위치를 증가시키면서, 해당 위치 원소 값을 1씩 증가
	이때 반복자 변수 it가 가리키는 원소 값을 참조하기위해 (*it) 형태로 코드작성

	단점: 전체를 돌기 때문에 동작 속도 면에서 안좋고, 임의의 위치에 자유롭게 접근이 불가능

	*/

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}

	waitKey();
	destroyAllWindows();
}

int main() {

	MatOp4();

	return 0;
}