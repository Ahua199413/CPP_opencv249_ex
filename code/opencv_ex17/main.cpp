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

        Mat Scharr_x, Scharr_y;
        /*
        void Scharr(InputArray src, OutputArray dst, int ddepth, int dx, int dy, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)

        �άOSobel(src, dst, ddepth, dx, dy, CV_SCHARR)�A��̮ĪG�ۦP�C

        src�G��J�ϡC
        dst�G��X�ϡA�M��J�Ϧ��ۦP���ؤo�M�q�D�ơC
        ddepth�G��X�Ϫ��`�סA�ϥΤ覡�MSobel�ۦP�C
        dx�Gx��V���L�����ơC
        dy�Gy��V���L�����ơC
        scale�G�Y���
        delta�G�����q�C
        */
        Scharr(gray_src, Scharr_x, CV_16S, 1, 0);
        Scharr(gray_src, Scharr_y, CV_16S, 0, 1);
        convertScaleAbs(Scharr_x, Scharr_x);
        convertScaleAbs(Scharr_y, Scharr_y);
        //--imshow("Scharr_x", Scharr_x);
        //--imshow("Scharr_y", Scharr_y);


        /*
        void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
        src�G��J�ϡC
        dst�G��X�ϡA�M��J�Ϧ��ۦP���ؤo�M�q�D�ơC
        ddepth�G��X�Ϫ��`�סA���]��J�Ϭ�CV_8U, �䴩CV_8U�BCV_16S�BCV_32F�BCV_64F�A���]��J�Ϭ� CV_16U, �䴩CV_16U�BCV_32F�BCV_64F�C
        dx�Gx��V���L�����ơC
        dy�Gy��V���L�����ơC
        ksize�G�֤ߡA������1�B3�B5��7�C
        scale�G�Y��ȡC
        delta�G�����q�C
        */
        Mat Sobel_x, Sobel_y;
        Sobel(gray_src, Sobel_x, CV_16S, 1, 0, 3);
        Sobel(gray_src, Sobel_y, CV_16S, 0, 1, 3);
        /*
        �p���J�ϦU�����A�ñN���G�ন8�줸��
        void convertScaleAbs(InputArray src, OutputArray dst, double alpha=1, double beta=0)
        src�G��J�ϡC
        dst�G��X�ϡC
        alpha�G��ܩʪ����k�]�l�C
        beta�G��ܩʪ��[�k�]�l�C
        ���禡�D�n�i��3�B�J�F1.�p�� 2.������� 3.�ন�L���t��8�줸��
        */
        convertScaleAbs(Sobel_x, Sobel_x);
        convertScaleAbs(Sobel_y, Sobel_y);
        imshow("Sobel_x", Sobel_x);
        imshow("Sobel_y", Sobel_y);

        Mat Sobel_xy = Mat(Sobel_x.size(), Sobel_x.type());
        int width = Sobel_x.cols;
        int height = Sobel_y.rows;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int xg = Sobel_x.at<uchar>(row, col);
                int yg = Sobel_y.at<uchar>(row, col);
                int xy = xg + yg;
                /*
                ��saturate_cast�N�C�����p�⵲�G���w�b�X�z�d��A�H���Ҩӻ��N�O�q0��255�A�W�L255�|�]�w��255�A�p��0�|�]�w��0�C
                OpenCV ���w�X�z�d��Gtemplate< �K > _Tp saturate_cast(_Tp2 v)
                v�G��J�ѼơA�|�����Ȧb�X�z�d��C
                saturate_cast�ϥμҪO�A�ҥH�I�s�ɭn���w�����`�סC
                */
                Sobel_xy.at<uchar>(row, col) = saturate_cast<uchar>(xy);
            }
        }
        imshow("Sobel_xy", Sobel_xy);

        Mat Sobel_x_y01 = Mat(Sobel_x.size(), Sobel_x.type());
        /*
        OpenCV�v���ۥ[�Gvoid addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1)
        src1�G��J�ϡC
        alpha�Gsrc1���v���C
        src2�G��J�ϡA�Msrc1���ؤo�M�q�D�ƬۦP�C
        beta�Gsrc2���v���C
        gamma�G��Ϭۥ[��A�W�[���ȡC
        dst�G��X�ϡA��X�x�}�M��J�x�}���ۦP���ؤo�M�q�D�ơC
        dtype�G�i���i�L����X�ϲ`�סC
        */
        addWeighted(Sobel_x, 0.5, Sobel_y, 0.5, 0, Sobel_x_y01);//Sobel_x*0.5+Sobel_y*0.5
        imshow("Sobel_x+y01", Sobel_x_y01);

        Mat Sobel_x_y02 = Mat(Sobel_x.size(), Sobel_x.type());//Sobel_x+Sobel_y
        /*
        OpenCV�v���ۥ[�Gvoid add(InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)

        src1 �G��J�ϩαj�׭ȡC
        src2 �G��J�ϩαj�׭ȡC
        dst�G��X�ϡA��X�ϩM��J�Ϧ��ۦP���ؤo�M�q�D�ơC
        mask�G�i���i�L���B�n�A8�줸��q�D�ϡA���w���ǹ����n�p��C
        dtype�G�i���i�L����X�ϲ`�סC
        */
        add(Sobel_x, Sobel_y, Sobel_x_y02);
        imshow("Sobel_x+y02", Sobel_x_y02);
    }
    waitKey(0);
    Pause();
    return 0;
}
