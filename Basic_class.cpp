#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


// 1. 간략화한 Point_ 클래스 정의와 이름 재정의
//template<typename _Tp> class Point_ 
//{
//
//public:
//	Point_();
//	Point_(_Tp _x, _Tp _y);
//	Point_(const Point_& pt);
//
//	Point_& operator = (const Point_& pt);
//
//	_Tp dot(const Point_& pt) const;
//	double ddot(const Point_& pt) const;
//	double cross(const Point_& pt) const;
//	bool inside(const Rect_<_Tp>&) const;
//
//	_Tp x, y;
//
//};
//
//typedef Point_<int> Point2i;
//typedef Point_<int64> Point2l;
//typedef Point_<float> Point2f;
//typedef Point_<double> Point2d;


// 2. 간략화한 Size_클래스 정의와 이름 재정의
//template<typename _Tp> class Size_
//{
//public:
//	Size_();
//	Size_(_Tp _width, _Tp _height);
//	Size_(const Size_& sz);
//
//	Size_& operator = (const Size& sz);
//
//	_Tp area() const;
//	bool empty() const;
//	_Tp width, height;
//};





int main(void) {

	// 1. How to use Point class

	//Point pt1;	//pt1 = (0, 0)
	//pt1.x = 5; pt1.y = 10;	//pt1 = (5, 10)
	//Point pt2(10, 30); // pt2 = (10, 30)
	//Point pt3 = pt1 + pt2;	//pt3 = (15, 40)
	//Point pt4 = pt1 * 2;	//pt4 = (10, 20)
	//int d1 = pt1.dot(pt2);
	//bool b1 = (pt1 == pt2);	//b1 = false

	//cout << pt1 << endl;
	//cout << pt4 << endl;
	//cout << d1 << endl;

	// 2. How to use Size class

	//Size sz1, sz2(10, 20);	// sz1 = [0x0], sz2 = [10x20]
	//sz1.width = 5; sz1.height = 10;	// sz1 = [5x10]
	//Size sz3 = sz1 + sz2;	// sz3 = [15x30]
	//Size sz4 = sz1 * 2; // sz4 = [10x20]
	//int area1 = sz4.area();	// area1 = 200

	//cout << sz3 << endl;
	//cout << sz4 << endl;

	// 3. How to use RotatedRect Class

	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);

	Point2f pts[4];
	rr1.points(pts);
	cout << pts[0] << endl;	// bottom left (bl)
	cout << pts[1] << endl;	// 
	cout << pts[2] << endl;
	cout << pts[3] << endl;

	Rect br = rr1.boundingRect();

	cout << br.x << endl;
	cout << br.y << endl;
	cout << br.width << endl;
	cout << br.height << endl;
	cout << br.height << endl;
	cout << br.area() << endl;
	return 0;

}
