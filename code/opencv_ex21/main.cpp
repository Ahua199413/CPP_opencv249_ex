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
    Mat input;
	input = imread("hough02.png");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        src=input.clone();

        char INPUT_TITLE[] = "input image";
        char OUTPUT_TITLE[] = "hough circle demo";
        namedWindow(INPUT_TITLE, CV_WINDOW_AUTOSIZE);
        namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
        imshow(INPUT_TITLE, src);

        Mat src_gray,dst;
        Canny(src, src_gray, 150, 200);
        imshow("edge image", src_gray);

        /*
        OpenCV ������
        void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, doubleparam2=100, int minRadius=0, int maxRadius=0)

        image�G��J�ϡA8�줸��q�D�ϡC
        circles�G�Hvector< Vec3f >�O���Ҧ��ꪺ��T�A�C��Vec3f�����@�Ӷꪺ��T�A�]�t3�ӯB�I�Ƹ�ơA���O���x�By�Bradius�C
        method�G�����ꪺ��k�A�ثe�u��ϥ�CV_HOUGH_GRADIENT�C
        dp�G�����ѪR�׭˼Ƥ�ҡA���]dp=1�A�����ϩM��J�Ϥؤo�ۦP�A���]dp=2�A�����Ϫ��M�e�Ҭ���J�Ϫ��@�b�C
        minDist�G�ꩼ�������̵u�Z���A�Ӥp���ܥi��|��F�񪺴X�Ӷ�����@�ӡA�Ӥj���ܥi��|���L�Y�Ƕ�C
        param1�G�갻�������|�I�sCanny()�M����ɡAparam1�N�OCanny()�����H�ȡA�C�H�Ȧ۰ʳ]�����Ȫ��@�b�C
        param2�G�p���H�ȡA�W�L���Ȫ���~�|�s�Jcircles�C-�վ㭫�n�Ѽ�
        minRadius�G�̤p����b�|�C
        maxRadius�G�̤j����b�|�C
        */

        vector<Vec3f> pcircles;
        HoughCircles(src_gray, pcircles, CV_HOUGH_GRADIENT, 1, 3, 100, 23, 5, 50);

        src.copyTo(dst);
        for (size_t i = 0; i < pcircles.size(); i++) {
            Vec3f cc = pcircles[i];
            circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255), 2, CV_AA);//��P
            circle(dst, Point(cc[0], cc[1]), 2, Scalar(198, 23, 155), 2, CV_AA);//���
        }
        imshow(OUTPUT_TITLE, dst);

    }

    waitKey(0);
    Pause();
    return 0;
}
