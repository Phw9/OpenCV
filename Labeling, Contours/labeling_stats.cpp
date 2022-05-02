#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void labeling_stats() {
	Mat src = imread("mask.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	//	src 영상을 오츠 알고리즘으로 이진화시켜 bin에 저장
	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

	/*
	bin 영상에 대해 레이블링을 수행하고 각 객체 영역의 통계 정보를 추출
	
	labels은 레이블맵
	
	stats는 CV_32SC1 타입의 행렬. 행 개수는 레이블 개수와 같고, 열 개수는 항상 5
	첫 번째 행은 배경 영역 정보, 두 번째 행부터는 1번부터 시작하는 객체 영역 정보
	각 열은 차례대로 특정 영역을 감싸는 바운딩 박스의
	x 좌표, y 좌표, 가로크기(width), 세로크기(height), 면적(해당 영역의 픽셀 개수)를 담고 있음.
	Rect클래스처럼 좌상단(LU) 좌표와 박스 크기 + 면적을 담았다고 생각하면 됨.

	centroids의 행 개수는 레이블 개수와 같고 열 개수는 항상 2
	각 열은 차례대로 각 영역의 무게 중심 x좌표, y좌표를 담고있음.
	이는 각각의 객체의 x좌표와 y좌표를 모두 더한 후 픽셀 개수로 나눈 값

	반환값(N)은 레이블 개수 실제 객체 개수는 N-1
	*/
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

	//	레이블링을 위해 src 영상을 3채널 컬러 영상 형식으로 변환
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	//	배경 영역을 제외하고 흰색 객체 영역에 대해서만 for문을 수행
	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);

		//	객체의 픽셀 개수가 20보다 작으면 잡음이라고 간주하고 무시
		if (p[4] < 20) continue;

		//	검출된 객체를 감싸는 바운딩 박스를 노란색으로 그림
		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {

	labeling_stats();

	return 0;
}