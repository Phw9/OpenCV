#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 명령행 인자에 영상 3개 입력이 안되면 오류 발생

int main(int argc, char* argv[]) {

	if (argc < 3) {
		cerr << "Usage: stitching.exe <image_file1> <image_file2> [<image_file3> ...]" << endl;
		return -1;
	}

	// vector<Mat> imgs 변수에 인자로 전달된 영상 입력.
	// 영상파일이 비어있으면 오류 발생

	vector<Mat> imgs;
	for (int i = 1; i < argc ; i++) {
		Mat img = imread(argv[i]);

		if (img.empty()) {
			cerr << "Image load failed" << endl;
			return -1;
		}
		imgs.push_back(img);
	}

	// stitcher 객체를 생성 후 영상을 붙인다.

	Ptr<Stitcher> stitcher = Stitcher::create();

	Mat dst;
	Stitcher::Status status = stitcher->stitch(imgs, dst);

	if (status != Stitcher::Status::OK) {
		cerr << "Error on stitching!" << endl;
		return -1;
	}
	// 파노라마 영상을 result.jpg로 저장한다.

	imwrite("result.jpg", dst);

	imshow("dst", dst);

	waitKey();
	return 0;
}