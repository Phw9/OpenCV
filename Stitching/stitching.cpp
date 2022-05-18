#include <iostream>
#include "opencv2/opencv.hpp"


int main(int argc, char* argv[]) 
{
	
	//	����� ���� ������ 3���� ������ ������ �ܼ� â�� ����ϰ� ���α׷� ����
	if (argc < 3) {
		std::cerr << "Usage: stitching.exe <image_file1> <image_file2> [<image_file3> ...]" << std::endl;
		return -1;
	}

	//	����� ���ڷ� ���޵� ���� ���� ���� �ҷ��ͼ� vector<Mat> Ÿ�� ���� imgs�� �߰�
	std::vector<cv::Mat> imgs;
	for (int i = 1; i < argc; i++) {
		cv::Mat img = cv::imread(argv[i]);

		if (img.empty()) {
			std::cerr << i << " th Image load failed" << std::endl;
			return -1;
		}

		imgs.push_back(img);
	}

	//	stitcher ��ü ����
	cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create();

	//	imgs�� ����� �Է� ������ �̾�ٿ� dst�� �����ϰ� status�� ���¸� ��Ÿ���� ��� ��ȯ
	cv::Mat dst;
	cv::Stitcher::Status status = stitcher->stitch(imgs, dst);

	//	stitching�� ���������� error���� ����
	if (status != cv::Stitcher::Status::OK) {
		std::cerr << "Error on stitching" << std::endl;
		return -1;
	}
	
	cv::imwrite("result.jpg", dst);
	cv::imshow("dst", dst);

	cv::waitKey();

	return 0;
}