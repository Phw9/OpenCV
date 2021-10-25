#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


// 간략화한 Point_ 클래스 정의와 이름 재정의
template<typename _Tp> class Point_ 
{

public:
	Point_();
	Point_(_Tp _x, _Tp _y);
	Point_(const Point_& pt);

	Point_& operator = (const Point_& pt);

	_Tp dot(const Point_& pt) const;
	double ddot(const Point_& pt) const;
	double cross(const Point_& pt) const;
	bool inside(const Rect_<_Tp>&) const;

	_Tp x, y;

};

typedef Point_<int> Point2i;
typedef Point_<int64> Point2l;
typedef Point_<float> Point2f;
typedef Point_<double> Point2d;
// typedef Point2i Point;

// 


int main(void) {

	return 0;

}
