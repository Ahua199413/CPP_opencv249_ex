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
        Mat input,gray_src,dst;
	input = imread("Lena_original.jpg");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        //��j
        pyrUp(input, src, Size(input.cols*2, input.rows*2));
        GaussianBlur(src, dst, Size(3, 3), 0, 0);//�����ҽkGaussianBlur�ت����F���Ϲ��w�B�z�ɭԴ�C���n(���T)
        cvtColor(dst, gray_src, CV_BGR2GRAY);//�m����Ƕ�
        imshow("Lena_gray", gray_src);

        Mat edge_image;
        char output_title[] = "Laplaiance Result";
        Laplacian(gray_src, edge_image, CV_16S, 3);
        convertScaleAbs(edge_image, edge_image);

        namedWindow(output_title, CV_WINDOW_AUTOSIZE);
        imshow(output_title, edge_image);

        threshold(edge_image, edge_image, 0, 255, THRESH_OTSU | THRESH_BINARY);
        namedWindow("Laplacian_threshold", CV_WINDOW_AUTOSIZE);
        imshow("Laplacian_threshold", edge_image);
    }
    waitKey(0);
    Pause();
    return 0;
}
