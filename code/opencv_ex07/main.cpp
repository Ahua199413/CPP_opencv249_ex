#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <cstdio>

#include <sys/timeb.h>
#if defined(WIN32)
    #define  TIMEB    _timeb
    #define  ftime    _ftime
    typedef __int64 TIME_T;
#else
    #define TIMEB timeb
    typedef long long TIME_T;
#endif

using namespace cv;
using namespace std;
Mat bgImage;//input image
void MyLines();//OPENCV�e�u
void MyRectangle();//OPENCV�x��
void MyEllipse();//OPENCV�꩷�ξ��
void MyCircle();//OPENCV���
void MyPolygon();//OPENCV���ʳ����N�Ϊ�
void RandomLineDemo();//�H���e�u
void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
	bgImage = imread("bgImage.jpg");
	if (!bgImage.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        MyLines();
        MyRectangle();
        MyEllipse();
        MyCircle();
        MyPolygon();

        putText(bgImage, "Hello OpenCV", Point(300, 300), CV_FONT_HERSHEY_COMPLEX, 1.0, Scalar(12, 23, 200), 3, 8);
        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", bgImage);

        RandomLineDemo();
    }
    waitKey(0);
    Pause();
    return 0;
}
void MyLines() {
	Point p1 = Point(20, 30);
	Point p2;
	p2.x = 400;
	p2.y = 400;
	Scalar color = Scalar(0, 0, 255);
	line(bgImage, p1, p2, color, 1, 8);
}

void MyRectangle() {
	Rect rect = Rect(200, 100, 300, 300);
	Scalar color = Scalar(255, 0, 0);
	rectangle(bgImage, rect, color, 2, 8);
}

void MyEllipse() {
	Scalar color = Scalar(0, 255, 0);
	ellipse(bgImage, Point(bgImage.cols / 2, bgImage.rows / 2), Size(bgImage.cols / 4, bgImage.rows / 8), 90, 0, 360, color, 2, 8);
}

void MyCircle() {
	Scalar color = Scalar(0, 255, 255);
	Point center = Point(bgImage.cols / 2, bgImage.rows / 2);
	circle(bgImage, center, 150, color, 2, 8);
}

void MyPolygon() {
	Point pts[1][5];
	pts[0][0] = Point(100, 100);
	pts[0][1] = Point(100, 200);
	pts[0][2] = Point(200, 200);
	pts[0][3] = Point(200, 100);
	pts[0][4] = Point(100, 100);

	const Point* ppts[] = { pts[0] };
	int npt[] = { 5 };
	Scalar color = Scalar(255, 12, 255);

	fillPoly(bgImage, ppts, npt, 1, color, 8);
}

void RandomLineDemo() {
	RNG rng(12345);//OPENCV�üƺؤl
	Point pt1;
	Point pt2;
	Mat bg = Mat::zeros(bgImage.size(), bgImage.type());//�إߪťյe��
	namedWindow("random line demo", CV_WINDOW_AUTOSIZE);
	for (int i = 0; i < 100000; i++) {
		pt1.x = rng.uniform(0, bgImage.cols);//���üƭ� ����0~X����
		pt2.x = rng.uniform(0, bgImage.cols);
		pt1.y = rng.uniform(0, bgImage.rows);
		pt2.y = rng.uniform(0, bgImage.rows);
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));//�]�w�C��]�O�ζüƨM�w
		if (waitKey(50) > 0) {//�]�w�i�H�H�ɤ��_�{�����\��,50ms�����@����L��J
			break;
		}
		line(bg, pt1, pt2, color, 1, 8);
		imshow("random line demo", bg);
	}
}
