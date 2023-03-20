#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

/*
영상 특징 중에서 에지, 직선 성분, 코너처럼 영상 전체가 아닌 일부 영역에서 추출할 수 있는 특징을 지역 특징(local feature)라고 함.
코너(corner)는 에지의 방향이 급격하게 변하는 부분으로서 삼각형의 꼭지점이나 연필 심처럼 뾰족하게 튀어나와 있는 부분이 코너다.
코너는 에지나 직선 성분 등의 다른 지역 특징에 비해 분별력이 높아 위치파악하기 쉽고 대체로 영상 전 영역에 골고루 분포하기 때문에 영상을 분석하는 데 유용한 지역특징으로 사용된다.
코너처럼 한 점의 형태로 표현할 수 있는 특징을 특징점(feature point)라고 하며, 특징점은 키포인트(keypoint), 관심점(interest point)라고도 부른다.

코너 검출 방법은 코너 점 구분을 위한 기본적인 아이디어를 수학적으로 잘 정의하였다는 점에서 큰 의미가 있음.

E(Δx,Δy) = ∑ w(x,y) * [I(x+Δx,y+Δy)-I(x,y)]^2

w(x,y)는 균일한 값을 갖는 사각형 윈도우 또는 가우시안 형태의 가중치를 갖는 윈도우.
만약 E(Δx,Δy) 함수가 모든 방향으로 값이 크게 나타난다면 점(x,y)는 코너라고 간주할 수 있음.
E(Δx,Δy)가 모든 방향으로 그 값이 크게 나타나는지를 검사하기 위해 테일러 급수, 고윳값 분석(eigenvalue analysis)등의 수학적 기법을 적용해 코너 응답 함수 R을 유도

R = Det(M) - k*Tr(M)^2

Det()는 행렬식(Determinant), Tr()은 대각합(trace)를 의미하고 행렬 M은 다음과 같이 정의 된다.

M = ∑ w(x,y) * { (Ix*Ix,Ix*Iy),(Ix*Iy,Iy*Iy) }

Ix와 Iy는 입력 영상 I를 각각 x축 방향과 y축 방향으로 편미분한 결과. 코너 응답 함수 정의에서 상수 k는 보통 0.04~0.06 사이의 값을 사용
코너 응답 함수(R)은 입력 영상 각각의 픽셀에서 정의되는 실수 값이며, 이 값을 분석해 코너, 에지, 평탄한 영역을 판별함.

R>0 : R이 0보다 충분히 큰 양수이면 코너 영역
R=0 : R이 0에 가까운 실수면 평탄한 영역
R<0 : R이 0보다 작은 음수면 에지 영역

cornerHarris()함수에서 사용자가 정한 임계값보다 크면 코너점으로 판단할 수 있는데
하나의 코너 위치에 사용자 지정 임계값보다 큰 픽셀이 여러 개 발생할 수 있으므로, 간단한 비최대 억제(non-maximum suppression)를 수행해
지역 최댓값 위치만 코너로 판별하는 것이 좋다.
이는 해당 픽셀의 상하좌우와 비교해 간단하게 비최대 억제를 수행할 수 있음.
*/

void corner_harris() {
	Mat src = imread("phw.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	//	src 영상으로부터 해리스 코너 응답(R) 함수 행렬harris를 구한다.
	Mat harris;
	cornerHarris(src, harris, 3, 3, 0.04);

	/*
	harris 행렬 원소 값 범위를 0~225로 정규화하고, 타입을 CV_8UC1로 변환해 저장
	해리스 코너 응답 함수 분포를 영상 형태로 화면에 표시하기 위해 만들어야함.
	*/
	Mat harris_norm;
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//	간단한 비최대 억제를 수행. (i,j) 위치에서 주변 네 개의 픽셀을 비교해 지역 최대인 경우에만 dst 영상에 빨간색 원으로 코너를 표시
	for (int j = 1; j < harris.rows - 1; j++) {
		for (int i = 1; i < harris.cols - 1; i++) {
			//	harris_norm 픽셀값이 200보다 큰 값만 코너로 간주한다. 임계값을 낮추면 더 많은 모서리를 코너로 검출
			if (harris_norm.at<uchar>(j, i) > 200) {
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j + 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j, i - 1) &&
					harris.at<float>(j, i) > harris.at<float>(j, i + 1)) {
					circle(dst, Point(i, j), 4, Scalar(0, 0, 255), 2);
				}

			}
		}
	}

	imshow("src", src);
	imshow("harris_norm", harris_norm);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}


int main() {

	corner_harris();

	return 0;
}