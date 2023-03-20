#include <iostream>
#include "opencv2/opencv.hpp"


int main(int argc, char* argv[]) 
{
	
	//	명령행 인자 개수가 3보다 작으면 사용법을 콘솔 창에 출력하고 프로그램 종료
	if (argc < 3) {
		std::cerr << "Usage: stitching.exe <image_file1> <image_file2> [<image_file3> ...]" << std::endl;
		return -1;
	}

	//	명령행 인자로 전달된 영상 파일 각각 불러와서 vector<Mat> 타입 변수 imgs에 추가
	std::vector<cv::Mat> imgs;
	for (int i = 1; i < argc; i++) {
		cv::Mat img = cv::imread(argv[i]);

		if (img.empty()) {
			std::cerr << i << " th Image load failed" << std::endl;
			return -1;
		}

		imgs.push_back(img);
	}

	//	stitcher 객체 생성
	cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create();

	//	imgs에 저장된 입력 영상을 이어붙여 dst에 저장하고 status에 상태를 나타내는 상수 반환
	cv::Mat dst;
	cv::Stitcher::Status status = stitcher->stitch(imgs, dst);

	//	stitching에 실패했으면 error띄우고 종료
	if (status != cv::Stitcher::Status::OK) {
		std::cerr << "Error on stitching" << std::endl;
		return -1;
	}
	
	cv::imwrite("result.jpg", dst);
	cv::imshow("dst", dst);

	cv::waitKey();

	return 0;
}