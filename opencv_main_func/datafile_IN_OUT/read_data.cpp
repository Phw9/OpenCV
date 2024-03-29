#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void readData() {
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs("mydata.json", FileStorage::READ);

	if (!fs.isOpened()) {
		cerr << "File open failed" << endl;
		return;
	}

	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();

	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "point: " << pt1 << endl;
	cout << "scores: " << Mat(scores).t() << endl;	// ��ġ���
	cout << "data:\n" << mat1 << endl;

}


int main(void) {

	readData();

	return 0;
}