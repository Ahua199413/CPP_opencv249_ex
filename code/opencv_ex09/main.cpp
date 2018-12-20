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
Mat src;//input image
void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
	src = imread("bgImage.jpg");
	if (!src.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        Mat medianBlur;
        Mat bilateralFilter;

        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src);

        char output_title00[] = "medianBlur";
        namedWindow(output_title00, CV_WINDOW_AUTOSIZE);
        cv::medianBlur(src, medianBlur, 3);
        imshow(output_title00, medianBlur);

        char output_title01[] = "bilateralFilter";
        cv::bilateralFilter(src, bilateralFilter, 15, 100, 5);
        //- 15 �V�p�⪺�b�|�A�b�|���������Ƴ��|�Q�ǤJ�p��A�p�G����-1 �h�ھ�sigma space�Ѽƨ���
        //- 150 �V sigma color �M�w�h�֮t�Ȥ����������|�Q�p��
        //- 3 �V sigma space �p�Gd���Ȥj��0�h�n���L�ġA�_�h�ھڥ��ӭp��d��
        namedWindow(output_title01, CV_WINDOW_AUTOSIZE);
        imshow(output_title01, bilateralFilter);

        Mat resultImg00;
        Mat resultImg01;
        Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

        filter2D(medianBlur, resultImg00, -1, kernel, Point(-1, -1), 0);
        namedWindow("medianBlur-Final Result", CV_WINDOW_AUTOSIZE);
        imshow("medianBlur-Final Result", resultImg00);


        filter2D(bilateralFilter, resultImg01, -1, kernel, Point(-1, -1), 0);
        namedWindow("bilateralFilter-Final Result", CV_WINDOW_AUTOSIZE);
        imshow("bilateralFilter-Final Result", resultImg01);
    }
    waitKey(0);
    return 0;
}
