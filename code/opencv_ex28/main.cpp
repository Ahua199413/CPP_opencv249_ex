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

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}

Mat src, dst;
const char* output_win = "findcontours-demo";
int threshold_value = 100;
int threshold_max = 255;
RNG rng;
void Demo_Contours(int, void*);
int main()
{
	Mat srcImg = imread("Patrick Star.jpg");
	if (!srcImg.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        namedWindow("input-image", CV_WINDOW_AUTOSIZE);
        imshow("input-image",srcImg);
        namedWindow(output_win, CV_WINDOW_AUTOSIZE);
        cvtColor(srcImg, src, CV_BGR2GRAY);

        const char* trackbar_title = "Threshold Value:";
        createTrackbar(trackbar_title, output_win, &threshold_value, threshold_max, Demo_Contours);
        Demo_Contours(0, 0);
    }
    waitKey(0);
    Pause();
    return 0;
}
void Demo_Contours(int, void*) {
	Mat canny_output;
	vector< vector<Point> > contours;
	vector<Vec4i> hierachy;

    /*
    OpenCV canny
        void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)

            src�G��J�ϡA��q�D8�줸�ϡC
            dst�G��X�ϡA�ؤo�B���A�M��J�ϬۦP�C
            threshold1�G�Ĥ@���H�ȡC
            threshold2�G�ĤG���H�ȡC
            apertureSize �GSobel��l���֤ߤj�p�C
            L2gradient �G��פj�p����k�A�w�]��false�C
    */
	Canny(src, canny_output, threshold_value, threshold_value * 2, 3, false);
    /*
    OpenCV�����
        void findContours(InputOutputArray image, OutputArrayOfArrays contours, int mode, int method, Point offset=Point())

            image�G��J�ϡA�ϥΤK�줸��q�D�ϡA�Ҧ��D�s���������|�C�J�Ҽ{�A�q�`���G���ƫ᪺�ϡC
            contours�G�]�t�Ҧ��������e��(vector)�A�C�ӽ������O�x�s�I���e��(vector)�A�ҥHcontours����Ƶ��c��vector< vector>�C
            hierarchy�G�i���i�L����X�V�q�A�H���h���覡�O���Ҧ������C
            mode�G���o�������Ҧ��C
                CV_RETR_EXTERNAL�G�u���̥~�h�������C
                CV_RETR_LIST�G���o�Ҧ������A���إ߶��h(hierarchy)�C
                CV_RETR_CCOMP�G���o�Ҧ������A�x�s����h�����h�A�����h������~��A�ĤG���h�������Ť߳����������A�p�G�󤺳�����l����A�]�t�󭺶��h�C
                CV_RETR_TREE�G���o�Ҧ������A�H�����h���覡�x�s�C
            method�G�x�s�����I����k�A���H�U�X�إi��ܡG
                CV_CHAIN_APPROX_NONE�G�x�s�Ҧ������I�C
                CV_CHAIN_APPROX_SIMPLE�G������B�����B�﨤�u�d�U�Y���I�A�ҥH���p�������@�x�ΡA�u�x�s�﨤���|�ӳ��I�C
    */
	findContours(canny_output, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	dst = Mat::zeros(src.size(), CV_8UC3);//CV_8UC3	�줸�`�׬�8�A�L�t���A�q�D��3 -> 0~255,BGR

	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++) {

		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    /*
    OpenCV�e�����u
        void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point())

            image�G��J��X�ϡA�|�N�����e�b���v���W�C
            contours�G�]�t�Ҧ��������e��(vector)�A�]�N�OfindContours()�ҧ�쪺contours�C
            contourIdx�G���w�e�Y�ӽ����C
            color�Gø�s���C��C
            lineType�Gø�s���u�����A�C
            hierarchy�G�������h�A�]�N�OfindContours()�ҧ�쪺hierarchy�C
            maxLevel�G�̤j���h�������A�i�H���w�Q�n�e�������A����Jhierarchy�ɤ~�|�Ҽ{�A��J���ȥN��ø�s���h�ơC
    */
		drawContours(dst, contours, i, color, 1, 8, hierachy, 0, Point(0, 0));
	}

	imshow(output_win, dst);
}
