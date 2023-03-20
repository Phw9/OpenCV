#include "opencv2/opencv.hpp"
#include <iostream>


using namespace std;
using namespace cv;

/*
�Է� ������ ��ǥ (x,y)�� ��� ������ ��ǥ (x',y')�� �̵��ϴ� ������
x' = f1(x,y) = ax + by + c
y' = f2(x,y) = dx + ey + f

�̸� ��ķ� ǥ���ϸ�

{ {x'}, {y'} } = { { a,b,c }, { d,e,f } } * { {x}, {y}, {1} } 

M = { { a,b,c }, { d,e,f } }�� ������ ��ȯ ���(affine tranformation matrix)
�̶�� �Ѵ�.

*/

/*
�̵� ��ȯ(translation transformation)
: ���� �Ǵ� ���� �������� ���� ũ�⸸ŭ �̵�
x' = x + a
y' = y + b
M = { { 1,0,a }, { 0,1,b } }
*/
void affine_translation() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	// 3-Channel image�� ���η� 150, ���η� 100 �ȼ� �̵�
	Mat M = Mat_<double>({ 2,3 }, { 1,0,150,0,1,100 });

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

/*
���� ��ȯ(shear transformation)
: ���簢�� ������ ������ ���� �������� �о ����纯�� ������� ����
x' = x + (mx)*y
y' = y
M = { { 1,mx,0 }, { 0,1,0 } }
or
x' = x
y' = (my)*x + y
M = { { 1,0,0 }, { my,1,0 } }
*/
void affine_shear() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	double mx = 0.3;
	Mat M = Mat_<double>({ 2,3 }, { 1,mx,0,0,1,0 });

	Mat dst;
	// M���� ������ ��ȯ�� �����ϰ� ���� ��ȭ�� ������ �Է� ������ �Ϻΰ� �߸��� �ʰ�
	// ���� ũ�⸦ �÷���
	warpAffine(src, dst, M, Size(cvRound(src.cols+src.rows*mx),src.rows));

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
/*
ũ�� ��ȯ(scale transformation)
: ������ ��ü���� ũ�⸦ Ȯ�� �Ǵ� ����ϴ� ��ȯ
x' = (sx)*x
y' = (sy)*y
M = { { sx,0,0 }, { 0,sy,0 } }
resize() �Լ� �̿�
*/
void affine_scale() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	Mat dst1, dst2, dst3, dst4;
	// src ������ x,y �������� ���� 4�� Ȯ���� dst1 ����, �ֱٹ� �̿� ������ ���
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
	// src ������ 1920x1280 ũ��� Ȯ���� dst2 ����, �缱�� ������(default��)
	resize(src, dst2, Size(1920, 1280));
	// src ������ 1920x1280 ũ��� Ȯ���� dst3 ����, 3�� ȸ�� ������
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
	// src ������ 1920x1280 ũ��� Ȯ���� dst4 ����, ���ʽ� ������
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

	
	imshow("src", src);
	// Ȯ�뺯ȯ ��� ������ (40,50) ��ǥ���� 400x400 ũ���� �κ� ������ ȭ�鿡 ���
	/*imshow("dst1", dst1(Rect(400, 500, 400, 400)));*/
	imshow("dst1", dst1(Rect(40, 50, 400, 400)));
	imshow("dst2", dst2(Rect(40, 50, 400, 400)));
	imshow("dst3", dst3(Rect(40, 50, 400, 400)));
	imshow("dst4", dst4(Rect(40, 50, 400, 400)));
	imshow("dst11", dst1);

	waitKey();
	destroyAllWindows();
}

/*
ȸ�� ��ȯ(rotation transformation)
: ���� ó�� �ý����� �����ϴٺ��� �Է� ������ ȸ���ؾ� �ϴ� ��찡 ���� ����
 (ex. OCR �ý��ۿ��� �۾� ������ ������ �¾ƾ� �νķ��� �����ϹǷ� ������ ȸ�� ������ ����)
x' = (cos(theta))*x + (sin(theta))*y
y' = -(sin(theta))*x + (cos(theta))*y
M = { { cos(theta),sin(theta),0 }, { -sin(theta),cos(theta),0 } }
resize() �Լ� �̿�
*/
void affine_rotation() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	
	// ������ �߽� ��ǥ�� ����Ű�� ���� cp ����
	Point2f cp(src.cols / 2.f, src.rows / 2.f);
	// cp ��ǥ�� �������� �ݽð� ���� 20�� ȸ���ϴ� ��ȯ ��� M ����
	Mat M = getRotationMatrix2D(cp, 20, 1);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}
/*
��Ī ��ȯ(flip transformation)
: ������ �¿츦 ���� �ٲٰų� ���ϸ� ������ ������ ��ȯ
x' = w-1-x
y' = y
M = { { -1,0,w-1 }, { 0,1,0 } }
or
x' = x
y' = h-1-y
M = { { 1,0,0 }, { 0,-1,h-1 } }
resize() �Լ� �̿�
*/
void affine_flip() {
	Mat src = imread("phw.jpg");	// 3-Channel image

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1,0,-1 };
	for (int i = 0; i < 3; i++) {
		flip(src, dst, flipCode[i]);
		
		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);


		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}

void affine_transform() {
	Mat src = imread("phw.jpg");

	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);
	srcPts[1] = Point2f(src.cols - 1, 0);
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
	dstPts[0] = Point2f(50, 50);
	dstPts[1] = Point2f(src.cols - 100, 100);
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

	Mat M = getAffineTransform(srcPts, dstPts);

	Mat dst;
	warpAffine(src, dst, M, Size());

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main(void) {
	affine_translation();
	affine_shear();
	affine_scale();
	affine_rotation();
	affine_flip();
	affine_transform();
	return 0;
}