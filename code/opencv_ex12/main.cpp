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
Mat src00;//input image
Mat src01;//GRAY
Mat src02;//BIN
Mat dst01,dst02,dst03,dst04,dst05;

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
	src00 = imread("input.png");
	if (!src00.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        namedWindow("color_input", CV_WINDOW_AUTOSIZE);
        imshow("color_input", src00);

        cvtColor(src00, src01, CV_BGR2GRAY);
        namedWindow("gray_input", CV_WINDOW_AUTOSIZE);
        imshow("gray_input", src01);

        adaptiveThreshold(~src01, src02, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -2);
        //�ϰ���֭�
        //src�G��J�ϡA�u���J8�줸��q�D�ϡC
        //dst�G��X�ϡA�ؤo�j�p�B�`�׷|�M��J�ϬۦP�C
        //maxValue�G�̤j�ȡAadaptiveThreshold�|�N��������0�MmaxValue�C
        //adaptiveMethod�G�ϰ��H�Ȥ�k�G�i�H���ADAPTIVE_THRESH_MEAN_C��ADAPTIVE_THRESH_GAUSSIAN_C�A��̨M�w�H�Ȫ��覡���P�C
        //thresholdType�G�G�Ȥƫ��A�G��THRESH_BINARY�MTHRESH_BINARY_INV��ث��A�i��C
        //blockSize�G�ϰ�ؤo�A�δX�ӹ����ӨM�w�H�ȡA�u���ܩ_�ƹ�3�B5�B7�K�K���C PS �u���V�ʫh�ƭȭn�V�j
        //C�G�`�ơA�p���H�ȮɡA�n�q�����Υ[�v������h���ơC
        namedWindow("binary_input", CV_WINDOW_AUTOSIZE);
        imshow("binary_input", src02);

        //����-��X�������ȬO���c�����л\�U��J�Ϲ����̤j������
        //�G�k-��X�������ȬO���c�����л\�U��J�Ϲ����̤p������

        // �������c����
        Mat hline = getStructuringElement(MORPH_RECT, Size(src00.cols/10, 1), Point(-1, -1));
        // �������c����
        Mat vline = getStructuringElement(MORPH_RECT, Size(1, src00.rows/5), Point(-1, -1));

        morphologyEx(src02, dst01, CV_MOP_OPEN, vline);//�Q�ζ}�B��O�d����
        namedWindow("binary_input_OPEN_vline", CV_WINDOW_AUTOSIZE);
        imshow("binary_input_OPEN_vline", dst01);

        morphologyEx(src02, dst02, CV_MOP_OPEN, hline);//�Q�ζ}�B��O�d����
        namedWindow("binary_input_OPEN_hline", CV_WINDOW_AUTOSIZE);
        imshow("binary_input_OPEN_hline", dst02);

        //---------------------//

        // �x�ε��c-�h���z�Z�u�d�U��r
        dst03 = imread("chars.png",IMREAD_GRAYSCALE);
        adaptiveThreshold(~dst03, dst04, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, -2);
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
        Mat temp;
        erode(dst04, temp, kernel);//�G�k
        dilate(temp, dst05, kernel);//����
        //CV_MOP_OPEN:���G�k�῱��-�i�H�h���p����H�A���]�ﹳ�O�e����A�I���O�¦�
        namedWindow("binary_chars_OPEN", CV_WINDOW_AUTOSIZE);
        imshow("binary_chars_OPEN", dst05);

    }
    waitKey(0);
    return 0;
}
